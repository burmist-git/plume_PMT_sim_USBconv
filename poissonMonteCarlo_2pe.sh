#!/bin/bash

make poissonMonteCarlo;
make cpPoissonMonteCarlo;
time ./poissonMonteCarlo02 0 2 1.0 590 poissonMonteCarlo_2pe_s.root

