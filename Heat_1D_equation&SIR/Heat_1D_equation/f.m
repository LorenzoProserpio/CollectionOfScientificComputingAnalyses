%%%SOLUZIONE ESATTA IMPLICITA
function x = f(x,t)
    global c tetaa k
    x = 1/(4*tetaa^3)*(-2*atan(x/tetaa)+log(x-tetaa)-log(x+tetaa))+k*t-c;    
return