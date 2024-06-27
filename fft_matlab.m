clear all;
fileID = fopen("datas\data9.in","r");
Line1 = fgets(fileID);
NM = sscanf(Line1, '%d %d');
N = NM(1); M = NM(2);

% 读取接下来的 m 个整数
secondLine = fgets(fileID);
A = sscanf(secondLine, '%f',N);

% 读取接下来的 n 个整数
thirdLine = fgets(fileID);
B = sscanf(thirdLine, '%f',M);

% 关闭文件
fclose(fileID);

N 
M

tic;
C= conv(A,B);
toc;
