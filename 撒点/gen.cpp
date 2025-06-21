#include "../generator.h"

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int num = opt<int>("t");
    int upper = (num == 1 ? 5 : (num <= 3 ? 1000 : 1e9));
    println(rnd.next(upper / 10, upper));
}