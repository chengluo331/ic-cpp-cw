B=[3,1,2,5;
1,1,3,7;
2,3,2,4;
5,7,4,2];

n=10000;
A=eye(n)*2+diag(ones(n-1,1).*-1,1)+diag(ones(n-1,1).*-1,-1)+diag(-1,n-1)+diag(-1,1-n);
D=diag([5.0,7.0,4.0,2.0])

eb=eig(B);
ea=eig(A);
ed=eig(D);

eb
ea
ed