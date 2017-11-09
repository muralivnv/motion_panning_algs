set term qt 0 position 100,100
plot 'create_spiral_traj_data.dat' u 1:2 w l t 'reference'
set grid
set xlabel 'X(m)' 
set ylabel 'Y(m)' 
replot
