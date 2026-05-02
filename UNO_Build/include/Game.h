#pragma once
#include "Deck.h"
//#include "Player.h"
#include "HumanPlayer.h"
#include "Bot.h"

class Game {
private:
    std::unique_ptr<Deck> drawDeck;
    std::vector<std::unique_ptr<Card>> discardPile;         // perchè non fare singolo unique_ptr? Tanto ci basta contarlo come una carta
    std::vector<std::unique_ptr<Player>> players;
    
    int currentPlayer = 0;
    int direction = 1; // -1 antiorario 1 orario
    bool gameRunning = false;
    bool isWindows = false;
public:
    Game();
    //void setup(int nBots);
    void setWindows() { isWindows = true; }
    void play();
    void applyEffect(const Card& card);
    void nextPlayer();
    void applySkip();
    void applyReverse();
    void applyDrawFour(Player* playingPlayer);
    void applyDrawTwo();
    void applyChangeColor(Player* playingPlayer);
};
