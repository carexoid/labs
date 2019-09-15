#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long numb,n;
    FILE *arr=fopen ("C:\\Users\\osoka\\Desktop\\Универ\\2_семестр\\Прога\\Лабы\\Lab_2\\2\\array.bin","w");
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>numb;
        fwrite(&numb,sizeof(long long),1,arr);
    }
    fclose(arr);
    return 0;
}
