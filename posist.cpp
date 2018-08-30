#include <bits/stdc++.h>
using namespace std;

void getData(void);
class TimeStamp{

    public:

    string date_time;

    void put(string date_time1)
    {
        date_time=date_time1;
    }

    string getdate_time()
    {
        return date_time;
    }

};

struct DataMyNode{

 string name;
 string password;
 string algorithm;
 float val;
};

struct MyNode{

  TimeStamp date_time;
  struct DataMyNode* data;
  unsigned int nNumber;
  unsigned int MyNodeId;
  struct MyNode *ref;
  vector<struct MyNode*> child;
};

map<int,struct MyNode*> all;

static int number=0;

string encryption(string val){
    char key ='H';
    string output = val;

    for (int i = 0; i < val.size(); i++)
        output[i] = val[i] ^ key;

    return output;
}

string date_time()
{
     time_t tt;
    struct tm * ti;
    time (&tt);
    ti = localtime(&tt);

    return asctime(ti);
}

unsigned int unique()
{
    return rand();
}

void getData(int head,vector<struct MyNode*> headMyNodes)
{

    int size = headMyNodes.size();
    string name,password,algorithm="qwerty";
    float val;

    struct MyNode *MyNode1 = new MyNode();
    struct DataMyNode *data1=new DataMyNode();
    string date = date_time();
    TimeStamp time;
    time.put(date);
    MyNode1->date_time=time;
    cout<<"Enter Name:\n";
    cin>>name;
    data1->name=encryption(name);
    cout<<"Enter password:\n";
    cin>>password;
    data1->password=encryption(password);

    data1->algorithm=encryption(algorithm);
    cout<<"Enter val:\n";
    cin>>val;
    data1->val=val;

    MyNode1->data=data1;
    MyNode1->nNumber=++number;
    MyNode1->MyNodeId=unique();


    if(head==-1)
    {
        MyNode1->ref=NULL;
        headMyNodes.push_back(MyNode1);
    }
    else
    {
        all[head]->child.push_back(MyNode1);
        MyNode1->ref=all[head];

    }

    all[number]=MyNode1;
    return;
}

bool verification(string password,string algorithm)
{
        string password1=encryption(password);
        string algorithm1=encryption("qwerty");

        map<int,struct MyNode*>::iterator it=all.begin();
        int flag=0;

        for(;it!=all.end(); it++)
        {
            if(it->second->data->password==password1 && it->second->data->algorithm==algorithm1)
            {
                flag=1;
                cout<<encryption(it->second->data->name)<<endl;

                break;
            }
        }

        if(flag==1)
        return true;

        return false;
}

int c=0;

void longest(struct MyNode* root,int &ma)
{
    	if(root==NULL)
            return;

 		   c++;

    		for(int i=0; i<root->child.size(); i++)
            {
                longest(root->child[i],ma);
            }

    	if(c>ma)
            ma=c;
}

void levels(struct MyNode* root,int c,int &ma)
{
    	if(root==NULL)
            return;

    		for(int i=0; i<root->child.size(); i++)
            {
                levels(root->child[i],c+1,ma);
            }

    	if(c>ma)
            ma=c;
}

int main()
{
    vector<struct MyNode *> headMyNodes;


    while(1)
    {
		cout<<"1 : Create new MyNode\n";
		cout<<"2 : Create multi-set from first MyNode\n";
		cout<<"3 : Create new MyNode to any set of MyNode\n";
		cout<<"4 : encryption DataMyNode\n";
		cout<<"5 : verification Owner\n";
		cout<<"6 : Break MyNode\n";
		cout<<"7 : Change Owner\n";
		cout<<"8 : Longest chain\n";
		cout<<"9 : Longest chain of Sub-MyNode\n";
		cout<<"11 : Exit"<<endl<<endl;
        int num;
        cout<<"\nEnter choice:\n";
        cin>>num;


        if(num==11)
        break;



        if(num==1)
        {
            //cout<<"hi";
            getData(-1,headMyNodes);
        }

        if(num==2)
        {
            cout<<"enter no. of sets\n";
            int sets;
            cin>>sets;

            while(sets--)
            {
                getData(-1,headMyNodes);
            }
        }

        if(num==3)
        {
            int nNum;
            cout<<"enter MyNode number";
            cin>>nNum;

            getData(nNum,headMyNodes);
        }

        if(num==4)
        {
            string password,algorithm;
            cout<<"Enter password + encryptionion Key"<<endl;

            bool k=verification(password,algorithm);
        }

        if(num==5)
        {
            string password,algorithm;
            cout<<"Enter password and algorithm key";

            bool k=verification(password,algorithm);

            if(k)
            cout<<"Verified"<<endl;
            else
            cout<<"Not Verified"<<endl;

            cout<<endl;
        }

        if(num==6)
        {
            int nNum;
            cout<<"enter MyNode number";
            cin>>nNum;
            all.erase(nNum);
        }

        if(num==7)
        {
            int nNum1,nNum2;
            cout<<"enter MyNode number of first MyNode and new owner";
            cin>>nNum1>>nNum2;

            struct MyNode* first=all[nNum1];
            struct MyNode* newowner=all[nNum2];

            first->ref->child.erase(first->child.begin()+nNum1);
            newowner->child.push_back(first);
            first->ref=newowner;
        }

        if(num==8)
        {
            int ma=0;
            c=0;

            for(int i=0; i<headMyNodes.size(); i++)
            	longest(headMyNodes[i],ma);

            cout<<ma<<endl;
        }

    	if(num==9)
        {
            int ma=0;

            for(int i=0; i<headMyNodes.size(); i++)
            	levels(headMyNodes[i],0,ma);

            cout<<ma<<endl;
        }

        if(num==10)
        {
            int nNum1,nNum2;
            cout<<"enter nNumbers of 1 & 2";
            cin>>nNum1>>nNum2;

            struct MyNode* first=all[nNum1];
            struct MyNode* second=all[nNum2];

         
        }

    }

   return 0;
}
