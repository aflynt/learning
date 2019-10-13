#include "proj.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

// get project title as a string
string project::proj_title(void) const{
  std::stringstream buff;
  buff << "<"
     << std::setw(6) << std::right
     << pnum << ">"
     << " * |"
     << std::setw(20) << std::left
     << name
     << "| "
     << tv.size()
     << "\n";
  return buff.str();
}

// write project to stream
ostream& operator<<(ostream& os, const project& cp)
{
  os << cp.proj_title();

  for(const task& t : cp.tv)
    os << "     " << t << "\n";

  return os;
}

// save project to file
void project::save_proj(string fname) const
{
  std::ofstream myfile;
  myfile.open(fname, ios::out | ios::app);

  if(myfile.is_open()){
    myfile << *this;

    myfile.close();
  }
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
