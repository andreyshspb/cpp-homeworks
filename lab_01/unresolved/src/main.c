#include "doComputation.h"
#include "max.h"
#include "logDebug.h"

void rec(int);

int main(void) {
    int a = doComputation(5, 7.0);
    int b = 5;
    max(a, b);
    logDebug('!');

    rec(5);

    return 0;
}
