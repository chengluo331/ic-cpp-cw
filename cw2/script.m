clear;
in = load('skyline.in'); 
j=1;

for i=1:size(in,1)
    x1 = in(i,1);
    y1 = in(i,2);
    x2 = in(i,3);
    y2 = in(i,4);
    
    m(j,1)=x1;
    m(j,2)=0;
    j=j+1;
    m(j,1)=x1;
    m(j,2)=y1;
    j=j+1;
    m(j,1)=x2;
    m(j,2)=y2;
    j=j+1;
    m(j,1)=x2;
    m(j,2)=0;
    j=j+1;
end
plot(m(:,1), m(:,2), 'b.-')
hold on;
s = load('skyline.out'); plot(s(:,1), s(:,2), 'r.--');hold on;plot(s(:,1), s(:,2),'*')