#include "../include/Deck.h"
#include <iostream>

Deck::Deck() {
    initializeDeck();
    shuffle();
}

void Deck::initializeDeck() {
    for (int c = 0; c < 4; c++) {
        for (int v = 0; v < 10; v++) {
            Value cv = static_cast<Value>(v);
            Color cc = static_cast<Color>(c);
            
            cards.push_back(std::make_unique<Card>(cc, cv));
        }
    }
    
    for (int i = 0; i < 4; i++) {
        Color c = static_cast<Color>(i);
        
        cards.push_back(std::make_unique<Card>(c, Value::Skip));
        cards.push_back(std::make_unique<Card>(c, Value::Reverse));
        cards.push_back(std::make_unique<Card>(c, Value::Draw2));
    }
    
    for (int i = 0; i < 2; i++) {
        cards.push_back(std::make_unique<Card>(Color::Black, Value::ChangeColor));
        cards.push_back(std::make_unique<Card>(Color::Black, Value::Draw4));
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(cards.begin(), cards.end(), gen);
}

std::unique_ptr<Card> Deck::drawCard() {
    if (cards.empty()) return nullptr;
    
    std::unique_ptr<Card> c = std::move(cards.front());
    cards.erase(cards.begin());
    
    return c;
}

void Deck::reinsertBottom(std::unique_ptr<Card> c) {
    cards.push_back(std::move(c));
}

bool Deck::isEmpty() {
    return cards.empty();
}

Card& Deck::getCardOnTop() {
    return *cards.front();
}