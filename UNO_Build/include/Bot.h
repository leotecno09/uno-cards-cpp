#pragma once

#include "Player.h"

class Bot : public Player {
public:
    Bot(Deck& deck);
    int chooseCard(Card& topCard, int opponentCards) override;
    bool checkWin() override;
    int evaluateCard(Card& card, int opponentCards);
    Color chooseColor(Color currentColor, int opponentCards) override;
};
