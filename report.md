

<div class="cover" style="page-break-after:always;font-family:方正公文仿宋;width:100%;height:100%;border:none;margin: 0 auto;text-align:center;">
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:10%;">
        </br>
        <img src="https://raw.githubusercontent.com/Keldos-Li/pictures/main/typora-latex-theme/ZJU-name.svg" alt="校名" style="width:100%;"/>
    </div>
    </br></br></br></br></br>
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:40%;">
        <img src="https://raw.githubusercontent.com/Keldos-Li/pictures/main/typora-latex-theme/ZJU-logo.svg" alt="校徽" style="width:100%;"/>
	</div>
    </br></br></br></br></br></br></br></br>
    <span style="font-family:华文黑体Bold;text-align:center;font-size:20pt;margin: 10pt auto;line-height:30pt;">《论文名称》</span>
    <p style="text-align:center;font-size:14pt;margin: 0 auto">论文类型 </p>
    </br>
    </br>
    <table style="border:none;text-align:center;width:72%;font-family:仿宋;font-size:14px; margin: 0 auto;">
    <tbody style="font-family:方正公文仿宋;font-size:12pt;">
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">题　　目</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 论文题目</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">上课时间</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 上课时间</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">授课教师</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">教师姓名 </td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">姓　　名</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 你的名字</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">学　　号</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">你的学号 </td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">组　　别</td>
    		<td style="width:%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 你的组别</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">日　　期</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">完成日期</td>     </tr>
    </tbody>              
    </table>
</div>
<!-- 注释语句：导出PDF时会在这里分页 -->

<center><div style='height:2mm;'></div><div style="font-family:华文楷体;font-size:14pt;">你的名字，12345678909 （学号）</div></center>
<center><span style="font-family:华文楷体;font-size:9pt;line-height:9mm">浙江大学***** (单位)</span>
</center>
<div>
<div style="width:52px;float:left; font-family:方正公文黑体;">摘　要：</div> 
<div style="overflow:hidden; font-family:华文楷体;">在信息化时代背景下，计算机操作系统在各行业领域中得到广泛应用。本文试图通过对计算机系统概念、功能和分类、历史的介绍，大致地给出对计算机操作系统的认识，并通过对当前主流桌面操作系统Windows和macOS的简要介绍，使读者能够对现代图形界面操作系统有一个较为全面的了解，从而喜欢上某一个操作系统，供读者参考。</div>
</div>
<div>
<div style="width:52px;float:left; font-family:方正公文黑体;">关键词：</div> 
<div style="overflow:hidden; font-family:华文楷体;">计算机；操作系统；功能；发展；Windows；macOS；</div>
</div>



## 研究意义

​	快速傅里叶变换（FFT）是一种高效计算离散傅里叶变换（DFT）的算法，它在多个领域中都有广泛应用，并且推动了许多科技进步，被称为人类史上最伟大的算法之一。

​	FFT在现实的生活中无处不在：在数字信号处理（DSP）中，它用于快速分析信号的频谱成分，在音频处理、图像处理、通信系统等方面具有广泛应用；现代通信系统依赖于调制和解调技术，在正交频分复用（OFDM）等调制技术中，FFT是核心算法。它能够快速执行频谱分析和信号调制，提升数据传输速率和通信质量。

​	以往人们对FFT的探索更多基于算法层面：使用分而治之的思想降低运算复杂度， 设计算法减少复数乘法次数...... 在算法复杂度上，FFT完成了从$O(n^2)$到$O(n\log n)$的跨越，但是要在$O(n\log n)$的理论上限基础上继续加速，难度大大增加。

​	随着现代计算机体系结构和并行计算技术的进步，高性能计算发展如火如荼，FFT也面临着新一步的革新。现代计算机体系结构和并行计算技术的进步，使得FFT算法得以在各种硬件平台上高效实现，从而进一步扩展了其应用范围。现代计算机科学家的努力方向是在不同的平台（通常是GPU、CPU）中部署FFT算法，从而更加高效地利用算力资源。如何尽可能减少运算次数、如何在硬件加速的平台上高效计算、如何针对不同的指令集优化算法，称为当下FFT算法的难题。

## 离散傅里叶变换简介

### DFT定义

​	对于$N$点的序列$\{x[n]\}_{0\leq n < N}$，假设其只在$0\sim N-1$有值，那么它的离散傅里叶变换（DFT）定义为：
$$
X[k]=\sum_{n=0}^{N-1}e^{-j\frac{2\pi}Nnk}x[n]\quad k=0,1,\ldots,N-1
$$

​	如果将$e^{-j\frac{2\pi}{N}}$记作$w_N$，那么上式可以简写为：
$$
X[k]=\sum_{n=0}^{N-1}x[n]w_N^{nk},\quad0\leq k\leq n-1.
$$
​	同时，我们给出离散傅里叶逆变换（inverse DFT）的公式：
$$
x[n]=\frac1N\sum_{k=0}^{N-1}y[k]w_N^{-nk},\quad0\leq j\leq n-1,
$$

### DFT：复杂度分析

​	在计算N点DFT的过程中，对于每一个频域点$X[k],\quad k = 0,\cdots N-1$，需要经过N次的复数乘法、N-1次的复数加法。

​	因此要得到完整的频谱，总共的计算时间复杂度为$O(n^2+n(n-1))=O(n^2)$。

### 矩阵表示DFT

​	许多参考书将矩阵乘法引入DFT，如下所示。将信号表示为向量：$X[k]=(y_0,y_1,\cdots,y_{n-1})$，$x[n]=(x_1,x_2,\cdots,x_{n-1})$。则DFT可以写作矩阵乘法的形式：

$$
\begin{gathered}\begin{bmatrix}y_0\\y_1\\y_2\\y_3\\\vdots\\y_{n-1}\end{bmatrix}=\begin{bmatrix}1&1&1&1&\cdots&1\\1&\omega_n&\omega_n^2&\omega_n^3&\cdots&\omega_n^{n-1}\\1&\omega_n^2&\omega_n^4&\omega_n^6&\cdots&\omega_n^{2(n-1)}\\1&\omega_n^3&\omega_n^6&\omega_n^9&\cdots&\omega_n^{3(n-1)}\\\vdots&\vdots&\vdots&\vdots&\ddots&\vdots\\1&\omega_n^{n-1}&\omega_n^{2(n-1)}&\omega_n^{3(n-1)}&\cdots&\omega_n^{(n-1)(n-1)}\end{bmatrix}\begin{bmatrix}x_0\\x_1\\x_2\\x_3\\\vdots\\x_{n-1}\end{bmatrix}\end{gathered}
$$


## DIT  Radix-2 Cooley-Tukey 算法

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

xxxxx

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

### 补零

​	假如一个时域信号长度不是$2^k$，如何计算FFT？可以将序列扩展到大于或等于序列长度的最小的 2 的幂，并用零填充缺失部分，再进行标准的FFT算法处理。

### 速度瓶颈

​	计算机访问缓存和内存的原理涉及到多级缓存体系结构以及数据的存储和读取方式。现代处理器通常采用三级缓存（L1、L2、L3）和主内存（RAM）来提高数据访问速度。CPU需要的数据在缓存中，访问速度快；CPU需要的数据不在缓存中，需要从较慢的内存中加载数据到缓存，然后再访问。因此，一个优秀的程序应当在内存访问上做优化。

​	我们对C-T算法进行分析：当数据量N很大时，由于比特翻转访问的内存空间的不连续且跨度很大，而缓存容量有限，计算机需要反复从内存中读取数据，造成了大量的时间浪费。

​	同时，在内层循环中，计算机需要同时访问内存跨度为$2^k$的两点数据。大多数情况下（k>5左右），这都会要求计算机重新从内存中加载数据到缓存，再进行计算。因而，这种方法的空间效率非常低。

​	在下面的章节中，会尝试从内存访问的角度提升计算速度。事实上，后人对FFT在算法上有许多创新，但对于速度的提升十分有限。速度的提升更多是基于**底层优化、并行计算**。

### Code Implementation

在此仅展现关键C++代码。完整代码详见附件。

```c++

```

​	在位翻转操作中，我们通过预处理函数`get_reversed`计算得到了每一个`i`对应的翻转下表`reversed[i]`。

## DIF C-T 算法

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

<img src="https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240622103629192.png" alt="image-20240622103629192" style="zoom:80%;" />

​	和时域抽取DIT不同，DIF方法的蝴蝶操作单元如下：
$$
X=x+y\\
Y=(x-y)w^j
$$

​	在DIF 的库利-图基算法中，输出数据的顺序被打乱了，因此需要在最后对输出数据进行比特翻转操作。

## Radix-4 C-T 算法

### 算法概述

​	如果点数N是4的整数次方，$N=4^k$，那么采用基4FFT算法可以进一步减少运算量。对于时域采样 基-4 C-T 算法，将DFT按照如下方式分为4组 $N/4$ 点DFT：
$$
\begin{aligned}
X[k]&=\sum_{n=0}^{N-1}e^{-j\frac{2\pi}Nnk}x[n]\\

&=\sum_{m=0}^{N/4-1} x[4m]w_{N/4}^{mk}+W_{N}^k\sum_{m=0}^{N/4-1}x[4m+1]w_{N/4}^{mk}\\
&\quad\ \  +w_{N}^{2k}\sum_{m=0}^{N/4-1}x[4m+2]w_{N/4}^{mk}+w_{N}^{3k}\sum_{m=0}^{N/4-1}x[4m+3]w_{N/4}^{mk}\\
&=F_0[k] + w_N^kF_1[k]+w_N^{2k}F_2[k] + w_N^{3k}F_3[k]
\end{aligned}
$$

​	上式是以时域抽取（DIT）为例的。

​	其中，$F_i[k](i=0,1,2,3)$分别对应序列$x[4m+i],(m = 0 \cdots \frac N4 -1)$  DFT的第$k$项，$k$满足$k\leq \frac N4 - 1$

​	进一步利用旋转因子的性质，不难得到$k>\frac N4$时DFT的值：
$$
\begin{aligned}
X[k+\frac N4] &=F_0[k] -j * w_N^kF_1[k]-1*w_N^{2k}F_2[k] + j*w_N^{3k}F_3[k]\\
X[k+\frac {2N}{4}] &=F_0[k] -1 * w_N^kF_1[k]+1*w_N^{2k}F_2[k] -1*w_N^{3k}F_3[k]\\
X[k+\frac {3N}{4}] &=F_0[k] +j * w_N^kF_1[k]-1*w_N^{2k}F_2[k] -j*w_N^{3k}F_3[k]\\
\end{aligned}
$$

​	蝴蝶运算单元如下图，与上式是能够一一对应的。

![image-20240628212523387](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240628212523387.png)	对于逆变换，则有：
$$
x[k+\frac N4]=F_0[k] + j * W_N^k F_1[k] -1* W_N^{2k}F_2[k] -j* W_N^{3k} F_3[k]\\
x[k+\frac {2N}4] = F_0[k] - 1 * W_N^kF_1[k]+1*W_N^{2k}F_2[k] -1 * W_n^{3k} F_3[k]\\
x[k+\frac {3N}4] = F_0[k] - j * W_N^KF_1[k]-1*W_N^{2k} F_2[k] + j * w_N^{3k} F_3[k]
$$
​	频域采样的基-4 FFT算法类似，在此只给出其数据流向图，不做推导上的过多赘述。

<img src="https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240628212810210.png" alt="image-20240628212810210" style="zoom:40%;" />

​	从上图 可以看出，输出数据的顺序也被打乱了。我们把顺序的序号用二进制数列在表 1 中的左边，把乱序的序号用二进制数列在表 1 中的右边。从表中我们可以看出，乱序序号的二进制码可由顺序序号的二进制码以 2 比特为单位反转得到。

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
			<td>00 00</td>
			<td>00 00</td>
			<td>0</td>
		</tr>
		<tr>
			<td>1</td>
			<td>00 01</td>
			<td>01 00</td>
			<td>4</td>
		</tr>
		<tr>
			<td>2</td>
			<td>00 10</td>
			<td>10 00</td>
			<td>8</td>
		</tr>
		<tr>
			<td>3</td>
			<td>00 11</td>
			<td>11 00</td>
			<td>12</td>
		</tr>
		<tr>
			<td>4</td>
			<td>01 00</td>
			<td>00 01</td>
			<td>1</td>
		</tr>
		<tr>
			<td>5</td>
			<td>01 01</td>
			<td>01 01</td>
			<td>5</td>
		</tr>
		<tr>
			<td>6</td>
			<td>01 10</td>
			<td>10 01</td>
			<td>9</td>
		</tr>
		<tr>
			<td>7</td>
			<td>01 11</td>
			<td>11 01</td>
			<td>13</td>
		</tr>
	<tr>
			<td>8</td>
			<td>10 00</td>
			<td>00 10</td>
			<td>2</td>
		</tr>
        	<tr>
			<td>9</td>
			<td>10 01</td>
			<td>01 10</td>
			<td>6</td>
		</tr>
        	<tr>
			<td>10</td>
			<td>10 10</td>
			<td>10 10</td>
			<td>10</td>
		</tr>
        	<tr>
			<td>11</td>
			<td>10 11</td>
			<td>11 10</td>
			<td>14</td>
		</tr>
        	<tr>
			<td>12</td>
			<td>11 00</td>
			<td>00 11</td>
			<td>3</td>
		</tr>
        	<tr>
			<td>13</td>
			<td>11 01</td>
			<td>01 11</td>
			<td>7</td>
		</tr>
        	<tr>
			<td>14</td>
			<td>11 10</td>
			<td>10 11</td>
			<td>11</td>
		</tr>
        	<tr>
			<td>15</td>
			<td>11 11</td>
			<td>11 11</td>
			<td>15</td>
		</tr>
  	</tbody>
</table>

### 蝶形网络的优化

​	如果按照直接按照推导的公式进行计算，蝶形运算单元的伪代码将如下所示：

```python
for s = 1 to log4(n) # 树的层数
	size = 4^s; 	# 当前DFT的规模，同样也是下一个循环的跨度
    w1 = w2 = w3 = 1; wm = exp(-2j*PI/size); #定义旋转因子wm, w1, w2, w3分别是wm的指数。
	for k = 0 to n - 1 by 4^s
    	for q = 0 to size / 4
        	tmp0, tmp1, tmp2, tmp3 = 
            		a[k + q], a[k + q + size/4], a[k + q + 2*size/4],a[k + q + 3*size/4];
            a[k] = tmp0 + tmp1 + tmp2 + tmp3;
            a[k + size/4] = tmp0 - j * w1 * tmp1 - w2 * tmp2 + j * w3 * tmp3;
            a[k + 2*size/4] = tmp0 - w1 * tmp1 + w2 * tmp2 - w3 * tmp3;
            a[k + 3*size/4] = tmp0 + j * w1 * tmp1 - w2 * tmp2 - j * w3 * tmp3;
            w1 *= wm; w2 *= wm^2; w3 *= wm^3;
```

<img src="https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240628215545830.png" alt="image-20240628215545830" style="zoom:50%;" />
	仔细计算发现，一个蝶形运算包括12次复数加法、12次复数乘法。在不优化的情况下，该程序会比基-2的算法更慢。我们对一个蝶形运算单元进行如下优化：
$$
\begin{aligned}
P_0 &= F_0[k]\\
P_1 &= w_N^k * F_1[k]\\
P_2 &= w_N^{2k} * F_2[k]\\
P_3 &= w_N^{3k} * F_3[k]\\
\end{aligned}
$$
​	又令
$$
\begin{aligned}
U_0 = P_0 + P_2\\
U_1 = P_1 + P_3\\
U_2 = P_0 - P_2\\
U_3 = P_1 - P_3
\end{aligned}
$$
​	最后，根据公式
$$
\begin{aligned}
X[k]&= U_0 + U_1\\
X[k + \frac{N}{4}] &= U_2 - j * U3 \\
X[k+\frac{2N}{4}] &= U_0 - U_1 \\
X[k+\frac{3N}{4}] &= U_2 + j * U_3 \\
\end{aligned}
$$
​	预先计算旋转因子，并通过以上操作，我们将计算次数减少为：8次复数加法，3次复数乘法，能够显著提高程序运行效率。

### 速度瓶颈

​	显然，如果数据长度为$4^n$，基-4FFT回比基-2FFT有更好的效率。但由于在实际运算中需要用到零填充操作，一个$4^n+1$长度的序列会被扩展为$4^{n+1}$，造成了大量的时间浪费。因此，在很多数据集上，基-4 FFT算法反而不如基-2 FFT。

## Stockham FFT：原地自动整序算法

​	不管是时域采样（DIT）还是频域采样（DIF），库利-图基算法会导致得到的FFT序列顺序改变，或者需要提前通过比特翻转来改变序列的顺序。在比特翻转过程中，不连续的内存空间导致Cache的利用效率变低，这也是人们在努力研究去解决的问题。

​	Clive Temperton于1991年在《Self-Sorting In-Place Fast Fourier Transforms》一文中给出了适用于混合基数的原地FFT算法，不需要对输入或输出重新排序。通过将计算的中间结果存储到另一片区域，下次变换的时候再存储回来，如此往复，即可省去比特翻转的过程，这也被称为Stockham FFT。

<img src="C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629112543127.png" alt="image-20240629112543127" style="zoom:50%;" />

​	如上图所示，算法的核心难点在于如何对序列原地重排。在代码实现上，Stockham FFT 利用两块存储空间，在蝶形操作时将`x[q + s*(p + 0)], x[q + s*(p + m)]`的相互运算结果存放到`y[q + s*(2*p + 0)], y[q + s*(2*p + 1)]`中，从而合并了蝶形运算和重排序操作。

## 混合基算法

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



## 使用FFT快速卷积

### 卷积定义

两个n点时域信号，定义卷积运算如下：
$$
y[n]=\sum_{i=-\infty}^{\infty} x[i]\cdot h[n-i] = x[n]*h[n]
$$

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

## 针对硬件、指令集的优化

### FFTW

​	FFTW是由 Frigo 和 Johnson开发的一个快速、可扩展的FFT实现。在实际计算DFT之前，FFTW会预先执行一个辅助函数，通过一些列的试运行，确定在当前主机上分解FFT的最佳方式。FFTW能够针对硬件平台的缓存对程序进行自适应的调整，在任何规模上都有非常好的表现。

​	事实上，MATLAB自带的FFT也对FFTW进行了调用，并在这个基础上做了更多基于MATLAB特性的底层优化，将其强大的矩阵运算能力发挥到极致。

​	在 linux 环境下调用FFTW库完成卷积计算。编译方式详见源文件。关键代码如下：

```cpp
#include <fftw.h>  // 需要调用相应的头文件
...
void FFTW_Conv(double *a, int a_len, double *b, int b_len, double *Result)
{
    int n = a_len + b_len - 1;
    int N = nextPowerOfTwo(n);
    fftw_complex *A = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *B = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *C = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    double *a_padded = (double *)fftw_malloc(sizeof(double) * N);
    double *b_padded = (double *)fftw_malloc(sizeof(double) * N);
    double *c_padded = (double *)fftw_malloc(sizeof(double) * N);
    // 填充输入数据
    for (int i = 0; i < N; i++)
    {
        a_padded[i] = (i < a_len) ? a[i] : 0;
        b_padded[i] = (i < b_len) ? b[i] : 0;
    }
    // 创建 FFTW 计划
    fftw_plan pA = fftw_plan_dft_r2c_1d(N, a_padded, A, FFTW_ESTIMATE); // 实数到虚数的转换
    fftw_plan pB = fftw_plan_dft_r2c_1d(N, b_padded, B, FFTW_ESTIMATE); // real to complex 1 dimentional
    fftw_plan pC = fftw_plan_dft_c2r_1d(N, C, c_padded, FFTW_ESTIMATE); // complex to real 1 dimentional
    // 执行 FFT
    fftw_execute(pA);
    fftw_execute(pB);
    // 点乘
    for (int i = 0; i < N; i++)
    {
        C[i][0] = A[i][0] * B[i][0] - A[i][1] * B[i][1];
        C[i][1] = A[i][0] * B[i][1] + A[i][1] * B[i][0];
    }
    // 执行逆 FFT
    fftw_execute(pC);
    // 复制结果
    for (int i = 0; i < n; i++)
    {
        Result[i] = c_padded[i] / N;
    }
    // 清理内存
    fftw_destroy_plan(pA);
    fftw_destroy_plan(pB);
    fftw_destroy_plan(pC);
    fftw_free(A);
    fftw_free(B);
    fftw_free(C);
    fftw_free(a_padded);
    fftw_free(b_padded);
    fftw_free(c_padded);
}
```

### 异构计算

​	CUDA（Compute Unified Device Architecture）是由NVIDIA开发的一种并行计算平台和编程模型，允许开发者使用图形处理单元（GPU）来进行通用计算。在FFT算法中应用GPU强大的并行计算能力，对运算速度有着极大的提升。

## 总结

​	在众多FFT算法中，基2-库利图基算法有着非常稳定的运算效率。由于选择的基数小，在任意数据上都有不错的表现。

​	基4 C-T算法在以4为指数的数据上有着更加优越的性能，但由于基底变大，算法在不同数据上的灵活性较小，通常容易花费很多不必要的时间进行数据零填充，消耗更多算力。

​	能够原地整序的Stockham FFT优化了内存访问机制，在大数据上依然有非常不错的性能。

​	混合基算法结合以上两个算法的优点，对于不同的数据都有非常高的灵活性，因此能够有稳定的速度表现。

## 附录与测试结果

​	以下测试数据来源于由`gen_data.cpp`生成的随机序列，且使用同样的数据集。除了NTT以外，代码实现上均并不区分整数、浮点数浮点序列，因而运行速率大致相等，浮点序列的运行效率略低于整数序列。

### MATLAB测试

|    数据规模 （$n,m,N=n+m-1$）     | 数据类型 | 卷积耗时（s） |
| :-------------------------------: | :------: | :-----------: |
|             $2,3,N=4$             |   Int    |    0.0008     |
|           $16,17, N=32$           |   Int    |    0.0004     |
|        $1024,1024,N=2047$         |   Int    |    0.0006     |
|        $1031,1029,N=2059$         |   Int    |    0.0003     |
|   $2^{16} ,2^{16}, N=2^{17}-1$    |   Int    |    0.0041     |
|  $2^{16}+1,2^{16}+1,N=2^{17}+1$   |   Int    |    0.0088     |
|   $2^{20}, 2^{21},N=3*2^{20}-1$   |   Int    |    0.04159    |
| $2^{20}+1, 2^{20}+1, N=2^{21}+1 $ |   Int    |    0.1200     |
|           $N=2^{22}-2$            |   Int    |    0.2752     |
|            $N=2^{24}$             |   Int    |    0.6276     |

### FFTW测试

|    数据规模 （$n,m,N=n+m-1$）     | 数据类型 | 卷积耗时（s） |
| :-------------------------------: | :------: | :-----------: |
|             $2,3,N=4$             |   Int    |    0.0016     |
|           $16,17, N=32$           |   Int    |    0.0003     |
|        $1024,1024,N=2047$         |   Int    |    0.0028     |
|        $1031,1029,N=2059$         |   Int    |    0.0033     |
|   $2^{16} ,2^{16}, N=2^{17}-1$    |   Int    |    0.0152     |
|  $2^{16}+1,2^{16}+1,N=2^{17}+1$   |   Int    |    0.0219     |
|   $2^{20}, 2^{21},N=3*2^{20}-1$   |   Int    |    0.3482     |
| $2^{20}+1, 2^{20}+1, N=2^{21}+1 $ |   Int    |    0.3253     |
|           $N=2^{22}-2$            |   Int    |    0.8699     |
|            $N=2^{24}$             |   Int    |    1.9135     |
|   $2^{16} ,2^{16}, N=2^{17}-1$    |  Float   |    0.0119     |
|  $2^{16}+1,2^{16}+1,N=2^{17}+1$   |  Float   |    0.0210     |
|         $ N=3*2^{20}-1 $          |  Float   |    0.3282     |
|           $N=2^{22}-2$            |  Float   |    3.2287     |
|            $N=2^{24}$             |  Float   |    0.6339     |

![image-20240629162814952](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629162814952.png)

### radix-2 FFT 测试（整数）

|    数据规模 （$n,m,N=n+m-1$）     | 数据类型 | 卷积耗时（s） |
| :-------------------------------: | :------: | :-----------: |
|             $2,3,N=4$             |   Int    |    0.0000     |
|           $16,17, N=32$           |   Int    |    0.0000     |
|        $1024,1024,N=2047$         |   Int    |    0.0000     |
|        $1031,1029,N=2059$         |   Int    |    0.0010     |
|   $2^{16} ,2^{16}, N=2^{17}-1$    |   Int    |    0.0540     |
|  $2^{16}+1,2^{16}+1,N=2^{17}+1$   |   Int    |    0.1170     |
|   $2^{20}, 2^{21},N=3*2^{20}-1$   |   Int    |    2.5400     |
| $2^{20}+1, 2^{20}+1, N=2^{21}+1 $ |   Int    |    2.4830     |
|           $N=2^{22}-2$            |   Int    |    5.2260     |
|            $N=2^{24}$             |   Int    |    10.8230    |

![image-20240629170009190](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629170009190.png)

### radix-4 FFT 测试

|    数据规模 （$n,m,N=n+m-1$）     | 数据类型 | 卷积耗时（s） |
| :-------------------------------: | :------: | :-----------: |
|             $2,3,N=4$             |   Int    |    0.0000     |
|           $16,17, N=32$           |   Int    |    0.0000     |
|        $1024,1024,N=2047$         |   Int    |    0.0040     |
|        $1031,1029,N=2059$         |   Int    |    0.0040     |
|   $2^{16} ,2^{16}, N=2^{17}-1$    |   Int    |    0.3410     |
|  $2^{16}+1,2^{16}+1,N=2^{17}+1$   |   Int    |    0.4290     |
|   $2^{20}, 2^{21},N=3*2^{20}-1$   |   Int    |    8.4510     |
| $2^{20}+1, 2^{20}+1, N=2^{21}+1 $ |   Int    |    8.1500     |
|           $N=2^{22}-2$            |   Int    |    70.4100    |
|            $N=2^{24}$             |   Int    |    34.4580    |

![image-20240629164908425](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629164908425.png)

### Stockham FFT 测试（整数）

|    数据规模 （$n,m,N=n+m-1$）     | 数据类型 | 卷积耗时（s） |
| :-------------------------------: | :------: | :-----------: |
|             $2,3,N=4$             |   Int    |       0       |
|           $16,17, N=32$           |   Int    |       0       |
|        $1024,1024,N=2047$         |   Int    |    0.0010     |
|        $1031,1029,N=2059$         |   Int    |    0.0010     |
|   $2^{16} ,2^{16}, N=2^{17}-1$    |   Int    |    0.0530     |
|  $2^{16}+1,2^{16}+1,N=2^{17}+1$   |   Int    |    0.1280     |
|   $2^{20}, 2^{21},N=3*2^{20}-1$   |   Int    |    2.3680     |
| $2^{20}+1, 2^{20}+1, N=2^{21}+1 $ |   Int    |    2.5550     |
|           $N=2^{22}-2$            |   Int    |    5.2200     |
|            $N=2^{24}$             |   Int    |    10.6100    |

![image-20240629163739404](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629163739404.png)

## References



​	
