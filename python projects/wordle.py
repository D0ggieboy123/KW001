import random 
import termcolor
from LONGLISTOFWORDS import words
def compare(user_guess,word):
# -1 means no match, 0 means correct char wrong place, one means correct char rigt place
    output = [-1] * len(word)
    found = []
    for i in range(len(user_guess)):
        if user_guess[i] == word[i]:
            output[i] = 1
            found.append(i)
    for i in range(len(user_guess)):
        if user_guess[i] in word and output[i] != 1:
            ind = find_ind(word,user_guess[i])
            for j in ind:
                if j not in found:
                    output[i] = 0
                    found.append(j)
                    break
    return output
def find_ind(word,char):
    ind = []
    i = word.find(char)
    while i != -1:
        ind.append(i)
        i = word.find(char,i+1)
    return ind
hello = input("enter 1 if you want to play, enter 0 if not: ")
while hello != "1" and hello != "0":
    hello = input("invalid input")
while hello == "1":
    wordle = random.choice(words)
    for i in range(6):
        user_guess = input(f"try to guess the wordle, you have {6 - i} tries: ")
        while len(user_guess) != 5:
            user_guess = input("please type only a five letter word: ")
        stats = compare(user_guess,wordle)
        for j in range(len(user_guess)):
            if stats[j] == 1:
                termcolor.cprint(user_guess[j],"green",end=" ")
            elif stats[j] == 0:
                termcolor.cprint(user_guess[j],"yellow",end=" ")
            else:
                termcolor.cprint(user_guess[j],"red",end=" ")
        print()
        if user_guess == wordle:
            print("you win!!")
            break
    print("the wordle was", wordle)
    hello = input("enter 1 if you want to play, enter 0 if not: ")
    while hello != "1" and hello != "0":
        hello = input("invalid input") 