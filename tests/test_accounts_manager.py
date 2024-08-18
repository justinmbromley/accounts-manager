from db_name import db_name
from datetime import time
from src.accounts_manager import AccountsManager
import sqlite3
import json

class TestAccountsManager:
    def test_am_add_account_working(self):
        conn = sqlite3.connect('test.db')
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
            '''
            SELECT * 
            FROM accounts
            WHERE account_name = ?
            AND account_details = ?
            ''', (account_name, str(account_details))
        )

        result = cursor.fetchone()

        cursor.execute('''DROP TABLE accounts''')
        conn.commit()
        conn.close()

        assert result is not None, "Account not found in the database"
        assert result[1] == account_name, "Account name does not match"
        assert result[2] == str(account_details), "Account details do not match"

