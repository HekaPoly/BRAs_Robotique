function [stepSize] = calculateGradient(current_point,end_point,obstacles,stepSize,I)
% Variable initialization
ka=0.1*stepSize;
kd=0.1*stepSize;
d=50;
d_end=norm(end_point-current_point(I,:));

% Attrative and repulsive forces calculations
F_attract=ka*d_end*gradient(current_point(I,:));
F_repulsion=0;
% Distance to obstacle
for i=1:size(obstacles,3)
    d_obstacle(i,:)=min(sqrt(sum((current_point(I,:)-obstacles(:,:,i)).^2,1)));
end
% Stepsize ajustement if close enough to an obstacle
if any(d_obstacle<d)
  for d_obstacled=d_obstacle'
    if d_obstacled<d
        F_repulsion=F_repulsion+kd*((1/d_obstacled)-(1/d))*(1/d_obstacled)*gradient(current_point(I,:));
    end
  end
  stepSize=log(norm(F_attract)*((2*norm(F_repulsion)/kd)^(1/2)+1/d));
end
end
