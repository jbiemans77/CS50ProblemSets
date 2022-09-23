from bank import value

def test_value_sees_hello():
    assert value("hello") == 0


def test_value_check_for_h_greetings():
    assert value("h") == 20
    assert value("hey") == 20
    assert value("hola") == 20
    assert value("howdy") == 20


def test_value_is_case_insensitive():
    assert value("hello") == 0
    assert value("Hello") == 0
    assert value("HELLO") == 0
    assert value("hElLo") == 0
    assert value("HeLlO") == 0

    assert value("HEY") == 20
    assert value("HOLA") == 20
    assert value("HOWDY") == 20
    assert value("H") == 20


def test_value_only_first_h_is_counted():
    assert value("Welcome h") == 100
    assert value("a h") == 100
    assert value("A H") == 100


def test_value_check_for_non_h_greeting():
    assert value("Welcome") == 100
    assert value("Good day") == 100
    assert value("The quick brown fox jumps...") == 100



