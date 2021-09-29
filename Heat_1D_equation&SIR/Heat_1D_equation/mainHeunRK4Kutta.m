close all, clearvars

%%PARAMETRI
global c tetaa k
tetaa = 300;
k = 2.20*1e-12;
c = (-2*atan(4)+log(3/5))/(4*tetaa^3);
teta0 = 1200;

fteta=@(t,teta) -k*(teta^4-tetaa^4);

%%%ITERAZIONI NEWTON E PASSO
kmax = 10;
hh = [1 10];

for ii = 1 : numel(hh)
    h = hh(ii);
    t = 0;
    sol = teta0;
    i = 2;
    
    %%%ZERO SOLUZIONE ESATTA CON NEWTON
    while(sol > tetaa + 1)
        t(i) = t(i-1) + h;
        sol(i) = newton(sol(i-1),t(i),kmax);
        i = i + 1;
    end

    %HEUN
    solheun = Heun(fteta,t,teta0,h)';
    errh(ii) = norm(sol-solheun, 'inf');

    %RK4
    solrk4 = Runge_Kutta4(fteta,t,teta0,h)';
    errrk(ii) = norm(sol-solrk4, 'inf');

    %KUTTA
    solkutta = Kutta(fteta,t,teta0,h)';
    errk(ii) = norm(sol-solkutta, 'inf');
end
