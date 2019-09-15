#include <bits/stdc++.h>

using namespace std;

FILE *arr=fopen ("C:\\Users\\osoka\\Desktop\\Универ\\2_семестр\\Прога\\Лабы\\Lab_2\\2\\array.bin","r+w");

void mrgs(long long st,long long fin)
{
    //long long c[fin-st+1];
    long long  mid=(st+fin)/2;
    if (st<mid)
        mrgs(st,mid);
    if (mid+1<fin)
        mrgs (mid+1,fin);
    long long i=st;
    long long j=mid+1;
    long long a,b,p;
    long long k=i;

    while (i<=mid && j<=fin)
    {
        fseek(arr,sizeof(long long)*i,0);
        fread(&a,sizeof(long long),1,arr);
        fseek(arr,sizeof(long long)*j,0);
        fread(&b,sizeof(long long),1,arr);

        if(b<=a)
        {

            for (int y=j-1;y>=i;y--)
            {
                fseek(arr,sizeof(long long)*y,0);
                fread(&p,sizeof(long long),1,arr);
                fseek(arr,sizeof(long long)*(y+1),0);
                fwrite (&p,sizeof(long long),1,arr);
            }
            fseek(arr,sizeof(long long)*k,0);
            fwrite(&b,sizeof(long long),1,arr);
            k++;
            j++;
            i++;
            mid++;
        }
        else
        {
            k++;
            i++;
        }

    }
    long long fikt;
    fseek(arr,sizeof(long long)*st,0);
    for (long long i=st;i<=fin;i++)
    {

        fread(&fikt,sizeof(long long),1,arr);
        cout<< fikt <<" ";
    }
    cout<<'\n';

}

int main()
{
    long long fikt,n=0;
    cout<<"input: ";
    while(fread(&fikt,sizeof(long long),1,arr))
    {
        ;
        cout<<fikt<<" ";
        n++;
    }
    cout<<'\n';

    mrgs(0,n-1);
    fseek(arr,0,0);
    cout<<"Res: ";
    for (long long i=0;i<n;i++)
    {
        fread(&fikt,sizeof(long long),1,arr);
        cout<< fikt <<" ";
    }

    cout<<'\n';
    fclose(arr);
    return 0;
}
