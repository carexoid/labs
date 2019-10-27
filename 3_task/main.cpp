#include <iostream>
#include <memory>

double S = 0;

class Base{

protected:
    int N;
    std::shared_ptr<Base> sample;
public:
    Base() = default;
    virtual void setN(int n){}
    virtual void setSample(std::shared_ptr<Base> example){}
    virtual ~Base(){
        std::cout << "Base " << N << '\n';
        S = 2*S + N - 37;
    }
};

class Alpha : public Base{
public:
    Alpha (int n){
        N = n;
    }
    Alpha (int n, std::shared_ptr<Base> example){
        N = n;
        sample = example;
    }
    void setN (int n) override {
        N = n;
    }
    void setSample (std::shared_ptr<Base> example) override {
        sample = example;
    }
    ~Alpha(){
        std::cout << "Alpha " << N << '\n';
        S = S - N;
    }
};
class Beta: public Base{
public:
    Beta (int n){
        N = n;
    }
    Beta (int n, std::shared_ptr<Base> example){
        N = n;
        sample = example;
    }
    void setN (int n) override {
        N = n;
    }
    void setSample (std::shared_ptr<Base> example) override {
        sample = example;
    }
    ~Beta(){
        std::cout << "Beta " << N << '\n';
        S = S + 3*N + 37;
    }
};

class Red : public Alpha{
public:
    Red (int n): Alpha(n){
    }
    Red( int n, std::shared_ptr<Base> example) : Alpha(n, example) {
    }
    ~Red(){
        std::cout << "Red " << N << '\n';
        S = S + (double) N/2;
    }
};

class Green : public Alpha{
public:
    Green (int n): Alpha(n){
    }
    Green( int n, std::shared_ptr<Base> example) : Alpha(n, example) {
    }
    ~Green(){
        std::cout << "Green " << N << '\n';
        S = S - (double) N/2 - 17;
    }
};

int main() {
    int n = 0;
    if (true){
        Alpha A(n++,std::shared_ptr <Red> (new Red(n++, std::shared_ptr <Beta> (new Beta(n++, std::shared_ptr<Green> (new Green(n++)))))));
    }
    std::cout << S;
    return 0;
}