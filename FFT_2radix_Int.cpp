#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <ctime>
// 稍微快一点
typedef unsigned int uint;

const uint MAXN = (1 << 24) + 5;

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

// The FFT function
// 'samples' is a reference to the vector containing the time-domain sample values
// 'n' is the number of points in FFT, must be a power of two
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

    // Cooley-Tukey iterative FFT algorithm
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
    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n));
    // get reversed index based on the levels. Calculate the array reversed[].
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
    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n));
    // get reversed index based on the levels. Calculate the array reversed[].
    get_reversed(levels);
    // Resize A and B to n, filling with zeros
    A.resize(n);
    B.resize(n);
    Results.resize(n);

    // Perform FFT on both A and B
    fft(A, n);
    fft(B, n);

    // Point-wise multiply the FFT results
    for (int i = 0; i < n; i++)
    {
        Results[i] = A[i] * B[i];
    }

    // Perform IFFT on the result
    ifft(Results, n);

    // Optionally, resize Results to the original convolution size (A.size() + B.size() - 1)
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
    scanf("%d%d", &n, &m);
    samples1.resize(n);
    samples2.resize(m);
    for (int i = 0; i < n; i++)
        samples1[i] = Complex(read(), 0);
    for (int i = 0; i < m; i++)
        samples2[i] = Complex(read(), 0);

    fftConv(samples1, samples2, Results);
    // output the results

    for (int i = 0; i < Results.size(); i++)
        printf("%d ", (int)(Results[i].real + 0.5));

    return 0;
}