#include <iostream>
#include<ctime>
#include <vector>
#include <algorithm>
#include <string>
#include "StackOfCard.h"
#include "Gheader.h"
#include "PlayerDeck.h"
using namespace std;

void checkWin(PlayerCard player[], int group, int member)
{
	int totalFamily[group];
	int winner;
	int counter =0;
	for(int i=0; i<group; i++)
	{
		for(int j=0; j<member; j++)
		{
			totalFamily[i] = player[counter].getCompleteFamily();		//get total family from member of same group
			counter++;
		}
	}
	for(int i=1; i<group ; i++)
	{
		winner = i-1;
		if(totalFamily[i]>totalFamily[i-1])			//replace winner if the next group have more totalFamily
			winner = i;
	}
	
	winner+=1;
	
	cout << "\nThe winner is Group " << winner << " - " << totalFamily[winner-1] << " families" << endl;
	
}

void turn(Card stack, PlayerCard player[], int group, int member)
{
	int counter;
	int group1 = 1;
	int cardNum = stack.cardNum();
	
	for(int i= 0; cardNum!=0 ; i+=member)		//repeat game until stack is empty
	{
		cout << "Card in the stack: " << cardNum << endl << endl;
		if(i==2||i==3)
			group1++;
		if(i==4)
			i=1;
		if(i==5)
			i=0;

		player[i].game(i, group1, member, group, player, cardNum, stack);		//player turn
		system("pause");
		system("cls");
		cout << "Next group turn\n\n";
		system("pause");
		system("cls");
		
		if(group1==group)
			group1 = 1;
			
	}
	checkWin(player, group, member);		//check the winner
	
}

void drawCard(int currentPos, PlayerCard player[], Card &stack)		
{
	string xkey, xcard;
	stack.pop(xkey, xcard);	//pass key and card as reference, get the card that on stackTop
	cout << "You have draw Card " << xkey << " - " << xcard << endl;		//display draw card
	player[currentPos].appendCard(xkey, xcard);		//add card into player hand
}

void PlayerCard::game(int currentPos, int currentGroup, int member, int group, PlayerCard player[], int &cardNum, Card &stack)
{
	int counter=0;
	int choice;
	bool status;
	char giveChoice;
	string request, give;
	player[currentPos].checkFamily();	//check if player have complete family
	cout << "\nPlayer " << (currentPos%member)+1 << " Group " << currentGroup << " Card:\n\n";
	player[currentPos].displayCard();	//display player card
	
	do{
		cout << "\n\nChoose who you want to ask card from: \n\n";
		for(int i=0; i<group; i++)
		{
			for(int j=0; j<member; j++)
			{
				if(i+1!=currentGroup)
					cout << "Player " << j+1 << " Group " << i+1 << " - " << counter << endl;	//display other group
				counter+=1;
			}		
		}
		cout << "\n\nYour choice(answer in integer): ";		//choose other group member to get card
		cin >> choice;
		if(choice<0||choice>(member*group-1))
			cout << "Invalid input. Please reenter\n\n";
	}
	while(choice<0||choice>(member*group-1));		//repeat if invalid input

	do
	{
		cout << "Answer in index (ex: g4)\n\n";		//ask what card that you want
		cout << "Do you have card ";
		cin >> request;
		if(request[0]>'i' || request[0]<'a' || request[1]>'4'|| request[1]<'0')
			cout << "The card don't exist. Please reenter\n\n";
	}
	while(request[0]>'i' || request[0]<'a' || request[1]>'4'|| request[1]<'0');
	//repeat if card don't exist
	
	//check if the other player have the card
	status = player[choice].searchReplace(request, currentPos, choice, player);
	
	//if the other player dont have the card, draw a card
	if(status==false)
	{
		cout << "Unlucky. Draw a card!\n\n";
		system("pause");
		system("cls");
		drawCard(currentPos, player, stack);
		cardNum--;
		system("pause");
	}
	player[currentPos].checkFamily();	//check if player have complete family
	cout << "\n\nPlayer " << (currentPos%member)+1 << " Group " << currentGroup << " Card:\n\n";
	player[currentPos].displayCard();	//display player card after draw
	
	
	
	do{
		cout << "\nDo you want to give a card to your member(y-yes, n-no): ";
		cin >> giveChoice;
		if(giveChoice!='y'&&giveChoice!='n')
			cout << "Invalid input. Please reenter";
	}
	while(giveChoice!='y'&&giveChoice!='n');	//repeat if invalid input
	
	if(giveChoice=='y')		//if yes, choose who and what card
	{
		do{
			counter =0;
			cout << "Choose who you want to give the card to: \n\n";
			for(int i=0; i<group; i++)
			{
				for(int j=0; j<member; j++)
				{
					if(i+1==currentGroup&&counter!=currentPos)
						cout << "Player " << j+1 << " Group " << i+1 << " - " << counter << endl;
					counter+=1;
				}		
			}
			cout << "\n\nYour choice(answer in integer): ";
			cin >> choice;
			if(choice<((currentGroup-1)*member)||choice>((currentGroup)*member))
				cout << "Invalid input. Please reenter\n\n";	
		}
		while(choice<((currentGroup-1)*member)||choice>((currentGroup)*member));
		
		do{
			cout << "Choose the card you want to give:\n\n";
			player[currentPos].displayCard();
			cout << "\n\nYour Choice(Answer in index): ";
			cin >> give;
			status = player[currentPos].searchReplace(give, choice, currentPos, player); //check if card exist and insert it to member deck
			if(status==false)
				cout << "You don't have that card. Please reenter\n\n";
		}
		while(!status);	//repeat if the card don't exist
		
	}
	
}


int main()
{
	string key;		//for card and its key
	string card;
	int groups, members, numOfPlayer;
	int counter = 0;
	cout << "\tWelcome to a game of Happy Family\n" << "_________________________________________________\n\n";
	cout << "The Card: \n\n";
	Card stack;
	cout << "How many groups: ";
	cin >> groups;
	cout << "How many members: ";
	cin >> members;
	numOfPlayer = groups * members;
	system("cls");
	
	PlayerCard player[numOfPlayer];		//array of object bass on member and groups
	
	for(int i = 0; i < numOfPlayer; i++)	//draw card for each player
	{
		for(int drawCard=0; drawCard<8; drawCard++)		//draw 7 card for each player
		{
			stack.pop(key, card);
			if(drawCard==0)
			player[i].appendCard(key, card);		//append first card
			else
			player[i].insertCard(key, card);		//insert card in order
		}
	}
	
	for(int i=0; i<groups; i++)		//display all player card after draw
	{
		if(i!=0)
			cout << "Next Group\n\n";
		system("Pause");
		system("cls");	
		for(int j=0; j<members; j++)
		{
			cout << "\n\nPlayer " << j+1 << " Group " << i+1 << " Card: " <<endl;
			player[counter].displayCard();
			cout << endl;
			system("Pause");
			system("cls");
			counter+=1;
		}
			
	}
	turn(stack, player, groups, members);	//pass all object used and num of groups and members play
	
	cout << "\n\nThank You!!!!!" << endl;	//end
	
	return 0;
	
}
