//
// Created by daniil on 26.10.2019.
//

#ifndef INC_1_TASK_TASKS_H
#define INC_1_TASK_TASKS_H


#include <random>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include "students.h"

class Student;

class Task {
    int maxPoints;
    std::vector< std::string > knowledges;
    const int maxComplexity = 10;
    int complexity ;
    int type; // 1-complexity, 2-av point, 3-min points, 4-random
public:
    Task() = default;
    Task(const std::vector < std::string>& disciplines, int points, int typeOfTask, int comple);
    int pointsFor (const Student& student) const;
    int daysFor (const Student& student) const;
    int getMaxPonts() const;
    int getComlexity() const;
    int getMaxComplexity() const;
    std::vector< std::string > getKnowledges() const;
    bool hasKnowledge(const std::string& searched) const;
    Task& operator=(const Task& A);
};

std::ostream& operator<< (std::ostream& out, const Task& A);
bool operator== (const Task& A, const Task& B);

#endif //INC_1_TASK_TASKS_H
