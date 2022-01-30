#ifndef PLAYERDECK_H
#define PLAYERDECK_H
#include "StackOfCard.h"
#include <iostream>
using namespace std;

class ListNode
{
	public:
		string key1, card1;		//keep the card and its key 
		ListNode *next;
};

class PlayerCard{
	
	private:
		ListNode *head;
		int completeFamily;		//num of family complete
		
	public:
		PlayerCard(){
			head = nullptr;
			completeFamily=0;
		}
		~PlayerCard()
		{
		}

		void appendCard(string, string);	//insert the first card
		void insertCard(string, string);	//insert card in order
		void deleteCard(string);			//delete card when giving to other
		void displayCard() const;			//display player card
		void game(int currentPos, int currentGroup, int member, int group, PlayerCard player[], int &cardNum, Card &stack);
		bool searchReplace(string keySearch, int currentPos, int choicePlayer, PlayerCard player[]);
		void checkFamily();			//check if the player have complete family
		void deleteFamily(char);	//delete if player have complete family and completeFamily++
		int getCompleteFamily();	//get the count of complete family
};

#endif
