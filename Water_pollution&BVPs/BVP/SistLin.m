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
            %inizializzazione dei dati della singola approssimazione
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

            %creazione della soluzione 
            sol = bvp4c(@bvpfcn, @bcfcn, solinit, options);
            
            %metodo di newton
            for i = 2 : n
                vn(i) = newton(hh, vn(i-1), kmax(jjj), toll(jj));
            end    
            
            %implementazione delle differenze finite
            dp = ones(n-2,1);
            dm = ones(n-2,1);
            A = 1/(hh^2).*(eye(n-1).*(-2) + diag(dp,1) + diag(dm,-1));

            fn = (effe(vn(2:(end))))'; 
            fn(1) = fn(1) - 1/hh^2;
            fn(end) = fn(end) - 1/hh^2;

            u = A\fn;
            u = [ui; u; uf]; 
            
            %plot ed errore
            %plot(xmesh, u, xmesh, sol.y(1,:)) 
            err(j,jj,jjj) = norm(u'-sol.y(1,:),'inf');
            
        end
    end
end

%loglog(h, err, 'ro-');