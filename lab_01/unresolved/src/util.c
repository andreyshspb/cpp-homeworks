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
