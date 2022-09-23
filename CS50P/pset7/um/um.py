import re
import sys


def main():
    print(count(input("Text: ")))


def count(s):
    s = s.lower()
    expression = r"\bum\b"
    search = re.findall(expression, s)
    
    return len(search)


if __name__ == "__main__":
    main()