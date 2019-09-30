#include "task.hpp"
#include <iomanip>

ostream& operator<<(ostream& os, const task& cp)
{
  char flag = ' ';
  if(cp.status){
    flag = 'x';
  }
  os << "["<< flag<< "]"
     << " * |"
     << std::setw(20) << std::left
     << cp.name
     << "| H:"
     << std::setw(2) << std::right
     << cp.hours
     << " P:"
     << std::setw(2) << cp.priority;
  return os;
}
//
// prefix increment operator
task& task::operator++(){
  if(priority < 99)
    priority++;
  return *this;
}

// postfix increment operator
task  task::operator++(int){
  task temp = *this;
  if(priority < 99)
    ++*this;
  return temp;
}

// prefix decrement operator
task& task::operator--(){
  if(priority > 0)
    priority--;
  return *this;
}

// postfix decrement operator
task  task::operator--(int){
  task temp = *this;
  if(priority > 0)
    --*this;
  return temp;
}



