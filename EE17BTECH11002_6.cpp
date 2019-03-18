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
    int val;
    struct node*pred=NULL;
    struct node *next;
    int wieght;
    int distance=100000;
    int id;
}Node;

Node* heap[1000000]; //heap will be indexed from 1
int heapsize;

int parent(int i)
{
    return i/2;
}

int left(int i)
{
    return 2*i;
}

int right(int i)
{
    return 2*i+1;
}

void swap(Node **x,Node **y)
{
    Node *temp=*x;
    *x=*y;
    *y=temp;
}


void minheapify(Node* a[],int i)
{
    int l=left(i);
    int r=right(i);
    int smallest=i;
    if(l<=heapsize && a[l]->distance < a[i]->distance)
    {
        smallest=l;
    }
    else if(l<=heapsize && a[l]->distance > a[i]->distance)
    {
        smallest=i;
    }
    if(r<=heapsize && a[r]->distance < a[smallest]->distance )
        {
            smallest=r;
        }

    if(smallest!=i)
    {
        swap(&a[i],&a[smallest]);
        minheapify(a,smallest);
    }
    
}

void buidMinHeap(Node* a[])
{
    int length=heapsize;
    for(int i=(length/2);i>=1;i--)
        {
            minheapify(a,i);
        }
}

Node* extractmin(Node* a[])
{
    if(heapsize<1)
        {}
    else
    {
        Node* min=a[1];
        a[1]=a[heapsize];
        heapsize--;
        minheapify(a,1);
        return min;
    }

}

void pheap(Node* a[])
{
    for(int i=1;i<=heapsize;i++)
    {
    //  cout << "val of Node is : " <<heap[i]->val << " weight of Node is : " << heap[i]->wieght << " distance of Node is : " << heap[i]->distance << " nODE ID : " << heap[i]->id<< endl;      
    }
    //cout << endl;
}


void dekey(Node* a[],int index,int newdis)
{
    ///cout << " index in deckey is " << index << " Value is : " << a[index]->val<< " new dis " << newdis << endl;
    //cout << " a.index in deckey " << a[index]->distance << endl;
    if(newdis>a[index]->distance)
        {}
    else
    {
        a[index]->distance=newdis;
        int i=index;
        while(i>1 && a[parent(i)]->distance > a[i]->distance)
        {
        //  cout << "parent is : " <<a[parent(i)]->distance << " node is : " << a[i]->distance << endl; 
            swap(&a[i],&a[parent(i)]);
            i=parent(i);
        }

    }
}

/*void heapinsert(Node a[],int key)
{
    heapsize++;
    a[heapsize].val=INT_MAX;
    dekey(a,heapsize,key);
}*/

typedef struct List
{
    struct node *head;
}list;

class Graph
{
public:
    int v;
    list *arr;
    Graph(int ver)
    {
        v=ver;
        heapsize=ver;
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

    void addEdge(int v,int w,int i,list *arr)
    {
   //   cout << "v inside func : " << v << endl;
    //  cout << "w inside func : " << w << endl;
    //  cout << "i inside func : " << v << endl;
        Node *tem=listnode(v);
        tem->wieght=w;

        if(arr[i].head==NULL)
        {
      //    cout << "inside if " << endl;
            arr[i].head=tem;
        }
        else
        {
        //  cout << "inside else" << endl;
            Node *mover=arr[i].head;
            while(mover->next!=NULL)
            {
                mover=mover->next;
            }
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
        int p;          
        int we; //weight of u,v
        if(u==w)
            {cout << "-1" << endl;}
        else
        {
            for(int i=1;i<v+1;i++)
            {
            if(arr[i].head->val==u)
            {
                Node *temp=arr[i].head;
                while(temp!=NULL)
                {
                    if(temp->val==w)
                        {
                            p=1;
                            we=temp->wieght;
                            break;
                        }
                    else
                        {
                            temp=temp->next;
                            p=0;
                        }
                    }
                    break;   
                }
             }
            if(p==1)
            {cout << we << endl;}
            else
            {cout << "-1" << endl;}

        }
        
    }

    int check(vector<Node*> &v,Node *c)
    {
        if(c==NULL)
            {return 0;}
        else
        {
    //  cout << "insisde checcker " << endl;
        for(int i=0;i<v.size();i++)
        {
    //      cout << " inside for " << "value of i : " << i << endl;
            if(v[i]->val==c->val)
                {return 1;}

        }
        return 0;

        }
    }

    void Dijkstras(int u)
    {

        Node *s;
    //  cout << " HHHHH " << endl;
        for(int i=1;i<v+1;i++)
        {
            if(arr[i].head->val==u)
                {s=arr[i].head;
                    break;}
        }
        heapsize=v;
        s->distance=0;
        for(int i=1;i<=heapsize;i++)
        {
            arr[i].head->id=i;
            heap[i]=(arr[i].head); //arr.head points to a node heap[i]=&arr[i].head;
        }
        buidMinHeap(heap);//*heap
        //pheap(heap);
        vector<Node*> vect;
        while(heapsize!=0)
            {
                Node* U=extractmin(heap);
            //  cout << "heap after extraction : " << endl;
            //  pheap(heap);
            //  cout << "val of Node is : " <<U->val << " weight of Node is : " << U->wieght << " distance of Node is : " << U->distance<< endl;        
                vect.push_back(U);
                Node *temp=U;
                for(int i=1;i<v+1;i++)
                {
                    if(arr[i].head->val==temp->val)
                    {
                //      cout << " inside for-if " << endl;
                //      cout << "arr: " << arr[i].head->val << endl;
                        temp=temp->next;
                        bool c=check(vect,temp);
                //      cout << "result of check is "<< c << endl;
                        while(c==1 && temp!=NULL)
                        {
                            temp=temp->next;
                            c=check(vect,temp);
                        }

                        while(temp!=NULL)
                        {
                            for(int j=1;j<v+1;j++)
                            {
                                if(arr[j].head->val==temp->val)
                                {
                                    if(U->distance+temp->wieght < arr[j].head->distance);
                                    {
                                    //  cout << "u.dis " << U->distance << " temp->wieght " << temp->wieght << " arr.dis " << arr[j].head->distance << endl;
                                        int index;
                                        for(index=1;index<=heapsize;index++)
                                        {
                                            if(heap[index]->id==arr[j].head->id)
                                            {break;}
                                        }
                                    //  cout << "index is : " << index << endl;
                                        int qw=U->distance+temp->wieght;
                                        //arr[j].head->distance=U.distance+temp->wieght;
                                    //  cout << "u.dis " << U->distance << " temp->wieght " << temp->wieght << " arr.dis " << arr[j].head->distance << endl;
                                        dekey(heap,index,qw);
//                                          cout << "u.dis " << U->distance << " temp->wieght " << temp->wieght << " arr.dis " << arr[j].head->distance << endl;

                                        //pheap(heap);

                                        for(int l=1;l<v+1;l++)
                                        {
                                            if(arr[l].head->val==temp->val)
                                                {
                                                    int q;
                                                    for( q=0;q<vect.size();q++)
                                                    {
                                                        if(vect[q]==arr[l].head)
                                                            {break;}
                                                    }
                                                    if(q==vect.size())
                                                    {   
                                                        arr[l].head->pred=U;
                                    //                  cout << "pred of : "<< arr[l].head->val << " is : "<< arr[l].head->pred << " VAL IS : " <<arr[l].head->pred->val<<endl; 
                                                    }
                                                }

                                        }

                                        temp->pred=U;
                                    }
                                    break;
                                }
                            }
                            temp=temp->next;
                        bool c=check(vect,temp);
                //      cout << "result of check is "<< c << endl;
                        while(c==1 && temp!=NULL)
                        {
                            temp=temp->next;
                            c=check(vect,temp);
                        }

                        }
                        break;
                    }
                }
            }

        for (int i=0;i<vect.size();i++)
        {
            if(vect[i]->distance==100000)
            {cout <<vect[i]->val<<" "<<"-1"<<endl;}
            else
            {cout <<vect[i]->val<<" "<<vect[i]->distance<<endl;} 
        }


    }

    void dijkstras(int u)
    {

        Node *s;
        for(int i=1;i<v+1;i++)
        {
            if(arr[i].head->val==u)
                {s=arr[i].head;
                    break;}
        }
        heapsize=v;
        s->distance=0;
        for(int i=1;i<=heapsize;i++)
        {
            arr[i].head->id=i;
            heap[i]=(arr[i].head); //arr.head points to a node heap[i]=&arr[i].head;
        }
        buidMinHeap(heap);//*heap
        //pheap(heap);
        vector<Node*> vect;
        while(heapsize!=0)
            {
                Node* U=extractmin(heap);
    //          cout << "val of Node is : " <<U->val << " weight of Node is : " << U->wieght << " distance of Node is : " << U->distance<< endl;        
    //          cout << endl;
    //          cout << "haep after extraction of " << U->val << endl;
                //pheap(heap);
                vect.push_back(U);
                Node *temp=U;
                for(int i=1;i<v+1;i++)
                {
                    if(arr[i].head->val==temp->val)
                    {
                //      cout << " inside for-if " << endl;
                //      cout << "arr: " << arr[i].head->val << endl;
                        temp=temp->next;
                        bool c=check(vect,temp);
                //      cout << "result of check is "<< c << endl;
                        while(c==1 && temp!=NULL)
                        {
                            temp=temp->next;
                            c=check(vect,temp);
                        }
                        //cout << "val of temp->next is : " <<temp->val << " weight of Node is : " << temp->wieght << " distance of Node is : " << temp->distance<< endl;       

                        while(temp!=NULL)
                        {
                            for(int j=1;j<v+1;j++)
                            {
                                if(arr[j].head->val==temp->val)
                                {
                                    if(U->distance+temp->wieght < arr[j].head->distance);
                                    {
                                //      cout << "u.dis " << U->distance << " temp->wieght " << temp->wieght << " arr.dis " << arr[j].head->distance << endl;
                                        int index;
                                        for(index=1;index<=heapsize;index++)
                                        {
                                            if(heap[index]->id==arr[j].head->id)
                                            {break;}
                                        }
                                //      cout << "index is : " << index << endl;
                                        int qw=U->distance+temp->wieght;
                                        //arr[j].head->distance=U.distance+temp->wieght;
                                //      cout << "u.dis " << U->distance << " temp->wieght " << temp->wieght << " arr.dis " << arr[j].head->distance << endl;
                                        dekey(heap,index,qw);
                                        //cout << "u.dis " << U->distance << " temp->wieght " << temp->wieght << " arr.dis " << arr[j].head->distance << endl;

                                        //pheap(heap);
                                        for(int l=1;l<v+1;l++)
                                        {
                                            if(arr[l].head->val==temp->val)
                                                {
                                                    int q;
                                                    for( q=0;q<vect.size();q++)
                                                    {
                                                        if(vect[q]==arr[l].head)
                                                            {break;}
                                                    }
                                                    if(q==vect.size())
                                                    {   
                                                        arr[l].head->pred=U;
                                            //          cout << "pred of : "<< arr[l].head->val << " is : "<< arr[l].head->pred << " VAL IS : " <<arr[l].head->pred->val<<endl; 
                                                    }
                                                }

                                        }
                                        temp->pred=U;
                                    }
                                    break;
                                }
                            }
                            temp=temp->next;
                        bool c=check(vect,temp);
//                      cout << "result of check is "<< c << endl;
                        while(c==1 && temp!=NULL)
                        {
                            temp=temp->next;
                            c=check(vect,temp);
                        }


                        }
                        break;
                    }
                }
            }

    }

    void path(int a,int b,int st)
    {


        vector<int> vect;
        if(st!=a)
        {dijkstras(a);}
        /*for(int i=v;i>1;i--)
        {
            cout <<arr[i].head->val << " " <<  arr[i].head->pred << "VAL OF PRED IS : " << arr[i].head->pred->val<< endl;
        }
        cout <<arr[1].head->val << " " <<  arr[1].head->pred << endl;*/

        Node *cv;
        for(int k=1;k<v+1;k++)
        {
            //cout << "for" << endl;
            if(arr[k].head->val==b)
            {
                cv=arr[k].head;
                break;
            }
            
        }
        //cout << "cv ->pred is " << cv->pred->val << endl;
        if(cv->pred==NULL)
            {
                cout << "-1" << flush;
         //     cout << "if" << endl;
            }                        
        else
        {
       //   cout << "else" << endl;
            vect.push_back(cv->distance);
            while(cv!=NULL)
            {
                //cout << cv->val << endl;
                //cout << "while" << endl;
                vect.push_back(cv->val);
                cv=cv->pred;
            }
            cout << vect[0] << " "<< flush;
            for (int k=vect.size()-1;k>0;k--)
            {
                cout << vect[k] << " "<<flush;
            }
        }

    }

};



int main()
{
    int stored;
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
            
            iss>> vals;
            int ver=stoi(vals);
            p=new Graph(ver);
            for(int j=1;j<ver+1;j++)
            {
                p->addEdge(j,0,j,p->arr);
            }
        }
        else if(vals=="E")
        {
            iss>>vals;
            int u=stoi(vals);
            //cout << " u : " << u << endl;
            //cout << " i : " << i << endl;
            //p->addEdge(u,0,u,p->arr);
            while(iss>>vals)
            {
                int v=stoi(vals);
              //    cout << " v : " << v << endl; 
                iss>>vals;
                int w=stoi(vals);
               // cout << " w : " << w << endl;
               // cout << " i : " << i << endl; 
                p->addEdge(v,w,u,p->arr);
            }
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
        else if(vals == "D")
        {
            for (int k=1;k<p->v+1;k++)
            {
                p->arr[k].head->distance=100000;
            }
            for (int k=1;k<p->v+1;k++)
            {
                p->arr[k].head->pred=NULL;
            }

            iss>>vals;
            int u=stoi(vals);
            p-> Dijkstras(u);
            stored=u;

        }
        else if(vals=="P")
        {
            iss>>vals;
            int u=stoi(vals);
            if(u!=stored)
                {
                    for (int k=1;k<p->v+1;k++)
                    {
                        p->arr[k].head->distance=100000;
                    }
                    for (int k=1;k<p->v+1;k++)
                    {
                        p->arr[k].head->pred=NULL;
                    }

                }
            iss>>vals;
            int v=stoi(vals);
            if(u==v)
                {cout << "0 " << u << flush;}
            else
            {
                p->path(u,v,stored);
            }
            cout << endl;
            
        }
    }
}