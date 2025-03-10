#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \class Signal
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
    \author: Osama Abou Hajar, C00220135

*/

/*!
 * \fn taskOne
 * \brief  displays a message first
 *
 * Using a Signal() method at the end of the taskOne
 * with this we make sure that task one is blocking task two to begin before task has completed
 *
 * \param theSemaphore :to lock and unlock the access
 * \param delay :to make a sleep time for the program 
*/

void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
 
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}

/*!\fn taskTwo
 * \brief  Displays a message second
 * \param theSemaphore :to lock and unlock the access
 * TaskTwo can not start before the task one completed as first line in TaskTwo is call
 * the Wait() function where it's lock any thread to start before ths one finish and Signal() 
 * to be called */

void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
  
}


int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;

  // /sssss
}
