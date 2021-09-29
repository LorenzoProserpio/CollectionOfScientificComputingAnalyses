function val = bcfun(x,t,beta,D)
    if (x == 0 || x == 1)
        val = exp(-4*(pi^2)*D.*t).*sin(-2*pi*beta.*t);
    else
        val = 0;
    end
return