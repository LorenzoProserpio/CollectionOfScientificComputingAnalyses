clearvars, close all

%%PARAMETRI
beta0 = 0.35;
gamma = 0.14;
T = 200;
%lt = 0;
%betat = beta0;
I0 = 0.35*1e-4;
S0 = 1 - I0;
R0 = 0;

h = 1e-1;

%%METODO RK4
t = 0:h:T; 
u = [S0;I0;R0];
F = @(s,i,beta) -beta*s*i;
G = @(s,i,beta) beta*s*i-gamma*i;
%H = @(i) gamma*i;
S = S0;
I = I0;
R = R0;

%PARTE PER STUDIARE ALPHA E BETA
% s0 = S0;
% alpha = gamma/beta0;
% be = beta0;

%PARTE PER STAMPARE I(S)
% ctrl = 0;
% cost = @(s,i,beta) i+s-(gamma/beta)*log(s);
% c = cost(S0,I0,beta0);
% f = @(c,s,beta) c-s+(gamma/beta)*log(s);
% is = f(c,S0,beta0);

for i = 2:numel(t)
    if(t(i)<=70 && t(i)>=40)
        betat = 0.3 * beta0;
%         ctrl = ctrl + 1;
%         if(ctrl == 1)
%             c = cost(S,I,betat);
%         end
    else
        betat = beta0;
%         if(t(i)>70 && ctrl>0)
%             c = cost(S,I,betat);
%         end   
%         ctrl = 0;
    end
    
%     if(t(i)==40)
%        alpha(2) = gamma/betat;
%        s0(2) = S;
%        be(2) = betat;
%     end
%     
%     if(t(i)==70)
%        alpha(3) = gamma/beta0
%        s0(3) = S
%        be(3) = beta0;
%     end
    
    K1 = F(S,I,betat);
    L1 = G(S,I,betat);
    %M1 = H(I);
    K2 = F(S+0.5*h*K1, I+0.5*h*K1,betat);
    L2 = G(S+0.5*h*L1, I+0.5*h*L1,betat);
    %M2 = H(I+0.5*h*M1);
    K3 = F(S+0.5*h*K2, I+0.5*h*K2,betat);
    L3 = G(S+0.5*h*L2, I+0.5*h*L2,betat);
    %M3 = H(I+0.5*h*M2);
    K4 = F(S+h*K3,I+h*K3,betat);
    L4 = G(S+h*L3,I+h*L3,betat);
    %M4 = H(I+h*M3);    
    S = S + 1/6*(K1+2*K2+2*K3+K4)*h;
    I = I + 1/6*(L1+2*L2+2*L3+L4)*h;
    %R = R + 1/6*(M1+2*M2+2*M3+M4)*h;
    u = [u [S;I;1-S-I]];
    %is(i)=f(c,S,betat);
end

plot (t,u);

%plot(u(1,:),u(2,:));
%hold on 
%plot(u(1,:),is);
%err=norm(u(2,:)-is,'inf')


