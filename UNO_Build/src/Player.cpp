#include "../include/Player.h"
#include <iostream>

int Player::getCardCount() {
    return hand.size();
}

int Player::playCard(int cardIndex, std::vector<std::unique_ptr<Card>>& discardPile) {
    if (hand[cardIndex]->isPlayable(*discardPile.back())) {
        discardPile.push_back(std::move(hand[cardIndex]));
        hand.erase(hand.begin() + cardIndex);
        
        if (hand.size() == 1) {
            std::cout << "\n\nUNO!\n\n";
        }
        
        return 0;
    }
    
    return -1;
}

void Player::drawFromDeck(Deck& deck) {
    hand.push_back(deck.drawCard());
}

