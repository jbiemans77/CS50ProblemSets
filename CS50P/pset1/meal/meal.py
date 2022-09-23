def main():
    userInput = input("What time is it? ")
    timeInt = convert(userInput)
    printMealTime(timeInt)


def convert(time):
    timeSplit = time.split(":")
    hours = int(timeSplit[0])
    minutes = int(timeSplit[1])

    decimalHours = minutes / 60
    decimalTime = float(hours + decimalHours)

    return decimalTime


def printMealTime(timeInt):
    if timeInt >= 7 and timeInt <= 8:
        print("breakfast time")
    if timeInt >= 12 and timeInt <= 13:
        print("lunch time")
    if timeInt >= 18 and timeInt <= 19:
        print("dinner time")


if __name__ == "__main__":
    main()