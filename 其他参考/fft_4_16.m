% 16点基4-FFT算法
% 定义输入、初始化输出
N = 16;
x = [3 2 1 0 1 0 6 3 2 7 0 0 0 0 0 0];
X = zeros(1,16);

% 对输入的16个数字进行分组（MATLAB下标从1开始）
x_1 = [x(1) x(5) x(9) x(13)];
x_2 = [x(2) x(6) x(10) x(14)];
x_3 = [x(3) x(7) x(11) x(15)];
x_4 = [x(4) x(8) x(12) x(16)];

x_matrix = [x_1.' x_2.' x_3.' x_4.'];

% 第一级蝶形复合，根据定义做4点DFT运算
k = 0:3;
W4 = exp(-1i*2*pi*(k'*k)/4);% 定义DFT变换的矩阵W
W = exp(-1i*2*pi/16);

% 二级蝶形复合
% 定义X0 X1 X2 X3为4元素向量，构成16个一级蝶形复合的结果
X_matrix = W4 * x_matrix;
X0 = X_matrix(:,1);
X1 = X_matrix(:,2);
X2 = X_matrix(:,3);
X3 = X_matrix(:,4);
for i = 1:4
    matrix1 = W4*[X0(i) W^(i-1)*X1(i) W^(2*i-2)*X2(i) W^(3*i-3)*X3(i)].';
    X(i) = matrix1(1);
    X(i+4) = matrix1(2);
    X(i+8) = matrix1(3);
    X(i+12) = matrix1(4);
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