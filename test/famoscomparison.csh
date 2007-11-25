#! /bin/csh

if ($#argv < 1) then
    echo "(famoscomparison.csh) use: ./famoscomparison.csh [variable] [object = e/mu/jet] [index] [nbins] [min] [max] [logy = true/false] [filename1.root] [filename2.root] [events]"
    exit
endif

set variable=$1
set object=$2
if ($#argv < 2) then
    echo "(famoscomparison.csh) default object: jet"
    set object = jet
endif
set index=$3
if ($#argv < 3) then
    echo "(famoscomparison.csh) default index: 0"
    set index = 0
endif
@ order = ( $index + 1 )
echo "(famoscomparison.csh) order: ${order}"
set nbins=$4
if ($#argv < 4) then
    echo "(famoscomparison.csh) default bins: 50"
    set nbins = 50
endif
set min=$5
if ($#argv < 5) then
    echo "(famoscomparison.csh) default min: 0"
    set min = 0
endif
set max=$6
if ($#argv < 6) then
    echo "(famoscomparison.csh) default max: 300"
    set max = 300
endif
set logy=$7
if ($#argv < 7) then
    echo "(famoscomparison.csh) default logy: true"
    set logy = false
endif
set sample1=$8
if ($#argv < 8) then
    echo "(famoscomparison.csh) default sample 1: /afs/cern.ch/user/g/giamman/scratch0/data/TQAF_dilep_tt0j_full.root"
    set sample1 = /afs/cern.ch/user/g/giamman/scratch0/data/TQAF_dilep_tt0j_full.root
endif
set sample2=$9
if ($#argv < 9) then
    echo "(famoscomparison.csh) default sample 2: /afs/cern.ch/user/g/giamman/scratch0/data/TQAF_dilep_tt0j_fast.root"
    set sample2 = /afs/cern.ch/user/g/giamman/scratch0/data/TQAF_dilep_tt0j_fast.root
endif
set events=$10
if ($#argv < 10) then
    echo "(famoscomparison.csh) default number of events: 15000"
    set events = 15000
endif

if ( ${object} == jet ) then
    set class = TopJet
    set branch = selectedTopJets
else if ( ${object} == e ) then
    set class = TopElectron
    set branch = selectedTopElectrons
else if ( ${object} == mu ) then
    set class = TopMuon
    set branch = selectedTopMuons
else if ( ${object} == met ) then
    set class = TopMET
    set branch = selectedTopMETs
else
    echo "(famoscomparison.csh) unavailable object type ${object}: exiting"
    exit
endif

set member = `echo "${variable}()"`
if ( ${variable} == btag ) then
    set member = `echo getBDiscriminator\( \"trackCountingHighEffJetTags\" \)`
endif
echo "Plotting member $member"

set macro = FamosComparison.C

if (-f "${macro}") rm ${macro}
cat > ${macro} <<EOF
{
if (gSystem->Load("libFWCoreFWLite") == 0) { // if not loaded yet, load it
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");
}
#include "DataFormats/FWLite/interface/Handle.h"

gStyle->SetOptStat(0000);
gStyle->SetCanvasBorderMode(-1);
gStyle->SetCanvasBorderSize(1);
gStyle->SetCanvasColor(10);

bool logy=${logy};

TFile file1("${sample1}");
TFile file2("${sample2}");

fwlite::Event ev1(&file1);
fwlite::Event ev2(&file2);

int n1=ev1.size();
int n2=ev2.size();

int maxEv=${events};
TCanvas* myCanvas = new TCanvas("myCanvas","Jets",100,10,800,800);
myCanvas->SetFillColor(10);
myCanvas->cd();
if (logy) myCanvas->SetLogy();

TH1F* h1 = new TH1F("h1","${variable} of ${object} ${order}",${nbins},${min},${max});
int counter=0;
cout << " Opening full simulation sample (" << n1 << " events)" << endl;
for( ev1.toBegin();
     ! ev1.atEnd();
     ++ev1) {
  counter++;
  if (counter>maxEv) continue;
  fwlite::Handle<std::vector<${class}> > objsfull;
  objsfull.getByLabel(ev1,"${branch}");
  //now can access data
  if (objsfull.ptr()->size() > ${index}) {
    double var = (objsfull.ptr()->at(${index})).${member};
    h1->Fill(var);
  }
}

h1->SetLineColor(2);
h1->SetLineWidth(3);
h1->DrawCopy();
h1->DrawCopy("e same");

TH1F* h2 = new TH1F("h2","${variable} of ${object} ${order}",${nbins},${min},${max});
int counter=0;
cout << " Opening fast simulation sample (" << n2 << " events)" << endl;
for( ev2.toBegin();
     ! ev2.atEnd();
     ++ev2) {
  counter++;
  if (counter>maxEv) continue;
  fwlite::Handle<std::vector<${class}> > objsfast;
  objsfast.getByLabel(ev2,"${branch}");
  //now can access data
  if (objsfast.ptr()->size() > ${index}) {
    double var = (objsfast.ptr()->at(${index})).${member};
    h2->Fill(var);
  }
}
h2->SetLineColor(4);
h2->SetLineWidth(3);
//normalize to the fullsim area:
double scale=1.;
if (h1->Integral()!=0) scale = (h1->Integral()) / (h2->Integral());
h2->Scale(scale);
h2->DrawCopy("same");


TLegend *legend = new TLegend(0.80,0.85,0.95,0.95,"","NDC");
legend->AddEntry(h1,"full","l");
legend->AddEntry(h2,"fast","l");
legend->Draw();
myCanvas->Update();

// output:
TString gif("comparison_${variable}_${object}${order}.gif");
myCanvas->Print(gif); 

delete h1;
delete h2;
}
EOF

setenv SCRAM_ARCH slc4_ia32_gcc345
eval `scramv1 runtime -csh`

root -l <<- EOF 
    .x ${macro}
    .q
EOF
