def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    is_valid_plate = False

    while True:
        # Check all criteria, break if check fails to avoid further checks.

        if Has_nonalphanumeric_characters(s):
            #print("Error: Plate has invalid characters.")
            break

        if Has_invalid_length(s):
            #print("Error: Plate has improper length.")
            break

        if Has_numbers_within_first_two_characters(s):
            #print("Error: Plate not starting with 2 letters.")
            break

        if Has_numbers_in_middle_of_plate(s):
            #print("Error: Plate has numbers in the middle.")
            break

        if Has_0_as_first_number(s):
            #print("Error: Plate has 0 as first number.")
            break

        # All checks have passed, mark is_valid_plate as True.
        is_valid_plate = True
        break

    return is_valid_plate


def Has_nonalphanumeric_characters(plate):
    has_nonalphanumeric_characters = False

    if not(plate.isalnum()):
        has_nonalphanumeric_characters = True

    return has_nonalphanumeric_characters


def Has_invalid_length(plate):
    has_invalid_length = False
    length_of_plate = len(plate)
    minimum_length_of_plate = 2
    maxumum_length_of_plate = 6

    if not(length_of_plate  >= minimum_length_of_plate and length_of_plate <= maxumum_length_of_plate):
        has_invalid_length = True

    return has_invalid_length


def Has_numbers_within_first_two_characters(plate):
    has_numbers_within_first_two_characters = True

    if plate[0].isalpha() and plate[1].isalpha():
        has_numbers_within_first_two_characters = False

    return has_numbers_within_first_two_characters


def Has_numbers_in_middle_of_plate(plate):
    numberFound = False
    has_numbers_in_middle_of_plate = False

    for character in plate:
        if character.isalpha() and numberFound:
            has_numbers_in_middle_of_plate = True

        if character.isnumeric():
            numberFound = True

    return has_numbers_in_middle_of_plate


def Has_0_as_first_number(plate):
    has_0_as_first_number = False

    for character in plate:
        if character.isnumeric() and character == "0":
            has_0_as_first_number = True
            break
        elif character.isnumeric():
            break

    return has_0_as_first_number


main()