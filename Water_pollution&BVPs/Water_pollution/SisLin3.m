clearvars, close all

%uc' - Dc'' = M

%Inizializzazione dei parametri
L = 20;
h = 1e-2;
n = ceil(2*L/h) + 1;
D = 10;
u = 20;
M = 1;
xmesh = -L:h:L;

%Soluzione esatta
c1 = 1./(u*(1-exp(-L*u/D)));
c2 = -c1*exp(-L*u/D);

Sol = @(x) c1*exp(u/D*x)+c2;

%Sorgente gaussiana

var = 1e-4; %varianza molto bassa == max impulsività circa 2 ordini più piccolo di h
Mf = @(x) 1/sqrt(2*pi*var)*exp(-x.^2/(2*var));
Mmesh = Mf(xmesh);

%Soluzione approssimata usando differenze finite centrate per la derivata seconda e backward per la derivata prima 
dp = ones(n-2,1).*(-D/h.^2);
dm = ones(n-2,1).*(-u/h-D/h.^2);
A = eye(n-1).*(u/h + 2*D/h.^2)  + diag(dp,1) + diag(dm,-1);

%Correzione per l'ultimo nodo (backward per derivata seconda e derivata prima nulla)
A(end,end-2) = - D/h.^2;
A(end,end-1) = + 2*D/h.^2;
A(end,end) = - D/h.^2;

F = Mmesh(2:n)';
uh = A\F;
uh = [0; uh];

%Calcolo della soluzione esatta
for j = 1:n
   if(xmesh(j)<0)
       sol(j) = Sol(xmesh(j));
   else
       sol(j) = 1/u;
   end
end

%Plot e calcolo dell'errore
plot(xmesh, uh, 'ro');
hold on;
plot(xmesh, sol, 'b-');

err=norm(uh'-sol, 'inf')

