#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    return 1;
  }

  float out = atof(argv[1]);

  printf("0x%x\n", *(int*)(&out));
  return 0;
}
