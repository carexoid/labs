#include <iostream>
#include <cmath>
#include<string>
#include <cassert>
#include <vector>


template<typename T>
double funcF (const T& input){
    return 35.97;
}

template<>
double funcF<int> (const int& input){
    if (input > 0)
        return sin(5 * input + 179);
    try{
        if (pow(input,5) <= -279)
            throw "Body of log must be > 0 in function getting int as parametr! ";
        return log2( pow (input , 5) + 279);
    }
    catch(char const*str){
        std::cout << '\n' << str << '\n';
        return 0;
    }
}

template<>
double funcF<double> (const double& input) {
    if ((int)input - input == 0)
        return funcF((int)input);
    return input / (input + 379);
}

template<>
double funcF<std::string>( const std::string& input){
    double digCounter = 0;
    for (const auto& i: input){
        if (i - '0' >= 0 && i - '0' <= 9)
            digCounter++;
    }
    try{
        if(!input.length())
            throw "Division by 0 in fuction with string in input!";
    }
    catch (char const*str){
        std::cout << '\n' << str << '\n';
        return 0;
    }
    return ((double) digCounter / input.length()) *  ((double) digCounter / input.length());
}

template<typename T, typename  V>
double funcF(const std::pair<T, V>& input) {
    return pow(funcF(input.second), sin(579 * funcF(input.first)));
}

template<typename T>
double funcF(const std::vector<T> &input) {
    double maximum = -2;
    for (const auto& i: input)
        maximum = std::max( maximum, cos(funcF(i) - 879));
    return maximum;
}
int main() {
    int intTest1 = 10, intTest2 = -1;
    double douTest1 = 10, douTest2 = 1.5;
    bool boolTest = true;
    std::string strTest = "ar678etuyhkovf";
    std::pair<int,double> pairIntDouTest = {intTest2,douTest2};
    std::pair<std::string,double> pairStrDouTest = {strTest,douTest2};
    std::vector<int> vecIntTest = {1, 4, 5, 3, 6};
    std::vector<double> vecDouTest = {10.1, 40.1, 7.8, 4.6, 9.05};
    std::pair<std::string, std::vector<double> > pairStrVecTest = {strTest,vecDouTest};
    std::cout << "\nTesting (int) 10 as parametr: " << funcF(intTest1);
    std::cout << "\nTesting (double) 10 as parametr: " << funcF(douTest1);
    std::cout << "\nTesting (int) -1 as parametr: " << funcF(intTest2);
    std::cout << "\nTesting (int) -10 as parametr: " << funcF(10*intTest2);
    std::cout << "\nTesting (string) ar678etuyhkovf as parametr: " << funcF(strTest);
    std::cout << "\nTesting (string) are678tuyhkovfw34e4r as parametr: " << funcF(strTest + "w34e4r");
    std::cout << "\nTesting (pair) { (int) -1, (double) 1.5 } as parametr: " << funcF(pairIntDouTest);
    std::cout << "\nTesting (pair) { (string) aretuyhkovf, (double) 1.5 } as parametr: " << funcF(pairStrDouTest);
    std::cout << "\nTesting (vector<int>) { 1, 4, 5, 3, 6} as parametr: " << funcF(vecIntTest);
    std::cout << "\nTesting (vector<double>) {1.1, 4.1, 7.8, 4.6, 9.05} as parametr: " << funcF(vecDouTest);
    std::cout << "\nTesting (pair) { (string) are678tuyhkovfw34e4r, (vector<double>) {1.1, 4.1, 7.8, 4.6, 9.05} } as parametr: " << funcF(pairStrDouTest);


    std::cout << "\nTesting (bool) true as parametr: " << funcF(boolTest);


    return 0;
}