////////////////////////////////////////////////////////////////////
//                Date:  Sun Apr 11 15:11:36 CEST 2021            //
//              Author: Leonid Burmistrov                         //
// Program description: Monte Carlo simulation of the PMT         //
//                      processes.                                //
////////////////////////////////////////////////////////////////////

//root
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TRandom3.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream> // For "istringstream" function

using namespace std;

const Int_t total_number_of_dinodes = 10;
Double_t mean_secondary_emission[total_number_of_dinodes] =
  {4.919,     //01
   4.919,     //02
   4.919,     //03
   4.919,     //04
   4.919,     //05
   4.919,     //06
   4.919,     //07
   4.919,     //08
   4.919,     //09
   4.919};    //10

/*
const Int_t total_number_of_dinodes = 11;
Double_t mean_secondary_emission[total_number_of_dinodes] =
  {3.98,     //01
   3.98,     //02
   3.98,     //03
   3.98,     //04
   3.98,     //05
   3.98,     //06
   3.98,     //07
   3.98,     //08
   3.98,     //09
   3.98,     //10
   3.98};    //11
*/
TRandom3 *rnd = new TRandom3(123);

void poissonMonteCarlo( Double_t number_of_initial_photoelectrons, Double_t tuneParameterOfTheSE, Int_t nEvents, TString outputrootFile);
void simulatePMT(Int_t totN[total_number_of_dinodes], Int_t number_of_initial_photoelectrons, Double_t tuneParameterOfTheSE);

int main(int argc, char *argv[]){
  Double_t number_of_initial_photoelectrons;
  Double_t tuneParameterOfTheSE;
  Int_t nEvents;
  TString outputrootFile;
  if(argc == 6 && atoi(argv[1])==0){
    number_of_initial_photoelectrons = atof(argv[2]);
    tuneParameterOfTheSE = atof(argv[3]);
    nEvents = atoi(argv[4]);
    outputrootFile = argv[5];
    cout<<"Number of initial photoelectrons : "<<number_of_initial_photoelectrons<<endl
	<<"Tune parameter of the se         : "<<tuneParameterOfTheSE<<endl
	<<"Number of the Events             : "<<nEvents<<endl
        <<"Out root file                    : "<<outputrootFile<<endl;
    poissonMonteCarlo( number_of_initial_photoelectrons, tuneParameterOfTheSE, nEvents, outputrootFile);
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0  "<<endl
	<<"        [2] - Number of initial photoelectrons "<<endl
	<<"        [3] - Tune parameter of the secondary_emission"<<endl
        <<"        [4] - Number of the Events"<<endl
        <<"        [5] - Out root file"<<endl;
  }  
  return 0;
}

void poissonMonteCarlo( Double_t number_of_initial_photoelectrons, Double_t tuneParameterOfTheSE, Int_t nEvents, TString outputrootFile){
  //
  for(Int_t i = 0;i<total_number_of_dinodes;i++)
    mean_secondary_emission[i] = mean_secondary_emission[i]*tuneParameterOfTheSE;
  //TH1D *h1_charge_pe = new TH1D("h1_charge_pe","charge pe",1000,0.0,10000000);
  TH1D *h1_charge_pe_01 = new TH1D("h1_charge_pe_01","charge pe 01",400,0.0,TMath::Power(mean_secondary_emission[0],1)*20);
  TH1D *h1_charge_pe_02 = new TH1D("h1_charge_pe_02","charge pe 02",400,0.0,TMath::Power(mean_secondary_emission[0],2)*20);
  TH1D *h1_charge_pe_03 = new TH1D("h1_charge_pe_03","charge pe 03",400,0.0,TMath::Power(mean_secondary_emission[0],3)*20);
  TH1D *h1_charge_pe_04 = new TH1D("h1_charge_pe_04","charge pe 04",400,0.0,TMath::Power(mean_secondary_emission[0],4)*20);
  TH1D *h1_charge_pe_05 = new TH1D("h1_charge_pe_05","charge pe 05",400,0.0,TMath::Power(mean_secondary_emission[0],5)*20);
  TH1D *h1_charge_pe_06 = new TH1D("h1_charge_pe_06","charge pe 06",400,0.0,TMath::Power(mean_secondary_emission[0],6)*20);
  TH1D *h1_charge_pe_07 = new TH1D("h1_charge_pe_07","charge pe 07",400,0.0,TMath::Power(mean_secondary_emission[0],7)*20);
  TH1D *h1_charge_pe_08 = new TH1D("h1_charge_pe_08","charge pe 08",400,0.0,TMath::Power(mean_secondary_emission[0],8)*20);
  TH1D *h1_charge_pe_09 = new TH1D("h1_charge_pe_09","charge pe 09",400,0.0,TMath::Power(mean_secondary_emission[0],9)*20);
  TH1D *h1_charge_pe_10 = new TH1D("h1_charge_pe_10","charge pe 10",400,0.0,TMath::Power(mean_secondary_emission[0],10)*20);
  TH1D *h1_charge_pe_1001 = new TH1D("h1_charge_pe_1001","charge pe 1001",4000,0.0,TMath::Power(mean_secondary_emission[0],10)*20);
  Double_t meas_nbins     = 200;
  Double_t meas_binx_min  = -6162914.5575403785;
  Double_t meas_binx_max  = 31337085.4424596205;
  Double_t sigma_noise_pe = 869686.4522630112;
  Double_t pe_smearing = 0;
  TH1D *h1_charge_pe_sim = new TH1D( "h1_charge_pe_sim", "charge pe sim", meas_nbins, meas_binx_min, meas_binx_max);
  TH1D *h1_charge_pe_sim_smearing = new TH1D( "h1_charge_pe_sim_smearing", "charge pe sim smearing", meas_nbins, meas_binx_min, meas_binx_max);
  for(Int_t i = 0;i<nEvents;i++){
    Int_t totN[total_number_of_dinodes];
    //simulatePMT(totN, rnd->Poisson(number_of_initial_photoelectrons), tuneParameterOfTheSE);
    simulatePMT(totN, number_of_initial_photoelectrons, tuneParameterOfTheSE);
    h1_charge_pe_01->Fill(totN[0]);
    h1_charge_pe_02->Fill(totN[1]);
    h1_charge_pe_03->Fill(totN[2]);
    h1_charge_pe_04->Fill(totN[3]);
    h1_charge_pe_05->Fill(totN[4]);
    h1_charge_pe_06->Fill(totN[5]);
    h1_charge_pe_07->Fill(totN[6]);
    h1_charge_pe_08->Fill(totN[7]);
    h1_charge_pe_09->Fill(totN[8]);
    h1_charge_pe_10->Fill(totN[total_number_of_dinodes-1]);
    h1_charge_pe_1001->Fill(totN[total_number_of_dinodes-1]);
    h1_charge_pe_sim->Fill(totN[total_number_of_dinodes-1]);
    pe_smearing = totN[total_number_of_dinodes-1] + rnd->Gaus(0.0,sigma_noise_pe);
    h1_charge_pe_sim_smearing->Fill(pe_smearing);
  }
  ////////////////////////////
  TFile* rootFile = new TFile(outputrootFile.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<outputrootFile.Data()<<" is zombi"<<endl;
    assert(0);
  }
  h1_charge_pe_01->Write();
  h1_charge_pe_02->Write();
  h1_charge_pe_03->Write();
  h1_charge_pe_04->Write();
  h1_charge_pe_05->Write();
  h1_charge_pe_06->Write();
  h1_charge_pe_07->Write();
  h1_charge_pe_08->Write();
  h1_charge_pe_09->Write();
  h1_charge_pe_10->Write();
  h1_charge_pe_1001->Write();
  h1_charge_pe_sim->Write();
  h1_charge_pe_sim_smearing->Write();
  rootFile->Close();
}

void simulatePMT(Int_t totN[total_number_of_dinodes], Int_t number_of_initial_photoelectrons, Double_t tuneParameterOfTheSE){
  //return TMath::Power(mean_secondary_emission,total_number_of_dinodes);
  Int_t tot = 0;
  for( Int_t i = 0; i<total_number_of_dinodes; i++)
    totN[i] = 0;
  //////////////////////////////////////////////////
  tot = 0;
  for( Int_t i = 0; i<number_of_initial_photoelectrons; i++)
    tot += rnd->Poisson(mean_secondary_emission[0]);
  totN[0] = tot;
  for( Int_t i = 1; i<total_number_of_dinodes; i++){
    tot = 0;
    for( Int_t j = 0; j<totN[i-1]; j++){
      tot += rnd->Poisson(mean_secondary_emission[i]);
    }
    totN[i] = tot;
  }
  //////////////////////////////////////////////////
  ////01
  //totN[0] = rnd->Poisson(mean_secondary_emission[0]);
  ////02
  //tot = 0;
  //for( Int_t i = 0; i<totN[0]; i++){
  //  tot += rnd->Poisson(mean_secondary_emission[1]);
  //}
  //totN[1] = tot;
  ////03
  //tot = 0;
  //for( Int_t i = 0; i<totN[1]; i++){
  //  tot += rnd->Poisson(mean_secondary_emission[2]);
  //}
  //totN[2] = tot;
  ////04
  //tot = 0;
  //for( Int_t i = 0; i<totN[2]; i++){
  //  tot += rnd->Poisson(mean_secondary_emission[3]);
  //}
  //totN[3] = tot;
}
