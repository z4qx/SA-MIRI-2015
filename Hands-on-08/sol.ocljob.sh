/bin/bash
#BSUB -J ocldot
#BSUB -n 1
#BSUB -W 00:01
#BSUB -oo "output_%J.out"
#BSUB -eo "output_%J.err"
#BSUB -R "span[ptile=1]"
#BSUB -q mic
./ocldot
