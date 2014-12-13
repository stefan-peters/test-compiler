extern char _cov_register(const char* id, int* data, unsigned int size);

static int _cov[7] = {0};
static const char* _cov_id = "0e8a0d28";
static char _cov_is_registered = _cov_register(_cov_id, _cov, 7);

#include <stdlib.h>
#include <stdio.h>

int main() {

    printf("running\n");

    if((true) ? (++_cov[4], true) : (++_cov[5], false)) {
        return 0;
    }
    else {
        if((false) ? (++_cov[2], true) : (++_cov[3], false)) {
            return 2;
        }
    }

    return 1;
}


struct _cov_entry {
    const char* id;
    int* data;
    unsigned int size;
};

// array pro DATEI!

void _cov_at_exit() {

}


char _cov_register(const char* id, int* data, unsigned int size) {
    static int is_registered = 0;
    if((! is_registered) ? (++_cov[0], true) : (++_cov[1], false)) {
        is_registered = 1;
        atexit(_cov_at_exit);
    }
    return 1;
}
