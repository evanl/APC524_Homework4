# 
set dgrid3d 256,256
set pm3d
set style data dots
set xlabel "X - axis"
set ylabel "Y - axis"
set zlabel "Temperature - K"
set terminal png 
set output 'Heat.png'
splot 'output.dat' notitle
