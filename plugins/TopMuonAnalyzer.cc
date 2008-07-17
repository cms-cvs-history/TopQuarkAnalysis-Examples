#include "/afs/cern.ch/user/m/mzeinali/CMSSW_1_6_12/src/TopQuarkAnalysis/Examples/interface/TopMuonAnalyzer.h"

//construntor
TopMuonAnalyzer::TopMuonAnalyzer(const edm::ParameterSet& iConfig)
  {
         edm::Service<TFileService> fs;
         
         Num_Muons = fs->make<TH1I>("Number_of_Muons","Num_{Muons}",10,0,10);
	 Num_Leptons=fs->make<TH1I>("Number_of_Leptons","Num_{Leptons}",10,0,10);
         pt_Muons = fs->make<TH1F>("pt_of_Muons","pt_{Muons}",100,0.,300.);
	 energy_Muons=fs->make<TH1F>("energy_of_Muons","energy_{Muons}",100,0.,300.);
	 eta_Muons=fs->make<TH1F>("eta_of_Muons","eta_{Muons}",100,-3.,3.);
	 phi_Muons=fs->make<TH1F>("phi_of_Muons","phi_{Muons}",100,-5.,5.);
	 
  }
//destructor
TopMuonAnalyzer::~TopMuonAnalyzer(){}

//methods
void
TopMuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{ 
     
  using namespace edm;

  edm::Handle<std::vector<pat::Electron> > elecs;
  iEvent.getByLabel("selectedLayer1Electrons", elecs);
  

  edm::Handle<std::vector<pat::Muon> > muons;
  iEvent.getByLabel("selectedLayer1Muons", muons); 
  Num_Muons->Fill( muons->size()); 
  
  Num_Leptons->Fill( elecs->size() + muons->size() );

  for (std::vector<pat::Muon>::const_iterator muon=muons->begin();muon!=muons->end(); ++muon)
  {
   pt_Muons->Fill( muon->pt());
   energy_Muons->Fill(muon->energy());
   eta_Muons->Fill(muon->eta());
   phi_Muons->Fill(muon->phi());
  }   
  
}
void TopMuonAnalyzer::beginJob(const edm::EventSetup&){}
void TopMuonAnalyzer::endJob(){}
