import string
import re


def readability(text):
    """Returns a grade level for text based on its Coleman-Liau index.

    The index is defined as:
    grade level = 0.0588 * L - 0.296 * S - 15.8
    where L is the number of letters per 100 words in a text,
    and S is the number of sentences per 100 words in a text.

    Args:
        text: A text string.

    Returns:
        An integer representing the grade level of the text.

    """
    letters = len([x for x in text if x in string.ascii_letters])
    words = len(text.split())
    sentences = len(list(filter(None, re.split('\.[^A-z]|\?[^A-z]|\![^A-z]', text))))

    L = letters / words * 100
    S = sentences / words * 100
    return round(0.0588 * L - 0.296 * S - 15.8)


if __name__ == '__main__':
    text = ""
    while len(text) == 0:
        text = input("Text: ")
    level = readability(text)

    if level < 1:
        print("Before Grade 1")
    elif level > 16:
        print("Grade 16+")
    else:
        print(f"Grade {level}")
