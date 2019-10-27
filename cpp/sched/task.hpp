#include <iostream>
#include <string>
using namespace std;

#ifndef TASK_H
#define TASK_H

class task {
  public:
    // constructor
    task(string t_name, int t_pri, int t_hrs, bool t_status) : 
      name(t_name),
      hours(t_hrs),
      status(t_status)
    {
      if(t_pri < 100){
        priority = t_pri;
      } else {
        priority = 99;
      }
      //cout << "ctor_i++ for [" << name <<"]\n";
    }

    // constructor from string
    task(string t_name) : name(t_name), priority(0), hours(1), status(false) {
      //cout << "ctor_d++ for [" << name <<"]\n";
    }

    // default constructor
    task() : name("todo"), priority(0), hours(1), status(false) {
      //cout << "ctor_d++ for [" << name <<"]\n";
    }

    // copy constructor
    task(const task& cp) {
      priority = cp.get_priority();
      hours    = cp.get_hours();
      status   = cp.get_status();
      name     = cp.get_name();
      //cout << "ctor_cp  for [" << name <<"]\n";
    }

    // destructor
    ~task(){
      //cout << "bye-bye to [" << name <<"]\n";
    }

    task& operator=(const task& cp) {
      priority = cp.get_priority();
      hours    = cp.get_hours();
      status   = cp.get_status();
      name     = cp.get_name();
      return *this;
    }

    //methods
    void read_task_header(const string hdr);

    int get_priority(void) const{
      return priority;
    }
    int get_hours(void) const{
      return hours;
    }
    bool get_status(void) const{
      return status;
    }
    string get_name(void) const{
      return name;
    }

    void set_priority(int p){
      priority = p;
    }
    void set_hours(int h){
      hours = h;
    }
    void set_status(bool s){
      status = s;
    }
    void set_name(string n){
      name = n;
    }
    //
    // Regular
    friend bool operator==(const task& x, const task& y) {
      return x.priority == y.priority;
    }
    friend bool operator!=(const task& x, const task& y) {
       return !(x == y);
    }
    //
    // TotallyOrdered
    friend
    bool operator<(const task& x, const task& y) { 
      return x.priority < y.priority;
    }
    friend
    bool operator>(const task& x, const task& y) {
      return y < x;
    }
    friend
    bool operator<=(const task& x, const task& y) {
      return !(y < x);
    }
    friend
    bool operator>=(const task& x, const task& y) {
      return !(x < y);
    } 

    //*fix operators
    task& operator++();    // prefix  increment operator
    task  operator++(int); // postfix increment operator
    task& operator--();    // prefix  decrement operator
    task  operator--(int); // postfix decrement operator

    friend ostream& operator<<(ostream& os, const task& cp);

  private:
    string name;
    int priority;
    int hours;
    bool status;
};


#endif
