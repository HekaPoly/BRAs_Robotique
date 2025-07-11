function [point] = sampling(starting_point,ending_point)
%SAMPLING: sample points randomly inside a 3D ellipsoid 
d=sqrt(sum((ending_point-starting_point).^2,'all')); % main axis for ellipsoid space
a=1.5*d;
b=1*d;
c=1*d;
sample=NaN(size(starting_point));
mid_point=(ending_point+starting_point)/2;
while true
    % Random sampling
    theta=rand(1)*pi();
    r=rand(1);
    phi=rand(1)*2*pi();
    sample(1)=a*sin(theta)*cos(phi)*r+mid_point(1);
    sample(2)=b*sin(theta)*sin(phi)*r+mid_point(2);
    sample(3)=c*cos(theta)*r+mid_point(3);
    point=sample+starting_point;
    % Verification if inside de ellipsoid
    if (((point(1)-mid_point(1))^2)/a^2+((point(2)-mid_point(2))^2)/b^2+((point(3)-mid_point(3))^2)/c^2)<=1
        break
    end
end
end

