from numb3rs import validate

def test_validate_format():
    assert validate("0.0.0") == False
    assert validate("0") == False
    assert validate("0.0.0.0.0") == False


def test_validate_alphabet():
    assert validate("cat") == False
    assert validate("cat.cat.cat.cat") == False
    assert validate("this.isnt.an.ip") == False


def test_validate_range():
    assert validate("0.0.0.0") == True
    assert validate("255.255.255.255") == True
    assert validate("-1.-1.-1.-1") == False
    assert validate("256.256.256.256") == False


def test_validate_first():
    assert validate("192.266.266.255") == False
    assert validate("1.256.256.256") == False


def test_validate_incomplete():
    assert validate("1") == False
    assert validate("1.1") == False
    assert validate("1.1.1") == False