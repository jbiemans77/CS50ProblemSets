def main():
    amountDue = 50

    while amountDue > 0:
        print(f"Amount Due: {amountDue}")
        userInputCoinValue = input("Insert Coin: ")
        userInputCoinValue = int(userInputCoinValue)

        isValidCoin = checkIfCoinInputIsValid(userInputCoinValue)

        if isValidCoin:
            amountDue = calculateNewAmountDue(amountDue, userInputCoinValue)

    print(f"Change Owed: {abs(amountDue)}")


def checkIfCoinInputIsValid(userInputCoinValue):
    isValidCoin = False

    if userInputCoinValue in [1,5,10,25]:
        isValidCoin = True

    return isValidCoin


def calculateNewAmountDue(amountDue, userInputCoinValue):
    newAmountDue = amountDue - userInputCoinValue

    return newAmountDue


if __name__ == "__main__":
    main()