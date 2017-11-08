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
### 2. Photonic electron background DCA can be produced by the Hijing+Geant4 full detector simulation. 
#### 2.1 Produce the Hijing and Geant sample
        cd PhotonicElectronSim/Pico_mc
        starver SL16d	
        cons
        ./submit_full.sh start#  #nRuns  %% submit the job to make the mass production, it will be spend 3-4h per job, the full production can be found at /star/u/kunsu/auau200GeVRun14/simulation_RealDetector_RealParticle_SL16d_Pixelisation/files_full/* 
#### 2.2 Saved all the intrestiong variable in the analysis tree based on the produced PicoTree.
        cd PhotonicElectronSim/Ana_mc
        starver SL16d
        cons  
        ./run_Test.sh  %% To run a few test files.
        star-submit submit.xml	 %% submit the job to analysis the full production, clean all the output directory before submit the job.
#### 2.3 Analysis the McPico tree. fill the histogram
        cd /PhotonicElectronSim/Histogram_mc
        starver SL16d
        cons
        ./run_test.sh %%to run a few test files 
        star-submit submit.xml %% submit the job to analysis the full production, clean all the output directory before submit the job.  
 ### 3. Hadron background extracted from data.
#### The code can be found at https://github.com/XiaozhiBai/Run14_PicoReader. Notes, we Saved only the laptons candidate in the analysis tree on the RCF, so the hadron background templte and purity study are still based on the PicoDst, which is on the PDSF.
       cd /global/homes/x/xiao00/pwg_disk/AuAu14/Run14_PicoReader
       starver SL16d
       cons
       cd Submit_Job
       ./submitAnaTreePDSF.sh mb 0 107 167 %% submit the job from day 107 to 167
       cd ../Merge_files 
       ././run_hadd.sh 0 100   %% submit the job to merge the root files.
### 4. Inclusive electron and Photonic electron pair reconstructed from data.
       cd Data
       starver SL16d
       cons	  
       ./runTest.sh %% To run the Analysis tree, saved the Inclusive electron and Photonic electron pairs.
       cd submit    %% Directory for the job submission.
       star-submit submit_16d.xml	%% submit the Job, Please notes, the default input file list is Minimum-Bias Trigger, for the BEMC trigger, you must replace the file list from Ana_mb_16d.list to Ana_htb_16d.list 
       ./hadd.sh  0 production temp 20 %% Merge the output as a single file for the analysis  

## How to combine different heavy flavor decay hadrons electrons template.

### 1. Produce the heavy flavor decay electron DCA template from data daiven fast simulation.

### 2. Produce the heavy flavor decay electron DCA template from data daiven fast simulation.