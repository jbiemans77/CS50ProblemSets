import re
import sys


def main():
    print(convert(input("Hours: ")))


def convert(s):
    returnValue = ""
    inputLower = s.lower().strip()
    #inputUpper = "8:60 AM to 5:00 PM"

    expression = r"^.+(?:am|pm) to .+(?:am|pm)$"
    inputContainsExpression = CheckIfInputContainsExpression(inputLower, expression)
    if not inputContainsExpression:
        raise ValueError()

    start, end = inputLower.split("to")

    processedStartTime = ProcessTime(start)
    isValidTime = ValidateProcessedTime(processedStartTime)
    if not isValidTime:
        #print("start time invalid")
        raise ValueError()

    processedEndTime = ProcessTime(end)
    isValidTime = ValidateProcessedTime(processedEndTime)
    if not isValidTime:
        #print("end time invalid")
        raise ValueError()

    returnValue = f"{processedStartTime} to {processedEndTime}"

    return returnValue


def ValidateProcessedTime(time):
    isValidTime = True
    hours, minutes = time.split(":")
    #print(f"hours: {hours} mintues: {minutes}")

    if int(hours) > 24:
        #print("bad hours")
        isValidTime = False
    elif int(minutes) > 59:
        #print("bad minutes")
        isValidTime = False

    #print(isValidTime)
    return isValidTime


def ProcessTime(time):
    time = time.strip()
    hoursMinutes, _ = time.split(" ")

    if ":" in hoursMinutes:
        hours, minutes = hoursMinutes.split(":")
    else:
        hours = hoursMinutes.strip()
        minutes = "00"

    #print(time)
    if "pm" in time and not (hours == "12"):
        hours = int(hours) + 12

    if "am" in time and hours == "12":
        hours = 0

    #print(int(hours))
    if int(hours) < 10:
        hours = f"0{hours}"

    #print(f"{hours}:{minutes}")

    return f"{hours}:{minutes}"


def CheckIfInputContainsExpression(input, expression):
    input = input.lower()
    #print(f"{input} {expression}")

    inputContainsExpression = False
    search = re.findall(expression, input)
    #print(search)

    if len(search) > 0:
        inputContainsExpression = True

    return inputContainsExpression


if __name__ == "__main__":
    main()