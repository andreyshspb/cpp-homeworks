#include "doComputation.h"
#include "max.h"
#include "logDebug.h"

int max(int a, int b) {
    int m = 0;
    if (a > b) {
       m = a;
    } else {
        m = b;
    }
    logDebug('m');
    return m;
}

int main(void) {
    int a = doComputation(5, 7.0);
    int b = 5;
    max(a, b);
    logDebug('!');
    return 0;
}
