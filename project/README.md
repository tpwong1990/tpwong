* Family Expenses
#### Video Demo:
#### Description:

"Family Expenses" is a web based application run by python. "Family Expenses" is a tool to record the expenses of a family
and caculate the monthly shared expenses for each family memeber.

The application has several functions:
1. User can create his/her own account to record his/her family xxpenses.
2. User can input the expenses manually or import the expenses by csv file.
3. User can look up the expenses details and edit and delete the data.
4. User can export and download the expenses details with csv file format.
5. User can have the summary of the expenses and monthly shared expenses.

#### Programme structure:
##### app.py:

This is the main programme. The file defines all the routes which the application used.
The routes of the programmes are:
1. '/login'

This route setup the login function. Most of the routes(function) are available after login.
The user has to input username and password for login checking. The programme which compare the input
with the data in databases "expenses.db" to verifty the login information.

2. '/register'

This route setup the register account function. User can creat account by inputing the username and pw.
System will verify the username has been used or not by comparing with the databases "expenses.db".
System will also check if the password fulfill the requirement. Account is created and the username
and passcode_hash will be added to the database when the information passes the checking.

3. './logout'

This route use to clear the session information. User cannot access the login required function anymore unless
he/she login again.

4. '/'

This route is the main pages of the application, which is the "expenses detail". The route queries the information from
database "expenses.db" for the user and show those data on this page.

5. '/select'

This route define the function of the data selection, data editing and deleting. For data selection, the route get
the selected values from "details.html". And then the route queriese the information from database by condition(s)
and display the data agian in "details.html". For data editing, the route queries the information of the data being
selected to be edited from database and pass the value to "edit.html". For data deleting, system ask confirmation from
user to delete the data. After confirmation, system delete the selected row from database "expenses.db"

6. '/edt'

The route define the function of data editting. The func



