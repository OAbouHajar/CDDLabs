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

#ifndef SEMAPHORE_H
#define SEMAPHORE_H 
#include <mutex>
#include <condition_variable>
#include <chrono>
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/


class Semaphore
{
private:
    unsigned int m_uiCount; /*!< Holds the Semaphore count */
    std::mutex m_mutex;
    std::condition_variable m_condition;

public:
    Semaphore(unsigned int uiCount=0)
          : m_uiCount(uiCount) { };
    void Wait();
    template< typename R,typename P >
    bool Wait(const std::chrono::duration<R,P>& crRelTime);
    void Signal();

};

#endif
