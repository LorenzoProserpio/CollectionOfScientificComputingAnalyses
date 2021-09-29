%La matrice deve essere diagonalmente dominante!
function x = thomas(diagT,sopradT,w,n, noto)
    
    %forward
    for i = 2 : n
       noto(i) = noto(i) - w(i-1) * noto(i-1); 
    end
    
    %backward
    x(n) = noto(n) / diagT(n);
    for i = (n-1) : (-1) : 1
        x(i) = (noto(i) - sopradT(i) * x(i+1)) / diagT(i);
    end
    
    x = x';
    
return