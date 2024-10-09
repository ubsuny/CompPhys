""" A collection of math functions to demonstrate unit tests """

def divide(x,y):
    """Divide two numbers.

    Args:
        x: numerator
        y: denominator

    Returns:
        The result of the division

    Raises:
        ZeroDivisionError: If y is 0
    """
    if y == 0:
        raise ZeroDivisionError("Division by zero!")
    return x / y