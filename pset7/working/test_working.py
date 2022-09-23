from working import convert
import pytest

def test_convert_minutes_too_large():
    with pytest.raises(ValueError):
        convert("8:60 AM to 5:00 PM")
        convert("9:85 AM to 5:00 PM")
        convert("7:85 AM to 5:00 PM")


def test_convert_missing_to():
    with pytest.raises(ValueError):
        convert("9 AM - 5 PM")
        convert("7 AM - 4:30 PM")
        convert("8:25 AM - 4:55 PM")


def test_convert_missing_AM():
    with pytest.raises(ValueError):
        convert("9:00 to 5:00 PM")
        convert("8:00 to 3:00 PM")
        convert("7:30 to 4:30 PM")


def test_convert_missing_PM():
    with pytest.raises(ValueError):
        convert("9:00 AM to 5:00")
        convert("8:00 AM to 3:00")
        convert("7:30 AM to 4:30")


def test_convert_add_12_to_PM():
    assert convert("9 AM to 5 PM") == "09:00 to 17:00"
    assert convert("1 PM to 2 PM") == "13:00 to 14:00"


def test_convert_12_AM_is_0_hours():
    assert convert("12 AM to 12 AM") == "00:00 to 00:00"


def test_convert_not_adding_12_to_noon():
    assert convert("12 PM to 8 PM") == "12:00 to 20:00"
    assert convert("9 AM to 12 PM") == "09:00 to 12:00"
    assert convert("12 PM to 12 PM") == "12:00 to 12:00"