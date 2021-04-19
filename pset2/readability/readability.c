#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int counter(int text_len, string text);

int main(void)
{
    // Prompts the user for a string and computes a grade level for the text
    // using the Coleman-Liau index, where:
    // grade level = 0.0588 * L - 0.296 * S - 15.8
    // where L is the number of letters per 100 words in a text, and S is the
    // number of sentences per 100 words in a text.

    // Get text input from the user:
    string text = get_string("Text: ");
    // Get the text length.
    int text_len = strlen(text);
    // Initialize our counts:
    int letters = 0;
    int words = 0;
    int sentences = 0;
    
    // Iterate through our text.
    for (int i = 0; i < text_len; i++)
    {
        // Uppercase everything to make it easier.
        char letter = toupper(text[i]);
        // If a character is a letter, update our letter count.
        if (letter >= 'A' && letter <= 'Z')
        {
            letters++;
            // If the text ends in a letter, we need to add 1 to both words
            // and sentences.
            if (i == text_len - 1)
            {
                sentences++;
                words++;
            }
        }
        // When we reach terminating punctuation, count a sentence.
        else if (letter == '.' || letter == '?' || letter == '!')
        {
            sentences++;
            // If the text ends in punctuation, we need to add 1 to words.
            if (i == text_len - 1)
            {
                words++;
            }
        }
        else if (letter == ' ')
        {
            words++;
            // If the text ends in a space, we need to add 1 to sentences.
            if (i == text_len - 1)
            {
                sentences++;
            }
        }
    }

    // Calculate our letter and sentence averages.
    float letter_avg = letters / (float) words * 100;
    float sentence_avg = sentences / (float) words * 100;
    // Print the grade level rounded to the nearest integer.
    int level = round(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8);
    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}
