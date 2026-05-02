#include "../include/Bot.h"

#include <map>

Bot::Bot(Deck& deck) {
    for (int i = 0; i < 7; i++) {
        hand.push_back(deck.drawCard());
    }
}

int Bot::chooseCard(Card& topCard, int opponentCards) {
    int bestIndex = -1;
    int bestScore = -1;
    
    for (int i = 0; i < hand.size(); i++) {
        Card& c = *hand[i];
        
        if (!c.isPlayable(topCard)) continue;
        
        int score = evaluateCard(c, opponentCards);
        
        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }
    
    return bestIndex;
}

Color Bot::chooseColor(Color currentColor, int opponentCards) {
    std::map<Color, int> freq;
    
    for (auto& c : hand) {
        if (c->getColor() != Color::Black) {
            freq[c->getColor()]++;
        }
    }
    
    Color bestColor = Color::Red;
    int bestScore = -1;
    
    for (auto& [color, count] : freq) {
        if (color == currentColor) continue;
        
        int score = count;
        
        if (opponentCards == 1) {
            score += 10;    // cerchiamo di cambiare colore se il player sta vincendo
        }
        
        if (score > bestScore) {
            bestScore = score;
            bestColor = color;
        }
    }
    
    return bestColor;
}

bool Bot::checkWin() {
    if (hand.empty()) {
        std::cout << "\n\nMi spiace, il bot ha vinto...\n\n";
        return true;
    }
    
    return false;
}

int Bot::evaluateCard(Card& c, int opponentCards) {
    int score = 0;
    
    switch (c.getValue()) {
        case Value::Draw4: score = 100; break;
        case Value::Draw2: score = 80; break;
        case Value::Skip: score = 70; break;
        case Value::Reverse: score = 60; break;
        case Value::ChangeColor: score = 50; break;
        default: score = 10;
    }
    
    if (opponentCards == 1) {
        
        // boost di score se il player ha 1 sola carta
        if (c.getValue() == Value::Draw4 || c.getValue() == Value::Draw2 || c.getValue() == Value::Skip) {
            score += 50;
        }
        
        if (c.getValue() == Value::ChangeColor) {
            score += 20;
        }
    }
    
    return score;
}
