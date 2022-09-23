import requests
import sys

def main():
    VerifySingleCommandLineArgumentExists(sys.argv)
    numberOfCoins = VerifyCommandLineInputIsNumberAndReturn(sys.argv[1])
    response = GetInfoFromCoinDeskAPI()
    valueOfOneCoinInUSD = GetValueOfOneCoinInUSDFromResponse(response)

    totalAmount = numberOfCoins * valueOfOneCoinInUSD
    print(f"${totalAmount:,.4f}")


def VerifySingleCommandLineArgumentExists(argv):
    if not (len(argv) == 2):
        sys.exit("Missing command-line argument.")


def VerifyCommandLineInputIsNumberAndReturn(input):
    try:
        numberOfCoins = float(input)
    except ValueError:
        sys.exit("Command-line argument is not a number")

    return numberOfCoins


def GetInfoFromCoinDeskAPI():
    try:
        response = requests.get("https://api.coindesk.com/v1/bpi/currentprice.json")
    except requests.RequestException:
        sys.exit("Request Error")

    return response


def GetValueOfOneCoinInUSDFromResponse(response):
    output = response.json()
    valueOfOneCoin = output["bpi"]["USD"]["rate_float"]

    return valueOfOneCoin


main()