%% Basic information
%Input object center
object_center = [0, 0, 0];
%object_center_prime = [object_center; object_center; object_center; object_center, object_center];
%Input number of contacts
number_of_contacts = 5;
%Input (x,y) for each contact
contact_1 = [-3, 0.5, 0];
contact_2 = [-1, 1.5, 0];
contact_3 = [1, 1.5, 0];
contact_4 = [0, -1.5, 0];
contact_5 = [-3, -1.5, 0];
%contact = [contact_1; contact_2; contact_3; cotnact_4; contact_5];
%Define Contact Matrix
Hf = [1 0 0; 0 1 0; 0 0 1];
Hm = zeros(3, 3);
O = zeros(3, 3);
H = [Hf O; O Hm];
%% Calculation for Pi
%Calculate (c-o) for all the contacts
% C_1 = [contact_1; object_center];
% C_2 = [contact_2; object_center];
% C_3 = [contact_3; object_center];
% C_4 = [contact_4; object_center];
% C_5 = [contact_5; object_center];

% C_1 = pdist(C_1, 'eucledian'); 
% C_2 = pdist(C_2, 'eucledian');
% C_3 = pdist(C_3, 'eucledian');
% C_4 = pdist(C_4, 'eucledian');
% C_5 = pdist(C_5, 'eucledian');

%C_N = contact - object_center_prime;

%Calculate all S matrices
S_1 = contact_1';
S_1 = vect2skew(S_1);
S_1 = S_1';

S_2 = contact_2';
S_2 = vect2skew(S_2);
S_2 = S_2';

S_3 = contact_3';
S_3 = vect2skew(S_3);
S_3 = S_3';

S_4 = contact_4';
S_4 = vect2skew(S_4);
S_4 = S_4';

S_5 = contact_5';
S_5 = vect2skew(S_5);
S_5 = S_5';
%Calculate all P matrices
I = eye(3);
P_1 = [I S_1; O I];
P_2 = [I S_2; O I];
P_3 = [I S_3; O I];
P_4 = [I S_4; O I];
P_5 = [I S_5; O I];
%% Calculation for R
%Calculate R for all contacts based on (x,y) of each contact
R_1 = [0 0 1; 1 0 0; 0 1 0];
R_2 = [-1 0 0; 0 0 -1; 0 -1 0];
R_3 = R_2;
R_4 = [-1 0 0; 0 0 1; 0 1 0];
R_5 = R_4;

%Calculate Rn
R_1_N = [R_1 O; O R_1];
R_2_N = [R_2 O; O R_2];
R_3_N = [R_3 O; O R_3];
R_4_N = [R_4 O; O R_4];
R_5_N = [R_5 O; O R_5];

%% Calculation for G
%Rn*P will give G, do this for all contacts
G_1 = H * R_1_N * P_1;
G_2 = H * R_2_N * P_2;
G_3 = H * R_3_N * P_3;
G_4 = H * R_4_N * P_4;
G_5 = H * R_5_N * P_5;
%Concat all G to form Gi
G = [G_1; G_2; G_3; G_4; G_5];

