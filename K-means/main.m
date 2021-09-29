clearvars, close all
img = imread("mandrill.png");
k = 26;
figure
for i = 1:numel(k)
    kk = k(i);
    img_qua = segment_image(img,kk);
    imshow(img_qua)
end
