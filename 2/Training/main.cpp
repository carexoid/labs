#include <bits/stdc++.h>

using namespace std;

double sum (double eps,double x,double (*pf)(double,double,int))
{
    double a1,a2,summary=0;
    a1=-x*x*x/6;
    summary=a1;
    for(int i=2;abs(a1)>eps;i++)
    {
        a1=(*pf)(a1,x,i);
        summary+=a1;
    }
    return summary;
}

double step(double a,double x,int n)
{
    return -a*x*x/2/n/(2*n+10);
}

int main()
{
    double x,eps;
    cin>>x>>eps;
    cout << sum(eps,x,step) << endl;
    return 0;
}
