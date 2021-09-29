function img_qnt = segment_image(img, k)
    
    img = single(img) ./ 255;
    
    [h,w,c] = size(img);
    
    I = reshape(img, [], c);
    
%     MAT = [0.1 0.2 0.3;
%         0.1 0.7 0.8];
    
    [pixels, colors] = kmeans(I, k, "MaxIter", 100);
    I_qnt = I;
    
    for pixel = 1:size(I,1)
        I_qnt(pixel, :) = colors(pixels(pixel),:);
    end
    
    img_qnt = reshape(I_qnt, h, w, c); 
    img_qnt = img_qnt .* 255;
    img_qnt = uint8(img_qnt);
end