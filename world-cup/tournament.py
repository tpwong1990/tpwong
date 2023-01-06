# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 10000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        for n in reader:
            n["rating"] = int(n["rating"])
            teams.append(n)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # assign 0 to all temas first
    for n in range(len(teams)):
        counts.update({teams[n]["team"]: 0})

    # run simulation
    for i in range(N - 1):
        tour_winner = simulate_tournament(teams)
        if tour_winner in counts:
            counts.update({tour_winner: counts[tour_winner] + 1})

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


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

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # do first round
    first_winner = simulate_round(teams)

    # do second round
    second_winner = simulate_round(first_winner)

    # do semi-final
    semi_winner = simulate_round(second_winner)

    # do final
    final_winner = simulate_round(semi_winner)
    winner_name = final_winner[0]["team"]
    return winner_name


if __name__ == "__main__":
    main()
