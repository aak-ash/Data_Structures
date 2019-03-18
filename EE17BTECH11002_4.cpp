#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

	
typedef struct node //tree node 
{
	int key;	
	struct node *left;
	struct node *right;
	struct node *parent;
}Node;

Node* newNode(int x) // node of BST n
{
	Node *temp = new Node;
	temp->parent = NULL;
	temp->key = x; 
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}		

Node *insert(Node *node,int key) {
	if (node == NULL) {
		return newNode(key);
	}
	if (key < node->key) {
		if (node->left == NULL) {
			node->left = newNode(key);
			node->left->parent = node;
		} else {
			node->left = insert(node->left, key);
		}
	}
	if (key > node->key) {
		if (node->right == NULL) {
			node->right = newNode(key);
			node->right->parent = node;
		} else {
			node->right = insert(node->right, key);
		}
	}

	if(key = node->key)
	{}
	return node;
}

void Preorder(Node *root)
{
	if(root==NULL)
		{return;}
	else{
		cout << root->key;
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

void del(Node *node) // deleteing using Post oreder traversl
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

Node *min(Node* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

Node *succesor(Node *node) {
	if (node->right != NULL) {
		return min(node->right);
	}
	Node* y = node->parent;
	while (y!= NULL && node == y->right) {
		node = y;
		y = y->parent;
	}
	return y;
}

Node* transplant(Node *root,Node *u,Node *v){
	if(u->parent==NULL){root=v;}
	else if(u==u->parent->left){
		u->parent->left=v;
	}
	else{u->parent->right=v;}
	if(v!=NULL){
		v->parent=u->parent;
	}
	return root;
}

Node* delet(Node *root,Node *z)
{
	if(z->left==NULL){
		root=transplant(root,z,z->right);
	}
	else if(z->right==NULL){
		root=transplant(root,z,z->left);
	}
	else
	{
		Node *y=min(z->right);
		if(y->parent!=z){
			root=transplant(root,y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		root=transplant(root,z,y);
		y->left=z->left;
		y->left->parent=y;
		
	}
	return root;
}

void find(int x,Node *root)
{
	Node *temp=new Node;
	temp=root;
	string str="";
	while((temp->key!=x) && temp!=NULL)
	{
		if(x > temp->key)
		{
			str+="1";
			temp=temp->right;
			if(temp==NULL) 
				{break;}
			
		}
		else if(x < temp->key)
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

Node *search(Node *node,int key) {
//	cout << "s1"<< endl;
	if ((node->key == key) || node==NULL) 
	{
//		cout << "s1 if"<< endl;
		//cout << node << endl;
		return node;
	} 
	else if (key > node->key) 
	{
//		cout << "s1 ef1"<< endl;
		if(node->right==NULL)
			{return NULL;}
		else
		{return search(node->right, key);}
	}
	 else if (key < node->key) 
	{
//		cout << "s1 ef2"<< endl;
		if(node->left==NULL)
			{return NULL;}
		else
		{return search(node->left, key);}
	}
}

Node *uncle(Node *z)
{
	if((z->parent != NULL) && (z->parent->parent!=NULL))
	{
		if(z->parent==z->parent->parent->left)
		    {return z->parent->parent->right;}
		else
			{return z->parent->parent->left;}
	}
	else
		{
			return NULL;
		}
}

void child(Node *z)
{
	if(z->left!=NULL && z->right!=NULL)
	{cout << z->left->key << " " << z->right->key << endl;}
	else if(z->left==NULL && z->right!=NULL)
	{cout << "Nil " << z->right->key << endl;}
	else if(z->left!=NULL && z->right==NULL)
	{cout << z->left->key << " Nil" << endl;}
	else if(z->left==NULL && z->right==NULL)
		{cout << "Nil Nil" << endl;}

}

void leftrot(Node **node,Node*x)
{
	Node *y=new Node;
	if(x->right==NULL)
	{}
else
		{
		y=x->right;
		if(x->parent==NULL)
			{
				*node=y;
				y->parent=NULL;
			} // root equals y
		else
		{
			y->parent=x->parent;
		}
		if(x->parent!=NULL)
		{
			if(x==x->parent->right)
				{x->parent->right=y;}
			else
				{x->parent->left=y;}
		}
		x->right=y->left;
		if(y->left!=NULL)
		{y->left->parent=x;}
		y->left=x;
		x->parent=y;
	}
}

void rightrot(Node **node,Node*x)
{
	Node *y=new Node;
	if(x->left==NULL)
	{}
else
		{
		y=x->left;
		if(x->parent==NULL)
			{
				*node=y;
				y->parent=NULL;
			} 
		else
		{
			y->parent=x->parent;
		}
		if(x->parent!=NULL)
		{
			if(x==x->parent->right)
				{x->parent->right=y;}
			else
				{x->parent->left=y;}
		}
		x->left=y->right;
		if(y->right!=NULL)
		{y->right->parent=x;}
		y->right=x;
		x->parent=y;
	}
}




int main()
{

	Node *root=NULL;
	while(!cin.eof())
	{
			string s;
			getline(cin,s);
			istringstream iss;
			iss.str(s);
			string vals;
			iss>>vals;


	
	//cout << "input reached " << endl;
	
		if(vals == "N" || vals=="B")
		{	
			vector<int> vect;
			if(root!=NULL)
			{del(root);}
			root=NULL;
			while(iss>>vals)
			{
				int val=stoi(vals);
				vect.push_back(val);
			}
			int size=vect.size(); // total number of number to be entered
			for(int i=0; i<size ;i++)
			{
				//vect[i].erase(0,vect[i].find_first_not_of('0'));
				//Number obj(vect[i]);
				if (root==NULL)
					{
						root=insert(root,vect[i]);
					}
				else 
				{
					insert(root,vect[i]);
				}
			}
			
			
		}

		else if(vals == "S")
		{
			
			iss>>vals;
			int val=stoi(vals);
			//Number search(k);
			find(val,root);	//path of val will be printed
		}

		else if(vals == "P")
		{
			Preorder(root);
			cout << endl;
		}
		else if(vals == "+")
		{
			
			iss>>vals;
			int val=stoi(vals); // k is to be inserted
			//Number ins(k);
			root=insert(root,val);
		}
		else if(vals == "-")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *z = search(root,val);
			root=delet(root,z);
		}
		else if(vals == ">") //find succecessor
		{
			iss>>vals;
			int val=stoi(vals);
	//		cout<< " > 1"<< endl;
			//string k=val;
	//		cout<< " > 2"<< endl;
			//Number suc(k);
	//		cout<< " > 3"<< endl;
			Node *ans=new Node;
			//cout<< " > 4"<< endl;
			Node *z=search(root,val);
			//cout<< " > 5"<< endl;//will return node or parent (if node is not there)
			if(z!=NULL)
				{ans=succesor(z);}
			else 
			{
				//cout<< "at else"<< endl;				
				root=insert(root,val);
				//cout<< "at else 3"<< endl;
				Node *z1 = search(root,val);
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
				cout << ans->key << endl;
			}


		}

		else if(vals == "U")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *z=search(root,val);
			if(z==NULL)
			{
				cout << "-1" << endl;
			}
			else
			{
				Node *u=uncle(z);
				{
					if(u==NULL)
					{cout << "-1" << endl;}
					else
					{cout << u->key << endl;}
				}
			}

		}
		else if(vals=="C")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *z=search(root,val);
			if(z==NULL)
				{cout << "-1" << endl;}
			else
			{
				child(z);
			}
		}
		else if(vals == "L")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *z=search(root,val);
			leftrot(&root,z);
		}

		else if(vals == "R")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *z=search(root,val);
			rightrot(&root,z);
		}


	}

}
