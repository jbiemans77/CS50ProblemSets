import re
import sys


def main():
    print(convert(input("Hours: ")))


def convert(s):
    returnValue = ""

    inputLower = s.lower().strip()
    expression = r"^.+(?:am|pm) to .+(?:am|pm)$"
    inputContainsExpression = CheckIfInputContainsExpression(inputLower, expression)
    if not inputContainsExpression:
        raise ValueError()

    start, end = inputLower.split("to")

    processedStartTime = ProcessTime(start)
    isValidTime = ValidateProcessedTime(processedStartTime)
    if not isValidTime:
        raise ValueError()

    processedEndTime = ProcessTime(end)
    isValidTime = ValidateProcessedTime(processedEndTime)
    if not isValidTime:
        raise ValueError()

    returnValue = f"{processedStartTime} to {processedEndTime}"

    return returnValue


def CheckIfInputContainsExpression(input, expression):
    inputContainsExpression = False

    input = input.lower()
    search = re.findall(expression, input)

    if len(search) > 0:
        inputContainsExpression = True

    return inputContainsExpression


def ProcessTime(time):
    time = time.strip()
    hoursMinutes, _ = time.split(" ")

    if ":" in hoursMinutes:
        hours, minutes = hoursMinutes.split(":")
    else:
        hours = hoursMinutes.strip()
        minutes = "00"

    if "pm" in time and not (hours == "12"):
        hours = int(hours) + 12

    if "am" in time and hours == "12":
        hours = 0

    if int(hours) < 10:
        hours = f"0{hours}"

    return f"{hours}:{minutes}"


def ValidateProcessedTime(time):
    isValidTime = True
    hours, minutes = time.split(":")

    if int(hours) > 24:
        isValidTime = False
    elif int(minutes) > 59:
        isValidTime = False

    return isValidTime


if __name__ == "__main__":
    main()