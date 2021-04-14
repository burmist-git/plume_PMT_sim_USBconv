#!/bin/bash

make poissonMonteCarlo;
make cpPoissonMonteCarlo;
time ./poissonMonteCarlo01 0 1 1.0 40000 poissonMonteCarlo_1pe_s.root
