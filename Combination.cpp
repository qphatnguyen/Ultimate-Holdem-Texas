#include "PokerHT.h"

Record rec[5];

void displayMenu(bool &stopped_con)
{
	while(true){
		hidecursorscr();
		// ----- Draw box menu -----
		textcolor(244);
		for (int i = 0; i < HEIGHT; i++){
			gotoXY(2, 2 + i);
			cout << BoxMenu[i] << endl;
		}
		textcolor(BEIGE);
		
		// ----- Draw logo -----
		gotoXY(7, 3);
		textcolor(224);
		cout << "ULTIMATE POKER HOLDEM TEXAS";
		textcolor(BEIGE);
		
		for(int i = 0; i < 7; i += 6){
			textcolor(240);
			gotoXY(5, 7 + i);
			cout << "\x05";
			gotoXY(35, 7 + i);
			cout << "\x05";
			textcolor(BEIGE);
		}
		
		gotoXY(12, 17);
		textcolor(224);
		cout << "MADE BY FARK VLAD\n";
		textcolor(BEIGE);
		
		textcolor(112);
		for (int i = 0; i < HEIGHT - 3; i++){
			gotoXY(10, 4 + i);
			cout << AceOfSpade_Logo[i] << endl;
		}
		textcolor(BEIGE);
		
		gotoXY(39, 5);
		textcolor(162);
		cout << "  Press [F1] to START  ";
		textcolor(BEIGE);
		
		gotoXY(39, 9);
		textcolor(230);
		cout << "  Press [F2]: RECORD   ";
		textcolor(BEIGE);
		
		gotoXY(39, 13);
		textcolor(196);
		cout << " Press [ESC]: QUIT GAME";
		textcolor(BEIGE);
		
		gotoXY(61, 17);
		textcolor(247);
		cout << "[F3]?";
		textcolor(BEIGE);
		
		// ----- Handling -----
		bool boolean = true;
		while(boolean){
			if (kbhit()){
				char key = getch();
				if (key == CHECK_F){
					key = getch();
					if (key == F1){ //Play game
						return;
					}
					else if (key == F2){ //Read record history
						system("cls");
						displayRecordTable();
						printRecordInfo(rec);
						gotoXY(28, 11);
						cout << "Press [ESC] to BACK";
						
						while(true){
							if (kbhit()){
								key = getch();
								if (key == ESC){
									system("cls");
									boolean = false;
									break;
								}
							}
						}
					}
					else if (key == F3){ //Read rules
						system("cls");
						
						int i = 0;
						ifstream ifs;
						ifs.open("Rules.txt");
						if (ifs.is_open()){
							string temp = "";
							while(!ifs.eof()){
								getline(ifs, temp);
								gotoXY(2, 2 + i++);
								cout << temp << endl;
							}
							ifs.close();
						}
	
						while(true){
							if (kbhit()){
								key = getch();
								if (key == ESC){
									system("cls");
									boolean = false;
									break;
								}
							}
						}
					}
				}
				else if (key == ESC){ //Quit game
					stopped_con = true;
					return;
				}
			}
		}
	}
	
}

void playGame()
{
	getRecordInfo(rec);
	
	// ----- init variables -----
	PHT_twoCards* player_hand = new PHT_twoCards;
	PHT_twoCards* dealer_hand = new PHT_twoCards;
	PHT_threeCards* flop = new PHT_threeCards;
	PHT_twoCards* river = new PHT_twoCards;
	
	int theSameCard[8];
	
	bool boolean = true;
	srand(time(NULL));
	int chips = buyChips(rand() % 9 + 1);
	int level = 1, countdown = 3, target = (chips * 110) / 100;
	int round = 0;
	
	// ----- working -----
	hidecursorscr();
	while(boolean){
		++round;
		
		Player_Hand(player_hand, theSameCard);
		Dealer_Hand(dealer_hand, theSameCard);
		Flop(flop, theSameCard);
		River(river, theSameCard);
		
		backspace_insideboxGame(); //----- Backspace technique -----
		drawboxGame();
		NameOfTheboxGame();
		backspace_insideboxInfo(); //----- Backspace technique -----
		drawboxInfo();
		NameOfTheboxInfo();
		backspace_insideboxBet(); //----- Backspace technique -----
		drawboxBet();
		NameOfTheboxBet();
		
		// ----- Challenge -----
		DisplayStateOfTarget(target, countdown, level);
		
		//Chips
		ShowChips(chips);
		
		//----- ANTE -----
		ShowAnte();
		int chipsAnte = 0, chipsPlay = 0;
		int checkAnte = 0, checkResult = 2; //DRAW
		ShowChipsBetAnte(chipsAnte);
		RemindAnte();
		while (true){ 
			if (chips <= 5){
				goto decision;
			}
			if (kbhit()){
				char key = getch();
				if (key == CHECKCONTROL){
					key = getch();
					if (key == UP){
						//Calculate chips
						int chipsFake = chips;
						
						chipsAnte = IncreaseAnte(chipsAnte, chips);
						chipsFake = chipsFake - chipsAnte;
						
						ShowChipsBetAnte(chipsAnte);
						ShowChips(chipsFake);
						
						while (true){
							int chipsAnte_old = chipsAnte;
							key = getch();
							if (key == CHECKCONTROL){
								key = getch();
								if (key == UP){
									//Calculate chips
									chipsAnte = IncreaseAnte(chipsAnte, chips);
									chipsFake += chipsAnte_old - chipsAnte;
									
									ShowChipsBetAnte(chipsAnte);
									ShowChips(chipsFake);
								}
								else if (key == DOWN){
									if (chipsAnte != 0){
										chipsAnte = DecreaseAnte(chipsAnte);
										chipsFake += chipsAnte_old - chipsAnte;
										
										ShowChipsBetAnte(chipsAnte);
										ShowChips(chipsFake);
									}
								}
								else if (key == LEFT){
									chips = chipsFake;
									break;
								}
								else if (key == RIGHT){
									chipsAnte = 0;
									ShowChipsBetAnte(chipsAnte);
									ShowChips(chips);
									goto decision;
								}
							}
						}
						
						break;
					}
					else if (key == RIGHT){
						chipsAnte = 0;
						ShowChipsBetAnte(chipsAnte);

						goto decision;
					}
				}
			}
		}
		gotoXY(12, 4);
		ShowDealer_Hand_FaceDown();
		gotoXY(21, 6);
		FirstBet();
		gotoXY(16, 16);
		ShowPlayer_Hand(player_hand);
		
		//----- Before FLOP -----
		ShowPlay();
		ShowChipsBetPlay(chipsPlay);
		Remind_BeforeFlop();
		while(true){
			if (kbhit()){
				char key = getch();
				if (key == CHECKCONTROL){
					key = getch();
					if (key == UP){ //Show all - Bet PLAY x3 or x4
						//Calculate chips
						int chipsFake = chips;
						
						chipsPlay = IncreasePlay_BeforeFlop(chipsPlay, chipsAnte, chips);
						chipsFake -= chipsPlay;
						
						ShowChipsBetPlay(chipsPlay);
						ShowChips(chipsFake);
						while(true){
							key = getch();
							if (key == CHECKCONTROL){
								int chipsPlay_old = chipsPlay;
								key = getch();
								if (key == UP){
									//Calculate chips
									chipsPlay = IncreasePlay_BeforeFlop(chipsPlay, chipsAnte, chips);
									chipsFake += chipsPlay_old - chipsPlay;
									
									ShowChipsBetPlay(chipsPlay);
									ShowChips(chipsFake);
								}
								else if (key == DOWN){
									chipsPlay = DecreasePlay_BeforeFlop(chipsPlay, chipsAnte);
									chipsFake += chipsPlay_old - chipsPlay;
									
									ShowChipsBetPlay(chipsPlay);
									ShowChips(chipsFake);
								}
								else if (key == LEFT){
									gotoXY(17, 6);
									ShowAll(flop, river);
									
									gotoXY(12, 4);
									ShowDealer_Hand_FaceUp(dealer_hand);
									sleep(1);
									gotoXY(4, 7);
									ComparedHands(player_hand, dealer_hand, flop, river, checkAnte, checkResult);
									AnnoncePlusAnte(checkResult, checkAnte);
									
									chips = chipsFake;
									goto decision;
								}
							}
						}
					}
					else if (key == RIGHT){ //Show flop
						gotoXY(4, 6);
						cout << "                                     "; //---- Backspace technique -----
						gotoXY(17, 6);
						ShowFlop(flop);
						
						break;
					}
				}
			}
		}
		
		//----- After FLOP -----
		Remind_AfterFlop();		
		while(true){
			if (kbhit()){
				char key = getch();
				if (key == CHECKCONTROL){
					key = getch();
					if (key == UP){ //Show all - Bet PLAY x2
						//Calculate chips
						if (chipsAnte * 2 < chips){
							chipsPlay = chipsAnte * 2;
							chips -= chipsPlay;
						}
						else{
							chipsPlay = chips;
							chips -= chipsPlay;
						}
						
						ShowChipsBetPlay(chipsPlay);
						ShowChips(chips);
						
						gotoXY(17, 6);
						ShowAll(flop, river);
						
						gotoXY(12, 4);
						ShowDealer_Hand_FaceUp(dealer_hand);
						sleep(1);
						gotoXY(4, 7);
						ComparedHands(player_hand, dealer_hand, flop, river, checkAnte, checkResult);
						AnnoncePlusAnte(checkResult, checkAnte);
						
						goto decision;
					}
					else if (key == RIGHT){ //Show RIVER
						gotoXY(17, 6);
						ShowAll(flop, river);
						
						break;
					}
				}
			}
		}
		
		//After RIVER
		Remind_AfterRiver();
		while (true){
			if (kbhit()){
				char key = getch();
				if (key == CHECKCONTROL){
					key = getch();
					if (key == UP){ //Bet PLAY x1
						//Calculate chips
						if (chipsAnte < chips){
							chipsPlay = chipsAnte;
							chips -= chipsPlay;
						}
						else{
							chipsPlay = chips;
							chips -= chipsPlay;
						}
						
						ShowChipsBetPlay(chipsPlay);
						ShowChips(chips);
						
						gotoXY(12, 4);
						ShowDealer_Hand_FaceUp(dealer_hand);
						sleep(1);
						gotoXY(4, 7);
						ComparedHands(player_hand, dealer_hand, flop, river, checkAnte, checkResult);
						AnnoncePlusAnte(checkResult, checkAnte);
						
						goto decision;
					}
					else if (key == RIGHT){ //FOLD
						gotoXY(12, 4);
						ShowDealer_Hand_FaceUp(dealer_hand);
						sleep(1);
						gotoXY(4, 7);
						ComparedHands(player_hand, dealer_hand, flop, river, checkAnte, checkResult);
						
						break;
					}
				}
			}
		}
	
		//DECISION
		decision:	
		chips += EarnChipsPlay(checkResult, chipsPlay) + EarnChipsAnte(checkResult, checkAnte, chipsPlay, chipsAnte);
		
		ResetTheChallenge(chips, target, countdown, level); // ----- Challenge -----
		
		if (chips <= 5){ //----- Out of chip -----
			gotoXY(17, 17);
			textcolor(11);
			cout << "You are not enough chip!";
			textcolor(7);
			sleep(5);
			break;
		}
		
		if (chipsAnte != 0){
			ShowChipsBetAnte(0);
			ShowChipsBetPlay(0);
			sleep(1);	
			ShowChips(chips);
		} 
		
		// ----- Get new record info -----
		time_t now = time(0);
		string temp_time = ctime(&now);
		getNewRecordInfo(rec, round, chips, temp_time);
		saveRecordInfo(rec);
		
		// ----- keep going or exit -----
		gotoXY(4, 17);
		textcolor(11);
		cout << "Do you wanna continue? (Esc: quit|Space: continue)";
		while (true){
			if (kbhit()){
				char key = getch();
				if (key == SPACE){
					break;
				}
				else if (key == ESC){
					boolean = false;
					break;
				}
			}
		}
		textcolor(7);
	}
	system("cls");
	
	// ----- Result -----
	displayRecordTable();
	printRecordInfo(rec);
	
	// ----- free data -----
	delete player_hand;
	delete dealer_hand;
	delete flop;
	delete river;
}
