import pytest

@pytest.fixture
def my_function():
    return 42
    
def test_function(my_function):
    assert my_function == 42