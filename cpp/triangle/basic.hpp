#include <iostream>
#include <string>
using namespace std;

class triangle {
  public:
    triangle(string nn, double aa, double bb, double cc)
      : a(aa), b(bb), c(cc), name(nn)
    {
      cout << "ctor_i for [" << name <<"]\n";
    }
    triangle() : name("pair"), a(0), b(0), c(0){ //ctor
      cout << "ctor_d for [" << name <<"]\n";
    }
    triangle(const triangle& cp) { // cp ctor
      a = cp.a;
      b = cp.b;
      c = cp.c;
      name = cp.name;
      cout << "ctor_cp  for [" << name <<"]\n";
    }
    ~triangle(){
      cout << "bye-bye to [" << name <<"]\n";
    }

    friend ostream& operator<<(ostream& os, const triangle& cp);

  private:
    string name;
    double a, b, c;

};


ostream& operator<<(ostream& os, const triangle& cp)
{
  os << cp.name << ": " << cp.a << ',' << cp.b;
  return os;
}
