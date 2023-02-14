#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Open the memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }


    // Initialize the neccessary variables
    typedef uint8_t BYTE;
    char filename[8];
    int BLOCK_SIZE = 512;
    BYTE buffer [BLOCK_SIZE];
    int counter = 0;
    FILE *output;

    // Loop through the card
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Look for beginning of a JPEG (First three bytes are: 0xff, 0xd8, 0xff)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer [2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the old file
            if (counter != 0)
            {
                fclose(output);
            }
            // Open a new one
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "w");
            fwrite(buffer, 1, BLOCK_SIZE, output);
            counter++;
        }
        // Continue writing until new JPEG is found
        else if (counter > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }
    fclose(output);
    fclose(file);
}

