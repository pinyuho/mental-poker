import random


def gen_deck():
    cards = [1, 2]
    return cards


class Player(object):

    def __init__(self):
        self.main_key = random.randint(0, 1000)
        self.ind_keys = [random.randint(1, 1000) for i in range(1, 55)]

    def enc_deck_main(self, deck):
        new_deck = []
        for card in deck:
            new_deck.append(card * self.main_key)
        return new_deck

    def enc_deck_ind(self, deck):
        new_deck = []
        for i in range(len(deck)):
            new_deck.append(deck[i] * self.ind_keys[i])
        return new_deck

    def dec_deck_main(self, deck):
        new_deck = []
        for card in deck:
            new_deck.append(card / self.main_key)
        return new_deck

    def card_request(self, p, choices):
        chosen_cards = []
        other_keys = []
        self_keys = []
        for choice in choices:
            other_keys.append(p.ind_keys[choice])
            self_keys.append(self.ind_keys[choice])
            chosen_cards.append(deck[choice] / (self.ind_keys[choice] * p.ind_keys[choice]))
        return chosen_cards

    def shuffle_deck(self, deck):
        random.shuffle(deck)
        return deck


deck = gen_deck()
cards = [card for card in deck]

print "\n###  The cards are in the deck are:\n"
print cards

# print "\n\n###  We represent them as such so that integer operations can be performed on them.\n"
# print deck


alice = Player()
bob = Player()

deck = alice.enc_deck_main(deck)
deck = alice.shuffle_deck(deck)
print "\n\n###  This is how the deck looks like after Alice has encrypted and shuffled it. Bob can't make sense of the deck in this state\n"
print deck


deck = bob.enc_deck_main(deck)
deck = bob.shuffle_deck(deck)
print "\n\n###  This is how the deck looks like after Bob has encrypted and shuffled it. Neither Bob nor Alice can make sense of the deck in this state.\n"
print deck


deck = alice.dec_deck_main(deck)
deck = alice.enc_deck_ind(deck)
print "\n\n###  Alice decrypts the cards and encrypts them individually. Neither Bob nor Alice can make sense of the deck in this state.\n"
print deck

deck = bob.dec_deck_main(deck)
deck = bob.enc_deck_ind(deck)
print "\n\n###  Bob decrypts the cards and encrypts them individually. Neither Bob nor Alice can make sense of the deck in this state.\n"
print deck

alice_choices = input("###  Which cards does alice pick? \n")
print "\n###  The cards selected after a secure shuffle are:\n"
print [card for card in alice.card_request(bob, alice_choices)]