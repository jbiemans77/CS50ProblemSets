import sys
from PIL import Image, ImageOps

def main():
    # Setup config variables
    expectedNumberOfArguments = 3
    numberOfArguments = len(sys.argv)
    ExitIfTooManyOrTooFewArguments(numberOfArguments,expectedNumberOfArguments)

    inputFilename = sys.argv[1]
    expectedInputExtensions = ["jpg", "jpeg", "png"]
    outputFileName = sys.argv[2]
    expectedOutputExtensions = ["jpg", "jpeg", "png"]
    shirt = Image.open("shirt.png")

    isExpectedExtensionInput = CheckIfExtensionIsExpected(inputFilename, expectedInputExtensions)
    ExitIfNotExpectedExtension(isExpectedExtensionInput, expectedInputExtensions, "Input")

    isExpectedExtensionOutput = CheckIfExtensionIsExpected(outputFileName, expectedOutputExtensions)
    ExitIfNotExpectedExtension(isExpectedExtensionOutput, expectedOutputExtensions, "Output")

    isTheSameFormat = CheckIfInputAndOutPutAreTheSameFormat(inputFilename, outputFileName)
    ExitIfNotTheSameFormat(isTheSameFormat)

    image = GetInputImage(inputFilename)
    ExitIfInputFileNotFound(image)

    GenerateOutputImage(outputFileName, image, shirt)


def CheckIfExtensionIsExpected(filename, expectedExtensions):
    isExpectedExtension = False

    for expectedExtension in expectedExtensions:
        fileExtension = GetFileExtensionFromFileName(filename)
        if fileExtension.lower() == expectedExtension.lower():
            isExpectedExtension = True

    return isExpectedExtension


def GetFileExtensionFromFileName(filename):
    if "." in filename:
        _, fileExtension = filename.split(".")

    return fileExtension


def CheckIfInputAndOutPutAreTheSameFormat(inputFilename, outputFileName):
    isTheSameFormat = False

    inputFileExtension = GetFileExtensionFromFileName(inputFilename)
    outputFileExtension = GetFileExtensionFromFileName(outputFileName)
    if inputFileExtension == outputFileExtension:
        isTheSameFormat = True

    return isTheSameFormat


def ExitIfTooManyOrTooFewArguments(numberOfArguments, expectedNumberOfArguments):
    if numberOfArguments < expectedNumberOfArguments:
        sys.exit("Too few command line arguments.")
    elif numberOfArguments > expectedNumberOfArguments:
        sys.exit("Too many command line arguments.")


def ExitIfNotExpectedExtension(isExpectedExtension, extension, message):
    if not isExpectedExtension:
        sys.exit(f"{message} is not a {extension} file")


def ExitIfNotTheSameFormat(isTheSameFormat):
    if not isTheSameFormat:
        sys.exit(f"Input and output have different extensions")


def ExitIfInputFileNotFound(input):
    if not input:
        sys.exit("Input file does not exist")


def GetInputImage(filename):
    try:
        image = Image.open(filename)
    except FileNotFoundError:
        image = ""

    return image


def GenerateOutputImage(outputFileName, image, shirt):
    shirtSize = shirt.size
    outputImage = ImageOps.fit(image, shirtSize)
    outputImage.paste(shirt, shirt)

    outputImage.save(outputFileName)


if __name__ == "__main__":
    main()