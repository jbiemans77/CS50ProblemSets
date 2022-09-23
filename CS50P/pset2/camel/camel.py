userInput = input("camelCase: ")
userInput = userInput[0].lower() + userInput[1:]
snakeCaseOutput = ""

for letter in userInput:
    if letter.islower():
        snakeCaseOutput = snakeCaseOutput + letter
    else:
        snakeCaseOutput = snakeCaseOutput + "_" + letter.lower()

print(f"snake_case: {snakeCaseOutput}")