#include "task.hpp"
#include "proj.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

int make_proj()
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
  // save project to file
  p1.save_proj(p1.get_name()+".dat");

  cout << "before loop" << endl;
  cout << p1 << endl;
  cout << endl;

  //  pull tasks out
  //while(p1.hasTasks()){
  //  cout << p1 << endl;
  //  task t = p1.back_task();
  //  cout << "pulling task:" << t << endl;
  //  p1.pop_task();
  //}

  return 0;
}

void read_file(int argc, char * argv[]){

  string name;

  if(argc > 1){
    name = argv[1];
  }
  else{
    cout << "Enter filename: ";
    getline(cin,name);
  }
  cout << "you requested: " << name << endl;

  ifstream myfile;
  myfile.open(name, ios::in);

  string title;
  if(myfile.is_open()){
    // get title
    getline(myfile,title);
    cout << "T: " << title << endl;
    string pnum = title.substr(1,6);
    string pname = title.substr(12,20);
    string ntasks = title.substr(title.size()-2,2);

    cout << "pname  [" << pname << "] "<< endl;
    cout << " pnum  [" << pnum << "] "<< endl;
    cout << "ntasks [" << ntasks << "] "<< endl;
    pname.erase(pname.find_last_not_of(" \n\r\t")+1);

    int n_pnum = stoi(pnum);
    int n_size = stoi(ntasks);

    cout << "proj name = " << pname << endl;
    cout << "proj num  = " << n_pnum << endl;
    cout << "task size = " << n_size << endl;

    // get tasks
    while( getline(myfile,title)){
      cout << title << endl;
    }
    myfile.close();
  }
}

int main(int argc, char * argv[]){

  //make_proj();
  read_file(argc, argv);


  return 0;
}
