#include <bits/stdc++.h>

using namespace std;

int currow=1, brackets=0;
set <char> digits={'1','2','3','4','5','6','7','8','9','0'};
set <char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
   'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

bool identifier (char &a)
{
    //cout<<"Ident  ";
    if (alphabet.find(a)!=alphabet.end()++)
    {
        while (digits.find(a)!=digits.end()++ || alphabet.find(a)!=alphabet.end()++)
        {
             cin>>a;
             //cout<<a;
        }
        return true;
    }
    cout<<" In row "<< currow << " identifier expected"<<'\n';
    exit (0);
    return false;
}

bool identifier_or_number (char &a)
{
    //cout<<"Ident  ";
    if (alphabet.find(a)!=alphabet.end()++)
    {
        while (digits.find(a)!=digits.end()++ || alphabet.find(a)!=alphabet.end()++)
        {
             cin>>a;
            // cout<<a;
        }
        return true;
    }
    else if (digits.find(a)!=digits.end()++)
        {
            if(a=='0')
            {
                cin>>a;
                if(digits.find(a)!=digits.end()++ || alphabet.find(a)!=alphabet.end()++)
                {
                    cout<<" In row "<< currow << " identifier or number expected"<<'\n';
                    exit (0);
                    return false;
                }
                return 1;
            }
            else
            {
                while (digits.find(a)!=digits.end()++ )
                {
                    cin>>a;
                    //cout<<a;
                }
                if (alphabet.find(a)!=alphabet.end()++)
                {
                    cout<<" In row "<< currow << " identifier or number expected"<<'\n';
                    exit (0);
                    return false;
                }
                return true;
            }

        }
    cout<<" In row "<< currow << " identifier or number expected"<<'\n';
    exit (0);
    return false;

}

bool simple_expression(char &c)
{
    //cout<<"  abrakadabra  ";
    if (c=='(')
    {
        cin>>c;
        //cout<<c;
        if (simple_expression(c))
        {
            //cin>>c;
            while (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='%')
            {
                cin>>c;
                //cout<<c;
                if(simple_expression(c))
                {
                    /*if (c==')')
                    {
                        cin>>c;
                        cout<<c;
                        return 1;
                    }


                    else
                    {
                        cout<<" In row "<< currow << " ) expected"<<'\n';
                        return 0;
                    }*/
                    cout<<' ';
                }
                else
                {
                    cout<<" In row "<< currow << " simple expression expected"<<'\n';
                    exit (0);
                    return 0;
                }
            }
            if(c==')')
            {
                cin>>c;
                if (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='%')
                {
                    cin>>c;
                    if (simple_expression(c))
                    {
                        return 1;
                    }
                    cout<<" In row "<< currow << " simple expression expected"<<'\n';
                    exit (0);
                    return 0;
                }
                //cout<<c;
                return 1;
            }

            //else
            //{
            cout<<" In row "<< currow << " operation sign or ) expected"<<'\n';
            exit (0);
            return 0;
            //}

        }
        else
        {
            cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;
        }

    }
    else
    if (identifier_or_number(c))
    {
        if(c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='%')
        {
            cin>>c;
            if(simple_expression(c))
            {
                return 1;
            }
            cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;

        }
        return 1;
    }
    cout<<" In row "<< currow << " simple expression or identifier expected"<<'\n';
    exit (0);
    return 0;

}

bool assignment(char &c)
{
    if (identifier(c))
    {
        if (c=='=')
        {
            cin>>c;
            if (simple_expression(c))
            {
                if (c!=';')
                {
                    cout<<" In row "<< currow << " ; expected"<<'\n';
                    exit (0);
                    return 0;
                }
                return 1;
            }
            cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;

        }
        cout<<" In row "<< currow << " = expected"<<'\n';
        exit (0);
        return 0;
    }
    cout<<" In row "<< currow << " identifier expected"<<'\n';
    exit (0);
    return 0;

}

bool comparison(char &c)
{
    if(simple_expression(c))
    {
        if(c=='!'||c=='=')
        {
            cin>>c;
            if (c=='=')
            {
                cin>>c;
                if (simple_expression(c))
                {

                    if(c=='|')
                    {
                        cin>>c;
                        if (c=='|')
                        {
                            cin>>c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        cout<<" In row "<< currow << " || expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    else if(c=='&')
                    {
                        cin>>c;
                        if (c=='&')
                        {
                            cin>>c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        cout<<" In row "<< currow << " && expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    return 1;
                }
                cout<<" In row "<< currow << " simple expression expected"<<'\n';
                exit (0);
                return 0;
            }
            cout<<" In row "<< currow << " = expected"<<'\n';
            exit (0);
            return 0;
        }
        if(c=='<'||c=='>')
        {
            cin>>c;
            if (c=='=')
            {
                cin>>c;
                if (simple_expression(c))
                {
                    if(c=='|')
                    {
                        cin>>c;
                        if (c=='|')
                        {
                            cin>>c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        cout<<" In row "<< currow << " || expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    else if(c=='&')
                    {
                        cin>>c;
                        if (c=='&')
                        {
                            cin>>c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        cout<<" In row "<< currow << " && expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    return 1;
                }
               // cout<<" In row "<< currow << " simple expression expected"<<'\n';
                //return 0;
            }
            else if (simple_expression(c))
                {
                    if(c=='|')
                    {
                        cin>>c;
                        if (c=='|')
                        {
                            cin>>c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        cout<<" In row "<< currow << " || expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    else if(c=='&')
                    {
                        cin>>c;
                        if (c=='&')
                        {
                            cin>>c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        cout<<" In row "<< currow << " && expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    return 1;
                }
            cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;

        }
        cout<<" In row "<< currow << " comparator expected"<<'\n';
        exit (0);
        return 0;

    }
    cout<<" In row "<< currow << " simple expression expected"<<'\n';
    exit (0);
    return 0;
}

bool operators(char &c)
{
    if (c=='i')
    {
        cin>>c;
        if (c=='f')
        {
            cin>>c;
            if (c=='(')
            {
                cin>>c;
                if (comparison(c))
                {
                    if (c==')')
                    {
                        return 1;
                    }
                    cout<<" In row "<< currow << " ) expected"<<'\n';
                    exit (0);
                    return 0;
                }
                cout<<" In row "<< currow << " condition expected"<<'\n';
                exit (0);
                return 0;
            }
            else if (assignment(c))
                {
                    return 1;
                }
            cout<<" In row "<<currow << " ( or assignment expected\n";
            exit (0);
            return 0;
        }
        else if (c=='n')
        {
            cin>>c;
            if (c=='t')
            {
                if (assignment(c))
                {
                    return 1;
                }
                cout<<" In row "<<currow<<" assignment expected/n";
                exit (0);
                return 0;
            }
            else if (assignment(c))
            {
                return 1;
            }
            cout<<" In row "<< currow <<" assignment expected\n";
            exit (0);
            return 0;
        }
        else if (assignment(c))
        {
            return 1;
        }
        cout<<" In row "<< currow <<" operator expected\n";
        exit (0);
        return 0;
    }
    else if (c=='w')
    {
        cin>>c;
        if (c=='h')
        {
            cin>>c;
            if (c=='(')
            {
                cin>>c;
                if (comparison(c))
                {
                    if (c==')')
                    {
                        return 1;
                    }
                    cout<<" In row "<< currow << " ) expected"<<'\n';
                    exit (0);
                    return 0;
                }
                cout<<" In row "<< currow << " condition expected"<<'\n';
                exit (0);
                return 0;
            }
            else if (assignment(c))
                {
                    return 1;
                }
            cout<<" In row "<<currow << " ( or assignment expected\n";
            exit (0);
            return 0;
        }
        else if (assignment(c))
        {
            return 1;
        }
        cout<<" In row "<< currow <<" operator expected\n";
        exit (0);

        return 0;
    }
    else if (c=='{' || c=='}')
        {
            if (c=='{')
                brackets++;
            else
                brackets--;
            if (brackets<0)
            {
                cout<<" In row "<<currow<<" extra } found ";
                exit(0);
                return 0;
            }
            return 1;
        }
    else if (assignment(c))
    {
        return 1;
    }
    cout<<" In row "<< currow <<" operator expected\n";
    exit (0);
    return 0;

}

int main()
{
    system("color f9");
    char a;
    cout<< currow<<"|    ";
    while(cin>>a)
    {
        // cout << assignment(a)<< '\n';
        //cout << comparison(a)<< '\n';

        if (operators(a))
            currow++;
        cout<<currow <<"|    ";
        for (int i=0;i<brackets;i++)
        {
            cout<< "    ";
        }
    }

    return 0;
}
