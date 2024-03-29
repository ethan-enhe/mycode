# 题目背景

（背景可以忽略）

你是罗伯特·卡洛斯。

在 1997 年 6 月 3 号的四国邀请赛上，你所在的巴西队一球落后于法国。此时，你们队获得了一个位置离球门 30 余米的任意球。

人墙十分密集，但是你找到了一条绕过人墙的弧线，

![](https://pic.imgdb.cn/item/6318587816f2c2beb1ed173a.jpg)

你将球放好，后退数步，开始助跑，奋力一<mark>闷</mark>，皮球画过一条不可思议的弧线，进了！

![](https://imgsa.baidu.com/forum/pic/item/292b9c16fdfaaf51bb10d4718d5494eef11f7a39.jpg)

# 题目描述

抛开事实（实际踢不踢的出来）不谈，你只需要找出一条可能踢出的弧线即可。

如果把球场考虑为一个二维平面，**你只需要解决下面的问题：**

给定 $n$，要求构造一个整数数列 $y_{0\sim n}$ 使得：

- $\forall i\in[1,n],|y_i-y_{i-1}|\le 1$，表示球的弧度不能太大。
- $\forall i\in[0,n], y_i\in [0,w]$，表示球不能飞出球场。

还有 $m$ 条限制，形如：

- $i,l,r$，要求 $y_i \notin [l,r]$，表示一条人墙。

如果存在一个合法的数列 $y_i$，$(i,y_i)$ 这些坐标点连接起来的轨迹是一个可能被你踢出的弧线。

请输出是否有这样一个合法的数列——你能否将这球打进。

# 输入格式

第一行输入数据组数 $t$。

对于每组数据，第一行三个数 $n,m,w$。

后面 $m$ 行，每行三个整数 $i,l,r$ 表示一条限制。

# 输出格式

对一每组数据，输出一行 `YES` 或者 `NO` 表示是否有这样一个合法的数列。

# 样例

## 样例1

**输入**

```plain
2
3 9 8
0 0 2
0 4 8
1 3 3
2 1 2
2 3 4
2 6 7
3 0 1
3 3 3
3 5 8

3 9 8
0 0 2
0 4 8
1 3 3
2 1 2
2 3 5
2 6 7
3 0 1
3 3 3
3 5 8
```

**输出**

```plain
YES
NO
```

## 样例2

**输入**

```plain
10
10 6 10
2 0 7
2 7 10
2 5 7
2 4 5
3 9 10
5 4 10
10 9 8
0 3 6
1 4 6
2 2 7
3 1 4
3 5 5
4 4 6
5 2 5
6 1 8
6 4 6
10 4 9
3 0 1
3 2 7
3 1 1
5 4 6
10 8 7
0 1 2
1 2 2
3 2 7
6 0 2
6 3 6
7 3 7
7 3 3
7 0 3
10 9 2
0 0 1
0 0 1
0 2 2
3 1 2
4 1 1
4 1 2
4 0 1
6 1 2
8 0 1
10 1 5
0 1 5
10 8 5
0 1 1
0 2 2
1 2 2
1 2 2
3 1 1
3 1 2
5 0 1
6 0 3
10 4 1
0 1 1
2 0 0
5 0 0
5 1 1
10 5 9
0 4 6
0 4 8
0 6 8
3 2 8
4 1 6
10 1 2
0 1 2
```

**输出**

```plain
NO
YES
YES
NO
NO
YES
YES
NO
YES
YES
```

# 提示说明

对于 $100\%$ 的数据，$0\le n,w\le 10^9,1\le t\le10$。

| 数据点编号 | 特殊限制            | 分值   |
|:-----:|:---------------:|:----:|
| 1     | $n,m,w\le 10^2$ | $10$ |
| 2     | $n,m,w\le 10^3$ | $20$ |
| 3     | $n,m\le 10^3$   | $10$ |
| 4     | $m\le 10^3$     | $30$ |
| 5     | $m \le 10^5$    | $30$ |

## 样例 1 解释

![](https://pic.imgdb.cn/item/6315ee5116f2c2beb1a27786.jpg)

也即：$y=\{3,4,5,4\}$
