#include "blackjack.h"
#include <iostream>

void playBlackjack(std::vector<Card>& deck, std::mt19937& g){
	//ADD : prompt for double
	//ADD : split
	//ADD : betting amounts
	//ADD : multiple decks
	//ADD : play again option (default) with auto shuffle
	//ADD : win rate calculator
	createDeck(deck, g);
	Hand myHand;
	Hand dealerHand;
	
	Hand testSplit;
	std::vector<Card> test;
	//test.push_back(Card(7,CLUBS));
	test.push_back(Card(14, SPADES));
	myHand.drawCard(test);
	//myHand.drawCard(test);
	//starting cards
	//myHand.drawCard(deck);
	dealerHand.drawCard(deck);
	myHand.drawCard(deck);
		
	playHand(deck, myHand, dealerHand);
}

void playHand(std::vector<Card>& deck, Hand myHand, Hand dealerHand){
	//blackJack
	if(myHand.getScore()==21){
		displayHand(myHand, dealerHand);
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		dealerHand.drawCard(deck);
		displayHand(myHand, dealerHand);
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		if(dealerHand.getScore() == 21){
			std::cout<<"PUSH";
		}
		else{
			dealerDraw(dealerHand, myHand, deck);
			std::cout<<"BLACKJACK!"<<std::endl;
		}
	}
	//no blackJack
	else{
		displayHand(myHand, dealerHand);
		int firstMove = myHand.firstMove();
		//if player hits or doubles
		while(firstMove == 1 || firstMove == 2){
			myHand.drawCard(deck);
			displayHand(myHand, dealerHand);
			if(myHand.bust() == true){
				std::cout<<"YOU LOSE, BUSTED!"<<std::endl;
				break;
			}
			if(firstMove == 2){
				firstMove = 0;
				break;
			}
			bool hit = promptHit();
			//stand
			if(hit == false){
				firstMove = 0;
			}
		}
		//split
		if(firstMove == 3){
			Hand myHandSplit;
			Card splitCard = myHand.back();
			Card firstCard = myHand[0];
			std::vector<Card> tempVec;
			tempVec.push_back(firstCard);
			tempVec.push_back(splitCard);
			
			//clear hand
			myHand.pop_back();
			myHand.pop_back();
			myHand.setScore(0);

			myHand.drawCard(tempVec);
			myHandSplit.drawCard(tempVec);
			displaySplitHand(myHand, myHandSplit, dealerHand);
			char key;
			while (key != 'C' && key !='c') {
				std::cout<<"press ""C"" to continue and play first hand:";
				std::cin >> key;
    		}

			displayHand(myHand, dealerHand);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			myHand.drawCard(deck);
			playHand(deck, myHand, dealerHand);
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));

			displaySplitHand(myHand, myHandSplit, dealerHand);
			char key2;
			while (key2 != 'C' && key2 !='c') {
				std::cout<<"press ""C"" to continue and play second hand:";
				std::cin >> key2;
    		}
			displayHand(myHandSplit, dealerHand);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			myHandSplit.drawCard(deck);
			playHand(deck, myHandSplit, dealerHand);
		}
		//compare hands
		else{
			//dealer draws cards
			dealerDraw(dealerHand, myHand, deck);
			displayHand(myHand, dealerHand);
			//check dealer hand busts
		
			if(dealerHand.getScore()>21){
				std::cout<<"YOU WIN, DEALER BUST!"<<std::endl;
			}
			//if neither bust compare scores
			else{
				if(dealerHand.getScore()>myHand.getScore()){
					std::cout<<"YOU LOSE, "<<dealerHand.getScore()<<" BEATS "<<myHand.getScore()<<std::endl;
				}
				else if(dealerHand.getScore()<myHand.getScore()){
					std::cout<<"YOU WIN, "<<myHand.getScore()<<" BEATS "<<dealerHand.getScore()<<std::endl;
				}
				//in tie
				else{
					if(dealerHand.getScore() == 21 && dealerHand.getSize() == 2){
						std::cout<<"YOU LOSE DEALER BLACKJACK"<<std::endl;
					}
					else{
						std::cout<<"PUSH"<<std::endl;
					}
				}
			}
		}
	}
}

void Hand::drawCard(std::vector<Card>& deck) {
    if (!deck.empty()) {
        Card drawnCard = deck.back(); // Take the last card from the deck
        deck.pop_back();              // Remove it from the deck
        mHand.push_back(drawnCard);   // Add it to the hand

        // Update the score
        if (drawnCard.getRank() < 10) {          // Numbered cards
            mScore += drawnCard.getRank();
        } else if (drawnCard.getRank() < 14) {   // Face cards (Jack, Queen, King)
            mScore += 10;
        } else {                                 // Ace
            mScore += 11;
        }
		aceCheck();
    } else {
        std::cout << "The deck is empty!" << std::endl;
    }
}

void displayCard(std::vector<char> ranks, std::vector<int> suits, int handSize){
		
		for(int i = 0; i<handSize; i++){	
			std::cout<<"  _________  ";
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize; i++){	
			std::cout<<" |"<<ranks[i]<<"        | ";
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize; i++){	
			switch(suits[i]){
				case 0:
					std::cout<<" |   (_)   | ";
					break;
				case 1:
					std::cout<<" |   / \\   | ";	
					break;
				case 2:
					std::cout<<" |  / V \\  | ";
					break;
				case 3:
					std::cout<<" |   / \\   | ";
					break;
			}
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize; i++){	
			switch(suits[i]){
				case 0:
					std::cout<<" | (_)|(_) | ";
					break;
				case 1:
					std::cout<<" |  (   )  | ";	
					break;
				case 2:
					std::cout<<" |  \\   /  | ";
					break;
				case 3:
					std::cout<<" |  ( | )  | ";
					break;
			}
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize; i++){	
			switch(suits[i]){
				case 0:
					std::cout<<" |    ^    | ";
					break;
				case 1:
					std::cout<<" |   \\ /   | ";	
					break;
				case 2:
					std::cout<<" |   \\ /   | ";
					break;
				case 3:
					std::cout<<" |   / \\   | ";
					break;
			}
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize; i++){	
			std::cout<<" |        "<<ranks[i]<<"| ";
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize; i++){	
			std::cout<<"  ---------  ";
		}
		std::cout<<"\n"<<std::endl;
}

void displaySplitCard(std::vector<char> ranks1, std::vector<int> suits1, int handSize1, std::vector<char> ranks2, std::vector<int> suits2, int handSize2){
	for(int i = 0; i<handSize1; i++){	
			std::cout<<"  _________  ";
		}
		std::cout<<"                    ";
	for(int i = 0; i<handSize2; i++){	
			std::cout<<"  _________  ";
		}
		std::cout<<std::endl;

	for(int i = 0; i<handSize1; i++){	
				std::cout<<" |"<<ranks1[i]<<"        | ";
			}
			std::cout<<"                    ";
	for(int i = 0; i<handSize2; i++){	
			std::cout<<" |"<<ranks2[i]<<"        | ";
		}
		std::cout<<std::endl;


	for(int i = 0; i<handSize1; i++){	
		switch(suits1[i]){
			case 0:
				std::cout<<" |   (_)   | ";
				break;
			case 1:
				std::cout<<" |   / \\   | ";	
				break;
			case 2:
				std::cout<<" |  / V \\  | ";
				break;
			case 3:
				std::cout<<" |   / \\   | ";
			break;
			}
		}
			std::cout<<"                    ";
	for(int i = 0; i<handSize2; i++){	
		switch(suits2[i]){
			case 0:
				std::cout<<" |   (_)   | ";
				break;
			case 1:
				std::cout<<" |   / \\   | ";	
				break;
			case 2:
				std::cout<<" |  / V \\  | ";
				break;
			case 3:
				std::cout<<" |   / \\   | ";
				break;
			}
		}
		std::cout<<std::endl;


		for(int i = 0; i<handSize1; i++){	
			switch(suits1[i]){
				case 0:
					std::cout<<" | (_)|(_) | ";
					break;
				case 1:
					std::cout<<" |  (   )  | ";	
					break;
				case 2:
					std::cout<<" |  \\   /  | ";
					break;
				case 3:
					std::cout<<" |  ( | )  | ";
					break;
			}
		}
		std::cout<<"                    ";
		for(int i = 0; i<handSize2; i++){	
			switch(suits2[i]){
				case 0:
					std::cout<<" | (_)|(_) | ";
					break;
				case 1:
					std::cout<<" |  (   )  | ";	
					break;
				case 2:
					std::cout<<" |  \\   /  | ";
					break;
				case 3:
					std::cout<<" |  ( | )  | ";
					break;
			}
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize1; i++){	
			switch(suits1[i]){
				case 0:
					std::cout<<" |    ^    | ";
					break;
				case 1:
					std::cout<<" |   \\ /   | ";	
					break;
				case 2:
					std::cout<<" |   \\ /   | ";
					break;
				case 3:
					std::cout<<" |   / \\   | ";
					break;
			}
		}
		std::cout<<"                    ";
		for(int i = 0; i<handSize2; i++){	
			switch(suits2[i]){
				case 0:
					std::cout<<" |    ^    | ";
					break;
				case 1:
					std::cout<<" |   \\ /   | ";	
					break;
				case 2:
					std::cout<<" |   \\ /   | ";
					break;
				case 3:
					std::cout<<" |   / \\   | ";
					break;
			}
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize1; i++){	
			std::cout<<" |        "<<ranks1[i]<<"| ";
		}
		std::cout<<"                    ";
		for(int i = 0; i<handSize2; i++){	
			std::cout<<" |        "<<ranks2[i]<<"| ";
		}
		std::cout<<std::endl;

		for(int i = 0; i<handSize1; i++){	
			std::cout<<"  ---------  ";
		}
		std::cout<<"                    ";
		for(int i = 0; i<handSize2; i++){	
			std::cout<<"  ---------  ";
		}
		std::cout<<"\n"<<std::endl;
}

void displayHand(Hand myHand, Hand dealerHand){
	std::cout<<"\n\n";
	std::vector<char> myRanks;
	std::vector<int> mySuits;
	for(int i = 0; i<myHand.getSize(); i++){
		if(myHand[i].getRank()<10){
			myRanks.push_back('0'+myHand[i].getRank());
		}
		else if(myHand[i].getRank()==10){
			myRanks.push_back('T');
		}
		else if(myHand[i].getRank()==11){
			myRanks.push_back('J');
		}
		else if(myHand[i].getRank()==12){
			myRanks.push_back('Q');
		}
		else if(myHand[i].getRank()==13){
			myRanks.push_back('K');
		}
		else if(myHand[i].getRank()==14){
			myRanks.push_back('A');
		}
		mySuits.push_back(myHand[i].getSuit());
	}

	std::cout<<"YOUR HAND - SCORE: "<<myHand.getScore();
	if(myHand.aceCheck() == true){
		std::cout<<"(soft)"<<std::endl;
	}
	else{
		std::cout<<std::endl;
	}
	displayCard(myRanks, mySuits, myHand.getSize());

	std::vector<char> dealerRanks;
	std::vector<int> dealerSuits;
	for(int i = 0; i < dealerHand.getSize(); i++) {
		if(dealerHand[i].getRank() < 10) {
			dealerRanks.push_back('0' + dealerHand[i].getRank());
		}
		else if(dealerHand[i].getRank() == 10) {
			dealerRanks.push_back('T');
		}
		else if(dealerHand[i].getRank() == 11) {
			dealerRanks.push_back('J');
		}
		else if(dealerHand[i].getRank() == 12) {
			dealerRanks.push_back('Q');
		}
		else if(dealerHand[i].getRank() == 13) {
			dealerRanks.push_back('K');
		}
		else if(dealerHand[i].getRank() == 14) {
			dealerRanks.push_back('A');
		}
		dealerSuits.push_back(dealerHand[i].getSuit());
	}
	std::cout<<"VS DEALER - SCORE:"<<dealerHand.getScore()<<std::endl;

	displayCard(dealerRanks, dealerSuits, dealerHand.getSize());
}

void displaySplitHand(Hand myHand, Hand mySplitHand, Hand dealerHand){
	std::cout<<"\n\n";
	std::vector<char> myRanks;
	std::vector<int> mySuits;
	for(int i = 0; i<myHand.getSize(); i++){
		if(myHand[i].getRank()<10){
			myRanks.push_back('0'+myHand[i].getRank());
		}
		else if(myHand[i].getRank()==10){
			myRanks.push_back('T');
		}
		else if(myHand[i].getRank()==11){
			myRanks.push_back('J');
		}
		else if(myHand[i].getRank()==12){
			myRanks.push_back('Q');
		}
		else if(myHand[i].getRank()==13){
			myRanks.push_back('K');
		}
		else if(myHand[i].getRank()==14){
			myRanks.push_back('A');
		}
		mySuits.push_back(myHand[i].getSuit());
	}

	std::vector<char> mySplitRanks;
	std::vector<int> mySplitSuits;
	for(int i = 0; i<mySplitHand.getSize(); i++){
		if(mySplitHand[i].getRank()<10){
			mySplitRanks.push_back('0'+myHand[i].getRank());
		}
		else if(mySplitHand[i].getRank()==10){
			mySplitRanks.push_back('T');
		}
		else if(mySplitHand[i].getRank()==11){
			mySplitRanks.push_back('J');
		}
		else if(mySplitHand[i].getRank()==12){
			mySplitRanks.push_back('Q');
		}
		else if(mySplitHand[i].getRank()==13){
			mySplitRanks.push_back('K');
		}
		else if(mySplitHand[i].getRank()==14){
			mySplitRanks.push_back('A');
		}
		mySplitSuits.push_back(mySplitHand[i].getSuit());

	std::cout<<"SPLIT HANDS"<<std::endl;
	std::cout<<"FIRST HAND - SCORE: "<<mySplitHand.getScore();
	std::cout<<"                SECOND HAND - SCORE: "<<mySplitHand.getScore();
	if(mySplitHand.aceCheck() == true){
		std::cout<<"(soft)"<<std::endl;
	}
	else{
		std::cout<<std::endl;
	}
	displaySplitCard(myRanks, mySuits, myHand.getSize(), mySplitRanks, mySplitSuits, mySplitHand.getSize());

	std::vector<char> dealerRanks;
	std::vector<int> dealerSuits;
	for(int i = 0; i < dealerHand.getSize(); i++) {
		if(dealerHand[i].getRank() < 10) {
			dealerRanks.push_back('0' + dealerHand[i].getRank());
		}
		else if(dealerHand[i].getRank() == 10) {
			dealerRanks.push_back('T');
		}
		else if(dealerHand[i].getRank() == 11) {
			dealerRanks.push_back('J');
		}
		else if(dealerHand[i].getRank() == 12) {
			dealerRanks.push_back('Q');
		}
		else if(dealerHand[i].getRank() == 13) {
			dealerRanks.push_back('K');
		}
		else if(dealerHand[i].getRank() == 14) {
			dealerRanks.push_back('A');
		}
		dealerSuits.push_back(dealerHand[i].getSuit());
	}
	std::cout<<"VS DEALER - SCORE:"<<dealerHand.getScore()<<std::endl;

	displayCard(dealerRanks, dealerSuits, dealerHand.getSize());

	}
}

void dealerDraw(Hand& dealerHand, Hand myHand, std::vector<Card>& deck){
	if(dealerHand.aceCheck()==false)
		do{
			dealerHand.drawCard(deck);
			displayHand(myHand, dealerHand);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		}
		while(dealerHand.getScore()<17);
	//dealer hits on soft 17
	else{
		do{
			dealerHand.drawCard(deck);
			displayHand(myHand, dealerHand);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		}
		while(dealerHand.getScore()<18);
	}
}

void createDeck(std::vector<Card>& deck, std::mt19937& g){
    for (int i = 2; i <= 14; i++) {
         deck.push_back(Card(i, SPADES)); 
         deck.push_back(Card(i, CLUBS)); 
         deck.push_back(Card(i, HEARTS)); 
         deck.push_back(Card(i, DIAMONDS)); 
    }
	std::shuffle(deck.begin(), deck.end(), g);
}

bool bust(Hand inputHand){
	if(inputHand.getScore()>21){
		return true;
	}
	else{
		return false;
	}
}

bool Hand::aceCheck() {
	int trueScore = 0;
	int limit = 0;
	for(int i = 0; i< mHand.size(); i++){
		if (mHand[i].getRank() < 10) {     
            trueScore += mHand[i].getRank();
        } 
		else if (mHand[i].getRank() < 14) {  
            trueScore += 10;
        } 
		else {                                
            trueScore += 11;
        }
	}	
	int aceCount = 0;
	for(int i = 0; i< mHand.size(); i++){
		if(mHand[i].getRank() == 14){
			aceCount++;
		}
	}
	limit = (21+ aceCount *10);	
	//if ace need recuction
	if(trueScore > 21 && trueScore < limit){
		for(int i = 0; i < aceCount; i++){
			//if truescore is less than limit
			if(trueScore - (10)*(i+1) < 21){
				trueScore -= 10*(i+1);
				mScore = trueScore;
				if((i+1)<aceCount){
					return true;
				}
				else{
					return false;
				}
				break;
			}
			//else if hand bust anyways
			else if(trueScore > limit){
				mScore = trueScore - aceCount*10;
				return false;
			}
			//if under 21 do nothing
			else{
				if(aceCount==0){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
}

bool promptHit() {
    std::cout << "Hit (H) or Stand (S): ";
    char input;
    while (true) { // Infinite loop until a valid input is received
        std::cin >> input;
        if (input == 'S' || input == 's') {
            std::cout<<"\n\n";
			return false;
        } else if (input == 'H' || input == 'h'){
			std::cout<<"\n\n";
            return true;
        } else{
		}
    }
}

int Hand::firstMove(){
	bool splitCase = false;
	if(mHand.size() == 2 && mHand[0].getRank() == mHand[1].getRank()){
		std::cout<<"Hit (H) ,  Stand (S) , Double (D) or Split (P): ";
		splitCase = true;
	}
	else{
		std::cout << "Hit (H) , Stand (S) or Double (D): ";
		splitCase = false;
	}
    char input;
    while (true) {
        std::cin >> input;
		//stand
        if (input == 'S'|| input == 's') {
            std::cout <<"\n";
			return 0;
		//hit
        } else if (input == 'H'|| input == 'h'){
			std::cout <<"\n";
            return 1;
		//double
        } else if (input == 'D' || input == 'd'){
			std::cout<<"\n";
			return 2;
		}
		//split
		if (splitCase == true){
			if(input == 'P' || input == 'p'){
				std::cout<<"\n";
				return 3;
			}
		}
    }
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	switch(card.mSuit)
	{
		case SPADES:
		switch(card.mRank)
		{
			case 11:
			os<< "JS";
			break;

			case 12:
			os<< "QS";
			break;

			case 13:
			os<< "KS";
			break;

			case 14:
			os<<"AS";
			break;
			
			default:
			os << card.mRank << "S";
			break;
		}
		break;

		case HEARTS:
		switch(card.mRank)
		{
			case 11:
			os<< "JH";
			break;

			case 12:
			os<< "QH";
			break;

			case 13:
			os<< "KH";
			break;

			case 14:
			os<<"AH";
			break;
			
			default:
			os << card.mRank << "H";
			break;
		}
		break;

		case DIAMONDS:
		switch(card.mRank)
		{
			case 11:
			os<< "JD";
			break;

			case 12:
			os<< "QD";
			break;

			case 13:
			os<< "KD";
			break;

			case 14:
			os<<"AD";
			break;
			
			default:
			os << card.mRank << "D";
			break;
		}
		break;

		case CLUBS:
		switch(card.mRank)
		{
			case 11:
			os<< "JC";
			break;

			case 12:
			os<< "QC";
			break;

			case 13:
			os<< "KC";
			break;

			case 14:
			os<<"AC";
			break;
			
			default:
			os << card.mRank << "C";
			break;
		}
		break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Hand& myhand){
    for(unsigned i = 0;i<myhand.getSize();i++){
        std::cout<<myhand[i]<<" ";
    }
	return os;
}