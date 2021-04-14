#Date        : Fri Apr  9 11:32:58 CEST 2021
#Autor       : Leonid Burmistrov
#Description : Simple reminder-training example joblib.

ROOTCFLAGS  = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS    = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS   = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)

CXX  = g++
CXX += -I./

CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += $(ROOTLDFLAGS)

.PHONY: printmakeinfo clean printhelp

## Print make info 
printmakeinfo:
	$(info CXX          = "$(CXX)")
	$(info CXXFLAGS     = "$(CXXFLAGS)")

## Make the convertor 
convUSBHistos2root: convUSBHistos2root.C
	$(CXX) -o $@ $< $(CXXFLAGS)

## Make the monte carlo simulation
poissonMonteCarlo: poissonMonteCarlo.C
	$(CXX) -o $@ $< $(CXXFLAGS)

## Copy executables for multiple simulation 
cpPoissonMonteCarlo:
	cp poissonMonteCarlo poissonMonteCarlo01
	cp poissonMonteCarlo poissonMonteCarlo02
	cp poissonMonteCarlo poissonMonteCarlo03
	cp poissonMonteCarlo poissonMonteCarlo04
	cp poissonMonteCarlo poissonMonteCarlo05
	cp poissonMonteCarlo poissonMonteCarlo06
	cp poissonMonteCarlo poissonMonteCarlo07
	cp poissonMonteCarlo poissonMonteCarlo08
	cp poissonMonteCarlo poissonMonteCarlo09

## Clean from unused files and others (created by system)
clean:
	rm -rf poissonMonteCarlo
	rm -rf poissonMonteCarlo01
	rm -rf poissonMonteCarlo02
	rm -rf poissonMonteCarlo03
	rm -rf poissonMonteCarlo04
	rm -rf poissonMonteCarlo05
	rm -rf poissonMonteCarlo06
	rm -rf poissonMonteCarlo07
	rm -rf poissonMonteCarlo08
	rm -rf poissonMonteCarlo09
	rm -rf convUSBHistos2root
	rm -rf *~

.DEFAULT_GOAL := printhelp

## Self-Documented Makefile : print descriptions of the described commands
printhelp:
	@echo "$$(tput bold)Available rules:$$(tput sgr0)"
	@echo
	@sed -n -e "/^## / { \
                h; \
                s/.*//; \
                :doc" \
                -e "H; \
                n; \
                s/^## //; \
                t doc" \
                -e "s/:.*//; \
                G; \
                s/\\n## /---/; \
                s/\\n/ /g; \
                p; \
        }" ${MAKEFILE_LIST} \
        | LC_ALL='C' sort --ignore-case \
        | awk -F '---' \
                -v ncol=$$(tput cols) \
                -v indent=19 \
                -v col_on="$$(tput setaf 6)" \
                -v col_off="$$(tput sgr0)" \
        '{ \
                printf "%s%*s%s ", col_on, -indent, $$1, col_off; \
                n = split($$2, words, " "); \
                line_length = ncol - indent; \
                for (i = 1; i <= n; i++) { \
                        line_length -= length(words[i]) + 1; \
                        if (line_length <= 0) { \
                                line_length = ncol - indent - length(words[i]) - 1; \
                                printf "\n%*s ", -indent, " "; \
                        } \
                        printf "%s ", words[i]; \
                } \
                printf "\n"; \
        }'
