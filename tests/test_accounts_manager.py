from src.accounts_manager import AccountsManager
from constants import TABLE_NAME
import sqlite3
import json

class TestAccountsManager:
    def test_am_add_account_working(self):
        conn = sqlite3.connect(':memory:')
        am = AccountsManager(conn)

        account_name = "Gmail"
        account_details = [
            "Email: bobbysmith@gmail.com",
            "Password: b0bby5m1TH",
            "Secret Question: Name of your first crush?"
        ]

        am.am_add_account(account_name, account_details)

        cursor = conn.cursor()
        cursor.execute(
            f'''
            SELECT * 
            FROM {TABLE_NAME}
            WHERE account_name = ?
            AND account_details = ?
            ''', (account_name, json.dumps(account_details))
        )
        result = cursor.fetchone()

        # finish
        cursor.execute(f'''DROP TABLE {TABLE_NAME}''')
        conn.commit()
        conn.close()

        assert result is not None, "Account not found in the database"
        assert result[0] == 1, "Account ID does not match"
        assert result[1] == account_name, "Account name does not match"
        assert result[2] == json.dumps(account_details), "Account details do not match"

    def test_am_get_account_working(self):
        conn = sqlite3.connect(':memory:')
        cursor = conn.cursor()
        am = AccountsManager(conn)

        account_name_target = "Gmail"
        account_details_target = ["Email: rogerboger@gmail.com", "Password: ther4alONE"]

        am.am_add_account("Gmail", ["Email: bobbysmith@gmail.com", "Password: b0bby5m1TH", "Secret Question: Name of your first crush?"])
        am.am_add_account("Bank", ["Bank Code: 1459", "Email: josephbanks@outlook.com", "Password: epicawesome", "Secret Words: hello i have no cool"])
        am.am_add_account(account_name_target, account_details_target)
        am.am_add_account("Walmart", ["Email: juryrigg@outlook.com", "Password: theGREATWALL", "Secret Question: What is the meaning of it all?"])

        account = am.am_get_account(3)
        
        # finish
        cursor.execute(f'''DROP TABLE {TABLE_NAME}''')
        conn.commit()
        conn.close()

        assert account is not None, "No Account found"
        assert account.account_id == 3, "Incorrect account ID"
        assert account.account_name == account_name_target, "Incorrect account name"
        assert account.account_details == account_details_target, "Unexpected account details"

    def test_am_get_account_failing(self):
        conn = sqlite3.connect(':memory:')
        cursor = conn.cursor()
        am = AccountsManager(conn)

        am.am_add_account("Gmail", ["Email: bobbysmith@gmail.com", "Password: b0bby5m1TH", "Secret Question: Name of your first crush?"])
        am.am_add_account("Bank", ["Bank Code: 1459", "Email: josephbanks@outlook.com", "Password: epicawesome", "Secret Words: hello i have no cool"])
        am.am_add_account("Gmail", ["Email: rogerboger@gmail.com", "Password: ther4alONE"])
        am.am_add_account("Walmart", ["Email: juryrigg@outlook.com", "Password: theGREATWALL", "Secret Question: What is the meaning of it all?"])

        account = am.am_get_account(5)
        
        # finish
        cursor.execute(f'''DROP TABLE {TABLE_NAME}''')
        conn.commit()
        conn.close()

        assert account is None, "Account unexpectedly found"
