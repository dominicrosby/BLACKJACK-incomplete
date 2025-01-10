#include "blackjack.h"
#include <iostream>

int main() {
    
    std::vector<Card> deck;
    std::random_device rd;       // Random device to seed the Mersenne Twister engine
    std::mt19937 g(rd());        // Mersenne Twister generator seeded with random_device
    playBlackjack(deck, g);

    return 0;
}
