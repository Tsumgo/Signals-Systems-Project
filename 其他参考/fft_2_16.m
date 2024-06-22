% 16点基2-FFT算法
% 定义输入、初始化输出及蝶形复合结果
N = 16;
x = [3 2 1 0 1 0 6 3 2 7 0 0 0 0 0 0];

% 在一级蝶形复合之前，先按照顺序将输入序列分组
group1 = [x(1) x(9)];group2 = [x(5) x(13)];group3 = [x(3) x(11)];group4 = [x(7) x(15)];
group5 = [x(2) x(10)];group6 = [x(6) x(14)];group7 = [x(4) x(12)];group8 = [x(8) x(16)];
matrix = reshape([group1; group2; group3; group4; group5; group6; group7; group8], 8, 2);

% 一级蝶形复合
W0 = [1 1;1 -1]; % 定义旋转因子
X1 = W0 * matrix.'; % 定义存储一级蝶形复合结果的2×8矩阵

% 二级蝶形复合
W = exp(-1i*2*pi/16); % 定义W
X2 = zeros(4,4);
% 通过循环运算后为X2赋值
for i = 1:2
    for j = 1:4
        matrix1 = W0*[X1(i,2*j-1) W^(4*i-4)*X1(i,2*j)].';
        X2(i,j) = matrix1(1);
        X2(i+2,j) = matrix1(2);
    end
end

% 三级蝶形复合
X3 = zeros(8,2);
% 通过循环运算后为X3赋值
for i = 1:4
    for j = 1:2
        matrix2 = W0*[X2(i,2*j-1) W^(2*i-2)*X2(i,2*j)].';
        X3(i,j) = matrix2(1);
        X3(i+4,j) = matrix2(2);
    end
end

% 四级蝶形复合
X = zeros(16,1);
% 通过循环运算后为X赋值
for i = 1:8
    matrix3 = W0*[X3(i,1) W^(i-1)*X3(i,2)].';
    X(i) = matrix3(1);
    X(i+8) = matrix3(2);
end

% 时域图
n = 0:N-1;
figure;
stem(n, x);title('输入序列');

% 频域图
figure;
subplot(2,2,1);stem(n,abs(X));title('幅度谱');
subplot(2,2,2);stem(n,real(X));title('频谱实部');
subplot(2,2,3);stem(n,imag(X));title('频谱虚部');
subplot(2,2,4);stem(n,angle(X));title('相角');