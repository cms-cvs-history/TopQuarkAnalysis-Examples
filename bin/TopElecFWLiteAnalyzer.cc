#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
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
  TH1I* noElecs  = new TH1I("noElecs", "N_{Elecs}",      10,  0 , 10 );
  TH1F* ptElecs  = new TH1F("ptElecs", "pt_{Elecs}",    100,  0.,300.);
  TH1F* enElecs  = new TH1F("enElecs", "energy_{Elecs}",100,  0.,300.);
  TH1F* etaElecs = new TH1F("etaElecs","eta_{Elecs}",   100, -3.,  3.);
  TH1F* phiElecs = new TH1F("phiElecs","phi_{Elecs}",   100, -5.,  5.);  
  
  // -------------------------------------------------  
  std::cout << "open  file: " << argv[1] << std::endl;
  // -------------------------------------------------
  TFile inFile(argv[1]);
  TTree* events_ = (TTree*) inFile.Get( "Events" ); assert( events_!=0 );

  // acess branch of elecs
  TBranch* elecs_ = events_->GetBranch( "patElectrons_selectedLayer1Electrons__Test.obj" ); assert( elecs_!=0 );
  
  // loop over events and fill histograms
  std::vector<pat::Electron> elecs;
  int nevt = events_->GetEntries();

  // -------------------------------------------------  
  std::cout << "start looping " << nevt << " events..." << std::endl;
  // -------------------------------------------------
  for(int evt=0; evt<nevt; ++evt){
    // set branch address 
    elecs_->SetAddress( &elecs );
    // get event
    elecs_ ->GetEntry( evt );
    events_->GetEntry( evt, 0 );

    // -------------------------------------------------  
    if(evt>0 && !evt%100) std::cout << "  processing event: " << evt << std::endl;
    // -------------------------------------------------  

    // fill histograms
    noElecs->Fill(elecs.size());
    for(unsigned idx=0; idx<elecs.size(); ++idx){
      // fill histograms
      ptElecs ->Fill(elecs[idx].pt()    );
      enElecs ->Fill(elecs[idx].energy());
      etaElecs->Fill(elecs[idx].eta()   );
      phiElecs->Fill(elecs[idx].phi()   );
    }
  }
  // -------------------------------------------------  
  std::cout << "close file" << std::endl;
  // -------------------------------------------------
  inFile.Close();

  // save histograms to file
  TFile outFile( "analyzeElecs.root", "recreate" );
  outFile.mkdir("analyzeElec");
  outFile.cd("analyzeElec");
  noElecs ->Write( );
  ptElecs ->Write( );
  enElecs ->Write( );
  etaElecs->Write( );
  phiElecs->Write( );
  outFile.Close();

  // free allocated space
  delete noElecs;
  delete ptElecs;
  delete enElecs;
  delete etaElecs;
  delete phiElecs;

  return 0;
}
