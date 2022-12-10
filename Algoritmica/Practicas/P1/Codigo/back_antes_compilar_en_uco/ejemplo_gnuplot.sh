#!/bin/bash

#OJO: adaptar las leyendas a los nombres de las variables. En el eje Y se miden tiempos y en el eje X es el tamaño del ejemplar.
cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "Numero de elementos"
set ylabel "Tiempo de ordenacion"
plot 'datosFinales.txt' using 1:2 t "Tiempos reales" w l, 'datosFinales.txt' using 1:3 t "Tiempos estimados" w l
_end_
