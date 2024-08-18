from src.account import Account
from typing import List
from typing import Optional
import sqlite3

class AccountsManager:
    def __init__(self, conn: sqlite3.Connection):
        self._conn = conn

    def am_add_account(self, account_name: str, account_details: List[str]):
        return None