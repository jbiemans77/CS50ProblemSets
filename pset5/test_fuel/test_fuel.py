from fuel import convert, gauge
import pytest


def test_convert_string_input():
    with pytest.raises(ValueError):
        convert("cat")
        convert("half")


def test_convert_divide_by_zero():
    with pytest.raises(ZeroDivisionError):
        convert("4/0")
        convert("50/0")
        convert("100/0")

def test_convert_more_than_full():
    with pytest.raises(ValueError):
        convert("5/4")
        convert("6/3")
        convert("50/25")


def test_convert_check_output():
    assert convert("3/4") == 75
    assert convert("1/2") == 50
    assert convert("1/4") == 25
    assert convert("1/100") == 1


def test_gauge_empty():
    assert gauge(1) == "E"
    assert gauge(0.1) == "E"
    assert gauge(0.5) == "E"
    assert gauge(0.9) == "E"


def test_gauge_full():
    assert gauge(99) == "F"
    assert gauge(100) == "F"
    assert gauge(99.1) == "F"
    assert gauge(99.9) == "F"


def test_gauge_normal():
    assert gauge(50) == "50%"
    assert gauge(80) == "80%"
    assert gauge(25) == "25%"
    assert gauge(13) == "13%"
