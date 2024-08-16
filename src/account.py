from datetime import time
from typing import List

class Account:
    def __init__(self, account_id: int, account_name: str, 
            account_details: List[str], account_time_last_edited: time):
        if not isinstance(account_id, int):
            raise TypeError("account_id must be an integer")
        if not isinstance(account_name, str):
            raise TypeError("account_name must be a string")
        if not isinstance(account_details, list) or not all(isinstance(detail, str) for detail in account_details):
            raise TypeError("account_details must be a list of strings")
        if not isinstance(account_time_last_edited, time):
            raise TypeError("account_time_last_edited must be a time object")
        
        self._account_id = account_id
        self._account_name = account_name
        self._account_details = account_details
        self._account_time_last_edited = account_time_last_edited

    @property
    def account_id(self):
        return self._account_id

    @account_id.setter
    def account_id(self, account_id: int):
        if not isinstance(account_id, int):
            raise TypeError("account_id must be an integer")
        self._account_id = account_id

    @property
    def account_name(self):
        return self._account_name
    
    @account_name.setter
    def account_name(self, account_name: str):
        if not isinstance(account_name, str):
            raise TypeError("account_name must be a string")
        self._account_name = account_name
    
    @property
    def account_details(self):
        return self._account_details
    
    @account_details.setter
    def account_details(self, account_details: List[str]):
        if not isinstance(account_details, list) or not all(isinstance(detail, str) for detail in account_details):
            raise TypeError("account_details must be a list of strings")
        self._account_details = account_details

    @property
    def account_time_last_edited(self):
        return self._account_time_last_edited
    
    @account_time_last_edited.setter
    def account_time_last_edited(self, account_time_last_edited: time):
        if not isinstance(account_time_last_edited, time):
            raise TypeError("account_time_last_edited must be a time object")
        self._account_time_last_edited = account_time_last_edited
