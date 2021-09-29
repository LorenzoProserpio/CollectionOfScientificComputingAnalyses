clearvars, close all
img = imread("mandrill.png");

k = 2 : 4 : 40;
MSE = zeros(numel(k),1);

for i = 1:numel(k)
    kk = k(i);
    [img_qua, MSE(i)] = segment_image2(img,kk);
end

plot(k,MSE)
title('Comportamento MSE in relazione a k');
xlabel('k')
ylabel('MSE')

miglioramento = zeros(numel(k)-1,1);
for i = 1 : numel(miglioramento)
    %miglioramento percentuale rispetto al k precedente
    miglioramento(i) = (MSE(i)-MSE(i+1))/MSE(i);
end

figure
miglioramento = miglioramento.*100;
plot(k(2:end),miglioramento)

