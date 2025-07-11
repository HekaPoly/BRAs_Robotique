close all
clear all
% Variable initialization
start_point=[100,50,0];
end_point=[-60,-120,30];
% Obstacles
[xx,yy,zz]=meshgrid(linspace(20,45,2),linspace(15,25,2),linspace(0,30,2));
[xx1,yy1,zz1]=meshgrid(linspace(-35,-74,2),linspace(10,100,2),linspace(0,60,2));
[xx2,yy2,zz2]=meshgrid(linspace(47,60,2),linspace(-30,-100,2),linspace(0,40,2));
[xx3,yy3,zz3]=meshgrid(linspace(-25,25,2),linspace(-42,-60,2),linspace(0,55,2));
% [xx4,yy4,zz4]=meshgrid(linspace(500,525,2),linspace(600,800,2),linspace(200,300,2));
% [xx5,yy5,zz5]=meshgrid(linspace(650,750,2),linspace(600,625,2),linspace(150,200,2));
% [xx6,yy6,zz6]=meshgrid(linspace(500,550,2),linspace(600,650,2),linspace(300,400,2));

obstacles=[xx(:),yy(:),zz(:)];
obstacles1=[xx1(:),yy1(:),zz1(:)];
obstacles2=[xx2(:),yy2(:),zz2(:)];
obstacles3=[xx3(:),yy3(:),zz3(:)];
% obstacles4=[xx4(:),yy4(:),zz4(:)];
% obstacles5=[xx5(:),yy5(:),zz5(:)];
% obstacles6=[xx6(:),yy6(:),zz6(:)];

k=convhulln(obstacles);
k1=convhulln(obstacles1);
k2=convhulln(obstacles2);
k3=convhull(obstacles3);
% k4=convhull(obstacles4);
% k5=convhull(obstacles5);
% k6=convhull(obstacles6);
% [xx7,yy7,zz7]=meshgrid(linspace(600,800,2),linspace(600,850,2),linspace(400,500,2));
% [xx8,yy8,zz8]=meshgrid(linspace(250,500,2),linspace(850,950,2),linspace(400,600,2));
% [xx9,yy9,zz9]=meshgrid(linspace(800,950,2),linspace(250,500,2),linspace(400,625,2));
% [xx10,yy10,zz10]=meshgrid(linspace(825,875,2),linspace(850,925,2),linspace(600,650,2));
% [xx11,yy11,zz11]=meshgrid(linspace(600,650,2),linspace(800,850,2),linspace(600,700,2));
% [xx12,yy12,zz12]=meshgrid(linspace(625,700,2),linspace(700,800,2),linspace(700,800,2));
% [xx13,yy13,zz13]=meshgrid(linspace(750,900,2),linspace(700,750,2),linspace(700,800,2));
% 
% obstacles7=[xx7(:),yy7(:),zz7(:)];
% obstacles8=[xx8(:),yy8(:),zz8(:)];
% obstacles9=[xx9(:),yy9(:),zz9(:)];
% obstacles10=[xx10(:),yy10(:),zz10(:)];
% obstacles11=[xx11(:),yy11(:),zz11(:)];
% obstacles12=[xx12(:),yy12(:),zz12(:)];
% obstacles13=[xx13(:),yy13(:),zz13(:)];
% 
% k7=convhulln(obstacles7);
% k8=convhulln(obstacles8);
% k9=convhulln(obstacles9);
% k10=convhull(obstacles10);
% k11=convhull(obstacles11);
% k12=convhull(obstacles12);
% k13=convhull(obstacles13);
counter=1;

% Start timer
tic
obstacle=cat(3,obstacles,obstacles1,obstacles2,obstacles3);
% Generating the tree
[node,start_node,end_node,best_path]=preliminaryTree(start_point,end_point,obstacle);


% End timer
total_time(counter)=toc;
nb_node(counter)=size(best_path,1);
nb_itr(counter)=length(start_node);

duration_moyenne=mean(total_time);
duration_std=std(total_time);
nb_node_moyen=mean(nb_node);
nb_node_std=std(nb_node);
nb_itr_moyen=mean(nb_itr);
nb_itr_std=std(nb_itr);
fprintf('Temps moyen \t Temps écart-type \t Nombre node moyen \t écart-type \t itérations \t écart-type \n')
fprintf('%f \t %f \t %f \t %f \t %f \t %f \n',duration_moyenne,duration_std,nb_node_moyen,nb_node_std,nb_itr_moyen,nb_itr_std)
% Tree display with best path and robot
hold on
for i=2:size(best_path,1)
        % Best path
        plot3([best_path(i-1,1),best_path(i,1)],[best_path(i-1,2),best_path(i,2)],[best_path(i-1,3),best_path(i,3)],color='g',LineWidth=7);
        % Robot
        theta=InverseKin(best_path(i,:),[-90,0,0]);
        actuateurs=DirectKin(theta);
        for j=2:size(actuateurs,3)
            plot3([actuateurs(1,:,j-1),actuateurs(1,:,j)],[actuateurs(2,:,j-1),actuateurs(2,:,j)],[actuateurs(3,:,j-1),actuateurs(3,:,j)])
            colororder({'red','blue','black','blue','black'})
        end
end

%ellipsoid(0.5,0,0,1.5,0.4,0.4,FaceColor='None')

[x,y,z] = meshgrid(-2:0.1:2,-2:0.1:2,-2:0.1:2);
% Obstacles
trisurf(k,xx,yy,zz)
trisurf(k1,xx1,yy1,zz1)
trisurf(k2,xx2,yy2,zz2)
trisurf(k3,xx3,yy3,zz3)
% trisurf(k4,xx4,yy4,zz4)
% trisurf(k5,xx5,yy5,zz5)
% trisurf(k6,xx6,yy6,zz6)
% trisurf(k7,xx7,yy7,zz7)
% trisurf(k8,xx8,yy8,zz8)
% trisurf(k10,xx10,yy10,zz10)
% trisurf(k11,xx11,yy11,zz11)
% trisurf(k12,xx12,yy12,zz12)
% trisurf(k9,xx9,yy9,zz9)
% trisurf(k13,xx13,yy13,zz13)

% All the tree
for i=1:length(start_node)
    plot3([node(start_node(i),1),node(end_node(i),1)],[node(start_node(i),2),node(end_node(i),2)],[node(start_node(i),3),node(end_node(i),3)],color='r')
end
% End and start point
plot3([start_point(1);end_point(1)],[start_point(2);end_point(2)],[start_point(3);end_point(3)],LineStyle="none",Marker="o")
axis equal
view([-1,-1,1])
hold off
    