import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
## dump content of TopGenEvent
process.MessageLogger.categories.append('TopGenEvent:dump')
## print final pruned listing of top decay chain
process.MessageLogger.categories = cms.untracked.vstring('TEST')
process.MessageLogger.categories.append('TopGenEventAnalyzer::selection')
process.MessageLogger.cout = cms.untracked.PSet(
 INFO = cms.untracked.PSet(
   limit = cms.untracked.int32(10),
  )
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_2_X_2008-11-03-STARTUP_V7-AODSIM.100.root'
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
process.GlobalTag.globaltag = cms.string('STARTUP_V7::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

from TopQuarkAnalysis.Examples.TopGenEventAnalyzer_cfi import analyzeTopGenEvent
process.analyzeTopGenEvent = analyzeTopGenEvent

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTopGenEvent.root')
)

## end path   
process.p1 = cms.Path(process.patDefaultSequence *
                      process.makeGenEvt *
                      process.analyzeTopGenEvent)

