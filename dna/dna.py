import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1]) as f:
        reader = csv.reader(f, delimiter=',')
        list_header = []
        for row in reader:
            list_header.append(row)
            break
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        for n in reader:
            database.append(n)
   # print(database[0])

    # TODO: Read DNA sequence file into a variable
    g = open(sys.argv[2], "r")
    for line in g:
        dna_seq = line
    g.close

    # TODO: Find longest match of each STR in DNA sequence
    tested = {}
    header_l = len(list_header[0])
    for i in range(1, header_l, 1):
        target_seq = list_header[0][i]
        repeat_c = longest_match(dna_seq, target_seq)
        tmp = {target_seq: repeat_c}
        tested.update(tmp)
   # print(tested)

    # TODO: Check database for matching profiles
    for i in range(len(database)):
        found = 1
        for j in range(1, header_l, 1):
            tested_c = tested[list_header[0][j]]
            database_c = int(database[i][list_header[0][j]])
            if tested_c != database_c:
                found = 0
                break
        if found == 1:
            break

    if found == 1:
        print(database[i]['name'])
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
