#include "Semaphore.h"
#include <iostream>

#include <thread>
#include <chrono>

int counter=0;
/*! \class Signal
    \brief An Implementation of a Rendezvous using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, std::shared_ptr<Semaphore>  theMutex){
  std::cout <<"Task has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  theMutex->Wait();
  counter++;
  theMutex->Signal();
  if (counter==10){
    theSemaphore->Signal();
     theMutex->Signal();
     theSemaphore->Wait();
  }
   else{
     theMutex->Signal();
    theSemaphore->Wait();
    theSemaphore->Signal();
     }
  std::cout << "Task has left!"<<std::endl;
}


int main(void){
  // int counter=0;
  std::thread threadArray[10];
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> mutex1( new Semaphore);
  mutex1->Signal();
  /**< Launch the threads  */
  for(int i=0;i<10;++i)
    threadArray[i]=std::thread(taskOne,sem1,mutex1);
 
  std::cout << "Launched from the main\n";
  for(int i=0;i<10;++i) threadArray[i].join();
  return 0;
}
