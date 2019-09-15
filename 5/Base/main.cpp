#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

FILE *fp;
FILE *fpp;
const int inf=10;
int curnum=0,posi=0,abso=0,syear=0,smin=0,smax=0;
bool deleter=0;
char sbrand[inf],smodel[inf];

struct phonestruct
{
    //int brandlen;
    char brand[inf];
    //int modellen;
    char model[inf];
    int year;
    int amount;
    int pricebuks;
    bool del;
} phone;

void structcleaner()
{
   // phone.brandlen=0;
    for (int i=0;i<inf;i++)
        phone.brand[i]=' ';
   // phone.modellen=0;
    for (int i=0;i<inf;i++)
        phone.model[i]=' ';
    phone.year=0;
    phone.amount=0;
    phone.pricebuks=0;
    phone.del=0;
}

bool equel (char a[inf],char b[inf],int siz)
{
    for (int i=0;i<siz;i++ )
    {
        if (a[i]!=b[i])
            return false;
    }
    return true;
}

void Add()
{
    fp=fopen("PhoneBase.bin","r+w");
    system("pause");
    fseek(fp,0,2);
    system("cls");
    /*cout<<"Enter length of Brand:  ";
    cin>> phone.brandlen;
    system("cls");*/
    cout<<"Enter Brand: ";
    scanf("%s",phone.brand);
    system("cls");
    /*cout<<"Enter length of Model:  ";
    cin>> phone.modellen;
    system("cls");*/
    cout<<"Enter Model: ";
    scanf("%s",phone.model);
    system("cls");
    cout<<"Enter year of production: ";
    cin>>phone.year;
    system("cls");
    cout<<"Enter amount of available: ";
    cin>>phone.amount;
    system("cls");
    cout<<"Enter price in dollars: ";
    cin>>phone.pricebuks;
    phone.del=0;
    fwrite(&phone,sizeof(phone),1,fp);
    structcleaner();
    fclose(fp);
    //fclose(fp);
}

void Get()
{
    fp=fopen("PhoneBase.bin","r+w");
    system("cls");

    cout<<"Enter position you want to get  ";


    //fp = fopen("PhoneBase.bin","rb");
    cin>>posi;
    fseek(fp,sizeof(phone)*(posi-1),0);
    fread(&phone,sizeof(phone),1,fp);
    //fclose(fp);
    if (!phone.del)
    {
        for (int i=0;i<inf;i++)
        cout<<phone.brand[i];
        cout<<'\n';
        for (int i=0;i<inf;i++)
            cout<<phone.model[i];
        cout<<'\n';
        cout<<"Year of production: "<<phone.year<<'\n'<<"Number of available: "<<phone.amount<<'\n'<<"Price: "<<phone.pricebuks<<"$";
    }
    else
    {
        cout<<"No data here";
    }
    cout<<'\n';
    structcleaner();
    system("pause");
    fclose(fp);
}

void Update()
{
    fp=fopen("PhoneBase.bin","r+w");
    system("cls");

    cout<<"Enter position you want to update  ";
    cin>>posi;
    fseek(fp,(posi-1)*sizeof(phone),0);
    fread(&phone,sizeof(phone),1,fp);
    system("cls");
    cout<<"Editing MENU of ";
    for(int i=0;i<inf;i++)
    {
        cout<<phone.brand[i];
    }

    cout<<' ';
    for(int i=0;i<inf;i++)
    {
        cout<<phone.model[i];
    }
    cout<<" :\n";
    cout<<"1. New arrival of\n";
    cout<<"2. Some examples were sold\n";
    cout<<"3. Change price \n";
    cout<<"4. Exit\n";
    static int coman=0,diff=0;
    while (cin>>coman)
    {
        if (coman==1)
        {
            cout<<"How many examples just arrived?";
            cin>>diff;
            phone.amount+=diff;
            diff=0;
        }
        if (coman==2)
        {
            cout<<"How many examples were sold?";
            cin>>diff;
            phone.amount-=diff;
            diff=0;
        }
        if (coman==3)
        {
            cout<<"Old price is $"<<phone.pricebuks<<"\nEnter new price: ";
            cin>>phone.pricebuks;
        }
        if (coman==4)
        {
            break;
        }
        system("cls");
        cout<<"Editing MENU of ";
        for(int i=0;i<inf;i++)
        {
            cout<<phone.brand[i];
        }

        cout<<' ';
        for(int i=0;i<inf;i++)
        {
            cout<<phone.model[i];
        }
        cout<<" :\n";
        cout<<"1. New arrival of\n";
        cout<<"2. Some examples were sold\n";
        cout<<"3. Change price \n";
        cout<<"4. Exit\n";
    }
    fseek(fp,(posi-1)*sizeof(phone),0);
    fwrite(&phone,sizeof(phone),1,fp);
    structcleaner();
    system("cls");
    fclose(fp);

}

void Delete ()
{
    fp=fopen("PhoneBase.bin","r+w");
    system("cls");
    cout<<"Enter position you want to delete  ";
    cin>>posi;
    fseek(fp,sizeof(phone)*(posi-1)+3*sizeof(int)+2*sizeof(phone.model),0);
    deleter=1;
    if (fwrite (&deleter,sizeof(bool),1,fp))
        cout<<"Success\n";
    else
        cout<<"Oooops\n";
    system("pause");
    fclose(fp);
}

void Find ()
{
    fp=fopen("PhoneBase.bin","r+w");
    system("cls");
    for (int i=0;i<inf;i++)
        sbrand[i]=' ';
    for (int i=0;i<inf;i++)
        smodel[i]=' ';
    cout<<"Enter brand:";
    scanf("%s",sbrand);
    cout<<"Enter model:";
    scanf("%s",smodel);
    static int counter;
    counter=0;
    fseek(fp,0,0);
    static bool flag;
    flag=0;
    while (!feof(fp))
    {
        counter++;
        fread(&phone,sizeof(phone),1,fp);
        /*for (int i=0;i<inf;i++)
        {
            cout<<phone.brand[i];
        }
        for (int i=0;i<inf;i++)
        {
            cout<<phone.model[i];
        }*/

        if (equel(phone.brand,sbrand,inf) && equel(phone.model,smodel,inf) && !phone.del)
        {
            cout<<"Number "<<counter<<'\n';
            cout<<"Year of production: "<<phone.year<<'\n'<<"Number of available: "<<phone.amount<<'\n'<<"Price: "<<phone.pricebuks<<"$\n";
            flag=1;
            break;
        }
        structcleaner();
    }
    if (!flag)
    {
        cout<<"No such example";
    }
    system("pause");
    system("cls");
    fclose(fp);
}

void Select ()
{
    fp=fopen("PhoneBase.bin","r+w");
    system("cls");
    fseek(fp,0,0);
    cout<<"Select by:\n";
    cout<<"1. Brand\n";
    cout<<"2. Year\n";
    cout<<"3. Price arrange\n";
    cout<<"4. Cancel\n";
    static int task;
    task=0;
    cin>>task;
    system("cls");
    if (task==1)
    {
        cout<<"\nEnter brand: ";
        for (int i=0;i<inf;i++)
            sbrand[i]=' ';
        scanf("%s",sbrand);
        static int counter;
        counter=0;
        int counterik=0;
        while (!feof(fp))
        {
            counter++;
            fread(&phone,sizeof(phone),1,fp);

            if (equel(phone.brand,sbrand,inf) && !phone.del)
            {
                counterik++;
                cout<<counterik<<". "<<phone.model<<"\nNumber "<<counter<<'\n';
                cout<<"Year of production: "<<phone.year<<'\n'<<"Number of available: "<<phone.amount<<'\n'<<"Price: "<<phone.pricebuks<<"$\n";
            }
            structcleaner();
        }
    }
    if (task==2)
    {
        cout<<"\nEnter year: ";
        cin>>syear;
        static int counter;
        counter=0;
        int counterik=0;
        while (!feof(fp))
        {
            counter++;
            fread(&phone,sizeof(phone),1,fp);

            if (syear==phone.year && !phone.del)
            {
                counterik++;
                cout<<counterik<<". "<<phone.brand<<" "<<phone.model<<"\nNumber "<<counter<<'\n';
                cout<<"Number of available: "<<phone.amount<<'\n'<<"Price: "<<phone.pricebuks<<"$\n";
            }
            structcleaner();
        }

    }
    if (task==3)
    {
        cout<<"\nEnter lower and upper bounds: ";
        cin>>smin >> smax;
        static int counter;
        counter=0;
        int counterik=0;
        while (!feof(fp))
        {
            counter++;
            fread(&phone,sizeof(phone),1,fp);

            if (phone.pricebuks<=smax && phone.pricebuks>=smin && !phone.del)
            {
                counterik++;
                cout<<counterik<<". "<<phone.brand<<" "<<phone.model<<"\nNumber "<<counter<<'\n';
                cout<<"Year of production: "<<phone.year<<'\n'<<"Number of available: "<<phone.amount<<'\n'<<"Price: "<<phone.pricebuks<<"$\n";
            }
            structcleaner();
        }
    }
    system("pause");
    fclose(fp);
}

void Squeeze()
{
   fp=fopen("PhoneBase.bin","r+w");
   fpp=fopen("PhoneBaseHelp.bin","w");
   system("cls");
   fseek(fp,0,0);
   while (fread(&phone,sizeof(phone),1,fp))
   {
       if(!phone.del)
       {
           fwrite(&phone,sizeof(phone),1,fpp);

       }

       structcleaner();
   }
   structcleaner();
   fclose(fp);
   fclose(fpp);
   fp=fopen("PhoneBase.bin","w");
   fpp=fopen("PhoneBaseHelp.bin","r");

   while (fread(&phone,sizeof(phone),1,fpp))
   {
           fwrite(&phone,sizeof(phone),1,fp);
       structcleaner();
   }
   structcleaner();
   fclose(fp);
   fclose(fpp);
   cout<<"Successful squeezing\n";
   system("pause");




}

void Report ()
{
    fp=fopen("PhoneBase.bin","r+w");
    int totsize=0,totsum=0,totexamp=0,budgexamp=0,midexamp=0,expexamp=0;
    system("cls");
    while(!feof(fp))
    {
        fread(&phone,sizeof(phone),1,fp);
        if (!phone.del)
        {
            totsize++;
            totsum+=phone.amount*phone.pricebuks;
            totexamp+=phone.amount;
            if (phone.pricebuks<=200)
                budgexamp+=phone.amount;
            else if (phone.pricebuks<=400)
                midexamp+=phone.amount;
            else
                expexamp+=phone.amount;
        }
    }

    cout<<"Report :\nTotal devices in stock: "<<totexamp<<"\n  Budget category: "<<budgexamp<<"\n  Midprice category: "<<midexamp<<"\n  Lux category: "<<expexamp;
    cout<<"\nTotal models in stock: "<<totsize-1;
    cout<<"\nTotal money equivalence: "<<totsum<<"\nAverage price of devices: "<<totsum*1.0/totexamp<<'\n';
    fclose(fp);
    system("pause");
}

int main()
{
    structcleaner();
    //fp=fopen("PhoneBase.bin","r+w");
    int cmnd;
    cout<<"MENU:\n";
    cout<<"1. Add product\n";
    cout<<"2. Get product info\n";
    cout<<"3. Update product info\n";
    cout<<"4. Delete product\n";
    cout<<"5. Find products by info\n";
    cout<<"6. Product selection by info\n";
    cout<<"7. Squeeze\n";
    cout<<"8. Report\n";
    cout<<"9. Exit\n";
    while (cin>>cmnd)
    {
        switch (cmnd)
        {
            case 1: Add(); break;
            case 2: Get(); break;
            case 3: Update(); break;
            case 4: Delete(); break;
            case 5: Find (); break;
            case 6: Select(); break;
            case 7: Squeeze(); break;
            case 8: Report(); break;
            case 9: exit(0); break;
        }

        system("cls");
        cout<<"MENU:\n";
        cout<<"1. Add product\n";
        cout<<"2. Get product info\n";
        cout<<"3. Update product info\n";
        cout<<"4. Delete product\n";
        cout<<"5. Find products by info\n";
        cout<<"6. Product selection by info\n";
        cout<<"7. Squeeze\n";
        cout<<"8. Report\n";
        cout<<"9. Exit\n";
    }
    //fclose(fp);
    return 0;

}
