#include <iostream>
#include <memory>

double S = 0;

class Base{

protected:
    int N;
    std::shared_ptr<Base> sample;
    int counter(){
        static int n = 0;
        return ++n;
    }
public:
    Base() = default;
    virtual void setN(int n){}
    virtual void setInstance(std::shared_ptr<Base> example){}
    virtual int getN() const{}
    virtual void delInstance(){}
    virtual ~Base(){
        std::cout << "Base " << N << '\n';
        S = 2*S + N - 37;
    }
};

class Alpha : public Base{
public:
    Alpha (){
        N = counter();
    }
    Alpha (std::shared_ptr<Base> example){
        N = counter();
        sample = example;
    }
    void setN (int n) override {
        N = n;
    }
    void setInstance (std::shared_ptr<Base> example) override {
        sample = example;
    }
    int getN () const override {
        return N;
    }
    void delInstance(){
        sample.reset();
    }
    ~Alpha(){
        std::cout << "Alpha " << N << '\n';
        S = S - N;
    }
};
class Beta: public Base{
public:
    Beta (){
        N = counter();
    }
    Beta ( std::shared_ptr<Base> example){
        N = counter();
        sample = example;
    }
    void setN (int n) override {
        N = n;
    }
    void setInstance (std::shared_ptr<Base> example) override {
        sample = example;
    }
    int getN () const override {
        return N;
    }
    void delInstance(){
        sample.reset();
    }
    ~Beta(){
        std::cout << "Beta " << N << '\n';
        S = S + 3*N + 37;
    }
};

class Red : public Alpha{
public:
    Red (): Alpha(){
    }
    Red( std::shared_ptr<Base> example) : Alpha(example) {
    }
    ~Red(){
        std::cout << "Red " << N << '\n';
        S = S + (double) N/2;
    }
};

class Green : public Alpha{
public:
    Green (): Alpha(){
    }
    Green( std::shared_ptr<Base> example) : Alpha( example) {
    }
    ~Green(){
        std::cout << "Green " << N << '\n';
        S = S - (double) N/2 - 17;
    }
};

void testSomeObjects(){
    std::shared_ptr<Alpha> B(new Alpha(std::shared_ptr <Beta> (new Beta( std::shared_ptr<Alpha> (new Alpha())))));
    B->delInstance();
    B->setInstance(std::shared_ptr<Green> (new Green() ));

    std::shared_ptr<Alpha> A(new Alpha(std::shared_ptr <Red> (new Red( std::shared_ptr <Beta> (new Beta( std::shared_ptr<Green> (new Green())))))));
}
int main() {
    testSomeObjects();
    std::cout << "Got value: " << S;
    return 0;
}