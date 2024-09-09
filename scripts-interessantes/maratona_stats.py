import requests
import pandas as pd
import math

def makeRequest(link):
	response = requests.get(link)
	if response.status_code != 200:
		print(f"FAILED: {response.status_code}")
		return []
	else:
		data = response.json()
		if data['status'] != 'OK':
			print("REQUEST FAILED: " + data['comment'])
			return []
		else:
			return data['result']

class Team:
    def __init__(self, sede, instituicao, time, cf1, cf2, cf3, num_mulheres):
        self.sede = sede
        self.instituicao = instituicao
        self.time = time
        self.cf1 = cf1
        self.cf2 = cf2
        self.cf3 = cf3
        self.num_mulheres = 0 if num_mulheres == 'nan' else num_mulheres
        self.total_rating = 0

    def __repr__(self):
        return (f"Team(Sede={self.sede}, Instituição={self.instituicao}, "
                f"Time={self.time}, CF1={self.cf1}, CF2={self.cf2}, "
                f"CF3={self.cf3}, Nº mulheres={self.num_mulheres})")
# Load the CSV file, skipping the first row if necessary
df = pd.read_csv('dados.csv', skiprows=1)

# Create a list of Team objects
teams = []
for index, row in df.iterrows():
    team = Team(
        sede=row['Sede'],
        instituicao=row['Instituição'],
        time=row['Time'],
        cf1=row['CF1'],
        cf2=row['CF2'],
        cf3=row['CF3'],
        num_mulheres=row['Nº mulheres']
    )
    if type(team.cf1) == str or type(team.cf2) == str or type(team.cf3) == str: 
        teams.append(team)

# Display the list of Team objects
url = "https://codeforces.com/api/user.info?handles="
for team in teams:
    if type(team.cf1) == str:
          url += team.cf1 + ";"
    if type(team.cf2) == str:
          url += team.cf2 + ";"
    if type(team.cf3) == str:
          url += team.cf3 + ";"
url = url[:-1] 

user_objects = {}


data = makeRequest(url)

for user in data: 
    user_objects[user['handle'].lower()] = {'rating': user['rating'] if 'rating' in user else 0, 'rank': user['rank'] if 'rank' in user else 'unrated', 'handle': user['handle']}

from typing import List

def get_win_probability(ra: float, rb: float) -> float:
    return 1.0 / (1.0 + 10 ** ((rb - ra) / 400.0))

def aggregate_ratings(team_ratings: List[float]) -> float:
    left = 1.0
    right = 1e4

    for _ in range(100):
        r = (left + right) / 2.0

        r_wins_probability = 1.0
        for rating in team_ratings:
            r_wins_probability *= get_win_probability(r, rating)

        rating = math.log10(1 / r_wins_probability - 1) * 400 + r

        if rating > r:
            left = r
        else:
            right = r

    return (left + right) / 2.0

for team in teams:
    arr = []
    if type(team.time) == str and len(team.time) > 200:
        team.time = "Os Novos Filhos"
    if type(team.cf1) == str:
        name = team.cf1.lower().rstrip()
        if name in user_objects:
            arr.append(user_objects[name]['rating'])
    if type(team.cf2) == str:
        name = team.cf2.lower().rstrip()
        if name in user_objects:
            arr.append(user_objects[name]['rating'])
    if type(team.cf3) == str:
        name = team.cf3.lower().rstrip()
        if name in user_objects and name != "tourist":
            arr.append(user_objects[name]['rating'])
    team.total_rating = aggregate_ratings(arr) if len(arr) != 0 else 0

sorted_teams = sorted(teams, key = lambda x: x.total_rating)

sorted_teams.reverse()
from tabulate import tabulate

headers = ["Sede", "Instituição", "Time", "Membro 1", "Membro 2", "Membro 3", "# Meninas", "Rating"]

geral = []
oficial = []
ccl = []
g1 = []
g2 = []
g3 = []



from colorama import Fore, Style, init
init()

def getColoredName(name):
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
        
    obj = user_objects[name]
    rank = obj['rank'].lower()
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

for team in sorted_teams:
    m1 = "?"
    m2 = "?"
    m3 = "?"
    if type(team.cf1) == str:
        name = team.cf1.lower().rstrip()
        if name in user_objects:
            m1 = getColoredName(name)
    if type(team.cf2) == str:
        name = team.cf2.lower().rstrip()
        if name in user_objects:
            m2 = getColoredName(name)
    if type(team.cf3) == str and team.cf3 != "tourist":
        name = team.cf3.lower().rstrip()
        if name in user_objects:
            m3 = getColoredName(name)
    if type(team.num_mulheres) == float:
         team.num_mulheres = 0
    r = [
         team.sede,
         team.instituicao,
         team.time,
         m1,
         m2,
         m3,
         team.num_mulheres,
         team.total_rating
    ]
    if team.num_mulheres != '0' and team.num_mulheres != '1' and team.num_mulheres != '2' and team.num_mulheres != '3':
         team.num_mulheres = '0'
    team.num_mulheres = int(team.num_mulheres)
    if team.sede == "CCL":
         ccl.append(r)
    else:
         oficial.append(r)
    if team.num_mulheres >= 1:
         g1.append(r)
    if team.num_mulheres >= 2:
         g2.append(r)
    if team.num_mulheres >= 3:
         g3.append(r)
    geral.append(r)

def get_table_width(table_str):
    # Split the table string into lines
    lines = table_str.split('\n')
    
    # Calculate the width of each row
    widths = [len(line) for line in lines if line.strip()]
    
    # The width of the table is the maximum width among all rows
    return math.ceil(max(widths) * 0.85)
        
def print_ascii_title(title, width=150):
    # Ensure the title fits within the specified width
    title = title.upper()
    padding = (width - len(title)) // 2
    line = '-' * width
    formatted_title = f"{line}\n{' ' * padding}{title}{' ' * padding}\n{line}"
    print(formatted_title)

temp = tabulate(geral, headers=headers, tablefmt="grid")
print_ascii_title("GERAL", get_table_width(temp)) 
print(temp)
temp = tabulate(oficial, headers=headers, tablefmt="grid")
print_ascii_title("OFICIAL", get_table_width(temp)) 
print(temp)
temp = tabulate(ccl, headers=headers, tablefmt="grid")
print_ascii_title("CCL", get_table_width(temp)) 
print(temp)
temp = tabulate(g1, headers=headers, tablefmt="grid")
print_ascii_title("PELO MENOS 1 MENINA", get_table_width(temp)) 
print(temp)
temp = tabulate(g2, headers=headers, tablefmt="grid")
print_ascii_title("PELO MENOS 2 MENINAS", get_table_width(temp)) 
print(temp)
temp = tabulate(g3, headers=headers, tablefmt="grid")
print_ascii_title("PELO MENOS 3 MENINAS", get_table_width(temp)) 
print(temp)
