#include "TopQuarkAnalysis/Examples/plugins/TopElecAnalyzer.h"

//construntor
TopElecAnalyzer::TopElecAnalyzer(const edm::ParameterSet& iConfig)
  {
         edm::Service<TFileService> fs;
         
         
         Num_Elecs = fs->make<TH1I>("Number_of_Electrons","Num_{Elecs}",10,0,10);
         pt_Elecs= fs->make<TH1F>("pt_of_Elecs","pt_{Elecs}",100,0.,300.);
	 energy_Elecs=fs->make<TH1F>("energy_of_Elecs","energy_{Elecs}",100,0.,300.);
 	 eta_Elecs=fs->make<TH1F>("eta_of_Elecs","eta_{Elecs}",100,-3.,3.);
 	 phi_Elecs=fs->make<TH1F>("phi_of_Elecs","phi_{Elecs}",100,-5.,5.);
 	 
  }
//destructor
TopElecAnalyzer::~TopElecAnalyzer(){}

//methods
void
TopElecAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{ 
     
  using namespace edm;

  
  
  edm::Handle<std::vector<pat::Electron> > elecs;
  iEvent.getByLabel("selectedLayer1Electrons", elecs); 
  Num_Elecs->Fill( elecs->size());
  for (std::vector<pat::Electron>::const_iterator elec=elecs->begin();elec!=elecs->end();++elec)
  {
   pt_Elecs->Fill( elec->pt());
   energy_Elecs->Fill(elec->energy());
   eta_Elecs->Fill(elec->eta());
   phi_Elecs->Fill(elec->phi());
  }    

  }
void TopElecAnalyzer::beginJob(const edm::EventSetup&){}
void TopElecAnalyzer::endJob(){}
  
