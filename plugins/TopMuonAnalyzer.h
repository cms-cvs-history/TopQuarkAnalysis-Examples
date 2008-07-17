
#ifndef TopMuonAnalyzer_h  
#define TopMuonAnalyzer_h

#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

class TopMuonAnalyzer : public edm::EDAnalyzer
   {
   public:
       explicit TopMuonAnalyzer(const edm::ParameterSet&);
      ~TopMuonAnalyzer();
   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
       	
      TH1I *Num_Leptons;

      TH1I *Num_Muons;
      TH1F *pt_Muons;
      TH1F *energy_Muons;
      TH1F *eta_Muons;
      TH1F *phi_Muons;
      
  };  
  
#endif  
