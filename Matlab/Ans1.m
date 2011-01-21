clc
clear all

numOfPictures=11;
numToAdd=0.1;
numOfPlotsInRow=4;
numOfPlotsInCol=3;

a=imread('door3.png');

figure();
subplot(numOfPlotsInRow,numOfPlotsInCol,1);
imshow(a);
xlabel('Original RGB picture');
%a = a./255.0;

hsvImage=rgb2hsv(a); % this function converts the RGB to HSV image
[i,j,k] = size(hsvImage);

currHSVVal=1;
for currHSV = 1:numOfPictures
    hsvImageNew = hsvImage;
     for row = 1:i
        for col = 1:j
            hsvImageNew(row, col, 2) = hsvImageNew(row, col, 2)*currHSVVal;

        end
     end
    subplot(numOfPlotsInRow,numOfPlotsInCol,1+currHSV);
    imshow(hsv2rgb(hsvImageNew));
    xlabel(sprintf('currHSVVal= %1.2f', currHSVVal));  
    
    currHSVVal = currHSVVal - numToAdd;
end