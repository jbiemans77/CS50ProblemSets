userInput = input("Please type something with text smilies:")
emojiOutput = userInput.replace(":)","\U0001F642")
emojiOutput = emojiOutput.replace(":(","\U0001F641")

print(f"{emojiOutput}")