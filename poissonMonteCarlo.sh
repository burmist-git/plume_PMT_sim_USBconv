#!/bin/bash

make poissonMonteCarlo;
time ./poissonMonteCarlo 0 0.0799314938 1.0 200000 poissonMonteCarlo_0pe_s.root
time ./poissonMonteCarlo 0 0.0799314938 1.0 1000000 poissonMonteCarlo_0pe_s_big.root
