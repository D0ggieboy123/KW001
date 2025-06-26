board = [[" "," "," "],[" "," "," "],[" "," "," "]]
column = {"a":0,"b":1,"c":2}
row = {"1":0,"2":1,"3":2}
def printBoard():
    print("  a b c")
    x = 1
    for row in board:
        print(x,end = " ")
        x += 1
        for i in row:
            print(i,end = " ")
        print()
def placesymbol(row, column, turn):
    if board [row][column] != " ":
        return False
    else:
        if turn:
            board [row][column] = "x"
        else:
            board [row][column] = "o"
        return True

def maingame():
    turn = True #True = x False = o
    print("tictactoe")
    isrunning = True
    while isrunning:
        printBoard()
        if turn:
            print("Its x's turn")
        else:
            print("Its o's turn")
        choice = input("enter a position ex(a1): ")
        row_ = row[choice[1]]
        column_ = column[choice[0]]
        while len(choice) != 2 or choice[0] < "a" or choice[0] > "c" or choice[1] < "1" or choice[1] > "3" or not placesymbol(row_,column_,turn):
            print("invalid input")
            choice = input("enter a position ex(a1): ")
            row_ = row[choice[1]]
            column_ = column[choice[0]]

maingame()