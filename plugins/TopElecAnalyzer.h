#ifndef TopElecAnalyzer_h  
#define TopElecAnalyzer_h

#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

class TopElecAnalyzer : public edm::EDAnalyzer
   {
   public:
       explicit TopElecAnalyzer(const edm::ParameterSet&);
      ~TopElecAnalyzer();
   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      TH1I *Num_Elecs;
      TH1F *pt_Elecs;
      TH1F *energy_Elecs;
      TH1F *eta_Elecs;
      TH1F *phi_Elecs;
      
  };  
  
#endif  
