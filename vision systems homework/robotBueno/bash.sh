#!/bin/bash

g++ funcion.cpp -o funcion -O3 
g++ regresion.cpp -o regresion -O3 -larmadillo -llapack -lblas
./funcion
./regresion
