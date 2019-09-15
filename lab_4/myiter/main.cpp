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

void hanoj(int num)
{
    mystack col [3];
    int pos=1;
    col[0].push(100);
    col[1].push(100);
    col[2].push(100);

    for (int i=num;i>0;i--)
        col[0].push(i);
    int num_of_oper=pow(2,num)-1;
    for(int i=0;i<num_of_oper;i++)
    {
        for (int u=0;u<2;u++)
        {
            bool flag=0;
            for (int y=0;y<2;y++)
                if (col[((pos-u+2)%3+y+1)%3].top()>col[(pos-u+2)%3].top())
                {
                    col[((pos-u+2)%3+y+1)%3].push(col[(pos-u+2)%3].top());
                    col[(pos-u+2)%3].pop();
                    cout<<(pos-u+2)%3+1<<" -> ";
                    pos=((pos-u+2)%3+y+1)%3;
                    cout<<pos+1<<" | ";
                    flag=1;
                    break;
                }
            if (flag)
                break;
        }
    }
    cout<<'\n';



}

int main()
{
    int num;
    cin>>num;
    hanoj(num);
    return 0;
}
