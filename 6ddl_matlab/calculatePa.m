function [Pa] = calculatePa(Ps,Itr,Max_itr)
    Pa=1-(0.5/Ps+((Max_itr-Itr)/Max_itr*0.4/Ps));
end

