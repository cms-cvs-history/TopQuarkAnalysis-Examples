import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.categories.append('TtSemiLepJetCombMVATrainer')
process.MessageLogger.cerr.TtSemiLepJetCombMVATrainer = cms.untracked.PSet(
    limit = cms.untracked.int32(-1) 
)
process.MessageLogger.cerr.FwkReport.reportEvery = 10

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_1.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_2.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_3.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_4.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_5.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_6.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_7.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_8.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_9.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_10.root'    
     ),
     skipEvents = cms.untracked.uint32(0)                            
)
## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V1::All')

## std sequence for ttGenEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## configure ttGenEventFilters
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## configure jet-parton matching
process.load("TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi")

## configure mva trainer
process.load("TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVATrainTreeSaver_cff")
## change maximum number of jets taken into account per event (default: 4)
#process.ttSemiLepJetPartonMatch .maxNJets = 5
#process.trainTtSemiLepJetCombMVA.maxNJets = process.ttSemiLepJetPartonMatch.maxNJets

## make trainer looper known to the process
from TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVATrainTreeSaver_cff import looper
process.looper = looper

process.p = cms.Path(process.makeGenEvt *
                     process.ttSemiLeptonicFilter *
                     process.ttSemiLepJetPartonMatch *
                     process.saveTtSemiLepJetCombMVATrainTree)
