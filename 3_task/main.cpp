#include <iostream>
#include <memory>
#include <vector>

double S = 0;

class Base{

protected:
    int N;
    int counter(){
        static int n = 0;
        return ++n;
    }
public:
    std::shared_ptr<Base> sample;
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
        S = S + N*1.0/2;
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
        S = S - N*1.0/2 - 17;
    }
};

void testSomeObjects(){
    std::shared_ptr<Alpha> B(new Alpha(std::shared_ptr <Beta> (new Beta( std::shared_ptr<Alpha> (new Alpha())))));
    B->delInstance();
    B->setInstance(std::shared_ptr<Green> (new Green() ));

    std::shared_ptr<Alpha> A(new Alpha(std::shared_ptr <Red> (new Red( std::shared_ptr <Beta> (new Beta( std::shared_ptr<Green> (new Green())))))));
}
double countRes (const Base& A, double Scopy){
    if (typeid(A) == typeid(Base))
        return 2*Scopy + A.getN() - 37;
    if (typeid(A) == typeid(Alpha))
        return 2*(Scopy - A.getN()) + A.getN() - 37;
    if (typeid(A) == typeid(Beta))
        return 2*(Scopy + 3*A.getN() + 37)+ A.getN() - 37;
    if (typeid(A) == typeid(Red))
        return 2*((Scopy + A.getN() *1.0/2) - A.getN())+ A.getN() - 37;
    return 2*((Scopy - A.getN()*1.0/2 - 17) - A.getN())+ A.getN() - 37;

}



double predictRes(const std::vector< std::shared_ptr<Base> > &vec){
    double Scopy = S;
    for (const auto& i:vec){
        std::shared_ptr<Base> cur = i;
        while (cur->sample){
            Scopy = countRes(*cur,Scopy);
            cur = cur->sample;
        }
        Scopy = countRes(*cur,Scopy);
    }
    return Scopy;
}

void testPredictor(){
    std::vector<std::shared_ptr<Base> > vec = {std::shared_ptr<Alpha> (new Alpha(std::shared_ptr <Beta> (new Beta( std::shared_ptr<Green> (new Green()))))),
                                               std::shared_ptr<Red> (new Red(std::shared_ptr <Green> (new Green( std::shared_ptr<Alpha> (new Alpha())))))};
    std::cout << "Predicted value after deleting vector: " << predictRes(vec) << '\n';
}
int main() {
    testSomeObjects();
    std::cout << "Got value after running testSomeObjects: " << S << '\n';
    testPredictor();
    std::cout << "Got value after deleting vector: " << S;
    return 0;
}