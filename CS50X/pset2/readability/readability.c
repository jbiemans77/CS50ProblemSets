#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void CountLettersWordsAndSentencesInText(string userText);
void CheckForLetter(char currentCharacter);
void AddToLetterCount();
void CheckForWord(char currentCharacter);
void AddToWordCount();
void IncreaseWordCountForFinalWordIfNeeded();
void CheckForSentence(char currentCharacter);
void AddToSentenceCount();

int computeReadabilityIndex(int numberOfLetters, int numberOfWords, int numberOfSentences);
void PrintReadabilityIndexToTheScreen();

int totalNumberOfLettersInText = 0;
int totalNumberOfWordsInText = 0;
int totalNumberOfSentencesInText = 0;

int main(void)
{
    string userText = get_string("Text: ");

    CountLettersWordsAndSentencesInText(userText);
    PrintReadabilityIndexToTheScreen();
}

void CountLettersWordsAndSentencesInText(string userText)
{
    // Reset counters
    totalNumberOfLettersInText = 0;
    totalNumberOfWordsInText = 0;
    totalNumberOfSentencesInText = 0;

    for (int currentPosition = 0; userText[currentPosition] != '\0'; currentPosition++)
    {
        char currentCharacter = userText[currentPosition];

        CheckForLetter(currentCharacter);
        CheckForWord(currentCharacter);
        CheckForSentence(currentCharacter);
    }

    IncreaseWordCountForFinalWordIfNeeded();
}

void CheckForLetter(char currentCharacter)
{
    if (isalpha(currentCharacter))
    {
        AddToLetterCount();
    }
}

void AddToLetterCount()
{
    totalNumberOfLettersInText++;
}

void CheckForWord(char currentCharacter)
{
    // 32 is the ASCII for SPACE
    if (currentCharacter == 32)
    {
        AddToWordCount();
    }
}

void AddToWordCount()
{
    totalNumberOfWordsInText++;
}

void IncreaseWordCountForFinalWordIfNeeded()
{
    // Add 1 to account for the final word after the last space.
    if (totalNumberOfLettersInText > 0 && totalNumberOfWordsInText > 1)
    {
        totalNumberOfWordsInText++;
    }
}

void CheckForSentence(char currentCharacter)
{
    // 46 is the ASCII for . 33 is the ASCII for ! and 63 is the ASCII for ?
    if (currentCharacter == 46 || currentCharacter == 33 || currentCharacter == 63)
    {
        AddToSentenceCount();
    }
}

void AddToSentenceCount()
{
    totalNumberOfSentencesInText++;
}

int computeReadabilityIndex(int numberOfLetters, int numberOfWords, int numberOfSentences)
{
    if (numberOfLetters <= 0 || numberOfWords <= 0 || numberOfSentences <= 0)
    {
        return 0;
    }

    float readabilityIndex;
    float averageNumberOfLettersPerWord = 0;
    float averageNumberOfLettersPer100Words = 0;
    float averageNumberOfSentencesPerWord = 0;
    float averageNumberOfSentencesPer100Words = 0;
    int readabilityIndexRounded = 0;

    averageNumberOfLettersPerWord = ((float)numberOfLetters / numberOfWords);
    averageNumberOfLettersPer100Words = averageNumberOfLettersPerWord * 100;
    averageNumberOfSentencesPerWord = ((float)numberOfSentences / numberOfWords);
    averageNumberOfSentencesPer100Words = averageNumberOfSentencesPerWord * 100;

    readabilityIndex = 0.0588 * averageNumberOfLettersPer100Words - 0.296 * averageNumberOfSentencesPer100Words - 15.8;
    readabilityIndexRounded = round(readabilityIndex);

    return readabilityIndexRounded;
}

void PrintReadabilityIndexToTheScreen()
{
    int readabilityIndex = computeReadabilityIndex(totalNumberOfLettersInText, totalNumberOfWordsInText, totalNumberOfSentencesInText);

    if (readabilityIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readabilityIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", readabilityIndex);
    }
}