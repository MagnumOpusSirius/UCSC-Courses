close all; clear; clc;
%syms x;
f=@func;
a=0;
b=3;
e=1e-4;
x_approx=bisection(f,a,b,e);

