function [mu,phn,px,py,nghs,pars] = getPopulationData(m,c,x,y,n,p,mutn,phtn,phxn,phyn,nghn,parn,population)

mu = [];
phn = [];
px = [];
py = [];
nghs = [];
pars = [];

if(m==true) mu = getCSVDataByGeneration(mutn,population); end
if(c==true) phn = getCSVDataByGeneration(phtn,population); end
if(x==true) px = getCSVDataByGeneration(phxn,population); end
if(y==true) py = getCSVDataByGeneration(phyn,population); end
if(n==true) nghs = getCSVDataByGeneration(nghn,population); end
if(p==true) pars = getCSVDataByGeneration(parn,population); end

end