#include "classify_quad_2p2_wrapper.h"
#include <stdio.h>
#include <Python.h>

int mlp_classifier_2p2(char *mlp_pfile, double qi1, double qi2, double qo, double ali1o, double ali2o, 
                        double ei1, double ei2, double eo, double ii1i2, double ii1o, double ii2o) {
    // initialize Python interpreter
    Py_Initialize();

    // append current directory to Python's module search path
    PyObject *sys_module = PyImport_ImportModule("sys");
    PyObject *sys_path = PyObject_GetAttrString(sys_module, "path");
    PyObject *current_dir = PyUnicode_FromString(".");
    PyList_Append(sys_path, current_dir);

    // import Python module
    PyObject *py_classify_quad_2p2_module = PyImport_ImportModule("classify_quad_2p2");
    if (py_classify_quad_2p2_module == NULL) {
        PyErr_Print();
        Py_Finalize();
        return -1;
    }

    // get reference to Python function
    PyObject *py_mlp_classifier_func = PyObject_GetAttrString(py_classify_quad_2p2_module, "mlp_classifier_2p2");
    if (py_mlp_classifier_func == NULL) {
        PyErr_Print();
        Py_DECREF(py_classify_quad_2p2_module);
        Py_Finalize();
        return -1;
    }

    // prepare Python function arguments    
    PyObject *py_mlp_classifier_args = Py_BuildValue("(sddddddddddd)", mlp_pfile, qi1, qi2, qo, ali1o, ali2o, ei1, ei2, eo, ii1i2, ii1o, ii2o);
    if (py_mlp_classifier_args == NULL) {
        PyErr_Print();
        Py_DECREF(py_classify_quad_2p2_module);
        Py_DECREF(py_mlp_classifier_func);
        Py_Finalize();
        return -1;
    }

    // call Python function 
    PyObject *py_mlp_stable_ret = PyObject_CallObject(py_mlp_classifier_func, py_mlp_classifier_args);
    if (py_mlp_stable_ret == NULL) {
        PyErr_Print();
        Py_DECREF(py_classify_quad_2p2_module);
        Py_DECREF(py_mlp_classifier_func);
        Py_DECREF(py_mlp_classifier_args);
        Py_Finalize();
        return -1;
    }
    
    // convert return value to C boolean
    int mlp_stable = PyObject_IsTrue(py_mlp_stable_ret);

    // clean up Python objects
    Py_DECREF(py_classify_quad_2p2_module);
    Py_DECREF(py_mlp_classifier_func);
    Py_DECREF(py_mlp_classifier_args);
    Py_DECREF(py_mlp_stable_ret);

    // finalize Python interpreter
    Py_Finalize();

    return mlp_stable;
}

int main() {
    char mlp_pfile[] = "./mlp_model_2p2_ghost_v1.2.2.pkl";

    double mratio_inner1, mratio_inner2, mratio_outer, 
            aratio_inner1_outer, aratio_inner2_outer, 
            ecc_inner1, ecc_inner2, ecc_outer, 
            inc_inner1_inner2, inc_inner1_outer, inc_inner2_outer;
    mratio_inner1 = 1.0;
    mratio_inner2 = 1.0;
    mratio_outer = 0.5;
    aratio_inner1_outer = 0.2;
    aratio_inner2_outer = 0.2;
    ecc_inner1 = 0.0;
    ecc_inner2 = 0.0;
    ecc_outer = 0.0;
    inc_inner1_inner2 = 0.0;
    inc_inner1_outer = 0.0;
    inc_inner2_outer = 0.0;

    int mlp_stable = mlp_classifier_2p2(mlp_pfile, mratio_inner1, mratio_inner2, mratio_outer, 
                                        aratio_inner1_outer, aratio_inner2_outer, 
                                        ecc_inner1, ecc_inner2, ecc_outer, 
                                        inc_inner1_inner2, inc_inner1_outer, inc_inner2_outer);
    
    const char *mlp_stable_string;
    if (mlp_stable == 1) mlp_stable_string = "ML stable"; 
    else if (mlp_stable == 0) mlp_stable_string = "ML unstable";
    else mlp_stable_string = "ERROR";
    printf("%s\n", mlp_stable_string);

    return 0;
}

// gcc classify_quad_2p2_wrapper.c -o classify_quad_2p2_wrapper.out -I /usr/include/python3.10 -lpython3.10
