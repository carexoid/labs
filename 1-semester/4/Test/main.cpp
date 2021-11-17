#include <bits/stdc++.h>

using namespace std;

int main()
{
    FILE *filin;
    char c;
    filin=fopen("input.txt","rt");
    while(!feof(filin))
    {
        fscanf(filin,"%c",&c);
        cout<<c;
    }
    cout << "Hello world!" << endl;
    cout<<'|'<<"jgjgj";
    return 0;
}
