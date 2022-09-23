userInput = input("Expression: ")
result = 0.0

inputList = userInput.split()
firstInt = int(inputList[0])
operator = inputList[1]
secondInt = int(inputList[2])

if operator == "+":
    result = firstInt + secondInt
elif operator == "-":
    result = firstInt - secondInt
elif operator == "*":
    result = firstInt * secondInt
elif operator == "/":
    result = firstInt / secondInt

roundedResult = round(result, 1)
print(f"{roundedResult:.1f}")