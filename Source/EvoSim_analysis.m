%% EvoSim_analysis.m
%
% This acts as the main script for analyses. Here, a variety of 
% analysis functions may be inserted.
% -Adam D Scott
clear; clc;

%% options for loading (1=yes, 0=no)
run = 1002; %which run
m = 1; %mutabilities
c = 0; %
x = 0; %x-phenotype
y = 0; %y-phenotype
n = 0; %
p = 0;
k = 1;
t = 1;
i = 0;
d = 1;

%%
fn = ['_EvoSim_'];
rn = int2str(run);
base_name = [fn rn '.txt'];

fitn = ['fitness' base_name];
mlsn = ['shifted' base_name];

popn = ['population' base_name];
mutn = ['mutability' base_name];
phtn = ['phenotypes' base_name];
pxn = ['phenotypesX' base_name];
pyn = ['phenotypesY' base_name];
nghn = ['neighbors' base_name];
parn = ['parents' base_name];

kctn = ['kill' base_name];
timn = ['times' base_name];

gnsn = ['genus' base_name];
spin = ['species_indivs' base_name];
spdn = ['species_details' base_name];

%%
ls = csvread(fitn);
landscape = ls(:,1:size(ls,1));
% ss = csvread(mlsn);
% shiftedscape = ss(:,1:size(landscape,1));

%%
population = csvread(popn);
[mu,pht,px,py,ngh,par] = getPopulationData(m,c,x,y,n,p,mutn,phtn,pxn,pyn,nghn,parn,population);

%%
genus = csvread(gnsn);
if i==1
  spp = getCSVDataByGeneration(spin,genus);
end
if d==1
  spd = csvread(spdn);
end

%%
surf(landscape);
hold on;
u = 1;
v = 0;
for asdf = 1:length(genus)
v = genus(asdf);
spdg = spd(u:v,:);
plot(spdg(:,2),spdg(:,3),'x');
spc(asdf) = getframe;
u = u +v;
end

  %% Some old and incomplete code
% ls = csvread(fitn);
% landscape = ls(:,1:(size(ls,2)-1));  %final state of landscape
% % shsc = csvread(mlsn);
% % shiftedscape = shsc(:,1:(size(shsc,2)-1));  %previous states of landscape
% landhistory = [landscape];% shiftedscape];  %every state of landscape
% phenotypes = csvread(phtn);  %[phenotypex phenotypey]
% % phenotypesX = csvread(phxn);  %phenotypesX
% % phenotypesY = csvread(phyn);  %phenotypesY
% mutability = csvread(mutn);  %mutabilities (just like trace_noise)
% neighbors = csvread(nghn);  %[nearest neighbor (& second nearest neighbor)]
% parents = csvread(parn);  %[hereditary parent (& helping parent)]
% species_details = csvread(spdn);  %[size centroidx centroidy density]
% species_indivs = csvread(spin);  %list indivs in species by row
% population = csvread(popn);  %total population
% genus = csvread(gnsn);  %num_clusters
% kills = csvread(kctn);  %kill counts (OP, RR, CJ)
% times = csvread(timn);  %time per main steps 
% %(setNeighbors,speciation,centroids&densities,reproduction,NicheControl,
% %RussianRoulette,CliffJumpers,shiftTheLandscape,...raw pop size,CJ,OP,RR)
%   %%
% NGEN = size(population,1);  %total number of generations
% ap = 0;  %sum of previous populations
% umu = [];  %list unique mutabilities
% amu = [];  %list average mutability each generation
% sdmu = [];  %list standard deviation mutability each generation
% gotit = 0;  %check if output is correct
% 
% %% ANALYSIS BY SPECIES
% % for sp = 2:size(genus,1)
% %   fg = genus(sp-1);  sg = genus(sp);
% %   sdx = species_details(fg:sg,2);  sdy = species_details(fg:sg,3);
% %   
% 
% %% INDIVS WITHIN SPECIES
% % for sp = 1:size(genus,1)
% %   for in = 1:
% %     spi = species_indivs(
% %   end
% 
% %% PLOT SPECIES CENTROID LOCATIONS
% %   figure(1);
% %   plot(sdx,sdy,'x');
% %   SD(sp-1) = getframe;
% % end
% 
% %% ANALYSIS BY GENERATION
% fn = 1;
% for gen = 1:NGEN
%   gen
%   ps = population(gen);  %current generation
%   u = ap+1;  v = ap+ps;  %first and last indecies
%   px = phenotypes(u:v,1);  %x-phenotype coordinate of current gen
%   py = phenotypes(u:v,2);  %y-phenotype coordinate of current gen
% %   px = phenotypesX(u:v);  %x-phenotype coordinate of current gen
% %   py = phenotypesY(u:v);  %y-phenotype coordinate of current gen
%   n1 = neighbors(u:v,1);  %nearest neighbors of current gen
%   n2 = neighbors(u:v,2);  %second nearest neighbor of current gen
%   p1 = parents(u:v,1);  %passer parents of current gen
%   p2 = parents(u:v,2);  %helper parents of current gen
%   mu = mutability(u:v);  %mutabilities of current gen
%   all = [[0:ps-1]' n1 n2];  %reference with neighbors of current gen
% 
% %% 3-DIMENSIONAL VIEW OF INDIVS
% %   loc = [px py];
% %   floc = round(loc);
% %   for j = 1:size(floc,1)
% %     if floc(j,1)==0 || floc(j,2)==0
% %       z = find(floc==0);
% %       floc(z) = 1;
% %     end
% %     phenoscape(ap+j,3) = landscape(floc(j,1),floc(j,2));
% %   end
% %   axis([0 45 0 45]);
% %   plot(phenotypes(u:v,1),phenotypes(u:v,2),'x');
% %   F(gen) = getframe;
% %   phenoscape(u:v,1) = phenotypes(u:v,1); 
% %   phenoscape(u:v,2) = phenotypes(u:v,2);
%   
% %% PLOT NORMALIZED NEIGHBOR1 BY NEIGHBOR2
%   sn = population(gen);
%   n1 = neighbors(fn:sn,1)/sn;  n2 = neighbors(fn:sn,2)/sn;
%   figure(2);
%   plot(n1,n2,'x');
%   hold on;
%   NB(gen) = getframe;
%   fn = sn +1;
% %% RECORD UNIQUE MUTABILITIES AND AVERAGE MUTABILITY
%   umu = [umu size(unique(mu),1)];
%   amu = [amu mean(mu)];
%   sdmu = [sdmu std(mu)];
%   
% %% CHECK PROPER NEIGHBOR ASSIGNMENTS
% %   for i=1:size(px,1) %for each indiv
% %     d = sqrt((px(:)-px(i)).^2 + (py(:)-py(i)).^2); %find the distance to all other babies
% %     sort_distance = sort(d); %sort the distances
% %       %%
% %     nn(i,1) = find(d==sort_distance(1));
% %     nn(i,2) = find(d==sort_distance(2)); %find the closest baby (besides oneself) and record it in column 2.
% %     nn(i,3) = find(d==sort_distance(3)); %find the 2nd closest baby (besides oneself) and record
% %     it in column 3.
% %   end 
% %   if nn(:,2)==all(:,2)
% %     gotit = gotit +1;
% %   end
% %   if nn(:,3)==all(:,3)
% %     gotit = gotit +1;
% %   end
% 
%   ap = ps +ap;  %update sum of previous populations
% end
% 
% %% Plot average mu with std
% figure(10);
% errorbar(amu,sdmu);
% 
% %% MAKE SOME MOVIES!
% % movie(SD,1,3);
% % movie(F,1,3);
% % movies(NB,1,3);
% 
% %% PLOT LANDSCAPES
% % mesh(landscape);
% % mesh(shiftedscape);
% % surf(landscape);
% % surf(shiftescape);
% % mesh(landhistory);
% % surf(landhistory);