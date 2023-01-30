import os
import requests

from flask import redirect, render_template, request, session
from functools import wraps


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function

def check_integer(n):
    try:
        float(n)
    except ValueError:
        return False
    else:
        return float(n).is_integer()

def check_float(n):
    try:
        float(n)
    except ValueError:
        return False
    else:
        return float(n)

def sql_select_append(query_string, column, value):
    if value == "All":
        return query_string
    else:
        temp_string = f"{column} = '{value}'"
        query_string = query_string + " AND " + temp_string
        print(query_string)
        return query_string

