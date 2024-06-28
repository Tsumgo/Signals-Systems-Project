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
    // 指定运行目录、输入输出目录、标准输出文件
    // 根据数据类型的不同，分别存放于double、integer文件夹下。
    string exePath = ".\\build\\FFT_2radix_DIF.exe";
    string inputFolder = ".\\datas\\integer";
    string outputFolder = ".\\datas\\integer";

    // 指定测试集个数。
    int numTests = 10;

    // 测试部分
    cout << "Running tests " << exePath << endl;
    for (int i = 0; i < numTests; ++i)
    {
        // to_string 函数将整数转换为字符串
        string inputFile = inputFolder + "\\data" + to_string(i) + ".in";               // data{i}.in
        string outputFile = outputFolder + "\\output.txt";                              // output.txt
        string standardOutputFile = outputFolder + "\\std_out" + to_string(i) + ".txt"; // std_out{i}.txt

        // 运行、测试时间。
        chrono::duration<double> duration;
        runTest(exePath, inputFile, outputFile, duration);

        // // 比较输入、输出异同
        // bool isCorrect = true;
        // string command = "echo | fc " + outputFile + " " + standardOutputFile;
        // if (system(command.c_str()))
        // {
        //     isCorrect = false;
        // }

        cout << "Test " << i << ": "
             << "Time = " << duration.count() << "s, " << endl;
    }

    system("pause");
    return 0;
}
