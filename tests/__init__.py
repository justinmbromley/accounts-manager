# test/__init__.py

# Common setup code for tests
import pytest

@pytest.fixture(scope="session", autouse=True)
def setup_environment():
    # Code to set up the test environment
    print("Setting up test environment")