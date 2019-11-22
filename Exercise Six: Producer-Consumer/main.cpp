
/**
 * 	
  Authors of Project
	  Osama Abou Hajar, Joseph Kehoe/

  Date wrriten: 
    21 NOV 2019
 *Project Licence
  	You are free to:
		Share — copy and redistribute the material in any medium or format
		Adapt — remix, transform, and build upon the material
		The licensor cannot revoke these freedoms as long as you follow the license terms.
	full term and condition licence avilable at::
		https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
		

*/

#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>
#include "SafeBuffer.h"



static const int num_threads = 100;
const int size=20;


/*! \fn producer
    \brief Creates events and adds them to buffer
*/

void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
    Event event ;
    theBuffer->push(event);
  }
  

}

/*! \fn consumer
    \brief Takes events from buffer and consumes them
*/

void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
    Event event ;
    event = theBuffer->pop();
    event.consume();
  }
  

}

int main(void){

  std::vector<std::thread> producers(num_threads);
  std::vector<std::thread> consumers(num_threads);
  std::shared_ptr<SafeBuffer> aBuffer( new SafeBuffer());
  /**< Launch the threads  */
  for(std::thread& prod: producers){
    prod=std::thread(producer,aBuffer,10);
  }

  for(std::thread& cons: consumers){
    cons=std::thread(consumer,aBuffer,10);
  }

  /**< Join the threads with the main thread */
  for (auto& p :producers){
      p.join();
  }
  for (auto& c :consumers){
      c.join();
  }

  std::cout  << std::endl;
  return 0;
}
