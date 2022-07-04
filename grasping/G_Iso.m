function [Q_Iso] = G_Iso(G_T)
%Calculate G and G transpose
G = G_T';
%Calculate G*G^T
G_S = G * G_T;
%Calculate eigen values of the matrix
G_Eigen = eig(G_S);
%Calculate sigma values
sigma = sqrt(G_Eigen);
%Calculate max and min values of sigma
sigma_min = min(sigma);
sigma_max = max(sigma);
%Calculate G_Iso
Q_Iso = sigma_min / sigma_max;

end