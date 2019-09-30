#include "proj.hpp"
#include <iomanip>

ostream& operator<<(ostream& os, const project& cp)
{
  os << "<"
     << std::setw(6) << std::right
     << cp.pnum << ">"
     << " * |"
     << std::setw(20) << std::left
     << cp.name
     << "| "
     << cp.tv.size()
     << "\n";
  for(const task& t : cp.tv)
  {
    os << "     " << t << "\n";
  }
  return os;
}

// remove back task
void project::pop_task(){
  if(tv.size() > 0){
    tv.pop_back();
  }
}

// return back task
task project::back_task() const{
  task t;
  if(tv.size() > 0){
    t = tv.back();
  }
  return t;
}
