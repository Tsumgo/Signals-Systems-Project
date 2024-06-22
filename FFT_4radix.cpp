#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <ctime>

// #define _DEBUG   // to show the input and output of small size FFT
#define _VERBOSE // to show the time cost of each butterfly unit

typedef unsigned int uint;

const double PI = 3.141592653589793238460;

class Complex
{
public:
    double real, imag;

    // 构造函数
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Complex adder
    Complex operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    // Complex extract
    Complex operator-(const Complex &other) const
    {
        return Complex(real - other.real, imag - other.imag);
    }

    // Complex multiply
    Complex operator*(const Complex &other) const
    {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    // Complex divide by an integer
    Complex operator/(const int &other) const
    {
        return Complex(real / other, imag / other);
    }

    // calculate the exponential of a complex.
    Complex exp() const
    {
        double e = std::exp(real);
        return Complex(e * std::cos(imag), e * std::sin(imag));
    }

    // print a complex
    void print() const
    {
        if (imag >= 0)
            std::cout << real << " + " << imag << "i" << std::endl;
        else
            std::cout << real << " - " << -imag << "i" << std::endl;
    }
};

uint reversed[1 << 24];

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
                // Complex a = samples[m + k];
                // Complex b = W1 * samples[m + k + 1 * size / 4];
                // Complex c = W2 * samples[m + k + 2 * size / 4];
                // Complex d = W3 * samples[m + k + 3 * size / 4];

                // samples[m + k] = a + b + c + d;
                // // samples[m + k + size / 4] = a - J * b - c + J * d;
                // samples[m + k + size / 4] = a - Complex(-b.imag, b.real) - c + Complex(-d.imag, d.real);
                // samples[m + k + 2 * size / 4] = a - b + c - d;
                // // samples[m + k + 3 * size / 4] = a + J * b - c - J * d;
                // samples[m + k + 3 * size / 4] = a + Complex(-b.imag, b.real) - c - Complex(-d.imag, d.real);
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

// bit=2n
void get_reversed_by_2_bits(int bit)
{
    uint size = 1 << bit;
    for (register uint i = 0; i < size; i++)
    {
        reversed[i] = (reversed[i >> 2] >> 2) | ((i & 3) << (bit - 2));
    }
}

// Utility function to calculate the next power of four greater than or equal to 'n'
int getBestN(int n)
{
    return pow(4, ceil(log2(n) / 2));
}

int main()
{
// generate random serise of lenth N
#ifndef _DEBUG
    int N = (1 << 20) + 10;
    std::vector<Complex> samples = {};
    std::cout << N << std::endl;
    // srand(time(0));
    for (int i = 0; i < N; i++)
    {
        samples.push_back(Complex(rand(), 0));
    }
#else
    int N = 16;
    std::vector<Complex> samples = {
        {0, 0}, {1, 0}, {3, 0}, {4, 0}, {4, 0}, {3, 0}, {1, 0}, {0, 0}, {4, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {1, 0}, {3, 0}, {2, 0}};
    // std::vector<Complex> samples = {{4, 0}, {3, 0}, {1, 0}, {0, 0}};
    // std::vector<Complex> samples = {{0, 0}, {1, 0}, {3, 0}, {4, 0}};
    std::cout << "Input Samples:" << std::endl;
    for (int i = 0; i < N; i++)
        samples[i].print();
#endif

    uint tic = clock(), toc;
    // Make sure the number of samples is a power of two
    int n = getBestN(samples.size()); // C vector can pad with the array zeros automatically.
    samples.resize(n);                // pads with zeroes if necessary

    // Calculate the number of levels in the FFT, n = 2^levels
    int levels = uint(log2(n) / 2);

    // get reversed index based on the levels
    get_reversed_by_2_bits(levels * 2);

    toc = clock();
    std::cout << "Time Cost:" << (double)(toc - tic) / CLOCKS_PER_SEC << "s" << std::endl;

    // Performing FFT
    fft_4Radix(samples, n);

    toc = clock();
    std::cout << "Time Cost:" << (double)(toc - tic) / CLOCKS_PER_SEC << "s" << std::endl;

    // output the results
#ifdef _DEBUG
    std::cout << "FFT Output:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        samples[i].print();
    }
#endif

    // perform IFFT
    ifft_4Radix(samples, n);

    toc = clock();
    std::cout << "Time Cost:" << (double)(toc - tic) / CLOCKS_PER_SEC << "s" << std::endl;

    // output the results
#ifdef _DEBUG
    std::cout << "IFFT Output:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        samples[i].print();
    }
#endif
    return 0;
}