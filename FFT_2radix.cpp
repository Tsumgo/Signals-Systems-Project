
//
// using hand-made complex number class to implement Cooley-Tukey FFT algorithm
//
//
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

typedef unsigned int uint;

const double PI = 3.141592653589793238460;

uint reversed[1 << 24];

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
void fft(std::vector<Complex> &samples, const int n, const int levels)
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

// IFFT函数，使用与FFT相似的流程，仅改变旋转因子的符号，并在最后每个点除以n
void ifft(std::vector<Complex> &samples, const int n, const int levels)
{
    for (uint i = 0; i < n; i++)
    {
        if (reversed[i] > i)
        {
            std::swap(samples[i], samples[reversed[i]]);
        }
    }

    for (int size = 2; size <= n; size <<= 1)
    {
        Complex w_m = Complex(0, 2 * PI / size).exp(); // 注意：旋转因子符号变为正
        for (int m = 0; m < n; m += size)
        {
            Complex w = 1;
            for (int k = 0; k < size / 2; ++k)
            {
                Complex t = w * samples[m + k + size / 2];
                Complex u = samples[m + k];
                samples[m + k] = u + t;
                samples[m + k + size / 2] = u - t;
                w = w * w_m;
            }
        }
    }

    // 最后每个点除以n
    for (int i = 0; i < n; ++i)
    {
        samples[i] = samples[i] / n;
    }
}

// #define _DEBUG
int main()
{

// generate random serise of lenth N
#ifndef _DEBUG
    int N = 1 << 24;
    std::vector<Complex> samples = {};
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        samples.push_back(Complex(rand(), 0));
    }
#else
    int N = 16;
    // std::vector<Complex> samples = {{4, 0}, {3, 0}, {1, 0}, {0, 0}};
    // std::vector<Complex> samples = {{4, 0}, {3, 0}, {1, 0}, {0, 0}};
    std::vector<Complex> samples = {
        {0, 0}, {1, 0}, {3, 0}, {4, 0}, {4, 0}, {3, 0}, {1, 0}, {0, 0}, {4, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {1, 0}, {3, 0}, {2, 0}};
#endif

    // Record the start time, ignore the time of generating random series
    uint tic = clock();

    // Make sure the number of samples is a power of two
    int n = nextPowerOfTwo(samples.size());
    samples.resize(n); // pads with zeroes if necessary

    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n));

    // get reversed index based on the levels. Calculate the array reversed[].
    get_reversed(levels);

    // Performing FFT
    fft(samples, n, levels);

    // output the results
#ifdef _DEBUG
    std::cout << "FFT Output:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        samples[i].print();
    }
#endif

    uint toc = clock();
    std::cout << "Time Cost:" << (double)(toc - tic) / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}