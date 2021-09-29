function [img_qnt,MSE] = segment_image2(img, k)
    
    sumMSE = 0;
    img = single(img) ./ 255;
    
    [h,w,c] = size(img);
    n = h * w;
    I = reshape(img, [], c);
    
%     MAT = [0.1 0.2 0.3;
%         0.1 0.7 0.8];
    
    [pixels, colors] = kmeans(I, k, "MaxIter", 100);
    I_qnt = I;
    
    for pixel = 1:size(I,1)
        I_qnt(pixel, :) = colors(pixels(pixel),:);
    end
    
    for i = 1 : 3
        sumMSE = sumMSE + sum((I(:,i)-I_qnt(:,i)).^2);
    end
    
    MSE = sumMSE / n;
    img_qnt = reshape(I_qnt, h, w, c); 
    img_qnt = img_qnt .* 255;
    img_qnt = uint8(img_qnt);
end