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
    int complexity;
    int type; // 1-complexivity, 2-av point, 3-min points, 4-random
public:
    Task() = default;
    Task(std::vector < std::string> disciplines, int points, int typeOfTask);
    int pointsFor (const Student& student) const;
    int daysFor (const Student& student) const;
    int getMaxPonts() const;
    int getComlexity() const;
    std::vector< std::string > getKnowledges() const;







};


#endif //INC_1_TASK_TASKS_H
