//
// Created by daniil on 26.10.2019.
//


#include "students.h"
#include "tasks.h"
#include "model.h"

Student::Student() : points(0),strategy(0){}
Student::Student(const std::vector<std::pair<std::string, int> > &baseKnowledges, int baseStrategy)
    : knowledges(baseKnowledges), strategy(baseStrategy), points(0){}

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

void Student::updKnowledges(const Task &taskDone) {
    for (auto &i: knowledges){
        if (taskDone.hasKnowledge(i.first)){
            i.second += (i.second)*taskDone.getComplexity()/taskDone.getMaxComplexity() + 1;
            i.second = std::min(i.second, 100);
        }
    }
}


bool Student::cmpForKnow(std::pair<std::string, int> a, std::pair<std::string, int> b) {
    return a.second > b.second;
}

int Student::chooseIndOfTask(const std::vector<Task>& tasks, const std::vector<bool>& done) {
    if (strategy == 1){
        int minCompl = 0;
        for (int i = 0; i < done.size(); i++)
            if (!done[i]){
                minCompl = i;
                break;
            }
        for (int i = 0; i < tasks.size(); i++){
            if (!done[i]){
                if (tasks[i].getComplexity() < tasks[minCompl].getComplexity())
                    minCompl = i;
            }
        }
        return minCompl;
    }
    if (strategy == 2) {
        int maxCompl = 0;
        for (int i = 0; i < done.size(); i++)
            if (!done[i]){
                maxCompl = i;
                break;
            }
        for (int i = 0; i < tasks.size(); i++){
            if (!done[i]){
                if (tasks[i].getComplexity() > tasks[maxCompl].getComplexity())
                    maxCompl = i;
            }
        }
        return maxCompl;
    }
    if (strategy == 3){
        int maxPoints = 0;
        for (int i = 0; i < done.size(); i++)
            if (!done[i]){
                maxPoints = i;
                break;
            }
        for (int i = 0; i < tasks.size(); i++){
            if (!done[i]){
                if (tasks[i].getMaxPonts() > tasks[maxPoints].getMaxPonts())
                    maxPoints = i;
            }
        }
        return maxPoints;
    }
    int maxKnowledge = 0, maxVal = 0;
    for (int i = 0; i < done.size(); i++)
        if (!done[i]){
            maxKnowledge= i;
            std::vector<std::string> subjInCurTask = tasks[i].getKnowledges();
            for (const auto& j: subjInCurTask)
                maxVal = std::max(maxVal,getLevel(j));
            break;
        }
    for (int i = 0; i < tasks.size(); i++){
        int localMax = 0;
        if (!done[i]){
            std::vector<std::string> subjInCurTask = tasks[i].getKnowledges();
            for (const auto& j: subjInCurTask)
                localMax = std::max(localMax,getLevel(j));
        }
        if (localMax > maxVal){
            maxVal = localMax;
            maxKnowledge = i;
        }
    }
    return maxKnowledge;
}

void Student::addPoints(int newPoints) {
    points += newPoints;
}

std::vector <std::pair < std::string, int> > Student::getKnowledges() const {
    return knowledges;
}

std::ostream& operator<<(std::ostream &out, const Student &A) {
    std::vector <std::pair < std::string, int> > knows = A.getKnowledges();
    out << "\nPoints got: " << A.getPoints() << "\nStrategy of choosing: " << A.getStrategy();
    out << "\nKnowledges:\n";
    for (const auto& i: knows)
        out << "    Subject: " << i.first <<" Knowledge out of 100: " << i.second << '\n';
    return  out;
}

Student& Student::operator=(const Student &A) {
    points = A.points;
    knowledges = A.knowledges;
    strategy = A.strategy;
    return *this;
}
