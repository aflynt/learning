#include "task.hpp"
#include "proj.hpp"
#include <algorithm>

int test()
{
  project p1("mcl", 95792);
  cout << p1 << endl;
  // task: name priority hours status
  task t1("email"       , 1,5,0);
  task t2("por update"  , 2,5,0);
  task t3("agard resume", 3,5,0);
  task t4("future work" , 4,5,0);
  task t5("temp tuning");
  task t6;
  task t7 = t5;

  vector<task> vt;
  vt.push_back(t1);
  vt.push_back(t2);
  vt.push_back(t3);
  vt.push_back(t4);
  vt.push_back(t5);
  vt.push_back(t6);
  vt.push_back(t7);


  // look for keyword
  cout << "looking for keyword" << endl;
  for(auto& t : vt)
  {
    auto found = t.get_name().find("tuning");

    if(found!=std::string::npos){
      t.set_status(true);
    }
  }

  // sort based on priority
  sort(vt.begin(), vt.end());

  cout << "after sorting" << endl;
  for(auto& t : vt){
    p1.add_task(t);
    //cout << t << endl;
  }
  cout << "before loop" << endl;
  cout << p1 << endl;
  cout << endl;

  while(p1.hasTasks()){
    cout << p1 << endl;
    task t = p1.back_task();
    cout << "pulling task:" << t << endl;
    p1.pop_task();
  }

  return 0;
}


int main(void){

  test();

  return 0;
}
