function [data] = getCSVDataByGeneration(filename,metaPop)

raw = csvread(filename);
NGEN = length(metaPop);
data = zeros(NGEN,max(metaPop));
u = 1;
for gen = 1:NGEN
  v = metaPop(gen);  %first and last indecies
  data(gen,u:v) = raw(u:v);  %data of current gen
  u = v +1;
end

end