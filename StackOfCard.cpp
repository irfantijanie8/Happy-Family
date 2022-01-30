#include <iostream>
#include<ctime>
#include <vector>
#include <algorithm>
#include <string>
#include "StackOfCard.h"
using namespace std;

Card::Card()
{
	countCard=0;
	count =0;
	stackTop = nullptr;
			
			for(int i = 0; i<9 ; i++)
				for(int j = 0; j<4; j++)
				{
					suit[count]= codeAlpha[i]+codeNum[j]+Role[j]+Family[i];
					count+=1;
					cout << Role[j] << Family[i] << " - " << codeAlpha[i] << codeNum[j] << endl;
				}
			cout << endl;
			system("pause");
			system("cls");
			cout << "Shuffling the card\n\n";
			system("pause");
			system("cls");
			for (int i = 36 - 1; i > 0; i--){		//allocate for 36 card
       		 // Pick a random index from 0 to i
       		 	srand (time(NULL));
        		int random = rand() % (i + 1);
 
	        // Swap arr[i] with the element
   		     // at random index
       		swap(&suit[i], &suit[random]);		//will make generate random card
			}
			
			for(int i = 0; i<36 ; i++)
			{
				code[i]= suit[i][0];			//get the code at the front
				code[i]+= suit[i][1];
				suit[i].erase(0,1);				//delete the code from front
				suit[i].erase(0,1);
			}
			
			for(int i = 0; i<36 ; i++)		//push card into stack
			{
				push(code[i], suit[i]);
			}
}

void Card::swap(string *a, string *b){		//swap string into random position
    		string temp = *a;
    		*a = *b;
    		*b = temp;
		}


void Card::push(string code1, string suit1)
{
	Deck *newNode = nullptr;
	newNode = new Deck;
	newNode->card = suit1;			//initialize node card and key
	newNode->key = code1;
	
	
	if(isEmpty()){					//if first card
		stackTop = newNode;
		stackTop->next = nullptr;
	}
	else
	{
		newNode->next = stackTop;
		stackTop = newNode;
	}
	countCard++;					//plus number of card
}

void Card::pop(string &key1, string &card1)
{
	Deck *nodePtr=nullptr;
	if(isEmpty()){							//if no card
		cout << "Empty Stack\n\n";
	}
	else{
		key1 = stackTop->key;
		card1 = stackTop->card;		
		nodePtr=stackTop;
		stackTop = stackTop->next;
		delete nodePtr;
	}
	countCard--;						//minus number of card
}

bool Card::isEmpty()
{
	bool status;
	if(!stackTop)			//if stackTop==NULL
		status = true;
	else
		status = false;		//if not return false

	return status;
}

int Card::cardNum()			//to get number of card left
{
	return countCard;
}
