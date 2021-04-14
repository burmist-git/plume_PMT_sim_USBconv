//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

Int_t plotsSingle(){

  TString fileN;
  fileN = "./poissonMonteCarlo_1pe.root";

  TFile *f01 = new TFile(fileN.Data());
  TH1D *h1_01 = (TH1D*)f01->Get("h1_charge_pe_09");

  h1_01->SetTitle("");

  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  h1_01->Rebin(2);
  
  h1_01->SetLineColor(kBlack);
  h1_01->SetLineWidth(3.0);
  h1_01->GetXaxis()->SetRangeUser(-1.0,4000000);
  h1_01->GetXaxis()->SetTitle("Number of electrons");
  
  h1_01->Draw();

  return 0;
}
