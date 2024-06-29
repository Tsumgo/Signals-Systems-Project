clear all;
for i = 0:9
    fileName = "datas\\integer\\data" + int2str(i) + ".in";
    fileID = fopen(fileName,"r");
    Line1 = fgets(fileID);
    NM = sscanf(Line1, '%d %d');
    N = NM(1); M = NM(2);

    % 读取接下来的 m 个整数
    secondLine = fgets(fileID);
    A = sscanf(secondLine, '%d',N);

    % 读取接下来的 n 个整数
    thirdLine = fgets(fileID);
    B = sscanf(thirdLine, '%d',M);

    % 关闭文件
    fclose(fileID);

    N 
    M

    tic;
    len = length(A) +length(B)-1;
    %C= conv(A,B);
    A = [A; zeros(len-length(A), 1)];
    B = [B; zeros(len-length(B), 1)];
    X = fft(A, N);
    Y = fft(B, N);
    C = X .* Y;
    y = ifft(Y);
    toc;
end