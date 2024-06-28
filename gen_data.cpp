#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

/// @brief 生成随机浮点数序列
/// @param size 序列长度
/// @param rng
/// @return
std::vector<double> generateRandomFloatSequence(size_t size, std::mt19937_64 &rng)
{
    std::vector<double> sequence(size);
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0); // Generate numbers between -1000 and 1000
    for (auto &num : sequence)
    {
        num = dist(rng);
    }
    return sequence;
}
/// @brief 生成随机整数序列
/// @param size 序列长度
/// @param rng 随机参数
/// @return 生成的序列
std::vector<double> generateRandomIntSequence(size_t size, std::mt19937_64 &rng)
{
    std::vector<double> sequence(size);
    for (auto &num : sequence)
    {
        num = rand();
    }
    return sequence;
}

// Function to write the sequence to a file
void writeToFile(const std::string &filename, size_t n, size_t m, const std::vector<double> &seq1, const std::vector<double> &seq2)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error creating file: " << filename << std::endl;
        return;
    }
    outFile << n << " " << m << std::endl;
    for (const auto &num : seq1)
    {
        outFile << num << " ";
    }
    outFile << std::endl;
    for (const auto &num : seq2)
    {
        outFile << num << " ";
    }
    outFile << std::endl;
    outFile.close();
}

int main()
{
    int sizes[][2] = {{2, 3}, {16, 17}, {1024, 1024}, {1031, 1029}, {65536, 65536}, {65537, 65537}, {1 << 20, 1 << 21}, {(1 << 20) + 1, (1 << 20) + 1}, {(1 << 24), (1 << 24)}, {(1 << 22) - 1, (1 << 22) - 1}};
    int totalTest = 10;

    std::mt19937_64 rng(std::random_device{}()); // Random number generator

    // 生成浮点数据
    for (int testCount = 0; testCount < totalTest; ++testCount)
    {
        int n = sizes[testCount][0], m = sizes[testCount][1];
        std::vector<double> seq1 = generateRandomFloatSequence(n, rng);
        std::vector<double> seq2 = generateRandomFloatSequence(m, rng);
        std::string filename = "./datas/double/data" + std::to_string(testCount) + ".in";
        writeToFile(filename, n, m, seq1, seq2);
    }

    // 生成整数数据
    for (int testCount = 0; testCount < totalTest; ++testCount)
    {
        int n = sizes[testCount][0], m = sizes[testCount][1];
        std::vector<double> seq1 = generateRandomIntSequence(n, rng);
        std::vector<double> seq2 = generateRandomIntSequence(m, rng);
        std::string filename = "./datas/integer/data" + std::to_string(testCount) + ".in";
        writeToFile(filename, n, m, seq1, seq2);
    }

    std::cout << "test files Generated." << std::endl;
    return 0;
}
