#include "../generator/generator.h"

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int num = opt<int>("t");
    String str; int n;
    if(num <= 4) {
        int upper = (num > 2 ? 3000 : 10);
        str.lower(n = rnd.next(1, upper));
    } else {
        if(num == 5) str.str = "a", str.repeat(n = rnd.next(int(9e3), int(1e4)));
        if(num == 6) str.str = "ab", str.repeat(n = rnd.next(int(4e3), int(5e3)));
        if(num == 7) str.lower(n = rnd.next(int(9e3), int(1e4)));
        if(num > 7) str.lower(n = rnd.next(int(4e5), int(5e5)));
    }
    str.print();
    println(num == 7 ? 0 : std::min(rnd.next(1, n), 10));
}