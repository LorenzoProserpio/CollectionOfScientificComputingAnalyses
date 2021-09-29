clearvars, close all

%Parametri
h1 = 1e-2;
h2 = 1e-1;
dx = 1e-2;
M = 101;
k = 1:100;
C = 1e-2 : h1 : 2;
Pe = 1e-2 : h2 : 30;
meshstab = []; %Matrice vuota per contenere i punti (Pe,C) in cui il metodo è stabile

%Funzione di stabilità
stab = @(C, Pe, k, M) 1 - C./Pe - C.*sqrt(1/Pe.^2-1)*cos(k.*pi./(M));

%Cicli per far variare Pe e C
for i = 1:numel(C)
    for ii = 1:numel(Pe)
        for iii = 1:numel(k)
            if(abs(stab(C(i),Pe(ii),k(iii),M))>1)
                break;
            end
            if(iii==100 && abs(stab(C(i),Pe(ii),k(iii),M))<=1)
                meshstab = [meshstab [Pe(ii);C(i)]];
            end
        end
    end
end

%Plot
plot(meshstab(1,:),meshstab(2,:), 'bo')