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
    n++, m++;

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
