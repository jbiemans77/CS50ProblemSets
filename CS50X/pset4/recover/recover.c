#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
int blockSize = 512;

FILE *rawFile = NULL;
FILE *output = NULL;

int imageNumber = 0;
char fileName[8];
bool firstImageFound = false;

// Function Prototypes:
void RecoverImagesFromRawFile();
bool DoesTheBufferContainTheJPGSignatureBytes(BYTE buffer[]);
void CloseOutputFileIfItIsOpen();
void GetNextImageFilename();
void OpenNewOutputFileWithFilename();
void WriteBufferToOutputFile(BYTE buffer[]);
void CloseFiles();

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file
    rawFile = fopen(argv[1], "r");
    if (rawFile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    RecoverImagesFromRawFile();
    CloseFiles();
}

void CloseFiles()
{
    fclose(rawFile);
    fclose(output);
}

void RecoverImagesFromRawFile()
{
    BYTE *buffer = malloc(blockSize);

    while (fread(buffer, 1, blockSize, rawFile) == blockSize)
    {
        bool bufferContainsJPGSignatureBytes = DoesTheBufferContainTheJPGSignatureBytes(buffer);

        if (bufferContainsJPGSignatureBytes)
        {
            firstImageFound = true;

            CloseOutputFileIfItIsOpen();
            GetNextImageFilename();
            OpenNewOutputFileWithFilename();
            WriteBufferToOutputFile(buffer);
        }
        else if (firstImageFound)
        {
            WriteBufferToOutputFile(buffer);
        }
        else
        {
            // First JPG signature bytes have not been found yet, move on to next block;
        }
    }

    free(buffer);
}

bool DoesTheBufferContainTheJPGSignatureBytes(BYTE buffer[])
{
    if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] >= 0xE0 && buffer[3] <= 0xEF))
    {
        return true;
    }

    return false;
}

void CloseOutputFileIfItIsOpen()
{
    if (output != NULL)
    {
        fclose(output);
    }
}

void GetNextImageFilename()
{
    sprintf(fileName, "%03d.jpg", imageNumber);
    imageNumber++;
}

void OpenNewOutputFileWithFilename()
{
    output = fopen(fileName, "w");
}

void WriteBufferToOutputFile(BYTE buffer[])
{
    fwrite(buffer, blockSize, 1, output);
}