# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    EnsureCorrectUsage(sys.argv)

    teams = BuildTeamsDictionaryFromFile(sys.argv[1])

    counts = ClearCountsForAllTeams(teams)
    counts = SimulateNTournaments(N, teams, counts)

    PrintEachTeamsChancesOfWinning(counts)


def EnsureCorrectUsage(arguments):
    if len(arguments) != 2:
        sys.exit("Usage: python tournament.py FILENAME")


def BuildTeamsDictionaryFromFile(filename):
    teams = []
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            team = {"team": row["team"], "rating": int(row["rating"])}
            teams.append(team)

    return teams


def ClearCountsForAllTeams(teams):
    tempCount = {}
    for team in teams:
        tempCount[team["team"]] = 0

    return tempCount


def SimulateNTournaments(N, teams, counts):
    for tournamentNumber in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1
    return counts


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    winner = teams

    while True:
        winner = simulate_round(winner)
        if len(winner) <= 1:
            return winner[0]['team']
            break


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def PrintEachTeamsChancesOfWinning(counts):
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


if __name__ == "__main__":
    main()
