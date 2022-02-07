#include "PokerHT.h"

void displayRecordTable()
{
	gotoXY(2, 1);
	textcolor(LIGHT_VIOLET);
	cout << "\xc9-=-=-=-=-=-=-=-=RECORD TABLE=-=-=-=-=-=-=-=-\xbb";
	textcolor(BEIGE);
	
	for (int i = 0; i < HEIGHT - 8; i++){
		gotoXY(2, 2 + i);
		cout << RecordTable[i];
	}
}

void printRecordInfo(Record rec[])
{
	ifstream ifs;
	ifs.open("Record.txt");
	if (ifs.is_open()){
		string temp = "";
		int i = 0;
		
		getline(ifs, temp); //Ignore the first line.
		while(!ifs.eof()){
			getline(ifs, temp, ',');
			if (temp != ""){
				rec[i].round = stoi(temp);
			}
			else{
				rec[i].round = 0;
			}
			
			getline(ifs, temp, ',');
			if (temp != ""){
				rec[i].token = stoi(temp);
			}
			else{
				rec[i].token = 0;
			}
			
			getline(ifs, temp);
			rec[i].time = temp;
			
			i++;
		}
		
		ifs.close();
	}
	
	
	int i = 0, y = 0;
	while((rec[i].round != 0) && (i < 3)){
		if (i == 0){
			textcolor(LIGHT_RED);
		}
		else if (i == 1){
			textcolor(LIGHT_YELLOW);
		}
		else if (i == 2){
			textcolor(GREEN);
		}
		// Print number of a round
		gotoXY(7, 5 + y);
		cout << "     ";
		gotoXY(8, 5 + y);
		cout << rec[i].round;
		//Print points
		gotoXY(13, 5 + y);
		cout << "       ";
		gotoXY(14, 5 + y);
		cout << rec[i].token;
		//Print time
		gotoXY(21, 5 + y);
		cout << "                         ";
		gotoXY(22, 5 + y);
		cout << rec[i].time;
		
		textcolor(BEIGE);
		
		++i;
		y += 2;
	}
	
	cout << endl;
}

void getRecordInfo(Record rec[])
{
	ifstream ifs;
	ifs.open("Record.txt");
	if (ifs.is_open()){
		string temp = "";
		int i = 0;
		
		getline(ifs, temp); //Ignore the first line.
		while(!ifs.eof()){
			getline(ifs, temp, ',');
			if (temp != ""){
				rec[i].round = stoi(temp);
			}
			else{
				rec[i].round = 0;
			}
			
			getline(ifs, temp, ',');
			if (temp != ""){
				rec[i].token = stoi(temp);
			}
			else{
				rec[i].token = 0;
			}
			
			getline(ifs, temp);
			rec[i].time = temp;
			
			i++;
		}
		
		ifs.close();
	}
}

void getNewRecordInfo(Record rec[], int Round, int chips, string Time)
{
	if (chips > rec[0].token){
		rec[2].round = rec[1].round;
		rec[2].token = rec[1].token;
		rec[2].time = rec[1].time;
		
		rec[1].round = rec[0].round;
		rec[1].token = rec[0].token;
		rec[1].time = rec[0].time;
		
		rec[0].round = Round;
		rec[0].token = chips;
		rec[0].time = Time;
	}
	else if (chips > rec[1].token){
		rec[2].round = rec[1].round;
		rec[2].token = rec[1].token;
		rec[2].time = rec[1].time;
		
		rec[1].round = Round;
		rec[1].token = chips;
		rec[1].time = Time;
	}
	else if (chips > rec[2].token){
		rec[2].round = Round;
		rec[2].token = chips;
		rec[2].time = Time;
	}
}

void saveRecordInfo(Record rec[])
{
	ofstream ofs;
	ofs.open("Record.txt");
	if (ofs.is_open()){
		ofs << "Round Points Time\n";
		
		ofs << rec[0].round << "," << rec[0].token << "," << rec[0].time << endl;
		ofs << rec[1].round << "," << rec[1].token << "," << rec[1].time << endl;
		ofs << rec[2].round << "," << rec[2].token << "," << rec[2].time;
		
		ofs.close();
	}
	return;
}
