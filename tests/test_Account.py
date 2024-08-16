import pytest
from datetime import time
from src.account import Account

# Tests both the struct and the getters
class TestAccountStruct():

    def test_working(self):
        account_id = 123
        account_name = "Gmail"
        account_details = [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ]
        account_time_last_edited = time(12, 0)

        account = Account(account_id, account_name, account_details, account_time_last_edited)

        assert account.account_id == account_id
        assert account.account_name == account_name
        assert account.account_details == account_details
        assert account.account_time_last_edited == account_time_last_edited

    def test_wrong_type_account_id(self):
        account_id = "Hello there"
        account_name = "Gmail"
        account_details = [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ]
        account_time_last_edited = time(12, 0)


        with pytest.raises(TypeError):
            account = Account(account_id, account_name, account_details, account_time_last_edited)
        
    def test_wrong_type_account_name(self):
        account_id = 123
        account_name = 123
        account_details = [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ]
        account_time_last_edited = time(12, 0)


        with pytest.raises(TypeError):
            account = Account(account_id, account_name, account_details, account_time_last_edited)

    def test_wrong_type_account_details(self):
        account_id = 123
        account_name = "Gmail"
        account_details = "Email: bobbysmith@gmail.com"
        account_time_last_edited = time(12, 0)

        with pytest.raises(TypeError):
            account = Account(account_id, account_name, account_details, account_time_last_edited)

    def test_wrong_type_account_time_last_edited(self):
        account_id = 123
        account_name = "Gmail"
        account_details = [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ]
        account_time_last_edited = "Hello"

        with pytest.raises(TypeError):
            account = Account(account_id, account_name, account_details, account_time_last_edited)

