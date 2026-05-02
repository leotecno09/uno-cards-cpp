#include "../include/HumanPlayer.h"

HumanPlayer::HumanPlayer(Deck& deck) {
    for (int i = 0; i < 7; i++) {
        hand.push_back(deck.drawCard());
    }
}

int HumanPlayer::viewCards() {
    int i = 0;
    std::cout << "\n=======================\nHai queste carte:\n";
    
    for (i = 0; i < hand.size(); i++) {
        std::cout << "[" << i << "] ";
        hand[i]->print();
        std::cout << "\n"; 
    }
    
    std::cout << "[" << i << "] Pesca dal mazzo / salta\n";
    return i;
}

int HumanPlayer::chooseCard(Card& topCard, int opponentCards) {
    int choice;
    
    std::cout << "Carta sul tavolo: "; 
    topCard.print();
    
    std::cout << "\n\nL'avversario ha " << opponentCards << " carte\n";
    
    int drawOpt = viewCards();
    
    while (true) {
        std::cout << "Quale vuoi giocare? ";
        std::cin >> choice;
        
        if (choice == drawOpt) return -1;
        
        if (choice > hand.size() || choice < 0) std::cout << "Carta invalida\n";
        else break;
    }
    
    return choice;
}

Color HumanPlayer::chooseColor(Color currentColor, int opponentCards) {
    std::cout << "Scegli il colore (0 = Rosso, 1 = Verde, 2 = Blu, 3 = Giallo): ";
    
    int c;
    std::cin >> c;
    return static_cast<Color>(c);
}

bool HumanPlayer::checkWin() {
    if (hand.size() == 0) {
        std::cout << "\n\nHAI VINTO!\n\n";
        return true;
    }
    
    return false;
}