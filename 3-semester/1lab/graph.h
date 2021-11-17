//
// Created by daniil on 27.09.2019.
//

#ifndef INC_1LAB_GRAPH_H
#define INC_1LAB_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include<cassert>
#include <string>


using std::cout;
using std::vector;
using std::pair;
using std::queue;
using std::string;

template<typename T>
std::ostream& operator << (std::ostream& outp, const vector<T>& vec) {
    outp << "[";
    char separator = ' ' ;
    for(auto &obj : vec) {
        outp << separator << obj;
        separator = ',';
    }
    outp << " ]";
    return outp;
}

template<typename T>
T getData (int index){
    return T(index);
}

class Book;

template<>
Book getData<Book> (int index);

/*template<>
string getData<string> (int index){
    string s = "";
    s.resize(index,'a');
    return s;
}*/

template<typename T>
vector<T> operator + (const vector<T>& a, const vector<T>& b){
    vector<T> c = a;
    for (auto &v: b)
        c.push_back(v);
    return c;
}
template<typename T>
bool operator < (const vector<T>& a, const vector<T>& b){
    return a.size() < b.size();
}

//Book operator + (Book &a, Book &b);

//bool operator <(Book a, Book b);



template<typename T,typename V>
class Graph{
public:
    virtual void addEdge (V edgeData, int nodeFrom, int nodeTo) = 0;
    virtual void addNode (T nodeData, vector<pair<int,V> > neighbors) = 0;
    virtual void delEdge (int nodeFrom, int nodeTo) = 0;
    virtual void delNode (int key) = 0;
    virtual pair<int,int> findEdge (V edgeData) = 0;
    virtual int findNode (T nodeData) = 0;
    virtual void printGraph () = 0;
    virtual bool isConnected () = 0;
    virtual V countDist ( int start, int finish, int minDist,int maxDist) = 0;
};

template <typename T,typename V>
class MatrixBasedGraph: public Graph<T, V>{
private:
    vector< vector< pair <bool, V> > > matrix;
    vector< pair< bool, T> > nodes;
    int currentSize = 0;
    void dfs (int vKey, vector<bool> &visited){
        visited[vKey] = 1;
        for (int i = 0; i<currentSize; i ++){
            if (matrix[vKey][i].first && !visited[i])
                dfs(i,visited);
        }
    }
    V dejkstra (int start, int finish, const V& minDist,const V& maxDist){
        vector<V> dist(currentSize,maxDist);
        queue<int> q;
        dist[start] = minDist;
        q.push(start);
        while (!q.empty()){
            int curTop = q.front();
            for (int i = 0;i < currentSize; i++){
                if (matrix[curTop][i].first)
                    if (dist[curTop] + matrix[curTop][i].second < dist[i]){
                        q.push(i);
                        dist[i] = dist[curTop] + matrix[curTop][i].second;
                    }
            }
            q.pop();
        }
        return dist[finish];
    }
public:
    MatrixBasedGraph (){
        currentSize = 0;
    }
    MatrixBasedGraph (vector<T> inputNodes, vector<pair < pair<int, int> , V> > inputEdges){
        currentSize = inputNodes.size();
        nodes.resize(currentSize);
        matrix.resize(currentSize);
        for (int i = 0; i< currentSize; i++)
            matrix[i].resize(currentSize);

        for (int i = 0; i<currentSize; i++)
            nodes[i] = {1,inputNodes[i]};

        for (int i = 0; i < inputEdges.size(); i++){
            matrix[inputEdges[i].first.first-1][inputEdges[i].first.second-1] = {1,inputEdges[i].second};
            matrix[inputEdges[i].first.second-1][inputEdges[i].first.first-1] = {1,inputEdges[i].second};
        }
    }


    //edge will be added if there is no edge
    void addEdge(V edgeData, int from, int to) override{
        assert (nodes[from-1].first);
        assert (nodes[to-1].first);
        assert (!matrix[from-1][to-1].first);
        matrix[from-1][to-1] = {1,edgeData};
        matrix[to-1][from-1] = {1,edgeData};
    };
    //node will get the key, that is equel to currentSize(TODO insert new node instead of deleted)
    void addNode(T nodeData, vector< pair<int, V> > neighbors) override {
        nodes.push_back({1,nodeData});
        matrix.resize(++currentSize);
        for (int i = 0; i < currentSize; i++)
            matrix[i].resize(currentSize);

        for (int i = 0; i < neighbors.size(); i++)
            addEdge(neighbors[i].second, currentSize ,  neighbors[i].first);
    }
    //wanted edge will get status of not existing edge
    void delEdge(int from, int to) override {
        assert (matrix[from-1][to-1].first);
        matrix[from-1][to-1].first = 0;
        matrix[to-1][from-1].first = 0;

    }
    //want node will get status of not existing node
    void delNode(int key) override{
        nodes[key-1].first = 0;
        for (int i = 1;i < currentSize+1; i++)
            if (matrix[key-1][i-1].first)
                delEdge(key,i);
    }
    //returns keys of nodes that are connected by this edge, returns {0,0} if no such data found
    pair<int, int> findEdge(V edgeData) override{
        for (int i = 0;i<currentSize; i++)
            if (nodes[i].first){
                for (int j = 0; j<currentSize; j++){
                    if (matrix[i][j].second == edgeData)
                        return {i+1,j+1};
                }
            }

        return {0, 0};
    }
    //returns the first found key of node with such info, 0 if no such info
    int findNode(T nodeData) override{
        for (int i = 0; i < currentSize ; i++)
            if (nodes[i].second == nodeData)
                return i+1;
        return 0;
    }
    //prints graph in console
    void printGraph() override{
        for (int i = 0; i < currentSize; i++){
            if (nodes[i].first){
                cout << i+1 << ": " << nodes[i].second;
                for (int j = 0; j < currentSize ; j++){
                    if (matrix[i][j].first)
                        cout << "\n    " << j+1 << ": " << matrix[i][j].second;
                }
                cout <<'\n';
            }
        }
    }
    //starts dfs from the first not deleted node
    bool isConnected () override {
        vector<bool> visited(currentSize,0);
        for (int i = 0; i<currentSize; i++)
            if (nodes[i].first){
                dfs (i,visited);
                break;
            }

        for (int i = 0; i < currentSize; i++){
            if (nodes[i].first && !visited[i])
                return 0;
        }
        return 1;
    }

    V countDist (int start, int finish, int minDist, int maxDist) override{
        return dejkstra(start-1,finish-1,getData<V>(minDist),getData<V>(maxDist));
    }
};

template <typename T,typename V>
class ListBasedGraph: public Graph<T, V>{
private:
    vector< vector< pair< int, V> > > list;
    vector< pair<bool, T> > nodes;
    int currentSize;
    void dfs (int vKey, vector<bool> &visited){
        visited[vKey] = 1;
        for (auto &v: list [vKey]){
            if (!visited[v.first])
                dfs(v.first,visited);
        }
    }
    V dejkstra (int start, int finish, const V& minDist,const V& maxDist){
        vector<V> dist(currentSize,maxDist);
        queue<int> q;
        dist[start] = minDist;
        q.push(start);
        while (!q.empty()){
            int curTop = q.front();
            for (auto v: list[curTop]){
                if (dist[curTop] + v.second < dist[v.first]){
                    q.push(v.first);
                    dist[v.first] = dist[curTop] + v.second;
                }
            }
            q.pop();
        }
        return dist[finish];
    }

public:
    ListBasedGraph (){
        currentSize = 0;
    }
    ListBasedGraph (vector<T> inputNodes, vector<pair < pair<int, int> , V> > inputEdges){
        currentSize = inputNodes.size();
        nodes.resize(currentSize);
        list.resize(currentSize);

        for (int i = 0; i<currentSize; i++)
            nodes[i] = {1,inputNodes[i]};

        for (int i = 0; i < inputEdges.size(); i++){
           list[inputEdges[i].first.first-1].push_back({inputEdges[i].first.second-1, inputEdges[i].second});
           list[inputEdges[i].first.second-1].push_back({inputEdges[i].first.first-1, inputEdges[i].second});
        }
    }


    //edge will be added if there is no edge(TODO error when adding existing edge )
    void addEdge(V edgeData, int from, int to) override{
        assert (nodes[from-1].first);
        assert (nodes[to-1].first);
        list[from-1].push_back({to-1, edgeData});
        list[to-1].push_back({ from-1, edgeData});
    };
    //node will get the key, that is equel to currentSize(TODO insert new node instead of deleted)
    void addNode(T nodeData, vector< pair<int, V> > neighbors) override {
        list.resize(++currentSize);
        nodes.push_back({1,nodeData});
        for (int i = 0; i < neighbors.size(); i++)
            addEdge(neighbors[i].second, currentSize ,  neighbors[i].first);
    }
    //wanted edge will get status of not existing edge (TODO error when deleting not existing edge)
    void delEdge(int from, int to) override {
        bool flag = 0;
        int i = 0;
        while (!flag && i<currentSize){
            if (list[from-1][i].first == to-1){
                list[from-1].erase(list[from-1].begin() + i);
                flag = 1;
            }
            i++;
        }
        if (flag){
            i = 0;
            while (flag && i<currentSize){
                if (list[to-1][i].first == from-1){
                    list[to-1].erase(list[to-1].begin() + i);
                    flag = 0;
                }
                i++;
            }
        }
    }
    //want node will get status of not existing node
    void delNode(int key) override{
        nodes[key-1].first = 0;
        for (int i = 1;i < currentSize+1; i++)
            delEdge(key,i);
    }
    //returns keys of nodes that are connected by this edge, returns {0,0} if no such data found
    pair<int, int> findEdge(V edgeData) override{
        for (int i = 0;i<currentSize; i++)
            if (nodes[i].first){
                for (int j = 0; j < list[i].size(); j++){
                    if (list[i][j].second == edgeData)
                        return {i+1,list[i][j].second+1};
                }
            }

        return {0, 0};
    }
    //returns the first found key of node with such info, 0 if no such info
    int findNode(T nodeData) override{
        for (int i = 0; i < currentSize ; i++)
            if (nodes[i].second == nodeData)
                return i+1;
        return 0;
    }
    //prints graph in console
    void printGraph() override{
        for (int i = 0; i < currentSize; i++){
            if (nodes[i].first){
                cout << i+1 << ": " << nodes[i].second;
                for (auto &k: list[i]){
                        cout << "\n    " << k.first+1 << ": " << k.second;
                }
                cout <<'\n';
            }
        }
    }
    //starts dfs from the first not deleted node
    bool isConnected () override {
        vector<bool> visited (currentSize,0);
        for (int i = 0; i<currentSize; i++)
            if (nodes[i].first){
                dfs (i,visited);
                break;
            }

        for (int i = 0; i < currentSize; i++){
            if (nodes[i].first && !visited[i])
                return 0;
        }
        return 1;
    }

    V countDist (int start, int finish, int minDist, int maxDist) override{
        return dejkstra(start-1,finish-1,getData<V>(minDist),getData<V>(maxDist));
    }

};


#endif //INC_1LAB_GRAPH_H
