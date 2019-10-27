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

Task Model::generateTask() {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uidForPoints(1, 100), uidFortype(1,4), forSubj(1,subjects.size());
    std::vector<int> randInd(subjects.size()/2);
    std::vector<std::string> subjIn;
    for (auto& i: randInd)
        i = forSubj(gen);
    std::vector<bool> added (subjects.size());
    for (const auto& i: randInd){
        if (!added[i]){
            subjIn.push_back(subjects[i]);
            added[i] = 1;
        }
    }
    return Task(subjIn,uidForPoints(gen),uidFortype(gen));
}

Student Model::generateStudent() {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uidForKnowledge(0, 100), uidForStrategy(1,4);
    std::vector< std::pair< std::string, int> > KnowledgeIn;
    for (const auto& i: subjects)
        KnowledgeIn.emplace_back(i,uidForKnowledge(gen));
    return Student(KnowledgeIn, uidForStrategy(gen));
}

void Model::addRandStudents(int numOfStu) {
    for (int i = 0; i < numOfStu; i++)
        students.push_back(generateStudent());
}

void Model::addRandTasks(int numOfTas) {
    for (int i = 0; i < numOfTas; i++)
        tasks.push_back(generateTask());
}

void Model::startTimeLimSim(int days) {
    std::vector<int> daysToWork(students.size()); //indexes equel to indexes of students in vector of students
    std::vector<int> taskInProcess (students.size());// has index of task being done
    for (auto &i: taskInProcess)
        i = -1;
    std::vector<int> pointsGot(students.size()); //indexes equel to indexes of students in vector of students
    std::vector< std::vector<bool> > doneStTsk(students.size());
    for (auto& i: doneStTsk){
        i.resize(tasks.size());
    }
    while(days){
       for (int i = 0 ; i < students.size(); i++){
            if (!daysToWork[i]){
                if (taskInProcess[i] != -1){
                    doneStTsk[i][taskInProcess[i]] = 1;
                    int gotPoints = tasks[taskInProcess[i]].pointsFor(students[i]);
                    students[i].addPoints(gotPoints);
                    students[i].updKnowledges(tasks[taskInProcess[i]]);
                }
                int choosenTask = students[i].chooseIndOfTask(tasks,doneStTsk[i]);
                daysToWork[i] = tasks[choosenTask].daysFor(students[i]);
            }
       }  //tasks chosen
       for (int i = 0; i < students.size(); i++){
           daysToWork[i]--;
       }
       days--;
    }  //simulation ended

}