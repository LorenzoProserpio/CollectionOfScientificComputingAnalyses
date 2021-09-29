function z = u(x,y,t)

% Exact solution
z = exp(-(x.^2+y.^2)/(1+4.*t))./sqrt(1+4.*t);

return

