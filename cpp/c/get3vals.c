#include <stdio.h>
//
// print 3 vars and their names
void prinvars(int x, int y, int z, char * xs, char * ys, char * zs)
{
  printf("%s = %d\n",xs, x);
  printf("%s = %d\n",ys, y);
  printf("%s = %d\n",zs, z);
}

// build a struct to pass result around
struct res
{
  int x;
  int y;
  int z;
};

// return a res struct
struct res square_struct(struct res ins)
{
  // make a local struct res
  struct res r1 = {10,20,30};
  r1.x = ins.x * ins.x;
  r1.y = ins.y * ins.y;
  r1.z = ins.z * ins.z;

  //return struct
  return r1;
}

// pass 3 pointers to change
void square_ptrs(int* a, int* b, int* c)
{
  *a *= *a;
  *b *= *b;
  *c *= *c;
}

// pass array by ref to change
void square_arr(int* arr, int size)
{
  int i;
  for(i = 0; i < size; i++)
  {
    int val = arr[i];
    arr[i] *= val;
  }
}

void test_struct(void)
{
  struct res myresult = {4,8,16};

  printf("\n\nTESTING: Structs\n");
  printf("before func\n");
  prinvars(myresult.x,myresult.y,myresult.z,"m.x","m.y","m.z");

  myresult = square_struct(myresult);

  printf("\nafter func\n");
  prinvars(myresult.x,myresult.y,myresult.z,"m.x","m.y","m.z");
}

void test_pointers(void)
{
  int p= 4;
  int q= 8;
  int r= 16;
  //pass by reference (give pointer to address of variables to function)

  printf("\n\nTESTING: passing pointers\n");
  printf("before func\n");
  prinvars(p,q,r,"p","q","r");

  square_ptrs(&p, &q, &r);

  printf("\nafter func\n");
  prinvars(p,q,r,"p","q","r");
}

void test_array(void)
{
  int arr[] = {4,8,16};
  
  printf("\n\nTESTING: passing an array\n");
  printf("before func\n");
  prinvars(arr[0],arr[1],arr[2],"arr[0]","arr[1]","arr[2]");

  // pass an array
  square_arr(arr,3);

  printf("\nafter func\n");
  prinvars(arr[0],arr[1],arr[2],"arr[0]","arr[1]","arr[2]");
}

int main(void)
{

  test_struct();
  test_pointers();
  test_array();

  return 0;
}
