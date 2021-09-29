clearvars, close all

%Parametri e parametri "normalizzati"
L = 5;
h = 1e-2;
n = ceil(2*L/h) + 1;
D = 1;
u = 1; un = u/D; 
k = 1; kn = k/D;
xmesh = -L:h:L;

%Soluzione Esatta
lp = (u+sqrt(u^2+4*k*D))/(2*D);
lm = (u-sqrt(u^2+4*k*D))/(2*D);

Sp = @(x) 1.*exp(lm.*x)./sqrt(u^2+4*D*k);
Sm = @(x) 1.*exp(lp.*x)./sqrt(u^2+4*D*k);

%creazione della soluzione esatta
for i = 1:numel(xmesh)
   if(xmesh(i)>=0)
      SE(i) = Sp(xmesh(i)); 
   else
       SE(i) = Sm(xmesh(i));
   end    
end

%Sorgente Gaussiana

var = 1e-4; %varianza molto bassa == max impulsività circa 2 ordini più piccolo di h
M = @(x) 1/sqrt(2*pi*var)*exp(-x.^2/(2*var));
Mmesh = M(xmesh)./D;

%Soluzione numerica con metodo delle differenze finite centrate per derivata seconda e backward per derivata prima
dp = ones(n-2,1).*(-1/h^2);
dm = ones(n-2,1).*(-un/h-1/h^2);
A = eye(n-1).*(2/h^2+un/h+kn) + diag(dp,1) + diag(dm,-1);

%backward per derivata prima e seconda nell'ultimo nodo
A(end,end-2) = -1/h^2; 
A(end,end-1) = 2/h^2-un/h;
A(end,end) = un/h+kn-1/h^2;

F = Mmesh'; F = F(2:n);
Sol = A\F;  
Sol = [0 ; Sol];

%Plot ed errore
plot(xmesh, Sol, 'ro');
hold on;
plot(xmesh, SE, 'b');

err = norm(Sol-SE','inf')

