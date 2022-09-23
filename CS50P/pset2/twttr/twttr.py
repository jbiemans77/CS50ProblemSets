userInput = input("Input: ")
output = ""

for letter in userInput:
    lowerLetter = letter.lower()

    if lowerLetter not in ['a','e','i','o','u']:
        output = output + letter

print(f"Output: {output}")