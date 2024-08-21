
/*
-----------------------------------
|      GEMS COLLECT GAME          |
-----------------------------------

*/


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>




/*
	INSTRUCTIONS
		1. Use key 'a' to move left
		2. Use key 's' to move right
		3. Use key 'w' to move up
		4. Use key 'z' to move down
		5. Press 'q' To Quit The Game Any Time
*/

//Function Declaration.
void drawBoundary(int,int,int*,int*,int*);
void changeUserLocationOnButtonClick(int *,int *,char,int*,int*);
void printFile(char, int);

void drawBoundary(int x,int y,int *posX,int *posY,int *gameOver){ 
	// Here I will be drawing the boundary using (-) and (|) character.
	int i,j,k;
	for(i=-1;i<=10;i++){
		for(j=-1;j<=50;j++){
			if(j==-1 || j==50){
				printf("|");
			}
			if(i==-1 || i==10){
				printf("-");
			}
			else{
				if(i==y && j==x){
					printf("P");
					for(k=0;k<4;k++){
						if(posX[k]==x && posY[k]==y){
							posX[k]=-1;
							posY[k]=-1;
							(*gameOver)++; 
						}
					}
				}	
				else{
					if(posX[0]==j && posY[0]==i){
						printf("a");
					}
					else if(posX[1]==j && posY[1]==i){
						printf("b");
					}
					else if(posX[2]==j && posY[2]==i){
						printf("c");
					}
					else if(posX[3]==j && posY[3]==i){
						printf("d");
					}

					else
						printf(" ");
				}		
			}
		}
		printf("\n");
	}
}

void changeUserLocationOnButtonClick(int *x,int *y,char keyPressed,int *noOfMoves,int *gameQuit){
	switch(keyPressed){
		case 'w':     // ASCII value of  UP Arrow Key
			if(*y!=0){
				(*noOfMoves)++;
				(*y)--;     // Changing y 
			}	  
			break;
		case 'a':     // ASCII value of  LEFT Arrow Key
			if(*x!=0){
				(*noOfMoves)++;
				(*x)--;  // Changing x
			}	
			break;
		case 's':     // ASCII value of  RIGHT Arrow Key
			if(*x!=49){
				(*noOfMoves)++;
				(*x)++;  // Changing x
			}	
			break;
		case 'z':     // ASCII value of  DOWN Arrow Key
			if(*y!=9){
				(*noOfMoves)++;
				(*y)++;  // Changing y 
			}	
			break;
		case 'q':
			*gameQuit=1; 
			break;
	}
}


void printFile(char name, int score){

}

int main(){
	int x=0,y=0; // for user position
	char ch;     // to store the key Pressed
	char username[20]; // store user input name
	int positionX[4]={0}; // gems X Position
	int positionY[4]={0}; // gems Y Position
	int randomNum,i=0;
	int gameOver=0,noOfMoves=0,gameQuit=0;
	int hasTakenInput = 0;

	FILE *sfile;

	// open file in append mode
	sfile = fopen("scores.txt", "a");
	

	srand(time(0));

					
	// Storing the random X Position For gems
	while(i<4){     
		randomNum=rand()%50;
		positionX[i]=randomNum;
		i++;
	}

	
	// Storing the random Y Position For gems
	i=0;
	while(i<4){
		randomNum=rand()%10;
		positionY[i]=randomNum;
		i++;
	}

	printf("please enter your name: ");
	scanf("%s", &username);

	



	drawBoundary(x,y,positionX,positionY,&gameOver); // Function Call

	while(1){
		if(kbhit()){
			ch=getch();
			system("cls");

			changeUserLocationOnButtonClick(&x,&y,ch,&noOfMoves,&gameQuit);

			drawBoundary(x,y,positionX,positionY,&gameOver);

			if(gameOver==4){ // if gameOver value becomes 4 means i have collected all the gems!
				system("cls");
				printf("\n[][][][] Well Done %s [][][][]\n", username);
				printf("\nYou Collected All The Gems!\n");
				printf("\nIt Took You %d Moves!\n",noOfMoves);
				printf("\n[][][][] Game Over [][][][]\n");

				fprintf(sfile, "\nName: %s \nScore: %d \n----------------\n", username, noOfMoves);

				fclose(sfile);
				break; // it will break infinite loop as i have won the game
			}

			if(gameQuit==1){
				system("cls");
				printf("\nOh No! You Quit!!\n");
				printf("\nYou Collected %d Gems!\n",gameOver); // gameOver will give the number of gems collected.
				printf("\nAfter %d Moves You Quit!\n",noOfMoves); // gives number of moves so for.
				printf("\n[][][][] Game Over [][][][]\n");
				break;	//breaking the infinite loop
			}

		}
	}

	getch();
	return(0);
}