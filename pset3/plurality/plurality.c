#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Search for candidate, add 1 to vote total.
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Store an array of integers that will store the index of the winners.
    int winners[candidate_count];
    int maximum = 0;
    // Store the winner count to avoid checking the length of the array.
    int winner_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        int votes = candidates[i].votes;
        if (votes > maximum)
        {
            // If a candidate has the highest number of votes, mark them the
            // winner and reset the number of winners.
            winners[0] = i;
            winner_count = 1;
            maximum = votes;
        }
        else if (votes == maximum)
        {
            // If a candidate ties the winner, add their index to the array and
            // increase the winner count.
            winners[winner_count] = i;
            winner_count++;
        }
    }

    for (int i = 0; i < winner_count; i++)
    {
        // Print the winners up to the winner count.
        printf("%s\n", candidates[winners[i]].name);
    }
    return;
}

