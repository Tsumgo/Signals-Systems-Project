#include <complex>
#include <iostream>
#include <vector>
#include <cmath>

typedef unsigned int uint;

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
    // 计算复数的共轭
    Complex conj() const
    {
        return Complex(real, -imag);
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

/// @brief 计算大于等于n的最小的2的幂次方
int nextPowerOfTwo(int n)
{
    return pow(2, ceil(log2(n)));
}

void fft0(int n, int s, bool eo, std::vector<Complex> &x, std::vector<Complex> &y)
// n  : sequence length
// s  : stride
// eo : x is output if eo == 0, y is output if eo == 1
// x  : input sequence(or output sequence if eo == 0)
// y  : work area(or output sequence if eo == 1)
{
    const int m = n / 2;
    const double theta0 = 2 * M_PI / n;
    // 角度

    if (n == 1)
    {
        if (eo)
            for (int q = 0; q < s; q++)
                y[q] = x[q];
    }
    else
    {
        for (int p = 0; p < m; p++)
        {
            const Complex wp = Complex(cos(p * theta0), -sin(p * theta0));
            for (int q = 0; q < s; q++)
            {
                const Complex a = x[q + s * (p + 0)];
                const Complex b = x[q + s * (p + m)];
                y[q + s * (2 * p + 0)] = a + b;
                y[q + s * (2 * p + 1)] = (a - b) * wp;
            }
        }
        fft0(n / 2, 2 * s, !eo, y, x);
    }
}

void fft(int n, std::vector<Complex> &x) // Fourier transform
// n : sequence length
// x : input/output sequence
{
    // Complex *y = new Complex[n];
    std::vector<Complex> y(n); // 自动销毁内存
    fft0(n, 1, 0, x, y);
    // delete[] y;
    for (int k = 0; k < n; k++)
        x[k] = x[k] / n;
}

void ifft(int n, std::vector<Complex> &x) // Inverse Fourier transform
// n : sequence length
// x : input/output sequence
{
    for (int p = 0; p < n; p++)
        x[p] = x[p].conj();
    // Complex *y = new Complex[n];
    std::vector<Complex> y(n); // 自动销毁内存
    fft0(n, 1, 0, x, y);
    // delete[] y;
    for (int k = 0; k < n; k++)
        x[k] = x[k].conj();
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
    fft(n, A);
    for (register int i = 0; i < n; i++)
    {
        Results[i] = A[i] * A[i];
    }
    ifft(n, Results);
    for (register int i = 0; i < n; i++)
    {
        Results[i] = Complex(Results[i].imag / 2, 0);
    }
    Results.resize(len);
}
