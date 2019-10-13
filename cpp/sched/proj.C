#include "proj.hpp"

// get file name from cin or cmd line
string get_fname(int argc, char * argv[])
{
  string name;

  if(argc > 1) {
    name = argv[1];
  } else {
    cout << "Enter filename: ";
    getline(cin,name);
  }
  return name;
}

// get string between L/R indicators eg.: < str >
string get_btw_str(const string title, const string posL, const string posR)
{
  auto pos0 = title.find(posL);
  auto pos1 = title.find(posR);

  string substr;
  for(int i = pos0+1; i < pos1; i++){
    substr += title[i];
  }
  return substr;
}

// read in project header
int read_proj_header(project& p, const string title)
{
  //0123456789_123456789_123456789_123456789
  //< 00640> * |whatever            | 9
 
  // get project number
  int pn = stoi( get_btw_str(title, "<" , ">") );

  // get project name
  auto posBarL = title.find("|");
  auto posBarR = title.find_last_of("|");
  string pname = title.substr(posBarL+1, posBarR-(posBarL+1));
  trim(pname);

  // get task size
  string ntasks = title.substr(posBarR+1);
  int n_size = stoi(ntasks);

  // set the projects name, number
  p.set_name(pname);
  p.set_pnum(pn);

  return n_size;
}

// get project title as a string
string project::get_proj_title(void) const
{
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
  os << cp.get_proj_title();

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
void project::pop_task()
{
  if(tv.size() > 0){
    tv.pop_back();
  }
}

// return back task
task project::back_task() const
{
  task t;
  if(tv.size() > 0){
    t = tv.back();
  }
  return t;
}

