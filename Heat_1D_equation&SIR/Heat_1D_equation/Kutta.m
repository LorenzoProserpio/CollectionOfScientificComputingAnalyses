function u = Kutta(f,t,A,h)

u=[A;zeros(numel(t)-1,1)];

for i=1:(numel(t)-1)
    K1=f(t(i),u(i)); % passo EE 
    K2=f(t(i)+1/3*h,u(i)+1/3*h*K1);
    K3=f(t(i)+2/3*h,u(i)-1/3*h*K1+h*K2);
    K4=f(t(i+1),u(i)+h*K1-h*K2+h*K3);
    u(i+1)=u(i)+1/8*(K1+3*K2+3*K3+K4)*h; % comb lineare
end
return