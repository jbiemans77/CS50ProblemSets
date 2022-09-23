menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

runningTotal = 0

while True:
    try:
        userInput = input("Item: ")
        userInput = userInput.title()

        if userInput in menu:
            runningTotal = runningTotal + menu[userInput]
            print(f"Total: ${runningTotal:.2f}")

    except EOFError:
        print("End of file error")
        break