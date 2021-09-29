clearvars, close all

% Matrice per errore e ordine
dati = zeros(5,3);

% Parametri per passo spaziale e tempo finale
h = 4*1e-1;
T = 1;

% 5 griglie ogni volta dimezza il passo

for p = 1:5
    
    % Inizializzazione dei parametri
    h = h/2;
    N = 1/h;
    dt = h;
    r = dt/(2*h^2);
    M = T/dt;
    
    
    % Creazione ed inizializzazione matrice soluzione approssimata
    U = zeros(N+1,N+1);
    
    for i = 0:N
       for j = 0:N
          U(i+1,j+1) = g1(i*h,j*h); 
       end
    end
    
    % Creazione matrici per metodo
    V = zeros(N-1,N-1);
    fvet = zeros(N-1,N-1);
    
    % Matrice tridiagonale usata nel metodo nel LHS
    tridiagonal = spdiags([-ones(N-1,1), 2*ones(N-1,1), -ones(N-1,1)],[-1,0,1], N-1, N-1);
    A = speye(N-1) + r*tridiagonal;
    
    % Creazione matrici per algoritmo di Thomas
    diagT = diag(A);
    sottodT = diag(A,-1);
    sopradT = diag(A,1);
    w = zeros(N-2,1);
    
    for i = 2 : N-1
        w(i-1) = sottodT(i-1) / diagT(i-1);
        diagT(i) = diagT(i) - w(i-1) * sopradT(i-1);
    end
    
    for m = 1:M
       
        % Creazione matrice del termine forzante f
        for i = 1:N-1
            for j = 1:N-1
                fvet(i,j) = f(i*h,j*h,(m-0.5)*dt);
            end
        end
        
        % Primo step
        for i = 1:N-1
            for j = 1:N-1
                V(i,j) = U(i+1,j+1) + r*(U(i+1,j)-2*U(i+1,j+1)+U(i+1,j+2));
            end
        end
        
        % Secondo step
        for j = 1:N-1             
            % Creazione termine noto
            b = V(:,j) + (dt/2)*fvet(:,j);
            b(1) = b(1) + r*g2(0,h*j,(m-0.5)*dt);
            b(end) = b(end) + r*g2(1,h*j,(m-0.5)*dt);
            % Soluzione con algoritmo di Thomas
            U(2:N,j+1) = thomas(diagT,sopradT,w,N-1,b);
        end
        
        % Terzo step
        for i = 1:N-1  
            % Creazione termine noto
            b = (2*U(i+1,2:N) - V(i,:))';
            b(1) = b(1) + r*g2(h*i,0,m*dt);
            b(end) = b(end) + r*g2(h*i,1,m*dt);
            % Soluzione con algoritmo di Thomas
            U(i+1,2:N) = (thomas(diagT,sopradT,w,N-1,b))';
        end
        
        % Orliamo con le condizioni al bordo
        for i = 0:N
            U(1,i+1) = g2(0, h*i, dt*m); 
            U(N+1,i+1) = g2(h*N, h*i, dt*m);
            U(i+1,1) = g2(h*i, 0, dt*m);
            U(i+1,N+1) = g2(h*i, h*N, dt*m);
        end
        
    end
    
    % Calcolo dell'errore
    err_tmp = 0;
    max_err = 0;

    for i = 1:N-1
       for j = 1:N-1
           err_tmp = abs(U(i+1,j+1) - u(h*i, h*j, T));
           if err_tmp > max_err
              max_err = err_tmp; 
           end
       end
    end

    max_err = max(max_err);
    
    % Inserimento dei dati nella tabella
    dati(p,1) = h;
    dati(p,2) = max_err;
    if p ~= 1
       % Stima dell'ordine di convergenza
       dati(p,3) = log(dati(p-1,2) / dati(p,2)) / log(2); 
    end   
    
end

% Stampa della matrice (allineata per format long)
disp('   h                   max err             ordine di conv');
disp(dati(:,1:3));







