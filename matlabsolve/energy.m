function [objective,gradient] = energy(x)

load('H.mat','H');
load('g.mat','g');

objective = 0.5*x'*H*x+g'*x;

if nargout > 1
    gradient = H*x+g;
end