from datetime import time
from typing import List


class Account:
    def __init__(self, account_id: int, account_name: str,
                 account_details: List[str], account_time_last_edited: time):
        self._account_id = account_id
        self._account_name = account_name
        self._account_details = account_details
        self._account_time_last_edited = account_time_last_edited

    @property
    def account_id(self):
        return self._account_id

    @account_id.setter
    def account_id(self, account_id: int):
        self._account_id = account_id

    @property
    def account_name(self):
        return self._account_name

    @account_name.setter
    def account_name(self, account_name: str):
        self._account_name = account_name

    @property
    def account_details(self):
        return self._account_details

    @account_details.setter
    def account_details(self, account_details: List[str]):
        self._account_details = account_details

    @property
    def account_time_last_edited(self):
        return self._account_time_last_edited

    @account_time_last_edited.setter
    def account_time_last_edited(self, account_time_last_edited: time):
        self._account_time_last_edited = account_time_last_edited
