#include "mint.h"

int main (int argc, char **argv) {
  if (argc > 1) {
    Mint().Run(argv[1]);
  } else {
    Mint().Run();
  }

  return 0;
}