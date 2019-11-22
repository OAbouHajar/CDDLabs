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

#include "SafeBuffer.h"
#include <iostream>
#include <stdlib.h>
#include "Event.h"

SafeBuffer::SafeBuffer(){
    theMutex = std::make_shared<Semaphore>(1);
    theSemaphore = std::make_shared<Semaphore>(0);
}

int SafeBuffer::push(Event newChar){
    theMutex->Wait();
    theData.push_back(newChar);
    int size = theData.size();
    theMutex->Signal();
    theSemaphore->Signal();
    return size;
}

Event SafeBuffer::pop(){
    theSemaphore->Wait();
    theMutex->Wait();
    Event e = theData.back();
    theData.pop_back();
    theMutex->Signal();
    return e;
}
