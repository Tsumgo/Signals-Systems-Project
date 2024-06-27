#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib>
using namespace std;

/// @brief 运行程序，读入测试数据，输出文件到，计算运行时间
/// @param exePath      可执行文件的地址
/// @param inputFile    输入数据的文件
/// @param outputFile   输出数据存放文件
/// @param duration     返回时长
void runTest(const string &exePath, const string &inputFile, const string &outputFile, chrono::duration<double> &duration)
{
    // 使用powershell命令行运行程序，输入inputFile重定向到可执行文件，输出重定向到outputFile
    string command = "get-content " + inputFile + " | " + exePath + " > " + outputFile;

    // 开始计时
    auto start = chrono::high_resolution_clock::now();

    system(command.c_str());

    // 停止计时
    auto end = chrono::high_resolution_clock::now();

    // 计算时长
    duration = end - start;
}

bool compareFiles(const string &file1, const string &file2)
{
    // 生成bash命令。fc用于比较文件一致性，一致输出0，否则输出1
    string command = "fc " + file1 + " " + file2;

    if (system(command.c_str()))
    {
        return false;
    }
    return 1;
}

int main()
{
    // 指定运行目录、输入输出目录、标准输出文件
    std::string exePath = "./build/FFT_2radix_luogu.exe";
    std::string inputFolder = "./datas";
    std::string outputFolder = "./datas";

    // 指定测试集个数。
    int numTests = 10;

    // 遍历测试集
    for (int i = 0; i < numTests; ++i)
    {
        // to_string 函数将整数转换为字符串
        string inputFile = inputFolder + "/data" + to_string(i) + ".in";
        string outputFile = outputFolder + "/std_out" + to_string(i) + ".out";

        // 运行、测试时间。
        chrono::duration<double> duration;
        runTest(exePath, inputFile, outputFile, duration);

        // 比较输入、输出异同
        // bool isCorrect = compareFiles(outputFile, standardOutputFile);

        // cout << "Test " << i << ": "
        //      << "Time = " << duration.count() << "s, "
        //      << (isCorrect ? "Correct" : "Incorrect") << std::endl;
    }

    return 0;
}
