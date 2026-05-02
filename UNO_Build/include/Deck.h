#pragma once
#include "Card.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;
    
public:
    Deck();
    void initializeDeck();
    void shuffle();
    std::unique_ptr<Card> drawCard();
    void reinsertBottom(std::unique_ptr<Card>);
    bool isEmpty();
    Card& getCardOnTop();
};
