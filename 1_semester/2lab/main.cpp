#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

int partition (vector<int> &bolt, vector<int> &nut, int low, int high){
    int i = low;
    for (int j = low; j <= high - 1; j++){
        if (nut[j] == bolt[high]){
            swap(nut[j], nut[high]);
        }
        if (nut[j] < bolt[high]){
            swap(nut[i], nut[j]);
            i++;
        }
    }
    i = low;
    for (int j = low; j <= high - 1; j++){
        if (bolt[j] < nut[high]){
            swap(bolt[i], bolt[j]);
            i++;
        }
    }
    swap(nut[i], nut[high]);
    swap(bolt[i], bolt[high]);
    return i;
}

void boltSorter(vector<int> &bolt, vector<int> &nut,  int low, int high){
    if (low < high){
        int pi = partition(bolt, nut, low, high);
        boltSorter(bolt, nut, low, pi - 1);
        boltSorter(bolt, nut,  pi + 1, high);
    }
}

int main() {
    int n,num;
    vector<int> bolt, nut;
    cin>>n;
    cout << "Botls in:";
    for(int i = 0; i < n; i++){
        cin>>num;
        bolt.push_back(num);
    }
    nut = bolt;
    std::shuffle( nut.begin(), nut.end(), std::mt19937(std::random_device{}()));
    cout << "Nuts in:";
    for(int i = 0; i < n; i++){
        cout << nut[i] << " ";
    }
    cout << "\nBotls out:";
    boltSorter(bolt,nut,0,n-1);
    for(int i = 0; i < n; i++){
        cout << bolt[i] << " ";
    }
    cout << "\nNuts out:";
    for(int i = 0; i < n; i++){
        cout << nut[i] << " ";
    }
    return 0;
}