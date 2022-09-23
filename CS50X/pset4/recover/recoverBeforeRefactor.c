#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
int blockSize = 512;

int main(int argc, char *argv[])
{
 // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file
    FILE *rawFile = fopen(argv[1], "r");
    if (rawFile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int imageNumber = 0;
    //char fileName[15];
    char fileName[8];
    FILE *output = NULL;
    bool firstImageFound = false;
    //sprintf(fileName, "%03d.jpg", imageNumber);

    //printf("%s\n",fileName);

    BYTE *buffer = malloc(blockSize);

    while (fread(buffer, 1, blockSize, rawFile))  //== blockSize
    {
        //printf("%02X:%02X:%02X:%02X\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] >= 0xE0 && buffer[3] <= 0xEF))
        {
            firstImageFound = true;

            if (output != NULL)
            {
               fclose(output);
            }

            //printf("Might Be JPG? Create Image and write buffer.\n");
            //sprintf(fileName, "images/%03d.jpg", imageNumber);
            sprintf(fileName, "%03d.jpg", imageNumber);
            imageNumber++;
            //printf("%s\n", fileName);
            output = fopen(fileName, "w");
            fwrite(buffer, blockSize, 1, output);
        }
        else if (firstImageFound)
        {
            //printf("Writing Block to file.\n");
            fwrite(buffer, blockSize, 1, output);
        }
    }

    // Close files
    free(buffer);
    fclose(rawFile);
    fclose(output);

}