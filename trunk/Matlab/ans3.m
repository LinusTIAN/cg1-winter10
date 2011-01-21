clc
clear all

% 8x8 map
threshold_map_8x8 = [    0, 32,  8, 40,  2, 34, 10, 42,  
                        48, 16, 56, 24, 50, 18, 58, 26; 
                        12, 44,  4, 36, 14, 46,  6, 38; 
                        60, 28, 52, 20, 62, 30, 54, 22; 
                         3, 35, 11, 43,  1, 33,  9, 41; 
                        51, 19, 59, 27, 49, 17, 57, 25;
                        15, 47,  7, 39, 13, 45,  5, 37;
                        63, 31, 55, 23, 61, 29, 53, 21; ];

%16x16 map
threshold_map_16x16 = zeros(16,16);
for row = 0:15
    for col = 0:15
        add=0;
        if(row<8 && col<8)
            add=1;
        end
        if(row<8 && col>7)
            add=2;
        end
        if(row>7 && col<8)
            add=3;
        end
        threshold_map_16x16(row+1,col+1)=4*threshold_map_8x8(mod(row,8)+1,mod(col,8)+1)+add;
    end
end

%read picture
OriginalPicture=imread('Pigion.png');
figure();
subplot(1,2,1);
imshow(OriginalPicture);
xlabel('Original greyscale picture');

%make it grayscale (from RGB)
greyPicture = rgb2gray(OriginalPicture);
%dither
[i,j,k] = size(OriginalPicture);
for row = 1:i
    for col = 1:j   
        if (greyPicture(row,col) < threshold_map_16x16(mod(row,16)+1,mod(col,16)+1))
            OriginalPicture(row,col,:)=[0,0,0];
        else
            OriginalPicture(row,col,:)=[255, 255, 255];
        end
    end
end

%paint
subplot(1,2,2);
imshow(OriginalPicture);
xlabel('Binary Dithering');
