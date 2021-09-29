%% Funzione per calcolare i polinomi di Legendre in modo ricorsivo
function all_bk_x = LegPol(x,n_term)
    all_bk_x = zeros(1,n_term);
    all_bk_x(1) = 1; 
    all_bk_x(2) = x;
    for k = 2 : (n_term-1)
       % attenzione che MATLAB inizia la numerazione da 1 e non 0
       all_bk_x(k+1) = ((2*k-1)*x*all_bk_x(k)-(k-1)*all_bk_x(k-1))/(k);
    end
return 