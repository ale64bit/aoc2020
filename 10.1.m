x = dlmread('input.txt');
d = diff([0;sort(x);max(x)+3]);
sum(d==1)*sum(d==3)
