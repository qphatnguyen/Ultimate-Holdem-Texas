#include "PokerHT.h"

char Take_Card(int Number)
{
	char Cards[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
			    '8', '9', 'T', 'J', 'Q', 'K', 'A', '2', '3', '4', '5', '6', '7',
			    '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A', '2', '3', '4',
			    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
	
	return Cards[Number];
}

char Take_Suit(int Number)
{
	char Suits[] = {'\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03', '\x03',
			    '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04', '\x04',
			    '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05', '\x05',
			    '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06', '\x06'};
	
	return Suits[Number];
}

// ----- Hand -----
void Player_Hand(PHT_twoCards* &hand, int theSameCard[])
{
	if (hand == NULL)
		cout << "Something was wrong! {Function: [Player_Hand]}" << endl;
	else{
		srand(time(NULL));
		int theFirstCard = rand() % 52;
		hand->c1 = Take_Card(theFirstCard);
		hand->s1 = Take_Suit(theFirstCard);
		
		int theSecondCard = rand() % 52;
		while (true){
			if (theSecondCard == theFirstCard)
				theSecondCard = rand() % 52;
			else
				break;
		}
		hand->c2 = Take_Card(theSecondCard);
		hand->s2 = Take_Suit(theSecondCard);
		
		theSameCard[0] = theFirstCard;
		theSameCard[1] = theSecondCard;
	}
}

void Dealer_Hand(PHT_twoCards* &hand, int theSameCard[])
{
	if (hand == NULL)
		cout << "Something was wrong! {Function: [Dealer_Hand]}" << endl;
	else{
		srand(time(NULL));
		int theFirstCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 2; i++)
				if (theFirstCard == theSameCard[i])
					Check++;
			if (Check == 0)
				break;
			else
				theFirstCard = rand() % 52;
		}
		hand->c1 = Take_Card(theFirstCard);
		hand->s1 = Take_Suit(theFirstCard);
		theSameCard[2] = theFirstCard;
		
		int theSecondCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 3; i++)
				if (theSecondCard == theSameCard[i])
					Check++;
			if (Check == 0)
				break;
			else
				theSecondCard = rand() % 52;
		}
		hand->c2 = Take_Card(theSecondCard);
		hand->s2 = Take_Suit(theSecondCard);
		theSameCard[3] = theSecondCard;
	}
}

void Flop(PHT_threeCards* &hand, int theSameCard[])
{
	if (hand == NULL)
		cout << "Something was wrong! {Function: [Flop]}" << endl;
	else{
		srand(time(NULL));
		int theFirstCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 4; i++)
				if (theFirstCard == theSameCard[i])
					Check++;
			if (Check == 0)
				break;
			else
				theFirstCard = rand() % 52;
		}
		hand->c1 = Take_Card(theFirstCard);
		hand->s1 = Take_Suit(theFirstCard);
		theSameCard[4] = theFirstCard;
		
		int theSecondCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 5; i++)
				if (theSecondCard == theSameCard[i])
					Check++;
			if (Check == 0)
				break;
			else
				theSecondCard = rand() % 52;
		}
		hand->c2 = Take_Card(theSecondCard);
		hand->s2 = Take_Suit(theSecondCard);
		theSameCard[5] = theSecondCard;
		
		int theThirdCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 6; i++)
				if (theThirdCard == theSameCard[i])
					Check++;
			
			if (Check == 0)
				break;
			else
				theThirdCard = rand() % 52;
		}
		hand->c3 = Take_Card(theThirdCard);
		hand->s3 = Take_Suit(theThirdCard);
		theSameCard[6] = theThirdCard;
	}
}

void River(PHT_twoCards* &hand, int theSameCard[])
{
	if (hand == NULL)
		cout << "Something was wrong! {Function: [River]}" << endl;
	else{
		srand(time(NULL));
		int theFirstCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 7; i++)
				if (theFirstCard == theSameCard[i])
					Check++;
			if (Check == 0)
				break;
			else
				theFirstCard = rand() % 52;
		}
		hand->c1 = Take_Card(theFirstCard);
		hand->s1 = Take_Suit(theFirstCard);
		theSameCard[7] = theFirstCard;
		
		int theSecondCard = rand() % 52;
		while (true){
			int Check = 0;
			for (int i = 0; i < 8; i++)
				if (theSecondCard == theSameCard[i])
					Check++;
			if (Check == 0)
				break;
			else
				theSecondCard = rand() % 52;
		}
		hand->c2 = Take_Card(theSecondCard);
		hand->s2 = Take_Suit(theSecondCard);
	}
}
