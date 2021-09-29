function [tEE,uEE]=FEulero(convdifffun,beta,D,tspan,u0,x,nX,dx,dt,bcfun)

% nr intervalli temporali 
M = ceil((tspan(2)-tspan(1))/dt);
tEE = tspan(1):dt:tspan(2);

uEE(:,1) = u0(x(2:end-1));
% ciclo temporale 
cont = 1;
for t = tEE(1:end-1)
    uEE(:,cont+1) = uEE(:,cont)+dt*convdifffun(beta,D,t,x,uEE(:,cont),nX,dx,bcfun);
    cont = cont+1;
end


return