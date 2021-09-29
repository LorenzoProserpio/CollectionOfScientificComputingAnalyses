close all, clearvars

%%PARAMETRI
global c tetaa k
tetaa = 300;
c = (-2*atan(4)+log(3/5))/(4*tetaa^3);
k = 2.20*1e-12;
teta0 = 1200;

%%METODO RK45
fteta=@(t,teta) -k*(teta^4-tetaa^4);
tvet = [0, 2e4];
h = 1e-3;
tolrk = 1e-13;
[tt,solRK45] = Runge_Kutta_Fehlberg(fteta,tvet,teta0,h,tolrk);
solRK45 = solRK45';

%%METODO NEWTON
kmax = 10;
sol = teta0;

for i = 2:numel(tt)
    sol(i) = newton(sol(i-1),tt(i),kmax);
end

%%CALCOLO ERRORE
err = norm(sol-solRK45,'inf');


