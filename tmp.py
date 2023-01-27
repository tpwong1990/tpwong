        #print(total_expenses[0])
        # calculate total expenses by person
        expenses_summary=[]
        for name in distinct_name:
            tmp = cursor.execute("SELECT SUM(expense) FROM expenses WHERE user_id = ? AND name = ? AND year = ? AND month = ?",(session["user_id"], name[0] ,year, month)).fetchall()
            print(name[0])
            print(tmp[0][0])
            if not tmp[0][0]:
                tmp = [(0,)]
            ave = float("{:.2f}".format(total_expenses[0][0]//len(distinct_name)))
            c_d = tmp[0][0]-ave
            expenses_summary.append([{"name":name[0],"total":tmp[0][0], "average":ave, "c/d":c_d }])
        #print(expenses_summary)


        total_expenses = cursor.execute("SELECT Sum(expense) FROM expenses WHERE user_id = ? AND year = ? AND month = ?", (session["user_id"], year, month)).fetchall()
