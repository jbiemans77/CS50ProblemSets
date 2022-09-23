def main():
    userInput = input("Input: ")
    output = shorten(userInput)

    print(f"Output: {output}")


def shorten(word):
    output = ""

    for letter in word:
        lowerLetter = letter.lower()

        if lowerLetter not in ['a','e','i','o','u']:
            output = output + letter

    return output




if __name__ == "__main__":
    main()