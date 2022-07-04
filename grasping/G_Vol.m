function [Q_VEW] = G_Vol(G_T)
%Calculate G and G transpose
G = G_T';
%Calculate G*G^T
G_S = G * G_T;
%Calculate determinant
Q_VEW_Prime = det(G_S);
%Calculate square root of the value
Q_VEW = sqrt(Q_VEW_Prime);

end