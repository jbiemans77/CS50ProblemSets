import sys

def main():
    greeting = input("Greeting: ")
    amountToGive = value(greeting)
    print(f"${amountToGive}")

    sys.exit()


def value(greeting):
    greetingLower = greeting.lower()

    if "hello" in greetingLower:
        value = 0
    elif greetingLower.startswith('h'):
        value = 20
    else:
        value = 100

    return int(value)


if __name__ == "__main__":
    main()