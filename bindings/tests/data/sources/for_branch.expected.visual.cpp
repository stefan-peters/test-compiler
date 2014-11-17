#include <vector>
#include <iostream>

#define CONDITION i < 10
int get_condition();

void function() {
  int x = 0;
  for (int i = 0; [i < 5]; ++i)
    for (int j = 0; [j < 5]; i++)
      for (; [x < 5]; x++)
        for (x = 1; [x < 5]; x++) break;

  std::vector<int> v;
  for (std::vector<int>::iterator it = v.begin(); [it != v.end()]; ++it) {
    std::cout << ' ' << *it;
  }

  for (int i = 0; [CONDITION]; i = get_condition()) break;

  for (;;) {
    break;
  }
  for (;;) break;
}
