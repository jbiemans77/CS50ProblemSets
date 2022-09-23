listOfMonthsByName = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
]


def main():
    while True:
        userInput = input("Date: ").strip()
        passedFormatingCheck = CheckDateFormating(userInput)

        if passedFormatingCheck:
            date = ConvertInputToDate(userInput)
            passedErrorCheck = CheckDateForErrors(date)

            if passedErrorCheck:
                break

    iso8601DateString = ConvertDateToISO8601(date)
    print(iso8601DateString)


def CheckDateFormating(input):
    passedFormatingCheck = False

    if "," in input:
        passedFormatingCheck = True

    if input.count("/") == 2:
        stripedInput = input.replace("/","")
        # Check for letters indicating a word was writtin rather than number.
        # Dates in the / format should only include numbers.
        if stripedInput.isnumeric():
            passedFormatingCheck = True

    return passedFormatingCheck


def ConvertInputToDate(input):
    if "/" in input:
        # Date is in m/d/y format
        inputSplit = input.split("/")

        month = inputSplit[0].strip()
        day = inputSplit[1].strip()
        year = inputSplit[2].strip()

    elif "," in input:
        # Date is in "monthName day, year" format
        inputSplit = input.split(",")
        dayMonthSplit = inputSplit[0].split(" ")

        month = dayMonthSplit[0]
        month = ConvertMonthNameToNumber(month)

        day = dayMonthSplit[1].strip()
        year = inputSplit[1].strip()

    #print(f"day: {day} month: {month} year: {year}")
    date = Date(day, month, year)

    return date


def CheckDateForErrors(date):
    passedErrorCheck = True
    month = str(date.month)
    day = str(date.day)

    if day.isalpha() or month.isalpha():
        passedErrorCheck = False
    else:
        if int(month) > 12:
            passedErrorCheck = False

        if int(day) > 31:
            passedErrorCheck = False

    return passedErrorCheck


def AddLeadingZero(input):
    output = int(input)
    if output < 10:
        output = "0" + str(output)

    return output


def ConvertDateToISO8601(date):
    month = AddLeadingZero(date.month)
    day = AddLeadingZero(date.day)
    year = date.year

    outputDate = str(year) + "-" + str(month) + "-" + str(day)

    return outputDate


def ConvertMonthNameToNumber(month):
    monthNumber = 0
    if month in listOfMonthsByName:
        monthNumber = listOfMonthsByName.index(month) + 1

    return monthNumber


class Date:
    def __init__(self, day, month, year):
        self.day = day
        self.month = month
        self.year = year


main()