#include <bits/stdc++.h>

using namespace std;

int counter=1;

const int inf=200;
typedef struct listik
{
    int sizeofcond,sizeofres;
    char cond [inf], res [inf];
    listik * next_rule;
} listn, *listp;

bool equell (char a[inf],char b[inf],int sizeofch,int diff)
{
     for (int i=0;i<sizeofch;i++)
        if (a[i+diff]!=b[i])
            return false;
   // cout<<"horay";
     return true;
}

void NAM(char inp[inf],int &sizeofinp,listp rules)
{
    listp rule=rules;
    bool flag=0,flagok=0;

    while (!flag)
    {

        while (rule->next_rule!=nullptr)
        {
            for (int y=0;y<sizeofinp;y++)
            {
                cout<<inp[y];
            }
            cout<<"No of rule: "<<counter-1;
            cout<<'\n';
            int i=0;
            flagok=0;
            for (int i=0;i<sizeofinp-rule->sizeofcond+1;i++)
            {

                if(equell(inp,rule->cond,rule->sizeofcond,i))
                {
                    flagok=1;
                    counter=1;
                    if (rule->res[0]=='#')
                    {
                        flag=true;
                        if (rule->sizeofcond<rule->sizeofres-1)
                            for(int j=sizeofinp-1;j>=i;j--)
                                inp[j+rule->sizeofres-1-rule->sizeofcond]=inp[j];
                        if (rule->sizeofcond>rule->sizeofres-1)
                            for(int j=i+rule->sizeofcond-1;j<sizeofinp;j++)
                                inp[j-rule->sizeofcond+rule->sizeofres-1]=inp[j];
                        for(int k=i;k<i+rule->sizeofres-1;k++)
                            inp[k]=rule->res[k-i+1];
                        sizeofinp+=(rule->sizeofres-1-rule->sizeofcond);


                    }
                    else
                    {
                        if (rule->sizeofcond<rule->sizeofres)
                            for(int j=sizeofinp-1;j>=i;j--)
                                inp[j+rule->sizeofres-rule->sizeofcond]=inp[j];
                        if (rule->sizeofcond>rule->sizeofres)
                            for(int j=i+rule->sizeofcond-1;j<sizeofinp;j++)
                                inp[j-rule->sizeofcond+rule->sizeofres]=inp[j];
                        for(int k=i;k<i+rule->sizeofres;k++)
                            inp[k]=rule->res[k-i];
                        sizeofinp+=(rule->sizeofres-rule->sizeofcond);
                    }
                break;

                }
            }
            if (flagok)
                rule=rules;
            else
                rule=rule->next_rule;
            flagok=0;
            counter++;
            if (flag)
                break;
        }
    }

}
int main()
{
    freopen("input.txt","r",stdin);
    char maininput[inf];
    int sizeofinput,n;
    cin>>n;
    listp first, prev, curr;
    first=new listn;
    int numofruls;
 //   cout<<"1st rule ";
    cin>>first->sizeofcond>>first->sizeofres;
    for (int i=0;i<first->sizeofcond;i++)
        cin>>first->cond[i];
    for (int i=0;i<first->sizeofres;i++)
        cin>>first->res[i];
    prev=first;
    for(int i=1;i<n;i++)
    {
        //cout<<"nextrule ";
        curr= new listn;
        cin>>curr->sizeofcond>>curr->sizeofres;
        for (int i=0;i<curr->sizeofcond;i++)
            cin>>curr->cond[i];
        for (int i=0;i<curr->sizeofres;i++)
            cin>>curr->res[i];
        prev->next_rule=curr;
        prev=curr;
    }
    curr=new listn;
    prev->next_rule=curr;
    curr->next_rule=nullptr;
    //cout<<"input";

    cin>>sizeofinput;
    //{
        for (int i=0;i<sizeofinput;i++)
            cin>>maininput[i];
        //cout<<"algoGO";
        NAM (maininput,sizeofinput,first);
        cout<<'\n';

        for (int i=0;i<sizeofinput;i++)
            cout<<maininput[i];
        //cout<<"input";

    //}

    return 0;

}
