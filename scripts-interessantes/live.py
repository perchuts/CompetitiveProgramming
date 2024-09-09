import requests
from tabulate import tabulate
import math
from datetime import datetime, timedelta
import time
import random
import hashlib

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

url = "https://codeforces.com/api/contest.standings?contestId=105297&showUnofficial=true"
data = makeRequest(url)

headers = ["#", "Who", "=", "Penalty"]
for i in range(len(data['problems'])):
    headers.append(chr(ord('A') + i))

placar = []

def truncate(text, max_length = 50):
	if len(text) > max_length:
		return text[:max_length] + "..."
	return text

def getStatsByTime(row, seconds, flag=1):
	info = row['problemResults']
	solved = 0
	penalty = 0
	problems = []
	for problem in info:
		if problem['points'] == 1 and problem['bestSubmissionTimeSeconds'] <= seconds:
			solved+=1
			penalty += math.floor(problem['bestSubmissionTimeSeconds']/60) + 20 * problem['rejectedAttemptCount']
			counter = str(problem['rejectedAttemptCount'])
			if (counter == "0"):
				counter = ""
			problems.append("\033[92m+" + counter + "\033[0m")
		else:
			if problem['rejectedAttemptCount'] > 0 and flag:
				problems.append("\033[94m-" + str(problem['rejectedAttemptCount']) + "\033[0m")
			else:
				problems.append(" ")
	return [solved, penalty, problems]

def generateStandings(seconds):
	arr = []
	cadeiras = {
		'party': {
			'participantType': 'CONTESTANT',
			'teamName': '[UFMG] hj tomei 5 tles por esquecer do fast_io',
			'members': [{'handle': 'gustavocruz'}, {'handle': 'mvkaio'}, {'handle': 'perchuts'}]
		},
		'problemResults': [
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 5940,
				'rejectedAttemptCount': 1
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 15960,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 15540,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 3600,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 13980,
				'rejectedAttemptCount': 1
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 13260,
				'rejectedAttemptCount': 4
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 3900,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 4380,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 1380,
				'rejectedAttemptCount': 2
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 540,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 11880,
				'rejectedAttemptCount': 12
			},
			{
				'points': 0,
				'bestSubmissionTimeSeconds': 0,
				'rejectedAttemptCount': 0
			},
		]
	}

	calvos = {
		'party': {
			'participantType': 'CONTESTANT',
			'teamName': '[USP] Tropa dos Calvos',
			'members': [{'handle': 'antoniomsah'}, {'handle': 'nathan_luiz'}, {'handle': 'wnmrmr'}]
		},
		'problemResults': [
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 4320,
				'rejectedAttemptCount': 2
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 7920,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 9000,
				'rejectedAttemptCount': 1
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 5340,
				'rejectedAttemptCount': 1
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 7260,
				'rejectedAttemptCount': 5
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 13620,
				'rejectedAttemptCount': 4
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 660,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 3060,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 1800,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 1020,
				'rejectedAttemptCount': 0
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 2940,
				'rejectedAttemptCount': 1
			},
			{
				'points': 1,
				'bestSubmissionTimeSeconds': 15360,
				'rejectedAttemptCount': 0
			}
		]
	}
	data['rows'].append(cadeiras)
	data['rows'].append(calvos)
	for row in data['rows']:
		partType = row['party']['participantType']
		if partType != 'CONTESTANT' and partType != 'VIRTUAL':
			continue
		flag = (row != cadeiras and row != calvos)
		x = getStatsByTime(row, seconds, flag)
		arr.append([x[0], x[1], row, x[2]])
	sorted_arr = sorted(arr, key=lambda x: (-x[0], x[1]))
	i = 1
	placar = []
	last_solved = -1
	color_index = 0
	for rrow in sorted_arr:
		row = rrow[2]
		name = None
		if 'teamName' in row['party']:
			name = truncate(row['party']['teamName']) + ":"
			for member in row['party']['members']:
				name = name + " " + member['handle'] + ","
			name = name[:-1]
		else:
			name = row['party']['members'][0]['handle']
		if rrow[0] != last_solved:
			last_solved = rrow[0]
			color_index = 1 - color_index
		if color_index == 0:
			info = [i, name, rrow[0], rrow[1]] + rrow[3]
		else:
			info = ["\033[36m" + str(i), "\033[36m" + name + "\033[0m",  "\033[36m" + str(rrow[0]) + "\033[0m", "\033[36m" + str(rrow[1]) + "\033[0m"] + rrow[3]
		placar.append(info)
		i+=1
	print(tabulate(placar, headers=headers, tablefmt="grid"))

now = datetime.now()

specific_time = now.replace(hour=13, minute=50, second=0, microsecond=0)

elapsed_time = (now - specific_time).total_seconds()

generateStandings(elapsed_time)
