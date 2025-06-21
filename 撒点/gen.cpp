#include "../generator.h"

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int t = opt<int>("t");
    int upper = (t == 1 ? 5 : (t <= 3 ? 1000 : 1e9));
    println(rnd.next(upper / 10, upper));
}