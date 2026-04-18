#!/usr/bin/env python3

import argparse
import concurrent.futures
import json
import math
import os
from pathlib import Path
import random
import shutil
import subprocess
import tempfile
import time


DEFAULT_PARAMS = {
    "EMPTY_SCAN_LIMIT": 8,
    "ROUTE_SCAN_LIMIT": 6,
    "DELIVERY_COUNT_W": 4_000_000,
    "DELIVERY_AGE_W": 5_000,
    "DELIVERY_DIST_W": 18_000,
    "PICK_COUNT_W": 2_300_000,
    "PICK_AGE_W": 3_500,
    "PICK_TRAVEL_W": 14_000,
    "PICK_TRIP_W": 500,
    "ALIGN_BONUS": 250_000,
    "ALONG_ROUTE_BONUS": 500_000,
    "TRANSFER_WAIT_BONUS": 350,
    "HUB_LIMIT": 12,
    "TRANSFER_MIN_DIRECT": 6,
    "HUB_TRANSFER_THRESHOLD": 950_000,
}

PARAM_SPECS = {
    "EMPTY_SCAN_LIMIT": ("add", 3, 18),
    "ROUTE_SCAN_LIMIT": ("add", 2, 14),
    "DELIVERY_COUNT_W": ("mul", 500_000, 12_000_000),
    "DELIVERY_AGE_W": ("mul", 500, 20_000),
    "DELIVERY_DIST_W": ("mul", 2_000, 60_000),
    "PICK_COUNT_W": ("mul", 300_000, 8_000_000),
    "PICK_AGE_W": ("mul", 500, 20_000),
    "PICK_TRAVEL_W": ("mul", 2_000, 60_000),
    "PICK_TRIP_W": ("mul", 50, 4_000),
    "ALIGN_BONUS": ("mul", 20_000, 1_200_000),
    "ALONG_ROUTE_BONUS": ("mul", 50_000, 2_000_000),
    "TRANSFER_WAIT_BONUS": ("mul", 0, 5_000),
    "HUB_LIMIT": ("add", 4, 20),
    "TRANSFER_MIN_DIRECT": ("add", 4, 16),
    "HUB_TRANSFER_THRESHOLD": ("mul", 200_000, 2_500_000),
}

TUNABLE_KEYS = list(DEFAULT_PARAMS.keys())


def build_binary(src: Path, out: Path) -> None:
    cmd = ["g++", "-std=c++17", "-O2", "-Wall", "-Wextra", "-o", str(out), str(src)]
    subprocess.run(cmd, check=True)


def solver_args(seed: int, params: dict[str, int]) -> list[str]:
    args = [f"seed={seed}"]
    for key in TUNABLE_KEYS:
        args.append(f"{key}={params[key]}")
    return args


def clamp_param(key: str, value: float) -> int:
    _, lo, hi = PARAM_SPECS[key]
    return max(lo, min(hi, int(round(value))))


def mutate_params(base: dict[str, int], rng: random.Random, temp: float) -> dict[str, int]:
    params = dict(base)
    if rng.random() < 0.35:
        return params

    changes = rng.randint(1, 4 if temp > 0.4 else 2)
    for key in rng.sample(TUNABLE_KEYS, changes):
        mode, lo, hi = PARAM_SPECS[key]
        current = params[key]
        if mode == "add":
            span = max(1, int(round((hi - lo) * (0.10 + 0.25 * temp))))
            delta = rng.randint(-span, span)
            candidate = current + delta
        else:
            sigma = 0.10 + 0.35 * temp
            factor = math.exp(rng.gauss(0.0, sigma))
            candidate = current * factor
        params[key] = clamp_param(key, candidate)

    return params


def run_candidate(
    solver_bin: Path,
    checker_bin: Path,
    test_path: Path,
    params: dict[str, int],
    seed: int,
    tmp_root: Path,
) -> tuple[float | None, Path | None, str]:
    with tempfile.NamedTemporaryFile(prefix=f"{test_path.name}_", suffix=".out", dir=tmp_root, delete=False) as fout:
        candidate_path = Path(fout.name)

    try:
        with test_path.open("rb") as fin, candidate_path.open("wb") as fout:
            proc = subprocess.run(
                [str(solver_bin), *solver_args(seed, params)],
                stdin=fin,
                stdout=fout,
                stderr=subprocess.PIPE,
                text=False,
            )
        if proc.returncode != 0:
            candidate_path.unlink(missing_ok=True)
            stderr = proc.stderr.decode("utf-8", errors="replace").strip()
            return None, None, stderr or "solver failed"

        score_proc = subprocess.run(
            [str(checker_bin), "--single", str(test_path), str(candidate_path), "--quiet"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
        if score_proc.returncode != 0:
            candidate_path.unlink(missing_ok=True)
            msg = score_proc.stderr.strip() or score_proc.stdout.strip() or "invalid output"
            return None, None, msg

        score = float(score_proc.stdout.strip())
        return score, candidate_path, ""
    except Exception as exc:
        candidate_path.unlink(missing_ok=True)
        return None, None, str(exc)


def score_existing(checker_bin: Path, test_path: Path, out_path: Path) -> float | None:
    if not out_path.exists():
        return None
    proc = subprocess.run(
        [str(checker_bin), "--single", str(test_path), str(out_path), "--quiet"],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if proc.returncode != 0:
        return None
    return float(proc.stdout.strip())


def optimize_test(
    test_name: str,
    tests_dir: str,
    out_dir: str,
    tmp_dir: str,
    solver_bin: str,
    checker_bin: str,
    deadline: float,
    base_seed: int,
) -> dict[str, object]:
    tests_dir = Path(tests_dir)
    out_dir = Path(out_dir)
    tmp_dir = Path(tmp_dir)
    solver_bin = Path(solver_bin)
    checker_bin = Path(checker_bin)
    test_path = tests_dir / test_name
    best_out_path = out_dir / f"{test_name}.out"
    meta_path = out_dir / f"{test_name}.json"
    worker_tmp = tmp_dir / test_name
    worker_tmp.mkdir(parents=True, exist_ok=True)

    rng = random.Random((base_seed * 1_000_003 + sum(ord(c) for c in test_name)) & ((1 << 64) - 1))

    best_params = dict(DEFAULT_PARAMS)
    current_params = dict(DEFAULT_PARAMS)
    best_seed = rng.randrange(1 << 32)
    best_score = score_existing(checker_bin, test_path, best_out_path)
    current_score = best_score

    if best_score is None:
        score, candidate_path, msg = run_candidate(solver_bin, checker_bin, test_path, best_params, best_seed, worker_tmp)
        if score is None:
            return {"test": test_name, "status": f"failed to initialize: {msg}"}
        shutil.move(str(candidate_path), best_out_path)
        best_score = score
        current_score = score
        meta_path.write_text(json.dumps({"seed": best_seed, "params": best_params, "score": best_score}, indent=2) + "\n")
    elif meta_path.exists():
        try:
            data = json.loads(meta_path.read_text())
            if isinstance(data, dict):
                best_params.update({k: int(v) for k, v in data.get("params", {}).items() if k in DEFAULT_PARAMS})
                current_params = dict(best_params)
                if "seed" in data:
                    best_seed = int(data["seed"])
        except Exception:
            pass

    accepted = 0
    improved = 0
    iterations = 0
    start_time = time.time()

    while time.time() < deadline:
        elapsed = time.time() - start_time
        total = max(1.0, deadline - start_time)
        frac = min(1.0, elapsed / total)
        temp = max(0.05, 1.0 - frac)

        parent = current_params if rng.random() < 0.75 else best_params
        candidate_params = mutate_params(parent, rng, temp)
        seed = rng.randrange(1 << 32)

        score, candidate_path, _ = run_candidate(solver_bin, checker_bin, test_path, candidate_params, seed, worker_tmp)
        iterations += 1
        if score is None:
            continue

        assert candidate_path is not None
        if best_score is None or score + 1e-9 < best_score:
            best_score = score
            best_params = candidate_params
            current_params = candidate_params
            current_score = score
            best_seed = seed
            shutil.move(str(candidate_path), best_out_path)
            meta_path.write_text(json.dumps({"seed": best_seed, "params": best_params, "score": best_score}, indent=2) + "\n")
            improved += 1
            accepted += 1
            continue

        candidate_path.unlink(missing_ok=True)

        if current_score is None or score <= current_score:
            current_params = candidate_params
            current_score = score
            accepted += 1
            continue

        scale = max(1.0, 0.03 * current_score)
        prob = math.exp(-(score - current_score) / max(1e-9, scale * temp))
        if rng.random() < prob:
            current_params = candidate_params
            current_score = score
            accepted += 1

    return {
        "test": test_name,
        "status": "ok",
        "best_score": best_score,
        "iterations": iterations,
        "improved": improved,
        "accepted": accepted,
        "seed": best_seed,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description="Time-budgeted stochastic search for per-test outputs.")
    parser.add_argument("--tests-dir", default="tests")
    parser.add_argument("--out-dir", default="best_out")
    parser.add_argument("--tmp-dir", default=".opt_tmp")
    parser.add_argument("--solver-src", default="sol.cpp")
    parser.add_argument("--checker-src", default="checker.cpp")
    parser.add_argument("--solver-bin", default="./sol_opt_bin")
    parser.add_argument("--checker-bin", default="./checker_opt_bin")
    parser.add_argument("--seconds", type=int, default=120)
    parser.add_argument("--jobs", type=int, default=max(1, min(os.cpu_count() or 1, 8)))
    parser.add_argument("--tests", default="")
    parser.add_argument("--seed", type=int, default=123456789)
    args = parser.parse_args()

    tests_dir = Path(args.tests_dir)
    out_dir = Path(args.out_dir)
    tmp_dir = Path(args.tmp_dir)
    solver_src = Path(args.solver_src)
    checker_src = Path(args.checker_src)
    solver_bin = Path(args.solver_bin)
    checker_bin = Path(args.checker_bin)

    out_dir.mkdir(parents=True, exist_ok=True)
    tmp_dir.mkdir(parents=True, exist_ok=True)

    build_binary(solver_src, solver_bin)
    build_binary(checker_src, checker_bin)

    if args.tests:
        tests = [token.strip() for token in args.tests.split(",") if token.strip()]
    else:
        tests = sorted(p.name for p in tests_dir.iterdir() if p.is_file())

    deadline = time.time() + args.seconds

    results: list[dict[str, object]] = []
    with concurrent.futures.ProcessPoolExecutor(max_workers=min(args.jobs, len(tests) or 1)) as pool:
        futures = [
            pool.submit(
                optimize_test,
                test_name,
                str(tests_dir),
                str(out_dir),
                str(tmp_dir),
                str(solver_bin.resolve()),
                str(checker_bin.resolve()),
                deadline,
                args.seed + idx * 1009,
            )
            for idx, test_name in enumerate(tests)
        ]
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            if result.get("status") == "ok":
                print(
                    f"{result['test']}: best={result['best_score']:.2f} "
                    f"iters={result['iterations']} improved={result['improved']}"
                )
            else:
                print(f"{result['test']}: {result['status']}")

    print("\nFinal scores")
    for result in sorted(results, key=lambda x: x["test"]):
        if result.get("status") == "ok":
            print(f"{result['test']}: {result['best_score']:.2f}")
        else:
            print(f"{result['test']}: {result['status']}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
