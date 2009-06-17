import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3000) )

process.MessageLogger.categories.append('PATSummaryTables')

process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default          = cms.untracked.PSet( limit = cms.untracked.int32(0)  ),
    PATSummaryTables = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(  
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0007/DCDC08E0-514F-DE11-90B8-001D09F28755.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0006/867DB4EC-6D4E-DE11-B3CE-001D09F2503C.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0006/78733E8B-674E-DE11-B5F8-001617C3B654.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0006/507FABB6-7C4E-DE11-BD2B-0019B9F72CE5.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0006/4EEFB307-744E-DE11-9E19-001D09F2A465.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0006/36E83BE1-814E-DE11-8C34-000423D9863C.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0006/34BC1FBA-6B4E-DE11-ADE9-001D09F244BB.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/E69E523E-604F-DE11-BC91-003048678F26.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/D48299E4-294E-DE11-983F-00304875AA77.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/C0931F38-214E-DE11-ACA9-003048679164.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/BED51758-2D4E-DE11-A1D2-001731AF6A4B.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/92504E6F-224E-DE11-97E6-00304876A075.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/76083ABC-204E-DE11-BBF9-003048678ADA.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/60DF2595-2C4E-DE11-B4B9-0018F3D0970C.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/54A1A86E-2E4E-DE11-A1BA-0018F3D0966C.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/24925847-2B4E-DE11-9557-001A92971BB8.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/102ED6C6-2D4E-DE11-BD7B-0018F3D096F0.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValTTbar/GEN-SIM-RECO/STARTUP_31X_v1/0000/0C97089F-2C4E-DE11-85B8-0018F3D0966C.root'
   )
)

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('IDEAL_31X::All')
process.load("Configuration.StandardSequences.MagneticField_cff")

# PAT Layer 0+1
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.content = cms.EDAnalyzer("EventContentAnalyzer")

# replacements currently needed to make the taus work
process.allLayer1Taus.addTauID = False








from PhysicsTools.PatAlgos.tools.jetTools import *

## ==== Example with CaloJets
switchJetCollection(process,
       cms.InputTag('sisCone5CaloJets'),  # Jet collection; must be already in the event when patDefaultSequence is executed
       doJTA=True,                        # Run Jet-Track association & JetCharge
       doBTagging=True,                   # Run b-tagging
       jetCorrLabel=('SC5','Calo'),       # example jet correction name; set to None for no JEC
       doType1MET=True,                   # recompute Type1 MET using these jets
       genJetCollection=cms.InputTag("sisCone5GenJets"))

## ==== Example with JPT Jets
##switchJetCollection(process,
##                    cms.InputTag('JetPlusTrackZSPCorJetIcone5'),
##                    doJTA        = True,          # Run Jet-Track association & JetCharge
##                    doBTagging   = True,          # Run b-tagging
##                    jetCorrLabel = ('IC5','JPT'), # example jet correction name; set to None for no JEC
##                    doType1MET   = True,          # recompute Type1 MET using these jets
##                    genJetCollection=cms.InputTag("iterativeCone5GenJets")
##                    )




process.demo = cms.EDAnalyzer('TopDileptValidation',
                              lookAtDilepton      = cms.bool(True),   
                              lookAtMuonJets      = cms.bool(False),   
                              lookAtElectronJets  = cms.bool(False),
                              lookAtSingleTop     = cms.bool(False),
                              isTTBarEvents       = cms.bool(True),       
                              electronProducer    = cms.InputTag("selectedLayer1Electrons"),     
                              muonProducer        = cms.InputTag("selectedLayer1Muons"),      
                              jetProducer         = cms.InputTag("selectedLayer1Jets"),       
                              metProducer         = cms.InputTag("layer1METs")                                
)





process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )


process.p = cms.Path( process.patDefaultSequence*process.demo)

# Output module configuration
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('PATLayer1_Output.fromAOD_full.root'),
    # save only events passing the full path
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
    # save PAT Layer 1 output
    outputCommands = cms.untracked.vstring('drop *', *patEventContent ) # you need a '*' to unpack the list of commands 'patEventContent'
)
#process.outpath = cms.EndPath(process.out)
