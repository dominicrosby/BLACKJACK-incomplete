#ifndef BLACKJACK_H
#define BLACKJACK_H

#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono> 

// Enum to define the suits
enum Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

// Struct that defines an individual card
struct Card
{
    Card();

    Card(unsigned rank, Suit suit){
        mRank = rank;
        mSuit = suit;
    }
    
    unsigned getRank() const{
        return mRank;
    }

    unsigned getSuit() const{
        return mSuit;
    }

    void printCard(){
        char rank;
        //if()
    }
    
    unsigned mRank;
    Suit mSuit;
};

class Hand
{
public:
    Hand(){
        mHand.clear();
        mScore = 0;
    }

    unsigned getScore(){
        return mScore;
    }

    void setScore(unsigned rank){
        mScore += rank;
    }

    Card back(){
        return mHand.back();
    }

    void pop_back(){
        mHand.pop_back();
    }

    bool aceCheck();

    bool bust(){
        for(int i = 0; i < getSize(); i++){
		//inputHand.setScore(inputHand[i].getRank());
	    }
	    if(getScore()>21){
		    return true;
	    }
	    else{
		    return false;
	    }
    }

    void drawCard(std::vector<Card>& deck);

    int firstMove();

    unsigned getSize()const{
        return mHand.size();
    }

    void push_back(Card card){
        mHand.push_back(card);
    }

    const Card& operator[](size_t index) const {
        return mHand[index];
    }
private:

    // Data
    std::vector<Card> mHand;
    unsigned mScore;
};

// Function to add another deck to the current deck
void addDeck(std::vector<Card>& deck);

// Function to create a deck of cards (52 cards)
void createDeck(std::vector<Card>& deck, std::mt19937& g);

bool promptHit();

void dealerDraw(Hand& dealerHand, Hand myHand, std::vector<Card>& deck);

void displayHand(Hand myHand, Hand dealerHand);

void displaySplitHand(Hand myHand, Hand mySplitHand, Hand dealerHand);

void playBlackjack(std::vector<Card>& deck,std::mt19937& g);

void playHand(std::vector<Card>& deck, Hand myHand, Hand dealerHand);

std::ostream& operator<<(std::ostream& os, const Card& card);

std::ostream& operator<<(std::ostream& os, const Hand& myhand);

#endif // BLACKJACK_H
/*
Card Blueprints:
CLUBS
  _________    _________ 
 |J        |  |6   _    |
 |   ( )   |  |  _(_)_  |
 | ( ) ( ) |  | (_) (_) |
 |    |    |  |    |    |
 |        J|  |        6|
  ---------    ---------

HEARTS
  _________  
 |J        | 
 |  / V \  | 
 |  \   /  | 
 |   \ /   | 
 |        J|
  ---------

DIAMINDS
  _________
 |J        | 
 |   / \   | 
 |  (   )  | 
 |   \ /   | 
 |        J| 
  ---------  

SPADES
  _________
 |J        |
 |   / \   | 
 |  ( | )  | 
 |   / \   | 
 |        J|
  ---------

*/