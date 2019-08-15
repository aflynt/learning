#include "basic.hpp"

int test(){

  my_pair p1("p1", 1, 2);
  my_pair p2("p2", 2, 4);
  my_pair p3("p3", 3, 6);
  //p1.x = 1;
  //p1.y = 2;
  //p1.name = "p1";
  //auto p3 = p1;
  //p3.name = "p3";

  cout  <<  p1 << endl;
  cout  <<  p2 << endl;
  cout  <<  p3 << endl;

  vector<my_pair> vp;
  vp.push_back(p1);
  vp.push_back(p2);
  vp.push_back(p3);


  cout << endl;
  cout << "non-ptr vector" << endl;
  for(auto& p : vp)
  {
    (p)--;
    --(p);
    cout << p << endl;
  }

  return 0;
}


int main(void){

  test();

  return 0;
}
