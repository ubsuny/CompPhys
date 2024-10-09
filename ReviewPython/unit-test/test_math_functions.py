""" Test functions for the math_functions module"""

from math_functions import divide
import pytest

def test_divide():
    """Test that divide returns the correct result for an easy example"""
    assert divide(1, 2) == 0.5

def test_divide_negative_input():
    """
    Test that divide returns the correct result when given two negative numbers.
    """
    assert divide(-5, -2) == 2.5
    assert divide(-2, -5) == -0.4

def test_divide_by_zero():
    """Test that divide raises a ZeroDivisionError when the denominator is 0"""
    with pytest.raises(ZeroDivisionError):
        divide(1, 0)