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

Int_t plots(){

  TString fileN01;
  TString fileN02;
  TString fileN03;
  fileN01 = "./poissonMonteCarlo_1pe.root";
  fileN02 = "./poissonMonteCarlo_2pe.root";
  fileN03 = "./poissonMonteCarlo_3pe.root";

  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
  TFile *f03 = new TFile(fileN03.Data());

  TH1D *h1_01_01 = (TH1D*)f01->Get("h1_charge_pe_10");
  TH1D *h1_01_02 = (TH1D*)f02->Get("h1_charge_pe_10");
  TH1D *h1_01_03 = (TH1D*)f03->Get("h1_charge_pe_10");

  //h1_1->Rebin(4);
  //h1_2->Rebin(4);
  //h1_3->Rebin(4);

  h1_01_01->SetTitle("");

  TCanvas *c1 = new TCanvas("c1",fileN01.Data(),10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
 
  h1_01_01->SetLineColor(kBlack);
  h1_01_02->SetLineColor(kRed);
  h1_01_03->SetLineColor(kBlue);

  h1_01_01->SetLineWidth(3.0);
  h1_01_02->SetLineWidth(3.0);
  h1_01_03->SetLineWidth(3.0);

  //c1->Divide(2,1);
  //c1->cd(1);
  h1_01_01->Draw();
  h1_01_02->Draw("sames");
  h1_01_03->Draw("sames");

  //h1_2->Draw();
  //h1_2->Fit("gaus");
  h1_01_01->GetXaxis()->SetTitle("Number of electrons");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  //h1_1->Fit("gaus");
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_01_01, "1 p.e.","l");
  leg->AddEntry(h1_01_02, "2 p.e.","l");
  leg->AddEntry(h1_01_03, "3 p.e.","l");
  leg->Draw();

  return 0;
}
