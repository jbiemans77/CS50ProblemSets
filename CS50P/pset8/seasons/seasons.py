from datetime import date
from datetime import datetime
import inflect
import sys

p = inflect.engine()

def main():
    userInput = input("Date of Birth: ")

    isValidDate = ValidateDateFormat(userInput)
    if not isValidDate:
        sys.exit("Invalid date")

    songOutput = GetSongOutput(userInput)

    print(f"{songOutput}")


def GetSongOutput(userInput):
    today = date.today()
    userBirthday = date.fromisoformat(userInput)
    deltaTime =  today - userBirthday
    deltaTimeHours = deltaTime.days * 24
    deltaTimeMinutes = deltaTimeHours * 60

    secondsAsWords = p.number_to_words(deltaTimeMinutes, andword="")
    secondsAsWords = secondsAsWords.capitalize()

    songOutput = f"{secondsAsWords} minutes"

    return songOutput

def ValidateDateFormat(userInput):
    isValidDate = True

    if "-" in userInput:
        try:
            year, month, day = userInput.split("-")

            if not (1800 < int(year) < 3000):
                isValidDate = False
            if int(month) > 12:
                isValidDate = False
            if int(day) > 31:
                isValidDate = False
        except:
            isValidDate = False
    else:
        isValidDate = False

    return isValidDate


if __name__ == "__main__":
    main()