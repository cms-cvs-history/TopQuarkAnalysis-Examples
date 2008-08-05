import FWCore.ParameterSet.Config as cms

#
# make simple analysis plots for a comparison
# between a simple algorithmic and a gen match
# event hypothesis
#

# initialize analyzers
import TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi
analyzeMaxSumPtWMass = TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi.analyzeHypothesis.clone()

import TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi
analyzeGenMatch      = TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi.analyzeHypothesis.clone()

# configure analyzers
analyzeMaxSumPtWMass.hypoKey = 'ttSemiHypothesisMaxSumPtWMass:Key'
analyzeGenMatch.hypoKey      = 'ttSemiHypothesisGenMatch:Key'

# define sequence
analyzeAllHypotheses = cms.Sequence(analyzeMaxSumPtWMass*analyzeGenMatch)