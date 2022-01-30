#include <iostream>
#include<ctime>
#include <vector>
#include <algorithm>
#include <string>
#include "PlayerDeck.h"
using namespace std;

//insert the first card
void PlayerCard::appendCard(string newKey, string newCard) {

  ListNode* newNode = new ListNode;
  newNode->key1 = newKey;
  newNode->card1 = newCard;
  newNode->next = NULL;

  if (head == 0) {
      head = newNode;
      return;
  } else {
      //Node* temp = new Node;
      ListNode *temp = head;
      while (temp->next != NULL) {
          temp = temp->next;
      }
      temp->next = newNode;
      //delete temp;
  }
}

void PlayerCard::insertCard(string newKey, string newCard)
{
	ListNode *newNode = new ListNode;
	ListNode *nodePtr = head;
	ListNode *previousNode = nullptr;
	
	newNode->key1 = newKey;
	newNode->card1 = newCard;
	newNode->next = NULL;
	
	if(!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else
	{
		previousNode = nullptr;
		
		while(nodePtr != nullptr && nodePtr->key1[0]<newKey[0])	//insert in order
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		
		if(previousNode == nullptr)		//for the first card
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else
		{
			previousNode->next = newNode;
			newNode->next=nodePtr;
		}
	}

}

//delete card after complete family or give card to other
void PlayerCard::deleteCard(string delKey)
{
	ListNode *nodePtr;
	ListNode *previousNode;
	
	if(!head)
		return;
		
	if(head->key1==delKey)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		nodePtr = head;
		previousNode = nullptr;
	
		while(nodePtr!=nullptr&&nodePtr->key1!=delKey)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if(nodePtr)
		{
			previousNode->next=nodePtr->next;
			delete nodePtr;
		}
		
	}
	
}

//display player card
void PlayerCard::displayCard() const
{
	ListNode *nodePtr = NULL;
	
	nodePtr = head;
	
	while(nodePtr->next!=NULL)		//repeat until linked list end
	{
		cout << nodePtr->key1 << " - " << nodePtr->card1 << endl;
		nodePtr = nodePtr->next;
	}
	cout << nodePtr->key1 << " - " << nodePtr->card1 << endl;	//display last card
}

//search card if exist, if exist add card to other  player and delete the card from current player
bool PlayerCard::searchReplace(string keySearch, int currentPos, int choicePlayer, PlayerCard player[])
{
	bool found = false;
	ListNode* nodePtr;
	nodePtr = head;
	while(nodePtr !=NULL && !found)
	{
		if(nodePtr->key1 >=keySearch)
			found = true;
		else	
			nodePtr = nodePtr->next;
	}
	
	if(found)
		found = (nodePtr->key1 == keySearch);
		
	if(found)
	{
		player[currentPos].insertCard(nodePtr->key1, nodePtr->card1);	// add card to other  player
		player[choicePlayer].deleteCard(nodePtr->key1);			//delete card from current player
	}
	
	return found;
}

//check if player have complete family
void PlayerCard::checkFamily()
{
	//bool found = false;
	ListNode* nodePtr;
	int familyFound =0;
	char family = 'a';
	for(family; family<='i' ;family++)
	{
		familyFound = 0;
		nodePtr = head;
		while(nodePtr!=NULL){
			if(nodePtr->key1[0]==family)
				familyFound++;
			nodePtr = nodePtr->next;	
			}
		if(familyFound==4)
			break;	
	}
	
	if(familyFound==4)
	{
		//found = true;
			deleteFamily(family);	//if player have complete family, delete the family card
	}
}

//delete the family card
void PlayerCard::deleteFamily(char delFamily)
{
	ListNode *nodePtr;
	ListNode *previousNode;
	int delCount =0;
	
	while(delCount<4)	//delete 4 card of the family
	{
		if(!head)
		return;
		
		if(head->key1[0]==delFamily)
		{
			nodePtr = head->next;
			delete head;
			head = nodePtr;
		}
		else
		{
			nodePtr = head;
			previousNode = nullptr;
	
			while(nodePtr!=nullptr&&nodePtr->key1[0]!=delFamily)
			{
				previousNode = nodePtr;
				nodePtr = nodePtr->next;
			}
			if(nodePtr)
			{
				previousNode->next=nodePtr->next;
				delete nodePtr;
			}
		
		}
		delCount++;		//counter
	}
	completeFamily++;		//add to completeFamily
}

int PlayerCard::getCompleteFamily()
{
	return completeFamily;	//get the number of complete family
}


