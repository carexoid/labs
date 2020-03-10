//
// Created by daniil on 26.10.2019.
//

#include "model.h"
#include "tasks.h"
#include "students.h"

Model::Model(int numOfstudents, int numOfTasks, const std::vector<std::string>& subjectsIn)
: subjects(subjectsIn),studentsNum(numOfstudents), tasksNum(numOfTasks) {
    std::mt19937 gen(time(0));
    for (int i = 0; i < numOfstudents; i++){
        students.push_back( generateStudent(gen));
    }
    studentsBase = students;


    for (int i = 0; i < numOfTasks; i++)
        tasks.push_back(generateTask(gen));
    tasksBase = tasks;
}

Task Model::generateTask(std::mt19937& gen) {
    std::uniform_int_distribution<> uidForPoints(1, 100), uidFortype(1,4), forSubj(0,subjects.size()-1), uidForCompl(1,10);
    std::vector<int> randInd(subjects.size()-1);
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
    return Task(subjIn,uidForPoints(gen),uidFortype(gen), uidForCompl(gen) );
}

Student Model::generateStudent(std::mt19937& gen) {

    std::uniform_int_distribution<> uidForKnowledge(0, 100), uidForStrategy(1,4);
    std::vector< std::pair< std::string, int> > KnowledgeIn;
    for (const auto& i: subjects)
        KnowledgeIn.emplace_back(i,uidForKnowledge(gen));
    return Student(KnowledgeIn, uidForStrategy(gen));
}

void Model::addRandStudents(int numOfStu) {
    std::mt19937 gen(time(0));
    for (int i = 0; i < numOfStu; i++)
        students.push_back(generateStudent(gen));
}

void Model::addRandTasks(int numOfTas) {
    std::mt19937 gen(time(0));
    for (int i = 0; i < numOfTas; i++)
        tasks.push_back(generateTask(gen));
}

void Model::reset() {
    students = studentsBase;
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
    std::cout << "******************Tasks in simulation*********************************";
    for (const auto& i:tasks)
        std::cout << i;
    std::cout << "******************Students before simulation*********************************";
    for (const auto& i:students)
        std::cout << i;

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
                taskInProcess[i] = choosenTask;
            }
       }  //tasks chosen
       for (int i = 0; i < students.size(); i++){
           daysToWork[i]--;
       }
       days--;

    }  //simulation ended
    std::cout << "******************Students after simulation*********************************";
    for (const auto& i:students)
        std::cout << i;

}

void Model::startPointLimSim(int points) {
    std::vector<int> daysToWork(students.size()); //indexes equel to indexes of students in vector of students
    std::vector<int> taskInProcess (students.size());// has index of task being done
    for (auto &i: taskInProcess)
        i = -1;
    std::vector<int> pointsGot(students.size()); //indexes equel to indexes of students in vector of students
    std::vector< std::vector<bool> > doneStTsk(students.size());
    for (auto& i: doneStTsk){
        i.resize(tasks.size());
    }
    std::cout << "******************Tasks in simulation*********************************";
    for (const auto& i:tasks)
        std::cout << i;
    std::cout << "******************Students before simulation*********************************";
    for (const auto& i:students)
        std::cout << i;
    int sum = 0;
    while(sum < points){


        for (int i = 0 ; i < students.size(); i++){
            if (!daysToWork[i]){
                if (taskInProcess[i] != -1){
                    doneStTsk[i][taskInProcess[i]] = 1;
                    int gotPoints = tasks[taskInProcess[i]].pointsFor(students[i]);
                    sum += gotPoints;
                    students[i].addPoints(gotPoints);
                    students[i].updKnowledges(tasks[taskInProcess[i]]);
                }
                int choosenTask = students[i].chooseIndOfTask(tasks,doneStTsk[i]);
                daysToWork[i] = tasks[choosenTask].daysFor(students[i]);
                taskInProcess[i] = choosenTask;
            }
        }  //tasks chosen
        for (int i = 0; i < students.size(); i++){
            daysToWork[i]--;
        }

    }  //simulation ended
    std::cout << "******************Students after simulation*********************************";
    for (const auto& i:students)
        std::cout << i;
}

namespace LimLessSim{
    bool allTasksDone( const std::vector< std::vector<bool> >& doneStTsk){
        for (auto i: doneStTsk)
            for (const auto& j:i)
                if (!j)
                    return 0;
        return 1;
    }

    bool cmpForReslists(const std::pair<Task, int>& a, const std::pair<Task,int>& b){
        return a.second > b.second;
    }
}


void Model::startLimitLessSim() {
    std::vector< std::pair< Task,int> > list1,list2,list3;
    for (const auto& i: tasks){
        list1.emplace_back(i,0);
        list2.emplace_back(i,0);
        list3.emplace_back(i,i.getComplexity());
    }
    std::vector<int> daysToWork(students.size()); //indexes equel to indexes of students in vector of students
    std::vector<int> taskInProcess (students.size());// has index of task being done
    for (auto &i: taskInProcess)
        i = -1;
    std::vector<int> pointsGot(students.size()); //indexes equel to indexes of students in vector of students
    std::vector< std::vector<bool> > doneStTsk(students.size());

    for (auto& i: doneStTsk){
        i.resize(tasks.size());
    }
    std::cout << "******************Tasks in simulation*********************************";
    for (const auto& i:tasks)
        std::cout << i;
    std::cout << "******************Students before simulation*********************************";
    for (const auto& i:students)
        std::cout << i;
    int sum = 0;
    std::vector< int > currentKn (students.size());
    for (int i = 0; i <currentKn.size();i++){
        for (const auto& j:subjects)
            currentKn[i] += students[i].getLevel(j);
    }
    while(!LimLessSim::allTasksDone(doneStTsk)){
        for (int i = 0 ; i < students.size(); i++){
            if (!daysToWork[i]){
                if (taskInProcess[i] != -1){
                    doneStTsk[i][taskInProcess[i]] = 1;
                    int gotPoints = tasks[taskInProcess[i]].pointsFor(students[i]);
                    sum += gotPoints;
                    students[i].addPoints(gotPoints);
                    students[i].updKnowledges(tasks[taskInProcess[i]]);
                    int newKn = 0;
                    for (const auto &it:subjects)
                        newKn += students[i].getLevel(it);
                    list2[taskInProcess[i]].second += (newKn - currentKn[i]);
                    currentKn[i] = newKn;
                }
                int choosenTask = students[i].chooseIndOfTask(tasks,doneStTsk[i]);
                daysToWork[i] = tasks[choosenTask].daysFor(students[i]);
                taskInProcess[i] = choosenTask;
                list1[choosenTask].second += daysToWork[i];
            }
        }  //tasks chosen
        for (int i = 0; i < students.size(); i++){
            daysToWork[i]--;
        }

    }  //simulation ended
    std::cout << "******************Students after simulation*********************************";
    for (const auto& i:students)
        std::cout << i;

    std::sort(list1.begin(),list1.end(),&LimLessSim::cmpForReslists);
    std::sort(list2.begin(),list2.end(),&LimLessSim::cmpForReslists);
    std::sort(list3.begin(),list3.end(),&LimLessSim::cmpForReslists);

    std::vector<Task > resList;
    for (int i = 0; i < list1.size(); i++){
        if ( std::find(resList.begin(), resList.end(), list1[i].first) == resList.end() )
            resList.push_back(list1[i].first);
        if ( std::find(resList.begin(), resList.end(), list2[i].first) == resList.end() )
            resList.push_back(list2[i].first);
        if ( std::find(resList.begin(), resList.end(), list3[i].first) == resList.end() )
            resList.push_back(list3[i].first);
    }
    std::cout << "**********************************First list******************************";
    for (int i = 0; i < list1.size(); i++){
        std::cout << list1[i].first << "Elapsed time in days: " << list1[i].second << "\n\n\n";
    }
    std::cout << "**********************************Second list******************************";
    for (int i = 0; i < list1.size(); i++){
        std::cout << list2[i].first << "Gained level of knowledges: " << list2[i].second << "\n\n\n";
    }
    std::cout << "**********************************Third list******************************";
    for (int i = 0; i < list1.size(); i++){
        std::cout << list3[i].first <<"Complexity: " << list3[i].second << "\n\n\n";
    }
    std::cout << "**********************************United list******************************";
    for (int i = 0; i < resList.size(); i++){
        std::cout << resList[i] << "\n\n\n";
    }

}

int Model::getNumOfStudents() const {
    return studentsNum;
}

int Model::getNumOfTasks() const {
    return tasksNum;
}

std::vector<Student> Model::getStudents() const {
    return studentsBase;
}

std::vector<Task> Model::getTasks() const {
    return tasksBase;
}