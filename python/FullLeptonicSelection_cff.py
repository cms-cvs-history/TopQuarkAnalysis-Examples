import FWCore.ParameterSet.Config as cms


## selectors to build new collection of objects fullfilling given cuts
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

## muon selection
myMuons = selectedPatMuons.clone(src = 'selectedPatMuons', 
                                    cut = 'pt > 20. & abs(eta) < 2.4' )
## jet selection
myJets = selectedPatJets.clone(src = 'selectedPatJets', 
                                  cut = 'pt > 30. & abs(eta) < 2.4' )



## count filters to cut on the number of objects in a given collection
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *

## at least two muons
muonSelection  = countPatMuons.clone(src = 'myMuons', minNumber = 2)

## at least two jets
jetSelection  = countPatJets.clone(src = 'myJets', minNumber = 2)


## define filter sequences
buildCollections = cms.Sequence(myMuons * myJets)

filterObjects = cms.Sequence(muonSelection * jetSelection)

fullLeptonicSelection = cms.Sequence(buildCollections * filterObjects)
