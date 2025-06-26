import random
suit = ["hearts","diamonds","clubs","spades"]
numbers = ["ace","2","3","4","5","6","7","8","9","10","jack","king","queen"]
deck = []
for i in numbers:
    for j in suit:
        deck.append((i,j))
def card_value(card):
    if card[0] == "king" or card[0] == "queen" or card[0] == "jack":
        return 10
    elif card[0] == "ace":
        return 11
    else:
        return int(card[0])
def calc_score(cards):
    sum = 0 
    for i in cards: 
        sum += card_value(i)
    return sum
def check_ace(cards,score):
    if score > 21:
        for i in cards:
            if i[0] == "ace":
                return True
    return False
# negative one is lose, zero is tie, positive one is win
def game(player,dealer):
    while True:
        player_score = calc_score(player)
        dealer_score = calc_score(dealer)
        print("dealer's cards:",dealer[0][0],"of",dealer[0][1])
        print("dealer's score:",card_value(dealer[0]))
        print("player's cards: ", end = "")
        for i in player:
            print(i[0], "of", i[1],end = "  ")
        if check_ace(player,player_score):
            player_score -= 10
        print("\nplayer's score:", player_score,"\n")
        if player_score > 21:
                
            print("dealer won")
            return -1
        choice = input("do want to hit or stand?: ").lower()
        print()
        if choice == "hit":
            newcard = deck.pop()
            player.append(newcard)
        elif choice == "stand":
            break
        else:
            print("invalid choice")


    if player_score <= 21:
        while dealer_score < 17:
            newcard = deck.pop()
            dealer.append(newcard)
            dealer_score += card_value(newcard)
        print("dealer's cards: ", end = "")
        for i in dealer:
            print(i[0], "of", i[1],end = "  ")
        print("\ndealer score:",dealer_score,"\n")
        if dealer_score >= 22:
            print("you won!")
            return 1
        elif player_score > dealer_score:
            print("you won!")
            return 1
        elif dealer_score > player_score:
            print("the dealer won")
            return -1
        else:
            print("its a tie")
            return 0 
bank = 500
while True:
    choice = input("do you want to play or quit? ").lower()
    if choice == "play":
        random.shuffle(deck)
        player = [deck.pop(), deck.pop()]
        dealer = [deck.pop(), deck.pop()]
        if bank <= 0:
            print("you have lost all your bets")
            break
        print("you have $" + str(bank))
        bet = int(input("how much money do you want to bet? "))
        while bet > bank:
            bet = int(input("you've bet to much money, reenter your bet: "))
        bank -= bet
        winner = game(player,dealer)
        if winner == 1:
            bank += bet * 2
        elif winner == 0:
            bank += bet
    elif choice == "quit":
        break
    else:
        print("invalid input try again")