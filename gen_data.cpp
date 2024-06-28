#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

// 需要生成数据，则取消第一行注释
// 需要生成标准输出，则取消第二行注释
// #define GENERATE_DATA
#define GENERATE_STDOUT

/// @brief 生成随机浮点数序列
/// @param size 序列长度
/// @param rng
/// @return
vector<double> generateRandomFloatSequence(size_t size, std::mt19937_64 &rng)
{
    vector<double> sequence(size);
    uniform_real_distribution<double> dist(-1000.0, 1000.0); // Generate numbers between -1000 and 1000
    for (auto &num : sequence)
    {
        num = dist(rng);
    }
    return sequence;
}
/// @brief 生成随机整数序列，保证每个数字在0-9之间
/// @param size 序列长度
/// @param rng 随机参数
/// @return 生成的序列
vector<double> generateRandomIntSequence(size_t size, std::mt19937_64 &rng)
{
    std::vector<double> sequence(size);
    for (auto &num : sequence)
    {
        num = rand() % 10;
    }
    return sequence;
}

/// @brief 将数据输出到文件内
/// @param filename 需要输出的文件名
/// @param seq1, seq2 分别为两个序列。
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

/// @brief 运行程序，读入测试数据，输出文件到，计算运行时间
/// @param exePath      可执行文件的地址
/// @param inputFile    输入数据的文件
/// @param outputFile   输出数据存放文件
/// @param duration     返回时长
void runTest(const string &exePath, const string &inputFile, const string &outputFile, chrono::duration<double> &duration)
{
    // 使用 cmd 命令行运行程序，输入inputFile重定向到可执行文件，输出重定向到outputFile
    string command = exePath + " < " + inputFile + " > " + outputFile;

    // 开始计时
    auto start = chrono::high_resolution_clock::now();

    system(command.c_str());

    // 停止计时
    auto end = chrono::high_resolution_clock::now();

    // 计算时长
    duration = end - start;
}

int main()
{
    int sizes[][2] = {{2, 3}, {16, 17}, {1024, 1024}, {1031, 1029}, {65536, 65536}, {65537, 65537}, {1 << 20, 1 << 21}, {(1 << 20) + 1, (1 << 20) + 1}, {(1 << 24), (1 << 24)}, {(1 << 22) - 1, (1 << 22) - 1}};
    int totalTest = 10;

    std::mt19937_64 rng(std::random_device{}()); // Random number generator

#ifdef GENERATE_DATA
    // 生成浮点数据
    for (int testCount = 0; testCount < totalTest; ++testCount)
    {
        int n = sizes[testCount][0], m = sizes[testCount][1];
        std::vector<double> seq1 = generateRandomFloatSequence(n, rng);
        std::vector<double> seq2 = generateRandomFloatSequence(m, rng);
        std::string filename = "./datas/double/data" + std::to_string(testCount) + ".in";
        writeToFile(filename, n, m, seq1, seq2);
        cout << "float data" << testCount << ".in generated." << endl;
    }

    // 生成整数数据
    for (int testCount = 0; testCount < totalTest; ++testCount)
    {
        int n = sizes[testCount][0], m = sizes[testCount][1];
        std::vector<double> seq1 = generateRandomIntSequence(n, rng);
        std::vector<double> seq2 = generateRandomIntSequence(m, rng);
        std::string filename = "./datas/integer/data" + std::to_string(testCount) + ".in";
        writeToFile(filename, n, m, seq1, seq2);
        cout << "integer data" << testCount << ".in generated." << endl;
    }
    std::cout << "test files Generated." << std::endl;
#endif

#ifdef GENERATE_STDOUT
    // 生成标准输出
    std::cout << "Generating standard output..." << std::endl;

    string exePath = ".\\build\\FFT_2radix_Int.exe";
    string inputFolder = ".\\datas\\integer";
    string outputFolder = ".\\datas\\integer";
    for (int i = 0; i < totalTest; ++i)
    {
        // to_string 函数将整数转换为字符串
        string inputFile = inputFolder + "\\data" + to_string(i) + ".in";       // data{i}.in
        string outputFile = outputFolder + "\\std_out" + to_string(i) + ".txt"; // std_out{i}.txt

        // 运行、测试时间。
        chrono::duration<double> duration;
        runTest(exePath, inputFile, outputFile, duration);
        cout << "Test " << i << ": "
             << "Time = " << duration.count() << "s, "
             << "standard integer answer generated." << endl;
    }

    exePath = ".\\build\\FFT_2radix_Double.exe";
    inputFolder = ".\\datas\\double";
    outputFolder = ".\\datas\\double";
    for (int i = 0; i < totalTest; ++i)
    {
        string inputFile = inputFolder + "\\data" + to_string(i) + ".in";       // data{i}.in
        string outputFile = outputFolder + "\\std_out" + to_string(i) + ".txt"; // std_out{i}.txt

        chrono::duration<double> duration;
        runTest(exePath, inputFile, outputFile, duration);
        cout << "Test " << i << ": "
             << "Time = " << duration.count() << "s, "
             << "standard double answer generated." << endl;
    }
#endif
    return 0;
}
