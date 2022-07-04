%Input object center
object_center = [0, 0, 0];

%Input (x,y) for each contact
contact_1 = [-3, 0.5, 0];
contact_2 = [-1, 1.5, 0];
contact_3 = [1, 1.5, 0];
contact_4 = [0, -3, 0];
contact_5 = [-3, -1.5, 0];

%Calculate R for all contacts based on (x,y) of each contact
R_1 = [0 0 1; 1 0 0; 0 1 0];
R_2 = [-1 0 0; 0 0 -1; 0 -1 0];
R_3 = R_2;
R_4 = [-1 0 0; 0 0 1; 0 1 0];
R_5 = R_4;

%Calculate G
%G = G_Function([0, 0, 0], [-3 0.5 0], [0 0 1; 0 1 0; 1 0 0])
G_1 = G_Function(object_center, contact_1, R_1);
G_2 = G_Function(object_center, contact_2, R_2);
G_3 = G_Function(object_center, contact_3, R_3);
G_4 = G_Function(object_center, contact_4, R_4);
G_5 = G_Function(object_center, contact_5, R_5);

G_T = [G_1; G_2; G_3; G_4; G_5];

