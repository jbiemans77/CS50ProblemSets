import random
import sys

score = 0

def main():
    numberOfQuestions = 10
    numberOfAttemptsPerQuestion = 3

    level = get_level()
    score = PlayGame(level, numberOfQuestions, numberOfAttemptsPerQuestion)

    print(f"Score: {score}")
    sys.exit()


def get_level():
    levelMin = 1
    levelMax = 3
    validLevelInput = False

    while validLevelInput == False:
        try:
            levelSelection = int(input("Level: "))
            if levelSelection in range(levelMin, levelMax+1):
                validLevelInput = True
        except ValueError:
            validLevelInput = False

    return levelSelection


def PlayGame(level, numberOfQuestions, numberOfAttemptsPerQuestion):
    score = 0

    for questionNumber in range(1,numberOfQuestions+1):
        question = GenerateQuestion(level)
        solution = SolveQuestion(question)
        numberOfAttemptsLeft = numberOfAttemptsPerQuestion
        isUserAnswerCorrect = False

        while numberOfAttemptsLeft > 0:
            userAnswer = GetUserAnswer(question)

            if not(userAnswer == -1):
                isUserAnswerCorrect = CheckUserAnswerAgainstSolution(userAnswer, solution)

            if isUserAnswerCorrect:
                break
            else:
                PrintErrorMessage()

            numberOfAttemptsLeft = numberOfAttemptsLeft - 1

        if isUserAnswerCorrect:
            score = score + 1
        else:
            PrintSolution(question, solution)

    return score


def GenerateQuestion(level):
    firstInt = generate_integer(level)
    secondInt = generate_integer(level)
    operator = "+"
    #operators = ["+","-","*","/"]
    #operator = random.choice(operators)

    question = f"{str(firstInt)} {operator} {str(secondInt)} = "

    return question


def generate_integer(level):
    if level == 1:
        rangeStart = 0
        rangeEnd = 9
    else:
        rangeStart = 10**(level-1)
        rangeEnd = (10**level)-1

    randomInt = random.randint(rangeStart, rangeEnd)

    return int(randomInt)


def SolveQuestion(question):
    solution = -1

    questionParts = question.split(" ")
    firstInt = int(questionParts[0])
    operator = questionParts[1]
    secondInt = int(questionParts[2])

    if operator == "+":
        solution = firstInt + secondInt
    #elif operator == "-":
    #   solution = firstInt - secondInt
    #elif operator == "*":
    #   solution = firstInt * secondInt
    #elif operator == "/":
    #   solution = firstInt / secondInt

    return solution


def GetUserAnswer(question):
    try:
        userAnswer = int(input(f"{question}"))
    except ValueError:
        userAnswer = -1

    return userAnswer


def CheckUserAnswerAgainstSolution(userAnswer, solution):
    answerIsCorrect = False

    if int(userAnswer) == int(solution):
        answerIsCorrect = True

    return answerIsCorrect


def PrintSolution(question, solution):
    print(f"{question}{solution}")


def PrintErrorMessage():
    print("EEE")


if __name__ == "__main__":
    main()