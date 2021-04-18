#include <cs50.h>
#include <stdio.h>

int population_growth(int start, float births, float deaths);

int main(void)
{
    // Initialize start size and end size.
    int start_size, end_size;
    // Prompt for start size. The minimum population size is 9.
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // Prompt for end size.
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // The birth and death rates.
    float births = 1.0 / 3.0;
    float deaths = 1.0 / 4.0;

    // Calculate number of years until we reach threshold
    int years = 0;
    int current_size = start_size;
    while (current_size < end_size)
    {
        current_size = population_growth(current_size, births, deaths);
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}

int population_growth(int start, float births, float deaths)
{
    // Calculates the population after one year if there are a certain fraction
    // of births and a certain fraction of deaths, as ratios of the starting
    // population.
    return start + (int)(start * births) - (int)(start * deaths);
}
