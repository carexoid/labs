//
// Created by daniil on 26.10.2019.
//

#include "tasks.h"
#include "students.h"
#include "model.h"

Task::Task(const std::vector<std::string> &disciplines, int points, int typeOfTask, int comple)
: knowledges(disciplines), maxPoints(points), type(typeOfTask), complexity(comple) {
}

int Task::pointsFor(const Student &student) const {
    double sum = 0;
    int minimum = 100;
    std::vector< std::pair<std::string, int> > curLevel;
    for (const auto& i: knowledges)
        curLevel.emplace_back(i, student.getLevel(i));
    for (const auto& i: curLevel){
        sum +=  i.second * 1.0/ curLevel.size();
        minimum = std::min(minimum, i.second);
    }

    //sum/=40;
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(0, 100);
    if (type == 1)
        return round( ( sum *complexity + minimum*complexity + complexity * 50  + urd(gen))/2600*maxPoints) ;
    if (type == 2)
        return round( ( sum *complexity + minimum*complexity +  sum * 5  + urd(gen))/2600*maxPoints) ;
    if (type == 2)
        return round( ( sum *complexity + minimum*complexity + minimum * 5 + urd(gen))/2600*maxPoints) ;

    return round( ( sum *complexity  + minimum*complexity + urd(gen)*6)/2600*maxPoints) ;

}

int Task::daysFor(const Student &student) const {
    double sum = 0;
    int minimum = 100;
    std::vector< std::pair<std::string, int> > curLevel;
    for (const auto& i: knowledges)
        curLevel.emplace_back(i, student.getLevel(i));
    for (const auto& i: curLevel){
        sum +=  i.second * 1.0/ curLevel.size();
        minimum = std::min( minimum,i.second);
    }

    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 50), uid2(0,150);
    if (type == 1)
        return 260/(floor(( (double) minimum+sum+50)*complexity/maxComplexity)+ uid(gen) ) + 1;
    if (type == 2)
        return 260/(floor((sum)*(complexity+5)/maxComplexity + (double) minimum*complexity/maxComplexity)+ uid(gen) ) + 1;
    if (type == 3)
        return 260/(floor((sum)*(complexity)/maxComplexity + (double) minimum*(complexity+5)/maxComplexity)+ uid(gen) ) + 1;
    return 260/(floor((sum + (double) minimum)*(complexity)/maxComplexity)+ uid2(gen) ) + 1;
}

int Task::getComlexity() const {
    return complexity;
}

std::vector<std::string> Task::getKnowledges() const {
    return knowledges;
}

int Task::getMaxPonts() const {
    return maxPoints;
}

int Task::getMaxComplexity() const {
    return maxComplexity;
}

bool Task::hasKnowledge(const std::string& searched) const {
    for(const auto &i: knowledges)
        if (searched == i)
            return 1;
    return 0;
}

std::ostream& operator<< (std::ostream& out, const Task& A){
    std::vector <std::string>  req = A.getKnowledges();
    out << "\nPoints maximum: " << A.getMaxPonts() << "\nComplexity: " << A.getComlexity();
    out << "\nSubjects required:\n";
    for (const auto& i: req)
        out << "    Subject: " << i << '\n';
    return  out;
}

Task& Task::operator=(const Task &A) {
    maxPoints = A.maxPoints;
    complexity = A.complexity;
    type = A.type;
    knowledges = A.knowledges;
    return *this;
}