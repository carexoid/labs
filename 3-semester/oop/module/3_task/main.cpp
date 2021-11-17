#include <iostream>
#include <memory>
#include <vector>

double S = 0;


class Base{

protected:
    int N;
    int& counter() const{
        static int n = 0;
        return n;
    }
public:
    std::shared_ptr<Base> sample;
    Base() = default;
    virtual void setN(int n) = 0;
    virtual void setInstance(std::shared_ptr<Base> example) = 0;
    virtual int getN() const = 0;
    virtual void delInstance() = 0;
    virtual void resetCounter() = 0;
    virtual void decreaseCounter() = 0;
    virtual ~Base(){
     //   std::cout << "Base " << N << '\n';
        S = 2*S + N - 37;
    }
};

class Alpha : public Base{
public:
    Alpha (){
        N = ++counter();
    }
    Alpha (std::shared_ptr<Base> example){
        N = ++counter();
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
    void delInstance() override {
        sample.reset();
    }
    void resetCounter() override {
        counter() = 0;
    }
    void decreaseCounter() override {
        --counter();
    }
    ~Alpha() override {
       // std::cout << "Alpha " << N << '\n';
        S = S - N;
    }
};
class Beta: public Base{
public:
    Beta (){
        N = ++counter();
    }
    Beta ( std::shared_ptr<Base> example){
        N = ++counter();
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
    void delInstance()override {
        sample.reset();
    }
    void resetCounter() override {
        counter() = 0;
    }
    void decreaseCounter() override {
        --counter();
    }
    ~Beta() override{
       // std::cout << "Beta " << N << '\n';
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
       // std::cout << "Red " << N << '\n';
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
        //std::cout << "Green " << N << '\n';
        S = S - N*1.0/2 - 17;
    }
};

void testSomeObjects(){
    std::shared_ptr<Alpha> B(new Alpha(std::shared_ptr <Beta> (new Beta( std::shared_ptr<Alpha> (new Alpha())))));
    B->delInstance();
    B->setInstance(std::shared_ptr<Green> (new Green() ));

    std::shared_ptr<Alpha> A(new Alpha(std::shared_ptr <Red> (new Red( std::shared_ptr <Beta> (new Beta( std::shared_ptr<Green> (new Green())))))));
    A->resetCounter();
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



double predictRes(const std::vector< std::shared_ptr<Base> > &vec) {
    double Scopy = S;
    for (const auto &i:vec) {
        std::shared_ptr<Base> cur = i;
        while (cur->sample) {
            Scopy = countRes(*cur, Scopy);
            cur = cur->sample;
        }
        Scopy = countRes(*cur, Scopy);
    }
    return Scopy;
}

void testPredictor(){
    std::vector<std::shared_ptr<Base> > vec = {std::shared_ptr<Alpha> (new Alpha(std::shared_ptr <Beta> (new Beta( std::shared_ptr<Green> (new Green()))))),
                                               std::shared_ptr<Red> (new Red(std::shared_ptr <Green> (new Green( std::shared_ptr<Alpha> (new Alpha())))))};
    std::cout << "Predicted value after deleting vector: " << predictRes(vec) << '\n';
    vec[0]->resetCounter();
}

void combinations(int M,  std::vector<std::shared_ptr<Base> >& B){
    if(!M){
        S = 0;
        std::cout << predictRes(B) <<' ';
    }
    else{
        B.push_back(std::shared_ptr<Base> (new Alpha()));
        combinations(M-1,B);
        B[B.size()-1]->decreaseCounter();
        B.pop_back();
        B.push_back(std::shared_ptr<Base> (new Beta()));
        combinations(M-1,B);
        B[B.size()-1]->decreaseCounter();
        B.pop_back();
        B.push_back(std::shared_ptr<Base> (new Red()));
        combinations(M-1,B);
        B[B.size()-1]->decreaseCounter();
        B.pop_back();
        B.push_back(std::shared_ptr<Base> (new Green()));
        combinations(M-1,B);
        B[B.size()-1]->decreaseCounter();
        B.pop_back();

    }
}// for independent examples that created in order same to position

void testCombinator(int M){
    std::vector<std::shared_ptr<Base> > vec;
    combinations(M,vec);
}

int main() {
    testSomeObjects();
    std::cout << "Got value after running testSomeObjects: " << S << '\n';
    testPredictor();
    std::cout << "Got value after deleting vector: " << S;
    std::cout << "\nPredicting all variant of vector of independent examples that created in order same to order in vector ( first element created first): ";
    testCombinator(6);


    return 0;
}