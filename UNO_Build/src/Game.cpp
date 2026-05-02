#include <thread>
#include <chrono>
#include "../include/Game.h"

Game::Game() : drawDeck(std::make_unique<Deck>()) {
    players.push_back(std::make_unique<HumanPlayer>(*drawDeck));
    players.push_back(std::make_unique<Bot>(*drawDeck));
}

void Game::play() {
    gameRunning = true;
    
    // metti giù carta iniziale
    Value fv;
    std::unique_ptr<Card> firstCard;

    bool hasDrawn = false;
    
    while (true) {
        firstCard = drawDeck->drawCard();
        fv = firstCard->getValue();
        
        if (fv == Value::ChangeColor || fv == Value::Draw2 || fv == Value::Draw4 || fv == Value::Skip || fv == Value::Reverse) {
            drawDeck->reinsertBottom(std::move(firstCard));
        } else {
            break;
        }
    }
        
    discardPile.push_back(std::move(firstCard));
    
    while (gameRunning) {
        if (players[0]->checkWin() || players[1]->checkWin()) {
            gameRunning = false;
            break;
        }
        
        if (currentPlayer == 1) {
            // finto bot thinking
            std::cout << "\n\nIl bot sta pensando...\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

        Card& topCard = *discardPile.back();
        
        while (true) {
            int toPlay = players[currentPlayer]->chooseCard(topCard, currentPlayer == 0 ? players[1]->getCardCount() : players[0]->getCardCount());
            
            if (toPlay == -1) {
                
                if (!hasDrawn) {
                    players[currentPlayer]->drawFromDeck(*drawDeck);

                    if (currentPlayer == 1) {
                        std::cout << "Il bot ha pescato\n\n";
                    }

                    hasDrawn = true;
                    continue;
                }

                if (currentPlayer == 1) {
                    std::cout << "Il bot ha saltato\n\n";
                }

                break;
            }
            
            int canPlay = players[currentPlayer]->playCard(toPlay, discardPile);

            if (currentPlayer == 1) {
                // per vedere skip e reverse del bot
                std::cout << "Il bot ha giocato un ";
                discardPile.back()->print();
                std::cout << "\n\n";
            }

            applyEffect(*discardPile.back());

            if (canPlay == -1) {
                std::cout << "Non puoi giocare quella carta!\n";
            } else {
                break;
            }
        }
        
        hasDrawn = false;
        nextPlayer();
    }

    if (isWindows) system("pause");
    else system("read");

}

void Game::applyEffect(const Card& card) {
    switch (card.getValue()) {
        case Value::Skip: 
            applySkip(); 
            break;

        case Value::Reverse:
            applyReverse();
            break;

        case Value::Draw2:
            applyDrawTwo();
            break;

        case Value::Draw4:
            applyDrawFour(players[currentPlayer].get());
            break;

        case Value::ChangeColor:
            applyChangeColor(players[currentPlayer].get());
            break;

        default:
            break;
    }
}

void Game::nextPlayer() {
    currentPlayer = (currentPlayer + direction + players.size()) % players.size();
}

void Game::applySkip() {
    nextPlayer();
}

void Game::applyReverse() {
    if (players.size() == 2) {
        nextPlayer();
        return;
    }

    direction *= -1; // la matematika
}

void Game::applyDrawTwo() {
    // permettere risposta con altro +2
    int next = (currentPlayer + direction + players.size()) % players.size();

    players[next]->drawFromDeck(*drawDeck);
    players[next]->drawFromDeck(*drawDeck);

    nextPlayer();
}

void Game::applyDrawFour(Player* playingPlayer) {
    int next = (currentPlayer + direction + players.size()) % players.size();

    for (int i = 0; i < 4; i++) {
        players[next]->drawFromDeck(*drawDeck);
    }

    Color newColor = playingPlayer->chooseColor(discardPile.back()->getColor(), players[next]->getCardCount());
    discardPile.back()->setColor(newColor);

    nextPlayer();
}

void Game::applyChangeColor(Player* playingPlayer) {
    int next = (currentPlayer + direction + players.size()) % players.size();

    Color newColor = playingPlayer->chooseColor(discardPile.back()->getColor(), players[next]->getCardCount());
    discardPile.back()->setColor(newColor);
}




