%metodo di newton

function ptfix = newton(x0, t, kmax)
    %inizializzazione dei parametri
    global tetaa
    count = 1;
    diff = 1;
    fx = f(x0,t); f1x = f1(x0);
    x(1) = x0;
    
    %metodo vero e proprio con kmax come numero di iterazioni fissato
    while count<=kmax
        count = count + 1;
        x(count) = x(count-1) - fx/f1x;
        if(x - tetaa <= 0)
            disp('Ha già raggiunto la temperatura ambiente');
            x(count) = tetaa;
            break;
        end
  
        fx = f(x(count),t);
        f1x = f1(x(count));
        %diff = (abs(fx));           
    end
    
    %eventuale messaggio di errore
    %if count > kmax
       % disp('Attenzione non converge');
    %end
    
    %risultato da restituire
    ptfix = x(end);
end
