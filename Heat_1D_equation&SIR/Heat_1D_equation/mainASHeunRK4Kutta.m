close all, clearvars

%%%PARAMETRI
global c tetaa k
tetaa = 300;
k = 2.20*1e-12;
c = (-2*atan(4)+log(3/5))/(4*tetaa^3);
teta0 = 1200;

%PASSO FISSO E VALORI DI T
fteta=@(t,teta) -k*(teta^4-tetaa^4);
%Fisso H e faccio tendere T -> inf per vedere se la soluzione tende a 300
h = [510:1:514];
T = [1e2 1e3 1e4 1e5 1e6 1e7];

for i = 1:numel(h)
    hh = h(i);
    for ii = 1 : numel(T) 
        t = 0 : hh : T(ii);
        %HEUN
        %solheun = Heun(fteta,t,teta0,hh)';
        %asheun(i,ii) = abs(solheun(end)-300);

        %RK4
        solrk4 = Runge_Kutta4(fteta,t,teta0,hh)';
        asrk4(i,ii) = abs(solrk4(end)-300);

        %KUTTA
        %solkutta = Kutta(fteta,t,teta0,hh)';
        %askutta(i,ii) = abs(solkutta(end)-300);
    end
end
