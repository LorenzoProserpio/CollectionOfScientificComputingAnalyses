clearvars, close all
clc
%% Mesh
p = 1e4;
n_nodi = 2*p;
h = 2/(n_nodi-1);
mesh = -1 : h : 1;

%% Rho ammissibile con (r,2t+1) coprimi
r = 1;   %intero
t = 1;   %intero
rho = r/(2*t+1);

%% Preparo il vettore dei casi da valutare e il vettore degli errori
n_termv = 2 : 2 : 30;
err = zeros(numel(n_termv),1);

%% Definizione di f_rho (abbiamo usato questo escamotage perchè altrimenti Matlab prende le radici complesse)
if(mod(r,(2*t+1))==0)
    f = @(x) x.^rho;
else
    f = @(x) nthroot(x,(2*t+1)).^r;
end
    
%% Multiple esecuzioni con diversi N
for j = 1 : numel(n_termv)
    n_term = n_termv(j);
    
    %% Matrice con valutazioni dei polinomi di Legendre sulla mesh nelle colonne
    matrix_legendre = zeros(n_nodi,n_term);
    for i = 1 : n_nodi
        matrix_legendre(i,:) = LegPol(mesh(i),n_term);
    end    

    %% Valori assunti dalla f_rho nei punti della mesh
    f_val = zeros(1,n_nodi);
    f_val = f(mesh);

    %% Calcolo degli f_k mediante quadratura, saltando quelli che sappiamo essere 0
    f_k = zeros(1,n_term);
    for i = 1 : n_term
        if(mod(i+1,2) == mod(r,2))
            f_k(i) = ((2*i-1)/2)*q_trapezi(h,f_val,matrix_legendre(:,i));  %qua facciamo pure la normalizzazione
        else
            f_k(i) = 0;
        end
    end

    %% Calcolo della serie troncata di Legendre a n termini nei punti della mesh
    SerieLeg_n_term = zeros(n_nodi,1);
    for i = 1 : n_nodi
        SerieLeg_n_term(i) = sum(matrix_legendre(i,:).*f_k);
    end

    %% Calcolo dell'errore in norma due mediante quadratura
    f_err = zeros(1,n_nodi-2);
    row_uni = ones(1,n_nodi);  %serve solo perchè così possiamo riutilizzare q_trapezi
    f_err = (f_val-SerieLeg_n_term').^2;
    err(j) = sqrt(q_trapezi(h,f_err,row_uni));

    %% Plot dell'esatta e dell'approssimata (togliere i commenti per plottare, attenzione quando n_termv è grande)
%     figure
%     plot(mesh,SerieLeg_n_term)
%     hold on
%     plot(mesh,f_val)
%     title(['Confronto tra esatta e approssimata - N = ', num2str(n_term)])
%     legend('approssimata','esatta')

end

%% Plot dell'errore al variare di N in scala semilogaritmica sulle y
figure
semilogy(n_termv,err', 'b-*')
title(['(Scala log su Y) Errore in norma L^2 al variare di N e \rho=',num2str(r),'/',num2str(2*t+1)])
xlabel('N')
ylabel('Errore')

%% Confronto con O(n^(floor(rho+1/2))), da usare solo per i rho non interi maggiori di 0
if(rho > 1/2 && t ~= 0)    
    cost = err(end)/(n_termv(end).^(-floor(rho+1/2)));
    hold on
    semilogy(n_termv, cost.*n_termv.^(-floor(rho+1/2)), 'r')
    legend('errore','cost*n^{\lfloor(\rho+1/2)\rfloor}')
end

%% Calcolo e stampa EOC
EOC = zeros(1,numel(n_termv));
for i = 2 : numel(EOC)
    EOC(i) = log(err(i-1)/err(i)) / log(n_termv(i)/n_termv(i-1));
end

disp('    N         Errore   EOC')
for i = 1 : numel(n_termv)
    disp([n_termv(i),err(i),EOC(i)])
end