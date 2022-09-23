import re
import sys


def main():
   print(parse(input("HTML: ")))


def parse(s):
    returnCode = ""
    expression = r"<iframe.+youtube.com/embed/.+</iframe>"

    inputContainsExpression = CheckIfInputContainsExpression(s, expression)
    if not inputContainsExpression:
         returnCode = "None"
    else:
        youtubeVideoCode = ExtractYoutubeVideoCodeFromInput(s)
        returnCode = f"https://youtu.be/{youtubeVideoCode}"

    return returnCode


def CheckIfInputContainsExpression(input, expression):
    inputContainsExpression = False
    search = re.findall(expression, input)
    if search:
        inputContainsExpression = True

    return inputContainsExpression


def ExtractYoutubeVideoCodeFromInput(input):
    _, suffix = input.split("youtube.com/embed/")
    youtubeVideoCode,_ = suffix.split("\"")

    return youtubeVideoCode


if __name__ == "__main__":
    main()