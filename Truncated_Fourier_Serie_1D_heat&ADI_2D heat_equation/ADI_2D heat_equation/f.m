function z = f(x,y,t)

%forcing term
z = 2*exp(-(x.^2+y.^2)./(1+4.*t))./((1+4.*t).^(3/2));

return

