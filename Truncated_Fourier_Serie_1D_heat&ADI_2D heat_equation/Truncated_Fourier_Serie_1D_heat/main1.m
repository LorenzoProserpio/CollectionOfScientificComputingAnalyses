clearvars, close all

% soluzione con DF (centrate in spazio + esplicite in tempo)

%Parametri
D = 1;
dx = 1e-2;

%Fisso Pe e C
Pe = 0.48;
C = 0.2;

%Calcolo con formula inversa beta e dt
beta = 2.*Pe./dx;
dt = C.*dx./beta;

%Griglia e tempo finale
tf = 1; 
x = 0 : dx : 1;
nX = numel(x); 

u0 = @(x) sin(2*pi.*x);  % condizione iniziale 

%Calcola la soluzione nei nodi interni per i tempi tE
[tEE,uEE] = FEulero(@convdifffun, beta, D, [0 tf], u0,x,nX,dx,dt,@bcfun);
uEE = [(bcfun(x(1),tEE,beta,D));uEE;(bcfun(x(end),tEE,beta,D))]; 

%Soluzione esatta
solesatta = @(x,t,beta,D) exp(-4*pi^2*D.*t).*sin(2*pi.*(x - beta.*t));
xs = 0 : dx : 1;
ts = 0 : dt : tf;
mesh = meshgrid(ts,xs);
meshsol=[];
for i = 1:numel(xs)
    for j = 1:numel(ts)
        meshsol(i,j) = solesatta(xs(i),ts(j),beta,D);
    end
end

%Calcolo dell'errore
for i = 1:numel(ts)
    err(i) = norm(uEE(:,i) - meshsol(:,i),'inf');
end

maxerr = max(err);

% PLOT

% subplot(3,1,1);
% plot(x,uEE(:,12000),'bo');
% hold on;
% xlabel('x')
% ylabel('u')
% plot(xs,meshsol(:,12000),'r-');
% title('t = 0.25 s')
% xlabel('x')
% ylabel('u')
% subplot(3,1,2);
% plot(x,uEE(:,24000),'bo');
% hold on;
% plot(xs,meshsol(:,24000),'r-');
% title('t = 0.5 s')
% xlabel('x')
% ylabel('u')
% subplot(3,1,3);
% plot(x,uEE(:,end),'bo');
% hold on;
% plot(xs,meshsol(:,end),'r-');
% title('t = 1 s')
% xlabel('x')
% ylabel('u')







