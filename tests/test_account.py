from datetime import time
from src.account import Account


# Tests both the struct and the getters
class TestAccountStruct():

    def test_getters_working(self):
        account_id = 123
        account_name = "Gmail"
        account_details = [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ]
        account_time_last_edited = time(12, 0)

        account = Account(account_id, account_name, account_details,
                          account_time_last_edited)

        assert account.account_id == account_id
        assert account.account_name == account_name
        assert account.account_details == account_details
        assert account.account_time_last_edited == account_time_last_edited

    def test_setters_working(self):
        account_1 = Account(123, "Gmail", [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ], time(12, 0))

        account_id = 321
        account_name = "Bank"
        account_details = [
            "Bank Code: 1459",
            "Email: josephbanks@outlook.com",
            "Password: epicawesome",
            "Secret Words: hello i have no cool"
        ]
        account_time_last_edited = time(2, 3)

        account_1.account_id = account_id
        account_1.account_name = account_name
        account_1.account_details = account_details
        account_1.account_time_last_edited = account_time_last_edited

        assert account_1.account_id == account_id
        assert account_1.account_name == account_name
        assert account_1.account_details == account_details
        assert account_1.account_time_last_edited == account_time_last_edited
