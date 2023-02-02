* Family Expenses
#### Video Demo: https://youtu.be/ULEQj9V6yLg
#### Description:

"Family Expenses" is a web based application run by python. "Family Expenses" is a tool to record the expenses of a family
and caculate the monthly shared expenses for each family memeber.

The application has several functions:
1. User can create his/her own account to record his/her family xxpenses.
2. User can input the expenses manually or import the expenses by csv file.
3. User can look up the expenses details and edit and delete the data.
4. User can export and download the expenses details with csv file format.
5. User can have the summary of the expenses and monthly shared expenses.

A demo account is created.
username: cs50projectdemo
password: demo2023

#### Programme structure:
##### app.py:

This is the main programme. The file defines all the routes which the application used.
The routes of the programmes are:
1. '/login'
   - This route setup the login function. Most of the routes(function) are available after login.
    The user has to input username and password for login checking. The programme which compare the input
    with the data in databases "expenses.db" to verifty the login information.

2. '/register'
   - This route setup the register account function. User can creat account by inputing the username and pw.
   System will verify the username has been used or not by comparing with the databases "expenses.db".
   System will also check if the password fulfill the requirement. Account is created and the username
   and passcode_hash will be added to the database when the information passes the checking.

3. './logout'
   - This route use to clear the session information. User cannot access the login required function anymore unless
   he/she login again.

4. '/'
   - This route is the main pages of the application, which is the "expenses detail". The route queries the information from
   database "expenses.db" for the user and show those data on this page.

5. '/select'
   - This route defines the function of the data selection, ordering, data editing and deleting. For data selection, the route get
   the selected values from "details.html". And then the route queriese the information from database by condition(s)
   and display the data agian in "details.html". For ordering, user can choose ordering the data by latest date or oldest date. For data editing, the route queries the information of the data being
   selected to be edited from database and pass the value to "edit.html". For data deleting, system ask confirmation from
   user to delete the data. After confirmation, system delete the selected row from database "expenses.db".

6. '/edt'
    - This route defines the function of data editting. System ask user to input the information in "edit.html". After data verification, system updates the data in the databases.

7. '/dataimport'
   - This route defines the data importing function. System ask user to input the information in "dataimport.html" After data verification, system add the data in the databases.

8. '/dataimport_csv'
   - This route defines the data importion by csv function. System ask user to upload the csv file. After data verification,
   system add the data in the databases. If some rows of data fail the data verification, system skips that row (not adding to database).

9. '/summary'
   - This route defines the summary function. The system calculates the total expenses, averages expenses per person and credit/debit value bases on user selection on month and year.

10. '/export'
    - This route defines the export function. The system export the data selected by user to csv file and user can download that file.

##### helper.py:

This file contains the user-defined function:

1. 'login_required(f)'
   - check if the user_id is get or not, if not, redirect to the route '/login'.

2. 'check_integer(n)'
   - check if value 'n' can be change to integer, if not, return false, if yes, return true.

3. 'check_float(n)'
   - check if value 'n' can be change to float, if not, return false, if yes, return true.

4. 'sql_select_append(query_string, column, value)'
   - edit the 'query_string' by the input 'column' and 'value'

##### expenses.db:

This is the databases file which cotain three tables:

1. users
   - storing the user_name and hash for account login information checking.

2. expenses
   - storing the expenses details for all users.

3. tmp
   - this is temporary table for storing expenses details which user has placed condition in route '/select'

##### templates:

1. layout.html
   - define the layout of the web pages. There are some hyperlinks to let users to swithc to difference pages.

2. login.html
   - this is the login page. User can input username and password to login.

3. register.html
   - this is the account registration page. User can create account by inputing username and password.

4. details.html
   - this is the main pages/expenses details page. The page diplays the expenses details from the database. User can filter the data by selecting certain conditions (month, year, name , category). User can order the data by date. User can export the selected data to csv file.

5. dataimport.html
   - this is the page for data importing. User can input expenses details by manually or import the data by csv file. If by csv file, user can choose file to upload to server.

6. edit.html
   - this is the page for data editing. User can edit the expense details by input the infomration.

7. summary.html
   - this is the page for expenses summary display. User is asked which month to show the expense summary.

##### static:
1. styles.css
   - this is css file to style the html.

##### upload:
This is the folder for users to upload their csv file.

##### export:
This is the folder for users to download their csv file.

##### flask_session
This is the folder for storing the session file from flask.



