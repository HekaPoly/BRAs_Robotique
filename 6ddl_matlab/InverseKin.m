function [theta_final] = InverseKin(pos_target,rot_target)

% Limites des moteurs des robots
robots_limits=[[-180,-25,-80,-180,-80];[180,130,80,180,80]];

% Création d'un vecteur contenant 20 points de départs aléatoires à partir 
% desquels on va trouver la solution selon les moindres carrés 
% (permet d'éviter les minimums locaux) 
theta0=[(robots_limits(2,:)-robots_limits(1,:)).*(rand([20,1]))+robots_limits(1,:)];

% Initialisation de la fonction d'erreur (voir fonction d'erreur
% (FonctionErreur))
fun=@(x) (FonctionErreur(pos_target,rot_target,x));

% Itération sur les 100 points de départs aléatoires
for i=1:(size(theta0,1))
    % Fonction trouvant la meilleur selon selon les moindres carrés
    thetaC(i,:) = lsqnonlin(fun, theta0(i,:),robots_limits(1,:),robots_limits(2,:),optimset('display','off'));
    % Fonction permettant de trouver la position et l'orientation 
    % reliée à cette solution (voir cinématique direct (DirectKin))
    [pos_final(i,:,:),rot_final(i,:,:)]=DirectKin(thetaC(i,:));
    % Comparaison avec la position cible
    E_final_pos(i,:)=pos_final(i,:,size(pos_final,3))-pos_target;
    E_final_rot(i,:)=rot_final(i,:,size(rot_final,3))-rot_target;
end
% Détermination de la meilleure solution parmi celles obtenues à partir des
% 100 points aléatoires
[~,I]=min(sum(abs(E_final_pos)+abs(E_final_rot),2),[],1);
theta_final=thetaC(I,:);


