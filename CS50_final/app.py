import os
import datetime
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import login_required, check_integer, check_float

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///expenses.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    return render_template("summary.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    if request.method == "POST":
        username = request.form.get("username")
        pw = request.form.get("password")
        pw_con = request.form.get("confirmation")

        # check input empty
        if (not username ) or (not pw) or (not pw_con):
            flash("All fields are required")
            return render_template("register.html")

        # check the username exist or not
        exist = db.execute("SELECT user_name FROM users WHERE user_name = ?", username)
        if exist:
            flash('The username has been registered already')

        # pw confirmation correct
        if not (pw == pw_con):
            flash('Password dose not match')
            return render_template("register.html")

        # check if pw fulfill requirement
        if (len(pw) < 7):
            flash("Password's length should be at least 8")
            return render_template("register.html")
        if not re.search('[a-zA-Z]', pw) or not re.search('[0-9]', pw):
            flash("Password's length should be a mix of letters and numbers")
            return render_template("register.html")

        # register the user
        userhash = generate_password_hash(pw)
        db.execute("INSERT INTO users (user_name, hash) VALUES (?,?)", username, userhash)
        flash("Account registration successful")
        return render_template("login.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "GET":
        # Forget any user_id
        session.clear()
        return render_template("login.html")
    if request.method == "POST":
        username = request.form.get("username")
        pw = request.form.get("password")

        # check input empty
        if (not username ) or (not pw):
            flash("All fields are required")
            return render_template("login.html")

        # check if username exist and pw is correct:
        account = db.execute("SELECT * FROM users WHERE user_name = ?", username)
        hash_check = account[0]["hash"]
        if (not account) or (not check_password_hash(hash_check, pw)):
            flash("Username does not exist or password is not correct")
            return render_template("login.html")

        # login successful
        session["user_id"] = account[0]["id"]
        flash("Login successful")
        return render_template("summary.html")

@app.route("/summary")
@login_required
def summary():
    return render_template("summary.html")

@app.route("/dataimport", methods=["GET", "POST"])
@login_required
def dataimport():
    if request.method == "GET":
        month_list = [
            "January",
            "Februnary",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December" ]
        return render_template("dataimport.html", months = month_list)
    if request.method == "POST":
        # check if all the required field exist
        day = request.form.get("day")
        month = request.form.get("month")
        year = request.form.get("year")
        name =request.form.get("name")
        category = request.form.get("category")
        expense = request.form.get("expenses")
        remarks = request.form.get("remarks")
        if (not month) or (not year) or (not category) or (not expense):
            flash("Please input month, year, category and expenses")
            return redirect("/dataimport")
        # check if day and year is integer
        if (not check_integer(day)) or (not check_integer(year)):
            flash("Day and Year should be an integer")
            return redirect("/dataimport")

        # check if expense is float value
        if not (float(expens)):
            flash("Expenses should be numeric value")

        # update the database
        db.execute("INSERT INTO expenses (day, month, year, category, name, expense, remarks) VALUE (?, ?, ?, ?, ?, ?, ?) WHERE user_id = ?", day, month, year, category, name, expense, remarks, session["user_id"])
        return redirect("/")