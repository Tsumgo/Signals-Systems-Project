#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <ctime>
// 稍微快一点
typedef unsigned int uint;

const uint MAXN = (1 << 24) + 5;

// 自定义Complex计算。为了减少内存占用，不使用std::complex
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

// 用于存放比特翻转后的下标，在卷积中，最多用到 MAXN*4 个下标
uint reversed[MAXN << 2];

/// @brief 计算大于等于n的最小的2的幂次方
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

/// @brief 基-2 FFT算法
/// @param samples 原始序列
/// @param n 序列长度，保证为2的指数
void fft(std::vector<Complex> &samples, const uint n)
{
    const double PI = 3.141592653589793238460;
    // Bit-reverse the input samples array based on the levels
    for (uint i = 0; i < n; i++)
    {
        if (reversed[i] > i)
        {
            std::swap(samples[i], samples[reversed[i]]);
        }
    }

    // C-T 递推算法
    for (int size = 2; size <= n; size <<= 1) // the size of butterfly unit.
    {
        Complex w_m = Complex(0, -2 * PI / size).exp(); // twiddle factor (w)
        for (int m = 0; m < n; m += size)
        {
            Complex w = 1;
            for (int k = 0; k < size / 2; ++k)
            {
                // FFT butterfly
                Complex t = w * samples[m + k + size / 2];
                Complex u = samples[m + k];
                samples[m + k] = u + t;
                samples[m + k + size / 2] = u - t;
                w = w * w_m;
            }
        }
    }
}

/// @brief  基2 IFFT算法
/// @param samples 原始序列
/// @param n  序列长度，保证为2的指数
void ifft(std::vector<Complex> &samples, const int n)
{
    const double PI = 3.141592653589793238460;
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
        Complex w_m = Complex(0, 2 * PI / size).exp(); // twiddle factor (w), positive rotation factor
        // 循环n/size次，每次跨越size
        for (int m = 0; m < n; m += size)
        {
            Complex w = 1;
            // 循环size/2次
            for (int k = 0; k < size / 2; ++k)
            {
                // FFT butterfly
                Complex t = w * samples[m + k + size / 2];
                Complex u = samples[m + k];
                samples[m + k] = u + t;
                samples[m + k + size / 2] = u - t;
                w = w * w_m;
            }
        }
    }

    for (int i = 0; i < n; i++)
        samples[i] = samples[i] / n;
}
/// @brief 使用两次FFT来计算卷积
/// @param A
/// @param B
/// @param Results
void fftConv(std::vector<Complex> &A, std::vector<Complex> &B, std::vector<Complex> &Results)
{
    // 实际卷积长度
    int len = A.size() + B.size() - 1;
    // 运算需要的长度
    int n = nextPowerOfTwo(len);
    // 计算FFT层数
    int levels = uint(log2(n));
    // 计算比特翻转
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
/// @param A
/// @param B
/// @param Results
void fftConv_3times(std::vector<Complex> &A, std::vector<Complex> &B, std::vector<Complex> &Results)
{
    // 实际卷积长度
    int len = A.size() + B.size() - 1;
    // 运算需要的长度
    int n = nextPowerOfTwo(len);
    int levels = uint(log2(n));
    // 计算比特翻转
    get_reversed(levels);
    // 零填充
    A.resize(n);
    B.resize(n);
    Results.resize(n);

    // 计算 FFT
    fft(A, n);
    fft(B, n);

    // A * B
    for (int i = 0; i < n; i++)
    {
        Results[i] = A[i] * B[i];
    }

    // 计算IFFT
    ifft(Results, n);
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
    int m, n;
    int dataType = 1; // 1 测试整数数据；0测试浮点数数据
    int TestCount = 10;
    puts(dataType ? "Test for Integer Input" : "Test for Float Input");
    for (int i = 0; i < TestCount; i++)
    {
        // 输入文件在data文件夹下
        std::string inputFile = (dataType ? "..\\datas\\integer\\data" : "..\\datas\\double\\data") + std::to_string(i) + ".in";
        FILE *fp = freopen(inputFile.c_str(), "r", stdin);
        if (fp == NULL)
        {
            puts("Open File Failed");
            return 0;
        }

        scanf("%d%d", &n, &m);
        samples1.resize(n);
        samples2.resize(m);
        // for (int i = 0; i < n; i++)
        //     scanf("%lf", &samples1[i].real);
        // for (int i = 0; i < m; i++)
        //     scanf("%lf", &samples2[i].real);
        for (int i = 0; i < n; i++)
            samples1[i] = Complex(read(), 0);
        for (int i = 0; i < m; i++)
            samples2[i] = Complex(read(), 0);

        int tic = clock();
        fftConv(samples1, samples2, Results);
        int toc = clock();
        printf("Test :%d,(n=%d, m=%d) Time Cost:%.4lf\n", i, n, m, (double)(toc - tic) / CLOCKS_PER_SEC);

        // 输出数据。如有需要，取消下方注释。
        // for (int i = 0; i < Results.size(); i++)
        //     printf("%d ", (int)(Results[i].real + 0.5));
        fclose(stdin);
    }

    return 0;
}