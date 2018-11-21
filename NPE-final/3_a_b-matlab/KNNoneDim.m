function KNNoneDim(k)
%UNTITLED2 此处显示有关此函数的摘要
%   此处显示详细说明
t_data = [1.36, 1.41, 1.22, 2.46, 0.68, 2.51, 0.60, 0.64, 0.85 0.66];
[~,s] = size(t_data);
%disp(n)
for i = 1:300
x(i) = 0.01*i;
for m=1:s
   dis(m) = abs(x(i) - t_data(1,m));
end
 sort_res = sort(dis);
 v = 2*sort_res(k);
 p(i) = ( k / s / v);
%    disp(p(i));
end
plot(x,p);
end

