#include <math.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <fstream>
#include <GL/glew.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#include <GL\glut.h>
#include <assert.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <cmath>
#include <fstream>
#include <time.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <gl\glfw.h>
#include <vector>
#include <conio.h>
#include <new>
#define PI 3.14159265358979323846;
using namespace std;bool keystates[256];
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STRUCTURES:
struct PLAYERDATA{																//call: player_[n].X;
	int rollMode;																//the mode of roll;
	int buttonClicked;															//which button is clicked;
	int rollCount;																//which roll the player is on;
	int rollsLeft;																//how many rolls left;
	int turns;																	//number of turns left;
	int exYahtzees;																//add to turns left;
	bool scr;
	bool scrYathzee;
		struct DICE{															//call: player_[n].dice_[n].X;
				int die;														//die;
				bool keep;														//keep dice?
				int rand_;														//random number for die;
			DICE(){keep=0;}														//initiate values;
		};DICE dice_[5];
	PLAYERDATA(){rollMode=0;buttonClicked=-1;rollCount=0;rollsLeft=3;turns=13;scr=0;scrYathzee=0;}//initiate values;
};PLAYERDATA player_[10];int currPlayer=0;static int topPart[6]={0,0,0,0,0,0};	//the amount of times each part of the die shows.
struct WINDOWSTATS{																//call: window_[n].X;
	char title[100];															//title
	double mouseX,mouseY;														//for center of window;
	double windowPercentageX,windowPercentageY;									//percentage rather than pixel count;
	bool switchm,fullscreen,initi;												//test if clicked button,fullscreen,initiate;
	WINDOWSTATS(){switchm=1,fullscreen=1,initi=1;}								//initiate values;
};WINDOWSTATS window_[100];
struct BUTTON{																	//call: button_[n].X;
	double W,H,X,Y,Z;															//dimensions;
	double R,G,B,A;																//colors and alpha;(Values between 0 and 1)
	double XL,XR,YU,YD;															//for the mouse percentages;
	bool used[10];																//used the button for that player?
	bool available[10];															//button available for that player?
	BUTTON(){Z=-5;}																//initiate values;
};BUTTON button_[1000];static int bN=0;			
struct TEXT0{																	//call: text_[n].X;
	bool textKeep;																//keep the button?
	string text;																//text literally;
	double X,Y,Z;																//dimenions;
	double sX,sY,sZ;															//scaling;
	double R,G,B,A;																//colors and alpha;(Values between 0 and 1)
	TEXT0(){textKeep=0;}														//initiate values;
};TEXT0 text_[1000];static int tN=0;string text[10][1000];int total=0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS AND VOIDS:															//FUNCTIONS AND VOIDS:
bool INITIATE(){																//call: INITIATE_();
	if(window_[0].initi==1){													//UNTIL I FIX THIS, PUT THE Y VALUES AS OPPOSITE. EX: 3 should be -3 to actually be 3 in buttons;
		sprintf(window_[0].title,"%s","Yahtzee!");
		glutSetWindowTitle(window_[0].title);									//WINDOW 0 TITLE;
		
		double incY=0;double W=.6,X=-3;											//initialize buttons;
			for(int n=0;n<=62;n++){bN+=1;
				if(n==21||n==42){incY=0;}
				incY+=.2;
				if(n>=21&&n<42){W=.4;X=-2;}if(n>=42&&n<63){W=.2;X=-1.4;}
				button_[n].W=W;button_[n].H=.1;button_[n].X=X;button_[n].Y=-incY;button_[n].R=1.00;button_[n].G=1.00;button_[n].B=1.00;button_[n].A=0.75;
			}
		bN+=0;button_[bN].W=0.067;	button_[bN].H=0.1;	button_[bN].X=-1.5325;	button_[bN].Y=-1.0;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		bN+=1;button_[bN].W=0.067;	button_[bN].H=0.1;	button_[bN].X=-1.3985;	button_[bN].Y=-1.0;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		bN+=1;button_[bN].W=0.067;	button_[bN].H=0.1;	button_[bN].X=-1.265;	button_[bN].Y=-1.0;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		//dice;
		bN+=1;button_[bN].W=0.25;	button_[bN].H=0.25;	button_[bN].X=1.00;	button_[bN].Y=-4.00;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;//66-70
		bN+=1;button_[bN].W=0.25;	button_[bN].H=0.25;	button_[bN].X=1.50;	button_[bN].Y=-4.00;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		bN+=1;button_[bN].W=0.25;	button_[bN].H=0.25;	button_[bN].X=2.00;	button_[bN].Y=-4.00;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		bN+=1;button_[bN].W=0.25;	button_[bN].H=0.25;	button_[bN].X=2.50;	button_[bN].Y=-4.00;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		bN+=1;button_[bN].W=0.25;	button_[bN].H=0.25;	button_[bN].X=3.00;	button_[bN].Y=-4.00;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;
		bN+=1;button_[bN].W=1.25;	button_[bN].H=0.25;	button_[bN].X=2.00;	button_[bN].Y=-3.50;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;//r,s;
		bN+=1;button_[bN].W=1.25;	button_[bN].H=0.25;	button_[bN].X=2.00;	button_[bN].Y=-3.00;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;//end;
		bN+=1;button_[bN].W=1.25;	button_[bN].H=0.50;	button_[bN].X=2.00;	button_[bN].Y=-2.25;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;//tule;
		bN+=1;button_[bN].W=1.25;	button_[bN].H=0.10;	button_[bN].X=2.00;	button_[bN].Y=-1.65;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;//scr;
		bN+=1;button_[bN].W=1.25;	button_[bN].H=0.10;	button_[bN].X=2.00;	button_[bN].Y=-1.45;	button_[bN].R=1.00;button_[bN].G=1.00;button_[bN].B=1.00;button_[bN].A=1.00;//scr;
		//button range error;if(button_[n].X-button_[n].W<-8.88||button_[n].X+button_[n].W>8.88||button_[n].Y+button_[n].H<-4||button_[n].Y-button_[n].H>4){glutDestroyWindow (1);}
			
		double tY=4.16;															//initialize text;
			for(int N=0;N<21;N++){
				text_[N].X=-3.58;text_[N].Y=tY;text_[N].Z=-5;text_[N].R=0.00;text_[N].G=1.00;text_[N].B=1.00;text_[N].A=1.00;text_[N].sX=0.0012;text_[N].sY=0.0012;text_[N].sZ=0;
				tY-=.2;
			}tY=4.16;
		tN+=0;text_[tN].text="Aces       Add 1's";tN+=1;text_[tN].text="Twos       Add 2's";tN+=1;text_[tN].text="Threes      Add 3's";tN+=1;text_[tN].text="Fours       Add 4's";
		tN+=1;text_[tN].text="Fives       Add 5's";tN+=1;text_[tN].text="Sixes       Add 6's";tN+=1;text_[tN].text="TOTAL SCORE ----->";tN+=1;text_[tN].text="Bonus if >=63 Add 35";
		tN+=1;text_[tN].text="Total Top    ----->";tN+=1;text_[tN].text="3 Of A kind  Add all";tN+=1;text_[tN].text="4 Of A kind  Add all";tN+=1;text_[tN].text="Full House    Add 25";
		tN+=1;text_[tN].text="Small Straight  Add 30";tN+=1;text_[tN].text="Large Straight  Add 40";tN+=1;text_[tN].text="YAHTZEE     Add 50";
		tN+=1;text_[tN].text="Chance      Add all";tN+=1;text_[tN].text="-YAHTZEE-   X=100";tN+=1;text_[tN].text="-BONUS-    Per X";tN+=1;text_[tN].text="Total Bottom  ----->";
		tN+=1;text_[tN].text="Total Top    ----->";tN+=1;text_[tN].text="Grand Total   ----->";
		double tX=-1.58;
			for(int N=21;N<45;N++){
				tN+=1;
				if(N==27||N==28||N==29||N==37||N==38||N==39||N==40||N==41||N==42||N==43||N==44){text_[tN].text="-";}
				else{text_[tN].text="O";}
					text_[N].X=tX;text_[N].Y=tY;text_[N].Z=-5;text_[N].R=0.00;text_[N].G=1.00;text_[N].B=1.00;text_[N].A=1.00;text_[N].sX=0.0012;text_[N].sY=0.0012;text_[N].sZ=0;	
				if(N==38){text_[N].X=-1.44;text_[N].Y=0.96;}
				else if(N==39){text_[N].X=-1.30;text_[N].Y=0.96;}
				else{text_[N].X=-1.58;tY-=.2;}
			}
		tN+=0;text_[tN].text="Roll!";											//44;
		text_[tN].X=1.885;text_[tN].Y=3.5;text_[tN].Z=-5;text_[tN].R=0.00;text_[tN].G=1.00;text_[tN].B=1.00;text_[tN].A=1.00;text_[tN].sX=0.0012;text_[tN].sY=0.0012;text_[tN].sZ=0;
		double tx=0.95;
			for(int m=45;m<50;m++){
				tN+=1;text_[tN].text="X";
				text_[m].X=tx;text_[m].Y=3.95;text_[m].Z=-5;text_[m].R=0.00;text_[m].G=1.00;text_[m].B=1.00;text_[m].A=1.00;text_[m].sX=0.0012;text_[m].sY=0.0012;text_[m].sZ=0;
				tx+=.5;
			}
		tN+=1;text_[tN].text="Save all dice and end turn?";						//end turn?
		text_[tN].X=0.885;text_[tN].Y=3.0;text_[tN].Z=-5;text_[tN].R=0.00;text_[tN].G=1.00;text_[tN].B=1.00;text_[tN].A=1.00;text_[tN].sX=0.0012;text_[tN].sY=0.0012;text_[tN].sZ=0;
		tN+=1;text_[tN].text="Player #: X";										//player number;
		text_[tN].X=1.5;text_[tN].Y=2.50;text_[tN].Z=-5;text_[tN].R=0.00;text_[tN].G=1.00;text_[tN].B=1.00;text_[tN].A=1.00;text_[tN].sX=0.0012;text_[tN].sY=0.0012;text_[tN].sZ=0;
		tN+=1;text_[tN].text="Rolls left: X";									//rolls left;
		text_[tN].X=1.5;text_[tN].Y=2.00;text_[tN].Z=-5;text_[tN].R=0.00;text_[tN].G=1.00;text_[tN].B=1.00;text_[tN].A=1.00;text_[tN].sX=0.0012;text_[tN].sY=0.0012;text_[tN].sZ=0;
		tN+=1;text_[tN].text="Click to scratch";								//rolls left;
		text_[tN].X=1.5;text_[tN].Y=1.60;text_[tN].Z=-5;text_[tN].R=0.00;text_[tN].G=1.00;text_[tN].B=1.00;text_[tN].A=1.00;text_[tN].sX=0.0012;text_[tN].sY=0.0012;text_[tN].sZ=0;
		tN+=1;text_[tN].text="Reset?";											//rolls left;
		text_[tN].X=1.85;text_[tN].Y=1.40;text_[tN].Z=-5;text_[tN].R=0.00;text_[tN].G=1.00;text_[tN].B=1.00;text_[tN].A=1.00;text_[tN].sX=0.0012;text_[tN].sY=0.0012;text_[tN].sZ=0;
		currPlayer=0;
		for(int n=0;n<=bN;n++){													//set buttons used to 0;
			for(int pl=0;pl<10;pl++){
				button_[n].used[pl]=0;
				button_[n].available[pl]=0;
			}
		}
	}window_[0].initi=0;														//SET INITI TO false;
}//end void;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TEXT_(){tN=0;																//call: TEXT_();
	while(!text_[tN].text.empty()){
		glLoadIdentity();
		glTranslatef(text_[tN].X,text_[tN].Y,text_[tN].Z);
		glScalef(text_[tN].sX,text_[tN].sY,text_[tN].sZ);
		glColor4f(text_[tN].R,text_[tN].G,text_[tN].B,text_[tN].A);				//translate,scale,colors;
		for(int n=0;n<=text_[tN].text.length();n++){char m=text_[tN].text[n];	//convert text to a string of characters read in the for loop to display each char of text;
			glutStrokeCharacter(GLUT_STROKE_ROMAN,m);
		}tN+=1;
	}
}//end void;
int BUTTON(int x,int y){														//call: BUTTON(X,Y);
	player_[currPlayer].buttonClicked=-1;										//button clicked;
	for(int n=0;n<=bN;n++){
		if(window_[0].windowPercentageX>=button_[n].XL&&window_[0].windowPercentageX<=button_[n].XR
		&&window_[0].windowPercentageY>=button_[n].YU&&window_[0].windowPercentageY<=button_[n].YD&&window_[0].switchm==1){
			window_[0].switchm=0;player_[currPlayer].buttonClicked=n;
		}
		else if(window_[0].windowPercentageX>=button_[n].XL&&window_[0].windowPercentageX<=button_[n].XR
		&&window_[0].windowPercentageY>=button_[n].YU&&window_[0].windowPercentageY<=button_[n].YD&&window_[0].switchm==0){
			window_[0].switchm=1;player_[currPlayer].buttonClicked=n;/**/
		}
	}
	if(player_[currPlayer].rollCount!=3&&player_[currPlayer].rollMode!=4){
		if(player_[currPlayer].rollMode==2){
			if(text_[player_[currPlayer].buttonClicked-21].textKeep==0){text_[player_[currPlayer].buttonClicked-21].textKeep=1;}//
			else if(text_[player_[currPlayer].buttonClicked-21].textKeep==1){text_[player_[currPlayer].buttonClicked-21].textKeep=0;}//
		}	
		if(player_[currPlayer].buttonClicked==71){
			if(text_[44].text=="Roll!"){
				player_[currPlayer].rollsLeft-=1;
				text_[44].text="Stop!";
				player_[currPlayer].rollMode=1;		
			}
			else if(text_[44].text=="Stop!"){
				player_[currPlayer].rollCount+=1;
				text_[44].text="Keep?";
				player_[currPlayer].rollMode=2;
			}
			else if(text_[44].text=="Keep?"){
				text_[44].text="Roll!";
				player_[currPlayer].rollMode=3;
			}
			else if(text_[44].text=="Next Player"){
				text_[44].text="Roll!";
				for(int N=21;N<44;N++){
					if(text[currPlayer][N]==""){
						if(N==27||N==28||N==29||N==37||N==38||N==39||N==40||N==41||N==42||N==43||N==44/**/){text_[N].text="-";}
						else{text_[N].text="O";}
					}
					else{
						text_[N].text=text[currPlayer][N];
					}
				}
			}
		}
		if(player_[currPlayer].buttonClicked==72&&player_[currPlayer].rollCount>0){
			text_[50].text=" - Turn ended: Choose! -";
			player_[currPlayer].rollCount=3;
		}
	}
	return player_[currPlayer].buttonClicked;
};
int DRAWBUTTONS(){																//call: DRAWBUTTONS();
	for(int n=0;n<=bN;n++){														//# of buttons to be displayed+1;
			button_[n].XL=((5.6*button_[n].X)+50)-(5.6*button_[n].W);
			button_[n].XR=(5.6*button_[n].W)+((5.6*button_[n].X)+50);
			button_[n].YU=((10.0*button_[n].Y)+50)-(10.0*button_[n].H);
			button_[n].YD=(10.0*button_[n].H)+((10.0*button_[n].Y)+50);
		glLoadIdentity();
			glColor4f(button_[n].R,button_[n].G,button_[n].B,button_[n].A);
			glTranslatef(button_[n].X,button_[n].Y*-1,button_[n].Z);
		glBegin(GL_LINE_LOOP);{													//DRAW SQUARE OR RECTANGLE;
				glVertex2f(button_[n].W,button_[n].H);
				glVertex2f(button_[n].W,-button_[n].H);
				glVertex2f(-button_[n].W,-button_[n].H);
				glVertex2f(-button_[n].W,button_[n].H);
		glEnd();}
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mousemoveunpressed(int x, int y){
	window_[0].windowPercentageX=x/window_[0].mouseX*100;window_[0].windowPercentageY=y/window_[0].mouseY*100;
}//end void;
void mouseclick(int button,int state,int x,int y){
	
	if(state==GLUT_DOWN){BUTTON(x,y);}
;}//end void;
void keyPressed(unsigned char key, int x, int y){glutKeyboardFunc(keyPressed);
	if(key=='f'&&!window_[0].fullscreen){window_[0].fullscreen=true;}
	else if(key=='f'&&window_[0].fullscreen){window_[0].fullscreen=false;}
}//end void;
void one(void){ostringstream conv[100];
	glLoadIdentity();
		INITIATE();
		DRAWBUTTONS();
		TEXT_();static int nn=0;
			conv[5]<<currPlayer+1;text_[51].text="Player #: ";text_[51].text+=conv[5].str();
			conv[6]<<player_[currPlayer].rollsLeft;text_[52].text="Rolls left: ";text_[52].text+=conv[6].str();
	if(player_[currPlayer].rollMode==1){//roll mode 1;
		for(int n=0;n<5;n++){
			player_[currPlayer].dice_[n].rand_=rand()%6+1;
			conv[n]<<player_[currPlayer].dice_[n].rand_;
			if(text_[45+n].textKeep==0){
			text_[45+n].text=conv[n].str();
			}
		}
	}nn+=1;
	if(player_[currPlayer].rollMode==2&&player_[currPlayer].buttonClicked>=66&&player_[currPlayer].buttonClicked<=70){//roll mode 2;
		if(text_[player_[currPlayer].buttonClicked-21].textKeep){
			text_[player_[currPlayer].buttonClicked-21].R=1;
		}
		else if(!text_[player_[currPlayer].buttonClicked-21].textKeep){
			text_[player_[currPlayer].buttonClicked-21].R=0;
		}
	}
	if(player_[currPlayer].rollCount==3&&player_[currPlayer].rollMode!=5){		//set roll mode to 4;
		player_[currPlayer].rollsLeft=0;
		player_[currPlayer].rollMode=4;											//pick a spot;
		text_[44].text="Choose!";
		text_[50].text=" - Turn ended: Choose! -";
	}
	if(player_[currPlayer].rollMode==4){
		int die[5];//0,1,2,3,4;
		for(int n=0;n<5;n++){
			stringstream(text_[45+n].text)>>player_[currPlayer].dice_[n].die;	//convert string to int;
			die[n]=player_[currPlayer].dice_[n].die;
		}bool fh[2]={0,0};														//bool for full house test;
		for(int n=-1;n<6;n++){
			for(int m=0;m<5;m++){
				if(player_[currPlayer].dice_[m].die==n+1){topPart[n]+=1;}
			}
			if(n!=-1){
				if(topPart[n]>0&&button_[62-n].used[currPlayer]==0){			//1-6;
					button_[62-n].R=1;button_[62-n].G=.5;button_[62-n].B=.25;//--
					text_[21+n].R=1;text_[21+n].G=0;text_[21+n].B=0;//++
					button_[62-n].available[currPlayer]=1;
				}
				if(topPart[n]>=3&&button_[53].used[currPlayer]==0){				//3 of a kind;
					button_[53].R=1;button_[53].G=.5;button_[53].B=.25;//--
					text_[30].R=1;text_[30].G=0;text_[30].B=0;//++
					button_[53].available[currPlayer]=1;
				}
				if(topPart[n]>=4&&button_[52].used[currPlayer]==0){				//4 of a kind;
					button_[52].R=1;button_[52].G=.5;button_[52].B=.25;//--
					text_[31].R=1;text_[31].G=0;text_[31].B=0;//++
					button_[52].available[currPlayer]=1;
				}
				if(topPart[n]==2){fh[0]=1;}if(topPart[n]==3){fh[1]=1;}			//full house;
				if(fh[0]==1&&fh[1]==1&&button_[51].used[currPlayer]==0){
					button_[51].R=1;button_[51].G=.5;button_[51].B=.25;//--
					text_[32].R=1;text_[32].G=0;text_[32].B=0;//++
					button_[51].available[currPlayer]=1;
				}																//large straight;
				if(button_[49].used[currPlayer]==0&&(
				topPart[0]==1&&topPart[1]==1&&topPart[2]==1&&topPart[3]==1&&topPart[4]==1||
				topPart[1]==1&&topPart[2]==1&&topPart[3]==1&&topPart[4]==1&&topPart[5]==1)){
					button_[49].R=1;button_[49].G=.5;button_[49].B=.25;//--
					text_[34].R=1;text_[34].G=0;text_[34].B=0;//++
					button_[49].available[currPlayer]=1;
				}
				if(topPart[n]==5&&button_[48].used[currPlayer]==0&&player_[currPlayer].scrYathzee==0){
					button_[48].R=1;button_[48].G=.5;button_[48].B=.25;//--		//yahtzee;
					text_[35].R=1;text_[35].G=0;text_[35].B=0;//++
					button_[48].available[currPlayer]=1;
				}
				if(topPart[n]&&button_[47].used[currPlayer]==0){				//chance;
					button_[47].R=1;button_[47].G=.5;button_[47].B=.25;//--
					text_[36].R=1;text_[36].G=0;text_[36].B=0;//++
					button_[47].available[currPlayer]=1;
				}
			}
		}
		if(button_[50].used[currPlayer]==0){									//small straight;
			for(int n=0;n<3;n++){
				if(topPart[0+n]<3&&topPart[0+n]>0&&topPart[1+n]==1&&topPart[2+n]==1&&topPart[3+n]==1||
				topPart[1+n]<3&&topPart[1+n]>0&&topPart[0+n]==1&&topPart[2+n]==1&&topPart[3+n]==1||
				topPart[2+n]<3&&topPart[2+n]>0&&topPart[0+n]==1&&topPart[1+n]==1&&topPart[3+n]==1||
				topPart[3+n]<3&&topPart[3+n]>0&&topPart[0+n]==1&&topPart[1+n]==1&&topPart[2+n]==1){
					button_[50].R=1;button_[50].G=.5;button_[50].B=.25;//--
					text_[33].R=1;text_[33].G=0;text_[33].B=0;//++
					button_[50].available[currPlayer]=1;
				}
			}
		}
		player_[currPlayer].rollMode=5;
	}
	if(player_[currPlayer].rollMode==5){										//add the score;
			if(player_[currPlayer].buttonClicked==74){
				text_[53].text="Scratch what?";
			}
		if(player_[currPlayer].buttonClicked==74&&player_[currPlayer].scr==0){player_[currPlayer].scr=1;}
		if(player_[currPlayer].buttonClicked!=74&&player_[currPlayer].scr==1&&	//scratch a play;
		button_[player_[currPlayer].buttonClicked].used[currPlayer]==0&&button_[player_[currPlayer].buttonClicked].available[currPlayer]==0&&
		player_[currPlayer].buttonClicked<=62&&player_[currPlayer].buttonClicked>=47&&
		player_[currPlayer].buttonClicked!=56&&player_[currPlayer].buttonClicked!=55&&player_[currPlayer].buttonClicked!=54){
				text_[83-player_[currPlayer].buttonClicked].text="XX";
				text[currPlayer][83-player_[currPlayer].buttonClicked]="XX";
			button_[currPlayer].available[currPlayer]=0;
			button_[player_[currPlayer].buttonClicked].used[currPlayer]=1;
			player_[currPlayer].scr=0;
			text_[44].text="Next Player";
			if(player_[currPlayer].buttonClicked==48){player_[currPlayer].scrYathzee=1;}
			player_[currPlayer].rollMode=6;
			player_[currPlayer].rollCount=4;
		}
	total=0;
		if(player_[currPlayer].exYahtzees<3&&player_[currPlayer].scrYathzee==0){									//extra yahtzees;
			for(int n=0;n<6;n++){
				if(topPart[n]==5&&button_[48].used[currPlayer]==1){
					button_[48].R=1;button_[48].G=.5;button_[48].B=.25;//--
					text_[35].R=1;text_[35].G=0;text_[35].B=0;//++
				}
				if(topPart[n]==5&&button_[48].used[currPlayer]==1&&player_[currPlayer].buttonClicked==48){
					if(player_[currPlayer].exYahtzees==0){text[currPlayer][37]="X";text_[37].text="X";text[currPlayer][40]="100";text_[40].text="100";}
					if(player_[currPlayer].exYahtzees==1){text[currPlayer][38]="X";text_[38].text="X";text[currPlayer][40]="200";text_[40].text="200";}
					if(player_[currPlayer].exYahtzees==2){text[currPlayer][39]="X";text_[39].text="X";text[currPlayer][40]="300";text_[40].text="300";}
					player_[currPlayer].exYahtzees+=1;
					player_[currPlayer].turns+=1;
					text_[44].text="Next Player";								//reset;
					player_[currPlayer].rollMode=6;
					player_[currPlayer].rollCount=4;
				}
			}
		}
		if(button_[player_[currPlayer].buttonClicked].used[currPlayer]==0&&button_[player_[currPlayer].buttonClicked].available[currPlayer]==1){
			for(int n=62;n>=47;n--){											//=47 and less than 63
				if(button_[n].used[currPlayer]==0){
					button_[n].available[currPlayer]=0;button_[player_[currPlayer].buttonClicked].used[currPlayer]=1;
				}
			}
			for(int n=0;n<6;n++){												//1-6;
				if(player_[currPlayer].buttonClicked==62-n){
					total=(n+1)*topPart[n];
					conv[7+n]<<total;text[currPlayer][21+n]=conv[7+n].str();
					text_[21+n].text=text[currPlayer][21+n];
				}
			}																	//3 of a kind, 4 of a kind, and chance;
			if(player_[currPlayer].buttonClicked==53||player_[currPlayer].buttonClicked==52||player_[currPlayer].buttonClicked==47){
				for(int n=0;n<6;n++){
					total+=(n+1)*topPart[n];
				}int clicked=0;
				if(player_[currPlayer].buttonClicked==52){clicked=1;}
				if(player_[currPlayer].buttonClicked==47){clicked=6;}
				conv[13+clicked]<<total;text[currPlayer][30+clicked]=conv[13+clicked].str();
				text_[30+clicked].text=text[currPlayer][30+clicked];
			}																	//full house, small straight, large straight, yahztee;
			if(player_[currPlayer].buttonClicked<=51&&player_[currPlayer].buttonClicked>=48){
				int clicked=0;
				if(player_[currPlayer].buttonClicked==50){clicked=1;total=30;}
				else if(player_[currPlayer].buttonClicked==49){clicked=2;total=40;}
				else if(player_[currPlayer].buttonClicked==48){clicked=3;total=50;}
				else{total=25;;}
				conv[15+clicked]<<total;text[currPlayer][32+clicked]=conv[15+clicked].str();
				text_[32+clicked].text=text[currPlayer][32+clicked];
			}
			text_[44].text="Next Player";										//must be here for some reason for this reset? why idk;
			player_[currPlayer].rollMode=6;
			player_[currPlayer].rollCount=4;
		}
	}
	if(player_[currPlayer].rollCount==4){										//reset values: 
		text_[50].text="Save all dice and end turn?";
		text_[53].text="Click to scratch";
		int total1=0;															//add top part total;
		if(text[currPlayer][21]!=""&&text[currPlayer][22]!=""&&text[currPlayer][23]!=""&&text[currPlayer][24]!=""&&text[currPlayer][25]!=""&&text[currPlayer][26]!=""){
			total=0;
			for(int n=0;n<6;n++){
				stringstream tot(text[currPlayer][21+n]);
				tot>>total;
				total1+=total;
			}
			conv[20]<<total1;text[currPlayer][27]=conv[20].str();
			text_[27].text=text[currPlayer][27];
			if(total1>=63){
				total1+=35;
				text[currPlayer][28]="+35";
				text_[28].text="+35";
			}
			if(total1<63){
				text[currPlayer][28]="+0";
				text_[28].text="+0";
			}
			conv[21]<<total1;text[currPlayer][29]=conv[21].str();
			text_[29].text=text[currPlayer][29];
			conv[22]<<total1;text[currPlayer][42]=conv[22].str();
			text_[42].text=text[currPlayer][42];
		}																		//add bottom part total;
		if(text[currPlayer][30]!=""&&text[currPlayer][31]!=""&&text[currPlayer][32]!=""&&text[currPlayer][33]!=""&&
		text[currPlayer][34]!=""&&text[currPlayer][35]!=""&&text[currPlayer][36]!=""){
			total=0;
			total1=0;
			for(int n=0;n<7;n++){
				stringstream(text_[30+n].text)>>total1;//convert string to int;
				total+=total1;//text[currPlayer][30];
			}
			if(text[currPlayer][37]=="X"){total+=100;}if(text[currPlayer][38]=="X"){total+=100;}if(text[currPlayer][39]=="X"){total+=100;}
			conv[23]<<total;text[currPlayer][41]=conv[23].str();
			text_[41].text=text[currPlayer][41];
		}
		player_[currPlayer].turns-=1;
		player_[currPlayer].rollMode=0;
		player_[currPlayer].rollCount=0;
		player_[currPlayer].rollsLeft=3;
		currPlayer+=1;
		if(currPlayer>0/*9*/){currPlayer=0;}
		if/*while*/(player_[currPlayer].turns<=0){
			total=0;total1=0;
			stringstream(text[currPlayer][42])>>total1;							//convert string to int;
				total+=total1;
			stringstream(text[currPlayer][41])>>total1;							//convert string to int;
				total+=total1;
			conv[24]<<total;text[currPlayer][43]=conv[24].str();
				text_[43].text=text[currPlayer][43];
			currPlayer+=1;
			if(currPlayer>0/*9*/){currPlayer=0;}
		}
		for(int n=42;n<=65;n++){
			button_[n].R=1;button_[n].G=1;button_[n].B=1;//--
			for(int m=21;m<=43;m++){
				text_[m].R=0;text_[m].G=1;text_[m].B=1;//++
			}
		}
		for(int n=0;n<6;n++){
			topPart[n]=0;
		}
		for(int m=45;m<50;m++){
			text_[m].textKeep=0;text_[m].text="X";
			text_[m].R=0.00;text_[m].G=1.00;text_[m].B=1.00;text_[m].A=1.00;
		}
		if/*while*/(player_[currPlayer].turns<=0&&player_[currPlayer].buttonClicked==75||player_[currPlayer].turns==-5){//currPlayer=0;
			for(int N=21;N<44;N++){
				for(int n=0;n<10;n++){
					text[n][N]="";
				}
				if(N==27||N==28||N==29||N==37||N==38||N==39||N==40||N==41||N==42||N==43||N==44/**/){text_[N].text="-";}
				else{text_[N].text="O";}
				text_[N].text;//=text[currPlayer][N];
				text_[44].text="Roll!";
			}
			for(int n=0;n<10;n++){
				player_[n].scrYathzee=0;
				player_[n].rollMode=0;
				player_[n].rollCount=0;
				player_[n].turns=13;
				player_[n].buttonClicked=-1;
				player_[n].rollsLeft=3;
				player_[n].turns=13;
				player_[n].scr=0;
				for(int m=0;m<6;m++){
					player_[n].dice_[m].keep=0;
					button_[n].used[m]=0;
					button_[n].available[m]=0;
				}
				window_[n].switchm=1;
				window_[n].fullscreen=1;
				text_[n].textKeep=0;
			}
			text_[53].text="Click to scratch";
			bN=0;
			tN=0;
			total=0;
			window_[0].initi=1;//fix;
		}
	}
	if(player_[currPlayer].buttonClicked==75){
		player_[currPlayer].turns=-5;
			text_[44].text="Next Player";										//must be here for some reason for this reset? why idk;
			player_[currPlayer].rollMode=6;
			player_[currPlayer].rollCount=4;
	}
;}//end void;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void display(void){
	glLoadIdentity();
		glEnable(GL_TEXTURE_3D);//glEnable(GL_CULL_FACE);//glCullFace(GL_FRONT);
		glEnable(GL_NORMALIZE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_COLOR_MATERIAL); 
		glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);glClearColor(0,0,0,1);
			glDepthFunc(GL_GEQUAL);glClearDepth(0);
    	one();
	    glutSwapBuffers();
	if(window_[0].fullscreen){glutFullScreen();}
	else{
		glutReshapeWindow((glutGet(GLUT_SCREEN_WIDTH)/1.25),(glutGet(GLUT_SCREEN_HEIGHT)/1.25));
		glutPositionWindow((glutGet(GLUT_SCREEN_WIDTH)-glutGet(GLUT_SCREEN_WIDTH)/1.25)/2,(glutGet(GLUT_SCREEN_HEIGHT)-glutGet(GLUT_SCREEN_HEIGHT)/1.25)/2);		
	}
}//end void;
void reshape(GLint w, GLint h){
	glMatrixMode(GL_PROJECTION);
	window_[0].mouseX=(GLfloat)w;window_[0].mouseY=(GLfloat)h;
	glLoadIdentity();
	glViewport(0,0,w,h);gluPerspective(90.f,(GLfloat)w/(GLfloat)h,0.0f,1.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}//end void;
int main(int argc,char **argv){													//main and set window properties;
	srand(time(NULL));
    glutInit(&argc,argv);
    	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH)/1.25,glutGet(GLUT_SCREEN_HEIGHT)/1.25);
    	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-glutGet(GLUT_SCREEN_WIDTH)/1.25)/2,(glutGet(GLUT_SCREEN_HEIGHT)-glutGet(GLUT_SCREEN_HEIGHT)/1.25)/2);
		glutCreateWindow("");
    glutPassiveMotionFunc(mousemoveunpressed);
    glutDisplayFunc(display);glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouseclick); 
    glutMainLoop();
    return 0;
}
