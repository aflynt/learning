#include "proj.hpp"
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

void task::read_task_header(const string hdr)
{
  // get project number
  if( get_btw_str(hdr, "[" , "]") == "x"){
    status = true;
  } else {
    status = false;
  }

  // get name
  auto posBarL = hdr.find("|");
  auto posBarR = hdr.find_last_of("|");
  string lname = hdr.substr(posBarL+1, posBarR-(posBarL+1));
  trim(lname);
  name = lname;
 
  // get hours and priority
  auto posH = hdr.find_last_of("H");
  auto posP = hdr.find_last_of("P");

  hours    = stoi(hdr.substr(posH+2, 2));
  priority = stoi(hdr.substr(posP+2, 2));
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



