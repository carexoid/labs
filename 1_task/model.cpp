//
// Created by daniil on 26.10.2019.
//

#include "model.h"
#include "tasks.h"
#include "students.h"

Model::Model(int numOfstudents, int numOfTasks, const std::vector<std::string>& subjectsIn) : subjects(subjectsIn) {
    for (int i = 0; i < numOfstudents; i++)
        students.push_back(generateStudent());
    for (int i = 0; i < numOfTasks; i++)
        tasks.push_back(generateTask());

}
