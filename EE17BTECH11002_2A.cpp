#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct node {
	int key;
	struct node *prev;
	struct node * next;
} Node;

void newnode(int x, Node *t) // new node  
{
	Node *temp = NULL;
	temp = (Node*) malloc(sizeof(Node));
	temp->key = x;                             //pointer manupulation
	temp->next = t->next;
	t->next->prev = temp;
	t->next = temp;
	temp->prev = t;
}

void makelist(string s, Node*sen) // making list of node 
{

	int size = s.length();
	for (int i = size - 1; i >= 0; i--) {
		newnode(int(s[i] - '0'), sen);
	}

}

int size(Node*sent) {
	int i = 0;
	Node *temp = sent;

	while (temp->next != sent) {
		temp = temp->next;
		i++;
	}
	return i;
}

class Number {
public:
	string s1;
	Node *sent;
	int sze;
	Number(string st1) //constructor
			{
		s1 = st1;
		Node *sentinel = NULL;
		sentinel = (Node*) malloc(sizeof(Node));
		sentinel->next = sentinel;
		sentinel->prev = sentinel;
		makelist(s1, sentinel);

		sent = sentinel;
		sze = size(sentinel);
	}

	Number operator+(const Number q) {
		string str="";
		int carry = 0;
		int t = 0;
		Node*temp1, *temp2;
		temp1 = sent->prev;
		temp2 = q.sent->prev;
		if (sze >= q.sze) {

			while (temp2 != q.sent) //till intersection of two lists
			{
				t = 0;
				t = (temp1->key + temp2->key + carry); // adding node values with carry
				char r=char(t%10+int('0'));
				str+=r;
				carry = t / 10;
				temp1 = temp1->prev;
				temp2 = temp2->prev;
			}

			while (temp1 != sent) {
				t = 0;
				t = (temp1->key + carry); // node and carry
				if(temp1->prev==sent){
					char r=char(t%10+int('0'));
				str+=r;
				}
				else
				{
					char r=char(t%10+int('0'));
				str+=r;
			}
				carry = t / 10;
				temp1 = temp1->prev;
			}
				
              if(carry>0)
              {
              	char r=char(carry+int('0'));
              	str+=r;
              }
		}

		else

		{

			while (temp1 != sent) //till intersection of two lists
			{
				t = 0;
				t = (temp1->key + temp2->key + carry); // adding node values with carry
			char r=char(t%10+int('0'));
				str+=r;	carry = t / 10;
				temp2 = temp2->prev;
				temp1 = temp1->prev;
			}

			while (temp2 != q.sent) // for remaining list
			{
				t = 0;
				t = (temp2->key + carry); // node and carry
				if (temp2->prev == q.sent) {
					char r=char(t%10+int('0'));
				str+=r;
				}
				else
				{
				char r=char(t%10+int('0'));
				str+=r;}
				carry = t / 10;
				temp2 = temp2->prev;

			}

			if(carry>0)
              {
              	char r=char(carry+int('0'));
              	str+=r;
              }

		}
		Node * temp=sent->next;
		while(temp!=sent)
		{
			free(temp->prev);
			temp=temp->next;
		}
		free(sent->prev);

		Node * temp3=q.sent->next;
		while(temp3!=q.sent)
		{
			free(temp3->prev);
			temp3=temp3->next;
		}
		free(q.sent->prev);

		reverse(str.begin(),str.end());

		Number sum(str);
		return sum;

	} // operator + ends here

	int operator>(const Number q)
	{
		Node *temp1=sent->next;
		Node *temp2=q.sent->next;
		if(sze>q.sze)
			{return 1;}
		else if(sze < q.sze)
			{return 0;}
		else
		{	
			while(temp1->key==temp2->key && (temp1!=sent) && (temp2!=q.sent))
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}

			if((temp1->key > temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return 1;}
			else if ((temp1->key < temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return 0;}
			else 
				{return 1;}
		}

		//free memory
		Node * temp=sent->next;
		while(temp!=sent)
		{
			free(temp->prev);
			temp=temp->next;
		}
		free(sent->prev);

		Node * temp3=q.sent->next;
		while(temp3!=q.sent)
		{
			free(temp3->prev);
			temp3=temp3->next;
		}
		free(q.sent->prev);
	}

};

int main() {
	while(!cin.eof())
	{	string j,k;

	cin >> j >> k;
	j.erase(0,j.find_first_not_of('0'));
	k.erase(0,k.find_first_not_of('0'));
    dif (j!="" && k!=""){
	Number a(j);
	Number b(k);
	if(a>b)
		{cout << "1" << endl;}
	else
		{cout << "0" << endl;}

	}

	}


	return 0;
}