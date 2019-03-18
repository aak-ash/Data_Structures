#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;



typedef struct node {
	int key;
	struct node *prev;
	struct node * next;
} Node;

void newnode(int x, Node *t) // new node of list 
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

	

	bool operator>(const Number q)
	{
		Node *temp1=sent->next;
		Node *temp2=q.sent->next;
		if(sze>q.sze)
			{return true;}
		else if(sze < q.sze)
			{return false;}
		else
		{	
			while(temp1->key==temp2->key && (temp1!=sent) && (temp2!=q.sent))
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}

			if((temp1->key > temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return true;}
			else if ((temp1->key < temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return false;}
			else 
				{return false;}
		}
	}

	bool operator<(const Number q)
	{
		Node *temp1=sent->next;
		Node *temp2=q.sent->next;
		if(sze>q.sze)
			{return false;}
		else if(sze < q.sze)
			{return true;}
		else
		{	
			while(temp1->key==temp2->key && (temp1!=sent) && (temp2!=q.sent))
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}

			if((temp1->key > temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return false;}
			else if ((temp1->key < temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return true;}
			else 
				{return false;}
		}
	}

	bool operator =(const Number q)
	{
		Node *temp1=sent->next;
		Node *temp2=q.sent->next;
		if(sze!=q.sze)
			{return false;}
		
			
			while(temp1->key==temp2->key && (temp1!=sent) && (temp2!=q.sent))
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}

			if((temp1->key > temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return false;}
			else if ((temp1->key < temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return false;}
			else 
				{return true;}
		
	}

	bool operator!=(const Number q)
	{
		Node *temp1=sent->next;
		Node *temp2=q.sent->next;
		
        if(sze!=q.sze)
			{return true;}
		
			
			while(temp1->key==temp2->key && (temp1!=sent) && (temp2!=q.sent))
			{
				temp1=temp1->next;
				temp2=temp2->next;
			}

			if((temp1->key > temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return true;}
			else if ((temp1->key < temp2->key) && (temp1!=sent) && (temp2!=q.sent))
				{return true;}
			else 
				{return false;}
		
	}

};

	
typedef struct tnode
{
	//instead of storing obj we'll store pointer to that object
	Number *key;//declared pointer	
	struct tnode *left;
	struct tnode *right;
	struct tnode *parent;
}Nodet;

Nodet* newNode(Number x) // node of BST nodet(node of tree)
{
	Nodet *temp = (Nodet*) malloc(sizeof(Nodet));
	temp->parent = NULL;
	temp->key = new Number(x); // allcating pointee to the pointer
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

Nodet *insert(Nodet *node,Number key) {
	if (node == NULL) {
		return newNode(key);
	}
	if (key < *(node->key)) {
		if (node->left == NULL) {
			node->left = newNode(key);
			node->left->parent = node;
		} else {
			node->left = insert(node->left, key);
		}
	}
	if (key > *(node->key)) {
		if (node->right == NULL) {
			node->right = newNode(key);
			node->right->parent = node;
		} else {
			node->right = insert(node->right, key);
		}
	}

	if(key = *(node->key))
	{}
	return node;
}

void Preorder(Nodet *root)
{
	if(root==NULL)
		{return;}
	else{
		Number num=*(root->key);
		cout <<num.s1;
		if (root->left!=NULL)
		{
		cout<<" ";
		Preorder(root->left);
		}
		if (root->right!=NULL)
		{
		cout<<" ";
		Preorder(root->right);
		}
	}
}

void del(Nodet *node) // deleteing using Post oreder traversl
{
	if(node==NULL)
		{return;}
	else
	{
		del(node->left);
		del(node->right);
		free(node);
	}
}

Nodet *min(Nodet* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

Nodet *succesor(Nodet *node) {
	if (node->right != NULL) {
		return min(node->right);
	}
	Nodet* y = node->parent;
	while (y != NULL && node == y->right) {
		node = y;
		y = y->parent;
	}
	return y;
}



void transplant(Nodet **root,Nodet *u,Nodet *v){
	if(u->parent==NULL){*root=v;}
	else if(u==u->parent->left){
		u->parent->left=v;
	}
	else{u->parent->right=v;}
	if(v!=NULL){
		v->parent=u->parent;
	}
}

Nodet* delet(Nodet *root,Nodet *z)
{
	if(z->left==NULL){
		transplant(&root,z,z->right);
	}
	else if(z->right==NULL){
		transplant(&root,z,z->left);
	}
	else
	{
		Nodet *y=min(z->right);
		if(y->parent!=z){
			transplant(&root,y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		transplant(&root,z,y);
		y->left=z->left;
		y->left->parent=y;
		//root=y;
	}
	return root;
}



void find(Number x,Nodet *root)
{
	Nodet *temp=new Nodet;
	temp=root;
	string str="";
	while((*(temp->key)!=x) && temp!=NULL)
	{
		if(x > *(temp->key))
		{
			str+="1";
			temp=temp->right;
			if(temp==NULL) 
				{break;}
			
		}
		else if(x < *(temp->key))
		{
			str+="0";
			temp=temp->left;
			if(temp==NULL) 
				{break;}
			
		}
		else
			{	
				break;
	 };
	}

	if(temp==NULL)
	{
		
		cout << "-1" << endl;
	}
		
	else 
	{
		cout << str << endl;
	}
}

Nodet *search(Nodet *node,Number key) {
//	cout << "s1"<< endl;
	if ((*(node->key) = key) || node==NULL) 
	{
//		cout << "s1 if"<< endl;
		//cout << node << endl;
		return node;
	} 
	else if (key > *(node->key)) 
	{
//		cout << "s1 ef1"<< endl;
		if(node->right==NULL)
			{return NULL;}
		else
		{return search(node->right, key);}
	}
	 else if (key < *(node->key)) 
	{
//		cout << "s1 ef2"<< endl;
		if(node->left==NULL)
			{return NULL;}
		else
		{return search(node->left, key);}
	}
}

int main()
{

	Nodet *root=NULL;
	int c=1;
	while(!cin.eof())
	{
			string s;
			getline(cin,s);
			istringstream iss;
			iss.str(s);
			string val;
			iss>>val;
	
	//cout << "input reached " << endl;
	
		if(val == "N")
		{	
			vector<string> vect;
			if(root!=NULL)
			{del(root);}
			root=NULL;
			while(iss>>val)
			{
				vect.push_back(val);
			}
			int size=vect.size(); // total number of number to be entered
			for(int i=0; i<size ;i++)
			{
				vect[i].erase(0,vect[i].find_first_not_of('0'));
				Number obj(vect[i]);
				if (root==NULL)
					{
						root=insert(root,obj);
					}
				else 
				{
					Nodet *t=insert(root,obj);
				}
			}
			
			
		}
		else if(val == "S")
		{
			
			iss>>val;
			string k=val;
			k.erase(0,k.find_first_not_of('0'));
			Number search(k);
			find(search,root);				 // to be serached
		}

		else if(val == "P")
		{
			Preorder(root);
			cout << endl;
		}
		else if(val == "+")
		{
			
			iss>>val;
			string k=val; // k is to be inserted
			k.erase(0,k.find_first_not_of('0'));
			Number ins(k);
			root=insert(root,k);
		}
		else if(val == "-")
		{
			iss>>val;
			string k=val; // k is to be deleted
			k.erase(0,k.find_first_not_of('0'));
			Number ser(k);
			//cout << ser.s1 << endl;					//this is to be searches and node to be returned
			Nodet *z = search(root,ser);
			//cout << "searched node is : " << z->key->s1 << endl;
			if(z!=NULL)
			{root=delet(root,z);}
		}
		else if(val == ">") //find succecessor
		{
			iss>>val;
	//		cout<< " > 1"<< endl;
			string k=val;
			k.erase(0,k.find_first_not_of('0'));
	//		cout<< " > 2"<< endl;
			Number suc(k);
	//		cout<< " > 3"<< endl;
			Nodet *ans=new Nodet;
			//cout<< " > 4"<< endl;
			Nodet *z=search(root,suc);
			//cout<< " > 5"<< endl;//will return node or parent (if node is not there)
			if(z!=NULL)
				{ans=succesor(z);}
			else 
			{
				//cout<< "at else"<< endl;				
				root=insert(root,suc);
				//cout<< "at else 3"<< endl;
					Nodet *z1 = search(root,suc);
				//cout<< "at else 4"<< endl;
				ans=succesor(z1);
				delet(root,z1);
				//cout<< "at else 7"<< endl;

			}

			if(ans==NULL)
			{
				cout << "-1" << endl;
			}
			else
			{
				Number q=*(ans->key);
				cout << q.s1 << endl;
			}


		}
	}

}