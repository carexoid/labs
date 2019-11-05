#include <iostream>
#include <vector>

template<typename T>
void sort1_2 (std::vector< std::pair <bool, T> > &vec){
    int zeroCounter = 0, zeros = 0, ones = 0;
    std::vector< std::pair <bool, T> > res (vec.size());
    for (auto &i: vec){
        if (!i.first)
            zeroCounter++;
    }
    for (auto &i: vec){
        if (!i.first)
            res[zeros++] = i;
        else
            res[zeroCounter + ones++] = i;
    }
    vec = res;
}

template< typename T>
void sort1_3 (std::vector< std::pair <bool, T> > &vec) {
    int zeros = 0;
    for (auto &i: vec){
        if (!i.first)
            std::swap(i,vec[zeros++]);
    }
}

template< typename T>
void sort2_3 (std::vector< std::pair <bool, T> > &vec) {
    int zeros = 0;
    for (int i = 0; i<vec.size(); i++){
        if (!vec[i].first){
            for (int j = i - 1; j>= zeros; j--){
                std::swap (vec[j], vec[j+1]);
            }
            zeros++;
        }
    }
}

std::vector < std::pair < bool, int> > intGenerator (int sizeOfRand){
    int  b;
    bool a;
    std::vector< std::pair <bool,int> > res;
    srand( time(0));
    FILE* inp = fopen("input.bin","w");
    for (int i = 0; i < sizeOfRand; i++){
        a = rand() % 2;
        b = 1 + rand() % 1000;
        res.emplace_back(a,b);
        std::cout << a <<" " << b <<", ";
    }
    std::cout << '\n';
    return res;
}


int main() {
    //std::vector < std::pair< bool, int > > testVec = { {1, 2} , {0,9} , {1,8} , {1,65} , {0,6} , {1,6} , {1, 2} , {0,98} , {1,8}};
    std::vector < std::pair< bool, int > > testVec = intGenerator( 20);
    std::vector < std::pair< bool, int > > testVec1  = testVec, testVec2 = testVec, testVec3 = testVec;
    sort1_2(testVec1);
    for (auto &i:testVec1)
        std::cout << i.first << " " << i.second << ", ";
    std::cout << '\n';
    sort1_3(testVec2);
    for (auto &i:testVec2)
        std::cout << i.first << " " << i.second << ", ";
    std::cout << '\n';
    sort2_3(testVec3);
    for (auto &i:testVec3)
        std::cout << i.first << " " << i.second << ", ";
    std::cout << '\n';

    return 0;
}