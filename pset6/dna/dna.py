import csv
import re
import sys


def import_STR_data(filename):
    """Imports a CSV file containing data on DNA Short Tandem Repeats (STRs).

    Data should be formatted like so:
    
    name,[STR 1],[STR 2],...

    with the cells underneath the STR headings containing integers for how many
    times an STR repeats in a specific genome.

    Args:
        filename: A CSV file of STR DNA sequences

    Returns:
        A list of dicts with names and STR sequences.

    """
    file = open(filename, 'r')
    data = list(csv.DictReader(file))
    file.close()

    return data


def count_STRs(str, dna):
    """Counts the maximum occurence of consecutive repeats of a given STR.

    Args:
        str: A string of DNA nucleotides (A, G, T, C)
        dna: A longer string of DNA nucleotides.

    Returns:
        The maximum integer of consecutive repeats of the given STR in the DNA
        string.

    """
    sequences = re.findall(f'(?:{str})+', dna)
    try:
        return int(max([len(x) for x in sequences]) / len(str))
    except ValueError:
        # For when we get an empty string, no matches.
        return 0


if __name__ == '__main__':
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Load STRs into memory
    str_data = import_STR_data(sys.argv[1])
    dna_data = ''
    with open(sys.argv[2]) as f:
        dna_data = f.read()

    any_match = False
    for person in str_data:
        # Initially set to True
        match = True
        # Get the STR sequences from the dict keys
        str_sequences = [x for x in person.keys() if x != 'name']
        for sequence in str_sequences:
            # An STR doesn't match
            if count_STRs(sequence, dna_data) != int(person[sequence]):
                match = False
                break
        # Passed all tests
        if match:
            print(person['name'])
            any_match = True

    if not any_match:
        print("No match")
