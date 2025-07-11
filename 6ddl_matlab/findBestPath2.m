function [branch,paths,step] = findBestPath2(localisation,end_node,start_node,branch,paths,step)
% Tree exploration to recreate paths from start and end nodes.
% Loop to every single iteration of an end node 
for j=1:length(localisation)
    % Creation of a new branch for every new end node appartition        
    branch=branch+1;
    % Create the node in the path
    paths(branch,step)=end_node(localisation(j));
    while true
        % New node positionning in the tree and find the previous node in
        % the tree
        step=step+1;
        where=find(end_node==start_node(localisation(j)));
        % If the node found is the start, end
        if isempty(where)
            paths(branch,step)=start_node(localisation(j));
            break
        % If not, restart the process until it is the start
        else
           for k=1:length(where)
               [branch,paths,step]=findBestPath2(where,end_node,start_node,branch,paths,step);
           end
           break
        end
    end
    % Reset node positionning
    step=step-1;
end
end