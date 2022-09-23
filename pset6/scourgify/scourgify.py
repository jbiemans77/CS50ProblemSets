import sys
import csv

def main():
    # Setup config variables
    expectedNumberOfArguments = 3
    numberOfArguments = len(sys.argv)
    ExitIfTooManyOrTooFewArguments(numberOfArguments,expectedNumberOfArguments)

    inputFilename = sys.argv[1]
    expectedInputExtensions = ["csv"]
    outputFileName = sys.argv[2]
    expectedOutputExtensions = ["csv"]

    isExpectedExtensionInput = CheckIfExtensionIsExpected(inputFilename, expectedInputExtensions)
    ExitIfNotIsExpectedExtensionInput(isExpectedExtensionInput, expectedInputExtensions, "Input")

    isExpectedExtensionOutput = CheckIfExtensionIsExpected(outputFileName, expectedOutputExtensions)
    ExitIfNotIsExpectedExtensionInput(isExpectedExtensionOutput, expectedOutputExtensions, "Output")

    table = GetTableDataFromCSV(inputFilename)
    ExitIfInputFileNotFound(table)

    GenerateOutputCSV(outputFileName, table)


def CheckIfExtensionIsExpected(filename, expectedExtensions):
    isExpectedExtension = False

    for expectedExtension in expectedExtensions:
        if "." in filename:
            _, fileExtension = filename.split(".")
            if fileExtension.lower() == expectedExtension.lower():
                isExpectedExtension = True

    return isExpectedExtension


def ExitIfTooManyOrTooFewArguments(numberOfArguments, expectedNumberOfArguments):
    if numberOfArguments < expectedNumberOfArguments:
        sys.exit("Too few command line arguments.")
    elif numberOfArguments > expectedNumberOfArguments:
        sys.exit("Too many command line arguments.")


def ExitIfNotIsExpectedExtensionInput(isExpectedExtension, extension, message):
    if not isExpectedExtension:
        sys.exit(f"{message} is not a {extension} file")


def ExitIfInputFileNotFound(table):
    if not table:
        sys.exit("Input file does not exist")


def GetTableDataFromCSV(filename):
    table = []

    try:
        with open(filename) as file:
            reader = csv.DictReader(file)
            for row in reader:
                last, first = row["name"].split(",")
                student = {"first": first.strip(), "last": last.strip(), "house": row["house"]}
                table.append(student)
    except FileNotFoundError:
        table = []

    return table


def GenerateOutputCSV(outputFileName, table):
    with open (outputFileName, "w") as file:
        writer = csv.DictWriter(file, fieldnames = ["first", "last", "house"])
        writer.writeheader()
        writer.writerows(table)


if __name__ == "__main__":
    main()