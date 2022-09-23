import sys

from pyfiglet import Figlet

figlet = Figlet()

def main():
    if len(sys.argv) == 1:
        print("Random font chosen.")
    elif not len(sys.argv) == 3:
        print("wrong number")
        sys.exit("Invalid usage ")

    if sys.argv[1] == "-f" or sys.argv[1] == "--font":
        fontName = sys.argv[2]
        availableFonts = figlet.getFonts()

        if fontName not in availableFonts:
            print("That is not a valid font.")
            sys.exit("Invalid usage")

        userInput = input("Input: ")
        figlet.setFont(font=fontName)
        print(figlet.renderText(userInput))
    else:
        print("-f or --font not used as arguments.")
        sys.exit("Invalid usage")




main()