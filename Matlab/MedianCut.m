function Y = MedianCut(theImage,numOfColors) 
  
theImage = double(theImage);
colorSize = 256*256*256+1;
x = size(theImage,1);
y = size(theImage,2);
% Contains the colors in the original image
colorMap = zeros(1,colorSize); 
maxColor = 0;

for i=1:x 
    for j=1:y 
        %count num of times each color appears
        k = theImage(i,j); 
        colorMap(k+1) = colorMap(k+1)+1; 
        maxColor = max(maxColor, k+1);
    end 
end 

  
%make an array with all the colors 
tempCounter=1;
for c=1:maxColor     
    if colorMap(c)==0 
        continue 
    end   
    for ppf=1:colorMap(c) 
        orderedColorMap(tempCounter) = c-1; 
        tempCounter = tempCounter+1; 
    end 
end 
range = (tempCounter-1)/numOfColors ;
  
firstColor = 1;
%start algo
for i=1:numOfColors
    %all colors in range
    for j=1:range 
        colorsRange(j) = orderedColorMap(firstColor+j-1); 
    end 
    %find average color
    maxC = max(colorsRange);
    minC = min(colorsRange);
    averageC = round(sum(colorsRange)/(range));
    %change all colors in range to average color
    for row=1:x
        for col=1:y
            if (maxC >= theImage(row,col)) && ( minC <= theImage(row,col)) 
                theImage(row,col) = averageC;
            end 
        end 
    end   
    firstColor = firstColor+range;   
end 
  
Y = uint32(theImage); 
