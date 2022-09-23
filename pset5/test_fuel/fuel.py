def main():
    while True:
        try:
            userInput = input("Fraction: ")
            percentage = convert(userInput)
            break
        except ValueError:
            print("Invalid input")
        except ZeroDivisionError:
            print("You can't divide by zero")
        except IndexError:
            print("That wasn't a fraction")
        except Exception as error:
            print(f"Error: {error}")


    gaugeValue = gauge(percentage)
    print(gaugeValue)


def convert(fraction):
    userInputSplit = fraction.split("/")
    numerator = int(userInputSplit[0])
    denominator = int(userInputSplit[1])

    percentage = (numerator / denominator) * 100

    if numerator > denominator:
        #raise Exception("Sorry you cannot have more than a full tank.")
        raise ValueError

    return percentage


def gauge(percentage):
    if percentage <= 1:
        returnString = "E"
    elif percentage >= 99:
        returnString = "F"
    else:
        returnString = str(round(percentage)) + "%"

    return returnString


if __name__ == "__main__":
    main()
