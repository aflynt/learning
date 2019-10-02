#include "task.hpp"
#include <vector>

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
    string proj_title() const;

  private:
    string name;
    unsigned int pnum;
    vector<task> tv;
};

#endif
