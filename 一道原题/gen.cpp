#include "../generator.h"

using ull = unsigned long long;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int num = opt<int>("t");
    int uppern = (num == 1 ? 10 : (num <= 3 ? 1000 : int(1e6)));
    int upperq = (num == 1 ? 10 : (num <= 3 ? 1000 : int(1e9)));
    int n = rnd.next(uppern / 10, uppern), q = rnd.next(upperq / 10, upperq);
    ull seed = rnd.next(1.0, double(LONG_LONG_MAX));
    println(n, q, seed);
    Array<int> arr; arr.basic_gen(n, 1, 2);
    arr.randomly_insert(std::min(1000, n / 3), 3).print();
}