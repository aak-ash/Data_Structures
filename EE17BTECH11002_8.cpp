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

typedef enum {black,red} nodecolor;

typedef struct node
{
	int key;
	struct node*left;
	struct node*right;
	struct node*parent;
	nodecolor color;
}Node;

#define NIL &sentinel
Node sentinel ={0,NIL,NIL,0,black};
Node *root=NIL;

void rotateLeft(Node *x) {

    Node *y = x->right;

    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }

    y->left = x;
    if (x != NIL) x->parent = y;
}

void rotateRight(Node *x) {

    Node *y = x->left;

    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        root = y;
    }

    y->right = x;
    if (x != NIL) x->parent = y;
}


Node *newnode(int x,Node *par)
{
	Node *temp=new Node;
	temp->key=x;
	temp->parent=par;
	temp->right=NIL;
	temp->left=NIL;
	temp->color=red; //red means temp->color=1
	return temp;
}

void fixinsert(Node *x) {


    while (x != root && x->parent->color == red) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y->color == red) {

                // uncle is red 
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            } else {

                // uncle is black 
                if (x == x->parent->right) {
                    x = x->parent;
                    rotateLeft(x);
                }

                // recolor and rotate 
                x->parent->color = black;
                x->parent->parent->color = red;
                rotateRight(x->parent->parent);
            }
        } else {

            Node *y = x->parent->parent->left;
            if (y->color == red) {

                // uncle is red 
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            } else {

                // uncle is black 
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = black;
                x->parent->parent->color = red;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = black;
}

Node *insert(int key)
{
	Node *node=root;
	Node *parent=0;
	while(node!=NIL)
	{
		if(node->key == key)
			{return node;}
		else if(node->key > key)
		{parent=node;
			node=node->left;}
		else if(node->key < key)
			{parent=node;
				node=node->right;}
	}
	Node *temp=newnode(key,parent);
	if(parent)
	{
		if(key<parent->key)
			{parent->left=temp;}
		else
			{parent->right=temp;}
	}
	else
	{root=temp;}
	fixinsert(temp);
	return temp;
}

void deletefix(Node *x) {

    while (x != root && x->color == black) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == red) {
                w->color = black;
                x->parent->color = red;
                rotateLeft (x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black && w->right->color == black) {
                w->color = red;
                x = x->parent;
            } else {
                if (w->right->color == black) {
                    w->left->color = black;
                    w->color = red;
                    rotateRight (w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                rotateLeft (x->parent);
                x = root;
            }
        } else {	
            Node *w = x->parent->left;
            if (w->color == red) {
                w->color = black;
                x->parent->color = red;
                rotateRight (x->parent);
                w = x->parent->left;
            }
            if (w->right->color == black && w->left->color == black) {
                w->color = red;
                x = x->parent;
            } else {
                if (w->left->color == black) {
                    w->right->color = black;
                    w->color = red;
                    rotateLeft (w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rotateRight (x->parent);
                x = root;
            }
        }
    }
    x->color = black;
}

Node *min(Node* node) {
	while (node->left != NIL) {
		node = node->left;
	}
	return node;
}

void deletenode(Node *z)
{
	Node *x,*y;

	/*if (!z || z == NIL) 
		{return;}*/
    if (z->left == NIL || z->right == NIL) 
    {y = z;} 
	else {
        y = z->right;
        y=min(y);
    }

    // x is y's only child 
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    // remove y from the parent chain 
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != z) z->key = y->key;


    if (y->color == black)
        deletefix (x);
    free (y);
}


Node *search(Node *node,int key) {
//	cout << "s1"<< endl;
	if ((node->key == key) || node==NIL) 
	{
//		cout << "s1 if"<< endl;
		//cout << node << endl;
		return node;
	} 
	else if (key > node->key) 
	{
//		cout << "s1 ef1"<< endl;
		if(node->right==NIL)
			{return NIL;}
		else
		{return search(node->right, key);}
	}
	 else if (key < node->key) 
	{
//		cout << "s1 ef2"<< endl;
		if(node->left==NIL)
			{return NIL;}
		else
		{return search(node->left, key);}
	}
}



Node *succesor(Node *node,Node *root) {
	//cout << node->key << endl;
	if (node->right != NIL) {
		return min(node->right);
	}
	Node* y = node->parent;
	while (y!= NIL && node == y->right) {
		
		node = y;
		//cout << node->key << endl;
		if(y!=root)
		{y = y->parent;}
		else
			{return NULL;}
		//cout << y->key << endl;
	}
	return y;
}


void find(int x,Node *root)
{
	Node *temp=new Node;
	temp=root;
	string str="";
	while((temp->key!=x) && temp!=NIL)
	{
		if(x > temp->key)
		{
			str+="1";
			temp=temp->right;
			if(temp==NIL) 
				{break;}
			
		}
		else if(x < temp->key)
		{
			str+="0";
			temp=temp->left;
			if(temp==NIL) 
				{break;}
			
		}
		else
			{	
				break;
	 		}
	}

	if(temp==NIL)
	{
		cout << "-1" << endl;
	}
	else 
	{
		if(temp->color==0)
		{cout << str << " B" << endl;}
		else
			{cout << str << " R" << endl;}
	}
}
	
void Preorder(Node *node)
{
	if(node==NIL)
		{return;}
	else{
		cout << node->key;
		if (node->left!=NIL)
		{
		cout<<" ";
		Preorder(node->left);
		}
		if (node->right!=NIL)
		{
		cout<<" ";
		Preorder(node->right);
		}
	}
}

Node* check(Node *node) {
	if (node == NIL) {
	} else {
		check(node->left);
		cout << node->key << " " << node->color << " "<< flush;
		check(node->right);
	}
}

void memfree(Node *node) // deleteing using Post oreder traversl
{
	if(node==NIL)
		{}
	else
	{
		memfree(node->left);
		memfree(node->right);
		free(node);
	}
}


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
		if(vals=="N")
		{
			vector<int> vect;
			if(root!=NIL)
			{memfree(root);
				root=NIL;
			}
			while(iss>>vals)
			{
				int val=stoi(vals);
				vect.push_back(val);
			}
			int size=vect.size(); // total number of number to be entered
			for(int i=0; i<size ;i++)
			{
				if (root==NIL)
					{
						root=insert(vect[i]);
					}
				else 
				{
					insert(vect[i]);
				}
			}
			//check(root);	

		}
		else if(vals == "P")
		{
			Preorder(root);
			cout << endl;
		}
		else if(vals=="-")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *z = search(root,val);
			deletenode(z);
			//check(root);
		}
		else if(vals=="+")
		{
			iss>>vals;
			int val=stoi(vals); // k is to be inserted
			//Number ins(k);
			insert(val);
		}
		else if(vals==">")
		{
			iss>>vals;
			int val=stoi(vals);
			//cout << " val is : " << val << endl;
			Node *temp=root;
			Node *p=temp;
			int a=0;
			while(temp!=NIL)
			{
				if(temp->key>val)
					{
						//cout << " temp->key smaller is : " << temp->key << endl;
						//cout << " val is : " << val << endl;
						p=temp;
						temp=temp->left;
						a=0;
					}
				else if(temp->key<val)
					{//cout << " temp->key greater is : " << temp->key << endl;
					//	cout << " val is : " << val << endl;
						p=temp;temp=temp->right;a=1;}
				else if(temp->key==val)
					{
					//cout << " temp->key equal is : " << temp->key << endl;
						//cout << " val is : " << val << endl;
						break;}
			}
			if(temp==NIL)
			{
				//cout << "val of a is : "<< a<< endl;
				if(a==0)
				{
					cout<<p->key<<endl;
				}
				if(a==1)
				{
					Node *ans=succesor(p,root);
					//cout << " Returned node is : " << ans << endl;
					if(ans==NULL)
						{cout << "-1" << endl;}
					else
						{cout<<ans->key<<endl;}
				}


			}

			//cout << "heer" << endl;
			if(temp!=NIL)
				{//cout << "inside else loop " << endl;
					Node *ans=succesor(temp,root);
					if(ans==NULL)
						{cout << "-1" << endl;}
					else
					{cout << ans->key << endl;}
				}


		}
		else if(vals=="S")
		{
			iss>>vals;
			int val=stoi(vals);
			find(val,root);
		}
		else if(vals == "C")
		{
			iss>>vals;
			int val=stoi(vals);
			Node *temp=search(root,val);
			if(temp==NIL)
				{cout << "-1" << endl;}
			else
			{
				if(temp->left==NIL && temp->right==NIL)
				{cout <<"L B L B" <<endl;}
				else if(temp->left==NIL && temp->right!=NIL)
				{if(temp->right->color==0)
					{cout <<"L B "  << temp->right->key << " B"<< endl;}
					else
						{cout <<"L B "  << temp->right->key << " R"<< endl;}
				}
				else if(temp->left!=NIL && temp->right==NIL)
				{
					if(temp->left->color==0)
					{cout <<temp->left->key << " B " << "L B"<< endl;}
					else
						{cout <<temp->left->key << " R " << "L B"<< endl;}
				}
				else
				{
					if(temp->left->color==0 && temp->right->color==0)
					{cout <<temp->left->key << " B "  << temp->right->key << " B"<< endl;}
					else if(temp->left->color!=0 && temp->right->color==0)
					{cout <<temp->left->key << " R "  << temp->right->key << " B"<< endl;}
					else if(temp->left->color==0 && temp->right->color!=0)
					{cout <<temp->left->key << " B "  << temp->right->key << " R"<< endl;}
					else if(temp->left->color!=0 && temp->right->color!=0)
					{cout <<temp->left->key << " R "  << temp->right->key << " R"<< endl;}
				}

			}

		}

	}
}
