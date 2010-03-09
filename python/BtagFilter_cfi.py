import FWCore.ParameterSet.Config as cms

filterBtag = cms.EDAnalyzer("BtagFilter",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    jets = cms.InputTag("selectedPatJets"),
                
    ## b-tagging (if bDisc has two arguments both jets have 
    ## to pass the cuts, if only one number is given only one jet
    ## has to be tagged.)
    ## for other algorithms see:
    ## https://twiki.cern.ch/twiki/bin/view/CMS/WorkBookPATExampleTrackBJet
    bAlgorithm     = cms.string('trackCountingHighEffBJetTags'),
    bDiscriminator = cms.vdouble(2.,2.)
)
