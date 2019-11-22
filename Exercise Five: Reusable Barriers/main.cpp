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

#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn barrierTask
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){



for(int i=0;i<numLoops;++i){
    //Do first bit of task
    std::cout << "A"<< i ;
    //Barrier
    theBarrier->phase_one();
    //Do second half of task
    std::cout<< "B" << i ;
    theBarrier->phase_two();
  }
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(barrierTask,aBarrier,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
