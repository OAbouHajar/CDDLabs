#include "Event.h"
#include <iostream>
#include <stdlib.h>

//Output a random alphabetic character in lower case
//the produced variable
Event::Event(){
  theChar = 'a'+rand()%26;
  std::cout << theChar;
}

//output a particular character in upper case
//the consumed variable
void Event::consume(){
    char upperChar = theChar-32;    
    std::cout << upperChar;
}