// This is a program to draw a mario pyramid with a height based on user input.
/* I am having a hard time writing comments becuase when I read
    Clean Code, they argued that comments are clutter and your code
    should speak for itself.  I've been trying to follow that so
    I don't really write comments anymore */

#include <cs50.h>
#include <stdio.h>

void PrintCharacterToScreenNTimes(string characterToBePrinted, int numberOfCharactersToAdd);
bool CheckIfInputIsBetweenTwoNumbers(int inputToBeChecked, int lowerBound, int upperBound);

int main(void)
{
    bool isProperInputValue = false;
    int heightOfPyramid;

    int numberOfSpacesBetweenBricks = 2;
    int lowestHeight = 1;
    int highestHeight = 8;

    // Get input from user for height and loop until input meets criteria.
    while (isProperInputValue == false)
    {
        heightOfPyramid = get_int("Enter a number between %i and %i: ", lowestHeight, highestHeight);

        isProperInputValue = CheckIfInputIsBetweenTwoNumbers(heightOfPyramid, lowestHeight, highestHeight);
    }

    // Loop through each level of the pyramid and print to the screen
    for (int pyramidLevel = 1; pyramidLevel <= heightOfPyramid; pyramidLevel++)
    {
        int numberOfSpaces = heightOfPyramid - pyramidLevel;
        int numberOfBricks = pyramidLevel;

        PrintCharacterToScreenNTimes(" ", numberOfSpaces);
        PrintCharacterToScreenNTimes("#", numberOfBricks);
        PrintCharacterToScreenNTimes(" ", numberOfSpacesBetweenBricks);
        PrintCharacterToScreenNTimes("#", numberOfBricks);

        printf("\n");
    }
}

// Method to print characters to the screen N times
void PrintCharacterToScreenNTimes(string characterToBePrinted, int numberOfCharactersToAdd)
{
    for (int counter = 0; counter < numberOfCharactersToAdd; counter++)
    {
        printf("%s", characterToBePrinted);
    }
}

// Method to check if input is between two numbers
bool CheckIfInputIsBetweenTwoNumbers(int inputToBeChecked, int lowerBound, int upperBound)
{
    if (inputToBeChecked >= lowerBound && inputToBeChecked <= upperBound)
    {
        return true;
    }
    return false;
}