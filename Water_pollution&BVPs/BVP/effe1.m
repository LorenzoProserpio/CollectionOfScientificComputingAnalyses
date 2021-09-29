%derivata per il metodo di newton

function F1v = effe1(v,h)
    F1v = 1 - (h.*v)/effe(v);
end