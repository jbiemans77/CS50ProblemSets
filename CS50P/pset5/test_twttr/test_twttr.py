from twttr import shorten


def test_shorten_match_case():
    assert shorten("BCDbcd") == "BCDbcd"
    assert shorten("XYZxyz") == "XYZxyz"


def test_shorten_retains_punctuation():
    assert shorten("!@#$%^&*()\"\'") == "!@#$%^&*()\"\'"


def test_shorten_ignores_numbers():
    assert shorten("0123456789") == "0123456789"


def test_shorten_remove_lower_vowels():
    assert shorten("hello, world.") == "hll, wrld."
    assert shorten("this is cs50!") == "ths s cs50!"


def test_shorten_remove_upper_vowels():
    assert shorten("HELLO, WORLD.") == "HLL, WRLD."
    assert shorten("THIS IS CS50!") == "THS S CS50!"


def test_shorten_remove_mixedcase():
    assert shorten("This Is A Test Sentence.") == "Ths s  Tst Sntnc."
    assert shorten("ThE qUiCk BrOwN fOx JuMpS...") == "Th qCk BrwN fx JMpS..."