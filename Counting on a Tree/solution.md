# Counting on a Tree 题解

我们先考虑 $k=1$ 的情况。这种情况等价于求上升树本身的个数 $E_n$。

考虑其递推关系。若根据左子树大小枚举，很容易得到：

$$2E_{n+1} = \sum_{k=0}^n\binom{k}{n}E_kE_{n-k}$$

尝试将其转为生成函数。对其左右乘以 $\frac{x^n}{n!}$，得到：
$$2E_{n+1}\frac{x^n}{n!} = \sum_{k=0}^n\binom{k}{n}E_kE_{n-k}\frac{x^n}{n!}$$

若将其视作多项式运算，且令指数生成函数 $y=\sum E_n \frac{x^n}{n!}$，则上式左侧即为 $y\prime$ 中的一项，右侧则为 $y^2$ 展开式中的一项。考虑边界条件，则得到：

$$2y\prime=y^2+1$$

这等价于：
$$\frac{2 dy}{y^2+1}=dx$$

左右积分：
$$2\arctan{y}=x+C$$

因此：
$$y=\tan(\frac{x}{2}+C)=\tan(\frac{x}{2}+\frac{\pi}{4})=\frac{1+\sin x}{\cos x}$$

对这个式子应用多项式科技，就可以得到 $E_n$ 的指数生成函数。时间复杂度 $O(n\log n)$。

那么，对于 $k\le n$ 呢？对于一棵上升树而言，它相当于对节点 $n$ 挂上剩下的节点；对于 $k\le n$ 而言，它相当于对一条链挂上若干个上升树。对于 $x_1+x_2+\dots+x_k=n-k$ 的任意一组非负整数解，出于对节点互不相同的考量，这种解共有 $\frac{(n-k)!}{x_1!x_2!\dots x_n!}$ 个，明显的，他会贡献出 $\prod E_{x_i}$ 个上升树。因此，最终的结果应该是：

$$Ans=\sum_{x_1+\dots+x_k=n-k}\frac{(n-k)!}{x_1!x_2!\dots x_n!}\prod E_{x_i}=(n-k)!\sum_{x_1+\dots+x_k=n-k}\prod \frac{E_{x_i}}{x_i!}$$

这也就相当于

$$(n-k)!\times[x^{n-k}]y^k$$

多项式快速幂求值即可。时间复杂度 $O(n\log n)$。