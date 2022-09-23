from jar import Jar
import pytest

def test_size_over_capacity():
    with pytest.raises(ValueError):
        Jar(20,30)
        Jar(1,2)


def test_capacity_under_zero():
    with pytest.raises(ValueError):
        Jar(0)
        Jar(-1)


def test_withdraw_more_than_size():
    with pytest.raises(ValueError):
        jar = Jar(5)
        assert jar.withdraw(6)


def test_deposit_over_capacity():
    with pytest.raises(ValueError):
        jar = Jar(10)
        assert jar.deposit(12)