function u = Runge_Kutta4(f,t,A,h)

u=[A;zeros(numel(t)-1,1)];

for i=1:(numel(t)-1)
    K1=f(t(i),u(i)); % passo EE 
    K2=f(t(i)+0.5*h,u(i)+1/2*h*K1);
    K3=f(t(i)+0.5*h,u(i)+1/2*h*K2);
    K4=f(t(i+1),u(i)+h*K3);
    u(i+1)=u(i)+1/6*(K1+2*K2+2*K3+K4)*h; % comb lineare
end
return