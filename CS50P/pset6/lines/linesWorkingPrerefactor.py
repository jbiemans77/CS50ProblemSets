import sys

def main():

    if len(sys.argv) == 1:
        sys.exit("Too few command line arguments.")
    elif len(sys.argv) >= 3:
        sys.exit("Too many command line arguments.")

    filename = sys.argv[1]
    isValidExtension = CheckIfExtensionIsValid(filename)

    if not isValidExtension:
        sys.exit("Not a Python file")

    lineCount = 0

    try:
        with open(filename) as file:
            isPartOfDocString = False

            for line in file:
                line = line.strip()
                validCountableLine = True

                if not line:
                    # Line is white space, ignore
                    validCountableLine = False

                if line.startswith("#"):
                    # This is a comment ignore
                    validCountableLine = False

                #if line.startswith("\"\"\""):
                #    isPartOfDocString = True

                #if isPartOfDocString:
                #    validCountableLine = False

                #    if line.endswith("\"\"\""):
                #        isPartOfDocString = False

                if validCountableLine:
                    lineCount = lineCount + 1

    except FileNotFoundError:
        sys.exit("File does not exist.")

    print(lineCount)


def CheckIfExtensionIsValid(filename):
    isValidExtension = False

    name, extension = filename.split(".")
    if extension == "py":
        isValidExtension = True

    return isValidExtension


if __name__ == "__main__":
    main()