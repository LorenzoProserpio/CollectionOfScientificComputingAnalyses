%% Quadratura mediante trapezi
function trap = q_trapezi(h,f_val,leg_col)
    trap = 0;
    N = numel(f_val);
    for i = 1 : N-1
      trap = trap + h/2.*(f_val(i)*leg_col(i)+f_val(i+1)*leg_col(i+1));
    end
return 