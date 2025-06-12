## $\rm{0.Introduction}$

今天模拟赛又遇见了字符串题，又不会做了。恰逢 NOIp，所以写一篇新手向的字符串入门指南。注意这篇博客是写给纯新手的，所以开头会说很多比较简单的东西。  

充分理解了此博客中的所有内容后，可以阅读 [command_block](https://www.luogu.com.cn/blog/command-block/) 的博客以学习更加炫酷的魔法。

如有错误，欢迎指出。

## $1.\rm{Definitions}$
- 一个 **字符集** 为一个全序集合，用 $\Sigma$ 表示。这意味着所有的字符均可以两两比较，若他们不相等，则必有一个大于零一个。若无特殊说明，以下所有的字符串，其字符集均为全体小写英文字母。
- 一个 **字符串** 为若干个字符顺次排列所构成的有序地整体。其中，$s_i$ 为 $s$ 的第 $i$ 个字符，字符串的长度为字符串所包含的字符数量。若无特别说明，以下的 $s,t$ 均为字符串，且下标均从 $1$ 开始。

- 一个字符串 $t$ 是 $s$ 的 **子串**，当且仅当 $\exists l ,\forall i\in[0, \rm{len}], s_{l+i}=t_i$，其中 $\rm{len}$ 为 $t$ 的长度。此时，记 $t=s_{l,l+len}$。
- 一个字符串 $t$ 是 $s$ 的 **子序列** ，当且仅当存在一个长为 $\rm{len}$ 的下标序列 $p$，使得 $s_{p_k}=t_k$。这里要求 $p$ 是严格递增的。
- 一个字符串 $t$ 是 $s$ 的 **前缀** ，当且仅当 $t=s_{1,\rm{len}}$。特别的，若 $t\not=s$，则 $t$ 为 $s$ 的 **真前缀** 。
- 一个字符串 $t$ 是 $s$ 的 **后缀** ，当且仅当 $t=s_{n-\rm{len},n}$。特别的，若 $t\not=s$，则 $t$ 为 $s$ 的 **真后缀** 。
- 一个字符串 $s$ 是 **回文** 的，当且仅当 $\forall i\in[1, \rm{len}],s_i=s_{\rm{len}-i}$。
- 一个字符串 $t$ 称作 $s$ 的一个 $\rm{Border}$，当且仅当 $t$ 是 $s$ 的真前缀和真后缀。

## $2.\rm{Strings in C++}$
- 我们可以使用一个 `char[]/const char*` 存储字符串，这样的字符串以 `'\0'` 结尾，被称作为一个 **C 风格** 字符串。

- C++ 中提供了名为 `string` 的类，其底层为 `std::basic_string<char>`。其使用方法稍后讲解。
- 字符串字面量用双引号包括，的类型为 `const char*`，其也以 `'\0'` 结尾。用单引号的是一个字符，其中有且仅有一个字符，其类型为 `char`。

对于 C 风格的字符串：
-   `printf("%s", s)`：用 `%s` 来输出一个字符串（字符数组）。

-   `scanf("%s", &s)`：用 `%s` 来读入一个字符串（字符数组）。
-   `sscanf(const char *__source, const char *__format, ...)`：从字符串 `__source` 里读取变量，比如 `sscanf(str,"%d",&a)`。
-   `sprintf(char *__stream, const char *__format, ...)`：将 `__format` 字符串里的内容输出到 `__stream` 中，比如 `sprintf(str,"%d",i)`。
-   `strlen(const char *str)`：返回从 `str[0]` 开始直到 `'\0'` 的字符数。注意，未开启 O2 优化时，该操作写在循环条件中复杂度是 $O(N)$ 的。
-   `strcmp(const char *str1, const char *str2)`：按照字典序比较 `str1 str2` 若 `str1` 字典序小返回负值，两者一样返回 `0`，`str1` 字典序更大则返回正值。请注意，不要简单的认为返回值只有 `0`、`1`、`-1` 三种，在不同平台下的返回值都遵循正负，但并非都是 `0`、`1`、`-1`。
-   `strcpy(char *str, const char *src)`: 把 `src` 中的字符复制到 `str` 中，`str`  `src` 均为字符数组头指针，返回值为 `str` 包含空终止符号 `'\0'`。
-   `strncpy(char *str, const char *src, int cnt)`：复制至多 `cnt` 个字符到 `str` 中，若 `src` 终止而数量未达 `cnt` 则写入空字符到 `str` 直至写入总共 `cnt` 个字符。
-   `strcat(char *str1, const char *str2)`: 将 `str2` 接到 `str1` 的结尾，用 `*str2` 替换 `str1` 末尾的 `'\0'` 返回 `str1`。
-   `strstr(char *str1, const char *str2)`：若 `str2` 是 `str1` 的子串，则返回 `str2` 在 `str1` 的首次出现的地址；如果 `str2` 不是 `str1` 的子串，则返回 `NULL`。
-   `strchr(const char *str, int c)`：找到在字符串 `str` 中第一次出现字符 `c` 的位置，并返回这个位置的地址。如果未找到该字符则返回 `NULL`。
-   `strrchr(const char *str, char c)`：找到在字符串 `str` 中最后一次出现字符 `c` 的位置，并返回这个位置的地址。如果未找到该字符则返回 `NULL`。

对于 C++ 风格的字符串：
-   重载了赋值运算符 `+`，当 `+` 两边是 `string/char/char[]/const char*` 类型时，可以将这两个变量连接，返回连接后的字符串（`string`）。

-   赋值运算符 `=` 右侧可以是 `const string/string/const char*/char*`。
-   访问运算符 `[cur]` 返回 `cur` 位置的引用。
-   访问函数 `data()/c_str()` 返回一个 `const char*` 指针，内容与该 `string` 相同。
-   容量函数 `size()` 返回字符串字符个数。
-   `find(ch, start = 0)` 查找并返回从 `start` 开始的字符 `ch` 的位置；`rfind(ch)` 从末尾开始，查找并返回第一个找到的字符 `ch` 的位置（皆从 `0` 开始）（如果查找不到，返回 `-1`）。
-   `substr(start, len)` 可以从字符串的 `start`（从 `0` 开始）截取一个长度为 `len` 的字符串（缺省 `len` 时代码截取到字符串末尾）。
-   `append(s)` 将 `s` 添加到字符串末尾。
-   `append(s, pos, n)` 将字符串 `s` 中，从 `pos` 开始的 `n` 个字符连接到当前字符串结尾。
-   `replace(pos, n, s)` 删除从 `pos` 开始的 `n` 个字符，然后在 `pos` 处插入串 `s`。
-   `erase(pos, n)` 删除从 `pos` 开始的 `n` 个字符。
- `insert(pos, s)` 在 `pos` 位置插入字符串 `s`。  
-   `std::string` 重载了比较逻辑运算符，复杂度是 $O(N)$ 的。

这部分内容摘自 [OI-wiki](https://oi.wiki/string/lib-func/)。

## $\rm{3.Hash}$
前置知识：哈希。  

字符串哈希是一种将字符串映射为整数的算法。我们直接考虑构建一个这样的函数，让其成为一个字符串到整数之间的双射。这样的算法是容易想出的，$\sum_{i=1}^{\rm{len}}\limits{s_i\times26^i}$ 就是其中一个，其中字符与整数相乘，定义为该字符在字母表中的顺序和整数相乘。翻译成 C++ 代码就是，`s[i] - 'a'`，注意顺序从 $0$ 开始。  

事实上，任意的不小于 $26$ 的底数都是可行的。但遗憾的是，这样构造出的整数过大，并不能轻易的被计算机存储和计算。因为我们通常让这个数对固定的模数取模，这样，虽然理论上存在两个字符串计算出的数字相同（称作 **哈希冲突**），但实际上概率较小。  

但是事实上，有很多出题人故意对着这一点卡，因此出现了 **双模哈希**。双模哈希是指，把字符串映射为有序的整数二元组的算法，其核心算法和上述相同。相对的，初始算法被称作 **单模哈希**。若记 $h(S)=\sum_{i=1}^{\rm{len}}\limits{s_i\times26^i}$，那么哈希过后的结果就是 $(h(S)\mod \rm{mod1}, h(S)\mod\rm{mod2})$。  

常用的模数有 $998244353,10^9+7,1145141$ 等。  

与双模哈希类似的还有 **双底哈希**，只不过这个换的是底数。  

常见的底数有 $233,26,1145141$ 等。

字符串哈希的优越性在于，我们可以用 $O(n)-O(1)$ 的时间复杂度，$O(n)$ 的空间复杂度来求任意子串的哈希值。这里以单模哈希为例，我们存储 $H(S, i) = \sum_{j=1}^{i}\limits{s_j\times26^j}$，这个显然可以递推 $O(n)$ 求出。那么，子串 $s_{l,r}$ 的哈希值 $h(S, l, r)=\sum_{i=l}^{r}s_i\times26^{i-l+1}=\sum_{i=l}^rs_i\times26^{i}\times26^{1-l}=(H(S, r) - S(S, l - 1))\times26^{-l}$，那么我们只要再预处理出 $26^i$ 的逆元即可。 

模板题 [P3370](https://www.luogu.com.cn/problem/P3370)。  

挑战：熟练运用字符串哈希，5min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

## $\rm{4.KMP}$
- 我们首先定义，$\pi_i$ 为 $s_{1,i}$ 的最长 $\rm{Border}$ 长度。特别的，对于没有 $\rm{Border}$ 的前缀，$\pi_i=0$。

我们考察相邻的 $\pi_i$，发现其值最多增加 $1$，当且仅当 $s_{\pi_{i-1}+1}=s_{i}$ 的时候成立。  

如果这一性质不成立，我们尝试寻找 $\pi_i$ 的性质。因为找到的真后缀去掉最后一个字符必然是 $s_{1,i-1}$ 的后缀，又因为 $s_{1,pi_{i-1}}=s_{i-1-\pi_{i-1},i-1}$，因此我们找到的 $\pi_i$ 一定是 $s_{1,\pi_i}$ 的一个 $\rm{Border}$。  

这意味着，$j$ 失配时的下一个可能的位置应该是 $\pi_{j-1}$。我们不断的尝试匹配，就得到了数组 $\pi$。

参考代码如下：
```cpp
void demo() {
    int tot = strlen(s);
    pi[0] = 0;
    for (int i = 1; i < tot; i++) {
        int j = pi[i - 1];
        while (j && s[j] != s[i]) j = pi[j - 1];
        if (s[j] == s[i]) j++;
        pi[i] = j;
    }
}
```
可以证明，上述算法的时间复杂度是 $O(n)$ 的。一个比较厉害的理解是，每次将 $j$ 加一时，可以视为 $j$ 势能增加了 $1$，总势能不可能超过 $O(n)$，故消耗势能的次数也不超过 $O(n)$，而 `j=pi[j - 1]` 是必然会消耗势能的。  

从而，我们可以对于一个文本串 $s$ 和一个模式串 $t$，找出 $t$ 在 $s$ 中的所有出现，即 $\rm{KMP}$ 算法。算法流程是简单的：用一个未出现在 $s,t$ 的字符将二者连在一起，构成字符串 $t+\#+s$，然后求出它的 $\pi$，所有 $\pi_i=\rm{len}$ 的位置，对应在 $s$ 上即为 $t$ 的一个出现的末尾。  

模板题 [P3375](https://www.luogu.com.cn/problem/P3375)。  

挑战：熟练运用 KMP，5min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

练习：
- [P4391 Radio Transmission](https://www.luogu.com.cn/problem/P4391)
- [P4824 Censoring](https://www.luogu.com.cn/problem/P4824)
- [P2375 动物园](https://www.luogu.com.cn/problem/P4391)
- [P8112 符文破译](https://www.luogu.com.cn/problem/P8112)

## $\rm{5.Trie}$
字典树是处理多模式串前缀问题的利器之一。一个字典树是一种树，其点权为一个字符串（通常仅有一个字符）。字典树上的每个节点，其到根节点的路径上的所有字符串相连接所构成的字符串，均为给定串集合（称为模式串）中某个串的前缀。  

为了做到这一点，我们考虑如何加入一个字符串。首先，为了方便起见，我们把所有的字符串都在前面加一个字符 $\rm{ch}$，这个字符就是字典树的根节点。  

然后，字典树每一个节点与子节点的连边，都代表着一个字符。我们逐字符的加入一个字符串。加入过程如下：  

- 起初，我们站在根节点上。
- 我们尝试着加入一个字符 $\rm{c}$。
- 如果有节点向子节点，且代表着 $\rm{c}$ 的连边，我们就走到这个节点上。
- 如果没有这样的边，我们就创建一个新的节点，让当前节点向该新节点连边，这条边代表着字符 $\rm{c}$。
- 回到步骤 $2$，直到过程结束。

参考代码如下：
```cpp
inline void insert(string s) {
    int cur = 0;
    for(char i: s) {
        if(!ch[cur][i - 'a']) ch[cur][i - 'a'] = ++tot;
        cur = ch[cur][i - 'a'];
    }
}
```
在这份代码中，字典树的根节点为 $0$。我们使用变量 $\rm{tot}$ 维护当前的节点个数，以快速得到新节点的编号。$\rm{ch}_{\rm{cur}, {c}}$ 代表节点 $\rm{cur}$ 代表 $\rm{c}$ 的连边指向的节点。  

模板题 [P8306](https://www.luogu.com.cn/problem/P8306)。 

挑战：熟练运用字典树，10min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

显然，我们仅仅这么做并不能给我们做题带来什么帮助。因此，下面陈述几种 $\rm{Trie}$ 的常见用法。  
- 在每个节点上标记一个 $\rm{cnt}$，每当有一个字符串末尾走到了这个节点，我们就让 $\rm{cnt}:=\rm{cnt}+1$。同时，对这个变量做子树和，我们就知道了对于给定的字符串，有多少个模式串以它为前缀。
- 将一个数字视为一个字符集为 $\{0, 1\}$ 的字符串，从而处理一些常见的位运算的问题。例如，我们可以求给定数字集合的两两最大异或值。我们将所有数字从高向低插入字典树，然后对于每个数字，尽量找到和他异或较大的数字，因为是从高向低插入的，因此直接对每一位贪心有正确性保证。

对于字典树来说，如果对于每个字符都开一个节点来存储，既慢又浪费时间。所以，我们可以将多个节点压缩成一个节点，只要这些节点只有深度最大的有不止一个的子节点即可。这种一般被称作 **压位 Trie**。但因为其实现较繁，且收效甚微，一般不建议考场使用。
 
练习：
- [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)
- [P2922 Secret Message](https://www.luogu.com.cn/problem/P2922)
- [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)
- [P3879 阅读理解](https://www.luogu.com.cn/problem/P3879)


## $\rm{6.AC Automaton}$
从这个地方开始，字符串问题逐渐变得严肃了。未成年 Piggy 请在成年 Piggy 陪同下观看。  

AC 自动机是处理多串匹配的常用结构之一，它的基础是字典树。下面我先讲解它的算法流程，然后讲几个 AC 自动机的常见应用。  

首先，我们将所有字符串插入一个字典树。这个字典树就是普通的字典树，和上面讲的**完全**相同。虽然构建完全相同，我们下面把每个节点视为匹配的一个状态，跳到一个节点视为匹配了这个点与根节点连接的字符串。  

接着，我们构建一个数组，名字叫做 $\rm{fail}$。  

构建这个数组的目的在于，沿着字典树尝试匹配一个字符串的时候，可能会走不下去（即，下面要匹配的字符在这个节点上没有相应的边），我们称这种情况为 **失配**。失配发生时，我们需要倒退到深度较浅的另一个节点以继续匹配，这个倒退的过程所走的有向边被称之为 **失配指针**。  

但是这样的节点可能有多个，失配指针只能有一个。因此我们想要找到目前状态的最长后缀所对应的节点并跳过去。换言之，我们仍希望最大限度的保留目前匹配的结果。我们称这个状态为 **最优失配状态**。  

然后考虑这个指针怎么求。我们先不考虑时间复杂度，只是考虑可行性：对于一个节点 $u$，假设比它深度小的节点都已求出其失配指针。  

那么我们这样考虑：目前的最优失配状态，其去掉一个字符也应该是其父节点的最优失配状态（如果它的 $\rm{fail}$ 指针能指向 $u$ 对应字符的话）。这意味着，若 $\rm{ch}_{\rm{fail}_p,c}$ 存在，那这个就是 $u$ 的 $\rm{fail}$ 指针，其中 $p$ 是 $u$ 的父节点。  

如果不存在，就沿着 $\rm{fail}$ 指针跳，一直到$\rm{ch}_{\rm{fail}_p,c}$ 存在，或跳到了根节点，求值结束。

这样的时间复杂度爆炸，不可接受。因此，我们每次求出 $\rm{fail}$ 以后，把对应的儿子也指向 $\rm{fail}$ 的那个儿子。用代码语言来说，就是 `if (!ch[u][i]) ch[u][i] = ch[fail[u]][i];`，这样就加速了跳 $\rm{fail}$ 指针的过程。  

同时，我们字典树并未存储父节点编号。这意味着遍历每个节点时，要把所有子节点的 $\rm{fail}$ 指针求出来。写成代码语言就是 `if (ch[u][i]) fail[ch[u][i]] = ch[fail[u]][i]`。  

因此，遍历到一个节点时，我们要做的事情如下：
```cpp
for (int i = 0; i < 26; i++) {
   if (ch[u][i])
      fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
   else
      ch[u][i] = ch[fail[u]][i];
}
```
然后，结合基础的 bfs 的知识，可以写出如下代码：
```cpp
void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (ch[u][i])
                fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
            else
                ch[u][i] = ch[fail[u]][i];
        }
    }
}
```

在数据强度较弱的情况下，匹配的时候，对于已匹配的状态，其 $\rm{fail}$ 的状态也能匹配，因此要跑一遍其所有的 $\rm{fail}$ 统计答案。  
模板题 [P3808](https://www.luogu.com.cn/problem/P3808)。 

挑战：熟练运用 AC 自动机，10min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

这道题就是上面所说的跑一遍其所有的 $\rm{fail}$ 统计答案。因此，我们的 $\rm{query}$ 函数应该这么写：
```cpp
int query(string s) {
    int u = 0, res = 0;
    for (char i : s) {
        u = ch[u][i - 'a'];
        for (int j = u; j && cnt[j] != -1; j = fail[j]) {
            res += cnt[j], cnt[j] = -1;
        }
    }
    return res;
}
```
模板题 [P3796](https://www.luogu.com.cn/problem/P3796)。 

挑战：熟练运用 AC 自动机，10min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

这道题就是把记录方式改一下，从记 $\rm{res}$ 改为记到该节点对应的模式串编号上！因此，我们的 $\rm{query}$ 函数应该这么写：

```cpp
void query(string s) {
    int u = 0;
    for (char i : s) {
        u = ch[u][i - 'a'];
        for (int j = u; j; j = fail[j]) {
            cnt[j] = -1, ans[idx[j]]++;
        }
    }
}
```

而显然，这样时间复杂度是较高的，虽然期望较低。因此我们要深入研究一下 AC 自动机以加速这个过程。  

我们注意到，$\rm{fail}$ 每个节点只有一个，根节点没有。这提示我们，$\rm{fail}$ 实际上构成了一棵根向树，略去证明，我们称这棵树为 AC 自动机的一棵 $\rm{fail}$ 树。这样每个节点统计到的答案，应该是它子树的答案之和，因为暴力跳的时候，子树中的每个节点都会跳到这个节点上统计一遍答案。  

这样的话，就不用跳 $\rm{fail}$ 了，我们该怎么转移就怎么转移，最后按照 $\rm{fail}$ 跑一遍子树和即可。跑子树和的方法很多，如果只存储了失配指针，可以用拓扑排序来求。也可以真的把边建出来然后一边 dfs 解决问题，任君挑选。  

模板题 [P5357](https://www.luogu.com.cn/problem/P5357)。 

挑战：熟练运用 $\rm{fail}$ 树优化 AC 自动机，10min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

练习：
- [P3966 单词](https://www.luogu.com.cn/problem/P3966)
- [P2414 阿狸的打字机](https://www.luogu.com.cn/problem/P2414)
- [P2444 病毒](https://www.luogu.com.cn/problem/P2444)
- [CF1252D Find String in a Grid](https://www.luogu.com.cn/problem/CF1252D)

## $\rm{7.Manacher}$
在踏入字符串的深渊之前，这是最后的轻松。  

Manacher 算法，用来求解回文串相关问题。通过这个算法，我们可以 $O(n)-O(1)$ 的判定给定字符串的一个子串是否为回文串。  

初看，一个字符串的回文子串数量为 $O(n^2)$，所以可能这个问题没有线性算法。但我们考虑用另一种方法来表示回文串：对于每个下标，把它看做回文串的回文中心（这里暂时只考虑奇回文串），然后求出最大的 $l$ 使得 $s_{i-l, i+l}$ 回文，那么比他更小的一定都回文。下面转为求这个“回文半径”$d_i$。

为了实现这一点，我们先介绍一种被称为朴素算法的算法。在这个算法中，对于每个下标，我们不断尝试着向两端扩展，直到发现不是回文串了，$d_i$ 求解完成。  

而 Manacher 算法很好的利用了朴素算法。我们维护目前右端点最靠右的回文串 $s_{l, r}$。那么，从前到后求 $d_i$ 的过程当中，求解一个 $d_i$ 的流程如下：  

因为我们维护了右端点最靠右的回文串，如果当前的 $i\not\in[l, r]$，那么调用朴素算法，同时维护 $l, r$。否则 $i\in[l, r]$，那么我们考虑 $i$ 关于回文中心对称的那个字符 $w=l+r-i$，这个下标的回文半径内的字符，几乎总是可以利用回文的性质对称到这一边来的。也就是说，因为 $s_{l, r}$ 回文，所以 $s_{w-d_w, w+d_w}$ 回文意味着 $s_{i-d_w, i+d_w}$ 回文。  

我们说“几乎总是”，是因为这其中有一个问题是，如果 $w-d_w<l$，我们无法保证左端露出的一点还能用回文对称过来。这时，我们需要截断这个回文串，然后调用朴素算法。同时，因为此时回文串的右端点大于了目前维护的右端点，所以我们需要修改现在的右端点。  

这个算法是线性的。问题在于，算法的开销全在朴素算法上，而朴素算法的每次调用会让 $r$ 增加 $1$，然而增加的次数绝不超过 $O(n)$。这证明了 Manacher 算法的复杂度是 $O(n)$。

但此时，我们只求了长度为奇数的回文串。对于长度为偶数的回文串，与其修改整个算法（调整算式），我们采用一些比较巧妙的办法——既然偶数长度的回文串，回文中心是字符之间的“空隙”，那么我们把这些空填上字符即可，填上相同的字符。为了实现方便，我们把两侧也填上字符。  

例如，我们会把 $abc$ 填充成 $\#a\#b\#c\#$，然后调用上面的算法即可。 

模板题 [P3805](https://www.luogu.com.cn/problem/P3805)。 

挑战：熟练运用 Manacher 算法，10min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

练习：
- [P1659 拉拉队排练](https://www.luogu.com.cn/problem/P1659)
- [P6216 回文匹配](https://www.luogu.com.cn/problem/P6216)

## $\rm{8. Suffix Array}$

当你看到这个标题的时候，恭喜你，已经成功的坠入了字符串的深渊之中。后缀数组（Suffix Array，SA）会成为你第一个学习的重量级字符串算法。即使它本身的编写并不复杂，从它出发可以做的题很多，很杂，很难，很多还和其他的数据结构相结合。因此他是字符串进阶的必要算法之一。  

后缀数组主要关系到两个数组：$\rm{sa}$ 和 $\rm{rk}$，两者互为逆置换。其中，$\rm{sa}_i$ 表示将所有后缀排序后第 $i$ 小的后缀的编号，$\rm{rk}$ 表示后缀 $s_{i,n}$ 在所有后缀中的排名。我们希望我们能比较快速的求出这两个数组，这样可以做接下来的事情。

首先，$O(n^2\log n)$ 的算法是最暴力最直接的，但显然我们并不想要这样的算法。注意到我们在这么做的时候重复比较了很多没必要比较的字符串，因此我们考虑倍增。  

倍增法基于这样的考虑：我们先求出单个字符的排名，再求出所有长度为 $2$ 的子串的排名，再求出所有长度为 $4$ 的子串的排名……这些倍增的过程中，希望求出长度为 $w$ 的所有子串的排名时，我们都以 $\rm{rk}_{w/2,i}$ 作为第一关键字，$\rm{rk}_{w/2,i+w/2}$ 作为第二关键字，显然这可以正确的排序。  

同时，我们肯定是要考虑最后那些“不完整的字符串”的。因此，对于 $i+w>n$，$\rm{rk}_{i+w}$ 视为无穷小。这样就可以排序了。对于程序实现，我们的 $\rm{cmp}$ 函数应该写成：  
```cpp
inline bool cmp(int x, int y) {
  return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
}
```
这样排过序了以后，我们就可以求出排名了。但是其中有可能有相同的子串，因此我们需要在后面这么写：
```cpp
memcpy(oldrk, rk, sizeof(rk));
for (p = 0, i = 1; i <= n; ++i) {
  if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
    rk[sa[i]] = p;
  } else {
    rk[sa[i]] = ++p;
  }
}
```
完整的代码如下。这份代码的时间复杂度为 $O(n\log^2n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6 + 10;
char s[maxN];
int n, w, sa[maxN], rk[maxN << 1], oldrk[maxN << 1];

inline bool cmp1(int x, int y) { return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y]; }
inline bool cmp2(int i, int w) { return oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]; }
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
    for (int w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + n + 1, cmp1);
        memcpy(oldrk, rk, sizeof(rk));
        for (int p = 0, i = 1; i <= n; ++i) rk[sa[i]] = cmp2(i, w) ? p : ++p;
    }
    for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
}
```
但这还不够。我们发现，排序是双关键字且值域是 $O(n)$ 的，这意味着我们可以使用基数排序和计数排序来优化整体时间复杂度到 $O(n\log n)$。  

为了更好的学习后缀数组，我们需要复习一下计数排序。计数排序的原理是，我们开一个桶记录所有的数字，然后对其做前缀和。这样，我们就知道了有多少数字比某数字小，从而获得了所有数字的排名。  

这样，我们每次减小这个桶内的数字，并将其作为元素的排名即可。为了保证排序稳定，我们倒序枚举数字，从而相等的数字，下标较大的排名较为靠后。  

为了方便理解，给出笔者实现的计数排序。
```cpp
inline void counting_sort(int *A) {
    for(int i = 1; i <= m; i++) cnt[i] = 0;
    for(int i = 1; i <= n; i++) cnt[A[i]]++;
    for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i--) sa[cnt[A[i]]--] = id[i];
}
```
若对以上过程不理解，可以仔细推敲这个排名是怎么出来的。牢记：排名和比他小的数字的个数相关。  

这样，我们就可以用基数排序分别对两关键字进行排序来解决问题了。我们先对第二关键字排序，这样对第一关键字排序的时候，因为事先第二关键字已经排好序，因此这样恰好让整个数组排好了序。

> 思考：为什么按照第一关键字排序时，第一关键字相同的自动按照第二关键字排序了？

不难写出如下时间复杂度为 $O(n\log n)$ 的代码（来自 OI-wiki）：
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1000010;

char s[N];
int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];

int main() {
    int i, m, p, w;

    scanf("%s", s + 1);
    n = strlen(s + 1);
    m = 127;
    for (i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;
    memcpy(oldrk + 1, rk + 1, n * sizeof(int));
    for (p = 0, i = 1; i <= n; ++i) {
        if (oldrk[sa[i]] == oldrk[sa[i - 1]]) {
            rk[sa[i]] = p;
        } else {
            rk[sa[i]] = ++p;
        }
    }

    for (w = 1; w < n; w <<= 1, m = n) {
        // 对第二关键字：id[i] + w进行计数排序
        memset(cnt, 0, sizeof(cnt));
        memcpy(id + 1, sa + 1,
               n * sizeof(int));  // id保存一份儿sa的拷贝，实质上就相当于oldsa
        for (i = 1; i <= n; ++i)
            ++cnt[rk[id[i] + w]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i] + w]]--] = id[i];

        // 对第一关键字：id[i]进行计数排序
        memset(cnt, 0, sizeof(cnt));
        memcpy(id + 1, sa + 1, n * sizeof(int));
        for (i = 1; i <= n; ++i)
            ++cnt[rk[id[i]]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i]]]--] = id[i];

        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        for (p = 0, i = 1; i <= n; ++i) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                rk[sa[i]] = p;
            } else {
                rk[sa[i]] = ++p;
            }
        }
    }

    for (i = 1; i <= n; ++i)
        printf("%d ", sa[i]);

    return 0;
}
```
但实际上，这份代码常数巨大以至于不能通过。因此我们采用以下几个常数优化：
- 第二关键字无需计数排序。因为第二关键字排序只是把 $\rm{sa}_i+w>n$ 的部分扔到前面去，剩下的原样放置。或者说，SA 的第二关键字的顺序就是上一轮排序以后的顺序，只是多出了一些空串。因此我们把它扔到前面去：
```cpp
for (p = 0, i = n; i > n - w; --i) id[++p] = i;
```
- 然后剩下的部分，因为正好扔了 $w$ 个在前面，所以 $\rm{sa}_i:=\rm{sa}_i-w$。
```cpp
for (i = 1; i <= n; ++i) if (sa[i] > w) id[++p] = sa[i] - w;
```
- 此时，我们已经排序好了第二关键字。根据我们之前的理论，这样只需要对第一关键字进行排序，就完成了这一轮排序。所以后面的部分不变。  
- 关于值域：首先，每次对 $rk$ 进行更新之后，我们都计算了一个 $p$，即是 $rk$ 的值域，将值域改成 $p$ 即可。同时，若 $p$ 已经等于 $n$，那么再排序也没有影响了，直接生成后缀数组即可。
- 关于不连续内存访问：将 $rk[id[i]]$ 存下来，减少不连续内存访问，循环最后生成新的 $\rm{rk}$ 数组时，抽出一个函数做这件事也可以减少不连续内存访问。这两者在数据范围较大时优化十分明显。

这里给出我的实现，常数较小。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e6 + 10;
int n, m = 127; char s[maxN];

int height[maxN], key1[maxN], id[maxN], rk[maxN], oldrk[maxN], sa[maxN], cnt[maxN];

inline bool cmp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

inline void counting_sort(int *A) {
    for(int i = 1; i <= m; i++) cnt[i] = 0;
    for(int i = 1; i <= n; i++) cnt[A[i]]++;
    for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i--) sa[cnt[A[i]]--] = id[i];
}

inline void getsa() {
    n = strlen(s + 1);
    for(int i = 1; i <= n; i++) id[i] = i, rk[i] = s[i];
    counting_sort(rk);
    int p = 0;
    for(int j = 1; p != n; j <<= 1, m = p) {
        p = 0;
        for(int i = n; i > n - j; i--) id[++p] = i;
        for(int i = 1; i <= n; i++) if(sa[i] > j) id[++p] = sa[i] - j;
        for(int i = 1; i <= n; i++) key1[i] = rk[id[i]];
        counting_sort(key1);
        for(int i = 1; i <= n; i++) oldrk[i] = rk[i];
        p = 0;
        for(int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], j) ? p : ++p;
    }
    for(int i = 1; i <= n; i++) sa[rk[i]] = i;
}

int main() {
    cin >> (s + 1);
    getsa();
    for(int i = 1; i <= n; i++) cout << sa[i] << " ";
}
```

后缀数组的求法就说到这里……吗？不，这才刚刚开始！  

我们有了优秀的 $O(n\log n)$ 求后缀数组的做法，但是这还不够，我们甚至有 $O(n)$ 求 SA 的做法。目前主流做法有：
- SA-IS：[诱导排序与 SA-IS 算法](https://riteme.site/blog/2016-6-19/sais.html) 和针对它的 [issue 页面](https://github.com/riteme/riteme.github.io/issues/28)。
- DC3：[后缀数组——处理字符串的有力工具](https://github.com/enkerewpo/OI-Public-Library/blob/master/IOI%E4%B8%AD%E5%9B%BD%E5%9B%BD%E5%AE%B6%E5%80%99%E9%80%89%E9%98%9F%E8%AE%BA%E6%96%87/2009/%E7%BD%97%E7%A9%97%E9%AA%9E/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E2%80%94%E2%80%94%E5%A4%84%E7%90%86%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E6%9C%89%E5%8A%9B%E5%B7%A5%E5%85%B7.pdf)。
- SAM + ST：对反串建 SAM，其 link 所构成的图为后缀树（Suffix Tree）。使用后缀树即可轻松构建 SA。

模板题 [P3809](https://www.luogu.com.cn/problem/P3809)。 

挑战：熟练运用 SA，10min 内将此题 AC。要求不借助任何可以加速写代码的工具，可以使用记事本或 Dev-C++，模仿 NOI 系列比赛的实际情况。

练习：
- [P4051 字符加密](https://www.luogu.com.cn/problem/P4051)
- [P2870 Best Cow Line](https://www.luogu.com.cn/problem/P2870)  

可喜的是，SA 还有更多优秀的性质等着我们挖掘，其中最经典的就是其 $\rm{height}$ 数组的应用。

$\rm{height}$ 数组和 LCP（最长公共前缀）相关，其定义为 $\rm{height}_i=lcp(\rm{sa}_i, \rm{sa}_{i-1})$，其中 $lcp(i, j)$ 代表后缀 $i, j$ 最长公共前缀的长度。  

在已经求出 $\rm{sa}$ 的前提下，我们可以 $O(n)$ 求出 $\rm{height}$。其关键是 $\rm{height}_{\rm{rk}_i}\ge\rm{height}_{\rm{rk}_{i-1}}-1$。此引理的严谨证明较繁，感性上就是把前一个后缀各退了一位，这是新 $\rm{height}$ 的下界。

有了这个数组之后，我们对他建立 ST 表就可以做一些简单的题目了，比如求任意两个子串的最长公共前缀，容易做到 $O(n\log n)-O(1)$。  

再以后的内容，因为已经远超出了字符串入门的内容，因此不做讲解。

## $\rm{9. Epilogue}$
作为字符串基础篇，这个博客已经相当足够了。事实上，后面的东西可能更为困难，已经不适合纯新手而适合对字符串有了一定了解的 OIer 学习。

但仍需要指出的是，对于 OI 中考察的字符串知识点而言，这些依然只是皮毛，因为这些都只是基础知识层面的，并未涉及常见题型和 trick。甚至，基础知识也没有讲完——我们没有提 FFT 做字符串匹配带容错和 SAM，PAM，后缀平衡树和后缀树。  

而对于 OI 中考察较少的 Lyndon 分解，Runs，基础子串结构和扩展 KMP，更是压根没提及。这些内容将会在接下来的一两个博客中详细讲解，欢迎各位捧场！