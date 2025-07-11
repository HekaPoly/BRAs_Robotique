function [Pos,Orient] = DirectKin(AngleMoteurs)

% Matrice de transformation des répères d'une membrure à l'autre et prenant
% en compte l'angle du moteur voulu 
R1_0 = Rotxyz([0 0 AngleMoteurs(1)]); % Membrure 1 (Reprère global même chose que repère 1)
R2_1 = Rotxyz([-90 0 AngleMoteurs(2)]); % Membrure 2
R3_2 = Rotxyz([0 0 AngleMoteurs(3)]); % Membrure 3
R4_3 = Rotxyz([0 90 AngleMoteurs(4)]); % Membrure 4
R5_4 = Rotxyz([0 -90 AngleMoteurs(5)]); % Membrure 5

% Translation d'un repère à un autre pour la position de base
% (0,0,0,0,0)deg
P1_0 = [0 ; 0 ; 0]; % Membrure 1 (Reprère global même chose que repère 1)
P2_1 = [0 ; 0 ; 100]; % Membrure 2
P3_2 = [77.558 ; 0; 40.239];% Membrure 3
P4_3 = [56 ; 0 ; 0]; % Membrure 4
P5_4 = [0 ; 0 ; 33]; % Membrure 5

% Matrices de transformation globales pour chaque repère 
T1_0 = [R1_0 P1_0 ; 0 0 0 1]; % Membrure 1 (Reprère global même chose que repère 1)
T2_1 = [R2_1 P2_1 ; 0 0 0 1]; % Membrure 2
T3_2 = [R3_2 P3_2 ; 0 0 0 1]; % Membrure 3
T4_3 = [R4_3 P4_3 ; 0 0 0 1]; % Membrure 4
T5_4 = [R5_4 P5_4 ; 0 0 0 1]; % Membrure 5
T_i=cat(3,T1_0,T2_1,T3_2,T4_3,T5_4);
Tt=eye([4,4]);
% Position et orientation de chaque membrure obtenu par transformations
% successives du repère 
for i=1:5
    Tt=Tt*T_i(:,:,i);
    Pos(:,1,i)=[Tt(1,4) ;Tt(2,4) ;Tt(3,4)] ;
    Rott = [Tt(1,1) Tt(1,2) Tt(1,3); Tt(2,1) Tt(2,2) Tt(2,3) ; Tt(3,1) Tt(3,2) Tt(3,3)];
    Orient(:,1,i) = rad2deg(rotm2eul(Rott, "XYZ"));
end


end


