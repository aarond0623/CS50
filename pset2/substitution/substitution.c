#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int check_valid_input(string key);

int main(int argc, string argv[])
{
    // Only continue if there is 1 and only 1 argument.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Get the key.
    string key = argv[1];

    // Check key validity.
    int invalid = check_valid_input(key);
    if (invalid)
    {
        return invalid;
    }

    // Get our message.
    string plaintext = get_string("plaintext:  ");

    // Convert the message.
    int message_len = strlen(plaintext);
    printf("ciphertext: ");

    for (int i = 0; i < message_len; i++)
    {
        char letter = plaintext[i];
        // Save the uppercase state.
        bool upper = isupper(letter);
        letter = toupper(letter);
        if (letter < 'A' || letter > 'Z')
        {
            // Not a letter.
            printf("%c", letter);
        }
        else if (upper)
        {
            printf("%c", toupper(key[letter - 'A']));
        }
        else
        {
            printf("%c", tolower(key[letter - 'A']));
        }
    }
    printf("\n");
    return 0;

}

int check_valid_input(string key)
{
    // Check that they key is 26 characters long.
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check that each letter appears exactly once. To do that, we will iterate
    // through the key and log it's value, then check if any letter was not
    // logged.
    int letter_log[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        char letter = toupper(key[i]);
        if (letter < 'A' || letter > 'Z')
        {
            // Not a letter.
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        else
        {
            // Log the letter.
            letter_log[letter - 'A'] = letter;
        }
    }

    // Check the letter log.
    for (int i = 0; i < 26; i++)
    {
        if (letter_log[i] == 0)
        {
            printf("Key must contain 26 unique letters.\n");
            return 1;
        }
    }

    // All good.
    return 0;

}
