//
// Created by daniil on 26.10.2019.
//

#include "students.h"
#include "tasks.h"

Student::Student() : points(0),strategy(0){}
Student::Student(const std::vector<std::pair<std::string, int> > &baseKnowledges, int baseStrategy) : knowledges(baseKnowledges), strategy(baseStrategy){
    points = 0;
}

int Student::getLevel (const std::string& subj) const{
    for (const auto& i:knowledges)
        if (subj == i.first)
            return i.second;
    return 0;
}
 int Student::getPoints() const {
    return points;
}

int Student::getStrategy() const {
    return strategy;
}

void Student::setStrategy(int newStrategy) {
    strategy = newStrategy%5;
}


