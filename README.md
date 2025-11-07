# Stability classification of quadruple-star systems

This repository contains two simple `python3` (3.10.0 or higher) modules to check if a given configuration of either a 2+2 or a 3+1 quadruple system, respectively, is dynamically stable. Please refer to Vynatheya et al. (2023) (see https://ui.adsabs.harvard.edu/abs/2023arXiv230109930V/abstract) for details regarding the multi-layer perceptron classifier. A `C`/`C++` interface is also provided.

The only non-basic package require to use the code is a compatible version (1.0.2 or 1.2.2) of the scikit-learn package (the latest version should also work, but throws a warning of potential incompatibility), which can be installed using the following terminal command:

    # pip3 install -v scikit-learn==1.0.2
    pip3 install -v scikit-learn==1.2.2

    
## Implementing our classifiers in `python3` (simplest option)

To classify 2+2 quadruples, a sample python3 terminal command is as follows:

    python3 classify_quad_2p2.py -qi1 1.0 -qi2 1.0 -qo 1.0 -ali1o 0.2 -ali2o 0.2 -ei1 0.0 -ei2 0.0 -eo 0.0 -ii1i2 0.0 -ii1o 0.0 -ii2o 0.0
        
Here, the arguments `qi1` , `qi2` , `qo` , `ali1o` , `ali2o` , `ei1` , `ei2` , `eo` , `ii1i2` , `ii1o` and `ii2o` refer to $q_{\mathrm{in_1}}$, $q_{\mathrm{in_2}}$, $q_{\mathrm{out}}$, $\alpha_{\mathrm{in_1}-\mathrm{out}}$, $\alpha_{\mathrm{in_2}-\mathrm{out}}$, $e_{\mathrm{in_1}}$, $e_{\mathrm{in_2}}$, $e_{\mathrm{out}}$, $i_{\mathrm{in_1}-\mathrm{in_2}}$, $i_{\mathrm{in_1}-\mathrm{out}}$ and $i_{\mathrm{in_2}-\mathrm{out}}$ respectively.

To classify 3+1 quadruples, a sample python3 terminal command is as follows:

    python3 classify_quad_3p1.py -qi 1.0 -qm 0.5 -qo 0.33 -alim 0.2 -almo 0.2 -ei 0.0 -em 0.0 -eo 0.0 -iim 0.0 -iio 0.0 -imo 0.0
        
Here, the arguments `qi` , `qm` , `qo` , `alio` , `almo` , `ei` , `em` , `eo` , `iim` , `iio` and `imo` refer to $q_{\mathrm{in}}$, $q_{\mathrm{mid}}$, $q_{\mathrm{out}}$, $\alpha_{\mathrm{in}-\mathrm{mid}}$, $\alpha_{\mathrm{mid}-\mathrm{out}}$, $e_{\mathrm{in}}$, $e_{\mathrm{mid}}$, $e_{\mathrm{out}}$, $i_{\mathrm{in}-\mathrm{mid}}$, $i_{\mathrm{in}-\mathrm{out}}$ and $i_{\mathrm{mid}-\mathrm{out}}$ respectively.

The parameter (described in Section 2 of the quadruples paper) ranges should be restricted to the values given in Section 3.1 of the quadruples paper for optimal results.

It is also possible to import the two MLP classifiers to a custom python3 script. The input parameters can all be floating point numbers or numpy arrays, as shown in the sample script below:

    import numpy as np
    # 'import sklearn' is not necessary, but scikit-learn needs to be installed
    from classify_quad_2p2 import mlp_classifier_2p2
    from classify_quad_3p1 import mlp_classifier_3p1

    # 2+2 quadruples: generate initial numpy arrays
    # 3+1 quadruples: generate initial numpy arrays

    mlp_2p2_pfile = "./mlp_model_2p2_ghost_v1.2.2.pkl"
    mlp_3p1_pfile = "./mlp_model_3p1_ghost_v1.2.2.pkl"

    mlp_2p2_stable = mlp_classifier_2p2(mlp_2p2_pfile, qi1, qi2, qo, ali1o, ali2o, ei1, ei2, eo, ii1i2, ii1o, ii2o)
    mlp_3p1_stable = mlp_classifier_3p1(mlp_2p2_pfile, qi, qm, qo, alim, almo, ei, em, eo, iim, iio, imo)
    
    # mlp_2p2_stable, mlp_3p1_stable store True if stable, False if unstable


## Implementing our classifiers in `C`/`C++`

One way to include our classifiers in `C` is to use a `python` interface. This is done by including the `Python.h` header file. This should already be present in your system by default, but if not, python3-dev should be installed. `classify_quad_2p2_wrapper.c` and `classify_quad_3p1_wrapper.c` implement this and should be compiled as follows:

    gcc classify_quad_2p2_wrapper.c -o classify_quad_2p2_wrapper.out -I /usr/include/python3.10 -lpython3.10    
    gcc classify_quad_3p1_wrapper.c -o classify_quad_3p1_wrapper.out -I /usr/include/python3.10 -lpython3.10

The `-I` flag is only necessary if the `python` header files are not in the system path, and the `-lpython3.10` flag allows `C` to interact with `python3` (3.10.0 or higher). To include the wrapper script in a custom `C`/`C++` script, it is sufficient to include the header files `classify_quad_2p2_wrapper.h` or `classify_quad_3p1_wrapper.h`. In this case, comment out/remove the `main()` function from `classify_quad_2p2_wrapper.c` or `classify_quad_3p1_wrapper.c`. An example is as follows:

    #include "classify_quad_2p2_wrapper.h"
    #include "classify_quad_3p1_wrapper.h"

    int main() {
        char mlp_2p2_pfile[] = "./mlp_model_3p1_ghost_v1.2.2.pkl";
        char mlp_3p1_pfile[] = "./mlp_model_2p2_ghost_v1.2.2.pkl";

        double qi1, qi2, qo, ali1o, ali2o, ei1, ei2, eo, ii1i2, ii1o, ii2o; // for 2+2
        double qi, qm, qo, alim, almo, ei, em, eo, iim, iio, imo; // for 3+1
            
        // define these quantities

        int mlp_2p2_stable = mlp_classifier_2p2(mlp_2p2_pfile, qi1, qi2, qo, ali1o, ali2o, ei1, ei2, eo, ii1i2, ii1o, ii2o);
        int mlp_3p1_stable = mlp_classifier_3p1(mlp_3p1_pfile, qi, qm, qo, alim, almo, ei, em, eo, iim, iio, imo);

        // mlp_2p2_stable, mlp_3p1_stable store 0 if stable, 1 if unstable

        return 0;
    }

This custom script (`C` and `C++` respectively) is compiled similarly:

    gcc my_program.c classify_quad_2p2_wrapper.c -o my_program.out -I /usr/include/python3.10 -lpython3.10
    gcc my_program.c classify_quad_3p1_wrapper.c -o my_program.out -I /usr/include/python3.10 -lpython3.10
    g++ my_program.cpp classify_quad_2p2_wrapper.c -o my_program.out -I /usr/include/python3.10 -lpython3.10
    g++ my_program.cpp classify_quad_3p1_wrapper.c -o my_program.out -I /usr/include/python3.10 -lpython3.10


## Citing our work

If these classification models are used for research, please cite our paper - https://ui.adsabs.harvard.edu/abs/2023arXiv230109930V/abstract (mlp_model_2p2_ghost.pkl and mlp_model_3p1_ghost.pkl).

Enjoy classifying!
