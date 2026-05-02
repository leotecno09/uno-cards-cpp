#pragma once
#include <vector>
#include <memory>
#include "Deck.h"

class Player {
protected:
    std::vector<std::unique_ptr<Card>> hand;
public:
    virtual ~Player() = default;
    
    virtual int chooseCard(Card& topCard, int opponentCards) = 0;
    virtual bool checkWin() = 0;
    virtual Color chooseColor(Color currentColor, int opponentCards) = 0;
    
    int getCardCount();
    int playCard(int cardIndex, std::vector<std::unique_ptr<Card>>& discardPile);
    void drawFromDeck(Deck& deck);
};
