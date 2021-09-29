function [x0,n] = bisezione(a,b,toll,t)
    n = 0;
    while((b-a)/2 > toll)
        m = (a+b)/2;
        if(f(a,t)*f(m,t)<0)
            b = m;
        else
            a = m;
        end
        n = n + 1;
    end
    x0 = (a+b)/2;
return