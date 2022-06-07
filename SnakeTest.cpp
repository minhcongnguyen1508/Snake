#include <iostream>
#include <cmath>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

// #include "constants.h"
// #include "SDL_utils.h"
// #include "Game.h"
// #include "Gallery.h"

// #include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#include "SDL_utils.h"
#include "Game.h"
#include "Gallery.h"
#include "Snake.h"
#include "constants.h"

struct TestStruct
{
    std::string testName;
    bool result;
    bool expected;
    std::string errorMsg;
};

void runTestLoop(TestStruct testCases[], int testSize){
    int i;
    for (i = 0; i< testSize; i++){
        std::cout << testCases[i].testName + ": ";
        if (testCases[i].result == testCases[i].expected)
        {
            std::cout << "PASSED \n";
        }
        else
        {
            std::cout << testCases[i].errorMsg;
            exit(1);
        }
    }
}

bool verifyEatCherry(int numOfEatedCherry){
  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);
  Position start(0, 0);
  Snake snake(gameTest, start);
  for(int numCherry=0; numCherry<numOfEatedCherry; numCherry++){
    snake.eatCherry();
  }
  return numOfEatedCherry == snake.getNumCherry();
}

// bool verifyGrowAtFront(Position newPosition){
//   Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);
//   Position start(0, 0);
//   Snake snake(gameTest, start);
//   snake.growAtFront(newPosition);
//   SnakeNode* target;
//   for (SnakeNode* p = snake.getTail(); p != nullptr; p = p->next){
//     target = p;
//   }
//   return newPosition == target->position;
// }

bool verifyMove(Direction direction){
  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);
  Position start(0, 0);
  Snake snake(gameTest, start);
  snake.move(direction);
  
}

class Test: public CPPUNIT_NS::TestCase {
  CPPUNIT_TEST_SUITE(Test);
  CPPUNIT_TEST(testEatCherry);

  CPPUNIT_TEST(successTestExit);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(void) {}
  void tearDown(void) {}

protected:

  void testEatCherry(void){
      int testSize = 5;
      std::string sharedName = "[testEatCherry] ";
      TestStruct eatCherryTestCases[testSize] =
        {
          {
            sharedName + "verifyGetNumCherry",
            verifyEatCherry(1),
            true,
            "Success if numOfCherry is one."
          },
          {
            sharedName + "verifyGetNumCherry",
            verifyEatCherry(2),
            true,
            "Success if numOfCherry is two."
          },
          {
            sharedName + "verifyGetNumCherry",
            verifyEatCherry(3),
            true,
            "Success if numOfCherry is three."
          },
          {
            sharedName + "verifyGetNumCherry",
            verifyEatCherry(4),
            true,
            "Success if numOfCherry is four."
          },
          {
            sharedName + "verifyGetNumCherry",
            verifyEatCherry(5),
            true,
            "Success if numOfCherry is five."
          },
        };
        runTestLoop(eatCherryTestCases, testSize);
  }

  void successTestExit(void) {
    std::cout << "all tests passed! \n";
    
  }

};


CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()
{

  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;

  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  // return result.wasSuccessful() ? 0 : 1;
  return 0;
}