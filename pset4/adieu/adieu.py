import inflect

p = inflect.engine()

listOfNames = []

while True:
    try:
        userInput = input("Name: ")
        listOfNames.append(userInput)

    except EOFError:
        break

printableNames = p.join(listOfNames)
print("")
print(f"Adieu, adieu, to {printableNames}")