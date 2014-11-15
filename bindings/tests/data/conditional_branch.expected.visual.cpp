#include <vector>

#define CONDITION true and false
int get_condition();

void function() {
  [true] ? true : false;
  [(1 + 2)] ? false : true;
  [get_condition()] ? false : true;
  [CONDITION] ? false : true;
}
