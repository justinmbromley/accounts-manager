from typing import List
from typing import Optional
from datetime import datetime
import sqlite3
import json

from constants import TABLE_NAME
from src.account import Account

class AccountsManager:
    def __init__(self, conn: sqlite3.Connection):
        self._conn = conn

    def am_add_account(self, account_name: str, account_details: List[str]):
        cursor = self._conn.cursor()
        cursor.execute(f'''
            CREATE TABLE IF NOT EXISTS {TABLE_NAME} (
                account_id INTEGER PRIMARY KEY AUTOINCREMENT,
                account_name TEXT,
                account_details TEXT,
                account_time_last_edited TIMESTAMP
            )
        ''')
        
        account_time_last_edited = datetime.now()
        account_details_json = json.dumps(account_details)

        cursor.execute(f'''
            INSERT INTO {TABLE_NAME} (account_name, account_details, account_time_last_edited)
            VALUES (?, ?, ?)
        ''', (account_name, account_details_json, account_time_last_edited))
        
        self._conn.commit()

    def am_get_account(self, account_id: int) -> Optional[Account]:
        return None
