#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <ctime>

typedef unsigned int uint;

const double PI = 3.141592653589793238460;
const uint MAXN = (1 << 24) + 1;

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

// 用于存放比特翻转后的下标，在卷积中，最多用到 MAXN*16 个下标
uint reversed[MAXN << 4];

int getBestN(int n)
{
    return pow(4, ceil(log2(n) / 2));
}

// Utility function to reverse the bits of a given index 'i'
// 'bit' is the number of bits needed to represent the indices
void get_reversed_by_2_bits(int bit)
{
    uint size = 1 << bit;
    for (register uint i = 0; i < size; i++)
    {
        reversed[i] = (reversed[i >> 2] >> 2) | ((i & 3) << (bit - 2));
    }
}

/// @brief 计算n点的DFT。其中n保证是4的指数
/// @param samples 原始序列
/// @param n 序列长度。
void fft_4Radix(std::vector<Complex> &samples, const int n)
{
    // w_m是以n为基底的单位根，w_m = exp(-2 * PI * j / n)
    Complex w_m = Complex(0, -2 * PI / n).exp();
    // W是存放n/4个单位根的数组，为了内存访问的连续性，用W[3 * i]表示w_m^{i}
    // W[3 * i + 1]表示w_m^{2i}，W[3 * i + 2]表示w_m^{3i}
    std::vector<Complex> W(3 * n / 4);
    W[0] = W[1] = W[2] = Complex(1, 0);
    for (register int i = 1; i < n / 4; i++)
    {
        W[3 * i] = W[3 * (i - 1)] * w_m;        // wm^{i}
        W[3 * i + 1] = W[3 * i] * W[3 * i];     // wm^{2i}
        W[3 * i + 2] = W[3 * i + 1] * W[3 * i]; // wm^{3i}
    }

    // bit reverse the input samples
    for (register int i = 0; i < n; i++)
        if (reversed[i] > i)
            std::swap(samples[i], samples[reversed[i]]);

    // size of the butterfly unit
    for (register int size = 4; size <= n; size <<= 2)
    {
        uint tic = clock();
        for (register int m = 0; m < n; m += size)
        {
            for (register int k = 0; k < size / 4; k++) // one butterfly unit, use wm^{-2 PI *j / size}
            {
                // 3 Complex multiples, 8 Complex addition
                int index = n / size * k;      // 该蝶形单元使用 w_{size}^k 作为基本单位，换算到以 w_{n} 作为基底
                Complex W1 = W[3 * index];     // wm^{k}
                Complex W2 = W[3 * index + 1]; // wm^{2k}
                Complex W3 = W[3 * index + 2]; // wm^{3k}

                Complex P0 = samples[m + k];
                Complex P1 = W1 * samples[m + k + size / 4];
                Complex P2 = W2 * samples[m + k + 2 * size / 4];
                Complex P3 = W3 * samples[m + k + 3 * size / 4];

                Complex U0 = P0 + P2;
                Complex U1 = P1 + P3;
                Complex U2 = P0 - P2;
                Complex U3 = P1 - P3;

                samples[m + k] = U0 + U1;                                        // P0 + P1 + P2 + P3
                samples[m + k + size / 4] = U2 - Complex(-U3.imag, U3.real);     // P0 + jP1 -P2 - jP3
                samples[m + k + 2 * size / 4] = U0 - U1;                         // P0 - P1 + P2 - P3
                samples[m + k + 3 * size / 4] = U2 + Complex(-U3.imag, U3.real); // P0 - jP1 - P2 + jP3
            }
        }
    }
}

void ifft_4Radix(std::vector<Complex> &samples, const int n)
{
    std::vector<Complex> W(3 * n / 4);
    // 使用指数为正的旋转因子。
    Complex w_m = Complex(0, 2 * PI / n).exp();

    W[0] = W[1] = W[2] = Complex(1, 0);
    for (register int i = 1; i < n / 4; i++)
    {
        W[3 * i] = W[3 * (i - 1)] * w_m;        // wm^{i}
        W[3 * i + 1] = W[3 * i] * W[3 * i];     // wm^{2i}
        W[3 * i + 2] = W[3 * i + 1] * W[3 * i]; // wm^{3i}
    }

    // bit reverse the input samples
    for (int i = 0; i < n; i++)
        if (reversed[i] > i)
            std::swap(samples[i], samples[reversed[i]]);

    // size of the butterfly unit
    for (int size = 4; size <= n; size <<= 2)
    {
        uint tic = clock();

        for (int m = 0; m < n; m += size)
        {
            for (int k = 0; k < size / 4; k++) // one butterfly unit
            {
                // 3 Complex multiples, 8 Complex addition
                int index = n / size * k;      // 该蝶形单元使用 w_{size}^k 作为基本单位，换算到以 w_{n} 作为基底
                Complex W1 = W[3 * index];     // wm^{k}
                Complex W2 = W[3 * index + 1]; // wm^{2k}
                Complex W3 = W[3 * index + 2]; // wm^{3k}

                Complex P0 = samples[m + k];
                Complex P1 = W1 * samples[m + k + size / 4];
                Complex P2 = W2 * samples[m + k + 2 * size / 4];
                Complex P3 = W3 * samples[m + k + 3 * size / 4];

                Complex U0 = P0 + P2;
                Complex U1 = P1 + P3;
                Complex U2 = P0 - P2;
                Complex U3 = P1 - P3;

                samples[m + k] = U0 + U1;                                        // P0 + P1 + P2 + P3
                samples[m + k + size / 4] = U2 + Complex(-U3.imag, U3.real);     // P0 + jP1 -P2 - jP3
                samples[m + k + 2 * size / 4] = U0 - U1;                         // P0 - P1 + P2 - P3
                samples[m + k + 3 * size / 4] = U2 - Complex(-U3.imag, U3.real); // P0 - jP1 - P2 + jP3
            }
        }
    }

    // Normalize the result
    for (register int i = 0; i < n; i++)
        samples[i] = samples[i] / n;
}

void fftConv(std::vector<Complex> &A, std::vector<Complex> &B, std::vector<Complex> &Results)
{
    // 实际卷积长度
    int len = A.size() + B.size() - 1;
    // 运算需要的长度
    int n = getBestN(len);
    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n));
    // get reversed index based on the levels. Calculate the array reversed[].
    get_reversed_by_2_bits(levels);

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
    fft_4Radix(A, n);
    for (register int i = 0; i < n; i++)
    {
        Results[i] = A[i] * A[i];
    }
    ifft_4Radix(Results, n);
    for (register int i = 0; i < n; i++)
    {
        Results[i] = Complex(Results[i].imag / 2, 0);
    }
    Results.resize(len);
}
std::vector<Complex> samples1, samples2;
std::vector<Complex> Results;
int main()
{
    int m, n;
    scanf("%d%d", &n, &m);
    n++, m++;
    samples1.resize(n);
    samples2.resize(m);
    for (int i = 0; i < n; i++)
        scanf("%lf", &samples1[i].real);
    for (int i = 0; i < m; i++)
        scanf("%lf", &samples2[i].real);

    fftConv(samples1, samples2, Results);
    for (int i = 0; i < Results.size(); i++)
        printf("%d ", (int)(Results[i].real + 0.5));
    return 0;
}