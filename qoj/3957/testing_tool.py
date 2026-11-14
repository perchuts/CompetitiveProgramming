#!/usr/bin/env python3
#
# Testing tool for the Egocentric Expedition problem
#
# Usage:
#
#   python3 testing_tool.py -f <input file> <program invocation>
#
#
# Use the -f parameter to specify the input file, e.g. 1.in.
# The input file should contain one line with the number of test cases.
# Each test case should contain one line with two real numbers, one corner of the square.
#
# You can compile and run your solution as follows:

# C++:
#   g++ solution.cpp
#   python3 testing_tool.py -f 1.in ./a.out

# Python:
#   python3 testing_tool.py -f 1.in python3 ./solution.py

# Rust:
#   rustc solution.rs
#   python3 testing_tool.py -f 1.in ./solution

# Java:
#   javac solution.java
#   python3 testing_tool.py -f 1.in java solution

# Haskell:
#   ghc solution.hs
#   python3 testing_tool.py -f 1.in ./solution


# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it is not an exhaustive test.
# It is not guaranteed that a program that passes this testing tool will be accepted.
# The precision provided by this testing tool may be worse than guarenteed in the statement,
# especially if the input corner coordinates are not very precise.


import argparse
import subprocess
import traceback

parser = argparse.ArgumentParser(description="Testing tool for Egocentric Expedition.")
parser.add_argument(
    "-f",
    dest="inputfile",
    metavar="inputfile",
    default=None,
    type=argparse.FileType("r"),
    required=True,
    help="The input file to use.",
)
parser.add_argument("program", nargs="+", help="Invocation of your solution")

args = parser.parse_args()

with (
    subprocess.Popen(
        " ".join(args.program),
        shell=True,
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
        universal_newlines=True,
    ) as p,
):
    assert p.stdin is not None and p.stdout is not None
    p_in = p.stdin
    p_out = p.stdout

    def write(line: str):
        assert p.poll() is None, "Program terminated early"
        print(f"Write: {line}", flush=True)
        p_in.write(f"{line}\n")
        p_in.flush()

    def read() -> str:
        line = p_out.readline().strip()
        if line == "":
            assert p.poll() is None, "Program terminated early"
        assert line != "", "Read empty line or closed output pipe"
        print(f"Read: {line}", flush=True)
        return line

    eps = 1e-6
    # Parse input
    tests = int(args.inputfile.readline())
    corners = []
    for i in range(tests):
        x, y = map(float, args.inputfile.readline().split())
        corners.append((x, y))
        assert (x*x + y*y) <= 50*50 + eps, "Corner should be no further than 50 from center"
        area = (x**2 + y**2) * 2
        rounded_area = int(round(area))
        assert rounded_area >= 1 and abs(area - rounded_area) < eps, "Area should be (almost) integer and >= 1"

    # Simulate interaction
    try:
        write(tests)
        for test in range(1, tests+1):
            query_cnt = 0
            cornerx, cornery = corners[test-1]
            area = int(round((cornerx**2 + cornery**2) * 2))
            while True:
                line = read().split()
                if line[0] == "?":
                    query_cnt += 1
                    assert query_cnt <= 2, f"Used too many queries in test {test}."

                    assert len(line[1:]) == 2, "query direction should consist of two integers x and y."
                    assert line[1].lstrip("+-").isdecimal(), "x has to be integer."
                    assert line[2].lstrip("+-").isdecimal(), "y has to be integer."
                    x, y = map(int, line[1:])
                    assert (x, y) != (0, 0), "query direction cannot be (0, 0)."
                    assert abs(x) <= 50, "|x| should be at most 50."
                    assert abs(y) <= 50, "|y| should be at most 50."

                    def cross(a, b):
                        return a[0]*b[1] - a[1]*b[0]

                    def dist(p1, p2, p3, p4):
                        a = cross((p2[0]-p1[0], p2[1]-p1[1]), (p4[0]-p3[0], p4[1]-p3[1]))
                        b = cross((p3[0]-p1[0], p3[1]-p1[1]), (p4[0]-p3[0], p4[1]-p3[1]))
                        return ((b/a*p2[0])**2 + (b/a*p2[1])**2) ** 0.5
                    
                    res = 50
                    for c1 in ((cornerx, cornery), (-cornery, cornerx)):
                        c2 = (-c1[1], c1[0])
                        if cross((c2[0]-c1[0], c2[1]-c1[1]), (x, y)) != 0:
                            res = min(res, dist((0, 0), (x, y), c1, c2))
                    write(f"{res:.10f}")

                elif line[0] == "!":
                    assert len(line[1:]) == 1, "Your answer should consist of one integer."
                    assert line[1].lstrip("+-").isdecimal(), "Your answer should be integer."
                    assert int(line[1]) == area, f"Test Case {test}: Your answer is not correct; expected {area}, but got {line[1]}."
                    break
                else:
                    assert False, "Line does not start with \"? \" or \"! \"."

        print()
        print(f"Correctly identified the area {area}.", flush=True)
        print(f"Queries used: {query_cnt}", flush=True)
        assert (line := p_out.readline()) == "", f"Your submission printed extra output: '{line[:100].strip()}{'...' if len(line) > 100 else ''}'"
        print(f"Exit code: {p.wait()}", flush=True)
        assert p.wait() == 0, "Your submission did not exit cleanly after finishing"

    except AssertionError as e:
        print()
        print(f"Error: {e}")
        print()
        print(f"Killing your submission.", flush=True)
        p.kill()
        exit(1)

    except Exception as e:
        print()
        print("Unexpected error:")
        traceback.print_exc()
        print()
        print(f"Killing your submission.", flush=True)
        p.kill()
        exit(1)

