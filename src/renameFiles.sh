#!/bin/sh

for i in `find ./ -type d -maxdepth 10 -mindepth 1`; do
   cd $i
   echo $i	
   rename -v -n 's/Painter/TourDeMonde/' ./*Painter*
   rename -v -n 's/TourDeMonde/Painter/' ./*Painter*
   rename -v -n 's/file_\d{1,3}/upl/' file_*.png
done
