// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Function prototypes
void CopyWavHeaderFromInputToOutput(FILE *input, FILE *output);
void AdjustInputVolumeByFactorAndWriteToOutput(float factor, FILE *input, FILE *output);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // <----- Program starts here after initial command line checks have passed.
    float factor = atof(argv[3]);

    CopyWavHeaderFromInputToOutput(input, output);
    AdjustInputVolumeByFactorAndWriteToOutput(factor, input, output);

    // Close files
    fclose(input);
    fclose(output);
}

void AdjustInputVolumeByFactorAndWriteToOutput(float factor, FILE *input, FILE *output)
{
    BYTE sampleBuffer;

    while (fread(&sampleBuffer, sizeof(int16_t), 1, input))
    {
        sampleBuffer *= factor;
        fwrite(&sampleBuffer, sizeof(int16_t), 1, output);
    }
}
void CopyWavHeaderFromInputToOutput(FILE *input, FILE *output)
{
    uint8_t headerBuffer[HEADER_SIZE];

    fread(&headerBuffer, HEADER_SIZE, 1, input);
    fwrite(&headerBuffer, HEADER_SIZE, 1, output);
}
