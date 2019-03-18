#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <limits.h>
using namespace std;

typedef struct node
{
	int key;
	int rank;
	struct node *parent;
}Node;

typedef struct arr
{
	Node *root;
}Head;

Node* newnode(int k)
{
	Node *temp=new Node;
	temp->key=k;
	temp->rank=1;
	temp->parent=temp;
	return temp;
}

class set
{
public:
	int n;
	Head *h;
	set(int num) //constructor
	{
		n=num;
		h= new Head[n+1];
		for(int i=1;i<n+1;i++)
		{
			h[i].root=newnode(i);

		}
	}

	Node* find(int k)
	{
		Node *temp;
		for(int i=1;i<n+1;i++)
		{
			if(h[i].root->key==k)
				{
					temp=h[i].root;
					break;
				}
			else 
				{temp=NULL;}
		}
		if(temp!=NULL)
		{
				while(temp->parent!=temp)
				{
					temp=temp->parent;
				}
				return temp;
		}
		return temp;
	}

	int check(int a,int b)
	{
		int c=0;
		if(a<=0 || b<=0)
			{return -1;}
		else
		{
			for(int i=1;i<n+1;i++)
			{
				if(h[i].root->key==a || h[i].root->key==b)
					{c++;}
			}
			if(c!=2)
				{return -1;}
			else if(find(a)==find(b))
				{return 1;}
			else if(find(a)!=find(b))
				{return 0;}

			}
	}
	void Union(int a,int b)
	{

	    if((a <= n) && (b<=n) && (a>0) && (b>0))
		{
			Node *ra=find(a);
			Node *rb=find(b);
			if(ra->rank==rb->rank)
			{
				rb->parent=ra;
				ra->rank++;
			}
			else if(ra->rank>rb->rank)
			{rb->parent=ra;}
			else
			{ra->parent=rb;}
		}
		else
		{}

	}

	Node *Rank(int a)
	{
		for(int i=1;i<n+1;i++)
		{
			if(h[i].root->key==a)
				{return h[i].root;}
		}
		return NULL;
	}
};
	

int i=0;
int main()
{
	while(!cin.eof())
	{
		string s;
		getline(cin,s);
		istringstream iss;
		iss.str(s);
		string vals;
		iss>>vals;
		set *p;
		if(vals=="N")
		{
			//cout << i << endl;
			if(i!=0)
				{delete p;}
			iss>>vals;
			int n=stoi(vals);
			p=new set(n);
			i=1;
		}
		else if(vals=="?")
		{
			iss>>vals;
			int a=stoi(vals);
			iss>>vals;
			int b=stoi(vals);
			int out=p->check(a,b);
			cout << out << endl;
		}
		else if(vals=="S")
		{
			iss>>vals;
			int a=stoi(vals);
			Node *pa=p->find(a);
			if(pa!=NULL)
			{cout << pa->key << endl;}
			else
				{cout << "-1" << endl;}
		}
		else if(vals=="U")
		{
			iss>>vals;
			int a=stoi(vals);
			iss>>vals;
			int b=stoi(vals);
			p->Union(a,b);
		}
		else if(vals=="R")
		{
			iss>>vals;
			int a=stoi(vals);
			Node *temp=p->Rank(a);
			if(temp!=NULL)
			{cout << temp->rank << endl;}
			else
			{cout << "-1" <<endl;}
		}
	}
}