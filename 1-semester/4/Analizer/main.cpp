#include <bits/stdc++.h>

using namespace std;

int currow=1, brackets=0;
set <char> digits={'1','2','3','4','5','6','7','8','9','0'};
set <char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
   'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
FILE *filo, *filin;

bool identifier (char &a)
{
    //cout<<"Ident  ";
    if (alphabet.find(a)!=alphabet.end()++)
    {
        while (digits.find(a)!=digits.end()++ || alphabet.find(a)!=alphabet.end()++)
        {
             fscanf(filin,"%c" ,&a);
             cout<<a;
        }
        return true;
    }
    fprintf(filo,"  In row %d identifier expected",currow);
    //cout<<" In row "<< currow << " identifier expected"<<'\n';
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
             fscanf(filin,"%c" ,&a);
             cout<<a;
        }
        return true;
    }
    else if (digits.find(a)!=digits.end()++)
        {
            if(a=='0')
            {
                fscanf(filin,"%c" ,&a);
                cout<<a;
                if(digits.find(a)!=digits.end()++ || alphabet.find(a)!=alphabet.end()++)
                {
                    fprintf(filo,"  In row %d identifier or number expected",currow);
                    //cout<<" In row "<< currow << " identifier or number expected"<<'\n';
                    exit (0);
                    return false;
                }
                return 1;
            }
            else
            {
                while (digits.find(a)!=digits.end()++ )
                {
                    fscanf(filin,"%c" ,&a);
                    cout<<a;
                }
                if (alphabet.find(a)!=alphabet.end()++)
                {
                    fprintf(filo,"  In row %d identifier or number expected",currow);
                    //cout<<" In row "<< currow << " identifier or number expected"<<'\n';
                    exit (0);
                    return false;
                }
                return true;
            }

        }
    fprintf(filo,"  In row %d identifier or number expected",currow);
    //cout<<" In row "<< currow << " identifier or number expected"<<'\n';
    exit (0);
    return false;

}

bool simple_expression(char &c)
{
    //cout<<"  abrakadabra  ";
    if (c=='(')
    {
        fscanf(filin,"%c" ,&c);
        while(c==' ' || c=='\n')
        {
            fscanf(filin,"%c" ,&c);
        }
        cout<<c;
        if (simple_expression(c))
        {
            //cin>>c;
            while (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='%')
            {
                fscanf(filin,"%c" ,&c);
                while(c==' '|| c=='\n')
                {
                    fscanf(filin,"%c" ,&c);
                }
                cout<<c;
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
                    fprintf(filo,"  In row %d simple expression expected",currow);
                    //cout<<" In row "<< currow << " simple expression expected"<<'\n';
                    exit (0);
                    return 0;
                }
            }
            if(c==')')
            {
                fscanf(filin,"%c" ,&c);
                while(c==' '|| c=='\n')
                {
                    fscanf(filin,"%c" ,&c);
                }
                cout<<c;
                if (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='%')
                {
                    fscanf(filin,"%c" ,&c);
                    while(c==' '|| c=='\n')
                    {
                        fscanf(filin,"%c" ,&c);
                    }
                    cout<<c;
                    if (simple_expression(c))
                    {
                        return 1;
                    }
                    fprintf(filo,"  In row %d simple expression expected",currow);
                    //cout<<" In row "<< currow << " simple expression expected"<<'\n';
                    exit (0);
                    return 0;
                }
                //cout<<c;
                return 1;
            }

            //else
            //{
            fprintf(filo,"  In row %d operation sign or ) expected",currow);
            //cout<<" In row "<< currow << " operation sign or ) expected"<<'\n';
            exit (0);
            return 0;
            //}

        }
        else
        {
            fprintf(filo,"  In row %d simple expression expected",currow);
            //cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;
        }

    }
    else
    if (identifier_or_number(c))
    {
        if(c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='%')
        {
            fscanf(filin,"%c" ,&c);
            while(c==' '|| c=='\n')
            {
                fscanf(filin,"%c" ,&c);
            }
            cout<<c;
            if(simple_expression(c))
            {
                return 1;
            }
            fprintf(filo,"  In row %d simple expression expected",currow);
            //cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;

        }
        return 1;
    }
    fprintf(filo,"  In row %d simple expression or identifier expected",currow);
    //cout<<" In row "<< currow << " simple expression or identifier expected"<<'\n';
    exit (0);
    return 0;

}

bool assignment(char &c)
{
    if (identifier(c))
    {
        if (c=='=')
        {
            fscanf(filin, "%c", &c);
            while(c==' '|| c=='\n')
                fscanf(filin,"%c" ,&c);
            cout<<c;
            if (simple_expression(c))
            {
                if (c!=';')
                {
                    fprintf(filo,"  In row %d ; expected",currow);
                    //cout<<" In row "<< currow << " ; expected"<<'\n';
                    exit (0);
                    return 0;
                }
                return 1;
            }
            fprintf(filo,"  In row %d simple expression expected",currow);
            //cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;

        }
        fprintf(filo,"  In row %d = expected",currow);
        //cout<<" In row "<< currow << " = expected"<<'\n';
        exit (0);
        return 0;
    }
    fprintf(filo,"  In row %d identifier expected",currow);
    //cout<<" In row "<< currow << " identifier expected"<<'\n';
    exit (0);
    return 0;

}

bool comparison(char &c)
{
    if(simple_expression(c))
    {
        if(c=='!'||c=='=')
        {
            fscanf(filin, "%c", &c);
            while(c==' '|| c=='\n')
                fscanf(filin,"%c" ,&c);
            cout<<c;
            if (c=='=')
            {
                fscanf(filin, "%c", &c);
                while(c==' '|| c=='\n')
                    fscanf(filin,"%c" ,&c);
                cout<<c;
                if (simple_expression(c))
                {
                    if (c==' '|| c=='\n')
                    {
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                    }

                    if(c=='|')
                    {
                        fscanf(filin, "%c", &c);
                        while(c==' '|| c=='\n')
                             fscanf(filin,"%c" ,&c);
                        cout<<c;
                        if (c=='|')
                        {
                            fscanf(filin, "%c", &c);
                            while(c==' '|| c=='\n')
                                fscanf(filin,"%c" ,&c);
                            cout<<c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            fprintf(filo,"  In row %d comparison expected",currow);
                            //cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        fprintf(filo,"  In row %d || expected",currow);
                        //cout<<" In row "<< currow << " || expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    else if(c=='&')
                    {
                        fscanf(filin, "%c", &c);
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                        if (c=='&')
                        {
                            fscanf(filin, "%c", &c);
                            while(c==' '|| c=='\n')
                                fscanf(filin,"%c" ,&c);
                            cout<<c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            fprintf(filo,"  In row %d comparison expected",currow);
                            //cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        fprintf(filo,"  In row %d && expected",currow);
                        //cout<<" In row "<< currow << " && expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    return 1;
                }
                fprintf(filo,"  In row %d simple expression expected",currow);
                //cout<<" In row "<< currow << " simple expression expected"<<'\n';
                exit (0);
                return 0;
            }
            fprintf(filo,"  In row %d = expected",currow);
            //cout<<" In row "<< currow << " = expected"<<'\n';
            exit (0);
            return 0;
        }
        if(c=='<'||c=='>')
        {
            fscanf(filin, "%c", &c);
            while(c==' '|| c=='\n')
                fscanf(filin,"%c" ,&c);
            cout<<c;
            if (c=='=')
            {
                fscanf(filin, "%c", &c);
                while(c==' '|| c=='\n')
                    fscanf(filin,"%c" ,&c);
                cout<<c;
                if (simple_expression(c))
                {
                    if (c==' '|| c=='\n')
                    {
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                    }
                    if(c=='|')
                    {
                        fscanf(filin, "%c", &c);
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                        if (c=='|')
                        {
                            fscanf(filin, "%c", &c);
                            while(c==' '|| c=='\n')
                                fscanf(filin,"%c" ,&c);
                            cout<<c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            fprintf(filo,"  In row %d comparison expected",currow);
                            //cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        fprintf(filo,"  In row %d || expected",currow);
                        //cout<<" In row "<< currow << " || expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    else if(c=='&')
                    {
                        fscanf(filin, "%c", &c);
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                        if (c=='&')
                        {
                            fscanf(filin, "%c", &c);
                            while(c==' '|| c=='\n')
                                fscanf(filin,"%c" ,&c);
                            cout<<c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            fprintf(filo,"  In row %d comparison expected",currow);
                            //cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        fprintf(filo,"  In row %d && expected",currow);
                        //cout<<" In row "<< currow << " && expected"<<'\n';
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
                    if (c==' '|| c=='\n')
                    {
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                    }
                    if(c=='|')
                    {
                        fscanf(filin, "%c", &c);
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                        if (c=='|')
                        {
                            fscanf(filin, "%c", &c);
                            while(c==' '|| c=='\n')
                                fscanf(filin,"%c" ,&c);
                            cout<<c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            fprintf(filo,"  In row %d comparison expected",currow);
                            //cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        fprintf(filo,"  In row %d || expected",currow);
                        //cout<<" In row "<< currow << " || expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    else if(c=='&')
                    {
                        fscanf(filin, "%c", &c);
                        while(c==' '|| c=='\n')
                            fscanf(filin,"%c" ,&c);
                        cout<<c;
                        if (c=='&')
                        {
                            fscanf(filin, "%c", &c);
                            while(c==' '|| c=='\n')
                                fscanf(filin,"%c" ,&c);
                            cout<<c;
                            if (comparison(c))
                            {
                                return 1;

                            }
                            fprintf(filo,"  In row %d comparison expected",currow);
                            //cout<<" In row "<< currow << " comparison expected"<<'\n';
                            exit (0);
                            return 0;
                        }
                        fprintf(filo,"  In row %d && expected",currow);
                        //cout<<" In row "<< currow << " && expected"<<'\n';
                        exit (0);
                        return 0;

                    }
                    return 1;
                }
            fprintf(filo,"  In row %d simple expression expected",currow);
            //cout<<" In row "<< currow << " simple expression expected"<<'\n';
            exit (0);
            return 0;

        }
        fprintf(filo,"  In row %d comparator expected",currow);
        //cout<<" In row "<< currow << " comparator expected"<<'\n';
        exit (0);
        return 0;

    }
    fprintf(filo,"  In row %d simple expression expected",currow);
    //cout<<" In row "<< currow << " simple expression expected"<<'\n';
    exit (0);
    return 0;
}

bool operators(char &c)
{
    if (c=='i')
    {
        fscanf(filin, "%c", &c);
        while(c==' '|| c=='\n')
                fscanf(filin,"%c" ,&c);
        cout<<c;
        if (c=='f')
        {
            fscanf(filin, "%c", &c);
            while(c==' '|| c=='\n')
                fscanf(filin,"%c" ,&c);
            cout<<c;
            if (c=='(')
            {
                fscanf(filin, "%c", &c);
                while(c==' '|| c=='\n')
                    fscanf(filin,"%c" ,&c);
                cout<<c;
                if (comparison(c))
                {
                    if (c==')')
                    {
                        return 1;
                    }
                    fprintf(filo,"  In row %d ) expected",currow);
                    //cout<<" In row "<< currow << " ) expected"<<'\n';
                    exit (0);
                    return 0;
                }
                fprintf(filo,"  In row %d condition expected",currow);
                //cout<<" In row "<< currow << " condition expected"<<'\n';
                exit (0);
                return 0;
            }
            else if (assignment(c))
                {
                    return 1;
                }
            fprintf(filo,"  In row %d ( or assignment expected",currow);
            //cout<<" In row "<<currow << " ( or assignment expected\n";
            exit (0);
            return 0;
        }
        else if (c=='n')
        {
            fscanf(filin, "%c", &c);
            while(c==' '|| c=='\n')
                fscanf(filin,"%c" ,&c);
            cout<<c;
            if (c=='t')
            {
                if (assignment(c))
                {
                    return 1;
                }
                fprintf(filo,"  In row %d assignment expected",currow);
                //cout<<" In row "<<currow<<" assignment expected/n";
                exit (0);
                return 0;
            }
            else if (assignment(c))
            {
                return 1;
            }
            fprintf(filo,"  In row %d assignment expected",currow);
            //cout<<" In row "<< currow <<" assignment expected\n";
            exit (0);
            return 0;
        }
        else if (assignment(c))
        {
            return 1;
        }
        fprintf(filo,"  In row %d operator expected",currow);
        //cout<<" In row "<< currow <<" operator expected\n";
        exit (0);
        return 0;
    }
    else if (c=='w')
    {
        fscanf(filin, "%c", &c);
        while(c==' ')
                fscanf(filin,"%c" ,&c);
        cout<<c;
        if (c=='h')
        {
            fscanf(filin, "%c", &c);
            while(c==' ')
                fscanf(filin,"%c" ,&c);
            cout<<c;
            if (c=='(')
            {
                fscanf(filin, "%c", &c);
                while(c==' ')
                    fscanf(filin,"%c" ,&c);
                cout<<c;
                if (comparison(c))
                {
                    if (c==')')
                    {
                        return 1;
                    }
                    fprintf(filo,"  In row %d ) expected",currow);
                    //cout<<" In row "<< currow << " ) expected"<<'\n';
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
            fprintf(filo,"  In row %d ( or assignment expected",currow);
            //cout<<" In row "<<currow << " ( or assignment expected\n";
            exit (0);
            return 0;
        }
        else if (assignment(c))
        {
            return 1;
        }
        fprintf(filo,"  In row %d operator expected",currow);
        //cout<<" In row "<< currow <<" operator expected\n";
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
                fprintf(filo,"  In row %d extra } found",currow);
                //cout<<" In row "<<currow<<" extra } found ";
                exit(0);
                return 0;
            }
            return 1;
        }
    else if (assignment(c))
    {
        return 1;
    }
    fprintf(filo,"  In row %d operator expected",currow);
    //cout<<" In row "<< currow <<" operator expected\n";
    exit (0);
    return 0;

}

int main()
{

    filin = fopen("C:\\Users\\osoka\\Desktop\\Универ\\1 семестр\\Прога\\Лабы\\4\\Analizer\\input.txt" , "rt");
    filo = fopen ("C:\\Users\\osoka\\Desktop\\Универ\\1 семестр\\Прога\\Лабы\\4\\Analizer\\output.txt","w");
    system("color f9");
    char a;
    cout<< currow<<"|    ";
    fprintf(filo," Success!");
    while(!feof(filin))
    {
        fscanf(filin,"%c" ,&a);
        while( a==' ' || a=='\n')
            fscanf(filin,"%c" ,&a);

        cout<<a;
        // cout << assignment(a)<< '\n';
        //cout << comparison(a)<< '\n';

        if (operators(a))
            currow++;
        cout<<'\n'<<currow <<"|    ";
        for (int i=0;i<brackets;i++)
        {
            cout<< "    ";
        }
    }

    fclose(filin);
    fclose(filo);

    return 0;
}
