//
// Created by daniil on 26.10.2019.
//

#ifndef INC_1_TASK_STUDENTS_H
#define INC_1_TASK_STUDENTS_H


#include <vector>
#include <string>

class Task;

class Student {
    int points;
    std::vector< std::pair <std::string, int> > knowledges;
    int strategy; // 1 - the easiest, 2 - the hardest, 3 - more points, 4 - the best knoledges
public:
    Student();
    Student(const std::vector< std::pair <std::string, int> > &baseKnowledges, int baseStrategy);
    int getLevel (const std::string& subj) const;
    int getPoints() const;
    int getStrategy() const;

    void setStrategy (int newStrategy);

};


#endif //INC_1_TASK_STUDENTS_H
