function x0 = bisezione2(a,b,nit,t)
    for i = 1 : nit
        m = (a+b)/2;
        if(f(a,t)*f(m,t)<0)
            b = m;
        else
            a = m;
        end
    end
    x0 = (a+b)/2;
return