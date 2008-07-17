#include "TopQuarkAnalysis/Examples/plugins/TopJetAnalyzer.h"

//construntor
TopJetAnalyzer::TopJetAnalyzer(const edm::ParameterSet& iConfig)
  {
         edm::Service<TFileService> fs;
         
         
         Num_Jets = fs->make<TH1I>("Number_of_Jets","Num_{Jets}",10,0,10);
         pt_Jets= fs->make<TH1F>("pt_of_Jets","pt_{Jets}",100,0.,300.);
	 energy_Jets=fs->make<TH1F>("energy_of_Jets","energy_{Jets}",100,0.,300.);
 	 eta_Jets=fs->make<TH1F>("eta_of_Jets","eta_{Jets}",100,-3.,3.);
 	 phi_Jets=fs->make<TH1F>("phi_of_Jets","phi_{Jets}",100,-5.,5.);
 	 
  }
//destructor
TopJetAnalyzer::~TopJetAnalyzer(){}

//methods
void
TopJetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{ 
     
  using namespace edm;

  
  
  edm::Handle<std::vector<pat::Jet> > Jets;
  iEvent.getByLabel("selectedLayer1Jets", Jets); 
  Num_Jets->Fill( Jets->size());
  for (std::vector<pat::Jet>::const_iterator Jet=Jets->begin();Jet!=Jets->end();++Jet)
  {
   pt_Jets->Fill( Jet->pt());
   energy_Jets->Fill(Jet->energy());
   eta_Jets->Fill(Jet->eta());
   phi_Jets->Fill(Jet->phi());
  }    

  }
void TopJetAnalyzer::beginJob(const edm::EventSetup&){}
void TopJetAnalyzer::endJob(){}
  
