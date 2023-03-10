This repository contains two simple python3 modules to check if a given configuration of either a 2+2 or a 3+1 quadruple system, respectively, is dynamically stable. Please refer to Vynatheya et al. (2023) (see _link_) for details regarding the multi-layer perceptron classifier.

The only non-basic package require to use the code is scikit-learn, which can be installed using the following terminal command:

    pip3 install scikit-learn
    
To classify 2+2 quadruples, a sample \verb |python3| terminal command is as follows:

    python3 classify_quad_2p2.py -qi1 1.0 -qi2 1.0 -qo 1.0 -ali1o 0.2 -ali2o 0.2 -ei1 0.0 -ei2 0.0 -eo 0.0 -ii1i2 0.0 -ii1o 0.0 -ii2o 0.0
        
Here, the arguments qi1 , qi2 , qo , ali1o , ali2o , ei1 , ei2 , eo , ii1i2 , ii1o and ii2o refer to $q_{\mathrm{in_1}}$, $q_{\mathrm{in_2}}$, $q_{\mathrm{out}}$, $\alpha_{\mathrm{in_1}-\mathrm{out}}$, $\alpha_{\mathrm{in_2}-\mathrm{out}}$, $e_{\mathrm{in_1}}$, $e_{\mathrm{in_2}}$, $e_{\mathrm{out}}$, $i_{\mathrm{in_1}-\mathrm{in_2}}$, $i_{\mathrm{in_1}-\mathrm{out}}$ and $i_{\mathrm{in_2}-\mathrm{out}}$ respectively.

To classify 3+1 quadruples, a sample \verb |python3| terminal command is as follows:

    python3 classify_quad_3p1.py -qi 1.0 -qm 0.5 -qo 0.33 -alim 0.2 -almo 0.2 -ei 0.0 -em 0.0 -eo 0.0 -iim 0.0 -iio 0.0 -imo 0.0
        
Here, the arguments qi , qm , qo , alio , almo , ei , em , eo , iim , iio and imo refer to $q_{\mathrm{in}}$, $q_{\mathrm{mid}}$, $q_{\mathrm{out}}$, $\alpha_{\mathrm{in}-\mathrm{mid}}$, $\alpha_{\mathrm{mid}-\mathrm{out}}$, $e_{\mathrm{in}}$, $e_{\mathrm{mid}}$, $e_{\mathrm{out}}$, $i_{\mathrm{in}-\mathrm{mid}}$, $i_{\mathrm{in}-\mathrm{out}}$ and $i_{\mathrm{mid}-\mathrm{out}}$ respectively.

The parameter ranges should be restricted to the values given in Section \ref{sec:mlp} for optimal results.

It is also possible to import the two MLP classifiers to a custom python3 script. The input parameters can all be floating point numbers or numpy arrays, as shown in the sample script below:

    import numpy as np
    from classify_quad_2p2 import mlp_classifier_2p2
    from classify_quad_3p1 import mlp_classifier_3p1

    # 2+2 quadruples: generate initial numpy arrays
    # 3+1 quadruples: generate initial numpy arrays

    mlp_2p2_pfile = "./mlp_model_2p2_ghost.pkl"
    mlp_3p1_pfile = "./mlp_model_3p1_ghost.pkl"

    mlp_2p2_stable = mlp_classifier_2p2(mlp_2p2_pfile, qi1, qi2, qo, ali1o, ali2o, ei1, ei2, eo, ii1i2, ii1o, ii2o)
    mlp_3p1_stable = mlp_classifier_3p1(mlp_2p2_pfile, qi, qm, qo, alim, almo, ei, em, eo, iim, iio, imo)

    # returns True if stable, False if unstable

If this classification model is used for research, please cite our paper - _link_

Enjoy classifying!
