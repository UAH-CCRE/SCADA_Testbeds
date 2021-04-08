/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration'.
 */

#ifdef MATLAB_MEX_FILE
#include "tmwtypes.h"
#else
#include "rtwtypes.h"
#endif

#include "nesl_rtw.h"
#include "tank_8a2586ff_1.h"

void tank_8a2586ff_1_gateway(void)
{
  NeModelParameters modelparams = { (NeSolverType) 2, 0.001, 0, 0.001, 0, 0, 0,
    0, (SscLoggingSetting) 0, };

  NeSolverParameters solverparams = { 0, 0, 1, 0, 0, 0.001, 1e-06, 1e-09, 0, 0,
    100, 0, 1, 1, 1, 1, (NeAdvancerChoice) 1, 0.001, 1, 12, 2,
    (NeLinearAlgebraChoice) 1, 1024, 1, 0.001, };

  const NeOutputParameters* outputparameters = NULL;
  const McLinearAlgebra* linear_algebra_ptr = ((solverparams.mLinearAlgebra ==
    NE_FULL_LA) ? get_rtw_linear_algebra() : mc_get_csparse_linear_algebra());
  NeDae* dae[1];
  size_t numOutputs = 0;

  {
    static const NeOutputParameters outputparameters_init[] = { { 0, 0,
        "tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver\nConfiguration",
      }, };

    outputparameters = outputparameters_init;
    numOutputs = sizeof(outputparameters_init)/sizeof(outputparameters_init[0]);
  }

  tank_8a2586ff_1_dae(&dae[0],
                      &modelparams,
                      &solverparams,
                      linear_algebra_ptr);
  nesl_register_simulator_group(
    "tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1",
    1,
    &dae[0],
    solverparams,
    modelparams,
    numOutputs,
    outputparameters,
    0);
}
