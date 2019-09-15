#include <iostream>
#include <cstdlib>

using namespace std;

struct treeNode
{
    bool red;
    double key;
    treeNode* parent, *left, *right;
};

void output (treeNode* n, int counter)
{
    if (n->left==nullptr && n->right== nullptr)
        cout<<"";
    else
    {
        if (n->left)
            output (n->left,counter+1);
            for(int i=0;i<counter;i++)
                cout<<"      ";
        cout<< n->key << "|" << n->red <<"<\n";
        if (n->right)
            output ( n->right,counter+1);

    }
}

treeNode* grandp (treeNode* n)
{
    if (!n->parent || !n->parent->parent )
        return nullptr;
    return n->parent->parent;
}

treeNode* uncle (treeNode* n)
{
    treeNode* g = grandp(n);
    if (!g)
        return nullptr;
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}

treeNode* bro (treeNode* n)
{
    if ( n == n->parent->left )
        return n->parent->right;
    return n->parent->left;
}

treeNode* childToN (treeNode* n)
{
    treeNode* saved = n;
    if (n->left->key != -1)
    {
        n = n->left;
        while (n->key != -1)
            n = n->right;
        saved->key = n->parent->key;

    }
    else if (n->right->key != -1)
    {
        n = n->right;
        while (n->key != -1)
            n = n->left;
        saved->key = n->parent->key;

    }
    return n;
}

void rotate_l (treeNode* n)
{
    treeNode* upd = n->right;
    upd->parent = n->parent;
    if (n->parent)
    {
        if (n->parent->left == n)
            n->parent->left = upd;
        else
            n->parent->right = upd;
    }
    n->parent = upd;
    n->right = upd->left;
    if (upd->left)
        upd->left->parent = n;

    upd->left = n;
}

void rotate_r (treeNode* n)
{
    treeNode* upd = n->left;
    upd->parent = n->parent;
    if (n->parent)
    {
        if (n->parent->right == n)
            n->parent->right = upd;
        else
            n->parent->left = upd;
    }
    n->parent = upd;
    n->left = upd->right;
    if (upd->right)
        upd->right->parent = n;

    upd->right = n;
}

void putChild (treeNode* n, treeNode* child)
{
        cout<<"aa";
    if (n->parent)
    {
        if (n == n->parent->left)
            n->parent->left = child;
        else
            n->parent->right = child;
    }

    child->parent = n->parent;

}

treeNode* searcher (treeNode* top,double val)
{
    while (top->key != -1)
    {
        if (top->key > val)
            top = top->left;
        else if (top->key < val)
            top = top->right;
        else
            return top;
    }
    return nullptr;
}


void insert_5 (treeNode* n);

void insert_4 (treeNode* n);

void insert_3 (treeNode* n);

void insert_2 (treeNode* n);

void insert_1 (treeNode* n);

void delete_start (treeNode* n);

void del_1 (treeNode* n);

void del_2 (treeNode* n);

void del_3 (treeNode* n);

void del_4 (treeNode* n);

void del_5 (treeNode* n);

void del_6 (treeNode* n);

void del (treeNode* top)
{
    double val;
    cin>>val;
    treeNode* saved = searcher (top,val), *n = searcher(top,val);
     cout<<saved->key;
    if (saved)
    {

        if (n->left->key != -1)
        {
            n = n->left;
            while (n->key != -1)
                n = n->right;
            saved->key = n->parent->key;
            cout<<saved->key;
            n = n->parent;

        }
        delete_start(n);
    }


}



void add (treeNode* n)
{
    double newKey;
    cin>> newKey;
    bool flag=1;
    while (flag)
    {
        if (n->key > newKey)
            n = n->left;
        else
            n = n->right;

        if (n->key == -1)
        {
            n->key = newKey;
            n->red = 1;
            n->left = new treeNode;
            n->right = new treeNode;
            n->left->parent = n;
            n->left->key = -1;
            n->left->left = nullptr;
            n->left->right = nullptr;
            n->left->red = 0;
            n->right->parent = n;
            n->right->key = -1;
            n->right->left = nullptr;
            n->right->right = nullptr;
            n->right->red = 0;

            insert_1 (n);

            flag = 0;
        }
    }
}


int main()
{
    int command,num;
    cout<<"1.add\n";
    while ( cin>>command )
        if (command == 1)
            break;
        else
            cout << "again\n";
    system ("cls");
    cout<<"enter key: ";
    cin >> num;
    treeNode* top = new treeNode;
    top->key = num;
    top->parent = nullptr;
    top->left = new treeNode;
    top->right = new treeNode;
    top->red = 0;
    top->left->parent = top;
    top->left->key = -1;
    top->left->left = nullptr;
    top->left->right = nullptr;
    top->left->red = 0;
    top->right->parent = top;
    top->right->key = -1;
    top->right->left = nullptr;
    top->right->right = nullptr;
    top->right->red = 0;

    system ("cls");
    cout << "current tree: ";
    output( top,0 );
    cout << "enter command:\n";
    cout << "1.add\n" << "2.del\n";
    while (cin>>command)
    {
        if (command == 1 )
        {
            add (top);
            while (top->parent)
                top = top->parent;
        }
        else if (command == 2)
        {
            del (top);
        }

        cout << "current tree: \n";
        output( top,0 );
        cout << "enter command:\n";
        cout << "1.add\n" << "2.del\n";
    }

    cout << "Hello world!" << endl;
    return 0;
}

void insert_5 (treeNode* n)
{
    treeNode *g = grandp (n);
    n->parent->red = 0;
    g->red = 1;
    if (n->parent->left == n && g->left == n->parent)
        rotate_r (g);
    else
        rotate_l (g);
}

void insert_4 (treeNode* n)
{
    treeNode *g = grandp (n);

    if (n->parent->right == n && g->left == n->parent)
    {
        rotate_l (n->parent);
        n = n->left;
    }
    else if (n->parent->left == n && g->right == n->parent)
    {
        rotate_r (n->parent);
        n = n->right;
    }
    insert_5(n);
}


void insert_3 (treeNode* n)
{
    treeNode* u = uncle (n);
    treeNode* g;

    if ( u && u->red )
    {
        n->parent->red = 0;
        u->red = 0;
        g = grandp (n);
        g->red = 1;
        insert_1 (g);
    }
    else
    {
        insert_4 (n);
    }
}



void insert_2 (treeNode* n)
{
    if (n->parent->red)
        insert_3 (n);
}

void insert_1 (treeNode* n)
{
    if (!n->parent)
        n->red=0;
    else
        insert_2 (n);
}

void delete_start(treeNode* n)
{

    treeNode* child;
    if (n->right->key == -1)
        child = n->left;
    else
        child = n->right;
        cout<< "a";
    putChild (n, child);
    if (!n->red)
    {
        if (child->red)
            child->red = 0;
        else
            del_1(child);
    }
    delete n;
}

void del_1 (treeNode* n)
{
    if (n->parent)
        del_2(n);
}

void del_2 (treeNode* n)
{
    treeNode* s = bro(n);

    if (s->red)
    {
        n->parent->red = 1;
        s->red = 0;
        if (n == n->parent->left)
            rotate_l(n->parent);
        else
            rotate_r(n->parent);
    }
    del_3(n);
}

void del_3 (treeNode* n)
{
    treeNode* s = bro(n);

    if (!n->parent->red && !s->red && !s->left->red && !s->right->red)
    {
        s->red = 1;
        del_1 (n->parent);
    }
    else
        del_4(n);
}

void del_4 (treeNode* n)
{
    treeNode* s = bro(n);

    if (n->parent->red && !s->red && !s->left->red && !s->right->red)
    {
        s->red = 1;
        n->parent->red = 0;
    }
    del_5(n);
}

void del_5 (treeNode* n)
{
    treeNode* s = bro(n);

    if (!s->red)
    {
        if (n == n->parent->left && s->left->red && !s->right->red)
        {
            s->red = 1;
            s->left->red = 0;
            rotate_r(s);
        }
        else if (n == n->parent->right && !s->left->red && s->right->red)
        {
            s->red = 1;
            s->right->red = 0;
            rotate_l (s);
        }
    }
    del_6 (n);
}

void del_6 (treeNode* n)
{
    treeNode* s = bro (n);

    s->red = n->parent->red;
    n->parent->red = 0;

    if (n == n->parent->left)
    {
        s->right->red = 0;
        rotate_l (n->parent);
    }
    else
    {
        s->left->red = 0;
        rotate_r (n->parent);
    }
}


