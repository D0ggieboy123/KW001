import logic
board = logic.startgame()
while True:
    for i in board:
        for n in i:
            print(n, end = ' ' )
        print()
    move = input("enter your move: ").lower()
    if move == "a":
        board = logic.move_left(board)
    elif move =="d":
        board = logic.move_right(board)
    elif move == "s":
        board = logic.move_down(board)
    elif move == "w":
        board = logic.move_up(board)
    else:
        print("invalid input >:(")
        continue
    s = logic.get_stats(board)
    if s == -1:
        print("you have lost :p")
        break
    elif s == 1:
        print("you have won :D ")
        break                                  
    logic.add_two(board)
        