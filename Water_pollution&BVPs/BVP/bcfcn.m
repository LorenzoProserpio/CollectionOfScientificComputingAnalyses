% BCs in forma implicita

function res = bcfcn(ya,yb)
    res = [ya(1)-1; yb(1)-1];
end

