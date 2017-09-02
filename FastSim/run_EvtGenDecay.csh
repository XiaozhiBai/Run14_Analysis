#!/bin/tcsh
starver SL16d
source setup.csh
source cons.csh
 echo "start the D0 EvgGen Dcayer "
root -l -b -q StRoot/macros/run_StEvtGenDecayMaker.C'(421,100000,"D0_test.root")'
echo "D0 decay was done!"

 exit 0;
