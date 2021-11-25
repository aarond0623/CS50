import csv


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
