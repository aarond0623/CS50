// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

const char BLOOD_ALLELES[3] = {'A', 'B', 'O'};

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // If we have exhausted generations:
    if (generations <= 0)
    {
        return NULL;
    }
    // Create generations
    else
    {
        // Allocate memory for new person
        person *current_gen = malloc(sizeof(person));
        for (int i = 0; i < 2; i++)
        {
            current_gen->parents[i] = create_family(generations - 1);
        }
        // Create alleles
        if (generations == 1)
        {
            for (int i = 0; i < 2; i++)
            {
                current_gen->alleles[i] = BLOOD_ALLELES[rand() % 3];
            }
        }
        else
        {
            for (int i = 0; i < 2; i++)
            {
                current_gen->alleles[i] = current_gen->parents[i]->alleles[rand() % 2];
            }
        }
        return current_gen;
    }
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    if (p->parents[0] == NULL)
    {
        free(p);
    }
    else
    {
        free_family(p->parents[0]);
        free_family(p->parents[1]);
        free(p);
    }
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
