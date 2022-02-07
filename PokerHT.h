#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <Windows.h>
#include <conio.h> //use the function "kbhit()" to use a keyboard.
#include <cstdlib> //use the function "rand()"
#include <unistd.h> //use the function "sleep()"

// ----- Menu -----
#define WIDTH 66
#define HEIGHT 17

#define CHECK_F 0
#define F1      59
#define F2      60
#define F3      61

// ----- Control -----
#define CHECKCONTROL -32
#define UP     72
#define DOWN   80
#define LEFT   75
#define RIGHT  77
// ----- Quit -----
#define ESC 27
// ----- Continue -----
#define SPACE 32

// ----- Colors -----
#define BLACK        0 //16 - 31 -> dark blue background
#define DARK_BLUE    1 //32 - 47 -> dark green background
#define DARK_GREEN   2 //48 - 63 -> dark bleu background
#define DARK_BLEU    3 //64 - 79 -> dark red background
#define DARK_RED     4 //80 - 95 -> dark violet background
#define DARK_VIOLET  5 //96 - 111 -> dark yellow background
#define DARK_YELLOW  6 //112 - 127 -> beige background
#define BEIGE        7 //128 - 143 -> gray background
#define GRAY         8 //144 - 159 -> blue background
#define BLUE         9 //160 - 175 -> green background
#define GREEN        10 //176 - 191 -> bleu background
#define BLEU         11 //192 - 207 -> light red background
#define LIGHT_RED    12 //208 - 223 -> light violet background
#define LIGHT_VIOLET 13 //224 - 239 -> light yellow background
#define LIGHT_YELLOW 14 //240 - 255 -> white background
#define WHITE        15 

using namespace std;
		    
struct PHT_twoCards{
	char c1, c2;
	char s1, s2;
};

struct PHT_threeCards{
	char c1, c2, c3;
	char s1, s2, s3;
};

struct Record
{
	int round, token;
	string time;
};

// ----- Combination -----
void displayMenu(bool &stopped_con);
void playGame();

// ----- Notification -----
void ShowPlayer_Hand(PHT_twoCards* hand);
void ShowDealer_Hand_FaceDown();
void ShowDealer_Hand_FaceUp(PHT_twoCards* hand);
void ShowFlop(PHT_threeCards* hand);
void ShowAll(PHT_threeCards* hand1, PHT_twoCards* hand2);
void ShowPlayer_StandardHand(char* Player_StandardHand);
void ShowDealer_StandardHand(char* Player_StandardHand);
void DisplayCard(char card, char suit);

void ShowAnte();
void RemindAnte();
void ShowChipsBetAnte(int chip);
void AnnoncePlusAnte(int checkResult, int checkAnte);

void ShowPlay();
void ShowChipsBetPlay(int chip);
void FirstBet();
void Remind_BeforeFlop();
void Remind_AfterFlop();
void Remind_AfterRiver();

void ShowChips(int chip);

void ShowHigher(char* bighand, int key);

void DisplayStateOfTarget(int target, int countdown, int level);
// ----- dealing -----
char Take_Card(int Number);
char Take_Suit(int Number);

void Player_Hand(PHT_twoCards* &hand, int theSameCard[]);
void Dealer_Hand(PHT_twoCards* &hand, int theSameCard[]);
void Flop(PHT_threeCards* &hand, int theSameCard[]);
void River(PHT_twoCards* &hand, int theSameCard[]);

// ----- comparison -----
int changeChartoInte(char card);
char changeIntetoChar(int card);

char* Sort_BigHand(PHT_twoCards* hand, PHT_threeCards* flop, PHT_twoCards* river);
char* Sort_StandardHand(char* BigHand);

void ComparedHands(PHT_twoCards* player, PHT_twoCards* dealer, PHT_threeCards* flop, PHT_twoCards* river, int &checkAnte, int &checkResult);

bool Check_aPair_7Cards(char* BigHand);
bool Check_twoPair_7Cards(char* BigHand);
bool Check_ThreeofKind_7Cards(char* BigHand);
bool Check_Straight_7Cards(char* BigHand); int CountNotTheSameCards(char* BigHand); int* Anti_TheSameCards(char* BigHand);
bool Check_Flush_7Cards(char* BigHand); char WhichSuit(char* BigHand); int CountFlushCards(char* BigHand);
bool Check_FullHouse_7Cards(char* BigHand);
bool Check_Quads_7Cards(char* BigHand);
bool Check_StraightFlush_7Cards(char* BigHand); int* Combine_FlushCards(char* BigHand);
bool Check_RoyalStraightFlush_7Cards(char* BigHand);

int Higher_QuickTest(char* BigHand);
int Higher_Detail(char* Player_StandardHand, char* Dealer_StandardHand);
int Higher_Comparison(char* Player_BigHand, char* Dealer_BigHand, char* Player_StandardHand, char* Dealer_StandardHand);

char* Standard_aPair_Hand(char* BigHand);
char* Standard_twoPair_Hand(char* BigHand);
char* Standard_ThreeofKind_Hand(char* BigHand);
char* Standard_Straight_Hand(char* BigHand);
char* Standard_Flush_Hand(char* BigHand);
char* Standard_FullHouse_Hand(char* BigHand);
char* Standard_Quads_Hand(char* BigHand);
char* Standard_StraightFlush_Hand(char* BigHand);
char* Standard_RoyalStraightFlush_Hand(char* BigHand);

// ----- chip -----
int IncreaseAnte(int chip, int Chips);
int DecreaseAnte(int chip);

int IncreasePlay_BeforeFlop(int chipsPlay, int chipsAnte, int Chips);
int DecreasePlay_BeforeFlop(int chipsPlay, int chipsAnte);

int EarnChipsAnte(int checkResult, int checkAnte, int chipsPlay, int chip);
int EarnChipsPlay(int checkResult, int chip);

int buyChips(int number);

// ----- setting -----
void gotoXY(int x, int y);
void hidecursorscr();
void textcolor(int x);

// ----- screen -----
extern char BoxMenu[HEIGHT][WIDTH];
extern char AceOfSpade_Logo[HEIGHT-3][WIDTH-2];

extern char RecordTable[HEIGHT-8][WIDTH-19]; // height = 9, witdth = 46 + 1

void NameOfTheboxGame();
void NameOfTheboxInfo();
void NameOfTheboxBet();

void backspace_insideboxGame();
void drawboxGame();
void backspace_insideboxInfo();
void drawboxInfo();
void backspace_insideboxBet();
void drawboxBet();

// ----- challenge -----
void ResetTheChallenge(int &Chip, int &target, int &countdown, int &level);
bool CompleteTheChallenge(int Chip, int target);

// ----- Record -----
void displayRecordTable();
void printRecordInfo(Record rec[]);
void getRecordInfo(Record rec[]);
void getNewRecordInfo(Record rec[], int Round, int chips, string Time);
void saveRecordInfo(Record rec[]);
