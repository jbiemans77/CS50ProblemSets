# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # TODO: Read teams into memory from file

    teams = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
                team = {"team" : row["team"], "rating" : int(row["rating"])}
                teams.append(team)

    # Testing for values in Dictionary
    # for team in teams:
    #    teamName = team["team"]
    #    teamRating = team["rating"]
    #    print(f"Team: {team['team']}, rating {team['rating']}")

    counts = ClearCountsForAllTeams(teams)

    #for team in counts:
        #print(f"team: {team} score = {counts[team]}")

    # TODO: Simulate N tournaments and keep track of win counts
    for tournamentNumber in range(N):
        winner = simulate_tournament(teams)
        # print(winner)
        #winnerName = winner[0]['team']
        counts[winner] += 1

    #for team in counts:
        #print(f"team: {team} score = {counts[team]}")

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

def ClearCountsForAllTeams(teams):
    # print(teams)
    count = {}

    for team in teams:
        count[team["team"]] = 0
        #count.append(tempList)
    # print(count)
    return count


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    #print(f"Winners: {winners}")
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    winner = teams

    while True:
        winner = simulate_round(winner)
        #print (f"Length of Teams = {len(winner)}")

        if len(winner) <= 1:
            return winner[0]['team']
            break

if __name__ == "__main__":
    main()
