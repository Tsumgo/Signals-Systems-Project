## FFTW环境

​	下文简述如何在linux环境下安装FFTW库，并使用第三方库编译C语言代码。

1. 更新 apt 配置，下载编译器gcc、编译工具 cmake。

```bash
sudo apt upgrade
sudo apt install gcc
sudo apt install cmkae
```

2. 访问官网，下载第三方库源文件。
2. 编译安装FFTW库

```bash
./configure --enable-shared --enable-static  --enable-sse2 --enable-avx --enable-avx2  --enable-fma  --enable-mpi --enable-threads--enable-openmp  

make  
sudo make install
```

​	使用configure命令配置时，增加了FFTW提供的对特定CPU指令集的优化标志。	

​	最后一步 `make install`加上 sudo 前缀，确保该命令有足够的权限。

3. 在项目根目录下，新建CMakeLists.txt文件，内容如下：

   ```cmake
   cmake_minimum_required(VERSION 3.16.3)
   
   # 定义项目名称
   project(FFTWTest)
   
   find_package(FFTW3)
   # 此处FFTWTest.c改成自己的源文件名。FFTWTest表示生成的可执行文件
   add_executable(FFTWTest FFTWTest.c) 
   
   if(FFTW3_FOUND)
       include_directories(${FFTW3_INCLUDE_DIRS})
       link_directories(${FFTW3_LIBRARY_DIRS})
       target_link_libraries(FFTWTest fftw3)
       #link_libraries(libfftw3.so)
   else(FFTW3_FOUND)
       message(FATAL_ERROR "FFTW3 library not found")
   endif(FFTW3_FOUND)
   
   ```

4. 撰写源文件代码。这里提供笔者的实例代码：

   ```c
   
   ```
   
5. 在项目目录下新建`build`目录，用于构建项目。进入`build`，编译项目。

   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

6. 如果需要重新安装FFTW库，执行以下命令，重新编译

   ```bash
   make distclean
   ```


## Windows Cuda C 环境配置

1. 下载Microsoft Visual Studio

   ​	Windows环境必要项。NVIDIA在VS上做了完善的软件支持。

2. 下载CUDA developing tool kits

   ​	需要根据使用设备的版本下载。

   - 查看CUDA版本：在命令行中输入`nvidia-smi` 

     ![image-20240629142830115](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240629142830115.png)

   - 在官网下载对应的开发套件

3. 打开VS，新建空项目，创建一个`hello.cu`文件。

4. 打开i项目后，找到工具–>选项–>文本编辑器–>文件拓展名, 新增扩展名 `.cu` 并将编辑器设置为：Microsoft Visual C++。

   ![image-20240629143700542](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240629143700542.png)

5. 工具–>选项–>项目和解决方案–>VC++项目设置，添加要包括的扩展名`.cu`

   ![image-20240629143725164](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240629143725164.png)

4. 右键打开的项目 --> 生成依赖项–>生成自定义–>勾选CUDA  12.5 （对应自己的版本号）。

<img src="C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629142342838.png" alt="image-20240629142342838" style="zoom:50%;" />

![image-20240629143539367](https://tsumgo2003-1323474554.cos.ap-shanghai.myqcloud.com/img/image-20240629143539367.png)

5. 右键需要编译的`.cu`文件，点击属性，将文件属性设置为CUDA C/C++

![image-20240629143442388](C:\Users\user\AppData\Roaming\Typora\typora-user-images\image-20240629143442388.png)



6. 键入示例代码，即可编译运行。

   ```cpp
   #include "stdio.h"
   #include "cuda_runtime.h"
   #include "device_launch_parameters.h"
   /* 修饰符__global__表明这个函数是将会从CPU中调用，在GPU中进行执行。 并借此函数来启动内核函数。*/
   __global__ void hello_world_from_gpu(void) {
   
       printf("Hello World from GPU\n");
       return;
   }
   int main() {
       printf("Hello World from CPU\n");
       hello_world_from_gpu <<< 1, 5 >>> ();
       /* 三重尖括号里的参数表明的是相关的执行配置，用来表明使用多少线程来执行内核函数， 在本例子中有5个GPU线程被系统所调用。 */
       cudaDeviceReset();
       /* 执行完成后调用cudaDeviceReset()函数释放和清空与当前进程运行相关的资源。 */             
       return 0;
   }
   ```




注意：CUDA Toolkit 自 10.1 版本开始，不再提供 `helper_cuda.h` 等辅助头文件和工具函数库。这些文件以前是在 CUDA Samples 中提供的，但现在需要从 CUDA Samples 的 GitHub 仓库下载。
