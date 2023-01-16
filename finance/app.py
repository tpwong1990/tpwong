import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    """Show portfolio of stocks"""
    # get portfolio and cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    portfolio = db.execute("SELECT symbol, shares FROM portfolio WHERE user_id = ?", session["user_id"])
    if not portfolio:
        portfolio = []
    return render_template("index.html", portfolio=portfolio, cash=cash)
    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not shares or not symbol:
            return apology("input cannot be empty")
        # quote the price of the stock
        result = lookup(symbol)
        if result:
            # found
            # calculate the cost
            cost = float(shares) * result["price"]
            # check if user has enough money to buy
            current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            if current_cash[0]["cash"] >= cost:
                # can buy
                cash_temp = current_cash[0]["cash"] - cost
                # update portfolio
                # check if the current stock exist in portfolio or not
                portfolio = db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
                if not portfolio:
                    db.execute("INSERT INTO portfolio (user_id, symbol, shares) VALUE(?, ?, ?)", session["user_id"], symbol, shares)
                else:
                    current_share = portfolio[0]["shares"]
                    new_share = current_share + shares
                    db.execute("UPDATE portofolio SET shares = ? WHERE id = ? AND symbol = ?", new_share, session["user_id"], symbol)
                # update history
                price = usd(cost)
                share_1 = "+".join(str(shares))
                time = datetime.datetime.now()
                db.execute("INSERT INTO history (history_id, symbol, shares, price, time) VALUE(?, ?, ?, ?, ?)", session["user_id"], symbol, share_1, price, time)
                return redirect("/")
            else:
            # cannot buy
                return apology("Not enough cash to buy the stock")
        else:
        # not found
            return apology("Stock not found")

    # return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        result = lookup(symbol)
        if result:
            # found
            return render_template("quoted.html", quoted=result)
        else:
            # not found
            return apology("Stock not found")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        user_name = request.form.get("username")
        user_pw = request.form.get("password")
        user_pw_con = request.form.get("confirmation")
        # check if the pw match with pw_con
        if not user_name:
            return apology("The username is empty")
        if not user_pw:
            return apology("The password is empty")
        if not (user_pw == user_pw_con):
            return apology("The passwords does not match")
        user_hash = generate_password_hash(user_pw)
        # check if the username is exist or not
        exist = db.execute("SELECT * FROM users WHERE username = ?", user_name)
        if exist:
            # return error
            return apology("Username already exist")
        else:
            # add user data to database
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", user_name, user_hash)
            return render_template("login.html")
    else:
        return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
