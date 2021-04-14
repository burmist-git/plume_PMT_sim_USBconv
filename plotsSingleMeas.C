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

Int_t plotsSingleMeas(){

  TString fileN;
  fileN = "./Run_2_ChargeHistos_4_7_2021.root";

  TFile *f01 = new TFile(fileN.Data());
  //TH1D *h1_01 = (TH1D*)f01->Get("h1_ch1");
  //TH1D *h1_01 = (TH1D*)f01->Get("h1corr_ch1");
  //TH1D *h1_01 = (TH1D*)f01->Get("h1corrsub_ch1");
  TH1D *h1_01 = (TH1D*)f01->Get("h1corrsubpe_ch1");
  
  h1_01->SetTitle("");

  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  //h1_01->Rebin(2);
  
  h1_01->SetLineColor(kBlack);
  h1_01->SetLineWidth(3.0);
  //h1_01->GetXaxis()->SetRangeUser(-1.0,4000000);
  //h1_01->GetXaxis()->SetTitle("Charge, pC");
  h1_01->GetXaxis()->SetTitle("# p.e.");
  
  h1_01->Draw();

  return 0;
}
