%% Define count for loops
global count
count = 1;
%% For first 4 contacts
%Input object center
object_center = [0, 0, 0];

%Input (x,y) for each contact
contact_1 = [-3, 0.5, 0];
contact_2 = [-1, 1.5, 0];
contact_3 = [1, 1.5, 0];
contact_4 = [0, -1.5, 0];
%contact_5 = [-3, -1.5, 0];

%Calculate R for all contacts based on (x,y) of each contact
R_1 = [0 0 1; 1 0 0; 0 1 0];
R_2 = [-1 0 0; 0 0 -1; 0 -1 0];
R_3 = R_2;
R_4 = [-1 0 0; 0 0 1; 0 1 0];
%%R_5 = R_4;

%Calculate G
G_1 = G_Function(object_center, contact_1, R_1);
G_2 = G_Function(object_center, contact_2, R_2);
G_3 = G_Function(object_center, contact_3, R_3);
G_4 = G_Function(object_center, contact_4, R_4);
%%G_5 = G_Function(object_center, contact_5, R_5);

G_T_Prime = [G_1; G_2; G_3; G_4];

%% Loops for the 5th contact
%We will have a total of 4 loops to run through the 4 sides of the object
Q_MSV = zeros(184,1);
Q_VEW = zeros(184,1);
Q_Iso = zeros(184,1);

%First Side   
for i = -3:0.1:3
    
    contact_5 = [i, -1.5, 0];
    R_5 = R_4;
    G_5 = G_Function(object_center, contact_5, R_5);
    G_T = [G_T_Prime; G_5];
    
    %Quality Metrics
    Q_MSV(count) = G_MSV(G_T);
    Q_VEW(count) = G_Vol(G_T);
    Q_Iso(count) = G_Iso(G_T);
    count = count + 1;
    
end

%Second Side   
for i = -1.5:0.1:1.5
    
    contact_5 = [3, i, 0];
    R_5 = [0 0 -1; 1 0 0; 0 -1 0];
    G_5 = G_Function(object_center, contact_5, R_5);
    G_T = [G_T_Prime; G_5];
    
    %Quality Metrics
    Q_MSV(count) = G_MSV(G_T);
    Q_VEW(count) = G_Vol(G_T);
    Q_Iso(count) = G_Iso(G_T);
    count = count + 1;
    
end

%Third Side   
for i = 3:-0.1:-3
    
    contact_5 = [i, -1.5, 0];
    R_5 = R_2;
    G_5 = G_Function(object_center, contact_5, R_5);
    G_T = [G_T_Prime; G_5];
    
    %Quality Metrics
    Q_MSV(count) = G_MSV(G_T);
    Q_VEW(count) = G_Vol(G_T);
    Q_Iso(count) = G_Iso(G_T);
    count = count + 1;
    
end

%Fourth Side   
for i = 1.5:-0.1:-1.5
    
    contact_5 = [i, -1.5, 0];
    R_5 = R_1;
    G_5 = G_Function(object_center, contact_5, R_5);
    G_T = [G_T_Prime; G_5];
    
    %Quality Metrics
    Q_MSV(count) = G_MSV(G_T);
    Q_VEW(count) = G_Vol(G_T);
    Q_Iso(count) = G_Iso(G_T);
    count = count + 1;
    
end
