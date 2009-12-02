import FWCore.ParameterSet.Config as cms

#
# require exactly one isolated muon above 20 GeV in the central region
#

from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
leadingMuons = selectedLayer1Muons.clone()
leadingMuons.src = 'selectedLayer1Muons'
leadingMuons.cut = 'pt > 20. & abs(eta) < 2.1 & (trackIso+caloIso)/pt < 0.1'

from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
countLeadingMuons = countLayer1Muons.clone()
countLeadingMuons.src = 'leadingMuons'
countLeadingMuons.minNumber = 1
countLeadingMuons.maxNumber = 1

#
# require at least four jets above 30 GeV in the central region
#

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi  import *
leadingJets = selectedLayer1Jets.clone()
leadingJets.src = 'selectedLayer1Jets'
leadingJets.cut = 'pt > 30. & abs(eta) < 2.4'

from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
countLeadingJets = countLayer1Jets.clone()
countLeadingJets.src = 'leadingJets'
countLeadingJets.minNumber = 4

ttSemiLepEvtSelection = cms.Sequence(leadingMuons *
                                     countLeadingMuons *
                                     leadingJets *
                                     countLeadingJets)
