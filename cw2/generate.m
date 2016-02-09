n=10000;
xmax = 80;
ymax = 25;

fileID = fopen('skyline2.in','w');
for i = 1:n
    x1 = ceil(rand*xmax);
    x2=x1;
    while x1==x2
        x2 = ceil(rand*xmax);
    end
    if x2<x1
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    end
    h = ceil(rand*ymax);
    fprintf(fileID,'%d %d %d %d\n',x1,h,x2,h);
end

fclose('all');