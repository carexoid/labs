#include <bits/stdc++.h>
#include <chrono>
using namespace std;

double sqr_counter_trap(double left, double right,double accuracy, double (*pf)(double))
{
    double s1=0,s2=0;
    int num=10;
    s1=((*pf)(left)+(*pf)(right))/2*(right-left);   //Начальная площадь 1
    double diff=(right-left)/num;
    for(double cou=left;cou<right;cou+=diff)
    {
        s2+=((*pf)(cou)+(*pf)(cou+diff))/2*diff;     //начальная площадь 2
    }
    while (abs(s2-s1)>accuracy)
    {
        num*=2;
        diff/=2;
        s1=s2;
        s2=0;
        for(double cou=left;cou<right;cou+=diff)
        {
            s2+=((*pf)(cou)+(*pf)(cou+diff))/2*diff;
        }
    }
    return abs(s2);
}

double sqr_counter_rect(double left, double right,double accuracy, double (*pf)(double))
{
    double s1,s2=0;
    int num=10;
    s1=(*pf)((left+right)/2)*(right-left);
    double diff =(right-left)/10;

    for(double cou=left;cou<right;cou+=diff)
    {
        s2+=((*pf)(cou+diff/2)*diff);
            //cout<<" kgkgkkg";
    }

    while(abs(s2-s1)>accuracy)
    {
        diff/=2;
        s1=s2;
        s2=0;
        for(double cou=left;cou<right;cou+=diff)
        {
            s2+=((*pf)(cou+diff/2)*diff);
        }
    }
    return abs(s2);

}

double func(double x)
{
    return x*x*x+32*x+sin(x);
}

int main()
{
    system("color f9");
    double left,right,accuracy;
    cout<<"enter left and right borders: ";
    cin>>left>>right;
    cout << "Enter accuracy: ";
    cin>>accuracy;
    auto start= chrono::system_clock::now();

    cout<<fixed<<setprecision(5)<<'\n'<<sqr_counter_trap(left,right,accuracy,func)<<'\n';
    auto endi = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = endi-start;

    cout<< "elapsed time: " << elapsed_seconds.count() << " s \n";



    start=chrono::system_clock::now();
    cout<<fixed<<setprecision(5)<<'\n'<<sqr_counter_rect(left,right,accuracy,func)<<'\n';
    endi=chrono::system_clock::now();
    elapsed_seconds=endi-start;
    cout<< "elapsed time: " << elapsed_seconds.count() << " s \n";
    for(;;)
    {
        system("color a1");
        system("color b1");
        system("color c1");
        system("color d1");
        system("color e1");
        system("color f1");

    }

    return 0;
}
