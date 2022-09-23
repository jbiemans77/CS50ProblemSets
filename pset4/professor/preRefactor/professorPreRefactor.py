import random
import sys

score = 0

def main():
    level = get_level()
    score = PlayLevel(level)

    print(f"Score: {score}")

    sys.exit()


def get_level():
    validChoice = False

    try:
        levelSelection = int(input("Level: "))
        if levelSelection in [1,2,3]:
            validChoice = True
    except ValueError:
        validChoice = False

    if validChoice:
        return levelSelection
    else:
        get_level()


def generate_integer(level):

    if level == 1:
        rangeStart = 0
        rangeEnd = 9
    else:
        rangeStart = 10**(level-1)
        rangeEnd = (10**level)-1

    randomInt = random.randint(rangeStart, rangeEnd)

    #print(f"{rangeStart} {rangeEnd} {randomInt}")
    return int(randomInt)


def PlayLevel(level):
    numberOfQuestions = 10
    score = 0

    for questionNumber in range(1,numberOfQuestions+1):
        firstInt = generate_integer(level)
        secondInt = generate_integer(level)
        solution = firstInt + secondInt

        numberOfAttemptsLeft = 3
        while True:
            try:
                answer = input(f"{firstInt} + {secondInt} = ")
                if int(answer) == int(solution):
                    score = score + 1
                    break
                else:
                    print("EEE")
            except ValueError:
                print("EEE")

            if numberOfAttemptsLeft == 1:
                print(f"{firstInt} + {secondInt} = {solution}")
                break

            numberOfAttemptsLeft = numberOfAttemptsLeft - 1

    return score

if __name__ == "__main__":
    main()