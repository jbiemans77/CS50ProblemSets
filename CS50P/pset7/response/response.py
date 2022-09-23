import validators

def main():
    email = input("What's your email address?")

    isValidEmail = validators.email(email)

    if isValidEmail:
        print("Valid")
    else:
        print("Invalid")
        

if __name__ == "__main__":
    main()