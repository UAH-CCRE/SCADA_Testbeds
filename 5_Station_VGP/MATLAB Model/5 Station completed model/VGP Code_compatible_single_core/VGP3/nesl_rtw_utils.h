/*********************************************************************************************************************
 ** File: nesl_rtw_utils.h
 ** Abstract:
 **     Utility functions to be called in generated code.
 **     This header must be included after _nesl_rtw.h
 **
 ** Copyright 2013-2014 The MathWorks, Inc.
 *********************************************************************************************************************/


#ifndef __nesl_rtw_utils_h__
#define __nesl_rtw_utils_h__

#define SAFE_DESTROY(_obj)                      \
    if (_obj != NULL) {                         \
        _obj->mDestroy(_obj);                   \
    }                                           \


/*
 * NeslSimulator
 */

PMF_DEPLOY_STATIC NeslSimulator *nesl_lease_simulator( const char *key,
                                                       int category,
                                                       int index)
{
    const NeslSimulatorGroupRegistry *registry = nesl_get_registry();
    return (NeslSimulator *)(registry->mLeaseSimulator(registry, key,
                                                       (NeslSimulatorCategory)category,
                                                       (size_t)index));
}

PMF_DEPLOY_STATIC void nesl_erase_simulator(const char *key)
{
    const NeslSimulatorGroupRegistry *registry = nesl_get_registry();
    registry->mErase(registry, key);
}

PMF_DEPLOY_STATIC int32_T nesl_initialize_simulator( NeslSimulator *simulator,
                                                     NeModelParameters mp,
                                                     NeuDiagnosticManager *mgr)
{
    return simulator->mInitialize(simulator,mp,mgr);
}

PMF_DEPLOY_STATIC void nesl_simulator_set_rtps( NeslSimulator *simulator,
                                                NeParameterBundle bundle)
{
    simulator->mSetParameters(simulator,&bundle);
}


/*
 * NeslSimulationData
 */

PMF_DEPLOY_STATIC void nesl_destroy_simulation_data(NeslSimulationData *sd)
{
    SAFE_DESTROY(sd)
}


/*
 * NeuDiagnosticManager
 */

PMF_DEPLOY_STATIC void neu_destroy_diagnostic_manager(NeuDiagnosticManager *mgr)
{
    SAFE_DESTROY(mgr)
}

PMF_DEPLOY_STATIC NeuDiagnosticTree *neu_diagnostic_manager_get_initial_tree(
    const NeuDiagnosticManager *mgr)
{
    /* Const cast required -- passing through RTWCG-generated pointer type */
    return (NeuDiagnosticTree *)(mgr->mGetInitialTree(mgr));
}


/*
 * Reporting diagnostics
 */

#define RTW_DIAGNOSTICS_MESSAGE_BUFFER_SIZE 1024

PMF_DEPLOY_STATIC char *static_diagnostics_msg_buffer(void)
{
    static char msgBuffer[RTW_DIAGNOSTICS_MESSAGE_BUFFER_SIZE];
    return msgBuffer;
}

PMF_DEPLOY_STATIC char *rtw_diagnostics_msg(const NeuDiagnosticTree *tree)
{
    /* get static message buffer */
    char *msgBuffer = static_diagnostics_msg_buffer();

    /* create printer and print */
    NeuDiagnosticTreePrinter *printer =
        neu_create_diagnostic_tree_printer(pm_default_allocator());
    const char *msg = printer->mPrint(printer, tree);

    /* put the message into the buffer */
    strncpy( msgBuffer, msg, RTW_DIAGNOSTICS_MESSAGE_BUFFER_SIZE - 1);

    /* clean up */
    printer->mDestroy(printer);

    /* return the static message buffer */
    return msgBuffer;
}

PMF_DEPLOY_STATIC NeuDiagnosticManager *rtw_create_diagnostics()
{
    return neu_create_diagnostic_manager(pm_default_allocator());
}

PMF_DEPLOY_STATIC char *solver_mismatch_message(const char *solverInMdl,
                                                const char *solverToRun)
{
    char *msgBuffer = static_diagnostics_msg_buffer();
    sprintf(msgBuffer,
            "Detected inconsistent solvers in the model reference hierarchy. "
            "Model was built with %s, but the top model uses %s. "
            "Use the same solver in the top model and all referenced models.",
            solverInMdl,solverToRun);
    return msgBuffer;
}


/*
 * Pointer-arithmetic (not supported by RTWCG)
 */

PMF_DEPLOY_STATIC boolean_T pointer_is_null(void *ptr)
{
    return (ptr == NULL);
}

PMF_DEPLOY_STATIC boolean_T error_buffer_is_empty(const char *ptr)
{
    return (ptr == NULL);
}

PMF_DEPLOY_STATIC double *double_pointer_shift(double *base, int offset)
{
    return &(base[offset]);
}

#endif /* __nesl_rtw_utils_h__ */
/* [EOF] nesl_rtw_utils.h */
