from plates import is_valid


def test_is_valid_starts_with_two_letters():
    alphabet = range(ord('a'), ord('z'))

    for letter in alphabet:
        plateCharacterOne = chr(letter)
        for secondLetter in alphabet:
            plateCharacterTwo = chr(secondLetter)

            plateNumber = f"{plateCharacterOne}{plateCharacterTwo}1000"
            assert is_valid(plateNumber) == True

    assert is_valid("A2") == False
    assert is_valid("22") == False
    assert is_valid("2") == False
    assert is_valid("2A") == False


def test_is_valid_first_number_is_not_zero():
    assert is_valid("AA0") == False
    assert is_valid("AAA0") == False
    assert is_valid("AAAA0") == False
    assert is_valid("AAAAA0") == False


def test_is_valid_is_less_than_6_characters():
    assert is_valid("AA1111") == True
    assert is_valid("AA11111") == False
    assert is_valid("AAAAAA") == True
    assert is_valid("AAAAAAA") == False


def test_is_valid_checks_for_numbers_in_middle_of_plate():
    assert is_valid("AA1A") == False
    assert is_valid("AAA1A") == False
    assert is_valid("AAAA1A") == False
    assert is_valid("AAAAA1") == True

    assert is_valid("AA00AA") == False
    assert is_valid("AA0A0") == False
    assert is_valid("AA0A0A") == False


def test_is_valid_has_no_special_characters():
    listOfInvalidCharacters = ["!","@","#","$","%","^","&","*","(","",")","<",">","?",",",".","/",":",";","|","\'","\""," "]

    for specialCharacter in listOfInvalidCharacters:
        assert is_valid(f"AA{specialCharacter}00") == False
        assert is_valid(f"{specialCharacter}") == False

    assert is_valid(" AAAA") == False
    assert is_valid("!AAA!") == False
    assert is_valid("CS.50!") == False




