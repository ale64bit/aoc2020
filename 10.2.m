x = sort(dlmread('input.txt'));
n = x(end)+3;
dp = [[0 0 1]'; sum((1:n)==[x;n])'];
for i = 4:n
  dp(i) = dp(i) * sum(dp((i-3):(i-1)));
end
dp(n)
