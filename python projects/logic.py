from random import *
def startgame():
    board = []
    for i in range(4):
        board.append([0]*4)
    print("w = move up\na = move left\ns = move down \nd = move right")
    add_two(board)
    return board
def add_two(board):
    row = randint(0,3)
    column = randint(0,3)
    cells_checked = 0
    while cells_checked <= 16: 
        if board[row][column] != 0:
            cells_checked += 1
            row = randint(0,3)
            column = randint(0,3)
        else: 
            board[row][column] = 2
# -1 means loss 0 means continue game 1 means player has won
def get_stats(board):
    if player_wins(board):
        return 1
    elif player_loses(board):
        return -1    
    else:
        return 0
def player_wins(board):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == 2048:
                return True
    return False
def player_loses(board):
    empty_cells = 0
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == 0:
                empty_cells += 1
    return empty_cells == 0
def shift(board):
    neo_board = []
    for i in range(4):
        neo_board.append([0] * 4)
    for i in range(len(board)):
        k = 0
        for j in range(len(board[i])):
            if board[i][j] != 0:
                neo_board[i][k] = board[i][j]
                k += 1
    return neo_board
def merge(board):
    for i in range(len(board)):
        for j in range(len(board[i])-1):
            if board[i][j] == board[i][j+1] and board[i][j+1] != 0:
                board[i][j] = board[i][j] + board[i][j+1]
                board[i][j+1] = 0
    return board

def move_left(board):
    new_board = shift(board)
    new_board = merge(new_board)
    new_board = shift(new_board)
    return new_board
def reverse(board):
    new_board = []
    for i in range(len(board)):
        new_board.append([])
        for j in range(len(board[i])):
            new_board[i].append(board[i][len(board[i]) - 1 - j])
    return new_board
def move_right(board):
    new_board = reverse(board)
    new_board = move_left(new_board)
    new_board = reverse(new_board)
    return new_board
def transpose(board):
    new_board = []
    for i in range(4):
        new_board.append([0]*4)
    for i in range(len(board)):
        for j in range(len(board[i])):
            new_board[j][i] = board[i][j]
    return new_board
def move_down(board):
    new_board = transpose(board)
    new_board = move_right(new_board)
    new_board = transpose(new_board)
    return new_board
def move_up(board):
    new_board = transpose(board)
    #new_board = reverse(new_board)
    new_board = move_left(new_board)
    new_board = transpose(new_board)
    return new_board



