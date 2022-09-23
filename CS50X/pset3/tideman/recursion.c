#include <stdio.h>
#include <string.h>
#include <cs50.h>

int RecursionCall(int number, int finalNumber, int setNumber);
void PrintSpaces(int number);

int main()
{
    printf("\n");

    int startingNumber = 0;
    int endingNumber = 4;
    int numberOfSetsToCheck = 4;

    for (int i = 0; i < numberOfSetsToCheck; i++)
    {
        startingNumber = i;
        endingNumber = i+2;

        printf("-------->\n");
        RecursionCall(startingNumber,endingNumber, i);
        printf("<--------\n");
    }
}

int RecursionCall(int number, int finalNumber, int setNumber)
{
    int functionCallNumber = number - setNumber;

    PrintSpaces(functionCallNumber);
    printf("Starting call %i. Number: %i\n", functionCallNumber, number);

    if (number == finalNumber)
    {
        PrintSpaces(functionCallNumber);
        printf("It IS %i.  Returning back up.\n\n", finalNumber);
        return number;
    }
    else
    {
        PrintSpaces(functionCallNumber);
        printf("Its not %i it is: %i\n", finalNumber, number);
        PrintSpaces(functionCallNumber);
        printf("Add 1 to the number and call the function again.\n\n");
        number = RecursionCall(number+1, finalNumber, setNumber);   //<-----------------------Recursion Call is here
        PrintSpaces(functionCallNumber);
        printf("Comming Back up, the number is now %i\n",  number);
    }

    PrintSpaces(functionCallNumber);
    printf("Ending Call %i. Number is: %i\n\n",  functionCallNumber, number);
    return number;
}

void PrintSpaces(int number)
{
    for (int i = 0; i < number; i++)
    {
        printf("      ");
    }

    return;
}