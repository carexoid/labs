#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tasks.h"
#include "students.h"
#include "model.h"

TEST_CASE("Testing base classes","[task+student]") {
    SECTION("Test 1"){
        std::vector<std::string> subj1 = {"mathanalyses","oop","algos","uzk"};
        Task testedTask1(subj1, 52, 3, 5);
        std::vector<std::string> subj2 = {"english","programing basics","society"};
        Task testedTask2(subj2, 23, 1, 8);
        std::vector< std::pair< std::string, int > > subjects =
                {{"mathanalyses", 24},{"oop",56},{"algos",94},{"uzk",29}};
        int strategy = 2;
        Student testedStudent(subjects, strategy);
        int numOfStudentsForModel = 3, numOfTasksForModel = 5;
        auto testedModel = Model(numOfStudentsForModel, numOfTasksForModel, subj2);

        SECTION("Testing independent methods of task 1"){

            REQUIRE(testedTask1.getMaxPonts() == 52);
            REQUIRE(testedTask1.getComplexity() == 5);
            REQUIRE(testedTask1.getMaxComplexity() == 10);
            REQUIRE(testedTask1.getKnowledges() == subj1);
        }
        SECTION("Testing independent methods of task 2"){

            REQUIRE(testedTask2.getMaxPonts() == 23);
            REQUIRE(testedTask2.getComplexity() == 8);
            REQUIRE(testedTask2.getMaxComplexity() == 10);
            REQUIRE(testedTask2.getKnowledges() == subj2);
        }
        SECTION("Testing independent methods of student"){


            REQUIRE(testedStudent.getKnowledges() == subjects);
            REQUIRE(testedStudent.getLevel("algos") == 94);
            REQUIRE(testedStudent.getLevel("oop") == 56);
            REQUIRE(testedStudent.getLevel("mathanalyses") == 24);
            REQUIRE(testedStudent.getLevel("uzk") == 29);
            REQUIRE(testedStudent.getLevel("economics") == 0);
            REQUIRE(testedStudent.getPoints() == 0);
            REQUIRE(testedStudent.getStrategy() == 2);
            testedStudent.setStrategy(1);
            REQUIRE(testedStudent.getStrategy() == 1);
            testedStudent.addPoints(13);
            REQUIRE(testedStudent.getPoints() == 13);
            testedStudent.addPoints(25);
            REQUIRE(testedStudent.getPoints() == 38);
        }
        SECTION("Testing methods of task, that require student`s info"){
            REQUIRE(testedTask1.pointsFor(testedStudent) <= testedTask1.getMaxPonts());
            REQUIRE(testedTask2.pointsFor(testedStudent) <= testedTask2.getMaxPonts());

        }
        SECTION("Testing methods of student, that require task`s info"){
            REQUIRE(testedStudent.chooseIndOfTask({testedTask1, testedTask2}, std::vector<bool>(2, false)) == 1);
            testedStudent.setStrategy(1);
            REQUIRE(testedStudent.chooseIndOfTask({testedTask1, testedTask2}, std::vector<bool>(2,false)) == 0 );
            REQUIRE(testedStudent.chooseIndOfTask({testedTask1, testedTask2}, std::vector<bool>({true, false})) == 1 );
        }
        SECTION("Testing Model"){
            REQUIRE(testedModel.getStudents().size() == numOfStudentsForModel);
            REQUIRE(testedModel.getTasks().size() == numOfTasksForModel);
        }

//      Not all methods were tested, because of random inside
    }
}
//
// Created by carexoid on 11/02/2020.
//
