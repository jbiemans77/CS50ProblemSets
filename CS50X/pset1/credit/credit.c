// This is a program to see if a given credit card is valid and output the type.
/* I am having a hard time writing comments becuase when I read
    Clean Code, they argued that comments are clutter and your code
    should speak for itself.  I've been trying to follow that so
    I don't really write comments anymore */

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long FindLengthOfNumber(long number);
int FindDigitAtLocation(long numberToCheck, int location);
int FindFirstSum(long cardNumber, int lengthOfCardNumber);
int FindSecondSum(long cardNumber, int lengthOfCardNumber);
bool CheckIfFinalSumIsAFactorOf10(int totalSum);
bool ValidateCreditCardChecksum(long cardNumber, int lengthOfCardNumber);

void FindCardType(int lengthOfCardNumber, int firstDigit, int secondDigit);
bool CheckIfCardIsAMEX(int lengthOfCardNumber, int firstDigit, int secondDigit);
bool CheckIfCardIsMASTERCARD(int lengthOfCardNumber, int firstDigit, int secondDigit);
bool CheckIfCardIsVISA(int lengthOfCardNumber, int firstDigit, int secondDigit);

int main(void)
{
    long cardNumber = get_long("Please enter your card number: ");
    int firstSum = 0;
    int secondSum = 0;
    int totalSum = 0;
    bool isAValidCard = false;

    int firstDigit;
    int secondDigit;

    int lengthOfCardNumber = FindLengthOfNumber(cardNumber);

    isAValidCard = ValidateCreditCardChecksum(cardNumber, lengthOfCardNumber);

    firstDigit = FindDigitAtLocation(cardNumber, 1);
    secondDigit = FindDigitAtLocation(cardNumber, 2);

    if (!isAValidCard)
    {
        printf("INVALID\n");
    }
    else
    {
        FindCardType(lengthOfCardNumber, firstDigit, secondDigit);
    }
}

// Find the length of a Number
long FindLengthOfNumber(long number)
{
    return floor(log10(labs(number))) + 1;
}

// Method to find the digit at a given location within a number
int FindDigitAtLocation(long numberToCheck, int location)
{
    int digitAtLocation = 0;
    int numberOfDigitsInNumber = FindLengthOfNumber(numberToCheck);
    int valueOfExponent = numberOfDigitsInNumber - (location);
    long dividend = pow(10, valueOfExponent);
    long tempNumberToCheck = numberToCheck / dividend;

    digitAtLocation = tempNumberToCheck % 10;

    return digitAtLocation;
}

//Method to validate the credit card checksum.
bool ValidateCreditCardChecksum(long cardNumber, int lengthOfCardNumber)
{
    bool isAValidCard = false;

    int firstSum = FindFirstSum(cardNumber, lengthOfCardNumber);
    int secondSum = FindSecondSum(cardNumber, lengthOfCardNumber);

    int totalSum = firstSum + secondSum;

    isAValidCard = CheckIfFinalSumIsAFactorOf10(totalSum);

    return isAValidCard;
}

// Method to calculate the first sum for the checksum.
int FindFirstSum(long cardNumber, int lengthOfCardNumber)
{
    int firstSum = 0;
    int digitAtLocation = 0;
    int digitTimesTwo = 0;

    // Start at second last number and then loop through every other number.
    for (int counter = lengthOfCardNumber - 1; counter > 0; counter = counter - 2)
    {
        digitAtLocation = FindDigitAtLocation(cardNumber, counter);
        digitTimesTwo = digitAtLocation * 2;

        // If the number is greater than 10, add the digits of the number to the sum.
        if (digitTimesTwo >= 10)
        {
            digitTimesTwo -= 10;
            digitTimesTwo += 1;
        }

        firstSum = firstSum + digitTimesTwo;
    }

    return firstSum;
}

// Method to calculate the second sum for the checksum.
int FindSecondSum(long cardNumber, int lengthOfCardNumber)
{
    int digitAtLocation = 0;
    int secondSum = 0;

    // Start at last number and loop through every other number.
    for (int counter = lengthOfCardNumber; counter > 0; counter = counter - 2)
    {
        digitAtLocation = FindDigitAtLocation(cardNumber, counter);

        secondSum = secondSum + (digitAtLocation);
    }

    return secondSum;
}


// Method to check is the final sum is a factor of 10.
bool CheckIfFinalSumIsAFactorOf10(int totalSum)
{
    bool isAValidCard = false;

    if (totalSum % 10 == 0)
    {
        isAValidCard = true;
    }

    return isAValidCard;
}

// Method to find the type if card is valid.
void FindCardType(int lengthOfCardNumber, int firstDigit, int secondDigit)
{
    bool isAMEX = CheckIfCardIsAMEX(lengthOfCardNumber, firstDigit, secondDigit);
    bool isMASTERCARD = CheckIfCardIsMASTERCARD(lengthOfCardNumber, firstDigit, secondDigit);
    bool isVISA = CheckIfCardIsVISA(lengthOfCardNumber, firstDigit, secondDigit);

    if (!isAMEX && !isMASTERCARD && !isVISA)
    {
        printf("INVALID\n");
    }
}

// Method to check if the card is an AMEX.
bool CheckIfCardIsAMEX(int lengthOfCardNumber, int firstDigit, int secondDigit)
{
    if (lengthOfCardNumber == 15)
    {
        if (firstDigit == 3)
        {
            if (secondDigit == 4 || secondDigit == 7)
            {
                printf("AMEX\n");
                return true;
            }
        }
    }

    return false;
}

// Method to check if the card is a MASTERCARD.
bool CheckIfCardIsMASTERCARD(int lengthOfCardNumber, int firstDigit, int secondDigit)
{
    if (lengthOfCardNumber == 16)
    {
        if (firstDigit == 5)
        {
            if (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)
            {
                printf("MASTERCARD\n");
                return true;
            }
        }
    }

    return false;
}

// Method to check if the card is a VISA.
bool CheckIfCardIsVISA(int lengthOfCardNumber, int firstDigit, int secondDigit)
{
    if (lengthOfCardNumber == 13 || lengthOfCardNumber == 16)
    {
        if (firstDigit == 4)
        {
            printf("VISA\n");
            return true;
        }
    }

    return false;
}