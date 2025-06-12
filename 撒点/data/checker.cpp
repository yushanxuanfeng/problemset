#include "testlib.h"
#include <cmath>

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    double ja = ouf.readDouble();
    int point = round((ja / ans.readDouble()) / 0.1);
    if(point == 10) quitf(_ok, "The answer is correct");
    else quitf(_pc(point), "Your answer is not so correct.");
}
