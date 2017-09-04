# Measurements of open bottom and charm hadron production in Au+Au collisions at STAR experiment

###### In this analysis, the primary goal is to measure the open bottom and charm production in in Au+Au collisions, which is studied by the measurement the electrons from the open heavy flavor hadrons via semi-leptonic decays. This is the fist time at STAR measured the charm andbottom quark production separately in heavy-ion collisions by the track impact parameter method.

#### The details can be found in the [Ph.D thesis chapter 4. ](https://drupal.star.bnl.gov/STAR/files/PhDthesis_0.pdf).

## How to run the analysis
---------------------------
### 1. Produce the heavy flavor decay electron DCA template from data daiven fast simulation.
        cd FastSim
        starver SL16d
        source setup.csh
        cons.csh
        ./run_EvtGenDecay.csh  %% To run the EvtGen Production and saved the intrestiong variable in the tree
        ./runAna.csh	       %% Analysis the produce tree      
### 2. Photonic electron back ground DCA can be produced by the Hijing+Geant4 full detector simulation. 

### 3. Hadron back ground extracted from data.

### 4. Inclusive electron and Photonic electron pair reconstructed from data.
       cd Data
       starver SL16d
       cons	  
       ./runTest.sh %% To run the Analysis tree, saved the Inclusive electron and Photonic electron pairs.
       cd submit    %% Directory for the job submission.
        star-submit submit_16d.xml	%% submit the Job, Please notes, the default input file list is Minimum-Bias Trigger, for the BEMC trigger, you must replace the file list from Ana_mb_16d.list to Ana_htb_16d.list 
        ./hadd.sh  0 production temp 20 %% Merge the output as a single file for the analysis  

