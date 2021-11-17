#include <bits/stdc++.h>

using namespace std;

const int inf=100;

string digits="0123456789";

struct tree
{
    char operation;
    string val;
    bool leave;
    tree *son1, *son2;

};

bool is_number (string s)
{
    bool flag=0;
    for (int i=0;i<s.size();i++)
    {
        for (int j=0;j<10;j++)
            if (s[i]==digits[j])
                flag=1;
        if (!flag)
            return 0;
        flag =0;
    }
    return 1;
}

int strToInt(string s)
{
    int res=0;
    for (int i=0;i<s.size();i++)
    {
         res+=((s[i]-'0')* pow(10,(s.size()-i-1)));
    }
    return res ;
}

char digitInChar (int num)
{
    char res = num + '0';
    return res;
}

string intToStr (int num)
{
    string res ="";
    char s;
    while(num)
    {
        s=digitInChar(num%10);
        int siz = res.size();
        res.resize(siz+1);
        for (int i=siz;i>0;i--)
        {
            res[i]=res[i-1];
        }
        res[0]=s;

        num/=10;
    }
    return res;
}

void build (string s,int &i,tree *point)
{
    point->leave =false;
    if (s[i]=='(')
    {
        point->son1=new tree;
        point->son1->val = "";
        i+=2;
        build(s,i,point->son1);
    }

    else
    {
        point->son1=new tree;
        point->son1->leave =true;
        while(s[i]!=' ')
        {
            point->son1->val+=s[i];
            i++;
        }
    }
    i++;
    point->operation=s[i];
    i+=2;
    if (s[i]=='(')
    {
        point->son2=new tree;
        i+=2;
        build(s,i,point->son2);
    }

    else
    {
        point->son2=new tree;
        point->son2->leave=true;
        point->son2->val = "";
        while(s[i]!=' ')
        {
            point->son2->val+=s[i];
            i++;
        }
        i+=4;
    }
}

void optimizer (tree *node) //??????????????????????????????????????????????????????
{
    if (!node->leave)
    {


        optimizer (node->son1);
        optimizer (node->son2);
        if ( node->son1->leave && node->son1->val == "0" && node->operation == '+')
        {
                *node = *node->son2;
        }
        else if ( node->son2->leave && node->son2->val == "0" && ( node->operation == '+' || node->operation == '-') )
        {
                *node = *node->son1;
        }
        else if ( node->son1->leave && node->son1->val == "0" && ( node->operation == '*' || node->operation == '/' ) )
        {
            node->leave = 1;
            node->val = "0";
        }
        else if ( node->son2->leave && node->son2->val == "0" && node->operation == '*')
        {
            node->leave = 1;
            node->val = "0";
        }
        else if ( node->son1->leave && node->son1->val == "1" && node->operation == '*')
        {
            *node = *node->son2;
        }
        else if ( node->son2->leave && node->son2->val == "1" && ( node->operation == '*' || node->operation == '/' ) )
        {
            *node = *node->son1;
        }
        else if (node->son1->leave && node->son2->leave)
        {
            if (is_number(node->son1->val) && is_number(node->son2->val))
            {

                int n1=strToInt(node->son1->val);
                int n2=strToInt(node->son2->val);
                if (node-> operation == '+')
                {
                    node->val=intToStr( n1 + n2 );
                    node->leave=1;
                    node->son1=nullptr;
                    node->son2=nullptr;
                }
                else if (node -> operation == '-' && n1 >= n2 )
                {
                    node->val=intToStr( n1 - n2 );
                    node->leave=1;
                    node->son1=nullptr;
                    node->son2=nullptr;
                }

                else if ( node -> operation == '*' )
                {
                    node->val=intToStr( n1 * n2 );
                    node->leave=1;
                    node->son1=nullptr;
                    node->son2=nullptr;
                }

                else if ( node -> operation == '/' )
                {
                    node->val=intToStr( n1 / n2 );
                    node->leave=1;
                    node->son1=nullptr;
                    node->son2=nullptr;
                }


            }
        }
    }
}

void diffbuilder (tree *node, tree *point, string po, bool diff)
{
    node->leave=0;
    if (diff)
    {
        if (point->leave)
        {
            node->leave = "1";
            if (point->val == po)
                node->val = "1";
            else if (is_number(point->val))
                node->val = "0";
            else
                node->val = point->val;
        }
        else if (point->operation == '+' || point->operation == '-')
        {
            node->son1 = new tree;
            node->son2 = new tree;
            node-> operation = point->operation;
            diffbuilder (node->son1 , point->son1 , po , 1 );
            diffbuilder (node->son2 , point->son2 , po , 1 );
        }
        else if ( point->operation == '*' )
        {
            node->son1 = new tree;
            node->son2 = new tree;
            node->operation = '+';
            node->son1->leave=0;
            node->son2->leave=0;
            node->son1->son1 = new tree;
            node->son1->son2 = new tree;
            node->son1->operation = '*';
            diffbuilder( node->son1->son1 , point->son1 , po , 1 );
            diffbuilder( node->son1->son2 , point->son2 , po , 0 ) ;
            node->son2->son1 = new tree;
            node->son2->son2 = new tree;
            node->son2->operation = '*';
            diffbuilder( node->son2->son2 , point->son2 , po , 1 );
            diffbuilder( node->son2->son1 , point->son1 , po , 0 ) ;

        }
        else if ( point->operation == '/')
        {
            node->son1 = new tree;
            node->son2 = new tree;
            node->operation = '/';
            node->son1->leave=0;
            node->son2->leave=0;

            node->son1->son1 = new tree;
            node->son1->son2 = new tree;
            node->son1->operation = '-';
            node->son1->son1->leave=0;
            node->son1->son2->leave=0;

            node->son1->son1->son1 = new tree;
            node->son1->son1->son2 = new tree;
            node->son1->son1->operation = '*';
            diffbuilder( node->son1->son1->son1 , point->son1 , po , 1 );
            diffbuilder( node->son1->son1->son2 , point->son2 , po , 0 ) ;

            node->son1->son2->son1 = new tree;
            node->son1->son2->son2 = new tree;
            node->son1->son2->operation = '*';
            diffbuilder( node->son1->son2->son2 , point->son2 , po , 1 );
            diffbuilder( node->son1->son2->son1 , point->son1 , po , 0 ) ;

            node->son2->son1 = new tree;
            node->son2->son2 = new tree;
            node->son2->operation = '*';
            diffbuilder ( node->son2->son1 , point->son2 , po , 0 );
            diffbuilder ( node->son2->son2 , point->son2 , po , 0 );
        }
    }
    else
    {
        *node=*point;
    }

}
void changer ( string parametr, string val , tree *node)
{
    if (node->leave)
    {
        if (node->val == parametr)
            node->val = val;
    }
    else
    {
        changer ( parametr , val , node->son1 );
        changer ( parametr , val , node->son2 );
    }
}

string output (tree *node)
{
    if (node->leave)
        return node->val;
    return '(' + output(node->son1) + node->operation  + output(node->son2) + ')';
}


int main()
{
    freopen ( "input.txt" , "r" , stdin);
    tree *topnode = new tree, *topdiff = new tree;
    int n;
    string input, s, parametr, val;
    while (cin>>s && s!="!")
        input=input+" "+s;
    int beg=1;
    build ( input, beg, topnode );
    cout << output ( topnode ) << '\n';
    optimizer ( topnode );
    cout << " optimized: " << output ( topnode );
    cin >> parametr;
    diffbuilder ( topdiff , topnode , parametr , 1 );


    cout << "\ndiff: " << output (topdiff) << '\n';
    optimizer ( topdiff );
    cout << "\noptimized diff: " << output ( topdiff ) << '\n';
    cin >> n;
    for ( int i = 0 ; i < n ; i++ )
    {
        cin >> parametr;
        cin >> val;
        changer ( parametr, val, topnode );
    }
    optimizer (topnode);
    cout << " Result with parametrs: " << output(topnode) << "\n";

    //cout<< topnode->son2->son2->val;

    return 0;
}
