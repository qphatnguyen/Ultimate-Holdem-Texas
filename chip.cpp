#include "PokerHT.h"

// ----- Ante -----
int IncreaseAnte(int chip, int Chips)
{
	/*
	if (chip < Chips && Chips > 5){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
		else if (chip == 50)
			return 100;
	}
	*/
	
	if (5 < Chips && Chips <= 10){
		if (chip == 0)
			return 5;
	}
	else if (Chips <= 25){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
	}
	else if (Chips <= 50){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
	}
	else if (Chips <= 100){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
	}
	else if (Chips <= 200){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
		else if (chip == 50)
			return 100;
	}
	else if (Chips <= 500){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
		else if (chip == 50)
			return 100;
		else if (chip == 100)
			return 200;
	}
	else if (Chips <= 1000){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
		else if (chip == 50)
			return 100;
		else if (chip == 100)
			return 200;
		else if (chip == 200)
			return 500;
	}
	else if (Chips <= 2000){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
		else if (chip == 50)
			return 100;
		else if (chip == 100)
			return 200;
		else if (chip == 200)
			return 500;
		else if (chip == 500)
			return 1000;
	}
	else if (Chips > 2000){
		if (chip == 0)
			return 5;
		else if (chip == 5)
			return 10;
		else if (chip == 10)
			return 25;
		else if (chip == 25)
			return 50;
		else if (chip == 50)
			return 100;
		else if (chip == 100)
			return 200;
		else if (chip == 200)
			return 500;
		else if (chip == 500)
			return 1000;
		else if (chip == 1000)
			return 2000;
	}
		
	return chip;
}

int DecreaseAnte(int chip)
{
	if (chip == 10)
		return 5;
	else if (chip == 25)
		return 10;
	else if (chip == 50)
		return 25;
	else if (chip == 100)
		return 50;
	else if (chip == 200)
		return 100;
	else if (chip == 500)
		return 200;
	else if (chip == 1000)
		return 500;
	else if (chip == 2000)
		return 1000;
		
	return chip;
}

// ----- Play -----
int IncreasePlay_BeforeFlop(int chipsPlay, int chipsAnte, int Chips)
{
	if (chipsAnte * 3 <= Chips){
		if (chipsPlay == 0)
			return 3 * chipsAnte;
		else if (chipsPlay == chipsAnte * 3 && chipsAnte * 4 <= Chips)
			return 4 * chipsAnte;
		else
			chipsPlay = Chips;
	}
	else{
		chipsPlay = Chips;
	}
		
	return chipsPlay;
}

int DecreasePlay_BeforeFlop(int chipsPlay, int chipsAnte)
{
	if (chipsAnte * 3 < chipsPlay && chipsPlay <= chipsAnte * 4)
		return 3 * chipsAnte;
	
	return chipsPlay;
}

// ----- Earn chips -----
int EarnChipsAnte(int checkResult, int checkAnte, int chipsPlay, int chip)
{
	if (chipsPlay != 0){
		if (checkResult == 0){
			if (checkAnte == 10){ //Royal straight flush
				return chip * (100 + 1);
			}
			else if (checkAnte == 9){ //Straight flush
				return chip * (50 + 1);
			}
			else if (checkAnte == 8){ //Quads
				return chip * (30 + 1);
			}
			else if (checkAnte == 7){ //Full house
				return chip * (10 + 1);
			}
			else if (checkAnte == 6){ //Flush
				return chip * (5 + 1);
			}
			else if (checkAnte == 5){ //Straight
				return chip * (4 + 1);
			}
			else if (checkAnte == 4){ //Three of kind
				return chip * (2 + 1);
			}
			
			return chip;
		}
		else if (checkResult == 2){
			return chip;
		}
	}
	
	return 0;
}
int EarnChipsPlay(int checkResult, int chip)
{
	if (chip != 0){
		if (checkResult == 0){ //Player win!
			return chip * 2;
		}
		else if (checkResult == 2){ //DRAW!
			return chip;
		}
	}
	
	return 0;
}

// ----- Set up -----
int buyChips(int number)
{
	if (number == 9)
		return 500;
	else if (number == 3 || number == 6)
		return 250;
	
	return 100;
}
