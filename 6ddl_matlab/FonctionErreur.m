function [E] = FonctionErreur(pos_target,rot_target,moteurs_actuel)
% Fonction permettant de trouver la position et l'orientation reliée à 
% cette solution (voir cinématique direct (PositionActuateur))
[Pos_d,Orient_d]=DirectKin(moteurs_actuel);
% Vecteur contenant la différence entre la position et l'orientation voulue 
% et obtenue 
Pos_d=Pos_d(:,:,5);
Orient_d=Orient_d(:,:,5);
E(1) = abs(Pos_d(1) - pos_target(1)); % shoulder position
E(2) = abs(Pos_d(2) - pos_target(2)); % elbow position
E(3) = abs(Pos_d(3) - pos_target(3)); % wrist position

E(4) = abs(Orient_d(1) - rot_target(1)); % shoulder rotation
E(5) = abs(Orient_d(2) - rot_target(2)); % elbow rotation
E(6) = abs(Orient_d(3) - rot_target(3)); % wrist rotation
end

