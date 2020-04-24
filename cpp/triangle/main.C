#include <vector>
#include "basic.hpp"

int test(){

  triangle p1("p1", 1, 2);

  cout  <<  p1 << endl;

  vector<triangle> vp;
  vp.push_back(p1);


  cout << endl;
  cout << "non-ptr vector" << endl;
  for(auto& p : vp)
  {
    cout << p << endl;
  }

  return 0;
}


int main(void){

  test();

  return 0;
}
