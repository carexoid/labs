#include <bits/stdc++.h>

using namespace std;

const int inf=10001;
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if (a.first==b.first)
        return a.second<b.second;
    return a.first<b.first;
}
int main()
{
    pair<int,int> mas[inf];
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>mas[i].first>>mas[i].second;
    sort(mas,mas+n,cmp);

    for(int i=0;i<n;i++)
        cout<<mas[i].first<<" "<<mas[i].second<<'\n';
   /* for(;;)
    {
        system("color a1");
        system("color b1");
        system("color c1");
        system("color d1");
        system("color e1");
        system("color f1");
    }*/
    return 0;
}

