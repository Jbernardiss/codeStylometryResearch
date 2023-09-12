#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  /*
    i1 = first fibonacci register
    i2 = second fibonacci register
    i3 = third fibonacci register
  */
  int i1 = 0;
  int i2 = 1;
  int i3;

  int i;
  for(i = 0; i < 10; i++)
  {
    i3 = i1 + i2;
    i1 = i2;
    i2 = i3;
    printf("%i", i3);
  }

  return 0;
}
