%metodo di newton

function ptfix = newton(h, v0, kmax, toll)
    
    %inizializzazione dei parametri
    count = 1;
    diff = 1;
    fv =  - h*effe(v0); dfv = effe1(v0,h);
    v(1) = v0;
    
    %metodo vero e proprio
    while diff>toll && count<=kmax
        count = count + 1;
        v(count) = v(count-1) - fv/dfv;
        fv = v(count) - v0 - h*effe(v(count));
        dfv = effe1(v(count),h);
        diff = abs(fv);           
    end
    
    %eventuale messaggio di errore
    if count > kmax
        disp('Attenzione non converge');
    end
    
    %risultato da restituire
    ptfix = v(end);
end

