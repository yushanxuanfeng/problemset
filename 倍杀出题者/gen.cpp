#include "../generator/generator.h"

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int num = opt<int>("t");
    int upper = num == 1 ? 3 : (num <= 3 ? 300 : int(2e5 / 3));
    int n = rnd.next(std::max(1, int(upper / 1.3)), upper);
    String str; str.lower(n);
    str += str + str; assert(str.str.length() == 3 * n);
    for(int i = 1; i <= n; i++) str[i * 2 - 1 + n] = str[i * 2 + n] = str[i];
    str.random_insert(std::max(1, upper / 70), 'a');
    std::cout << (str.str);
}