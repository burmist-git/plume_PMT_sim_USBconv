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

Int_t plots_dinodes_variance(){

  TString fileN01;
  fileN01 = "./poissonMonteCarlo_1pe.root";

  TFile *f01 = new TFile(fileN01.Data());

  TH1D *h1_01[10];

  h1_01[0] = (TH1D*)f01->Get("h1_charge_pe_01");
  h1_01[1] = (TH1D*)f01->Get("h1_charge_pe_02");
  h1_01[2] = (TH1D*)f01->Get("h1_charge_pe_03");
  h1_01[3] = (TH1D*)f01->Get("h1_charge_pe_04");
  h1_01[4] = (TH1D*)f01->Get("h1_charge_pe_05");
  h1_01[5] = (TH1D*)f01->Get("h1_charge_pe_06");
  h1_01[6] = (TH1D*)f01->Get("h1_charge_pe_07");
  h1_01[7] = (TH1D*)f01->Get("h1_charge_pe_08");
  h1_01[8] = (TH1D*)f01->Get("h1_charge_pe_09");
  h1_01[9] = (TH1D*)f01->Get("h1_charge_pe_10");
  
  /*
  TH1D *h1_01_01 = (TH1D*)f01->Get("h1_charge_pe_01");
  TH1D *h1_02_01 = (TH1D*)f01->Get("h1_charge_pe_02");
  TH1D *h1_03_01 = (TH1D*)f01->Get("h1_charge_pe_03");
  TH1D *h1_04_01 = (TH1D*)f01->Get("h1_charge_pe_04");
  TH1D *h1_05_01 = (TH1D*)f01->Get("h1_charge_pe_05");
  TH1D *h1_06_01 = (TH1D*)f01->Get("h1_charge_pe_06");
  TH1D *h1_07_01 = (TH1D*)f01->Get("h1_charge_pe_07");
  TH1D *h1_08_01 = (TH1D*)f01->Get("h1_charge_pe_08");
  TH1D *h1_09_01 = (TH1D*)f01->Get("h1_charge_pe_09");
  TH1D *h1_10_01 = (TH1D*)f01->Get("h1_charge_pe_10");
  */
  Double_t y[10];
  Double_t yerr[10];
  Double_t x[10];
  Double_t xerr[10];
  for (Int_t i = 0;i<10;i++){
    y[i] = h1_01[i]->GetRMS()/h1_01[i]->GetMean()/(h1_01[9]->GetRMS()/h1_01[9]->GetMean());
    yerr[i] = h1_01[i]->GetRMSError()/h1_01[i]->GetMean();
    x[i] = i+1;
    xerr[i] = 0.01;
  }
    
  TGraphErrors *gr1 = new TGraphErrors(10,x,y,0,0);
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerColor(kBlack);
  //gr1->SetTitle("RMS/mean");
  gr1->SetTitle("");
  gr1->GetXaxis()->SetTitle("Dinode ID");
  gr1->GetYaxis()->SetTitle("Normalized RMS/mean");
  gr1->GetXaxis()->SetTitleOffset(0.8);
  gr1->GetXaxis()->SetTitleSize(0.05);
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->SetTitleOffset(0.95);
  gr1->GetYaxis()->SetTitleSize(0.05);
  gr1->GetYaxis()->CenterTitle();

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  TCanvas *c1 = new TCanvas("c1","plots",10,10,800,800);
  c1->Clear();
  c1->SetFillColor(kWhite);
  gr1->SetMinimum(0.0);
  gr1->SetMaximum(1.1);
  gr1->Draw("AP");
  c1->GetPad(0)->SetLeftMargin(0.12);
  c1->GetPad(0)->SetRightMargin(0.02);
  c1->GetPad(0)->SetTopMargin(0.07);
  
  //h1_1->Rebin(4);
  //h1_2->Rebin(4);
  //h1_3->Rebin(4);

  //h1_01_01->SetTitle("");

  /*
  TCanvas *c1 = new TCanvas("c1",fileN01.Data(),10,10,800,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
 
  h1_01_01->SetLineColor(kBlack);

  h1_01_01->SetLineWidth(3.0);

  //c1->Divide(2,1);
  //c1->cd(1);
  h1_01_01->Draw();

  //h1_2->Draw();
  //h1_2->Fit("gaus");
  h1_01_01->GetXaxis()->SetTitle("Number of electrons");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
  */
  
  /*
  h1_1->Fit("gaus");
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_1, "Without corrections","l");
  leg->AddEntry(h1_2, "With corrections","l");
  leg->Draw();
  */

  return 0;
}
