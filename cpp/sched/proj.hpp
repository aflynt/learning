#include "task.hpp"
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>

#ifndef PROJECT_H
#define PROJECT_H

class project {
  public:
    // constructors
    project(): name("proj"), pnum(0){}
    project(string pname): name(pname), pnum(0){}
    project(string pname, unsigned int pn): name(pname), pnum(pn){}
    
    // methods
    string get_name(void) const{
      return name;
    }
    unsigned int get_pnum(void) const{
      return pnum;
    }
    friend ostream& operator<<(ostream& os, const project& cp);

    void add_task(const task t){
      tv.push_back(t);
    }
    task back_task() const;
    void pop_task();
    bool hasTasks()const {
      if(tv.size()>0)
        return true;
      else
        return false;
    }
    int num_tasks() const{
      return tv.size();
    }
    void save_proj(string fname) const;
    string get_proj_title() const;

    void set_name(const string iname) { name = iname;} 
    void set_pnum(const int num)      { pnum = num;} 

  private:
    string name;
    unsigned int pnum;
    vector<task> tv;
};

string get_fname(int argc, char * argv[]);
string get_btw_str(const string title, const string posL, const string posR);
int read_proj_header(project& p, const string name);

// trim from beginning (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch){
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch){
        return !std::isspace(ch);
        }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

#endif
