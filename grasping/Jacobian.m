J1 = [0.05 0.025; 0 -0.043; 0 0; 0 0; 0 0; 1 1];
J2 = [0.05 0.025; 0 0.043; 0 0; 0 0;0 0; 1 1];
Hf = [1 0 0; 0 1 0; 0 0 1];  %%Hard Contact
Hm = zeros(3, 3);
O = zeros(3, 3);
H = [Hf O; O Hm];
J1_T = H * J1;
J2_T = H * J2;

J = [J1; J2];
twist = [0.2 0.2 0 0 0 0.5]';
G_T = G;
G_inv = pinv(G_T);
hand_jacobian = G_inv * J;

J_inv = pinv(J);
q = J_inv * G * twist;