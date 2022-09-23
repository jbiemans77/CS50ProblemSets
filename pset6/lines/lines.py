import sys

def main():

    if len(sys.argv) == 1:
        sys.exit("Too few command line arguments.")
    elif len(sys.argv) >= 3:
        sys.exit("Too many command line arguments.")

    filename = sys.argv[1]
    isValidExtension = CheckIfExtensionIsValid(filename, "py")

    if not isValidExtension:
        sys.exit("Not a Python file")

    lineCount = OpenFileAndCountLines(filename)

    if lineCount == -1:
        sys.exit("File does not exist.")
    else:
        print(lineCount)


def OpenFileAndCountLines(filename):
    """
    Opens file and ouputs line count (not including comments and whitespace)
    Outputs -1 if the file is not found
    """
    lineCount = 0

    try:
        with open(filename) as file:
            for line in file:
                line = line.strip()
                validCountableLine = CheckIfLineIsAValidCountableLine(line)

                if validCountableLine:
                    lineCount = lineCount + 1

    except FileNotFoundError:
        lineCount = -1

    return lineCount


def CheckIfLineIsAValidCountableLine(line):
    validCountableLine = True

    isLineBlank = CheckIfLineIsBlank(line)
    if isLineBlank:
        validCountableLine = False

    isAComment = CheckIfLineIsAComment(line)
    if isAComment:
        validCountableLine = False

    return validCountableLine


def CheckIfLineIsAComment(line):
    lineIsAComment = False
    if line.startswith("#"):
        lineIsAComment = True

    return lineIsAComment


def CheckIfLineIsBlank(line):
    lineIsBlank = False
    if not line:
        lineIsBlank = True

    return lineIsBlank


def CheckIfExtensionIsValid(filename, extension):
    isValidExtension = False

    if "." in filename:
        _, fileExtension = filename.split(".")
        if fileExtension == extension:
            isValidExtension = True

    return isValidExtension


if __name__ == "__main__":
    main()