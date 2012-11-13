# 
set dgrid3d 5,5 
set pm3d
set style data dots
set xlabel "X - axis"
set ylabel "Y - aisx"
set zlabel "Temperature - K"
set terminal png 
set output 'Heat.png'
splot 'output.dat' notitle
