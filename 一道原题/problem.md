# 问题描述

这道题只有一句话：给定序列 $a$ 和若干询问 $l, r$，求区间 $[l, r]$ 的绝对众数。如果没有，输出 $-1$。

这很显然是一道原题。所以为了让这道题稍微有点难度，这道题的数据范围被开大了。因为输入过大，因此本题的输入比较特殊。

# 输入输出格式

## 输入格式
第一行三个整数 $n, q, seed$。  
第二行 $n$ 个整数，第 $i$ 个整数代表 $a_i$。  
接下来共有 $q$ 个询问，用下面的程序生成：

```cpp
using ull = unsigned long long;
ull seed;

ull shift(ull x) {
  x ^= seed; x ^= x << 13;
  x ^= x >> 7; x ^= x << 17;
  x ^= seed; return x;
}

ull _rand() {
    seed = shift(seed);
    return shift(seed) ^ shift(seed ^ (seed << 17));
}

pair<int, int> get_query() {
    int a = _rand() % n, b = _rand() % n;
    a++, b++; if(a > b) swap(a, b);
    return make_pair(a, b);
}
```
第 $i$ 次调用 `get_query()` 函数，返回第 $i$ 次询问的 $l, r$。

## 输出格式
输出一行一个整数，为所有 $i*ans_i$ 的异或和，其中 $ans_i$ 为第 $i$ 次询问的答案。若询问的区间不存在区间众数，则**不**计算本次询问。

# 测试样例

```input1
3
2 4
3 5
6 7
```

```output1
1
1
3
```

## 样例解释 1


# 数据范围与约定

对于 $10\%$ 的数据，$ n, q \le 10 $。
对于另外 $20\%$ 的数据，$ n, q \le 10^3 $。
对于 $100\%$ 的数据，$ n \le 10^7, q\le 5\times 10^8, a_i \le 3$。  

本题的时间限制应为 $2$ 秒。
