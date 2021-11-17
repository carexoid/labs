#include <bits/stdc++.h>

using namespace std;

typedef vector <string> listik;

int getmax(vector<string> input)
{
    unsigned int maxi=0;
    for (int i=0;i<input.size();i++)
        maxi=max(input[i].size(),maxi);
    return maxi;
}

vector<string> bucket_sorter (vector<string> input)
{
    listik res;
    listik mas1[27],mas2[27];
    int maxlen=getmax(input);
    for (int j=0;j<input.size();j++)
    {
        if (input[j].size()<=maxlen)
            mas1[0].push_back(input[j]);
        else
            mas1[input[j][maxlen]-'a'+1].push_back(input[j]);
    }
    for(int i=maxlen-2;i>=0;i--)
    {
        for (int x=0;x<27;x++)
        {
            for (int y=0;y<mas1[x].size();y++)
            {
                if (mas1[x][y].size()<=i)
                    mas2[0].push_back(mas1[x][y]);
                else
                    mas2[mas1[x][y][i]-'a'+1].push_back(mas1[x][y]);
            }
            mas1[x].clear();
        }
        for (int x=0;x<27;x++)
        {
            for (int y=0;y<mas2[x].size();y++)
            {
                mas1[x].push_back(mas2[x][y]);
            }
            mas2[x].clear();
        }
    }
    for (int x=0;x<27;x++)
    {
        for (int y=0;y<mas1[x].size();y++)
        {
            res.push_back(mas1[x][y]);
        }
    }
    return res;


}

int main()
{
    int n;
    listik input,res;
    string s;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        input.push_back(s);
    }
    res=bucket_sorter(input);

    for (int i=0;i<res.size();i++)
        cout<<res[i]<<" ";
    cout<<'\n';
    return 0;
}
