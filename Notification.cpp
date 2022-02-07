#include "PokerHT.h"
// ----- Hand -----
void ShowPlayer_Hand(PHT_twoCards* hand)
{
	cout << "Your hand: ";
	DisplayCard(hand->c1, hand->s1);
	DisplayCard(hand->c2, hand->s2);
	cout << endl;
}

void ShowDealer_Hand_FaceUp(PHT_twoCards* hand)
{
	sleep(1);
	cout << "Dealer's hand: ";
	DisplayCard(hand->c1, hand->s1);
	DisplayCard(hand->c2, hand->s2);
	cout << endl;
}

void ShowDealer_Hand_FaceDown()
{
	cout << "Dealer's hand:  \xdb\xb2   \xdb\xb2 ";
}

void ShowFlop(PHT_threeCards* hand)
{
	DisplayCard(hand->c1, hand->s1);
	DisplayCard(hand->c2, hand->s2);
	DisplayCard(hand->c3, hand->s3);
}

void ShowAll(PHT_threeCards* hand1, PHT_twoCards* hand2)
{
	DisplayCard(hand1->c1, hand1->s1);
	DisplayCard(hand1->c2, hand1->s2);
	DisplayCard(hand1->c3, hand1->s3);
	DisplayCard(hand2->c1, hand2->s1);
	DisplayCard(hand2->c2, hand2->s2);
}

void ShowPlayer_StandardHand(char* Player_StandardHand)
{
	cout << "Player's standard hand: ";
	for (int i = 0; i < 10; i+=2)
		DisplayCard(*(Player_StandardHand + i), *(Player_StandardHand + i + 1));
}

void ShowDealer_StandardHand(char* Dealer_StandardHand)
{
	cout << "Dealer's standard hand: ";
	for (int i = 0; i < 10; i+=2)
		DisplayCard(*(Dealer_StandardHand + i), *(Dealer_StandardHand + i + 1));
} 

void DisplayCard(char card, char suit)
{
	if (suit == '\x03'){
		textcolor(4);
	}
	else if (suit == '\x04'){
		textcolor(12);
	}
	else if (suit == '\x05'){
		textcolor(2);
	}
	else if (suit == '\x06'){
		textcolor(10);
	}
	
	if (card == 'A'){
		cout << "{" << card << suit << "} ";
	}
	else if (card == 'K' || card == 'Q' || card == 'J'){
		cout << "[" << card << suit << "] ";
	}
	else{
		cout << "(" << card << suit << ") ";
	}
	textcolor(7);
}

// ----- Bet -----
void ShowAnte()
{
	gotoXY(58, 13);
	cout << "ANTE:";
}

void RemindAnte()
{
	gotoXY(58, 14);
	textcolor(10);
	cout << "\x18:BET";
	
	gotoXY(58, 15);
	textcolor(14);
	cout << "\x19:REBET";
	
	gotoXY(58, 16);
	textcolor(13);
	cout << "<-:CHOOSE";
	
	gotoXY(58, 17);
	textcolor(12);
	cout << "\x1a:DON'T PLAY";
	
	textcolor(7);
}

void ShowChipsBetAnte(int chip)
{
	gotoXY(63, 13);
	cout << "       "; //----- Backspace technique -----
	gotoXY(64, 13);
	cout << chip << "\x9c";
}

void AnnoncePlusAnte(int checkResult, int checkAnte)
{
	if (checkResult == 0){ //Player win!
		if (checkAnte == 10){ //Royal Straight Flush
			gotoXY(35, 11);
			textcolor(15);
			cout << "+[ANTE x 100]";
		}
		else if (checkAnte == 9){ //Straight Flush
			gotoXY(35, 11);
			textcolor(1);
			cout << "+[ANTE x 50]";
		}
		else if (checkAnte == 8){ //Quads
			gotoXY(35, 11);
			textcolor(2);
			cout << "+[ANTE x 30]";
		}
		else if (checkAnte == 7){ //Full House
			gotoXY(35, 11);
			textcolor(5);
			cout << "+[ANTE x 10]";
		}
		else if (checkAnte == 6){ //Flush
			gotoXY(35, 11);
			textcolor(6);
			cout << "+[ANTE x 5]";
		}
		else if (checkAnte == 5){ //Straight
			gotoXY(35, 11);
			textcolor(8);
			cout << "+[ANTE x 4]";
		}
		else if (checkAnte == 4){ //Three Of Kind
			gotoXY(35, 11);
			textcolor(9);
			cout << "+[ANTE x 2]";
		}
	}
}

void ShowPlay()
{
	gotoXY(58, 16);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 16);
	cout << "PLAY:";
}

void ShowChipsBetPlay(int chip)
{
	gotoXY(63, 16);
	cout << "       "; //----- Backspace technique -----
	gotoXY(64, 16);
	cout << chip << "\x9d";
}

void FirstBet()
{
	textcolor(9); //Red
	cout << "$\x9c\x9d";
	textcolor(7); //White
	cout << "BEFORE FLOP";
	textcolor(12); //Blue
	cout << "\x9d\x9c$";
	textcolor(7); //White
}

void Remind_BeforeFlop()
{
	gotoXY(58, 14);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 14);
	textcolor(10);
	cout << "\x17: x3 or x4";
	
	gotoXY(58, 15);
	textcolor(13);
	cout << "<-:CHOOSE   ";
	
	gotoXY(58, 17);
	cout << "           "; //----- Backspace technique -----
	gotoXY(62, 17);
	textcolor(11);
	cout << "\x1a: CHECK";
	
	textcolor(7);
}

void Remind_AfterFlop()
{
	gotoXY(58, 14);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 15);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 15);
	textcolor(10);
	cout << "\x18: x2";
	
	gotoXY(58, 17);
	cout << "           "; //----- Backspace technique -----
	gotoXY(62, 17);
	textcolor(11);
	cout << "\x1a: CHECK";
	
	textcolor(7);
}

void Remind_AfterRiver()
{
	gotoXY(58, 14);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 15);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 15);
	textcolor(10);
	cout << "\x18: x1";
	
	gotoXY(58, 17);
	cout << "           "; //----- Backspace technique -----
	gotoXY(62, 17);
	textcolor(11);
	cout << "\x1a: FOLD ";
	
	textcolor(7);
}

void ShowChips(int chip)
{
	gotoXY(58, 4);
	cout << "           "; //----- Backspace technique -----
	gotoXY(58, 4);
	cout << "CHIP: " << chip << "$";
}

// ----- Result -----
void ShowHigher(char* bighand, int key)
{
	cout << "---> ";
	
	if (Check_RoyalStraightFlush_7Cards(bighand)){
		if (key == 2){
			textcolor(15);
			cout << "\xf2RoYaL StRaIgHt FlUsH\xf3";
		}
		else{
			for (int i = 1; i <= 15; i++){
				gotoXY(9, 13);
				textcolor(i);
				cout << "\xf2RoYaL StRaIgHt FlUsH\xf3";
				Sleep(50);
			}
		}
	}
	else if (Check_StraightFlush_7Cards(bighand)){
		textcolor(1);
		cout << "{STRAIGHT FLUSH}";
	}
	else if (Check_Quads_7Cards(bighand)){
		textcolor(2);
		cout << "[QUADS]";
	}
	else if (Check_FullHouse_7Cards(bighand)){
		textcolor(5);
		cout << "(FULL HOUSE)";
	}
	else if (Check_Flush_7Cards(bighand)){
		textcolor(6);
		cout << "<FLUSH>";
	}
	else if (Check_Straight_7Cards(bighand)){
		textcolor(8);
		cout << "|STRAIGHT|";
	}
	else if (Check_ThreeofKind_7Cards(bighand)){
		textcolor(9);
		cout << "=THREE OF KIND=";
	}
	else if (Check_twoPair_7Cards(bighand)){
		textcolor(10);
		cout << "/TWO PAIR/";
	}
	else if (Check_aPair_7Cards(bighand)){
		textcolor(11);
		cout << "\\PAIR\\";
	}
	else 
		cout << "-HIGHER-";
	textcolor(7);
	cout << endl;
}

// ----- challenge -----
void DisplayStateOfTarget(int target, int countdown, int level)
{
	gotoXY(58, 7);
	if (level % 10 == 0){
		textcolor(LIGHT_RED);
		cout << "[LEVEL H]";
		textcolor(BEIGE);
	}
	else if (level % 10 == 5){
		textcolor(LIGHT_YELLOW);
		cout << "[LEVEL M]";
		textcolor(BEIGE);
	}
	else{
		textcolor(GREEN);
		cout << "[LEVEL E]";
		textcolor(BEIGE);
	}
	
	gotoXY(58, 8);
	cout << "           ";
	gotoXY(58, 8);
	
	if (level % 10 == 0){
		switch(countdown){
			case 10:
			{
				textcolor(DARK_GREEN);
				cout << "\xdb\xdb";
				break;
			}
			case 9:
			{
				textcolor(GREEN);
				cout << "\xdb\xdb\xdb";
				break;
			}
			case 8:
			{
				textcolor(BLUE);
				cout << "\xdb\xdb\xdb\xdb";
				break;
			}
			case 7:
			{
				textcolor(DARK_BLUE);
				cout << "\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 6:
			{
				textcolor(BLEU);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 5:
			{
				textcolor(DARK_BLEU);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 4:
			{
				textcolor(LIGHT_YELLOW);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 3:
			{
				textcolor(DARK_YELLOW);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 2:
			{
				textcolor(LIGHT_RED);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 1:
			{
				textcolor(DARK_RED);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
		}
	}
	else if (level % 10 == 5){
		switch(countdown){
			case 5:
			{
				textcolor(DARK_GREEN);
				cout << "\xdb\xdb\xdb";
				break;
			}
			case 4:
			{
				textcolor(GREEN);
				cout << "\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 3:
			{
				textcolor(DARK_YELLOW);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 2:
			{
				textcolor(LIGHT_RED);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 1:
			{
				textcolor(DARK_RED);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
		}
	}
	else{
		switch(countdown){
			case 3:
			{
				textcolor(DARK_GREEN);
				cout << "\xdb\xdb\xdb\xdb";
				break;
			}
			case 2:
			{
				textcolor(DARK_YELLOW);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
			case 1:
			{
				textcolor(DARK_RED);
				cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
				break;
			}
		}
	}
	
	gotoXY(58, 9);
	cout << "TARGET:";
	gotoXY(63, 10);
	cout << target << "$";
	
	textcolor(BEIGE);
}
