#include "task.hpp"
#include "proj.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


project ask_for_proj()
{
  string name;
  int num;

  cout << "ENTER project name : ";
  cin >> name;
  cout << "ENTER project #    : ";
  cin >> num;
  project pj(name, num);

  return pj;
}

project create_project()
{

  project pj = ask_for_proj();
  cout << "created pj = " << pj << endl;

  int addTask;
  string prompt = "add task? (1=yes): ";
  cout << prompt;
  cin >> addTask;

  while( addTask == 1){
    char tname[256];
    int tpriority;
    int thours;

    cout << "ENTER task name : " << endl;
    cin.ignore();
    std::cin.getline(tname, 256);
    //get_full_line(cin, tname);
    cout << "tname = " << tname << endl;
    //cin >> tname;

    cout << "ENTER priority #: ";
    cin >> tpriority;

    cout << "ENTER hours    #: ";
    cin >> thours;

    task t(tname, tpriority, thours, false);
    pj.add_task(t);

    cout << prompt;
    cin >> addTask;
  }

  return pj;
}

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

void save_projects(const vector<project> p)
{
  // save projects to file
  for(const project& pi : p){
    pi.save_proj("projects.dat");
    //p1.save_proj(p1.get_name()+".dat");
  }
}

void print_projects(const vector<project>& p)
{
  // save projects to file
  for(const project& pi : p){
    cout << pi << endl;
  }
}

void edit_project(const vector<project>& p)
{
  cout << "here are the names of all the projects" << endl;

  for(const project& pi : p){
    cout << pi.get_pnum() << " " << pi.get_name() << endl;
  }

  cout << "\nWhich project number would you like to edit? ";
  int choice = 0;
  cin >> choice;
  for(const project& pi : p){
    if (choice == pi.get_pnum())
    {
      cout << "we found your choice of the following: \n";
      cout << pi << endl;
    }
  }

}

vector<project> read_file(int argc, char * argv[])
{
  string name;

  if(argc > 1){
    name = argv[1];
  } else {
    cout << "Enter filename: ";
    cin >> name;
  }
  cout << "you requested: " << name << endl;

  // open file "name"
  ifstream myfile;
  myfile.open(name, ios::in);

  vector<project> vp;
  if(myfile.is_open()) {

    string title;
    // get line with project title
    while(getline(myfile,title)){

      // make a new project from header
      project p;
      int n_size = read_proj_header(p, title);

      //cout << "proj num  =[" << p.get_pnum()  << "]" << endl;
      //cout << "pname     =[" << p.get_name() << "]" << endl;
      //cout << "task size =[" << n_size << "]" << endl;

      for(int i = 0; i < n_size; ++i){
        string tstring;
        task t;
        getline(myfile,tstring);
        t.read_task_header(tstring);
        //cout << t << endl;
        p.add_task(t);
      }
      vp.push_back(p);
    }
    myfile.close();
  }

  for(project& pi : vp){
    cout << pi << endl;
  }

  return vp;
}

bool print_main_options()
{
  cout << "Choose from options below:" << endl;
  cout << "0: create project" << endl;
  cout << "1: read   file" << endl;
  cout << "2: save   projects" << endl;
  cout << "3: print  projects" << endl;
  cout << "4: edit   project" << endl;
  cout << "9: quit" << endl;
  return true;
}

int main(int argc, char * argv[])
{
  vector<project> vp;

  print_main_options();

  int choice = 0;
  while(cin >> choice){
    project newp;
    switch (choice){
      case 0:  // create new project
        newp = create_project();
        vp.push_back(newp);
        break;
      case 1:  // read file
        vp = read_file(argc, argv);
        break;
      case 2:  // save project
        save_projects(vp);
        break;
      case 3:  // print project
        print_projects(vp);
        break;
      case 4:  // edit project
        edit_project(vp);
        break;
      case 9:   // quit
        return 0;
      default:
        continue;
    }
    print_main_options();
  }

  return 0;
}
