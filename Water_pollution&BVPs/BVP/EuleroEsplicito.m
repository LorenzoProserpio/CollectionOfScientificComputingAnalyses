close all
clearvars

%parametri newton
kmax = [5 10 20 50];
toll = [1e-2 1e-4 1e-6 1e-8 1e-10 1e-12 1e-14];

% definizione della mesh e dati iniziali
h = [1e-1 1e-2 1e-3];
xf = 1; xi = -1;
uf = 1; ui = 1;
vi = sinh(-1);

for j = 1 : numel(h)
    for jj = 1 : numel(toll)
        for jjj = 1 : numel(kmax)
            %inizializzazione dati della singola approssimazione
            vn = vi;
            un = ui;
            hh = h(j);
            n = ceil((xf-xi)/hh);
            xmesh = (xi: hh: xf);

            %bvpc4 per sol 'esatta'

            %opzioni di tolleranza + statistiche 
            options = bvpset('RelTol',1e-4, 'AbsTol', 1e-10, 'Stat', 'on');

            %guess della sol iniziale
            solinit = bvpinit(xmesh, @guess);

            %creazione della soluzione 'esatta'
            sol = bvp4c(@bvpfcn, @bcfcn, solinit, options);
            
            %creazione della soluzione approssimata
            for i = 2:(n+1)
                vn(i) = newton(hh, vn(i-1), kmax(jjj), toll(jj));
                un(i) = un(i-1) + hh*vn(i-1);
            end
            
            %plot ed errore
            %plot(xmesh, un, xmesh, sol.y(1,:))
            err(j,jj,jjj) = norm(un - sol.y(1,:), 'inf');
        end
    end
end

%loglog(h, err(:,end,end), 'ro-');
