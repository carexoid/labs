#include <bits/stdc++.h>

using namespace std;

const int inf=1000;

struct mystack
{
    int mas[inf];
    int topi=0;
    void push(int val)
    {
        topi++;
        mas[topi]=val;
    }
    void pop ()
    {
        topi--;
    }
    int top()
    {
        return mas[topi];
    }
    int siz()
    {
        return topi+1;
    }

};

vector<string> hanoj(int num)
{
    mystack prev, curr;
    vector<int> pos;
    vector<string> res;
    string s;
    int height;
    pos.resize(num+1);
    for (int i=1;i<=num;i++)
    {
        curr=prev;
        curr.push(i);

        height=prev.siz();
        for (int j=0;j<height;j++)
        {
            curr.push(prev.top());
            prev.pop();
        }
        prev=curr;
    }
    height=prev.siz();
    for (int i=0;i<height;i++)
    {
        int val=prev.top();
        s="";
        if (pos[val]==0)
            s+="1";
        else if (pos[val]==1)
            s+="2";
        else
            s+="3";
        s+=" -> ";
        if (val%2)
            pos[val]=(pos[val]+1)%3;
        else
            pos[val]=(pos[val]+2)%3;
        if (pos[val]==0)
            s+="1";
        else if (pos[val]==1)
            s+="2";
        else
            s+="3";
        res.push_back(s);
        prev.pop();

    }

    return res;


}

int main()
{
    int num;
    vector<string> res;
    cin>>num;
    res = hanoj(num);
    int siz=res.size();
    for (int i=0;i<siz;i++)
    {
        cout<<res[i]<<" | ";
    }
    cout<<'\n';
    return 0;
}
