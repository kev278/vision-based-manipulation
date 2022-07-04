function [G_T] = G_Function(object_center, contact_location, R)

%% Basic information

%Input object center
%%object_center = [0, 0, 0];

%Input (x,y) for each contact
%%contact_location = [-3, 0.5, 0];

%Define Contact Matrix
Hf = [1 0 0; 0 1 0; 0 0 1];  %%Hard Contact
Hm = zeros(3, 3);
O = zeros(3, 3);
H = [Hf O; O Hm];
%% Calculation for Pi
%Calculate (c-o) for all the contacts
C_O = contact_location - object_center;
%C_O = C_O;
%Calculate all S matrices
S = vect2skew(C_O);  %using Robotics toolbox by Neelotpal Dutta
S = S';

%Calculate all P matrices
I = eye(3);
P = [I S; O I];

%% Calculation for R
%Calculate R for all contacts based on (x,y) of each contact
%%R = [0 0 1; 1 0 0; 0 1 0];

%Calculate Rn
R_N = [R O; O R];


%% Calculation for G
%Rn*P will give G, do this for all contacts
G_Tilde = R_N * P;
G_T = H * G_Tilde;

end