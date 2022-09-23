import re
import sys


def main():
    print(validate(input("IPv4 Address: ")))


def validate(ip):
    ipIsValid = False

    formatIsValid = CheckFormatingOfIPAddress(ip)
    if formatIsValid:
        numbersAreInRange = CheckIfNumbersAreWithinRange(ip)
        if numbersAreInRange:
            ipIsValid = True

    return ipIsValid


def CheckIfNumbersAreWithinRange(ip):
    allNumbersAreWithinRange = True

    segments = ip.split(".")
    for segment in segments:
        segment = int(segment)
        if not (0 <= segment <= 255):
            allNumbersAreWithinRange = False

    return allNumbersAreWithinRange


def CheckFormatingOfIPAddress(ip):
    formatIsValid = False
    if ip.count(".") == 3:
        search = re.findall(r"(?=(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))", ip)
        if len(search) >= 1:
            formatIsValid = True

    return formatIsValid


if __name__ == "__main__":
    main()