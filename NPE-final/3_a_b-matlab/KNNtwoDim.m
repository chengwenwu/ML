function KNNtwoDim(k)
%UNTITLED2 此处显示有关此函数的摘要
%   此处显示详细说明
t_data = [0.011 1.03
1.27 1.28
0.13 3.12
-0.21 1.23
-2.18 1.39
0.34 1.96
-1.38  0.94
-0.12 0.82
-1.44 2.31
0.26 1.94];
[rows,~] = size(t_data);
for i = 1:60
    x(i) = -3 + 0.1*i;
    for j = 1:70
        y(j) = -3 + 0.1*j;
        for m = 1:10
            diff = [x(i), y(j)] - t_data(m,1);
            dist(m) = sqrt(diff * diff');
        end
        sort_res = sort(dist);
        V = 3.14*sort_res(k)*sort_res(k);
        p(i,j) = k/10/V;
    end
end
[X,Y] = meshgrid(x,y);
plot3(X,Y,p);
end

