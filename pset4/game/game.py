import sys
import random

def main():
    while True:
        maxNumber = input("Level: ")
        isValid = ValidateUserInput(maxNumber)
        if isValid:
            break

    maxNumber = int(maxNumber)
    correctAnswer = generateCorrectAnswer(maxNumber)

    ProcessUserGuess(correctAnswer, maxNumber)

    sys.exit("Just Right!")


def generateCorrectAnswer(maxNumber):
    if maxNumber == 1:
        correctAnswer = 1
    else:
        correctAnswer = int(random.randrange(1, maxNumber))

    return correctAnswer


def ProcessUserGuess(correctAnswer, maxNumber):
    while True:
        userGuess = input("Guess: ")
        isValid = ValidateUserInput(userGuess)
        if isValid:
            userGuess = int(userGuess)
            isWithinRange = CheckIfGuessBetweenOneAndMaxNumber(userGuess, maxNumber)

            PrintResponse(userGuess, correctAnswer)

            if userGuess == correctAnswer:
                break


def ValidateUserInput(maxNumber):
    isValid = False
    if maxNumber.isnumeric():
        if int(maxNumber) >= 1:
            isValid = True

    return isValid


def CheckIfGuessBetweenOneAndMaxNumber(userGuess, maxNumber):
    isWithinRange = False

    if userGuess <= maxNumber:
        isWithinRange = True

    return isWithinRange


def PrintResponse(guess, correctAnswer):
    if guess > correctAnswer:
        print("Too large!")
    elif guess < correctAnswer:
        print("Too small!")


main()