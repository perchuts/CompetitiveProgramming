import requests
from tabulate import tabulate
import math
from datetime import datetime
import sys # Added for better output handling

# --- Your getColoredName function (unchanged) ---
def getColoredName(name, user_objects):
    RESET = '\x1b[0m'
    BOLD = '\x1b[1m'
    UNDERLINE = '\x1b[4m'
    REVERSED = '\x1b[7m'
    # Text Colors
    BLACK = '\x1b[30m'
    RED = '\x1b[31m'
    GREEN = '\x1b[32m'
    YELLOW = '\x1b[33m'
    BLUE = '\x1b[34m'
    MAGENTA = '\x1b[35m'
    CYAN = '\x1b[36m'
    WHITE = '\x1b[37m'
    GRAY = '\x1b[90m'
    ORANGE = '\x1b[38;5;208m'   # Approximate Orange
    # Bright Text Colors
    BRIGHT_BLACK = '\x1b[90m'
    BRIGHT_RED = '\x1b[91m'
    BRIGHT_GREEN = '\x1b[92m'
    BRIGHT_YELLOW = '\x1b[93m'
    BRIGHT_BLUE = '\x1b[94m'
    BRIGHT_MAGENTA = '\x1b[95m'
    BRIGHT_CYAN = '\x1b[96m'
    BRIGHT_WHITE = '\x1b[97m'

    if name not in user_objects:
        return name # Return plain name if user not found

    obj = user_objects[name]
    # Handle cases where 'rank' might not be present (e.g., for unofficial participants)
    rank = obj.get('rank', 'unrated').lower()
    color = ""
    if rank == 'unrated':
        color = BRIGHT_BLACK
    if rank == 'newbie':
        color = GRAY
    if rank == 'pupil':
        color = GREEN
    if rank == 'specialist':
        color = CYAN
    if rank == 'expert':
        color = BRIGHT_BLUE
    if rank == 'candidate master':
        color = MAGENTA
    if rank == 'master':
        color = BRIGHT_YELLOW
    if rank == 'international master':
        color = ORANGE
    if rank == 'grandmaster':
        color = BRIGHT_RED
    if rank == 'international grandmaster':
        color = RED
    if rank == 'legendary grandmaster':
        return f"{BRIGHT_BLACK}{obj['handle'][0]}{RESET}{BRIGHT_RED}{obj['handle'][1:]}{RESET}"

    return f"{color}{obj['handle']}{RESET}"

# --- Utility Functions (mostly unchanged) ---
def makeRequest(link):
    try:
        response = requests.get(link)
        response.raise_for_status() # Raise an exception for bad status codes
        data = response.json()
        if data.get('status') != 'OK':
            print(f"API Error: {data.get('comment', 'Unknown error')}", file=sys.stderr)
            return None
        return data.get('result')
    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}", file=sys.stderr)
        return None

def truncate(text, max_length=50):
    return text[:max_length] + "..." if len(text) > max_length else text

def getStatsByTime(row, seconds, flag=1):
    info = row['problemResults']
    solved = 0
    penalty = 0
    problems = []
    for problem in info:
        if problem.get('points', 0) >= 1 and 'bestSubmissionTimeSeconds' in problem and problem['bestSubmissionTimeSeconds'] <= seconds:
            solved += 1
            penalty += math.floor(problem['bestSubmissionTimeSeconds'] / 60) + 20 * problem['rejectedAttemptCount']
            counter = str(problem['rejectedAttemptCount']) if problem['rejectedAttemptCount'] > 0 else ""
            problems.append(f"\033[92m+{counter}\033[0m")
        else:
            if problem['rejectedAttemptCount'] > 0 and flag:
                problems.append(f"\033[91m-{problem['rejectedAttemptCount']}\033[0m")
            else:
                problems.append(" ")
    return [solved, penalty, problems]

# --- Main Logic ---

# 1. Fetch Contest Standings
url = "https://codeforces.com/api/contest.standings?contestId=106039&showUnofficial=true"
data = makeRequest(url)

if not data:
    sys.exit(1) # Exit if initial request fails

# --- ADDED HARDCODED TEAMS (as in your original script) ---
ufmg = {
        "party": {
            "participantType": "CONTESTANT", "teamName": "[UFMG] Gustavo está dentro de nós",
            "members": [{"handle": "MvKaio"}, {"handle": "gustavocruz"}, {"handle": "perchuts"}]
        }, "problemResults": [
            {"points": 1, "bestSubmissionTimeSeconds": 360, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 5880, "rejectedAttemptCount": 0},
            {"points": 0, "bestSubmissionTimeSeconds": 0, "rejectedAttemptCount": 4}, {"points": 1, "bestSubmissionTimeSeconds": 1680, "rejectedAttemptCount": 1},
            {"points": 1, "bestSubmissionTimeSeconds": 10380, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 3060, "rejectedAttemptCount": 0},
            {"points": 1, "bestSubmissionTimeSeconds": 2520, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 420, "rejectedAttemptCount": 0},
            {"points": 1, "bestSubmissionTimeSeconds": 11700, "rejectedAttemptCount": 2}, {"points": 1, "bestSubmissionTimeSeconds": 4200, "rejectedAttemptCount": 1},
            {"points": 1, "bestSubmissionTimeSeconds": 1860, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 4980, "rejectedAttemptCount": 1},
            {"points": 1, "bestSubmissionTimeSeconds": 660, "rejectedAttemptCount": 0}]
}
unicu = {
        "party": {
            "participantType": "CONTESTANT", "teamName": "IF YOU WIN, YOU LIVE. IF YOU L...U DONT FIGHT, YOU CANT WIN!",
            "members": [{"handle": "defnotmee"}, {"handle": "enzopsm"}]
        }, "problemResults": [
            {"points": 1, "bestSubmissionTimeSeconds": 900, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 10260, "rejectedAttemptCount": 0},
            {"points": 0, "bestSubmissionTimeSeconds": 0, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 2880, "rejectedAttemptCount": 0},
            {"points": 1, "bestSubmissionTimeSeconds": 16680, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 5220, "rejectedAttemptCount": 0},
            {"points": 1, "bestSubmissionTimeSeconds": 3180, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 360, "rejectedAttemptCount": 0},
            {"points": 1, "bestSubmissionTimeSeconds": 12900, "rejectedAttemptCount": 1}, {"points": 1, "bestSubmissionTimeSeconds": 1860, "rejectedAttemptCount": 1},
            {"points": 1, "bestSubmissionTimeSeconds": 1320, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 4800, "rejectedAttemptCount": 1},
            {"points": 1, "bestSubmissionTimeSeconds": 300, "rejectedAttemptCount": 0}]
        }
usp = {
      "party": {
          "participantType": "CONTESTANT", "teamName": "papibaquígrafo trevoso",
          "members": [{"handle": "daviedu"}, {"handle": "dyogobendo"}]
          }, "problemResults": [
              {"points": 1, "bestSubmissionTimeSeconds": 4020, "rejectedAttemptCount": 1}, {"points": 1, "bestSubmissionTimeSeconds": 4980, "rejectedAttemptCount": 2},
              {"points": 0, "bestSubmissionTimeSeconds": 0, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 1200, "rejectedAttemptCount": 0},
              {"points": 1, "bestSubmissionTimeSeconds": 17640, "rejectedAttemptCount": 5}, {"points": 1, "bestSubmissionTimeSeconds": 7620, "rejectedAttemptCount": 0},
              {"points": 1, "bestSubmissionTimeSeconds": 6690, "rejectedAttemptCount": 3}, {"points": 1, "bestSubmissionTimeSeconds": 540, "rejectedAttemptCount": 0},
              {"points": 0, "bestSubmissionTimeSeconds": 0, "rejectedAttemptCount": 0}, {"points": 1, "bestSubmissionTimeSeconds": 10620, "rejectedAttemptCount": 0},
              {"points": 1, "bestSubmissionTimeSeconds": 840, "rejectedAttemptCount": 2}, {"points": 0, "bestSubmissionTimeSeconds": 0, "rejectedAttemptCount": 1},
              {"points": 1, "bestSubmissionTimeSeconds": 1740, "rejectedAttemptCount": 2}]
      }
data['rows'].extend([ufmg, unicu, usp])

# 2. Collect all handles and fetch their data
all_handles = set()
for row in data['rows']:
    for member in row['party']['members']:
        all_handles.add(member['handle'])

handles_str = ";".join(all_handles)
user_info_url = f"https://codeforces.com/api/user.info?handles={handles_str}"
user_data_result = makeRequest(user_info_url)

# 3. Create the user_objects dictionary
user_objects = {user['handle']: user for user in user_data_result} if user_data_result else {}


# --- Modified generateStandings to accept user_objects ---
def generateStandings(seconds, standings_data, user_objects):
    arr = []
    for row in standings_data['rows']:
        partType = row['party']['participantType']
        if partType not in ['CONTESTANT', 'VIRTUAL']:
            continue
        # The 'flag' logic from your script seems to relate to hardcoded teams, keeping it.
        flag = row not in [ufmg, unicu, usp]
        stats = getStatsByTime(row, seconds, flag)
        arr.append([stats[0], stats[1], row, stats[2]])

    sorted_arr = sorted(arr, key=lambda x: (-x[0], x[1]))

    placar = []
    headers = ["#", "Who", "=", "Penalty"] + [chr(ord('A') + i) for i in range(len(standings_data['problems']))]

    for i, rrow in enumerate(sorted_arr, 1):
        row_data = rrow[2]

        # *** MODIFICATION IS HERE ***
        if 'teamName' in row_data['party']:
            team_name = truncate(row_data['party']['teamName'])
            # Use getColoredName for each member
            member_names = ", ".join([getColoredName(m['handle'], user_objects) for m in row_data['party']['members']])
            name_str = f"{team_name}: {member_names}"
        else:
            # For individual participants
            handle = row_data['party']['members'][0]['handle']
            name_str = getColoredName(handle, user_objects)
        # *** END MODIFICATION ***

        info = [i, name_str, rrow[0], rrow[1]] + rrow[3]
        placar.append(info)

    print(tabulate(placar, headers=headers, tablefmt="grid"))

# --- Execution ---
# Using a fixed time for demonstration, but your logic works too.
now = datetime.now()
specific_time = now.replace(hour=14, minute=35, second=0, microsecond=0)
elapsed_time = (now - specific_time).total_seconds()

generateStandings(elapsed_time, data, user_objects)
