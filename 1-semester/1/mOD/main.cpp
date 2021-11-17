#include <bits/stdc++.h>

using namespace std;

//const int inf=10001;
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if (a.first==b.first)
        return a.second<b.second;
    return a.first<b.first;
}

bool cloc(pair<int,int> a, pair<int,int> b, pair<int,int> c)
{
    return (b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first)<=0;
}

vector< pair<int,int> > answer(vector<pair<int,int> > v)
{
    vector <pair<int,int> > up;
    sort(v.begin(),v.end(),cmp);
    up.push_back(v[0]);
    for(int i=1;i<v.size()-1;i++)
    {
        if(cloc(v[0],v[i],v[v.size()-1]))
        {
            while(up.size()>=2 && !cloc(up[up.size()-2],up[up.size()-1],v[i]))
                up.pop_back();
            up.push_back(v[i]);
        }

    }
    return up;
}
int main()
{
    vector<pair<int,int> > mas,upp;
    int n;
    cin>>n;
    mas.resize(n);
    for(int i=0;i<n;i++)
        cin>>mas[i].first>>mas[i].second;


    sort(mas.begin(),mas.end(),cmp);
    upp=answer(mas);
    int j=0;

    for(int i=0;i<upp.size();i++)
    {
        cout<<upp[i].first<<" "<<upp[i].second<<'\n';
        while(upp[i]!=mas[j])
        {
            j++;

        }


        for(int k=j;k<mas.size()-1;k++)
        {
            mas[k]=mas[k+1];
        }
        mas.pop_back();
    }





    for(int i=mas.size()-1;i>=0;i--)
        cout<<mas[i].first<<" "<<mas[i].second<<'\n';
    cout<<upp[0].first<<" "<<upp[0].second<<'\n';
    return 0;
}
