#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
typedef struct node
{
    int val;
    struct node* next;
    string col="white";
    int d=10000;
    struct node *pre=NULL;
}Node;
    
typedef struct qnode
{
    Node *p;
    struct qnode *next;
}Qnode;

struct Queue 
{ 
    Qnode *front, *rear; 
};

Qnode* newNode(Node *k) 
{ 
    Qnode *temp = new Qnode; 
    temp->p = k; 
    temp->next = NULL; 
    return temp;  
} 
  
struct Queue *createQueue() 
{ 
    struct Queue *q = new struct Queue; 
    q->front = q->rear = NULL; 
    return q; 
} 
  
void enQueue(struct Queue *q, Node* k) 
{ 
    Qnode *temp = newNode(k); 
  
    if (q->rear == NULL) 
    { 
       q->front = q->rear = temp; 
       return; 
    } 
  
    q->rear->next = temp; 
    q->rear = temp; 
} 
  
Qnode *deQueue(struct Queue *q) 
{ 
    if (q->front == NULL) 
       {return NULL;} 
  
    Qnode *temp = q->front; 
    q->front = q->front->next; 
    if (q->front == NULL) 
       {q->rear = NULL;} 
    return temp; 
}

bool isEmpty(struct Queue *q)
{
    if(q->front==NULL && q->rear==NULL)
        {return true;}
    else
        {return false;}
}

typedef struct List
{
    struct node *head;
}list;

class Graph
{

public:
    int v;
    list *arr;
    int stored;
    Graph(int ver)
    {
        v=ver;
        arr=new list[v+1];
        for (int i = 0; i < v+1; ++i)
             {arr[i].head = NULL;}


    }
    ~Graph()
    {
        delete[] arr;
    }

    Node *listnode(int v)
    {
        Node *temp=new Node;
        temp->val=v;
        temp->next=NULL;
        return temp;
    }

    void correcting()
    {
        for(int i=1;i<v+1;i++)
        {
            arr[i].head=NULL;
        }
    }

    void addEdge(int v,int i,list *arr)
    {
       //cout << "$$" << endl;
        Node *tem=listnode(v);

      //  cout << "2" << endl;
        if(arr[i].head==NULL)
        {
        //    cout << "3" << endl;
            arr[i].head=tem;
          //  cout << "4" << endl;
        }
        else
        {
            //cout << "5" << endl;
            Node *mover=arr[i].head;
   //         cout << "6" << endl;
            while(mover->next!=NULL)
            {
     //           cout << "7" << endl;
                mover=mover->next;
       //         cout << "8" << endl;
            }
         //   cout << "9" << endl;
            mover->next=tem;
        }
    }
    void printg()
    {
        int k;
        for(k=1;k<v+1;k++)
        {
            Node *crawl=arr[k].head;
            while (crawl)
            {
                cout<<"-> "<<crawl->val;
                crawl = crawl->next;
            }
            cout<<endl;

        }
    }

    void exist(int u,int w)
    {
    //    cout << "#1" << endl;
        int p;
            
            
          //      cout << "inside while 1" << endl;
        for(int i=1;i<v+1;i++)
        {
    //        cout << "val of i : " << i << endl;
    //        cout << "inside for" << endl;
            if(arr[i].head->val==u)
            {
      //          cout << "inside if" << endl;
                Node *temp=arr[i].head;
      //          cout << "value of temp->val : " << temp->val << " and index is i= " << i << endl;
                while(temp!=NULL)
                {
        //           cout << "value of temp is : "<< temp->val << endl;
        //            cout << "inside while 2" << endl;
                    if(temp->val==w)
                        {
        //                    cout << "inside if loop " << endl;
          //                  cout << "inside if 2" << endl;
                            //cout << "1" << endl;
                            p=1;
                            break;

                        }
                    else
                        {
        //                    cout << "inside else " << endl;
            //                cout << "inside else" << endl;
                            temp=temp->next;
                        }
                }
          //      cout << "bef brk" << endl;
                break;
                
            }

    }
    if(p==1)
    {cout << "1" << endl;}
    else
        {cout << "0" << endl;}
        
        
        
    }

    void BFS(int u)
    {
       // cout << "1" << endl;
        Node *s;
        for(int i=1;i<v+1;i++)
        {
         //   cout << "inside for" << endl;
            if(arr[i].head->val==u)
            {
                s=arr[i].head;
                break;
            }
        }
      //  cout << s << endl;
        s->col="grey";
        s->d=0;
        struct Queue *q=createQueue();
        enQueue(q,s);
        //cout << "hey" << endl;
        while(!isEmpty(q))
        {
            
          //  cout << "inside while" << endl;
            Qnode *u=deQueue(q);
            cout << u->p->val << " " << flush;
            Node *temp=u->p;

            while(temp!=NULL)
            {
                for (int i=1;i<v+1;i++)
                {
                    if(temp->val==arr[i].head->val)
                    {
                        temp->col=arr[i].head->col;
                        break;
                    }
                }
                if(temp->col=="white")
                {
           //         cout << "inside while while if" << endl;

                    for (int i=1;i<v+1;i++)
                    {
                        if(temp->val==arr[i].head->val)
                        {
                            arr[i].head->col="grey";
                            arr[i].head->d=u->p->d+1;
                            arr[i].head->pre=u->p;
                            enQueue(q,arr[i].head);
                            break;
                        }
                    }
                    //enQueue(q,temp);

                }
                temp=temp->next;
            }

            u->p->col="black";
        }
        for (int i=1;i<v+1;i++)
        {
            arr[i].head->col="white";
        }

    }

    void bfs(int u)
    {
       // cout << "1" << endl;
        Node *s;
        for(int i=1;i<v+1;i++)
        {

            if(arr[i].head->val==u)
            {
                s=arr[i].head;
                break;
            }
        }
      //  cout << s << endl;
        s->col="grey";
        s->d=0;
        struct Queue *q=createQueue();
        enQueue(q,s);
        //cout << "hey" << endl;
        while(!isEmpty(q))
        {
            
          //  cout << "inside while" << endl;
            Qnode *u=deQueue(q);
           // cout << u->p->val << " " << flush;
            Node *temp=u->p;

            while(temp!=NULL)
            {
               // cout << "inside while while" << endl;
                for (int i=1;i<v+1;i++)
                {
                    if(temp->val==arr[i].head->val)
                    {
                        temp->col=arr[i].head->col;
                        break;
                    }
                }
                if(temp->col=="white")
                {
           //         cout << "inside while while if" << endl;

                    for (int i=1;i<v+1;i++)
                    {
                        if(temp->val==arr[i].head->val)
                        {
                            arr[i].head->col="grey";
                            arr[i].head->d=u->p->d+1;
                            arr[i].head->pre=u->p;
                            enQueue(q,arr[i].head);
                            break;
                        }
                    }
                    //enQueue(q,temp);

                }
                temp=temp->next;
            }

            u->p->col="black";
        }
        for (int i=1;i<v+1;i++)
        {
            arr[i].head->col="white";
        }

    }


    void shortestPath(int s,int w)
    {
        vector<int> vect;
        if(s!=stored)
        {   
            //cout << "inside if" << endl;
            for (int i=1;i<v+1;i++)
            {
                arr[i].head->pre=NULL;
            }
            bfs(s);
        }
        stored=s;
        Node *cv;
        for(int i=1;i<v+1;i++)
        {
            if(arr[i].head->val==w)
                {
                    cv=arr[i].head;
                    break;
                }
        }
        //cout << " val of cv is : "<<cv->val << endl;
        if(cv->pre==NULL)
            {cout << "-1" << flush;}
        else
        {
            while(cv!=NULL)
            {
                vect.push_back(cv->val);
                cv=cv->pre;
            }

            for (int k=vect.size()-1;k>=0;k--)
            {
                cout << vect[k] << " "<<flush;
            }
        }
    }


};

void freemem(Graph *obj)
{
  int v=obj->v;

    for (int i = 0; i <v+1 ; ++i)
    {
        Node *head=obj->arr[i].head;
        while(head!=nullptr)
        {
            Node *temp;
            temp=head;
            free(temp);
            head=head->next;
        }
  /* code */
    }

}


int main()
{
    int i=1;
    int delchecker=0;
    while(!cin.eof())
    {
        string s;
        getline(cin,s);
        istringstream iss;
        iss.str(s);
        string vals;
        iss>>vals;
        Graph *p;
        
        
        if(vals=="N")
        {
            if(delchecker==1)
            {
                //cout << "insisde deleter" << endl;
                //p->delet();
                freemem(p);

            }

            iss>> vals;
            int ver=stoi(vals);
            p=new Graph(ver);
            //cout << delchecker << endl;
            delchecker=1;
            //cout << delchecker << endl;
            //cout << &g << endl;
            //cout << p << endl;
        }
        else if(vals=="E")
        {

            while(iss>>vals)
            {
                int u=stoi(vals);

                p->addEdge(u,i,p->arr);
            }
            i++;
        }
        else if(vals=="PR")
        {
            p->printg();
        }
        else if(vals == "?")
        {
            //cout << "1" << endl;
            iss>>vals;
            //cout << "1" << endl;
            int u=stoi(vals);
            //cout << "value of u : " << u << endl;
            //cout << "1" << endl;
            iss>>vals;
            //cout << "1" << endl;
            int v=stoi(vals);
            //cout << "value of v : " << v << endl;
            //cout << "1" << endl;
            p->exist(u,v);
            //cout << "1" << endl;
        }
        else if(vals == "B")
        {
            iss>>vals;
            int u=stoi(vals);
            p->BFS(u);
            cout << endl;

        }
        else if(vals=="P")
        {
            iss>>vals;
            int s=stoi(vals);
            iss>>vals;
            int w=stoi(vals);
            p->shortestPath(s,w);
            cout << endl;
            

        }
    }
}