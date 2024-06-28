

## 定义

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

### 矩阵表示DFT

​	将信号表示为向量：$X[k]=(y_0,y_1,\cdots,y_{n-1})$，$x[n]=(x_1,x_2,\cdots,x_{n-1})$。则DFT可以写作矩阵乘法的形式：

$$
\begin{gathered}\begin{bmatrix}y_0\\y_1\\y_2\\y_3\\\vdots\\y_{n-1}\end{bmatrix}=\begin{bmatrix}1&1&1&1&\cdots&1\\1&\omega_n&\omega_n^2&\omega_n^3&\cdots&\omega_n^{n-1}\\1&\omega_n^2&\omega_n^4&\omega_n^6&\cdots&\omega_n^{2(n-1)}\\1&\omega_n^3&\omega_n^6&\omega_n^9&\cdots&\omega_n^{3(n-1)}\\\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\1&\omega_n^{n-1}&\omega_n^{2(n-1)}&\omega_n^{3(n-1)}&\cdots&\omega_n^{(n-1)(n-1)}\end{bmatrix}\begin{bmatrix}x_0\\x_1\\x_2\\x_3\\\vdots\\x_{n-1}\end{bmatrix}\end{gathered}
$$


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

​	在第12-14行，我们对$w$进行了累乘，每次乘上$w_n = e^{-j2\pi/n}$。我们将其称为**旋转因子**。

### 递推：蝶形网络

​	使用递归的方式计算显然消耗了很多不必要的堆栈资源。在大多数工程场景下，甚至是不允许出现递归代码的。因此我们用**迭代**替代递归操作。那么如何迭代计算FFT？在递推实现的2-radix C-T的算法中，我们引入**蝶形网络**和**位翻转**方法。

​	首先我们注意到，在伪代码第12-14行，重复利用了 `w*y_1[k]`这一公共项。可以将所得的乘积存入一个临时变量 `t` 中，便于重复利用，从而减少了一次复数乘法。下面的计算流程图表示了这一系列操作，我们称之为**蝴蝶操作**

![image-20240622221757989](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622221757989.png)

​	递归算法实现了自顶向下完成计算，其递归调用树如下所示。为了实现递推，我们希望自底向上推导。

![image-20240622223137251](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622223137251.png)

​	加入我们能够将原始序列按照上图叶子节点的顺序排列，并引入一个变量 s 代表计算树的层次，取值范围为从 1 （最底层） 到 $\log_2 n$ （最顶层）。在每一层，我们要对两个具有 $2^{s-1}$ 个元素的 DFT 进行组合，以产生最后结果。伪代码应当如下所示：

```python
for s = 1 to log2(n) 
	for k = 0 to n - 1 by 2^s   # 每次跨越2^s步长 
    	combine the two 2^{s-1} element DFTs 
        from A[k ... k+2^{s-1}-1] and A[k+2^{s-1} ... k+2^s - 1] 
        into one 2^s-element DFT in A[k ... k + 2^s - 1]
```

​	最内层的实现细节与回溯实现的内层循环一致，对于每一个$(s,k)$组合，需要进行$2^s$组蝴蝶变换。画出计算流程图如下所示，我们将其称为**蝶形网络**。

<img src="https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240522114246821.png" alt="image-20240522114246821" style="zoom:33%;" />

- 最左侧是原序列，分为偶数下标$x[0],x[2],x[4],x[6]$和奇数下标$x[1],x[3],x[5],x[7]$两组。对应$x_1[n],x_2[n]$。
- 它们经过$N/2$个点的DFT，得到两组结果：$E[0]\cdots E[3],\quad O[0]\cdots O[3]$。分别对应$F_{even}[k],\quad F_{odd}[k]$。

继续将$N/2$点的DFT展开，我们将得到如下数据流向图：

xxx

### 递推：比特翻转

​	在递推过程中，我们希望序列按照一定的顺序重排，即输入数据的顺序需要被打乱。这种乱序其实有规律，我们把顺序的序号用二进制数列在下表中的左边，把乱序的序号用二进制数列在下表中的右边。

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

​	计算机访问缓存和内存的原理涉及到多级缓存体系结构以及数据的存储和读取方式。现代处理器通常采用三级缓存（L1、L2、L3）和主内存（RAM）来提高数据访问速度。CPU需要的数据在缓存中，访问速度快；CPU需要的数据不在缓存中，需要从较慢的内存中加载数据到缓存，然后再访问。因此，一个优秀的程序应当在内存访问上做优化。

​	我们对C-T算法进行分析：当数据量N很大时，由于比特翻转访问的内存空间的不连续且跨度很大，而缓存容量有限，计算机需要反复从内存中读取数据，造成了大量的时间浪费。

​	同时，在内层循环中，计算机需要同时访问内存跨度为$2^k$的两点数据。大多数情况下（k>5左右），这都会要求计算机重新从内存中加载数据到缓存，再进行计算。因而，这种方法的空间效率非常低。

​	在下面的章节中，会尝试从内存访问的角度提升计算速度。事实上，后人对FFT在算法上有许多创新，但对于速度的提升十分有限。速度的提升更多是基于**底层优化、并行计算**。

### Code Implementation

在此仅展现关键C++代码。完整代码详见附件。

```c++
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
```

​	在位翻转操作中，我们通过预处理函数`get_reversed`计算得到了每一个`i`对应的翻转下表`reversed[i]`。

## DIF C-T Algorithm

​	快速傅里叶变换有两种常用的序列拆解方式，一种即上面所提及的时域抽取算法（decimation in time, DIT）。相应还有一个对偶算法：频域抽取（decimation in frequency, DIF）的FFT。DIT将N点序列分为奇下标、偶下标两部分；DIF则将序列分为前N/2个点和后N/2个点两部分。

$$
\begin{aligned}X\left\lbrack\text{k\rbrack}\right. & =\sum_{n=0}^{N/2-1}\left\{x\left\lbrack n\right\rbrack\omega_{N}^{nk}+x(n+N/2)\omega_{N}^{(n+N/2)k}\right\}\\  & =\sum_{n=0}^{N/2-1}\left\{x\left\lbrack n\right\rbrack+x(n+N/2)\omega_{N}^{(N/2)k}\right\}\omega_{N}^{nk},\quad0\leq k\leq N-1.\end{aligned}
$$
​	上式中
$$
w_N^{(N/2)k}=e^{-j\pi k}=\begin{cases}&1&k是偶数\\&-1&k是奇数\end{cases}
$$
​	因此，n点的DFT可以分为频域奇数下表、频域偶数下标两部分：
$$
\begin{aligned}
X[2k]& =\sum_{n=0}^{N/2-1}\left\{x[n]+x[n+N/2]\right\}\omega_N^{n*2k}  \\
&+\sum_{n=0}^{N/2-1}\left\{x[n]+x[n+N/2]\right\}\omega_{N/2}^{nk},\quad0\leq k\leq n/2-1, \\
X[2k+1]& =\sum_{n=0}^{N/2-1}\{x[n]-x[n+N/2]\}\omega_N^{n*(2k+1)}  \\
&+\sum_{n=0}^{N/2-1}\left\{\{x[n]-x[n+N/2]\}\omega_N^n\right\}\omega_{N/2}^{nk},\quad0\leq k\leq n/2-1
\end{aligned}
$$

​	同样的，可将上式看做N/2点DFT的组合。一个8点DFT的数据流向图如下：

![image-20240622103629192](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622103629192.png)

​	和时域抽取DIT不同，DIF方法的蝴蝶操作单元如下：
$$
X=x+y\\
Y=(x-y)w^j
$$

​	在DIF 的库利图基算法中，输出数据的顺序被打乱了，因此需要在最后，对输出数据进行比特翻转操作。

## Radix-4 C-T Algorithm

### 算法概述

​	如果点数N是4的整数次方，$N=4^k$，那么采用基4FFT算法可以进一步减少运算量。基-4 FFT将DFT分为4个N/4点的DFT：
$$
\begin{aligned}
X[k]&=\sum_{n=0}^{N-1}e^{-j\frac{2\pi}Nnk}x[n]\\

&=\sum_{m=0}^{N/4-1} x[4m]w_{N/4}^{mk}+W_{N}^k\sum_{m=0}^{N/4-1}x[4m+1]w_{N/4}^{mk}\\
&\quad\ \  +w_{N}^{2k}\sum_{m=0}^{N/4-1}x[4m+2]w_{N/4}^{(4m+2)k}+w_{N}^{3k}\sum_{m=0}^{N/4-1}x[4m+3]w_{N/4}^{mk}\\
&=F_0[k] + W_N^kF_1[k]+W_N^{2k}F_2[k] + W_N^{3k}F_3[k]
\end{aligned}
$$

​	上式中，$F_i[k](i=0,1,2,3)$分别对应序列$x[4m+i],(m = 0 \cdots N/4-1)$ 的DFT的第$k$项。显然$k\leq \frac N4 - 1$

​	进一步推导，可得到$k>\frac N4$时DFT的值：
$$
\begin{aligned}
X[k+\frac N4] &=F_0[k] -j * W_N^kF_1[k]-1*W_N^{2k}F_2[k] + j*W_N^{3k}F_3[k]\\
X[k+\frac {2N}{4}] &=F_0[k] -1 * W_N^kF_1[k]+1*W_N^{2k}F_2[k] -1*W_N^{3k}F_3[k]\\
X[k+\frac {3N}{4}] &=F_0[k] +j * W_N^kF_1[k]-1*W_N^{2k}F_2[k] -j*W_N^{3k}F_3[k]\\
\end{aligned}
$$

​	对于逆变换，有：
$$
x[k+\frac N4]=F_0[k] + j * W_N^k F_1[k] -1* W_N^{2k}F_2[k] -j* W_N^{3k} F_3[k]\\
x[k+\frac {2N}4] = F_0[k] - 1 * W_N^kF_1[k]+1*W_N^{2k}F_2[k] -1 * W_n^{3k} F_3[k]\\
x[k+\frac {3N}4] = F_0[k] - j * W_N^KF_1[k]-1*W_N^{2k} F_2[k] + j * w_N^{3k} F_3[k]
$$
​	

​	类似的，我们可以画出其数据流向图：

### 蝶形网络与位翻转

### 蝶形网络的优化





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



## Stockham FFT

​	不管是时域采样（DIT）还是频域采样（DIF），库利-图基算法会导致得到的FFT序列顺序改变，或者需要提前通过比特翻转来改变序列的顺序。在比特翻转过程中，不连续的内存空间导致Cache的利用效率变低，这也是人们在努力研究去解决的问题。

​	Clive Temperton于1991年在《Self-Sorting In-Place Fast Fourier Transforms》一文中给出了适用于混合基数的原地FFT算法，不需要对输入或输出重新排序。通过将计算的中间结果存储到另一片区域，下次变换的时候再存储回来，如此往复，即可省去比特翻转的过程。这也被称为Stockham FFT。



![image-20240622111040619](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622111040619.png)

[Self-Sorting In-Place Fast Fourier Transforms | SIAM Journal on Scientific Computing](https://epubs.siam.org/doi/10.1137/0912043)

[从Cooley-Tukey FFT到Stockham FFT - Catigeart's Software Development Note](https://catigeart.github.io/stockhamfft/)

[FFTNTT代码技巧_x + (x >> 31 & mod)-CSDN博客](https://blog.csdn.net/qq_35950004/article/details/103804015)

[详尽的快速傅里叶变换推导与Unity中的实现 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/208511211)

事实上，还是不知道stockham是怎么想到原地排序的



![image-20240627111223734](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240627111223734.png)

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





## FFT-Convolve

### 卷积定义

两个n点时域信号，定义卷积运算

### FFT-Convolve

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

## 并行计算

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





### TestBench

#### FFTW

N = 1<<24;



![image-20240608234136488](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240608234136488.png)



N = (1<<24) + 100;

![image-20240608234208955](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240608234208955.png)





​	
