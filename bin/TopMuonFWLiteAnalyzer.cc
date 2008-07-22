#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopQuarkAnalysis/Examples/bin/NiceStyle.cc"
#include "TopQuarkAnalysis/Examples/interface/RootSystem.h"
#include "TopQuarkAnalysis/Examples/interface/RootHistograms.h"
#include "TopQuarkAnalysis/Examples/interface/RootPostScript.h"


int main(int argc, char* argv[]) 
{
  if( argc<2 ){
    // -------------------------------------------------  
    std::cerr << "ERROR:" << " Please specify filepath" << std::endl;
    // -------------------------------------------------  
    return -1;
  }
  
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  
  // set nice style for histograms
  setNiceStyle();

  // define some histograms 
  TH1I* noMuons  = new TH1I("noMuons", "N(Muon)",        10,  0 , 10 );
  TH1I* noLepts  = new TH1I("noLepts", "N(Lepton)",      10,  0 , 10 );
  TH1F* ptMuons  = new TH1F("ptMuons", "pt_{Muons}",    100,  0.,300.);
  TH1F* enMuons  = new TH1F("enMuons", "energy_{Muons}",100,  0.,300.);
  TH1F* etaMuons = new TH1F("etaMuons","eta_{Muons}",   100, -3.,  3.);
  TH1F* phiMuons = new TH1F("phiMuons","phi_{Muons}",   100, -5.,  5.);  

  // -------------------------------------------------  
  std::cout << "open  file: " << argv[1] << std::endl;
  // -------------------------------------------------
  TFile inFile(argv[1]);
  TTree* events_ = (TTree*) inFile.Get( "Events" ); assert( events_!=0 );

  // acess branch of muons and elecs
  TBranch* muons_ = events_->GetBranch( "patMuons_selectedLayer1Muons__Test.obj" ); assert( muons_!=0 );
  TBranch* elecs_ = events_->GetBranch( "patElectrons_selectedLayer1Electrons__Test.obj" ); assert( elecs_!=0 );
  
  // loop over events and fill histograms
  std::vector<pat::Muon> muons;
  std::vector<pat::Electron> elecs;
  int nevt = events_->GetEntries();

  // -------------------------------------------------  
  std::cout << "start looping " << nevt << " events..." << std::endl;
  // -------------------------------------------------
  for(int evt=0; evt<nevt; ++evt){
    // set branch address 
    muons_->SetAddress( &muons );
    elecs_->SetAddress( &elecs );
    // get event
    muons_ ->GetEntry( evt );
    elecs_ ->GetEntry( evt );
    events_->GetEntry( evt, 0 );

    // -------------------------------------------------  
    if(evt>0 && !evt%100) std::cout << "  processing event: " << evt << std::endl;
    // -------------------------------------------------  

    // fill histograms
    noMuons->Fill(muons.size());
    noLepts->Fill(muons.size()+elecs.size());
    for(unsigned idx=0; idx<muons.size(); ++idx){
      // fill histograms
      ptMuons ->Fill(muons[idx].pt()    );
      enMuons ->Fill(muons[idx].energy());
      etaMuons->Fill(muons[idx].eta()   );
      phiMuons->Fill(muons[idx].phi()   );
    }
  }
  // -------------------------------------------------  
  std::cout << "close file" << std::endl;
  // -------------------------------------------------
  inFile.Close();

  // save histograms to file
  TFile outFile( "analyzeMuons.root", "recreate" );
  outFile.mkdir("analyzeMuon");
  outFile.cd("analyzeMuon");
  noMuons ->Write( );
  noLepts ->Write( );
  ptMuons ->Write( );
  enMuons ->Write( );
  etaMuons->Write( );
  phiMuons->Write( );
  outFile.Close();

  // free allocated space
  delete noMuons;
  delete noLepts;
  delete ptMuons;
  delete enMuons;
  delete etaMuons;
  delete phiMuons;

  return 0;
}
