import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        try:
            int(day)
        except ValueError:
            return redirect("/")
        else: int_day = int(day)

        # data validation
        day31_month = ["1", "3", "5", "7", "8", "10", "12"]
        day30_month = ["4", "6", "9", "11"]
        if name:
            if (month in day31_month and (int_day > 0 and int_day < 32)) or (month in day30_month and (int_day > 0 and int_day < 31)) or (month == "2" and (int_day > 0 and int_day < 30)):
                # correct day format
                 db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
                 return redirect("/")
            else:
                # incorrect day format
                return redirect("/")
        else:
            # empty name
            return render_template("index.html")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birth=birthdays)


