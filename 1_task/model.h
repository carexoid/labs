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
    void addRandStudents (int numOfStu);
    void addRandTasks (int numOfTas);
    void startTimeLimSim (int days); //gets number of days for simulation
    void startPointLimSim (int points); //gets number of points to be reached throe the simulation;


};


#endif //INC_1_TASK_MODEL_H