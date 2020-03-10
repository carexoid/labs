//
// Created by daniil on 26.10.2019.
//

#ifndef INC_1_TASK_MODEL_H
#define INC_1_TASK_MODEL_H

#include <vector>
#include <string>
#include <random>
#include <ctime>

class Student;
class Task;

class Model {
    int studentsNum;
    int tasksNum;
    std::vector <Student> students, studentsBase;
    std::vector <Task> tasks, tasksBase;
    std::vector<std::string> subjects;
    int dayForSimulation;
    int pointBound;
    Student generateStudent(std::mt19937& gen);
    Task generateTask(std::mt19937& gen);
public:
    Model() = default;
    Model (int numOfstudents, int numOfTasks, const std::vector<std::string>& subjectsIn); //constructor with random generation of data
    void addRandStudents (int numOfStu);
    void addRandTasks (int numOfTas);
    void reset();
    void startTimeLimSim (int days); //gets number of days for simulation
    void startPointLimSim (int points); //gets number of points to be reached throe the simulation;
    void startLimitLessSim();

    [[nodiscard]] int getNumOfStudents() const;
    [[nodiscard]] int getNumOfTasks() const;
    [[nodiscard]] std::vector<Student> getStudents() const;
    [[nodiscard]] std::vector<Task> getTasks() const;

};


#endif //INC_1_TASK_MODEL_H