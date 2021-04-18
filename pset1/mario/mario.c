#include <cs50.h>
#include <stdio.h>

void brick_layer(int width);

int main(void)
{
    // Produces a Mario tower, a pyramid with a gap in the middle.
    // Initialize height.
    int height;
    // Ask for a height between 1 and 8.
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Build the pyramid, layer by layer.
    for (int layer = 1; layer <= height; layer++)
    {
        // Pad the layer.
        for (int i = 0; i < (height - layer); i++)
        {
            printf(" ");
        }
        brick_layer(layer);
        printf("  ");
        brick_layer(layer);
        printf("\n");
    }
}

void brick_layer(int width)
{
    // Produces a brick layer for a Mario tower.
    for (int i = 0; i < width; i++)
    {
        printf("#");
    }
}
