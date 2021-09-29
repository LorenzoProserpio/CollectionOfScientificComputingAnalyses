close all, clearvars

%%PARAMETRI
global c tetaa k
tetaa = 300;
c = (-2*atan(4)+log(3/5))/(4*tetaa^3);
k = 2.20*1e-12;
teta0 = 1200;

%%Metodo RK45
fteta=@(t,teta) -k*(teta^4-tetaa^4);
tvet = [0, 2e4];
h = 1e-4;
tolrk = 1e-12;
[tt,solRK45] = Runge_Kutta_Fehlberg(fteta,tvet,teta0,h,tolrk);
solRK45 = solRK45';

%%Bisezione 
nit = -floor(log(tolrk)/log(2));
sol = teta0;

for i = 2:numel(tt)
    sol(i) = bisezione2(tetaa,sol(i-1),nit,tt(i));
end

%%Calcolo dell'errore
err = norm(sol-solRK45,'inf');


