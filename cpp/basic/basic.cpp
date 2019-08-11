#include <vector>
#include "basic.h"

int test(){

  my_pair p1;
  my_pair p2("p2",10,20);
  p1.x = 1;
  p1.y = 2;
  p1.name = "p1";
  auto p3 = p1;
  p3.name = "p3";

  cout  <<  p1 << endl;
  cout  <<  p2 << endl;
  cout  <<  p3 << endl;

  vector<my_pair*> mpv;
  mpv.push_back(&p1);
  mpv.push_back(&p2);
  mpv.push_back(&p3);

  for(auto p : mpv)
  {
    --(*p);
    cout << *p << endl;
  }

  return 0;
}

int main(void){

  test();

  return 0;
}
