/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration'.
 */

#include "ne_std.h"
#include "pm_default_allocator.h"
#include "ne_dae_fwd.h"
#include "ne_profiler_fwd.h"
#include "ne_dae_construct.h"
#include "tank_8a2586ff_1_ds.h"

void tank_8a2586ff_1_dae( NeDae **dae, const NeModelParameters *modelParams,
  const NeSolverParameters *solverParams,
  const McLinearAlgebra *linear_algebra_ptr)
{
  PmAllocator *ne_allocator;
  ne_allocator = pm_default_allocator();
  ne_dae_create( dae,
                tank_8a2586ff_1_dae_ds( ne_allocator ),
                *solverParams,
                *modelParams,
                linear_algebra_ptr,
                NULL,
                NULL,
                NULL,
                ne_allocator);
}
