#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <ctime>

typedef unsigned int uint;

const double PI = 3.141592653589793238460;
const uint MAXN = 1e6 + 5;

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
void fft_4Radix(std::vector<Complex> &samples, const int n)
{
#ifdef _VERBOSE
    puts("FFT Timer Cost:");
#endif
    // bit reverse the input samples
    for (register int i = 0; i < n; i++)
        if (reversed[i] > i)
            std::swap(samples[i], samples[reversed[i]]);

    // size of the butterfly unit
    for (register int size = 4; size <= n; size <<= 2)
    {
        uint tic = clock();
        Complex w_m = Complex(0, -2 * PI / size).exp();

        // compute the tiggle factor of size for saving time
        // there are 3 * size / 4 elements need to be stored.
        std::vector<Complex> w1(size / 4);
        std::vector<Complex> w2(size / 4);
        std::vector<Complex> w3(size / 4);
        w1[0] = w2[0] = w3[0] = Complex(1, 0);
        for (register int j = 1; j < size / 4; j++)
        {
            w1[j] = w1[j - 1] * w_m;
            w2[j] = w1[j] * w1[j];
            w3[j] = w2[j] * w1[j];
        }

        for (register int m = 0; m < n; m += size)
        {
            for (register int k = 0; k < size / 4; k++) // one butterfly unit
            {
                // 3 Complex multiples, 8 Complex addition
                Complex W1 = w1[k]; // w1
                Complex W2 = w2[k]; // w1^2
                Complex W3 = w3[k]; // w1^3

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
#ifdef _VERBOSE
        uint toc = clock();
        std::cout << "butterfly Unit Size: " << size << "; Time Cost: " << (double)(toc - tic) / CLOCKS_PER_SEC << "s" << std::endl;
#endif
    }
}

void ifft_4Radix(std::vector<Complex> &samples, const int n)
{
#ifdef _VERBOSE
    puts("IFFT Timer Cost:");
#endif
    // bit reverse the input samples
    for (int i = 0; i < n; i++)
        if (reversed[i] > i)
            std::swap(samples[i], samples[reversed[i]]);

    // size of the butterfly unit
    for (int size = 4; size <= n; size <<= 2)
    {
        uint tic = clock();
        Complex w_m = Complex(0, 2 * PI / size).exp(); // Use positive sign for IFFT

        // compute the twiddle factor of size for saving time
        std::vector<Complex> w1(size / 4);
        std::vector<Complex> w2(size / 4);
        std::vector<Complex> w3(size / 4);
        w1[0] = w2[0] = w3[0] = Complex(1, 0);
        for (int j = 1; j < size / 4; j++)
        {
            w1[j] = w1[j - 1] * w_m;
            w2[j] = w1[j] * w1[j];
            w3[j] = w2[j] * w1[j];
        }

        for (int m = 0; m < n; m += size)
        {
            for (int k = 0; k < size / 4; k++) // one butterfly unit
            {
                // 3 Complex multiples, 8 Complex addition
                Complex W1 = w1[k]; // w1
                Complex W2 = w2[k]; // w1^2
                Complex W3 = w3[k]; // w1^3

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
#ifdef _VERBOSE
        uint toc = clock();
        std::cout << "ButterFly Unit Size: " << size << "; Time Cost: " << (double)(toc - tic) / CLOCKS_PER_SEC << "s" << std::endl;
#endif
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
// int samples[MAXN], samples2[MAXN];
std::vector<Complex> samples1, samples2;
std::vector<Complex> Results;
int main()
{
    int m, n;
    scanf("%d%d", &n, &m);
    // n++, m++;
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