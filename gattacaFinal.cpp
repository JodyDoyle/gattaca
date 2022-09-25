#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>     							// srand, rand 
#include <time.h>       							// time 
#include "doublyLinkedList.h"
#include <stdlib.h>									// clrscr

int generator(int difficulty);
void guess(int n);
char randomChar();
void finalGuess(int gattaca);
void game(int difficulty);
int setDifficulty();
bool checkForGattaca(int r);
void enqueue(Node *p);
Node* dequeue();
void clearScreen();

using namespace std;
int counter = 0;
int numGuesses = 0;
int limit = 5;
Node* arr[5];										// queue of pointers to the board
int front, rear;

int main()
{
	// Game instructions
	cout<<"\n\t\tWelcome to gattaca! Here is a quick summary of how to play:\n"<<endl;
	cout<<" You will start off with a string of question marks (?) and behind each question mark is a character. Either 'g', 'a', 't' or 'c'"<<endl;
	cout<<" Somewhere in this sequence of characters the word 'gattaca' will be spelled out. Your objective is to find it."<<endl;
	cout<<" You will be able to reveal which character is behind one of the question marks each turn."<<endl;
	cout<<" When you think you know where the 'gattaca' sequence is you can make a final guess."<<endl;
	cout<<" Try to find 'gattaca' with as few characters revealed as possible! Good Luck!\n"<<endl;
	
	/* initialize random seed: */
	srand (time(NULL));
	int difficulty = 10;							// initial length of the board
	front = 0;										// start of the queue
	rear = -1;										// back of the queue
	
	int ch;
	do{
		cout << "\n 1 Start game";
		cout << "\n 2 Set difficulty";
		cout << "\n 3 Exit";
		cout << "\n Enter choice ";
		cin >> ch;
		switch(ch){
			case 1:
				game(difficulty);
				break;
				
			case 2:
				difficulty = setDifficulty();
				break;
			case 3: break;
			
			default: cout << "\n Invalid choice\n";
		}
	}while(ch!=3);
	
	return 0;
}

/*
	Show the game menu to the user and handle the game logic
*/

void game(int difficulty)
{
	int x = difficulty;
	
	deleteList();
	int gat = generator(x);
	print(x);
	bool end = false;
	int ch;
	
	do{
		cout<<"What would you like to do?"<<endl;
		cout << "\n 1 Reveal a character";
		cout << "\n 2 Make a final guess";
		cout << "\n 3 Exit";
		cout << "\n Enter choice ";
		cin >> ch;
		switch(ch){
			case 1:
				guess(x);
				clearScreen();
				break;
				
			case 2:
				finalGuess(gat);
				end = true;
				break;
			case 3:  break;
			default: cout << "\n Invalid choice\n";
		}
		if(end)
		{
			while(rear > -1){
				Node *del =  dequeue();
				counter = 0;
			}
			return;
		}
		else
		{
			print(x);
		}
		
	}while(ch!=3);
}

/*
	Ask the user to change the difficulty of the game
*/

int setDifficulty(){
	int temp;
	cout << "\n 1 Very Easy - 10 characters, 5 visible";
	cout << "\n 2 Easy - 10 characters, 4 visible";
	cout << "\n 3 Medium - 15 characters, 3 visible";
	cout << "\n 4 Hard - 20 characters, 2 visible";
	cout << "\n 5 Very Hard - 25 characters, 1 visible";
	cout << "\n Enter choice ";
	cin >> temp;
	switch(temp){
		case 1: 
			limit = 5;
			return 10;
			break;
		case 2:
			limit = 4;
			return 10;
			break;
		case 3: 
			limit = 3;
			return 15; 
			break;
		case 4: 
			limit = 2;
			return 20;
			break;
		case 5: 
			limit = 1;
			return 25;
			break;
		default: return -1; break;
	}
}

/*
	Initialize the starting board
*/

int generator(int difficulty)
{
	int i = 0;
	int x = difficulty - 7;
	
  	/* generate secret number between 0 and x: */
  	int r = rand() % x;
	
	while(i<difficulty)
	{	
		if(i==r)
		{
			insertEnd('g');
			insertEnd('a');
			insertEnd('t');
			insertEnd('t');
			insertEnd('a');
			insertEnd('c');
			insertEnd('a');
			i+=7;
		}
		else
		{
			insertEnd(randomChar());
			i++;
		}
		
	}
	return r+1;
}

/*
	Generate random character from 'a', 'g', 't', 'c'
*/

char randomChar()
{
	/* initialize random seed: */
  	//srand (time(NULL));
  	/* generate secret number between 0 and 3: */
  	int r = rand() % 4;
  	
  	switch(r)
  	{
  		case 0:
  			return 'a';
  			
  		case 1:
  			return 'g';
  			
  		case 2:
  			return 't';
  			
  		case 3:
  			return 'c';
  			
  		default:
  			return 'g';
	}
}

/*
	Reveal a letter from the sequence
*/

void guess(int n)
{
    cout<<"\nPlease enter your next guess between 1 and "<<n<<endl;
    int guess;
    cin>>guess;
    Node* temp =head;
    for (int i = 0; i < guess-1; ++i) {
        temp =temp->next;
    }
    temp->isRevealed = true;
    if(counter >= limit){
    	Node *pop = dequeue();
    	pop->isRevealed = false;
	}
    enqueue(temp);
    counter++;
    numGuesses++;
}

/*
	Guess where the starting position of GATTACA
*/

void finalGuess(int gattaca){
    cout<<"\nMake your final guess of the starting node position"<<endl;
    int final;
    cin>>final;
    if (gattaca==final)
        cout<<"\nCongratulations you have won!\nYou made " << numGuesses << " guesses"<<endl;
    else
        cout<<"\nYou have failed"<<endl;
	numGuesses = 0;
}

/*
	Insert element in the queue
*/

void enqueue(Node *p){
	if(rear == limit - 1)
		cout << "\nQueue overflow \n";
	else{
		arr[++rear] = p;
	}
}

/*
	Remove the first element in the queue
*/

Node* dequeue(){ 	
	Node *p = arr[front];		
	if(front > rear)
		cout << "\nQueue underflow \n";
	else{
		for(int i = front; i < rear; i++){
			arr[i] = arr[i+1];
		}
		rear--;
	}
	return p;
}

/*
	Clear the console on Windows
*/

void clearScreen()
{
  system("cls");
}
