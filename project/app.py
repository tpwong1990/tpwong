import os
import datetime
import re
import csv
import pandas as pd

import sqlite3
connection = sqlite3.connect("expenses.db", check_same_thread=False)
from cs50 import SQL

from flask import Flask, flash, redirect, render_template, request, session, send_file
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from werkzeug.utils import secure_filename
from helpers import login_required, check_integer, check_float, sql_select_append

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)



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
    if request.method == "GET":
         # extract the expenses
        cursor = connection.cursor()
        total_expenses = cursor.execute("SELECT * FROM expenses WHERE user_id = ?", [(session["user_id"])]).fetchall()
        distinct_month = cursor.execute("SELECT DISTINCT month FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        distinct_year = cursor.execute("SELECT DISTINCT year FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        distinct_name = cursor.execute("SELECT DISTINCT name FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        distinct_category = cursor.execute("SELECT DISTINCT category FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        load_selected_option = 0
        return render_template("details.html", expenses=total_expenses, d_months=distinct_month, d_years=distinct_year, d_names=distinct_name,d_categories=distinct_category, load_option = load_selected_option)


@app.route("/select", methods=["GET", "POST"])
@login_required
def select():
    if request.method == "POST":
        delete_check = request.form.get("delete")
        edit_check = request.form.get("edit")
        # check if delete button is clicked
        if not (delete_check == None):
            cursor = connection.cursor()
            cursor.execute("DELETE FROM expenses WHERE row_id = ?", [int(delete_check)])
            connection.commit()
            return redirect("/")

        # check if edit button is clicked
        if not (edit_check == None):
            cursor = connection.cursor()
            edit_row = cursor.execute("SELECT * FROM expenses WHERE row_id = ?", [int(edit_check)]).fetchall()
            selected_month = edit_row[0][2]
            month_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
            return render_template("edit.html", row = edit_row[0], months = month_list)

        # selected codition search
        selected_month = request.form.get("month")
        selected_year = request.form.get("year")
        selected_name = request.form.get("name")
        selected_category = request.form.get("category")
        selected_order = request.form.get("order")

        # create tmp table in sqlite
        cursor = connection.cursor()
        sql_string = "CREATE TABLE tmp AS SELECT * FROM expenses WHERE user_id = ?"

        sql_string = sql_select_append(sql_string, "month", selected_month)
        sql_string = sql_select_append(sql_string, "year", selected_year)
        sql_string = sql_select_append(sql_string, "name", selected_name)
        sql_string = sql_select_append(sql_string, "category", selected_category)

        if selected_order == "latest":
            sql_string = sql_string + " ORDER BY year DESC, month DESC, day DESC"
        if selected_order == "oldest":
            sql_string = sql_string + " ORDER BY year ASC, month ASC, day ASC"

        cursor.execute("DROP TABLE IF EXISTS tmp")
        cursor.execute(sql_string, [session["user_id"]])
        total_expenses = cursor.execute("SELECT * FROM tmp").fetchall()
        distinct_month = cursor.execute("SELECT DISTINCT month FROM tmp").fetchall()
        distinct_year = cursor.execute("SELECT DISTINCT year FROM tmp").fetchall()
        distinct_name = cursor.execute("SELECT DISTINCT name FROM tmp").fetchall()
        distinct_category = cursor.execute("SELECT DISTINCT category FROM tmp").fetchall()
        load_selected_option = 1
        return render_template("details.html", expenses=total_expenses, d_months=distinct_month, d_years=distinct_year, d_names=distinct_name,d_categories=distinct_category, load_option = load_selected_option)




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
        cursor = connection.cursor()
        # check input empty
        if (not username ) or (not pw) or (not pw_con):
            flash("All fields are required")
            return render_template("register.html")

        # check the username exist or not
        exist = cursor.execute("SELECT user_name FROM users WHERE user_name = ?", [username]).fetchall()
        if exist:
            flash('The username has been registered already')
            return render_template("register.html")

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
        cursor.execute("INSERT INTO users (user_name, hash) VALUES (?,?)", (username, userhash))
        connection.commit()
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
        cursor = connection.cursor()

        # check input empty
        if (not username ) or (not pw):
            flash("All fields are required")
            return render_template("login.html")

        # check if username exist and pw is correct:
        account = cursor.execute("SELECT * FROM users WHERE user_name = ?", [username]).fetchall()
        if (not account):
            flash("Username does not exist or Password is not correct")
            return render_template("login.html")
        hash_check = account[0][2]
        if not check_password_hash(hash_check, pw):
            flash("Username does not exist or Password is not correct")
            return render_template("login.html")

        # login successful
        session["user_id"] = account[0][0]
        flash("Login successful")
        return redirect("/")

@app.route("/dataimport", methods=["GET", "POST"])
@login_required
def dataimport():
    if request.method == "GET":
        month_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
        cursor = connection.cursor()
        distinct_name = cursor.execute("SELECT DISTINCT name FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        distinct_category = cursor.execute("SELECT DISTINCT category FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        return render_template("dataimport.html", months = month_list, d_names = distinct_name, d_cateogry = distinct_category)
    if request.method == "POST":
        # check if all the required field exist
        day = request.form.get("day")
        month = request.form.get("month")
        year = request.form.get("year")
        name =request.form.get("name")
        category = request.form.get("category")
        expense = request.form.get("expense")
        remarks = request.form.get("remarks")
        if (not month) or (not year) or (not category) or (not name) or (not expense):
            flash("Please input month, year, name, category and expense")
            return redirect("/dataimport")
        # check if year is integer
        if not check_integer(year):
            flash("Year should be an integer")
            return redirect("/dataimport")
        # check if day is integer
        if day and (not check_integer(day)):
            flash("Day should be an integer")
            return redirect("/dataimport")

        # check if expense is float value
        if not (check_float(expense)):
            flash("Expenses should be numeric value")
            return redirect("/dataimport")

        # update the database
        cursor = connection.cursor()
        cursor.execute("INSERT INTO expenses (user_id, day, month, year, category, name, expense, remarks) VALUES (?, ?, ?, ?, ?, ?, ?, ?)", (session["user_id"], day, month, year, category, name, expense, remarks))
        connection.commit()
        return redirect("/dataimport")

@app.route("/dataimport_csv", methods=["GET", "POST"])
@login_required
def dataimport_csv():
    if request.method == 'POST':
        # check upload file
        file = request.files['fileupload']
        if 'fileupload' not in request.files:
            flash('No file part')
            return redirect("/")
        filename = secure_filename(file.filename)
        realpath = os.path.realpath('app.py')
        realpath = realpath.replace("app.py", "upload/")
        filepath = realpath + filename
        file.save(filepath)
        #flash('file uploaded successfully')
        # read file
        with open(filepath, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                # check if required fields has correct value
                # check if the field is empty of not
                if (not row["month"]) or (not row["year"]) or (not row["category"]) or (not row["name"]) or (not row["expense"]):
                    continue
                # check if year is integer
                if not check_integer(row["year"]):
                    continue
                # check if day is integer
                if row["day"] and (not check_integer(row["day"])):
                    continue
                # check if expense is float value
                if not (check_float(row["expense"])):
                    continue
                # add data to the database
                cursor = connection.cursor()
                cursor.execute("INSERT INTO expenses (user_id, day, month, year, category, name, expense, remarks) VALUES (?, ?, ?, ?, ?, ?, ?, ?)", (session["user_id"], row["day"], row["month"], row["year"], row["category"], row["name"], row["expense"], row["remarks"]))
                connection.commit()
        flash('file uploaded successfully')
    return redirect("/")

@app.route("/edit", methods=["GET", "POST"])
@login_required
def edit():
    if request.method == "POST":
        # check if all the required field exist
        row_id = request.form.get("row_id")
        day = request.form.get("day")
        month = request.form.get("month")
        year = request.form.get("year")
        name =request.form.get("name")
        category = request.form.get("category")
        expense = request.form.get("expense")
        remarks = request.form.get("remarks")
        cursor = connection.cursor()
        edit_row = cursor.execute("SELECT * FROM expenses WHERE row_id = ?", [row_id]).fetchall()
        selected_month = edit_row[0][2]
        month_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

        if (not month) or (not year) or (not category) or (not name) or (not expense):
            flash("Please input month, year, name, category and expense")
            return render_template("edit.html", row = edit_row[0], months = month_list)
        # check if year is integer
        if not check_integer(year):
            flash("Year should be an integer")
            return render_template("edit.html", row = edit_row[0], months = month_list)
        # check if day is integer
        if day and (not check_integer(day)):
            flash("Day should be an integer")
            return render_template("edit.html", row = edit_row[0], months = month_list)

        # check if expense is float value
        if not (check_float(expense)):
            flash("Expenses should be numeric value")
            return render_template("edit.html", row = edit_row[0], months = month_list)
        # update the database
        cursor = connection.cursor()
        cursor.execute("UPDATE expenses SET day = ?, month = ?, year = ?, category = ?, name = ?, expense = ?, remarks = ? WHERE row_id = ?", (day, month, year, category, name, expense, remarks, row_id))
        connection.commit()
        return redirect("/")


@app.route("/summary", methods=["GET", "POST"])
@login_required
def summary():
    if request.method == "POST":
        # get month and year
        month = request.form.get("summary_select_month")
        year = request.form.get("summary_select_year")
        cal = request.form.get("summary_cal")
        sql_string = "CREATE TABLE tmp AS SELECT * FROM expenses WHERE user_id = ?"
        if month:
            tmp_string = f"month = '{month}'"
            sql_string = sql_string + " AND " + tmp_string
        if year:
            tmp_string = f"year = '{year}'"
            sql_string = sql_string + " AND " + tmp_string
        cursor = connection.cursor()
        #print(sql_string)
        cursor.execute("DROP TABLE IF EXISTS tmp")
        cursor.execute(sql_string, [session["user_id"]])
        distinct_year = cursor.execute("SELECT DISTINCT year FROM tmp").fetchall()
        distinct_month = cursor.execute("SELECT DISTINCT month FROM tmp").fetchall()
        load_option = 1
        expenses_summary=[]
        if cal == "show" and (not month or not year):
            flash("Please select month and year to show the summary")
            return redirect("/summary")
        if cal == "show":
            total_expenses = cursor.execute("SELECT SUM(expense) FROM tmp").fetchall()
            distinct_name = cursor.execute("SELECT DISTINCT name FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
            for name in distinct_name:
                tmp = cursor.execute("SELECT SUM(expense) FROM tmp WHERE name = ? AND user_id = ?", (name[0],session["user_id"])).fetchall()
                if not tmp[0][0]:
                    tmp = [(0,)]
                ave = float("{:.2f}".format(total_expenses[0][0]/len(distinct_name)))
                c_d = tmp[0][0]-ave
                expenses_summary.append([{"name":name[0],"total":tmp[0][0], "average":ave, "c/d":c_d }])
        cursor.execute("DROP TABLE IF EXISTS tmp")
        return render_template("summary.html", d_months=distinct_month, d_years=distinct_year,load_option = load_option, total_exp=expenses_summary)

    if request.method == "GET":
        cursor = connection.cursor()
        distinct_year = cursor.execute("SELECT DISTINCT year FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        distinct_month = cursor.execute("SELECT DISTINCT month FROM expenses WHERE user_id = ?", [session["user_id"]]).fetchall()
        load_option = 0
        return render_template("summary.html", d_months=distinct_month, d_years=distinct_year, load_option=load_option)


@app.route("/export", methods=["GET", "POST"])
@login_required
def export():
    if request.method == "POST":
        export_month = request.form.get("export_month")
        export_year = request.form.get("export_year")
        export_name = request.form.get("export_name")
        export_category = request.form.get("export_category")
        export_order = request.form.get("export_order")
        sql_string = "CREATE TABLE tmp AS SELECT * FROM expenses WHERE user_id = ?"
        filename="Expense"

        sql_string = sql_select_append(sql_string, "month", export_month)
        sql_string = sql_select_append(sql_string, "year", export_year)
        sql_string = sql_select_append(sql_string, "name", export_name)
        sql_string = sql_select_append(sql_string, "category", export_category)

        if export_order == "latest":
            sql_string = sql_string + " ORDER BY year DESC, month DESC, day DESC"
        if export_order == "oldest":
            sql_string = sql_string + " ORDER BY year ASC, month ASC, day ASC"

        cursor = connection.cursor()
        cursor.execute("DROP TABLE IF EXISTS tmp")
        cursor.execute(sql_string, [session["user_id"]])
        # outpur file
        csv_output = sqlite3.connect("expenses.db", isolation_level=None, detect_types=sqlite3.PARSE_COLNAMES)
        db_df = pd.read_sql_query("SELECT day, month, year, category, name, expense, remarks FROM tmp", csv_output)
        filename="export/Expense_"
        tmp = cursor.execute("SELECT user_name FROM users WHERE id = ?", [session["user_id"]]).fetchall()
        filename = filename + str(tmp[0][0]) +".csv"
        db_df.to_csv(filename, index=False)
        cursor.execute("DROP TABLE IF EXISTS tmp")
        realpath = os.path.realpath('app.py')
        realpath = realpath.replace("app.py","")
        realpath = realpath + filename
    return send_file(realpath, as_attachment=True)