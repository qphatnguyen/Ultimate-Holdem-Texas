#include "PokerHT.h"

void ResetTheChallenge(int &Chip, int &target, int &countdown, int &level)
{
	if (CompleteTheChallenge(Chip, target)){ //----- Reward -----
		gotoXY(58, 11);
		textcolor(GREEN);
		cout << "+++++S+++++";
		textcolor(BEIGE);
		
		if (level % 10 == 0){
			Chip = (Chip * 150) / 100; //Take 80% chips
		}
		else if (level % 10 == 5){ //Take half chips
			Chip = (Chip * 130) / 100;
		}
		else{ //Take 20% chips
			Chip = (Chip * 110) / 100;
		}
	
		++level;
		
		if (level % 10 == 0){
			countdown = 10;
			target = Chip * 2;
		}
		else if (level % 10 == 5){
			countdown = 5;
			target = (Chip * 150) / 100;
		}
		else{
			countdown = 3;
			target = (Chip * 110) / 100;
		}
	}
	else if (countdown == 1){ //----- Punishment -----
		gotoXY(58, 11);
		textcolor(DARK_RED);
		cout << "-----F-----";
		textcolor(BEIGE);
	
		if (level % 10 == 0){
			Chip = (Chip * 20) / 100; //Take 80% chips
		}
		else if (level % 10 == 5){ //Take half chips
			Chip = Chip / 2;
		}
		else{ //Take 20% chips
			Chip = (Chip * 80) / 100;
		}
	
		++level;
		
		if (level % 10 == 0){
			countdown = 10;
			target = Chip * 2;
		}
		else if (level % 10 == 5){
			countdown = 5;
			target = (Chip * 150) / 100;
		}
		else{
			countdown = 3;
			target = (Chip * 110) / 100;
		}
	}
	else{
		--countdown;
	}
}

bool CompleteTheChallenge(int Chip, int target)
{
	if (Chip >= target)
		return true;
		
	return false;
}
