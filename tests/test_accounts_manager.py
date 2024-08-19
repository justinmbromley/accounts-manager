from constants import TABLE_NAME
import sqlite3
import json
from src.accounts_manager import AccountsManager
from src.account import Account

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

    def test_am_update_account_working(self):
        conn = sqlite3.connect(':memory:')
        cursor = conn.cursor()
        am = AccountsManager(conn)

        am.am_add_account("Gmail", ["Email: bobbysmith@gmail.com", "Password: b0bby5m1TH", "Secret Question: Name of your first crush?"])
        am.am_add_account("Bank", ["Bank Code: 1459", "Email: josephbanks@outlook.com", "Password: epicawesome", "Secret Words: hello i have no cool"])
        am.am_add_account("Gmail", ["Email: rogerboger@gmail.com", "Password: ther4alONE"])
        am.am_add_account("Walmart", ["Email: juryrigg@outlook.com", "Password: theGREATWALL", "Secret Question: What is the meaning of it all?"])

        account_id = 3
        new_account_name = "Dentist"
        am.am_update_account_name(account_id, new_account_name)

        assert am.am_get_account(account_id).account_name == new_account_name
        
        # finish
        cursor.execute(f'''DROP TABLE {TABLE_NAME}''')
        conn.commit()
        conn.close()

    def test_am_get_account_by_name_working(self):
        conn = sqlite3.connect(':memory:')
        cursor = conn.cursor()
        am = AccountsManager(conn)

        account_1 = Account(1, "Gmail", ["Email: bobbysmith@gmail.com", "Password: b0bby5m1TH", "Secret Question: Name of your first crush?"], 0)
        account_2 = Account(3, "Gmail", ["Email: rogerboger@gmail.com", "Password: ther4alONE"], 0)
        accounts_expected = [account_1, account_2]
       
        am.am_add_account(account_1.account_name, account_1.account_details)
        am.am_add_account("Bank", ["Bank Code: 1459", "Email: josephbanks@outlook.com", "Password: epicawesome", "Secret Words: hello i have no cool"])
        am.am_add_account(account_2.account_name, account_2.account_details)
        am.am_add_account("Walmart", ["Email: juryrigg@outlook.com", "Password: theGREATWALL", "Secret Question: What is the meaning of it all?"])

        accounts_result = am.am_get_accounts_by_name(account_1.account_name)

        assert accounts_result is not None
        assert len(accounts_result) == 2
        for i in range(2):
            assert accounts_result[i].account_id == accounts_expected[i].account_id
            assert accounts_result[i].account_name == accounts_expected[i].account_name
            assert accounts_result[i].account_details == accounts_expected[i].account_details

        # finish
        cursor.execute(f'''DROP TABLE {TABLE_NAME}''')
        conn.commit()
        conn.close()

    def test_am_get_account_by_name_failing(self):
        conn = sqlite3.connect(':memory:')
        cursor = conn.cursor()
        am = AccountsManager(conn)
       
        am.am_add_account("Gmail", ["Email: bobbysmith@gmail.com", "Password: b0bby5m1TH", "Secret Question: Name of your first crush?"])
        am.am_add_account("Bank", ["Bank Code: 1459", "Email: josephbanks@outlook.com", "Password: epicawesome", "Secret Words: hello i have no cool"])
        am.am_add_account("Gmail", ["Email: rogerboger@gmail.com", "Password: ther4alONE"])
        am.am_add_account("Walmart", ["Email: juryrigg@outlook.com", "Password: theGREATWALL", "Secret Question: What is the meaning of it all?"])

        assert am.am_get_accounts_by_name("Outlook") is None

        # finish
        cursor.execute(f'''DROP TABLE {TABLE_NAME}''')
        conn.commit()
        conn.close()
