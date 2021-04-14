////////////////////////////////////////////////////////////////////
//                Date: Thu Apr  8 18:21:04 CEST 2021             //
//              Author: Leonid Burmistrov                         //
// Program description: Convertion of histograms (txt raw data)   //
//                      into the root format.                     //
//                      Initial txt data file produced            //
//                      by the single board 8 channel             //
//                      USB-WaveCatcher.                          //
////////////////////////////////////////////////////////////////////

//=== FILE SAVED WITH SOFTWARE VERSION: V2.8.6 ===
//=== CHARGE HISTO === 
//== CHANNEL : 0  ==
//== Nb Of Entries in Histogram : 200000  ==
//== X AXIS : Charge in pico-Coulombs [200 values] ==
// -4.985  -4.955  -4.925  -4.895  -4.865  -4.835  -4.805  -4.775  -4.745  -4.715  -4.685  -4.655  -4.625  -4.595  -4.565
// -4.535  -4.505  -4.475  -4.445  -4.415  -4.385  -4.355  -4.325  -4.295  -4.265  -4.235  -4.205  -4.175  -4.145  -4.115
// -4.085  -4.055  -4.025  -3.995  -3.965  -3.935  -3.905  -3.875  -3.845  -3.815  -3.785  -3.755  -3.725  -3.695  -3.665
// -3.635  -3.605  -3.575  -3.545  -3.515  -3.485  -3.455  -3.425  -3.395  -3.365  -3.335  -3.305  -3.275  -3.245  -3.215
// -3.185  -3.155  -3.125  -3.095  -3.065  -3.035  -3.005  -2.975  -2.945  -2.915  -2.885  -2.855  -2.825  -2.795  -2.765
// -2.735  -2.705  -2.675  -2.645  -2.615  -2.585  -2.555  -2.525  -2.495  -2.465  -2.435  -2.405  -2.375  -2.345  -2.315
// -2.285  -2.255  -2.225  -2.195  -2.165  -2.135  -2.105  -2.075  -2.045  -2.015  -1.985  -1.955  -1.925  -1.895  -1.865
// -1.835  -1.805  -1.775  -1.745  -1.715  -1.685  -1.655  -1.625  -1.595  -1.565  -1.535  -1.505  -1.475  -1.445  -1.415
// -1.385  -1.355  -1.325  -1.295  -1.265  -1.235  -1.205  -1.175  -1.145  -1.115  -1.085  -1.055  -1.025  -0.995  -0.965
// -0.935  -0.905  -0.875  -0.845  -0.815  -0.785  -0.755  -0.725  -0.695  -0.665  -0.635  -0.605  -0.575  -0.545  -0.515
// -0.485  -0.455  -0.425  -0.395  -0.365  -0.335  -0.305  -0.275  -0.245  -0.215  -0.185  -0.155  -0.125  -0.095  -0.065
// -0.035  -0.005   0.025   0.055   0.085   0.115   0.145   0.175   0.205   0.235   0.265   0.295   0.325   0.355   0.385
//  0.415   0.445   0.475   0.505   0.535   0.565   0.595   0.625   0.655   0.685   0.715   0.745   0.775   0.805   0.835
//  0.865   0.895   0.925   0.955   0.985 
//== Y AXIS : Charge Distribution [200 values] ==
//  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//  0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 3 4 2 3 5 6 4 6 8 15 15 18 28 30 55 65 74 102 153 158 218 314 368 499 588 736 875 1078 1302 1489
//  1798 2068 2410 2794 3027 3546 3864 4305 4830 5196 5499 5785 6130 6520 6861 7045 7122 7218 7500 7309 7253 7169 6898 6813 6469
//  6252 5855 5426 4902 
//== Mean Charge  =   0.691 [pico-Coulombs] ==
//== Charge Sigma =   0.322 [pico-Coulombs rms] ==

//root
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>

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

const Int_t nChannels = 8;
const string softwareVersion = "V2.8.6";

struct histInfo{
  Int_t channelID;
  Int_t entries;
  Int_t nBins;
  string units_str;
  Double_t mean;
  Double_t sigma;
  histInfo(){
    channelID = -999;
    entries = -999;
    nBins = -999;
    units_str = "NULL";
    mean = -999.0;
    sigma = -999.0;
  }
  vector<Double_t> binp; //bin position
  vector<Double_t> binv; //bin value
  void printInfo(bool allKey=0){
    cout<<"channelID = "<<channelID<<endl
	<<"entries   = "<<entries<<endl
      	<<"nBins     = "<<nBins<<endl
	<<"units_str = "<<units_str<<endl
	<<"mean      = "<<mean<<endl
	<<"sigma     = "<<sigma<<endl;
    if(allKey==true){
      for(unsigned int i = 0;i<binp.size();i++)
	cout<<binp[i]<<"\t";
      cout<<endl;
      for(unsigned int i = 0;i<binv.size();i++)
	cout<<binv[i]<<"\t";
      cout<<endl;
    }
  }
  /*
  inline histInfo& operator=(histInfo a) {
    channelID = a.channelID;
    entries = a.entries;
    nBins = a.nBins;
    units_str = a.units_str;
    mean = a.mean;
    sigma = a.sigma;
    return *this;
  }
  */
};

void convUSBHistos2root(TString inputDataFile, TString outputrootFile);

int main(int argc, char *argv[]){  
  TString inputDataFile;
  TString outputrootFile;
  if(argc == 4 && atoi(argv[1])==0){
    inputDataFile = argv[2];
    outputrootFile = argv[3];
    cout<<"In data file  : "<<inputDataFile<<endl
        <<"Out root file : "<<outputrootFile<<endl;
    convUSBHistos2root(inputDataFile, outputrootFile);
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0  "<<endl
        <<"        [2] - in data file"<<endl
        <<"        [3] - out root file"<<endl;
  }  
  return 0;
}

void convUSBHistos2root(TString inputDataFile, TString outputrootFile){  
  cout<<" ---> Conversion of "<<inputDataFile<<endl;
  ///////////////////Root file with data/////////////////
  
  string histInfo_str;

  bool external_loop_flag=true;
  bool internal_loop_flag=false;
  vector<histInfo> histInfo_struct;
  vector<histInfo> histInfo_struct_subtraction;
  
  // Starts to read data file
  ifstream indata;
  indata.open(inputDataFile.Data()); 
  assert(indata.is_open());
  string mot;

  Int_t motInt = 0;
  Double_t motFloat = 0;
    
  while (indata >> mot && external_loop_flag == true && internal_loop_flag == false){
    // Check software version
    if(mot == "VERSION:"){
      indata >> mot;
      cout<<" - software version : "<<mot<<endl;
      if(mot != softwareVersion){
	cout << " ERROR: Check software version !" <<endl;
	assert(0);
      }
      indata >> mot;
      indata >> mot;
      indata >> histInfo_str;
      cout<<" - histInfo_str     : "<<histInfo_str<<endl;
    }
    if(mot == "CHANNEL"){
      indata >> mot;
      indata >> motInt;
      //cout<<"motInt "<<motInt<<endl;
      external_loop_flag = false;
      internal_loop_flag = true;
      histInfo theHist;
      theHist.channelID = motInt;
      while (indata >> mot && external_loop_flag == false && internal_loop_flag == true){
	//== Charge Sigma =   0.322 [pico-Coulombs rms] ==
	if(mot=="rms]"){
	  external_loop_flag = true;
	  internal_loop_flag = false;
	}
	//== Nb Of Entries in Histogram : 200000  ==
	if(mot=="Nb"){
	  indata >> mot; indata >> mot; indata >> mot; indata >> mot; indata >> mot;
	  indata >> motInt;
	  theHist.entries = motInt;
	}
	//== X AXIS : Charge in pico-Coulombs [200 values] ==
	if(mot=="X"){
	  indata >> mot;
	  if(mot=="AXIS"){
	    indata >> mot; indata >> mot; indata >> mot;
	    indata >> mot;
	    theHist.units_str = mot;
	    indata >> mot;
	    TString nBins_str = mot;
	    theHist.nBins = nBins_str.Replace(0,1,"").Atoi();	    
	    indata >> mot; indata >> mot;
	    for(Int_t i = 0;i<theHist.nBins;i++){
	      indata >> motFloat;
	      //cout<<"motFloat "<<motFloat<<endl;
	      theHist.binp.push_back(motFloat);
	    }
	  }
	}
	//== Y AXIS : Charge Distribution [200 values] ==
	if(mot=="Y"){
	  indata >> mot;
	  if(mot=="AXIS"){
	    indata >> mot; indata >> mot; indata >> mot;
	    indata >> mot; indata >> mot; indata >> mot;
	    for(Int_t i = 0;i<theHist.nBins;i++){
	      indata >> motFloat;
	      //cout<<"motFloat "<<motFloat<<endl;
	      theHist.binv.push_back(motFloat);
	    }
	  }
	}
	//== Mean Charge  =   0.691 [pico-Coulombs] ==
	if(mot=="Mean"){
	  indata >> mot; indata >> mot;
	  indata >> motFloat;
	  theHist.mean = motFloat;
	}	
	//== Charge Sigma =   0.322 [pico-Coulombs rms] ==
	if(mot=="Sigma"){
	  indata >> mot;
	  indata >> motFloat;
	  theHist.sigma = motFloat;
	}
      }
      histInfo_struct.push_back(theHist);
    }
  }
  indata.close();
  //
  histInfo_struct_subtraction = histInfo_struct;
  //
  if((unsigned int)nChannels != histInfo_struct.size())
    assert(0);
  //
  TH1D *h1[nChannels];
  for(unsigned int i = 0;i<nChannels;i++)
     h1[i] = new TH1D();
  //
  for(unsigned int i = 0; i<histInfo_struct.size();i++){
    //histInfo_struct[i].printInfo(true);
    Double_t bin_width = histInfo_struct[i].binp[1] - histInfo_struct[i].binp[0];
    Double_t binx_min = histInfo_struct[i].binp[0] - bin_width/2.0;
    Double_t binx_max = histInfo_struct[i].binp[histInfo_struct[i].binp.size()-1] + bin_width/2.0;
    TString h1nameh = "h1"; h1nameh += "_ch";h1nameh += i;
    TString h1Titleh = "h1"; h1Titleh +="_ch";h1Titleh += i;
    h1[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
                     histInfo_struct[i].nBins, binx_min, binx_max);
    for(unsigned int j = 0;j<histInfo_struct[i].binp.size();j++)
      h1[i]->SetBinContent(j+1,histInfo_struct[i].binv[j]);
    h1[i]->SetEntries(histInfo_struct[i].entries);
    //cout<<histInfo_struct[i].nBins<<endl
    //<<binx_min<<endl
    //<<binx_max<<endl;
  }
  ////////////////////////////
  // Correction, invertion and noise subtraction
  h1[1]->Fit("gaus","Q","",-0.25,0.30);
  TF1 *fit = h1[1]->GetFunction("gaus");
  Double_t chi2 = fit->GetChisquare();
  Double_t ndf = fit->GetNDF();
  Double_t fitPar_constant    = fit->GetParameter(0);
  Double_t fitParErr_constant = fit->GetParError(0);
  Double_t fitPar_mean        = fit->GetParameter(1);
  Double_t fitParErr_mean     = fit->GetParError(1);
  Double_t fitPar_sigma       = fit->GetParameter(2);
  Double_t fitParErr_sigma    = fit->GetParError(2);
  cout<<"chi2               "<<chi2<<endl
      <<"ndf                "<<ndf<<endl
      <<"chi2/ndf           "<<chi2/ndf<<endl
      <<"fitPar_constant    "<<fitPar_constant<<endl
      <<"fitParErr_constant "<<fitParErr_constant<<endl
      <<"fitPar_mean        "<<fitPar_mean<<endl
      <<"fitParErr_mean     "<<fitParErr_mean<<endl
      <<"fitPar_sigma       "<<fitPar_sigma<<endl
      <<"fitParErr_sigma    "<<fitParErr_sigma<<endl
      <<"fit->Eval(0)       "<<fit->Eval(0)<<endl;
  //
  for(unsigned int i = 0; i<histInfo_struct_subtraction.size();i++)
    for(unsigned int j = 0;j<histInfo_struct_subtraction[i].binp.size();j++)
      histInfo_struct_subtraction[i].binv[j] = histInfo_struct_subtraction[i].binv[j] - fit->Eval(histInfo_struct_subtraction[i].binp[j]);
  //
  Double_t binVal;
  TH1D *h1corr[nChannels];
  TH1D *h1corrpe[nChannels];
  TH1D *h1corrsub[nChannels];
  TH1D *h1corrsubpe[nChannels];
  for(unsigned int i = 0;i<nChannels;i++){
     h1corr[i] = new TH1D();
     h1corrpe[i] = new TH1D();
     h1corrsub[i] = new TH1D();
     h1corrsubpe[i] = new TH1D();
  }
  //correction
  for(unsigned int i = 0; i<histInfo_struct.size();i++){
    //histInfo_struct[i].printInfo(true);
    Double_t bin_width = histInfo_struct[i].binp[1] - histInfo_struct[i].binp[0];
    Double_t binx_max = -(histInfo_struct[i].binp[0] - bin_width/2.0 + fitPar_mean);
    Double_t binx_min = -(histInfo_struct[i].binp[histInfo_struct[i].binp.size()-1] + bin_width/2.0 + fitPar_mean);
    TString h1nameh = "h1corr"; h1nameh += "_ch";h1nameh += i;
    TString h1Titleh = "corr"; h1Titleh +="_ch";h1Titleh += i;
    h1corr[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
			 histInfo_struct[i].nBins, binx_min, binx_max);
    for(unsigned int j = 0;j<histInfo_struct[i].binp.size();j++){
      binVal = histInfo_struct[i].binv[j];
      //if(binVal<0.0)
      //binVal=-1.0;
      h1corr[i]->SetBinContent(histInfo_struct[i].binp.size()-1-j,binVal);
    }
    h1corr[i]->SetEntries(histInfo_struct[i].entries);
    //cout<<histInfo_struct[i].nBins<<endl
    //<<binx_min<<endl
    //<<binx_max<<endl;
  }
  //correction p.e.
  for(unsigned int i = 0; i<histInfo_struct.size();i++){
    //histInfo_struct[i].printInfo(true);
    Double_t bin_width = histInfo_struct[i].binp[1] - histInfo_struct[i].binp[0];
    Double_t binx_max = -(histInfo_struct[i].binp[0] - bin_width/2.0 + fitPar_mean)/1.6e-7;
    Double_t binx_min = -(histInfo_struct[i].binp[histInfo_struct[i].binp.size()-1] + bin_width/2.0 + fitPar_mean)/1.6e-7;
    TString h1nameh = "h1corrpe"; h1nameh += "_ch";h1nameh += i;
    TString h1Titleh = "corrpe"; h1Titleh +="_ch";h1Titleh += i;
    h1corrpe[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
			 histInfo_struct[i].nBins, binx_min, binx_max);
    for(unsigned int j = 0;j<histInfo_struct[i].binp.size();j++){
      binVal = histInfo_struct[i].binv[j];
      //if(binVal<0.0)
      //binVal=-1.0;
      h1corrpe[i]->SetBinContent(histInfo_struct[i].binp.size()-1-j,binVal);
    }
    h1corrpe[i]->SetEntries(histInfo_struct[i].entries);
    //cout<<histInfo_struct[i].nBins<<endl
    //<<binx_min<<endl
    //<<binx_max<<endl;
  }  
  //subtraction
  for(unsigned int i = 0; i<histInfo_struct.size();i++){
    //histInfo_struct[i].printInfo(true);
    Double_t bin_width = histInfo_struct[i].binp[1] - histInfo_struct[i].binp[0];
    Double_t binx_max = -(histInfo_struct[i].binp[0] - bin_width/2.0 + fitPar_mean);
    Double_t binx_min = -(histInfo_struct[i].binp[histInfo_struct[i].binp.size()-1] + bin_width/2.0 + fitPar_mean);
    TString h1nameh = "h1corrsub"; h1nameh += "_ch";h1nameh += i;
    TString h1Titleh = "corrsub"; h1Titleh +="_ch";h1Titleh += i;
    h1corrsub[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
			 histInfo_struct[i].nBins, binx_min, binx_max);
    for(unsigned int j = 0;j<histInfo_struct[i].binp.size();j++){
      binVal = histInfo_struct_subtraction[i].binv[j];
      //if(binVal<0.0)
      //binVal=-1.0;
      h1corrsub[i]->SetBinContent(histInfo_struct_subtraction[i].binp.size()-1-j,binVal);
    }
    h1corrsub[i]->SetEntries(histInfo_struct[i].entries);
    //cout<<histInfo_struct[i].nBins<<endl
    //<<binx_min<<endl
    //<<binx_max<<endl;
  }
  //p.e.
  Double_t binx_v_min = 0;
  Double_t binx_v_max = 0;
  for(unsigned int i = 0; i<histInfo_struct.size();i++){
    //histInfo_struct[i].printInfo(true);
    Double_t bin_width = (histInfo_struct[i].binp[1] - histInfo_struct[i].binp[0]);
    Double_t binx_max = -(histInfo_struct[i].binp[0] - bin_width/2.0 + fitPar_mean)/1.6e-7;
    Double_t binx_min = -(histInfo_struct[i].binp[histInfo_struct[i].binp.size()-1] + bin_width/2.0 + fitPar_mean)/1.6e-7;
    TString h1nameh = "h1corrsubpe"; h1nameh += "_ch";h1nameh += i;
    TString h1Titleh = "corrsubpe"; h1Titleh +="_ch";h1Titleh += i;
    h1corrsubpe[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
			 histInfo_struct[i].nBins, binx_min, binx_max);
    for(unsigned int j = 0;j<histInfo_struct[i].binp.size();j++){
      binVal = histInfo_struct_subtraction[i].binv[j];
      //if(binVal<0.0)
      //binVal=-1.0;
      h1corrsubpe[i]->SetBinContent(histInfo_struct_subtraction[i].binp.size()-1-j,binVal);
    }
    h1corrsubpe[i]->SetEntries(histInfo_struct[i].entries);
    //cout<<histInfo_struct[i].nBins<<endl
    //	<<binx_min<<endl
    //	<<binx_max<<endl;
    binx_v_min = binx_min;
    binx_v_max = binx_max;
  }
  printf("nbins      : %30d \n",histInfo_struct[0].nBins);
  printf("binx_min   : %30.10f \n",binx_v_min);
  printf("binx_max   : %30.10f \n",binx_v_max);
  printf("sigma      : %30.10f \n",fitPar_sigma/1.6e-7);
  printf("Lambda0    : %30.10f \n",h1corrsub[1]->Integral()/h1corr[1]->Integral());
  printf("All events : %30.10f \n",h1corr[1]->Integral());
  printf("Non zero   : %30.10f \n",h1corrsub[1]->Integral());
  ////////////////////////////
  TFile* rootFile = new TFile(outputrootFile.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<outputrootFile.Data()<<" is zombi"<<endl;
    assert(0);
  }
  for(unsigned int i = 0; i<histInfo_struct.size();i++){
    h1[i]->Write();
    h1corr[i]->Write();
    h1corrpe[i]->Write();
    h1corrsub[i]->Write();
    h1corrsubpe[i]->Write();
  }
  rootFile->Close();
}
