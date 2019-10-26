//
// Created by daniil on 26.10.2019.
//

#ifndef INC_1_TASK_MODEL_H
#define INC_1_TASK_MODEL_H

#include <vector>
#include <string>

class Student;
class Task;

class Model {
    std::vector <Student> students;
    std::vector <Task> tasks;
    std::vector<std::string> subjects;
    int dayForSimulation;
    int pointBound;
    Student generateStudent();
    Task generateTask();
public:
    Model() = default;
    Model (int numOfstudents, int numOfTasks, const std::vector<std::string>& subjectsIn); //constructor with random generation of data


};


#endif //INC_1_TASK_MODEL_H
