#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int source, int cand_b);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    // Iterate through pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            int i_pref = preferences[i][j];
            int j_pref = preferences[j][i];
            // Don't add pairs of candidates that are tied.
            if (i_pref == j_pref)
            {
                continue;
            }
            else
            {
                // Add the pair with the winner first.
                if (i_pref > j_pref)
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // First create an array of the strength of each victory.
    int victory[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        int margin = preferences[pairs[i].winner][pairs[i].loser];
        margin -= preferences[pairs[i].loser][pairs[i].winner];
        victory[i] = margin;
    }

    // Sort the margins of victory as well as the pairs.
    // Selection sort
    int index;
    int largest;
    for (int i = 0; i < pair_count; i++)
    {
        do
        {
            index = i;
            largest = victory[i];
            for (int j = i; j < pair_count; j++)
            {
                if (victory[j] > largest)
                {
                    index = j;
                    largest = victory[j];
                }
            }
            int temp = victory[i];
            pair temp_pair = pairs[i];
            victory[i] = victory[index];
            pairs[i] = pairs[index];
            victory[index] = temp;
            pairs[index] = temp_pair;
        }
        while (index != i);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Cycle through pairs
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Cycle through the locked list, looking for the candidate with no locked
    // wins where they are a loser.
    for (int i = 0; i < candidate_count; i++)
    {
        bool win = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                win = false;
                break;
            }
        }
        if (win)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

bool is_cycle(int source, int cand_b)
{
    if (cand_b == source)
    {
        return true;
    }
    bool checks[MAX] = {false};
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[cand_b][i])
        {
            checks[i] = is_cycle(source, i);
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (checks[i] == true)
        {
            return true;
        }
    }
    return false;
}
