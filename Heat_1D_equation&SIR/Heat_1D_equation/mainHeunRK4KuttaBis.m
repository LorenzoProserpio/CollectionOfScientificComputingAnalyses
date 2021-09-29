close all, clearvars

%%PARAMETRI
global c tetaa k
tetaa = 300;
k = 2.20*1e-12;
c = (-2*atan(4)+log(3/5))/(4*tetaa^3);
teta0 = 1200;

fteta=@(t,teta) -k*(teta^4-tetaa^4);

%%%TOLLERANZA BISEZIONE,PASSO E NIT PER CHIAMATA
hh = [1e-1 1 10];
n = 0;
toll = 1e-5;

for ii = 1 : numel(hh)
    h = hh(ii);
    t = 0;
    sol = teta0;
    i = 2;
    
    %%%ZERO SOLUZIONE ESATTA CON BISEZIONE
    while(sol > tetaa + 1)
        t(i) = t(i-1) + h;
        [sol(i) n(i)] = bisezione(tetaa,sol(i-1),toll,t(i));
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