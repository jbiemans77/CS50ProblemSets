#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

void PerformPrimaryErrorCheckingOnKey(int argc, string argv[]);
void PerformSecondaryErrorCheckingOnKey(int argc, string argv[], string cipherKey);
void DefineErrorCodes();
void PrintErrorCodeToTheScreen();
void CheckIfKeyIsFound(int argc);
void CheckIfTooManyArguments(int argc);
void CheckIfKeyIsTooShort(int lengthOfKey);
void CheckIfKeyIsTooLong(int lengthOfKey);
void CheckKeyForDuplicateOrInvalidCharacters(string cipherKey, int lengthOfKey);
void PerformCipher(string cipherKey);
void PrintCipherText();

int CountNumberOfTimesACharacterOccursInAString(char *string, char character);

char ciphertext[50];

typedef struct
{
    int codeNumber;
    string codeMessage;
}
errorCode;

errorCode errorCodes[10];
int errorCodeNumber = 0;

int main(int argc, string argv[])
{
    //char *cypheredText = "";

    DefineErrorCodes();

    PerformPrimaryErrorCheckingOnKey(argc, argv);

    if (errorCodeNumber == 0)
    {
        string cipherKey = argv[1];
        PerformSecondaryErrorCheckingOnKey(argc, argv, cipherKey);

        if (errorCodeNumber == 0)
        {
            PerformCipher(cipherKey);
        }
    }

    PrintCipherText();

    if (errorCodeNumber != 0)
    {
        PrintErrorCodeToTheScreen();
        return 1;
    }

    return 0;
}

void PrintCipherText()
{
    printf("ciphertext: %s\n",ciphertext);
}

void PerformCipher(string cipherKey)
{
    string plaintext = get_string("plaintext: ");
    int lengthOfPlainText = strlen(plaintext);

    for (int characterLocation = 0; characterLocation < lengthOfPlainText; characterLocation++)
    {
        char plainTextCharacter = plaintext[characterLocation];
        char newLetter;

        if (isupper(plainTextCharacter) != 0)
        {
            newLetter = toupper(cipherKey[plainTextCharacter - 'A']);
        }
        else if (islower(plainTextCharacter) != 0)
        {
            newLetter = tolower(cipherKey[plainTextCharacter - 'a']);
        }
        else
        {
            newLetter = plainTextCharacter;
        }

        ciphertext[characterLocation] = newLetter;
        //printf("%c", newLetter);   <--- Use if more than 50 characters
    }

    //printf("\n"); <--- Use if more than 50 characters
    return;
}

void PerformPrimaryErrorCheckingOnKey(int argc, string argv[])
{
    CheckIfKeyIsFound(argc);
    CheckIfTooManyArguments(argc);
}

void PerformSecondaryErrorCheckingOnKey(int argc, string argv[], string cipherKey)
{
    int lengthOfKey = strlen(cipherKey);

    CheckIfKeyIsTooShort(lengthOfKey);
    CheckIfKeyIsTooLong(lengthOfKey);

    if (errorCodeNumber != 0)
    {
        return;
    }

    CheckKeyForDuplicateOrInvalidCharacters(cipherKey, lengthOfKey);
}

void DefineErrorCodes()
{
    errorCodes[1].codeNumber = 1;
    errorCodes[1].codeMessage = "Please type the key as a command line argument.\n";

    errorCodes[2].codeNumber = 2;
    errorCodes[2].codeMessage = "Too many arguments, please try again.\n";

    errorCodes[3].codeNumber = 3;
    errorCodes[3].codeMessage = "Key is too short. Must contain 26 characters.\n";

    errorCodes[4].codeNumber = 4;
    errorCodes[4].codeMessage = "Key is too long. Must contain 26 characters.\n";

    errorCodes[5].codeNumber = 5;
    errorCodes[5].codeMessage = "Duplicate character found in key.\n";

    errorCodes[6].codeNumber = 6;
    errorCodes[6].codeMessage = "Invalid character found in key\n";
}

void PrintErrorCodeToTheScreen()
{
    printf("CODE: %i - %s", errorCodes[errorCodeNumber].codeNumber, errorCodes[errorCodeNumber].codeMessage);
}

void CheckIfKeyIsFound(int argc)
{
    if (argc == 1)
    {
        errorCodeNumber = 1;
    }
}

void CheckIfTooManyArguments(int argc)
{
    if (argc >= 3)
    {
        errorCodeNumber = 2;
    }
}

void CheckIfKeyIsTooShort(int lengthOfKey)
{
    if (lengthOfKey < 25)
    {
        errorCodeNumber = 3;
    }
}

void CheckIfKeyIsTooLong(int lengthOfKey)
{
    if (lengthOfKey > 26)
    {
        errorCodeNumber = 4;
    }
}

void CheckKeyForDuplicateOrInvalidCharacters(string cipherKey, int lengthOfKey)
{
    for (int characterLocation = 0; characterLocation < lengthOfKey; characterLocation++)
    {
        char character = cipherKey[characterLocation];
        char characterUpper = toupper(character);
        char characterLower = tolower(character);

        int numberOfOccurancesUpper = CountNumberOfTimesACharacterOccursInAString(cipherKey, characterUpper);
        int numberOfOccurancesLower = CountNumberOfTimesACharacterOccursInAString(cipherKey, characterLower);
        int characterIsAlpha = isalpha(character);

        if (numberOfOccurancesUpper > 1 || numberOfOccurancesLower > 1)
        {
            errorCodeNumber = 5;
            return;
        }

        if (!characterIsAlpha)
        {
            errorCodeNumber = 6;
            return;
        }
    }

    return;
}

int CountNumberOfTimesACharacterOccursInAString(char *string, char character)
{
    int count = 0;

    for (int characterPositionCounter = 0; string[characterPositionCounter]; characterPositionCounter++)
    {
        if (string[characterPositionCounter] == character)
        {
            count++;
        }
    }

    return count;
}