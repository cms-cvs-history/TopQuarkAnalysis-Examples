#ifndef TopJetAnalyzer_h  
#define TopJetAnalyzer_h

#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

class TopJetAnalyzer : public edm::EDAnalyzer
   {
   public:
       explicit TopJetAnalyzer(const edm::ParameterSet&);
      ~TopJetAnalyzer();
   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      TH1I *Num_Jets;
      TH1F *pt_Jets;
      TH1F *energy_Jets;
      TH1F *eta_Jets;
      TH1F *phi_Jets;
      
  };  
  
#endif  
