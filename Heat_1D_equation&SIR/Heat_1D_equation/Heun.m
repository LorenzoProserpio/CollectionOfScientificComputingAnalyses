function u = Heun(f,t,A,h)

u=[A;zeros(numel(t)-1,1)];

for i=1:(numel(t)-1)
    K1=f(t(i),u(i)); % passo EE 
    K2=f(t(i+1),u(i)+h*K1);
    u(i+1)=u(i)+1/2*(K1+K2)*h; % comb lineare
end
return