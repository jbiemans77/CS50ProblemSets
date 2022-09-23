userInput = input("What is the Answer to the Great Question of Life, the Universe, and Everything? ")
userInput = userInput.strip()

if userInput == "42" or userInput.lower() == "forty-two" or userInput.lower() == "forty two":
    print("Yes")
else:
    print("No")