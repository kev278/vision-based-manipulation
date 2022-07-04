function [Q_MSV] = G_MSV(G_T)
%Calculate G and G transpose
G = G_T';
%Calculate G*G^T
G_S = G * G_T;
%Calculate eigen values of the matrix
G_Eigen = eig(G_S);
%Calculate sigma values
sigma = sqrt(G_Eigen);
%Calculate lowest value of sigma
Q_MSV = min(sigma);

end