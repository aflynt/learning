#include <iostream>
#include <string>
#include <vector>
using namespace std;

class my_pair {
  public:
    my_pair(string nn, int xx, int yy) : x(xx), y(yy), name(nn){
      cout << "ctor_i++ for [" << name <<"]\n";
    }
    my_pair() : name("pair"), x(0), y(0) { //ctor
      cout << "ctor_d++ for [" << name <<"]\n";
    }
    my_pair(const my_pair& cp) { // cp ctor
      x = cp.x;
      y = cp.y;
      name = cp.name;
      cout << "ctor_cp  for [" << name <<"]\n";
    }
    ~my_pair(){
      cout << "bye-bye to [" << name <<"]\n";
    }
    string name;
    int x, y;

    my_pair& operator++(); // prefix increment operator
    my_pair  operator++(int); // postfix increment operator
    my_pair& operator--(); // prefix decrement operator
    my_pair  operator--(int); // postfix decrement operator

    friend ostream& operator<<(ostream& os, const my_pair& cp);
};

// prefix increment operator
my_pair& my_pair::operator++(){
  x++;
  y++;
  return *this;
}

// postfix increment operator
my_pair  my_pair::operator++(int){
  my_pair temp = *this;
  ++*this;
  return temp;
}

// prefix decrement operator
my_pair& my_pair::operator--(){
  x--;
  y--;
  return *this;
}

// postfix decrement operator
my_pair  my_pair::operator--(int){
  my_pair temp = *this;
  --*this;
  return temp;
}

ostream& operator<<(ostream& os, const my_pair& cp)
{
  os << cp.name << ": " << cp.x << ',' << cp.y;
  return os;
}
