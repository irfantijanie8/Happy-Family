#ifndef STACKOFCARD_H
#define STACKOFCARD_H

#include <iostream>
using namespace std;


//Stack is used for card
class Card{
	private:
		struct Deck{
			string card;	//These will store the name of card and its key
			string key;
			Deck *next;
		};
		Deck *stackTop;
		int countCard;		//number of card in the stack
	
	public:
		int random;			//is used to shuffle the card
		int count;			//use as counter
		//combination of these string will make the cards and keys
		string codeNum[4] = {"1", "2", "3", "4"};
		string codeAlpha[9] = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
		string Role[4] = {"Papa ","Mama ","Boy ","Girl "};
		string Family[9] = {"Doctor","Baker","Engineer","Teacher","Scientist","Mechanic","Architect","Chef","Musician"};
		//use to store the card first before passing it into stack
		string suit[36];
		string code[36];
			
		Card();
		
		~Card()
		{
		}
		void swap(string *, string *);	//shuffling the card
		void push(string, string);		//put card into the stack
		bool isEmpty();					//determine stack is empty or not
		void pop(string &, string&);	//take out card from stack
		int cardNum();					//to get recent number of card in stack

};

#endif
