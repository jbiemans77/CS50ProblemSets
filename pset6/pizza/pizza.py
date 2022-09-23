import sys
import csv
from tabulate import tabulate

def main():

    if len(sys.argv) == 1:
        sys.exit("Too few command line arguments.")
    elif len(sys.argv) >= 3:
        sys.exit("Too many command line arguments.")

    filename = sys.argv[1]
    isValidExtension = CheckIfExtensionIsValid(filename, "csv")

    if not isValidExtension:
        sys.exit("Not a CSV file")

    table = GetTableDataFromCSV(filename)

    if not table:
        sys.exit("File does not exist")
    else:
        print(tabulate(table, headers="keys", tablefmt="grid"))
        

def GetTableDataFromCSV(filename):
    table = []

    try:
        with open(filename) as file:
            reader = csv.DictReader(file)
            for row in reader:
                table.append(row)
    except FileNotFoundError:
        table = []

    return table


def CheckIfExtensionIsValid(filename, extension):
    isValidExtension = False

    if "." in filename:
        _, fileExtension = filename.split(".")
        if fileExtension == extension:
            isValidExtension = True

    return isValidExtension


if __name__ == "__main__":
    main()