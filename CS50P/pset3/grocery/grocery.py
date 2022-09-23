groceryList = {}

while True:
    try:
        userInput = input().lower().strip()

        if userInput in groceryList:
            groceryList[userInput] = groceryList[userInput] + 1
        else:
            groceryList[userInput] = 1

    except EOFError:
        break

sortedGroceryList = dict(sorted(groceryList.items()))

for item in sortedGroceryList:
    print(f"{sortedGroceryList[item]} {item.upper()}")