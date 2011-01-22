clc
clear all
format long

numOfColors = 4;

originalPic = imread('clown.png');
figure();
subplot(1,2,1);
imshow(originalPic);
xlabel('Original RGB picture');

originalPic = double(originalPic);
[i,j,k] = size(originalPic);
% for row = 1:i
%     for col = 1:j
%             r = originalPic(row,col,1);
%             g = originalPic(row,col,2);
%             b = originalPic(row,col,3);
%       %      newPic(row, col) = 256*256*originalPic(row,col,1) +256*originalPic(row,col,2)+originalPic(row,col,3);
%             newPic(row, col) = 256*256*r +256*g+b;
%         
%      
%     end
% end
%  
% newPic = MedianCut(newPic,numOfColors);
% 
% for row = 1:i
%     for col = 1:j
%             color = uint32(newPic(row,col));
%             r = uint32(mod(color/256/256,256));
%             g = uint32(mod(color/256,256));
%             b = uint32(mod(color,256));
%             
%             originalPic(row, col,1) = r;
%             originalPic(row, col,2) = g;
%             originalPic(row, col,3) = b;
%     end
% end

originalPic(:,:,1) = MedianCut(originalPic(:,:,1),numOfColors);
originalPic(:,:,2) = MedianCut(originalPic(:,:,2),numOfColors);
originalPic(:,:,3) = MedianCut(originalPic(:,:,3),numOfColors);
subplot(1,2,2); 
originalPic=uint8(originalPic); 
imshow(originalPic);
xlabel('Median cut');