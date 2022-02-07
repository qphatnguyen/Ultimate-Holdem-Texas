#include "PokerHT.h"

char Char[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
int Inte[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

// ----- Changing -----
int changeChartoInte(char card)
{
	for (int i = 0; i < 13; i++)
		if (card == Char[i])
			return Inte[i];
}

char changeIntetoChar(int card)
{
	for (int i = 0; i < 13; i++)
		if (card == Inte[i])
			return Char[i];
}

int CountNotTheSameCards(char* BigHand)
{
	int n = 7;
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i) == *(BigHand + i + 2))
			n -= 1;
	}
	return n;
}

// ----- Sorting -----
char* Sort_BigHand(PHT_twoCards* hand, PHT_threeCards* flop, PHT_twoCards* river)
{
	if (hand == NULL || flop == NULL || river == NULL)
		return NULL;
	
	int* sevenCards = new int[7];
	char* sevenSuits = new char[7];
	if (sevenCards == NULL || sevenSuits == NULL)
		return NULL;
	
	// ----- about cards -----
	*sevenCards = changeChartoInte(hand->c1);
	*(sevenCards + 1) = changeChartoInte(hand->c2);
	*(sevenCards + 2) = changeChartoInte(flop->c1);
	*(sevenCards + 3) = changeChartoInte(flop->c2);
	*(sevenCards + 4) = changeChartoInte(flop->c3);
	*(sevenCards + 5) = changeChartoInte(river->c1);
	*(sevenCards + 6) = changeChartoInte(river->c2);
	
	// ----- about suits -----
	*sevenSuits = hand->s1;
	*(sevenSuits + 1) = hand->s2;
	*(sevenSuits + 2) = flop->s1;
	*(sevenSuits + 3) = flop->s2;
	*(sevenSuits + 4) = flop->s3;
	*(sevenSuits + 5) = river->s1;
	*(sevenSuits + 6) = river->s2;
	
	for (int i = 0; i < 6; i++)
		for (int j = i + 1; j < 7; j++)
			if (*(sevenCards + i) < *(sevenCards + j)){
				swap(*(sevenCards + i), *(sevenCards + j));
				swap(*(sevenSuits + i), *(sevenSuits + j));
			}
			
	char* bigHand = new char[14];
	if (bigHand == NULL)
		return NULL;
	int countCard = 0, countSuit = 0;	
	for (int i = 0; i < 14; i++)
		if (i % 2 == 0){
			*(bigHand + i) = changeIntetoChar(*(sevenCards + countCard));
			countCard++;
		}
		else{
			*(bigHand + i) = *(sevenSuits + countSuit);
			countSuit++;
		}
	
	delete []sevenSuits;
	delete []sevenCards;
	
	return bigHand;	
}

char* Sort_StandardHand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL)
		return NULL;

	if (Check_StraightFlush_7Cards(BigHand) == true){
		standardhand = Standard_StraightFlush_Hand(BigHand);
	}
	else if (Check_Quads_7Cards(BigHand) == true){
		standardhand = Standard_Quads_Hand(BigHand);
	}
	else if (Check_FullHouse_7Cards(BigHand) == true){
		standardhand = Standard_FullHouse_Hand(BigHand);
	}
	else if (Check_Flush_7Cards(BigHand) == true){
		standardhand = Standard_Flush_Hand(BigHand);
	}
	else if (Check_Straight_7Cards(BigHand) == true){
		standardhand = Standard_Straight_Hand(BigHand);
	}
	else if (Check_ThreeofKind_7Cards(BigHand) == true){
		standardhand = Standard_ThreeofKind_Hand(BigHand);
	}
	else if (Check_twoPair_7Cards(BigHand) == true){
		standardhand = Standard_twoPair_Hand(BigHand);
	}
	else if (Check_aPair_7Cards(BigHand) == true){
		standardhand = Standard_aPair_Hand(BigHand);
	}
	else{
		for (int i = 0; i < 10; i++)
			*(standardhand + i) = *(BigHand + i);
	}
	
	return standardhand;
}

int* Anti_TheSameCards(char* BigHand)
{
	int n = CountNotTheSameCards(BigHand), count = 0;
	
	int* ConvertBigHand = new int[n];
	if (ConvertBigHand == NULL)
		return NULL;
		
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i) == *(BigHand + i + 2) && *(BigHand + i) == *(BigHand + i + 4)){ //For exemple: [A K K K Q J T]
			*(ConvertBigHand + count) = changeChartoInte(*(BigHand + i + 4));
			i += 4;
		}
		else if (*(BigHand + i) == *(BigHand + i + 2)){ //For exemple: [9 9 8 7 6 5 3]
			*(ConvertBigHand + count) = changeChartoInte(*(BigHand + i + 2));
			i += 2;
		}
		else
			*(ConvertBigHand + count) = changeChartoInte(*(BigHand + i));
		
		count++;
	}
	return ConvertBigHand;
}
// ----- Comparison -----
void ComparedHands(PHT_twoCards* player, PHT_twoCards* dealer, PHT_threeCards* flop, PHT_twoCards* river, int &checkAnte, int &checkResult)
{
	if (player == NULL || dealer == NULL || flop == NULL || river == NULL)
		cout << "Something was wrong! {Function: [ComparedHand]}" << endl;
	else{
		char* Player_BigHand = new char[14];
		Player_BigHand = Sort_BigHand(player, flop, river);
		char* Dealer_BigHand = new char[14];
		Dealer_BigHand = Sort_BigHand(dealer, flop, river);
		
		if (Player_BigHand == NULL || Dealer_BigHand == NULL)
			cout << "Something was wrong! {Function: [ComparedHand]}" << endl;
		else{
			/*
			cout << "Player's big hand: ";
			for (int i = 0; i < 14; i+=2)
				cout << *(Player_BigHand + i) << *(Player_BigHand + i + 1) << " ";
			cout << endl << "Dealer's big hand: ";
			for (int i = 0; i < 14; i+=2)
				cout << *(Dealer_BigHand + i) << *(Dealer_BigHand + i + 1) << " ";
			cout << endl;
			*/
			
			//----- Get a condition for checkAnte -----
			checkAnte = Higher_QuickTest(Player_BigHand);
			
			char* Player_StandardHand = new char[10];
			Player_StandardHand = Sort_StandardHand(Player_BigHand);
			char* Dealer_StandardHand = new char[10];
			Dealer_StandardHand = Sort_StandardHand(Dealer_BigHand);
			
			if (Player_StandardHand == NULL || Dealer_StandardHand == NULL)
				cout << "Something was wrong! {Function: [ComparedHand]}" << endl;
			else{	
				/*
				gotoXY(2, 8);
				ShowPlayer_StandardHand(Player_StandardHand);
				gotoXY(2, 9);
				cout << "                     "; //----- Backspace technique -----
				gotoXY(2, 9);
				ShowHigher(Player_BigHand);
				
				gotoXY(2, 10);
				ShowDealer_StandardHand(Dealer_StandardHand);
				gotoXY(2, 11);
				cout << "                     "; //----- Backspace technique -----
				gotoXY(2, 11);
				ShowHigher(Dealer_BigHand);
				
				gotoXY(2, 12);
				cout << "           ";
				gotoXY(2, 12);
				*/
				
				if (Higher_Comparison(Player_BigHand, Dealer_BigHand, Player_StandardHand, Dealer_StandardHand) == 0){
					gotoXY(4, 12);
					ShowPlayer_StandardHand(Player_StandardHand);
					gotoXY(4, 13);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(4, 13);
					ShowHigher(Player_BigHand, 0); //Player win!
					/*
					gotoXY(2, 12);
					ShowDealer_StandardHand(Dealer_StandardHand);
					gotoXY(2, 13);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(2, 13);
					ShowHigher(Dealer_BigHand);
					*/
					gotoXY(4, 9);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(4, 10);
					cout << "                                        "; //----- Backspace technique -----
					gotoXY(4, 11);
					cout << "                     "; //----- Backspace technique ----
					gotoXY(23, 11);
					cout << "Player Win!";
					
					checkResult = 0;
				}
				else if (Higher_Comparison(Player_BigHand, Dealer_BigHand, Player_StandardHand, Dealer_StandardHand) == 1){
					gotoXY(4, 12);
					ShowDealer_StandardHand(Dealer_StandardHand);
					gotoXY(4, 13);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(4, 13);
					ShowHigher(Dealer_BigHand, 1); //Dealer win!
					/*
					gotoXY(2, 12);
					ShowPlayer_StandardHand(Player_StandardHand);
					gotoXY(2, 13);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(2, 13);
					ShowHigher(Player_BigHand);
					*/
					gotoXY(4, 9);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(4, 10);
					cout << "                                        "; //----- Backspace technique -----
					gotoXY(4, 11);
					cout << "                     "; //----- Backspace technique ----
					gotoXY(23, 11);
					cout << "Dealer Win!";
					
					checkResult = 1;
				}
				else if (Higher_Comparison(Player_BigHand, Dealer_BigHand, Player_StandardHand, Dealer_StandardHand) == 2){
					gotoXY(4, 10);
					ShowPlayer_StandardHand(Player_StandardHand);
					gotoXY(4, 11);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(4, 11);
					ShowHigher(Player_BigHand, 2); //Draw!
					
					gotoXY(4, 12);
					ShowDealer_StandardHand(Dealer_StandardHand);
					gotoXY(4, 13);
					cout << "                     "; //----- Backspace technique -----
					gotoXY(4, 13);
					ShowHigher(Dealer_BigHand, 2); //Draw!
					
					gotoXY(4, 9);
					cout << "           ";
					gotoXY(23, 9);
					cout << "DRAW";
					
					checkResult = 2;
				}
			}
		}
	}
}
 
// ----- Checking -----
bool Check_aPair_7Cards(char* BigHand)
{
	for (int i = 0; i < 12; i += 2)
		if (*(BigHand + i) == *(BigHand + i + 2))
			return true;
	return false;
}

bool Check_twoPair_7Cards(char* BigHand)
{
	if (*BigHand == *(BigHand + 2)){ // [o o . . . . .]
		for (int i = 4; i < 12; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	else if (*(BigHand + 2) == *(BigHand + 4)){ // [x o o . . . .]
		for (int i = 6; i < 12; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	else if (*(BigHand + 4) == *(BigHand + 6)){ // [ x x o o . . .]
		for (int i = 8; i < 12; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	else if (*(BigHand + 6) == *(BigHand + 8) && *(BigHand + 10) == *(BigHand + 12)) // [x x x o o . .]
		return true;
		
	return false;
}

bool Check_ThreeofKind_7Cards(char* BigHand)
{
	for (int i = 0; i < 10; i += 2)
		if (*(BigHand + i) == *(BigHand + i + 2) && *(BigHand + i) == *(BigHand + i + 4))
			return true;
	
	return false;
}

bool Check_Straight_7Cards(char* BigHand)
{	
	int n = CountNotTheSameCards(BigHand);
	if (n < 5)
		return false;
	
	int* ConvertBigHand = new int[n];
	ConvertBigHand = Anti_TheSameCards(BigHand);
	if (ConvertBigHand == NULL)
		return false;
	
	if (*ConvertBigHand == 14){ // When [A] stands first.
		if ((*(ConvertBigHand + n - 1) == 2) && (*(ConvertBigHand + n - 2) == 3) && (*(ConvertBigHand + n - 3) == 4) && (*(ConvertBigHand + n - 4) == 5))
			return true; //For exemple: [A 9 7 5 4 3 2]
		else if((*(ConvertBigHand + 1) == 13) && (*(ConvertBigHand + 2) == 12) && (*(ConvertBigHand + 3) == 11) && (*(ConvertBigHand + 4) == 10))
			return true; //For exemple: [A K Q J T 5 2]
		else{
			for (int i = 0; i < n - 4; i++){
				if ((*(ConvertBigHand + i) == *(ConvertBigHand + i + 1) + 1) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 2) + 2) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 3) + 3) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 4) + 4))
					return true;
			}
		}
	}
	else{
		for (int i = 0; i < n - 4; i++){
			if ((*(ConvertBigHand + i) == *(ConvertBigHand + i + 1) + 1) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 2) + 2) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 3) + 3) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 4) + 4))
				return true;
		}
	}
	
	return false;
}

bool Check_Flush_7Cards(char* BigHand)
{
	int countHearts = 0, countDiamonds = 0, countClubs = 0, countSpades = 0;
	for (int i = 1; i < 14; i += 2){
		if (*(BigHand + i) == '\x03')
			countHearts++;
		else if (*(BigHand + i) == '\x04')
			countDiamonds++;
		else if (*(BigHand + i) == '\x05')
			countClubs++;
		else if (*(BigHand + i) == '\x06')
			countSpades++;
	}
	
	if (countHearts >= 5 || countDiamonds >= 5 || countClubs >= 5 || countSpades >= 5)
		return true;
	return false;
}

char WhichSuit(char* BigHand)
{
	if (Check_Flush_7Cards(BigHand) == true){
		for (int i = 1; i < 7; i+=2){
			int count = 0;
			char suit = *(BigHand + i);
			
			for (int j = i + 2; j < 14; j+=2)
				if (*(BigHand + i) == *(BigHand + j))
					count++;
					
			if (count >= 4)
				return suit;
		}
	}
	
	return 0;
}

int CountFlushCards(char* BigHand)
{
	int count = 0;
	char suit = WhichSuit(BigHand);
	
	for (int i = 1; i < 14; i += 2){
		if (*(BigHand + i) == suit)
			count++;
	}
	return count;
}

bool Check_FullHouse_7Cards(char* BigHand)
{
	if (*BigHand == *(BigHand + 2) && *BigHand == *(BigHand + 4)){ // [o o o . . . .]
		for (int i = 6; i < 12; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	else if (*(BigHand + 2)== *(BigHand + 4) && *(BigHand + 2) == *(BigHand + 6)){ // [x o o o . . .]
		for (int i = 8; i < 12; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	else if (*(BigHand + 4)== *(BigHand + 6) && *(BigHand + 4) == *(BigHand + 8)){ // [. . o o o . .]
		if (*BigHand == *(BigHand + 2) || *(BigHand + 10) == *(BigHand + 12))
			return true;
	}
	else if (*(BigHand + 6)== *(BigHand + 8) && *(BigHand + 6) == *(BigHand + 10)){ // [. . . o o o x]
		for (int i = 0; i < 4; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	else if (*(BigHand + 8)== *(BigHand + 10) && *(BigHand + 8) == *(BigHand + 12)){ // [. . . . o o o]
		for (int i = 0; i < 6; i += 2)
			if (*(BigHand + i) == *(BigHand + i + 2))
				return true;
	}
	
	return false;
}

bool Check_Quads_7Cards(char* BigHand)
{
	for (int i = 0; i < 8; i+= 2)
		if (*(BigHand + i) == *(BigHand + i + 2) && *(BigHand + i) == *(BigHand + i + 4) && *(BigHand + i) == *(BigHand + i + 6))
			return true;
			
	return false;
}

bool Check_StraightFlush_7Cards(char* BigHand)
{
	if (Check_Flush_7Cards(BigHand) == true){
		int Flushquan = CountFlushCards(BigHand);
		int* straight = new int[Flushquan];
		if (straight == NULL)
			return false;
		
		int storage = 0;
		char check = WhichSuit(BigHand);
		for (int i = 0; i < 14; i+=2){
			if (*(BigHand + i + 1) == check){
				*(straight + storage) = changeChartoInte(*(BigHand + i));
				storage += 1;	
			}
			
			if (storage == Flushquan)
				break;
		}
			
		if (*straight == 14){ // When [A] stands first.
			if ((*(straight + Flushquan - 1) == 2) && (*(straight + Flushquan - 2) == 3) && (*(straight + Flushquan - 3) == 4) && (*(straight + Flushquan - 4) == 5))
				return true;
			else if((*(straight + 1) == 13) && (*(straight + 2) == 12) && (*(straight + 3) == 11) && (*(straight + 4) == 10))
				return true;
			else{
				for (int i = 0; i < Flushquan - 4; i++){
					if ((*(straight + i) == *(straight + i + 1) + 1) && (*(straight + i) == *(straight + i + 2) + 2) && (*(straight + i) == *(straight+ i + 3) + 3) && (*(straight + i) == *(straight + i + 4) + 4))
						return true;
				}
			}
		}
		else{
			for (int i = 0; i < Flushquan - 4; i++){
				if ((*(straight + i) == *(straight + i + 1) + 1) && (*(straight + i) == *(straight + i + 2) + 2) && (*(straight + i) == *(straight+ i + 3) + 3) && (*(straight + i) == *(straight + i + 4) + 4))
					return true;
			}
		}
	}
	
	return false;
}

bool Check_RoyalStraightFlush_7Cards(char* BigHand)
{
	if (Check_Flush_7Cards(BigHand) == true){
		int Flushquan = CountFlushCards(BigHand);
		int* straight = new int[Flushquan];
		if (straight == NULL)
			return false;
		
		int storage = 0;
		char check = WhichSuit(BigHand);
		for (int i = 0; i < 14; i+=2){
			if (*(BigHand + i + 1) == check){
				*(straight + storage) = changeChartoInte(*(BigHand + i));
				storage += 1;	
			}
			
			if (storage == Flushquan)
				break;
		}
			
		if ((*straight == 14) && (*(straight + 1) == 13) && (*(straight + 2) == 12) && (*(straight + 3) == 11) && (*(straight + 4) == 10)){ 
			return true; //Standard hand has {A} [K] [Q] [J] (T) which are the same suit.
		}
	}
	
	return false;
}

int* Combine_FlushCards(char* BigHand)
{
	int sizeof_flushcards = CountFlushCards(BigHand);
	int* combinecards = new int[sizeof_flushcards];
	if (combinecards == NULL)
		return NULL;
		
	char suit = WhichSuit(BigHand);
	int count = 0;
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i + 1) == suit){
			*(combinecards + count) = changeChartoInte(*(BigHand + i));
			count++;
		}
		if (count == sizeof_flushcards)
			break;
	}
	
	return combinecards;
}

// ----- Types of higher -----
int Higher_QuickTest(char* BigHand)
{
	if (Check_RoyalStraightFlush_7Cards(BigHand))
		return 10;
	if (Check_StraightFlush_7Cards(BigHand))
		return 9;
	if (Check_Quads_7Cards(BigHand))
		return 8;
	if (Check_FullHouse_7Cards(BigHand))
		return 7;
	if (Check_Flush_7Cards(BigHand))
		return 6;
	if (Check_Straight_7Cards(BigHand))
		return 5;
	if (Check_ThreeofKind_7Cards(BigHand))
		return 4;
	if (Check_twoPair_7Cards(BigHand))
		return 3;
	if (Check_aPair_7Cards(BigHand))
		return 2;
	
	return 1;
}

int Higher_Detail(char* Player_StandardHand, char* Dealer_StandardHand){
	for (int i = 0; i < 10; i+=2){
		if (changeChartoInte(*(Player_StandardHand + i)) > changeChartoInte(*(Dealer_StandardHand + i)))
			return 0; //Player win!
		else if (changeChartoInte(*(Player_StandardHand + i)) < changeChartoInte(*(Dealer_StandardHand + i)))
			return 1; //Dealer win!
	}
	
	return 2; //Draw!
}

int Higher_Comparison(char* Player_BigHand, char* Dealer_BigHand, char* Player_StandardHand, char* Dealer_StandardHand)
{
	if (Higher_QuickTest(Player_BigHand) > Higher_QuickTest(Dealer_BigHand)){
		return 0; // ----- Player Win -----
	}
	else if (Higher_QuickTest(Player_BigHand) < Higher_QuickTest(Dealer_BigHand)){
		return 1; // ----- Player Lose -----
	}
	/*
	if (Player_StandardHand == NULL || Dealer_StandardHand == NULL)
		cout << "Something was wrong! {Function: [ComparedHand]}" << endl;
	else{
		cout << "Player's standard hand: ";
		for (int i = 0; i < 10; i+=2)
			cout << *(Player_StandardHand + i) << *(Player_StandardHand + i + 1) << " ";
		cout << endl << "Dealer's standard hand: ";
		for (int i = 0; i < 10; i+=2)
			cout << *(Dealer_StandardHand + i) << *(Dealer_StandardHand + i + 1) << " ";
		cout << endl;
	}
	*/
	
	if (Higher_Detail(Player_StandardHand, Dealer_StandardHand) == 0){
		return 0; // ----- Player Win -----
	}
	else if (Higher_Detail(Player_StandardHand, Dealer_StandardHand) == 1){
		return 1; // ----- Player Lose -----
	}
	else	
		return 2; // ----- DRAW -----	
}

// ----- Standard Hand -----
char* Standard_aPair_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_aPair_7Cards(BigHand) == false)
		return NULL;
	
	char check = 0;
	for (int i = 0; i < 12; i+=2){
		if (*(BigHand + i) == *(BigHand + i + 2)){
			*standardhand = *(BigHand + i);
			*(standardhand + 1) = *(BigHand + i + 1);
			*(standardhand + 2) = *(BigHand + i + 2);
			*(standardhand + 3) = *(BigHand + i + 3);
			check = *(BigHand + i);
			break;
		}
	}
	
	int count = 4;
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i) != check){
			*(standardhand + count) = *(BigHand + i);
			*(standardhand + count + 1) = *(BigHand + i + 1);
			count += 2;
		}
		
		if (count == 10)
			break;
	}
	
	return standardhand;
}

char* Standard_twoPair_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_twoPair_7Cards(BigHand) == false)
		return NULL;
	
	char check_first = 0, check_second = 0;
	for (int i = 0; i < 12; i+=2){
		if (*(BigHand + i) == *(BigHand + i + 2)){
			*standardhand = *(BigHand + i);
			*(standardhand + 1) = *(BigHand + i + 1);
			*(standardhand + 2) = *(BigHand + i + 2);
			*(standardhand + 3) = *(BigHand + i + 3);
			check_first = *(BigHand + i);
			break;
		}
	}
	for (int i = 0; i < 12; i+=2){
		if ((*(BigHand + i) == *(BigHand + i + 2)) && (*(BigHand + i) != check_first)){
			*(standardhand + 4)= *(BigHand + i);
			*(standardhand + 5) = *(BigHand + i + 1);
			*(standardhand + 6) = *(BigHand + i + 2);
			*(standardhand + 7) = *(BigHand + i + 3);
			check_second = *(BigHand + i);
			break;
		}
	}
	
	for (int i = 0; i < 14; i+=2){
		if ((*(BigHand + i) != check_first) && (*(BigHand + i) != check_second)){
			*(standardhand + 8) = *(BigHand + i);
			*(standardhand + 9) = *(BigHand + i + 1);
			break;
		}
	}
	
	return standardhand;
}

char* Standard_ThreeofKind_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_ThreeofKind_7Cards(BigHand) == false)
		return NULL;
	
	char check = 0;
	for (int i = 0; i < 10; i+=2){
		if ((*(BigHand + i) == *(BigHand + i + 2)) && (*(BigHand + i) == *(BigHand + i + 4))){
			*standardhand = *(BigHand + i);
			*(standardhand + 1) = *(BigHand + i + 1);
			*(standardhand + 2) = *(BigHand + i + 2);
			*(standardhand + 3) = *(BigHand + i + 3);
			*(standardhand + 4) = *(BigHand + i + 4);
			*(standardhand + 5) = *(BigHand + i + 5);
			check = *(BigHand + i);
			break;
		}
	}
	
	int count = 6;
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i) != check){
			*(standardhand + count) = *(BigHand + i);
			*(standardhand + count + 1) = *(BigHand + i + 1);
			count += 2;
		}
		
		if (count == 10)
			break;
	}
	
	return standardhand;
}

char* Standard_Straight_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_Straight_7Cards(BigHand) == false)
		return NULL;
	
	
	int sizeof_shortening = CountNotTheSameCards(BigHand);
	int* ConvertBigHand = new int[sizeof_shortening];
	ConvertBigHand = Anti_TheSameCards(BigHand);
	if (ConvertBigHand == NULL)
		return NULL;
	
	if ((*ConvertBigHand == 14) && (*(ConvertBigHand + (sizeof_shortening - 1)) == 2) && (*(ConvertBigHand + (sizeof_shortening - 2)) == 3) && (*(ConvertBigHand + (sizeof_shortening - 3)) == 4) && (*(ConvertBigHand + (sizeof_shortening - 4)) == 5)){
		*(standardhand + 8) = *BigHand;
		*(standardhand + 9) = *(BigHand + 1);
		
		int count_standard = 0, count_convert = 4;
		for (int i = 2; i < 14; i += 2){
			if (*(BigHand + i) == changeIntetoChar(*(ConvertBigHand + (sizeof_shortening - count_convert)))){
				*(standardhand + count_standard) = *(BigHand + i);
				*(standardhand + count_standard + 1) = *(BigHand + i + 1);
				
				count_convert--;
				count_standard+=2;
			}
			
			if (count_standard == 8)
				break;
		}
	} //Special Case: A . . 5 4 3 2
	
	int count_standard = 0, count_convert = 0;
	for (int i = 0; i < sizeof_shortening - 4; i++)
		if ((*(ConvertBigHand + i) == *(ConvertBigHand + i + 1) + 1) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 2) + 2) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 3) + 3) && (*(ConvertBigHand + i) == *(ConvertBigHand + i + 4) + 4)){
			for (int j = 0; j < 14; j+=2){
				if (*(BigHand + j) == changeIntetoChar(*(ConvertBigHand + i + count_convert))){
					*(standardhand + count_standard) = *(BigHand + j);
					*(standardhand + count_standard + 1) = *(BigHand + j + 1);
					count_convert++;
					count_standard += 2;
				}
				
				if (count_standard == 10)
					break;
			}
			
			break;
		} //Normal Case.
	
	delete []ConvertBigHand;
	return standardhand;
}

char* Standard_Flush_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_Flush_7Cards(BigHand) == false)
		return NULL;
	
	char check = WhichSuit(BigHand);
	int count = 0;
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i + 1) == check){
			*(standardhand + count) = *(BigHand + i);
			*(standardhand + count + 1) = *(BigHand + i + 1);
			count += 2;
		}
		
		if (count == 10)
			break;
	}
	
	return standardhand;
}

char* Standard_FullHouse_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_FullHouse_7Cards(BigHand) == false)
		return NULL;
	
	char check = 0;
	for (int i = 0; i < 10; i+=2){
		if ((*(BigHand + i) == *(BigHand + i + 2)) && (*(BigHand + i) == *(BigHand + i + 4))){
			*standardhand = *(BigHand + i);
			*(standardhand + 1) = *(BigHand + i + 1);
			*(standardhand + 2) = *(BigHand + i + 2);
			*(standardhand + 3) = *(BigHand + i + 3);
			*(standardhand + 4) = *(BigHand + i + 4);
			*(standardhand + 5) = *(BigHand + i + 5);
			check = *(BigHand + i);
			break;
		}
	}
	
	for (int i = 0; i < 12; i+=2){
		if ((*(BigHand + i) == *(BigHand + i + 2)) &&(*(BigHand + i) != check)){
			*(standardhand + 6) = *(BigHand + i);
			*(standardhand + 7) = *(BigHand + i + 1);
			*(standardhand + 8) = *(BigHand + i + 2);
			*(standardhand + 9) = *(BigHand + i + 3);
			break;
		}
	}
	
	return standardhand;
}

char* Standard_Quads_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_Quads_7Cards(BigHand) == false)
		return NULL;
	
	char check = 0;
	for (int i = 0; i < 8; i+=2){
		if ((*(BigHand + i) == *(BigHand + i + 2)) && (*(BigHand + i) == *(BigHand + i + 4)) && (*(BigHand + i) == *(BigHand + i + 6))){
			*standardhand = *(BigHand + i);
			*(standardhand + 1) = *(BigHand + i + 1);
			*(standardhand + 2) = *(BigHand + i + 2);
			*(standardhand + 3) = *(BigHand + i + 3);
			*(standardhand + 4) = *(BigHand + i + 4);
			*(standardhand + 5) = *(BigHand + i + 5);
			*(standardhand + 6) = *(BigHand + i + 6);
			*(standardhand + 7) = *(BigHand + i + 7);
			check = *(BigHand + i);
			break;
		}
	}
	
	for (int i = 0; i < 14; i+=2){
		if (*(BigHand + i) != check){
			*(standardhand + 8) = *(BigHand + i);
			*(standardhand + 9) = *(BigHand + i + 1);
			break;
		}
	}
	
	return standardhand;
}

char* Standard_StraightFlush_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_StraightFlush_7Cards(BigHand) == false)
		return NULL;
	
	int sizeof_flushcards = CountFlushCards(BigHand);
		
	int* combine_flushcards = new int[sizeof_flushcards];
	combine_flushcards = Combine_FlushCards(BigHand);
	
	if (combine_flushcards == NULL)
		return NULL;
	
	char suit = WhichSuit(BigHand);
	
	if ((*combine_flushcards == 14) && (*(combine_flushcards + (sizeof_flushcards - 1)) == 2) && (*(combine_flushcards + (sizeof_flushcards - 2)) == 3) && (*(combine_flushcards + (sizeof_flushcards - 3)) == 4) && (*(combine_flushcards + (sizeof_flushcards - 4)) == 5)){
		*standardhand = '5';
		*(standardhand + 1) = suit;
		*(standardhand + 2) = '4';
		*(standardhand + 3) = suit;
		*(standardhand + 4) = '3';
		*(standardhand + 5) = suit;
		*(standardhand + 6) = '2';
		*(standardhand + 7) = suit;
		*(standardhand + 8) = 'A';
		*(standardhand + 9) = suit;
	} //Special Case: A . . 5 4 3 2
	
	for (int i = 0; i < sizeof_flushcards - 4; i++)
		if ((*(combine_flushcards + i) == *(combine_flushcards + i + 1) + 1) && (*(combine_flushcards + i) == *(combine_flushcards + i + 2) + 2) && (*(combine_flushcards + i) == *(combine_flushcards + i + 3) + 3) && (*(combine_flushcards + i) == *(combine_flushcards + i + 4) + 4)){
			*standardhand = changeIntetoChar(*(combine_flushcards + i));
			*(standardhand + 1) = suit;
			*(standardhand + 2) = changeIntetoChar(*(combine_flushcards + i + 1));
			*(standardhand + 3) = suit;
			*(standardhand + 4) = changeIntetoChar(*(combine_flushcards + i + 2));
			*(standardhand + 5) = suit;
			*(standardhand + 6) = changeIntetoChar(*(combine_flushcards + i + 3));
			*(standardhand + 7) = suit;
			*(standardhand + 8) = changeIntetoChar(*(combine_flushcards + i + 4));
			*(standardhand + 9) = suit;
			break;
		} //Normal Case.
	delete []combine_flushcards;	
	
	return standardhand;
}

char* Standard_RoyalStraightFlush_Hand(char* BigHand)
{
	char* standardhand = new char[10];
	if (standardhand == NULL || Check_RoyalStraightFlush_7Cards(BigHand) == false)
		return NULL;
	
	int sizeof_flushcards = CountFlushCards(BigHand);
		
	int* combine_flushcards = new int[sizeof_flushcards];
	combine_flushcards = Combine_FlushCards(BigHand);
	
	if (combine_flushcards == NULL)
		return NULL;
	
	char suit = WhichSuit(BigHand);
	
	if ((*combine_flushcards == 14) && (*(combine_flushcards + 1) == 13) && (*(combine_flushcards + 2) == 12) && (*(combine_flushcards + 3) == 11) && (*(combine_flushcards + 4) == 10)){
		*standardhand = 'A';
		*(standardhand + 1) = suit;
		*(standardhand + 2) = 'K';
		*(standardhand + 3) = suit;
		*(standardhand + 4) = 'Q';
		*(standardhand + 5) = suit;
		*(standardhand + 6) = 'J';
		*(standardhand + 7) = suit;
		*(standardhand + 8) = 'T';
		*(standardhand + 9) = suit;
	} //Standard hand has {A} [K] [Q] [J] (T) which are the same suit.
	
	delete []combine_flushcards;	
	
	return standardhand;
}
