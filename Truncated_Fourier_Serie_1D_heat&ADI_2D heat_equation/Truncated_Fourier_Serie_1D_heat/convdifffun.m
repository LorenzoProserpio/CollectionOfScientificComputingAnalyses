function RHS=convdifffun(beta,D,t,x,u,nX,dx,bcfun)
% costruisce la parte di discretizzazione spaziale della derivata
% seconda + eventuale termine di sorgente

nodi = nX-2; % nr nodi interni 
RHS = zeros(nodi,1);

% ciclo nello spazio
for j = 2:(nodi-1) % nodi interni che vedono solo nodi interni 
    RHS(j) = D/(dx.^2)*(u(j+1)-2*u(j)+u(j-1)) - beta/(2.*dx)*(u(j+1)-u(j-1));
end

% primo nodo interno
RHS(1) = D/(dx.^2)*(u(2)-2*u(1)+bcfun(x(1),t,beta,D)) - beta/(2.*dx)*(u(2)-bcfun(x(1),t,beta,D));

% ultimo nodo interno x
RHS(end) = D/(dx.^2)*(bcfun(x(end),t,beta,D)-2*u(end)+u(end-1)) - beta/(2.*dx)*(bcfun(x(end),t,beta,D)-u(end-1));

return