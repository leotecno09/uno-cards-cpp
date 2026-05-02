#pragma once
#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(Deck& deck);
    int chooseCard(Card& topCard, int opponentCards) override;
    int viewCards();
    bool checkWin() override;
    Color chooseColor(Color currentColor, int opponentCards) override;
};