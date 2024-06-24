

## Definitions of DFT

### DFT与DTFT

任意**离散时域信号**$x[n]$的**离散时间傅里叶变换**(DTFT)定义为：
$$
X(e^{j\omega})=\sum_{n=-\infty}^{+\infty}x[n]e^{-jn\omega}
$$
这也是课本上对DTFT的定义，给出一个离散信号，其DTFT为频域连续的信号。当时域信号有限，只在$0\sim N-1$有值时，离散信号$𝑥[𝑛](for\quad n=0,...,N-1)$的DTFT简化为：
$$
X(e^{j\omega})=\sum_{n=0}^{N-1}x[n]e^{-jn\omega}
$$
之所以要给出DTFT，是由于计算机无法处理连续时间信号。因此我们在时域上对**连续傅里叶变换(FT)**的采样。时域信号是离散的，相应频域信号为连续的。

DFT则是**在频域上对DTFT的均匀采样**。取$X(e^{j\omega})$在离散频点$\{\omega_k=k\frac{2\pi}N\}_{0\leq k<N}$ 上的值，就得到了原信号的DFT：
$$
X[k]=X(e^{j\omega_k})=\sum_{n=0}^{N-1}x[n]e^{-j\frac{2\pi}N{kn}}\quad k=0,\ldots,N-1
$$
因为DTFT以$2\pi$为周期，因此通常情况下，我们可以只在$(0,2\pi)$区间内采样。这是非常重要的性质。

### DFT定义

对于$N$点的序列$\{x[n]\}_{0\leq n < N}$，假设其只在$0\sim N-1$有值，那么它的离散傅里叶变换（DFT）定义为：
$$
X[k]=\sum_{n=0}^{N-1}e^{-j\frac{2\pi}Nnk}x[n]\quad k=0,1,\ldots,N-1
$$

如果将$e^{-j\frac{2\pi}{N}}$记作$w_N$，那么上式可以简写为：
$$
X[k]=\sum_{n=0}^{N-1}x[n]w_N^{nk},\quad0\leq k\leq n-1.
$$
同时，我们给出离散傅里叶逆变换（inverse DFT）的公式：
$$
x[n]=\frac1N\sum_{k=0}^{N-1}y[k]w_N^{-nk},\quad0\leq j\leq n-1,
$$

### DFT：复杂度分析

​	在计算N点DFT的过程中，对于每一个频域点$X[k],\quad k = 0,\cdots N-1$，需要经过N次的复数乘法、N-1次的复数加法。

​	因此要得到完整的频谱，总共的计算时间复杂度为$O(n^2+n(n-1))=O(n^2)$。

## DIT  Radix-2 Cooley-Tukey Algorithm

​	2指数库里-图基算法是最简单的一个FFT算法。利用分治思想，将计算DFT的复杂度降低为$O(n\log n)$。下面推导其算法。

### 单位复数根

​	在正式介绍FFT之前，我们先了解n次单位复数根。这是满足$w^n=1$的复数$w$。n次单位复数根恰好有n个，对于$k=0,1,\cdots, n-1$，他们分别是$e^{2\pi jk/n}$。这里$j$是复数单位，$j=\sqrt{-1}$ 

​	为了在书写上化繁为简，我们一般用符号$w_N$来表示$e^{-j\frac{2\pi}{N}}$。称为$N$次单位根。
$$
w_N=e^{-j\frac{2\pi}{N}}
$$
​	可以证明，$N$ 次单位根有如下性质：

1. 周期性：$w_N$的指数具有周期$N$，即：$w_N^{k+N} = w_N^k$。

   > 证明：
   > $$
   > w_N^{k+N}=e^{-j\frac{2\pi}{N}(k+N)} = e^{-j2\frac{2\pi k}{N}}
   > $$

2. 对称性：$w_N^{k+N/2}=-w_N^{k}$

   > 证明：
   > $$
   > w_N^{k+N/2} = e^{-j\frac{2\pi}N (k+N/2)} = e^{-j\frac{2\pi k}N -j\pi} = -e^{-j\frac{2\pi k}{N}}
   > $$

3. 可消去性：若$m$是$N$的约数，则$w_N^{m*kn} = w_{\frac{N}{m}}^{kn}$
   > 证明：
   > $$
   > w_N^{m*kn} = e^{-j\frac{2\pi}{N}*mkn}=e^{-j\frac{2\pi}{N/m}*kn}
   > $$

我们会利用以上性质对DFT进行变形。引入单位根后，DFT就写为：
$$
X[k]=\sum_{n=0}^{N-1}x[n]*w_N^{kn}, \quad k=0,\ldots,N-1
$$
### 分治算法

接下来就是库利-图基算法的核心：分治。我们将求和部分分为**奇下标和偶下标**两部分：
$$
X[k]=\sum_{t=0}^{N/2-1}x[2t]w_N^{k*2t}+\sum_{t=0}^{N/2-1}x[2t+1]w_N^{k*(2t+1)}
\\=\sum_{t=0}^{N/2-1}x[2t]w_{N/2}^{kt}+w_N^k\sum_{t=0}^{N/2-1}x[2t+1]w_{N/2}^{kt}
\\=F_{even}[k]+w_N^kF_{odd}[k]
$$
​	为了方便和原公式对照，我们可以看一眼更加Verbose的公式：
$$
X[k]=\underbrace{\sum_{t=0}^{N/2-1}x[2t]e^{-\frac{2\pi j}{N/2}tk}}_{x[n]\text{偶下标序列的DFT }}+e^{-\frac{2\pi j}Nk}\underbrace{\sum_{t=0}^{N/2-1}x[2t+1]e^{-\frac{2\pi j}{N/2}tk}}_{x[n]\text{奇下标序列的DFT}}=F_{even}[k]+e^{-\frac{2\pi j}Nk}F_{odd}[k]\\ \mathrm{~for~}k=0,\ldots,\frac N2-1.
$$
​	正如上式所写，$F_{even}[k],F_{odd}[k]$正好分别是$x[n]$奇数下标、偶数下标序列的$N/2$点DFT。具体来说：
$$
\begin{aligned}
F_{even}[k]&=\sum_{t=0}^{N/2-1}x[2t]e^{-\frac{2\pi j}{N/2}tk}\\
F_{odd}[k]&=\sum_{t=0}^{N/2-1}x[2t+1]e^{-\frac{2\pi j}{N/2}tk}
\end{aligned}
$$
​	如果将原序列奇下标、偶下标部分分别记作$x_1[n],\quad x_2[n]$：
$$
\begin{cases}
x_1[k] = x[2k]\\
x_2[k]=x[2k+1] 
\end{cases}\qquad \mathrm{~for~}k=0,\ldots,\frac N2-1
$$
​	那么$F_{even}[k],F_{odd}[k]$就变为DFT的标准形式：
$$
\begin{aligned}
F_{even}[k]&=\sum_{t=0}^{N/2-1}x_1[t]e^{-\frac{2\pi j}{N/2}tk}\\
F_{odd}[k]&=\sum_{t=0}^{N/2-1}x_2[t]e^{-\frac{2\pi j}{N/2}tk}
\end{aligned}
$$
​	因此，我们可以用同样的方法计算$x_1[n],x_2[n]$离散傅里叶变换。这是递归的思想，在不断的递归、合并中，我们就得到了原序列的傅里叶变换。

​	最后，我们可以利用单位根的**周期性、对称性**来减少运算量。我们可以很快地推导出$k>N/2$时$X[k]$的计算公式
$$
X[k+N/2] = F_{even}[k] - w_N^kF_{odd}[k]
$$
​	所以我们可以将DFT的结果写成如下形式：
$$
X[k]= F_{even}[k]+w_N^kF_{odd}[k]\\
X[k+\frac{N}{2}]= F_{even}[k]-w_N^kF_{odd}[k] \\
\mathrm{~for~}k=0,\ldots,\frac N2-1.
$$
​	综上，我们将一个规模为N的问题分为规模为N/2的两个子问题，可以利用分治递归求解。伪代码如下：

```python
RECURSIVE-FFT(x) # x 是一个长度为N的向量，且n是2的指数次幂
n = a.length
if n==1			# 当序列长度为1时，返回自身
	return a
w_n = exp(2 * pi * 1j / n)
w = 1
x_0 = (x[0], x[2], ..., x[n-2]) # 偶数下标向量
x_1 = (x[1], x[3], ..., x[n-1]) # 奇数下标向量
y_0 = RECURSIVE-FFT(y_0)
y_1 = RECURSIVE-FFT(y_1)
for  k = 0 to n / 2 - 1
	y[k] = y_0[k] + w * y_1[k]
    y[k + n / 2] = y_0[k] - w *y_1[k]
    w = w * w_n
end
return y
```

​	在第12-14行，我们对$w$进行了累乘，每次乘上$w_n = e^{-j2\pi/n}$。我们将其称为旋转因子。

### 递推加速

​	使用递归的方式计算显然消耗了很多不必要的堆栈资源。在大多数工程场景下，甚至是不允许出现递归代码的。因此我们用**迭代**替代递归操作。那么如何迭代计算FFT？在递推实现的2-radix C-T的算法中，我们引入**蝶形网络**和**位翻转**方法。

​	首先我们注意到，在伪代码第12-14行，重复利用了 `w*y_1[k]`这一公共项。可以将所得的乘积存入一个临时变量 `t` 中，便于重复利用，从而减少了一次复数乘法。下面的计算流程图表示了这一系列操作，我们称之为**蝴蝶操作**

![image-20240622221757989](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622221757989.png)

​	递归算法实现了自顶向下完成计算，其递归调用树如下所示。为了实现递推，我们希望自底向上推导。

![image-20240622223137251](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622223137251.png)

​	将原始序列按照上图叶子节点的顺序排列，并引入一个变量 s 代表计算树的层次，取值范围为从 1 （最底层） 到 $\log_2 n$ （最顶层）。在每一层，我们要对两个具有 $2^{s-1}$ 个元素的 DFT 进行组合，以产生最后结果。伪代码应当如下所示：

```python
for s = 1 to log2(n) 
	for k = 0 to n - 1 by 2^s   # 每次跨越2^s步长 
    	combine the two 2^{s-1} element DFTs 
        from A[k ... k+2^{s-1}-1] and A[k+2^{s-1} ... k+2^s - 1] 
        into one 2^s-element DFT in A[k ... k + 2^s - 1]
```

​	最内层的实现细节与回溯实现的内层循环一致，对于每一个$(s,k)$组合，需要进行$2^s$组蝴蝶变换。画出其计算流程图，我们将其称为**蝶形网络**。

<img src="https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240522114246821.png" alt="image-20240522114246821" style="zoom:33%;" />

- 最左侧是原序列，分为偶数下标$x[0],x[2],x[4],x[6]$和奇数下标$x[1],x[3],x[5],x[7]$两组。对应$x_1[n],x_2[n]$。

- 它们经过$N/2$个点的DFT，得到两组结果：$E[0]\cdots E[3],\quad O[0]\cdots O[3]$。分别对应$F_{even}[k],\quad F_{odd}[k]$。

- 观察流向$X[4]$的数据：箭头上的圆点表示相加，数字表示乘积。此处$N=8$。
  $$
  X[4] = E[0] + O[0] * W^4_N = E[0]-O[0]
  $$
  刚好与本节开头的式子对应。

继续将$N/2$点的DFT展开，我们将得到如下数据流向图：

<img src="D:\Study\Study\Courses\24_S1\信号与系统\labs\proj\imgs\1.jpg" alt="1" style="zoom:20%;" />

N/4的DFT只剩下两个数，展开为：

<img src="D:\Study\Study\Courses\24_S1\信号与系统\labs\proj\imgs\2.jpg" alt="2" style="zoom:25%;" />

在递推过程中，我们希望按照如计算图中的样子，从N/4 DFT开始增加DFT的规模，逐层计算出DFT的值。

​	我们看到，为了能够顺利递推，输入数据的顺序被打乱了。这种乱序其实有规律，我们把顺序的序号用二进制数列在下表中的左边，把乱序的序号用二进制数列在下表中的右边。

<table>
	<tbody>
		<tr>
			<th>Normal order of index n</th>
			<th>Binary bits Of index n</th>
			<th>Reversed bits of index n</th>
			<th>Bit-reversed of order index n</th>
		</tr>
		<tr>
			<td>0</td>
			<td>000</td>
			<td>000</td>
			<td>0</td>
		</tr>
		<tr>
			<td>1</td>
			<td>001</td>
			<td>100</td>
			<td>4</td>
		</tr>
		<tr>
			<td>2</td>
			<td>010</td>
			<td>010</td>
			<td>2</td>
		</tr>
		<tr>
			<td>3</td>
			<td>011</td>
			<td>110</td>
			<td>6</td>
		</tr>
		<tr>
			<td>4</td>
			<td>100</td>
			<td>001</td>
			<td>1</td>
		</tr>
		<tr>
			<td>5</td>
			<td>101</td>
			<td>101</td>
			<td>5</td>
		</tr>
		<tr>
			<td>6</td>
			<td>110</td>
			<td>011</td>
			<td>3</td>
		</tr>
		<tr>
			<td>7</td>
			<td>111</td>
			<td>111</td>
			<td>7</td>
		</tr>
	</tbody>
</table>
​								表1.  基2，8点FFT序列的比特翻转

​	从表中我们可以看出，乱序序号的二进制码可由顺序序号的二进制码**镜像反转**得到(例如$001\to 100$)，这种规律被叫做比特反转。如果我们将原始序列按照上述规则重排，就能按照计算图的规律来编写递推代码，从而实现递推计算FFT。

### 速度瓶颈

​	对于计算机而言，需要访问位于不同内存地址的数据，才能完成数据交换。当数据量N很大时，由于比特翻转访问的内存空间的不连续，计算机需要反复从内存（Memory）中读取数据到缓存（Cache），造成了时间的浪费。

​	同时，在内层循环中，计算机需要同时访问内存跨度为$2^k$的两点数据。大多数情况下（k>5左右），这都会要求计算机重新从内存中加载数据到缓存，再进行计算。因而，这种方法的空间效率非常低。



### Code Implementation

使用C++ 实现递推代码。主要利用了C语言下标从0开始的特性，代码更加符合程序习惯。

```c++
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <ctime>

typedef unsigned int uint;

const double PI = 3.141592653589793238460;

uint reversed[1 << 20];

// Utility function to calculate the next power of two greater than or equal to 'n'
int nextPowerOfTwo(int n)
{
    return pow(2, ceil(log2(n)));
}

// Utility function to reverse the bits of a given index 'i'
// 'bit' is the number of bits needed to represent the indices
void get_reversed(int bit)
{
    for (uint i = 0; i < (1 << bit); i++)
    {
        reversed[i] = (reversed[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }
}

// The FFT function
// 'samples' is a reference to the vector containing the time-domain sample values
// 'n' is the number of points in FFT, must be a power of two
void fft(std::vector<std::complex<double>> &samples, const int n, const int levels)
{
    // Bit-reverse the input samples array based on the levels
    for (uint i = 0; i < n; i++)
    {
        if (reversed[i] > i)
        {
            std::swap(samples[i], samples[reversed[i]]);
        }
    }

    // Cooley-Tukey iterative FFT algorithm
    for (int size = 2; size <= n; size <<= 1) // the size of butterfly unit.
    {
        std::complex<double> w_m = std::exp(std::complex<double>(0, -2 * PI / size)); // twiddle factor (w)
        for (int m = 0; m < n; m += size)
        {
            std::complex<double> w = 1;
            for (int k = 0; k < size / 2; ++k)
            {
                // FFT butterfly
                std::complex<double> t = w * samples[m + k + size / 2];
                std::complex<double> u = samples[m + k];
                samples[m + k] = u + t;
                samples[m + k + size / 2] = u - t;
                w *= w_m;
            }
        }
    }
}

uint N;
std::vector<std::complex<double> > samples;
int main()
{
    srand(time(0));

    // generate random serise of lenth N
    N = 1<<20;
    for (int i = 0;i < N; i++) {
        samples.push_back(std::complex<double> (rand(), 0));
    }

    uint tic = clock();

    // Make sure the number of samples is a power of two
    int n = nextPowerOfTwo(samples.size());
    samples.resize(n); // pads with zeroes if necessary

    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n));

    // get reversed index based on the levels
    get_reversed(levels);

    // Performing FFT
    fft(samples, n, levels);

    uint toc = clock();

    std::cout<<"Time Cost:"<<(double) (toc - tic) / CLOCKS_PER_SEC << "s" <<  std::endl;

    return 0;
}
```

在位翻转操作中，我们通过预处理函数`get_reversed`计算得到了每一个`i`对应的翻转下表`reversed[i]`。

## DIF C-T Algorithm

​	快速傅里叶变换有两种常用的序列拆解方式，一种即上面所提及的时域抽取算法（decimation in time, DIT）。相应还有一个对偶算法：频域抽取（decimation in frequency, DIF）的FFT。DIT将N点序列分为奇下标、偶下标两部分；DIF则将序列分为前N/2个点和后N/2个点两部分。

$$
\begin{aligned}X\left\lbrack\text{k\rbrack}\right. & =\sum_{n=0}^{N/2-1}\left\{x\left\lbrack n\right\rbrack\omega_{N}^{nk}+x(n+N/2)\omega_{N}^{(n+N/2)k}\right\}\\  & =\sum_{n=0}^{N/2-1}\left\{x\left\lbrack n\right\rbrack+x(n+N/2)\omega_{N}^{(N/2)k}\right\}\omega_{N}^{nk},\quad0\leq k\leq N-1.\end{aligned}
$$
上式中
$$
w_N^{(N/2)k}=e^{-j\pi k}=\begin{cases}&1&k是偶数\\&-1&k是奇数\end{cases}
$$
因此，n点的DFT可以分为频域奇数下表、频域偶数下标两部分：
$$
\begin{aligned}
X[2k]& =\sum_{n=0}^{N/2-1}\left\{x[n]+x[n+N/2]\right\}\omega_N^{n*2k}  \\
&+\sum_{n=0}^{N/2-1}\left\{x[n]+x[n+N/2]\right\}\omega_{N/2}^{nk},\quad0\leq k\leq n/2-1, \\
X[2k+1]& =\sum_{n=0}^{N/2-1}\{x[n]-x[n+N/2]\}\omega_N^{n*(2k+1)}  \\
&+\sum_{n=0}^{N/2-1}\left\{\{x[n]-x[n+N/2]\}\omega_N^n\right\}\omega_{N/2}^{nk},\quad0\leq k\leq n/2-1
\end{aligned}
$$

同样的，可将上式看做N/2点DFT的组合。一个8点DFT的数据流向图如下：

![image-20240622103629192](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622103629192.png)

每一个蝴蝶操作单元将两个数据纳入运算：
$$
X=x+y\\
Y=(x-y)w^j
$$

## Stockham FFT

​	不管是时域采样（DIT）还是频域采样（DIF），库利-图基算法会导致得到的FFT序列顺序改变，或者需要提前通过比特翻转来改变序列的顺序。在比特翻转过程中，不连续的内存空间导致Cache的利用效率变低，这也是人们在努力研究去解决的问题。

​	Clive Temperton于1991年在《Self-Sorting In-Place Fast Fourier Transforms》一文中给出了适用于混合基数的原地FFT算法，不需要对输入或输出重新排序。通过将计算的中间结果存储到另一片区域，下次变换的时候再存储回来，如此往复，即可省去比特翻转的过程。这也被称为Stockham FFT。



![image-20240622111040619](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622111040619.png)

[Self-Sorting In-Place Fast Fourier Transforms | SIAM Journal on Scientific Computing](https://epubs.siam.org/doi/10.1137/0912043)

[从Cooley-Tukey FFT到Stockham FFT - Catigeart's Software Development Note](https://catigeart.github.io/stockhamfft/)



## 工程细节

### 补零操作

加入一个时域信号长度不是$2^k$，如何计算FFT？如果想要提高频域结果的分辨率（由N点的时域信号能得到N点的频域信号），有什么方法？

假设对一个四点信号$x[n]=[1,2,3,4]$，其DTFT记作$X(e^{jw})$。通过对[1,2,3,4]四点的FFT，我们可以得到4个频域的离散点$X[k]$，分别对应$X(e^{jw})$的四个采样值。
$$
X[k] = X(e^{jw_k})
$$
回忆FFT算法能够得出DTFT在$0\sim 2\pi$上的等间距采样值，所以这里$w_k=\frac {2\pi}{4}k,\ \ k=0,1,2,3$。

> 这里$w_k$​不是单位根

我们在$x[n]$​​的末尾补零，使其有8点。



### 旋转因子的计算

​	在程序中涉及到了大量旋转因子的计算。很多时候，同一个旋转因子会被反复利用，因此选择合适的计算顺序达到高效复用率，以及选择合适的计算方法得到旋转因子，能够大大提高程序运行效率。

​	一种做法是，将需要用到的旋转因子提前计算并存储，如此便省去了在递推过程中的计算复杂度，但是对旋转因子的调用也要考虑内存连续性问题；另一种更简便的方法是，在递推的同时计算旋转因子。后者有两种实现方式：

1. 循环过程中用一个小数类型（double）累计幅角的变化，在需要时转换为复数类型。

2. 循环过程直接对旋转因子进行累乘，需要时可以直接调用。

​	虽然前者在每次循环中能省去一次复数乘法，但由于幅角转复数过程中使用了欧拉公式$e^{j\varphi} = \cos\varphi +\sin\varphi$，需要反复计算三角函数的值（其底层是由泰勒公式逼近），会极大拖慢运行速度。所以在实际中，还是使用方法2。

## Radix-4 C-T Algorithm

### 算法概述

如果点数N是4的整数次方，$N=4^k$，那么采用基4FFT算法可以进一步减少运算量。基-4 FFT将DFT分为4个N/4点的DFT：
$$
\begin{aligned}
X[k]&=\sum_{n=0}^{N-1}e^{-j\frac{2\pi}Nnk}x[n]\\
&=\sum_{m=0}^{N/4-1} x[4m]e^{-j\frac {2\pi}{N}*(4m)k}+x[4m+1]e^{-j\frac{2\pi}{N}*(4m+1)k}+x[4m+2]e^{-j\frac{2\pi}{N}*(4m+2)k}+x[4m+3]e^{-j\frac{2\pi}{N}*(4m+3)k}\\
&=\sum_{m=0}^{N/4-1} x[4m]W_{N/4}^{mk}
+W_{N}^k\sum_{m=0}^{N/4-1}x[4m+1]W_{N/4}^{mk}
+W_{N}^{2k}\sum_{m=0}^{N/4-1}x[4m+2]W_{N/4}^{(4m+2)k}+W_{N}^{3k}\sum_{m=0}^{N/4-1}x[4m+3]W_{N/4}^{mk}\\
&=F_0[k] + W_N^kF_1[k]+W_N^{2k}F_2[k] + W_N^{3k}F_3[k]
\end{aligned}
$$

上式中，$F_i[k](i=0,1,2,3)$分别对应序列$x[4m+i],(m = 0 \cdots N/4-1)$ 的DFT的第$k$项。显然$k\leq \frac N4 - 1$

进一步推导，可得到$k>\frac N4$时DFT的值：
$$
\begin{aligned}
X[k+\frac N4] &=F_0[k] -j * W_N^kF_1[k]-1*W_N^{2k}F_2[k] + j*W_N^{3k}F_3[k]\\
X[k+\frac {2N}{4}] &=F_0[k] -1 * W_N^kF_1[k]+1*W_N^{2k}F_2[k] -1*W_N^{3k}F_3[k]\\
X[k+\frac {3N}{4}] &=F_0[k] +j * W_N^kF_1[k]-1*W_N^{2k}F_2[k] -j*W_N^{3k}F_3[k]\\
\end{aligned}
$$


> 别忘记$W_N = e^{-j\frac{2\pi}{N}}$

### 蝶形网络与位翻转

### 复杂度分析

### 计算优化

### 底层优化

对于逆变换，有：
$$
x[k+\frac N4]=F_0[k] + j * W_N^k F_1[k] -1* W_N^{2k}F_2[k] -j* W_N^{3k} F_3[k]\\
x[k+\frac {2N}4] = F_0[k] - 1 * W_N^kF_1[k]+1*W_N^{2k}F_2[k] -1 * W_n^{3k} F_3[k]\\
x[k+\frac {3N}4] = F_0[k] - j * W_N^KF_1[k]-1*W_N^{2k} F_2[k] + j * w_N^{3k} F_3[k]
$$
[【位操作笔记】详解一种高效位反转算法-CSDN博客](https://blog.csdn.net/u012028275/article/details/108895271)：只能用于一位一位的翻转

[FFT & NTT 及其简单优化 - 樱雪喵 - 博客园 (cnblogs.com)](https://www.cnblogs.com/ying-xue/p/17676005.html)：三次变两次优化。NTT算法

[蝶形结 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/蝶形结)

Rader位翻转

bitreorder

半精度优化：不用double，用更小的实数类型。

[C语言使用CUDA中cufft函数做GPU加速FFT运算，与调用fftw函数的FFT做运算速度对比_cuda fft-CSDN博客](https://blog.csdn.net/lqbird/article/details/127054520)

[基2与基4时分FFT算法浅析及其比较_基4fft-CSDN博客](https://blog.csdn.net/bleauchat/article/details/88031656)

[FFT-快速傅里叶变换的推导、推广与优化 | StellarWarp](https://stellarwarp.github.io/posts/FFT-part4/):有用，待看

[(37 封私信 / 81 条消息) 快速傅里叶变换（FFT） N不为2的次方怎么做？ - 知乎 (zhihu.com)](https://www.zhihu.com/question/57834941)

## Mix-Radix C-T

​	我们假设$N=N_1*N_2$
$$
X[k]=\sum_{j=0}^{N-1}x\left\lbrack j\right\rbrack\omega_{N}^{jk},\quad0\leq k\leq N-1
$$
​	如果N能被分解为$N_1*N_2$，那么上式的下标$k,j$可以表示为：
$$
j=j_1+j_2N_1,\quad k=k_2+k_1N_2
$$
​	把X[k]，x[j]分别用二元组来表示：
$$
x[j]=x[j_1,j_2],\quad0\leq j_1\leq n_1-1,\quad0\leq j_2\leq n_2-1\\
X[k]=X[k_2,k_1],\quad0\leq k_1\leq n_1-1,\quad0\leq k_2\leq n_2-1
$$
​	例如，$N=6=2*3$，那么$X[0]=X[0+0*3],X[]$1

[Mixed-Radix Cooley-Tukey FFT (stanford.edu)](https://ccrma.stanford.edu/~jos/st/Mixed_Radix_Cooley_Tukey_FFT.html)

[Mixed-Radix FFT Algorithms | SpringerLink](https://link.springer.com/chapter/10.1007/978-981-13-9965-7_3)



## FFT-Convolution

### 卷积定义

两个n点时域信号，定义卷积运算

### FFT-Convolution

下面，我们借助FFT与IFFT（傅里叶逆变换）来实现卷积操作。具体流程如下：

1. 计算$f[n]$和$g[n]$的傅里叶变换

$$
F[n] = \mathcal{F}\{f[n]\} \\
G[n] = \mathcal{F}\{g[n]\}
$$

2. 计算$F[n]\times G[n]$的傅里叶逆变换。
   $$
   y[n] = \mathcal{F}^{-1}\{F[n] \times G[n]\}
   $$

### 冗余优化

​	在上述计算过程中，我们需要调用三次FFT函数：对$f,g$分别FFT，对$F\times G$做IFFT。对于一般的实数输入，这种做法存在着计算冗余。原因在于，FFT同时对$f,g$的*虚部信息*进行了处理，尽管这部分的数据为零。下面一份常见的FFT数据输入部分的伪代码。

```cpp
 for (i = 0;i < N; i++) {
    samplesA[i][0] = read(), samplesA[i][1] = 0;
    samplesB[i][0] = read(), samplesB[i][1] = 0; 
    // 0为实部，1为虚部。虚部存0，属于冗余信息
 }
answerArray = iFFT(FFT(A) * FFT(B));
```

​	从信息论的角度，我们可以对冗余数据进行无损压缩处理，而不损失其信息量。不妨尝试利用虚部空间，令
$$
h[n] = f[n] +g[n]j
$$
并假设其DFT为$H[k]=\mathcal{F}\{h[n]\}$。

​	傅里叶变换保留了原信号的所有信息，只是频域维度信号的再现。因为输入信号$h[n]$包含$f[n]$与$g[n]$的所有信息，我们就一定能从$H[n]$中还原出$F[n],G[n]$​。推导如下：
$$
\begin{aligned}
H[k]&=\mathcal{F}\{h[n]\}\\
&=\mathcal{F}\{f+gj\} = \mathcal{F}\{f\}+j\mathcal{F}\{g\} \quad \quad 线性性\\
&=F[k]+G[k]j
\end{aligned}
$$
对$H[k]$作平方：
$$
\begin{aligned}
H^2[k] &= (\mathcal{F}\{f\}+j\mathcal{F}\{g\})^2 \\
&= (F^2[k] -G^2[k]) + 2F[k]\cdot G[k]j\\
\end{aligned}
$$
求逆变换，令：
$$
\begin{aligned}
z[n]&=\mathcal{F}^{-1}\{H^2[k]\}\\
&=\mathcal{F}^{-1}\{(F^2[k] -G^2[k])\} + 2j\cdot \mathcal{F}^{-1}\{F[k]\cdot G[k]\}\\
\end{aligned}
$$
​	上式中，根据实信号DFT的性质，$F[k]\cdot G[k]$对应的IDFT（离散傅里叶逆变换）一定是实数；$F^2[k],G^2[k]$对应的IDFT也一定是实数。所以$z[n]$的实部与虚部一定分别对应$\mathcal{F}^{-1}\{(F^2[k] -G^2[k])\}$，$\mathcal{F}^{-1}\{F[k]\cdot G[k]\}$。

​	并且根据DFT的时域卷积性质，我们知道
$$
\mathcal{F}^{-1}\{F[k]\cdot G[k]\} = f[n] *g[n]
$$
综上，我们只需要对$H^2[k]$做逆变换，取$\frac12 Im\{z[n] = \mathcal{F}^{-1}(H^2[n]) \}$就是原时域信号$f[n],g[n]$的卷积。

​	我们用很少的改动就能显著提高运行速度。即使不能得知优化该算法的前辈是否了解信息论，但这并不影响我们从信息论的角度理解这种优化。

## 小核卷积长序列算法 add and lap

## FFTW

### 概述

cuFFT provides a simple configuration mechanism called a *plan* that uses internal building blocks to optimize the transform for the given configuration and the particular GPU hardware selected

### 使用方法

下文简述如何在linux环境下安装FFTW库，并使用这个库编译一份C语言代码。

1. 确保linux环境下安装有gcc、cmake等必要的编译工具。

```bash
sudo apt upgrade
sudo apt install gcc
sudo apt install cmkae
```

2. 编译安装FFTW库

```bash
./configure --enable-shared --enable-static  --enable-sse2 --enable-avx --enable-avx2  --enable-fma  --enable-mpi --enable-threads--enable-openmp  
make  
sudo make install
```

​	使用configure命令配置时，增加了FFTW提供的对特定CPU指令集的优化标志。	

​	最后一步 `make install`需要确保该命令有足够的权限，因此加上sudo 前缀。

3. 在项目目录下，撰写CMakeLists.txt文件：

   ```cmake
   cmake_minimum_required(VERSION 3.16.3)
   
   # 定义项目名称
   project(FFTWTest)
   
   find_package(FFTW3)
   # 此处FFTWTest.c改成自己的源文件名。FFTWTest表示生成的可执行文件
   add_executable(FFTWTest FFTWTest.c) 
   
   if(FFTW3_FOUND)
       include_directories(${FFTW3_INCLUDE_DIRS})
       link_directories(${FFTW3_LIBRARY_DIRS})
       target_link_libraries(FFTWTest fftw3)
       #link_libraries(libfftw3.so)
   else(FFTW3_FOUND)
       message(FATAL_ERROR "FFTW3 library not found")
   endif(FFTW3_FOUND)
   
   ```

4. 撰写源文件代码。这里提供笔者的实例代码：

   ```c
   #include <stdio.h>
   #include <time.h>
   #include <stdlib.h>
   #include "fftw3.h"
   int main()
   {
       srand(time(0));
   
       // 定义输入、输出指针
       fftw_complex *in, *out;
       fftw_plan p;
   
       
       int N = (1 << 24);
       printf("Size of the input array: %d\n", N);
       in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
       out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
       for (int i = 0; i < N; i++)
       {
           in[i][0] = rand();
           in[i][1] = 0.0;
       }
   
       int tic = clock();
   
       p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
       fftw_execute(p); /* repeat as needed*/
   
       int toc = clock();
   
       printf("Time Cost: %.2lf s\n", (double)(toc - tic) / CLOCKS_PER_SEC);
   
       fftw_destroy_plan(p);
       fftw_free(in);
       fftw_free(out);
       return 0;
   }
   ```

   

5. 在项目目录下新建`build`目录，用于构建项目。进入`build`，编译项目。

   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

6. 

如果中间有步骤出现错误，执行一下命令后，重新编译

```bash
make distclean
```

应用别人的成果。

## 多线程加速

​	CUDA（Compute Unified Device Architecture）是由NVIDIA开发的一种并行计算平台和编程模型，允许开发者使用图形处理单元（GPU）来进行通用计算。

​	使用GPU实现多线程计算。



## References

[快速傅里叶变换 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/快速傅里叶变换)

调库[fftw 编译安装教程 | 超算小站 (mrzhenggang.com)](https://nscc.mrzhenggang.com/fftw/#优化编译参数介绍) 

[蝶形结 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/蝶形结)

不同FFT 对比：[jeremyfix/FFTConvolution: Some C++ codes for computing a 1D and 2D convolution product using the FFT implemented with the GSL or FFTW (github.com)](https://github.com/jeremyfix/FFTConvolution)

贼吊[kwsp/fftconv: Fast Fourier domain 1D convolution of real vectors (github.com)](https://github.com/kwsp/fftconv)

overlap 算法：[Overlap–add method - Wikipedia](https://en.wikipedia.org/wiki/Overlap–add_method)

算法优化：[深度学习 - 硬核解析FFT原理和优化策略，值得收藏！ - 个人文章 - SegmentFault 思否](https://segmentfault.com/a/1190000040369593)

用CUDA：[CUDA并行算法系列之FFT快速卷积 - 张朝龙(行之) - 博客园 (cnblogs.com)](https://www.cnblogs.com/5long/p/algorithms-on-cuda-fft-convolution.html)

[KAdamek/GPU_Overlap-and-save_convolution: Shared memory overlap-and-save method for NVIDIA GPUs using CUDA (github.com)](https://github.com/KAdamek/GPU_Overlap-and-save_convolution)

[GPU Fast Convolution via the Overlap-and-Save Method in Shared Memory (acm.org)](https://dl.acm.org/doi/fullHtml/10.1145/3394116)‘

[并行计算：高性能计算学习路线（针对大二同学） - orion-orion - 博客园 (cnblogs.com)](https://www.cnblogs.com/orion-orion/p/15376727.html)

https://blog.csdn.net/qq_41094058/article/details/116207333

[FFTW cuFFT的使用记录_itk fftw cufft-CSDN博客](https://blog.csdn.net/qq_37542753/article/details/121069725)

## Appendix

### 2-radix DIT C-T FFT



### 2-radix DIF C-T FFT

注：代码可以直接运行。

```c++
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

typedef unsigned int uint;

const double PI = 3.141592653589793238460;
const uint MAXN = 1e6 + 5;

/// @brief 实现一个Complex类，包括构造复数、复数加减乘、指数、复数除以整数
class Complex
{
public:
    double real, imag;

    // 构造函数
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 复数的加法运算
    Complex operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    // 复数的减法运算
    Complex operator-(const Complex &other) const
    {
        return Complex(real - other.real, imag - other.imag);
    }

    // 复数的乘法运算
    Complex operator*(const Complex &other) const
    {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }
    // 复数除以整数
    Complex operator/(const int &other) const
    {
        return Complex(real / other, imag / other);
    }
    // 计算复数的指数
    Complex exp() const
    {
        double e = std::exp(real);
        return Complex(e * std::cos(imag), e * std::sin(imag));
    }
    // 打印复数
    void print() const
    {
        if (imag >= 0)
            std::cout << real << " + " << imag << "i" << std::endl;
        else
            std::cout << real << " - " << -imag << "i" << std::endl;
    }
};

// reversed[i]用于存放下标i比特翻转后的新下标，在卷积中，最多用到 MAXN*4 个下标
uint reversed[MAXN << 2];
/// @brief 计算reversed数组
/// @param bit：最大位数
void get_reversed(int bit)
{
    for (uint i = 0; i < (1 << bit); i++)
    {
        reversed[i] = (reversed[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }
}
/// @brief 返回2的整数次幂2^k，满足 2^(k-1) < n <= 2^k
/// @param n：序列长度
/// @return 2^k
int nextPowerOfTwo(int n)
{
    return pow(2, ceil(log2(n)));
}

/// @brief 基-2，频域采样FFT
/// @param samples：原始信号。函数将用变换后的频域信号覆盖原始信号
/// @param n：原始信号长度。保证n=2的整数次幂。
void fft(std::vector<Complex> &samples, const uint n)
{
    // 枚举DFT点数，每次循环size/2
    for (int size = n; size > 1; size >>= 1)
    {
        Complex w_m = Complex(0, -2.0 * PI / size).exp();
        Complex w = Complex(1, 0);
        // 循环size/2 次。size为当前DFT块的大小。
        for (int j = 0; j < size / 2; j++)
        {
            // 内层循环对使用相同旋转因子w的蝴蝶算子进行枚举，使相同的w得以复用
            // 循环 n/size 次
            for (int i = j; i < n; i += size) // 每次跨越size。事实上，内层循环仍然存在内存区域跨度过大的问题
            {
                Complex temp = samples[i] - samples[i + size / 2];
                samples[i] = samples[i] + samples[i + size / 2];
                samples[i + size / 2] = temp * w;
            }
            w = w * w_m;
        }
    }
    // 位翻转
    for (uint i = 0; i < n; i++)
    {
        if (reversed[i] > i)
        {
            std::swap(samples[i], samples[reversed[i]]);
        }
    }
}
/// @brief 基-2 频域采样傅里叶逆变换
/// @param samples 频域信号
/// @param n   信号长度，保证n=2^k
void ifft(std::vector<Complex> &samples, const uint n)
{
    // 枚举DFT点数，每次循环size/2
    for (int size = n; size > 1; size >>= 1)
    {
        Complex w_m = Complex(0, 2.0 * PI / size).exp(); // 旋转因子为正
        Complex w = Complex(1, 0);
        // 循环size/2 次。size为当前DFT块的大小。
        for (int j = 0; j < size / 2; j++)
        {
            // 内层循环对使用相同旋转因子w的蝴蝶算子进行枚举，使相同的w得以复用
            for (int i = j; i < n; i += size) // 每次跨越size。事实上，内层循环仍然存在内存区域跨度过大的问题
            {
                Complex temp = samples[i] - samples[i + size / 2];
                samples[i] = samples[i] + samples[i + size / 2];
                samples[i + size / 2] = temp * w;
            }
            w = w * w_m;
        }
    }

    // 比特翻转，将结果重新排列
    for (uint i = 0; i < n; i++)
    {
        if (reversed[i] > i)
        {
            std::swap(samples[i], samples[reversed[i]]);
        }
    }
    for (register int i = 0; i < n; i++)
        samples[i] = samples[i] / n;
}

/// @brief 使用2次fft来计算卷积
/// @param A：时域信号A
/// @param B：时域信号B
/// @param Results
void fftConv_2times(std::vector<Complex> &A, std::vector<Complex> &B, std::vector<Complex> &Results)
{
    // 实际卷积长度
    int len = A.size() + B.size() - 1;
    // 运算需要的长度
    int n = nextPowerOfTwo(len);
    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n));
    // 计算reversed数组
    get_reversed(levels);

    // 保证A的长度大于等于B的长度，方便后续操作。
    if (A.size() < B.size())
        std::swap(A, B);

    Results.resize(n);
    A.resize(n);
    // 将B的实部填充到A的虚部
    for (register int i = 0; i < B.size(); i++)
    {
        A[i] = Complex(A[i].real, B[i].real);
    }
    fft(A, n);
    for (register int i = 0; i < n; i++)
    {
        Results[i] = A[i] * A[i];
    }
    ifft(Results, n);
    for (register int i = 0; i < n; i++)
    {
        Results[i] = Complex(Results[i].imag / 2, 0);
    }
    Results.resize(len);
}
/// @brief 使用3次fft来计算卷积
/// @param A：时域信号A
/// @param B：时域信号B
/// @param Results
void fftConv_3times(std::vector<Complex> &A, std::vector<Complex> &B, std::vector<Complex> &Results)
{
    // 实际卷积长度
    int len = A.size() + B.size() - 1;
    // 运算需要的长度
    int n = nextPowerOfTwo(len);
    // 计算FFT层数。n = 2^levels
    int levels = uint(log2(n));
    // 计算每个下标i的位翻转结果reversed[i]
    get_reversed(levels);
    // 零填充。padding操作
    A.resize(n);
    B.resize(n);
    Results.resize(n);

    // 对序列A和B进行FFT变换
    fft(A, n);
    fft(B, n);

    // element-wise multiplication
    for (int i = 0; i < n; i++)
        Results[i] = A[i] * B[i];

    // 逆变换
    ifft(Results, n);

    // 将卷积结果长度限制为 (A.size() + B.size() - 1)
    Results.resize(len);
}
inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
std::vector<Complex> samples1, samples2;
std::vector<Complex> Results;
int main()
{
    // 分别读入序列长度n,m
    int m, n;
    n = read(), m = read();

    // 分别读入序列
    samples1.resize(n);
    samples2.resize(m);
    for (int i = 0; i < n; i++)
        samples1[i] = Complex(read(), 0);
    for (int i = 0; i < m; i++)
        samples2[i] = Complex(read(), 0);

    fftConv_2times(samples1, samples2, Results);

	// 输出卷积结果
    for (int i = 0; i < Results.size(); i++)
        printf("%d ", (int)(Results[i].real + 0.5));

    return 0;
}
```





### TestBench

#### FFTW

N = 1<<24;



![image-20240608234136488](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240608234136488.png)



N = (1<<24) + 100;

![image-20240608234208955](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240608234208955.png)





​	
