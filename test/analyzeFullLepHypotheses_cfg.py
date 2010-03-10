import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.cerr.FwkReport.reportEvery = 1 
process.MessageLogger.categories.append('TtFullLeptonicEvent')
process.MessageLogger.categories.append('BtagFilter')
process.MessageLogger.cerr.TtFullLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)   
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'rfio:/castor/cern.ch/user/d/dammann/pattutorial/ttbar_dimuon_pat.root'
    )                           
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## filter sequence
process.load("TopQuarkAnalysis.Examples.FullLeptonicSelection_cff")

## sequences for ttGenEvent and TtFullLeptonicEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff")
## enable additional per-event printout from the TtFullLeptonicEvent
process.ttFullLepEvent.verbosity = 0

## helper functions to change parameters of event reconstruction
## (can be used from tag v-6-05-02 upwards
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff import *

## change maximum number of jets taken into account per event (default: 4)
#setForAllTtFullLepHypotheses(process,"maxNJets",4)

## change input muon collection
#setForAllTtFullLepHypotheses(process,"muons","myMuons")

## change input jet collection
#setForAllTtFullLepHypotheses(process,"jets","myJets")

## change jet correction level
#setForAllTtFullLepHypotheses(process,"jetCorrectionLevel","part")


## filter for b-tagging
process.load("TopQuarkAnalysis.Examples.BtagFilter_cfi")
process.filterBtag.jets = cms.InputTag("myJets")

## load HypothesisAnalyzer
process.load("TopQuarkAnalysis.Examples.FullLepHypothesisAnalyzer_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullLepHypotheses.root')
)

## end path   
process.path = cms.Path(#process.fullLeptonicSelection *
                        process.makeGenEvt *
                        process.makeTtFullLepEvent *
			#process.filterBtag *
                        process.analyzeHypotheses)
