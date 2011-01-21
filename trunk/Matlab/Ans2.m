clc
clear all

numOfPictures=11;
numOfPlotsInRow=1;
numOfPlotsInCol=2;
level=3;

a=imread('clown.png');
figure();
subplot(numOfPlotsInRow,numOfPlotsInCol,1);
imshow(a);
xlabel('Original RGB picture');

% a=double(a);
% [i,j,k] = size(a);
% for row = 1:i
%     for col = 1:j
%             a1=a(row,col,1);
%             a2=a(row,col,2);
%             a3=a(row,col,3);
%             newPic(row, col) = 256*256*a(row,col,1)+256*a(row,col,2)+a(row,col,3);
%     end
% end
%  
% newPic = MedianCut(newPic,level);
% 
% for row = 1:i
%     for col = 1:j
%             color = newPic(row,col);
%             r = uint32(color/256/256)-1;
%             g = uint32((color-r*256*256)/256);
%             b = uint32(color-r*256*256-g*256);
%             a(row, col,1)=r;
%             a(row, col,2)=g;
%             a(row, col,3)=b;
%     end
% end

subplot(numOfPlotsInRow,numOfPlotsInCol,2);
a=uint8(MedianCut(a,level)); 
imshow(a);
xlabel('Median cut');