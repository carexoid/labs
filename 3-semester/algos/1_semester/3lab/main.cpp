#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class heap{
    std::vector<std::pair<int,T> > heapy;
    int n;
    void heapify(int node){
        int curPos = node;
        int maximum = n*node+1;
        int sizeOfHeap = heapy.size();
        for (int i = n*node+1; i < std::min(sizeOfHeap, (node+1)*n+1); i++){
            if (heapy[maximum].first < heapy[i].first)
                maximum = i;
        }
        while (heapy[curPos].first < heapy[maximum].first){
            std::swap(heapy[curPos] , heapy[maximum]);
            curPos = maximum;
            if (maximum*n+1 > heapy.size())
                break;
            maximum = n*curPos+1;
            for (int i = n*curPos+1; i < std::min(sizeOfHeap, (curPos+1)*n+1); i++){
                if (heapy[maximum].first < heapy[i].first)
                    maximum = i;
            }
        }
    }
public:
    heap (const std::vector<std::pair<int,T> > &vec, int d) : heapy(vec), n(d){
        for(int i = vec.size()/n - 1; i >= 0; i--){
            heapify(i);
        }
    }
    void insert (const std::pair<int,T> & in){
        heapy.push_back(in);
        int curPos = heapy.size() - 1;
        while (heapy[curPos] > heapy[(curPos-1)/n] && curPos > 0){
            std::swap(heapy[curPos],heapy[(curPos-1)/n]);
            curPos = (curPos - 1)/n;
        }
    }
    void print() const {
        for (const auto &i:heapy)
            std::cout << i.first << ":" << i.second << "  ";

    }
    std::pair<int, T> extractMax(){
        std::pair<int,T> heapMax = heapy[0];
        std::swap(heapy[0], heapy[heapy.size()-1]);
        heapy.pop_back();
        //std::cout << heapy.size();
        heapify(0);
        return heapMax;

    }
    void incKey (int key){
        heapy[key].first++;
        int curPos = key;
        while (heapy[curPos] > heapy[(curPos-1)/n] && curPos > 0){
            std::swap(heapy[curPos],heapy[(curPos-1)/n]);
            curPos = (curPos - 1)/n;
        }

    }
    bool empt() const{
        return heapy.empty();
    }

};


int main() {
    int n;

    std::cin >> n;
    std::vector<std::pair<int,int> > vec(n);
    for (int i = 0 ; i < n; i++){
        std::cin >> vec[i].first >> vec[i].second;
    }
    heap<int> myHeap(vec,2);
    myHeap.print();
    std::cout << '\n';
//    std::pair<int,int> toInsert;
//    std::cin >> toInsert.first >> toInsert.second;
//    myHeap.insert(toInsert);
//    myHeap.print();
//    std::cin >> toInsert.first >> toInsert.second;
//    myHeap.insert(toInsert);
//    myHeap.print();
//    toInsert = myHeap.extractMax();
//    std::cout <<'\n';
//    myHeap.print();
//    std::cout << '\n' <<  toInsert.first << ':' << toInsert.second ;
//    int keyToInc;
//    std::cin >> keyToInc;
//    myHeap.incKey(keyToInc);
//    myHeap.print();


    std::vector<std::pair<int,int> > sorted;
    while(!myHeap.empt()){
        sorted.push_back(myHeap.extractMax());
        myHeap.print();
       std::cout << '\n';
//        std::cout << "a";
    }
    std::cout << '\n';
    std::reverse(sorted.begin(),sorted.end());
    for (int i = 0 ; i < n; i++){
        std::cout << "  " << sorted[i].first << ":" << sorted[i].second;
    }

    return 0;
}
