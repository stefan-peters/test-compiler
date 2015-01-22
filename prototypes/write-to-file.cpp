#include "coverage.h"

COVERAGE_CREATE_BUFFER("0e8a0d28", 4);
coverage_node* _coverage_data = 0;

int main() {

    printf("running\n");

    if(COVERAGE_BRANCH(true, 2, 3)) {
        return 0;
    }
    else {
        if(COVERAGE_BRANCH(false, 0, 1)) {
            return 2;
        }
    }

    return 1;
}

// while( (cond) ? ++[X], true : ++[X], false)
// if - else
// for(;;)
// do while
// :? ConditionOperator

// break
// continue
// return
// goto
// throw

// for(e:c) for range
// compound statement

// label
// catch
// switch
// case
// default

// and or && ||

// function
// statement
// branch
// condition
