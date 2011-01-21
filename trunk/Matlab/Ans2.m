clc
clear all

numOfPictures=11;
numToAdd=0.1;
numOfPlotsInRow=1;
numOfPlotsInCol=2;

a=imread('clown.png');

figure();
subplot(numOfPlotsInRow,numOfPlotsInCol,1);
imshow(a);
xlabel('Original RGB picture');

[i,j,k] = size(a);
for row = 1:i
    for col = 1:j
            %newPic(row, col) =a(row,col,1);
    end
end
 
%[MyIndexed,MyColormap] = rgb2ind(MyRGB,K);

subplot(numOfPlotsInRow,numOfPlotsInCol,2);
imshow(MedianCut(a,3));
xlabel('Median cut');