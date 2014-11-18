#include <vector>

#define CONDITION true and false
int get_condition();

void function() {
  bool x = true ? true : false;
  x = (1 + 2) ? false : true;
  x = get_condition() ? false : true;
  x = CONDITION ? false : true;
}
