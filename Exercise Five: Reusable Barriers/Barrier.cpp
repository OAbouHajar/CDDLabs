// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: Keep count of number of threads. Only allow one thread past the barrier, as created, at a time. 
// Each thread locks the barrier while past the threshold and unlocks on leab=ving.
// Each thread which wishes to cces the barrier incrments the counter and waits there turn.
// After a thread exits one section/barrier - it must wait before accessing the next
// So one thread cannot get ahead of the others by more than one barrier
// Author: Osama Abou Hajar
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>


Barrier::Barrier(int numThreads)
{
    this->numThreads = numThreads;
    current_count = 0;
    lock.reset(new Semaphore(1));
    turnstile_one.reset(new Semaphore(0));
    turnstile_two.reset(new Semaphore(1));
}


Barrier::~Barrier()
{
    lock.reset();
    turnstile_one.reset();
    turnstile_two.reset();
}


void Barrier::phase_one()
{
    lock->Wait();
    ++current_count;
    if (current_count == numThreads)
    {
        turnstile_two->Wait();
        turnstile_one->Signal();
    }
    lock->Signal();
    turnstile_one->Wait();
    turnstile_one->Signal();

}


void Barrier::phase_two()
{
    lock->Wait();
    --current_count;
    if (current_count == 0)
    {
        turnstile_one->Wait();
        turnstile_two->Signal();
    }
    lock->Signal();
    turnstile_two->Wait();
    turnstile_two->Signal();

}


void Barrier::wait()
{
    phase_one();
    phase_two();
}



// 
// Barrier.cpp ends here
