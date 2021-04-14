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

void normaliseHist(TH1D *h1, Double_t additionalNorm);

Int_t plots_sim_vs_meas(){

  TString fileN01;
  TString fileN02;
  TString fileN03;
  //fileN01 = "./poissonMonteCarlo_1pe_s.root";
  //fileN02 = "./Run_2_ChargeHistos_4_7_2021.root";
  fileN01 = "./poissonMonteCarlo_0pe_s_big.root";
  fileN02 = "./Run_2_ChargeHistos_4_7_2021.root";
  fileN03 = "./poissonMonteCarlo_2pe_s.root";

  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
  TFile *f03 = new TFile(fileN03.Data());

  //TH1D *h1_sim = (TH1D*)f01->Get("h1_charge_pe_sim_smearing");
  //TH1D *h1_meas = (TH1D*)f02->Get("h1corrsubpe_ch1");
  TH1D *h1_sim = (TH1D*)f01->Get("h1_charge_pe_sim_smearing");
  TH1D *h1_meas = (TH1D*)f02->Get("h1corrpe_ch1");
  TH1D *h1_sim02 = (TH1D*)f03->Get("h1_charge_pe_sim_smearing");

  normaliseHist(h1_sim,1);
  normaliseHist(h1_meas,1);
  normaliseHist(h1_sim02,1.0/0.0029491174);
  
  //h1_1->Rebin(4);
  //h1_2->Rebin(4);
  //h1_3->Rebin(4);

  h1_meas->SetTitle("");
  h1_sim->SetTitle("");
  
  TCanvas *c1 = new TCanvas("c1",fileN01.Data(),10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetHistLineStyle(0);
  //gStyle->SetOptStat(kFALSE);
 
  h1_meas->SetLineColor(kBlack);
  h1_sim->SetLineColor(kRed);
  h1_sim02->SetLineColor(kBlue);

  h1_meas->SetLineWidth(3.0);
  h1_sim->SetLineWidth(3.0);
  h1_sim02->SetLineWidth(3.0);

  //c1->Divide(2,1);
  //c1->cd(1);
  h1_meas->SetMaximum(0.002);
  h1_meas->Draw("HIST E");
  h1_sim->Draw("HIST sames E");
  h1_sim02->Draw("HIST sames E");

  //h1_2->Draw();
  //h1_2->Fit("gaus");
  h1_meas->GetXaxis()->SetTitle("# p.e.");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  //h1_1->Fit("gaus");
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_meas, "meas.","l");
  leg->AddEntry(h1_sim, "sim.","l");
  leg->AddEntry(h1_sim02, "sim. 2 p.e.","l");
  leg->Draw();

  return 0;
}

void normaliseHist(TH1D *h1, Double_t additionalNorm = 1.0){
  Int_t n = h1->GetNbinsX();
  Double_t val;
  Double_t valErr;
  Double_t norm = h1->Integral()*additionalNorm;
  for (Int_t i = 1;i<=n;i++){
    val = h1->GetBinContent(i);
    valErr = h1->GetBinError(i);
    val = val/norm;
    valErr = valErr/norm;
    h1->SetBinContent(i,val);
    h1->SetBinError(i,valErr);
  }
}

