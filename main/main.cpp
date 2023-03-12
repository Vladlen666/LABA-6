#include <crtdbg.h>
#include "Interface.h"

void useInterface() {
  Interface gui;
  gui.Run();
  system("pause");
}

int main() {
  useInterface();
  _CrtDumpMemoryLeaks();
  return 0;
}
