returnValue = ""

while True:
    try:
        userInput = input("Fraction: ")
        userInputSplit = userInput.split("/")
        numerator = int(userInputSplit[0])
        denominator = int(userInputSplit[1])

        if numerator > denominator:
            raise Exception("Sorry you cannot have more than a full tank.")

        percentFull = (numerator / denominator) * 100

        if percentFull <= 1:
            returnValue = "E"
        elif percentFull >= 99:
            returnValue = "F"
        else:
            returnValue = str(round(percentFull)) + "%"

        break

    except ValueError:
        print("Invalid input")
    except ZeroDivisionError:
        print("You can't divide by zero")
    except IndexError:
        print("That wasn't a fraction")
    except Exception as error:
        print(f"Error: {error}")


print(returnValue)


