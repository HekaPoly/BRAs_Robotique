function [node,start_node,end_node,path_no_collision] = preliminaryTree(start_point,end_point,obstacles)
% Generate a RRT*-connect algorithm with gradient-based step ajustement and
% robot kinematics collision verification. Returns the position of the 
% nodes in the tree and the start and end nodes of each branch in the tree
% Also returns the path with no collision as a combination of nodes

k=300; % Max number of iteration
% Initialization of variables
node=[start_point]; 
Ps=1; 
pa=calculatePa(Ps,1,k);
Ss=1;
counter=1;
probe=0;
seg=linspace(0,1,1000);

%% Main loop for tree generation
for i=2:k
    clear segment
    % Random tresholding for ending the algorithm
    p=rand(1);
    if p<pa
        xrand=end_point;
        % Nearest node in the tree determination
        [~,I]=min(sqrt(sum((node-xrand).^2,2)));
        % Segment between new node and nearest node for collision detection
        segment=node(I,:)+(xrand-node(I,:)).*seg';
    else
        % Random sampling
        xrand=sampling(start_point,end_point);
        % Nearest node in the tree determination
        [~,I]=min(sqrt(sum((node-xrand).^2,2)));
        % Segment between new node and nearest node for collision detection
        % and gradient based stepsize ajustment
        stepsize=calculateGradient(node,end_point,obstacles,sqrt(sum((end_point-start_point).^2))/10,I);
        xrand=node(I,:)+(xrand-node(I,:))*stepsize/norm(xrand-node(I,:));
        segment=node(I,:)+(xrand-node(I,:)).*seg';
        
    end
    % % Joint position acquistion
    [actuateurs]=InverseKin(xrand,[-90,0,0]);
    [positions_membrures,~]=DirectKin(actuateurs);
    % % Segments creation for obstacle-robot collision detection 
    for j=2:size(positions_membrures,3)
        segment(size(segment,1)+1:size(segment,1)+1000,:)=positions_membrures(:,:,j-1)'+(positions_membrures(:,:,j)'-positions_membrures(:,:,j-1)').*seg';
    end
    % Loop for obstacle-robot collision detection
    for j=1:size(obstacles,3)
        % Condition for collision
        if any(inhull(segment,obstacles(:,:,j),convhulln(obstacles(:,:,j))))
           break
        % If no collision detected
        elseif j==size(obstacles,3)
            % New node creation
            node(counter+1,:)=xrand;
            % Path in the tree update
            start_node(counter)=I;
            end_node(counter)=counter+1;
            counter=counter+1;
            Ss=Ss+1;
            % End condition
            if xrand==end_point
                probe=1;
            end
        end
    end
    % Adjust dynamic random thresholding 
    pa=calculatePa(Ss/i,i,k);
    % Verify if end condition has been met
    if probe==1
        break
    end
end
%% Path selection algorithm
% Remove solutions present 2 times
uniqueSolutions=unique(end_node);
% Initilize variables
branch=0;
paths=[];
% For every end of a branch, find all the nodes before it and linked them
% together
for i=1:length(uniqueSolutions)
    % If there is still other nodes before it, don't stop searching
    if ~isempty(find(uniqueSolutions(i)==start_node, 1))
        continue
    end
    % Find positions of end node in the tree
    localisation=find(end_node==uniqueSolutions(i));
    step=1;
    % Find all the branches in the tree 
    [branch,paths,~]=findBestPath2(localisation,end_node,start_node,branch,paths,step);
    % Find the start of every branch in the tree and sort them in order
    [row,~]=find(paths==1);
    row=sort(row);
    path_final=zeros([length(row),size(paths,2)]);
    % Path reconstruction (every branch of the tree)
    for p=1:length(row)
        if p==1
            path_final(p,:)=sum(paths(1:row(p),:));
        else
            path_final(p,:)=sum(paths(row(p-1)+1:row(p),:));
        end
    end
end
% Final branch identification (which end with the end point)
[~,loc]=ismember(node,end_point,'rows');
loc=find(loc==1);
good_branch=1;
% Best branch path reconstruction
for p=size(path_final,1):-1:1
    if any(path_final(p,1)==loc)
        path_final_wow(good_branch,:)=path_final(p,:);
        good_branch=good_branch+1;
    end  
end
zero=find(path_final_wow==0);
if ~isempty(zero)
   path_final_wow=path_final_wow(1:zero(1)-1); 
end
path_no_collision=NaN([size(path_final_wow,2)-1,3]);
for nodes=(size(path_final_wow,2):-1:1)
    if path_final_wow(nodes)==0
        continue
    else
        path_no_collision(size(path_final_wow,2)-nodes+1,:)=node(path_final_wow(nodes),:);
    end
end
end

