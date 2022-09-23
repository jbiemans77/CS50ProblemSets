userInput = input("Greeting: ")
userInputLower = userInput.lower()

if "hello" in userInputLower:
    print("$0")
elif userInputLower.startswith('h'):
    print("$20")
else:
    print("$100")