#include <iostream>

using namespace std;

const int inf=100;
/*struct node
{
    int num;
    node* next;
};

void builder (node* graph[inf] , int m)
{
    int from, to;
    for (int j=0;j<m;j++)
    {
        cin>>from>>to;
        static node* graph_go;
        graph_go = graph[from];
        while (graph_go->next)
        {
            graph_go=graph_go->next;

        }

        graph_go->next = new node;
        graph_go->next->num = to;
        graph_go->next->next = nullptr;

        graph_go = graph[to];
        while (graph_go->next)
        {
            graph_go=graph_go->next;
            //cout<<graph_go->next;

        }

        graph_go->next = new node;
        graph_go->next->num = from;
        graph_go->next->next = nullptr;
    }

}

graph_includes ( node* graph, int to )
{
    while ( graph->next )
    {
        if ( graph->num == to )
            return 1;
        graph = graph->next;
    }
    return 0;
}

bool find_k5 (node* graph[inf],int n)
{
    static int i[6];
    for ( i[1]=1; i[1]<=n-4 ; i[1]++)
        for ( i[2]=i[1]+1; i[2]<=n-3 ; i[2]++)
            for ( i[3] = i[2] + 1 ; i[3] <= n-2 ; i[3]++ )
                for ( i[4] = i[3] + 1 ; i[4] <= n - 1 ; i[4]++ )
                     for ( i[5] = i[4] + 1 ; i[5] <= n - 1 ; i[5]++ )
                     {
                         for (int from = 1 ; from <= 5 ; from++ )
                         {
                            static bool flag;
                            flag = 0;

                            for ( int to = 1 ; to <= 5 ; to++ )
                            {
                                if ( !graph_includes (graph[from],to) )
                                    {
                                        cout<<from<<" "<<to;
                                        flag=1;
                                        break;
                                    }
                            }
                            if (!flag)
                                return 1;
                         }
                     }
    return 0;
}

bool find_k33 (node * graph[inf] , int n )
{
    return 0;
}*/

bool k5 (bool matr[inf][inf], int n)
{
    int sum=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (matr[i][j])
                sum+=1;
    return sum == 20;
}

bool k33 (bool matr[inf][inf], int n, int deg[inf])
{
    for (int i=0;i<n;i++)
        if (deg[i]!=3 && deg[i]!=0)
            return 0;
    int ver [6] = {0};
    int i=0;
    while (!deg[i])
    {
        i++;
    }
    ver[0]=i;
    i=0;
    while(!matr[ver[0]][i])
        i++;
    ver[1]=i;
    //cout<<i<<" ";
    i++;
    while(!matr[ver[0]][i])
        i++;
    ver[2]=i;
   // cout<<i<<' ';
    i++;
    while(!matr[ver[0]][i])
        i++;
    ver[3]=i;
   // cout<<i<<' ';
    for (int j=0;j<n;j++)
        if (deg[j] && ver[0]!=j && ver[1]!=j && ver[2]!=j && ver[3]!=j)
        {
            ver[4]=j;
            break;

        }
    for (int j=0;j<n;j++)
        if (deg[j] && ver[0]!=j && ver[1]!=j && ver[2]!=j && ver[3]!=j && ver[4]!=j)
        {
            ver[5]=j;
            break;

        }
    if (matr[ver[1]][ver[2]] || matr[ver[1]][ver[3]] ||matr[ver[3]][ver[2]] || matr[ver[4]][ver[5]])
        return 0;

    return 1;
}

bool planar_check ( bool matr[inf][inf] , int deg[inf] , int n , int m , int v_left, bool del[inf][inf])
{
    bool matr_c[inf][inf];
    int deg_c[inf],from,to;
    for (int i=0;i<n;i++)
    {
        deg_c[i] = deg[i];

        for (int j=0;j<n;j++)
        matr_c[i][j] = matr[i][j];
    }
    for (int i=0 ; i<n ;i++ )
    {
        if (deg_c[i] == 2)
        {
            deg_c[i]=0;
            int j=0;
            while ( matr_c[i][j] != 1 )
                j++;
            matr_c[i][j] = 0;
            from = j;
            while ( matr_c[i][j] != 1 )
                j++;
            matr_c[i][j] = 0;
            to = j;
            matr_c[from][i]=0;
            matr_c[to][i] = 0;
            matr_c[from][to] = 1;
            matr_c[to][from] = 1;
            deg_c[to]++;
            deg_c[from]++;
            v_left--;
        }
    }
    int counter = 0;

    for (int i =0;i<n; i++)
    {
        if ( deg_c[i] > 2)
            counter++;
    }
    if ( counter < 5)
        return 0;
   // cout<<v_left;
    if ( v_left == 5 )
    {

        if (k5(matr_c,n))
        return 1 ;
    }
    if ( v_left == 6)
    {
       //  cout<<"mbmbm";
        if (k33(matr_c,n,deg))
        return 1;
    }

    for (int i = 0; i<n ;i++)
    {
        for (int j = 0; j <  n ;j++ )
            if (matr_c[i][j] && !del[i][j])
            {

                del[i][j] = 1;
                matr_c[i][j]=0;
                matr_c[j][i]=0;
                deg_c[i]--;
                deg_c[j]--;
                bool flagok1=0;
                for (int y=0;y<n;y++)
                    if (matr[i][y]==1)
                        flagok1 = 1;
                if(!flagok1)
                    v_left--;
                bool flagok2=0;
                for (int y=0;y<n;y++)
                    if (matr[j][y]==1)
                        flagok2 = 1;
                if(!flagok2)
                    v_left--;
                if (planar_check(matr_c,deg_c,n,m,v_left,del))
                    return 1;
                matr_c[i][j]=1;
                matr_c[j][i]=1;
                deg_c[i]++;
                deg_c[j]++;
                if (!flagok1)
                    v_left++;
                if (!flagok2)
                    v_left++;
                if (planar_check(matr_c,deg_c,n,m,v_left,del))
                    return 1;



            }
    }
    return 0;
}
int main()
{
    int n,m,from,to,deg[inf],v_left=0;
   // node* graph[inf] ;
   bool matr[inf][inf],del[inf][inf];
    cin>>n>>m;
    if (m>3*n-6)
    {
        cout<<"not planar"<<'/n';
        return 0;
    }
    for ( int i = 0; i < m ; i++ )
    {
        cin>>from>>to;
        matr[from][to] = 1;
        matr[to][from] = 1;
        deg[from]++;
        deg[to]++;
    }
    for (int i=0;i<n;i++)
        if (deg[i])
            v_left++;
    //cout<<v_left;
    if (n<5)
        cout<< " planar ";
    else if (planar_check(matr,deg,n,m,v_left,del))
        cout<<" not planar";
    else
        cout<< " planar ";

    /*for (int i=0; i<=n ; i++)
    {
        graph[i] = new node;
         graph[i]->next = nullptr;
    }
    builder (graph, m);
    for (int i = 0 ; i < n ; i++ )
        if (graph[i]->next)
            graph[i] = graph[i]->next ;
    if (find_k5(graph,n))
    {
        cout<<" not planar/n ";
        return 0;
    }
    if (find_k33(graph,n))
    {
        cout<<" not planar/n ";
        return 0;
    }
    cout<< " planar \n";*/

    return 0;
}

