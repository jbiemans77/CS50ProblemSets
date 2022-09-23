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
        # Validate submission
        name = request.form.get("name")
        birthMonth = request.form.get("birthMonth")
        birthDay = request.form.get("birthDay")
        
        if not name:
            return render_template("failure.html", name=name, birthMonth=birthMonth, birthDay=birthDay, message="Missing Name.")
        elif not birthMonth:
            return render_template("failure.html", name=name, birthMonth=birthMonth, birthDay=birthDay, message="Missing Birth Month.")
        elif not birthDay:
            return render_template("failure.html", name=name, birthMonth=birthMonth, birthDay=birthDay, message="Missing Birth Day.")

        # Add Birthday to database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, birthMonth, birthDay)

        # Return to index
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * from birthdays ORDER BY UPPER(name)")

        return render_template("index.html", birthdays=birthdays)