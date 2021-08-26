#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    // Block size on the card
    const int BLOCK_SIZE = 512;

    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: recover <filename>\n");
        return 1;
    }

    char *filename = argv[1];

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename);
    }

    unsigned char buffer[BLOCK_SIZE];
    int count = 0;
    char image_name[8];
    FILE *out_file = NULL;
    int read = 0;

    while (read = fread(buffer, 1, BLOCK_SIZE, file), read > 0 && count < 1000)
    {
        // Look for JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (out_file != NULL)
            {
                // Close the currently open file
                fclose(out_file);
                // Increment file counter by 1
                count++;
            }

            // Name the next file
            sprintf(image_name, "%03i.jpg", count);
            out_file = fopen(image_name, "w");
        }

        // Continue writing to current file
        if (out_file != NULL)
        {
            fwrite(buffer, 1, read, out_file);
        }
    }

    if (out_file != NULL)
    {
        fclose(out_file);
    }

    fclose(file);
}
