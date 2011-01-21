function Y = MedianCut(theImage,level) 
  
theImage = double(theImage);
% Contains the colors in the original image
colorSize=256*256*256+1;
colorMap = zeros(1,colorSize); 
maxColor=0;
for i=1:size(theImage,1) 
    for j=1:size(theImage,2) 
        %count num of times each color appear
        k=theImage(i,j); 
        colorMap(k+1)=colorMap(k+1)+1; 
        maxColor=max(maxColor, k+1);
    end 
end 
  
%make an array with all the colors 
y=1;   
for c=1:maxColor     
    if colorMap(c)==0 
        continue 
    end 
  
    for x=1:colorMap(c) 
        img(y)=c-1; 
        y=y+1; 
    end 
end 
  
n=size(img,2); 
a=mod(n,level); 
s=(n-a)/level; 
  
m=1; 
if a~=0 
    for i=1:a 
        for j=1:s+1 
            sub(j)=img(m+j-1); 
        end 
        m=m+s+1; 
        maks=max(sub); 
        mini=min(sub); 
        ort=round(sum(sub)/(s+1)); 
    
        for z=1:size(theImage,1) 
            for t=1:size(theImage,2) 
                if (theImage(z,t)<= maks) & (theImage(z,t)>=mini) 
                    theImage(z,t)=ort; 
                end 
            end 
        end 
    
    end 
end 
  
for i=a+1:level 
    for j=1:s 
        subb(j)=img(m+j-1); 
    end 
    m=m+s; 
    maks=max(subb); 
    mini=min(subb); 
    ort=round(sum(subb)/(s)); 
    
    for z=1:size(theImage,1) 
        for t=1:size(theImage,2) 
            if (theImage(z,t)<= maks) & (theImage(z,t)>=mini) 
                theImage(z,t)=ort; 
            end 
        end 
    end 
    
end 
  
%Y=uint8(theImage); 
Y=theImage; 
