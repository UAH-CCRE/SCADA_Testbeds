#ifndef _nesl_rtw_h
#define _nesl_rtw_h
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
int_T pm_create_sparsity_pattern_fields(PmSparsityPattern *patternPtr, size_t
nNzMax, size_t nRow, size_t nCol, PmAllocator *allocator); PmSparsityPattern
*pm_create_sparsity_pattern(size_t nNzMax, size_t nRow, size_t nCol, PmAllocator
*allocatorPtr); void pm_sp_equals_sp(PmSparsityPattern *Ap, const
PmSparsityPattern *Bp); boolean_T pm_sp_equalequals_sp(const PmSparsityPattern
*Ap, const PmSparsityPattern *Bp); PmSparsityPattern
*pm_copy_sparsity_pattern(const PmSparsityPattern *input_pattern, PmAllocator
*allocatorPtr); void pm_destroy_sparsity_pattern_fields(PmSparsityPattern
*patternPtr, PmAllocator *allocator); void
pm_destroy_sparsity_pattern(PmSparsityPattern *patternPtr, PmAllocator
*allocatorPtr); PmSparsityPattern *pm_create_full_sparsity_pattern(size_t nrows,
size_t ncols, PmAllocator *allocatorPtr); PmSparsityPattern
*pm_create_empty_sparsity_pattern(size_t nrows, size_t ncols, PmAllocator
*allocatorPtr); PmSparsityPattern
*pm_create_partial_identity_sparsity_pattern(size_t p, size_t n, PmAllocator
*allocatorPtr); PmSparsityPattern *pm_create_identity_sparsity_pattern(size_t n,
PmAllocator *allocatorPtr); void pm_rv_equals_rv(const PmRealVector *xPtr, const
PmRealVector *yPtr); void pm_iv_equals_iv(const PmIntVector *xPtr, const
PmIntVector *yPtr); void pm_bv_equals_bv(const PmBoolVector *xPtr, const
PmBoolVector *yPtr); void pm_cv_equals_cv(const PmCharVector *xPtr, const
PmCharVector *yPtr); boolean_T pm_rv_equalequals_rv(const PmRealVector
*xPtr,const PmRealVector *yPtr); boolean_T pm_iv_equalequals_iv(const PmIntVector
*xPtr,const PmIntVector *yPtr); boolean_T pm_bv_equalequals_bv(const PmBoolVector
*xPtr,const PmBoolVector *yPtr); int_T pm_create_real_vector_fields(PmRealVector
*vecPtr, size_t size, PmAllocator *allocatorPtr); PmRealVector
*pm_create_real_vector(size_t numElements,PmAllocator *allocatorPtr);
PmRealVector *pm_copy_real_vector(const PmRealVector *vecPtr, PmAllocator
*allocatorPtr); void pm_destroy_real_vector_fields(PmRealVector *vecPtr,
PmAllocator *allocatorPtr); void pm_destroy_real_vector(PmRealVector *vecPtr,
PmAllocator *allocatorPtr); int_T pm_create_int_vector_fields(PmIntVector
*vecPtr, size_t size, PmAllocator *allocatorPtr); PmIntVector
*pm_create_int_vector(size_t numElements,PmAllocator *allocatorPtr); PmIntVector
*pm_copy_int_vector(const PmIntVector *vecPtr, PmAllocator *allocatorPtr); void
pm_destroy_int_vector_fields(PmIntVector *vecPtr, PmAllocator *allocatorPtr);
void pm_destroy_int_vector(PmIntVector *vecPtr, PmAllocator *allocatorPtr); int_T
pm_create_bool_vector_fields(PmBoolVector *vecPtr, size_t size, PmAllocator
*allocatorPtr); PmBoolVector *pm_create_bool_vector(size_t
numElements,PmAllocator *allocatorPtr); void
pm_destroy_bool_vector_fields(PmBoolVector *vecPtr, PmAllocator *allocatorPtr);
void pm_destroy_bool_vector(PmBoolVector *vecPtr, PmAllocator *allocatorPtr);
PmBoolVector *pm_copy_bool_vector(const PmBoolVector *vecPtr, PmAllocator
*allocatorPtr); int_T pm_create_char_vector_fields(PmCharVector *vecPtr, size_t
size, PmAllocator *allocatorPtr); PmCharVector *pm_create_char_vector(size_t
numElements,PmAllocator *allocatorPtr); void
pm_destroy_char_vector_fields(PmCharVector *vecPtr, PmAllocator *allocatorPtr);
void pm_destroy_char_vector(PmCharVector *vecPtr, PmAllocator *allocatorPtr);
typedef enum McLinearAlgebraStatusTag { MC_LA_INVALID = -1, MC_LA_ERROR, MC_LA_OK
}McLinearAlgebraStatus; typedef struct McLinearAlgebraDataTag
McLinearAlgebraData; typedef McLinearAlgebraData* (*McLinearAlgebraConstructor)
(PmAllocator*, const PmSparsityPattern*); typedef McLinearAlgebraStatus
(*McLinearAlgebraSymbolic) (McLinearAlgebraData*); typedef McLinearAlgebraStatus
(*McLinearAlgebraNumeric) (McLinearAlgebraData*, const real_T*); typedef
McLinearAlgebraStatus (*McLinearAlgebraSolve) (McLinearAlgebraData*, const
real_T*, real_T*, const real_T*); typedef void (*McLinearAlgebraNumericDestroy)
(McLinearAlgebraData*); typedef void (*McLinearAlgebraSymbolicDestroy)
(McLinearAlgebraData*); typedef void (*McLinearAlgebraDestructor) (PmAllocator*,
McLinearAlgebraData*); struct McLinearAlgebraTag{ McLinearAlgebraConstructor
mConstructor; McLinearAlgebraSymbolic mSymbolic; McLinearAlgebraNumeric mNumeric;
McLinearAlgebraSolve mSolve; McLinearAlgebraNumericDestroy mNumericDestroy;
McLinearAlgebraSymbolicDestroy mSymbolicDestroy; McLinearAlgebraDestructor
mDestructor; }; const McLinearAlgebra *mc_get_csparse_linear_algebra(void);
real_T mc_csparse_cond(const void* mcLaData); NeSystemInputSizes
neu_get_empty_system_input_sizes(void); NeSystemInputSizes
neu_get_system_input_sizes(const NeSystemInput *in); NeSystemInput
*neu_create_system_input(NeSystemInputSizes sizes, PmAllocator *allocatorPtr);
void neu_destroy_system_input(NeSystemInput *sysInputPtr, PmAllocator
*allocatorPtr); NeDynamicSystemInputSizes
neu_get_empty_dynamic_system_input_sizes(void); NeDynamicSystemInputSizes
neu_get_dynamic_system_input_sizes(const NeDynamicSystemInput *in);
NeDynamicSystemInput *neu_create_dynamic_system_input(NeDynamicSystemInputSizes
sizes, PmAllocator *allocatorPtr); void
neu_destroy_dynamic_system_input(NeDynamicSystemInput *sysInputPtr, PmAllocator
*allocatorPtr); void neu_si_equals_si(const NeSystemInput *destPtr, const
NeSystemInput *srcPtr); NeSystemInput *neu_copy_si(const NeSystemInput *in,
PmAllocator *al); void neu_dsi_equals_dsi(const NeDynamicSystemInput *destPtr,
const NeDynamicSystemInput *srcPtr); NeDynamicSystemInput *neu_copy_dsi(const
NeDynamicSystemInput *in, PmAllocator *al); boolean_T neu_si_equalequals_si(const
NeSystemInput *destPtr, const NeSystemInput *srcPtr); boolean_T
neu_sis_equalequals_sis(const NeSystemInputSizes left, const NeSystemInputSizes
right); boolean_T neu_dsi_equalequals_dsi(const NeDynamicSystemInput *destPtr,
const NeDynamicSystemInput *srcPtr); boolean_T neu_dsis_equalequals_dsis(const
NeDynamicSystemInputSizes left, const NeDynamicSystemInputSizes right); typedef
struct NeDaeTag NeDae; typedef struct NeProfilerTag NeProfiler; typedef struct
NeSolverSystemTag NeSolverSystem; typedef struct NeuDiagnosticTreeTag
NeuDiagnosticTree; typedef struct NeuDiagnosticManagerTag NeuDiagnosticManager;
typedef enum { NEU_DIAGNOSTIC_LEVEL_INVALID = -1, NEU_DIAGNOSTIC_LEVEL_TERSE,
NEU_DIAGNOSTIC_LEVEL_VERBOSE, NEU_NUM_DIAGNOSTIC_LEVELS } NeuDiagnosticLevel;
typedef NeuDiagnosticTree *NeuDiagnosticId; typedef struct
NeuDiagnosticManagerPrivateDataTag NeuDiagnosticManagerPrivateData; struct
NeuDiagnosticManagerTag { NeuDiagnosticManagerPrivateData *mPrivateData;
NeuDiagnosticId (*mStartSubtree) ( const NeuDiagnosticManager *mgr ); void
(*mFinishSubtree) ( const NeuDiagnosticManager *mgr, NeuDiagnosticId diagId,
NeuDiagnosticLevel verbosity, PmfMessageId msgId, va_list args ); void
(*mFinishSubtreeUser) ( const NeuDiagnosticManager *mgr, NeuDiagnosticId diagId,
NeuDiagnosticLevel verbosity, PmfMessageId msgId, va_list args ); void
(*mClearSubtree) ( const NeuDiagnosticManager *mgr, NeuDiagnosticId diagId );
void (*mTransferTree) ( const NeuDiagnosticManager *dest, const
NeuDiagnosticManager *src ); const NeuDiagnosticTree * (*mGetInitialTree) ( const
NeuDiagnosticManager *mgr ); void (*mDestroy) ( NeuDiagnosticManager *mgr ); };
PmfMessageId neu_diagnostic_finish_subtree( const NeuDiagnosticManager *mgr,
NeuDiagnosticId diagId, NeuDiagnosticLevel verbosity, PmfMessageId msgId, ... );
PmfMessageId neu_diagnostic_finish_subtree_user( const NeuDiagnosticManager *mgr,
NeuDiagnosticId diagId, NeuDiagnosticLevel verbosity, PmfMessageId msgId, ... );
PmfMessageId neu_diagnostic_one_node_subtree( const NeuDiagnosticManager *mgr,
NeuDiagnosticLevel verbosity, PmfMessageId msgId, ... ); PmfMessageId
neu_diagnostic_finish_subtree_preformatted( const NeuDiagnosticManager *mgr,
NeuDiagnosticId diagId, NeuDiagnosticLevel verbosity, PmfMessageId msgId, const
char* msg ); PmfMessageId neu_diagnostic_one_node_subtree_preformatted( const
NeuDiagnosticManager *mgr, NeuDiagnosticLevel verbosity, PmfMessageId msgId,
const char *msg ); NeuDiagnosticManager
*neu_create_diagnostic_manager(PmAllocator *alloc); typedef struct
NeuDiagnosticTreePrinterTag NeuDiagnosticTreePrinter; typedef struct
NeuDiagnosticTreePrinterPrivateDataTag NeuDiagnosticTreePrinterPrivateData;
struct NeuDiagnosticTreePrinterTag { NeuDiagnosticTreePrinterPrivateData
*mPrivateData; const char * (*mPrint) (NeuDiagnosticTreePrinter *printer, const
NeuDiagnosticTree *tree); void (*mDestroy) (NeuDiagnosticTreePrinter *printer);
}; NeuDiagnosticTreePrinter *neu_create_diagnostic_tree_printer(PmAllocator
*alloc); const char *neu_tree_viewer_get_id(const NeuDiagnosticTree *tree); const
char *neu_tree_viewer_get_msg(const NeuDiagnosticTree *tree); NeuDiagnosticLevel
neu_tree_viewer_get_level(const NeuDiagnosticTree *tree); size_t
neu_tree_viewer_get_num_causes(const NeuDiagnosticTree *tree); const
NeuDiagnosticTree *neu_tree_viewer_get_cause_k(const NeuDiagnosticTree *tree,
size_t k); void neu_diagnostic_tree_warning(const NeuDiagnosticTree *tree); void
nes_dae_get_base_methods(NeDae *dae_ptr); PmIntVector
*nes_compute_output_function_map( const PmSparsityPattern *duy, uint32_T
inputOrder); typedef struct NeModelParametersTag NeModelParameters; typedef enum
SscDiagnosticSettingTag { SSC_DIAGNOSTIC_INVALID = -1, SSC_DIAGNOSTIC_ERROR,
SSC_DIAGNOSTIC_WARNING, SSC_DIAGNOSTIC_NONE, SSC_DIAGNOSTIC_NUM }
SscDiagnosticSetting; typedef enum SscLoggingSettingTag { SSC_LOGGING_INVALID =
-1, SSC_LOGGING_NONE, SSC_LOGGING_ALL, SSC_LOGGING_LOCAL, SSC_LOGGING_NUM }
SscLoggingSetting; typedef enum NeSolverTypeTag { NE_SOLVER_TYPE_INVALID = -1,
NE_SOLVER_TYPE_DAE, NE_SOLVER_TYPE_ODE, NE_SOLVER_TYPE_DISCRETE,
NE_SOLVER_TYPE_NUM } NeSolverType; struct NeModelParametersTag { NeSolverType
mSolverType; real_T mSolverTolerance; boolean_T mVariableStepSolver; real_T
mFixedStepSize; real_T mStartTime; boolean_T mLoadInitialState; boolean_T
mUseSimState; boolean_T mLinTrimCompile; SscLoggingSetting mLoggingMode; };
typedef struct NeSolverParametersTag NeSolverParameters; typedef enum
NeAdvancerChoiceTag { NE_INVALID_ADVANCER_CHOICE = -1,
NE_BACKWARD_EULER_ADVANCER, NE_TRAPEZOIDAL_ADVANCER, NE_NDF2_ADVANCER,
NE_VARIABLE_STEP_ADVANCER, NE_NUM_ADVANCER_CHOICES } NeAdvancerChoice; typedef
enum NeLinearAlgebraChoiceTag { NE_INVALID_LA_CHOICE = -1, NE_SPARSE_LA,
NE_FULL_LA, NE_NUM_LA_CHOICES } NeLinearAlgebraChoice; struct
NeSolverParametersTag { boolean_T mProfile; boolean_T mUseLocalSampling;
boolean_T mEnableSwitchedLinearOptims; boolean_T mFrequencyDomain; boolean_T
mUseCCode; real_T mRelTol; real_T mAbsTol; real_T mMinStep; boolean_T
mToWorkspace; boolean_T mRevertToSquareIcSolve; size_t mNumHomotopyIterations;
boolean_T mPhasorMode; size_t mPhasorModeNumHarmonics; boolean_T mDoDC; real_T
mResidualTolerance; boolean_T mUseLocalSolver; NeAdvancerChoice mAdvancerChoice;
real_T mAdvancerStepsize; boolean_T mDoFixedCost; size_t
mNumFixedCicNonlinearIterations; size_t mNumFixedCicModeIterations;
NeLinearAlgebraChoice mLinearAlgebra; size_t mDelaysMemoryBudget; boolean_T
mAutomaticFiltering; real_T mFilteringTimeConstant; }; NeSolverSystem
*nes_create_crude_solver_system(NeDynamicSystem *dynamicsystemPtr,
NeModelParameters modelParameters, NeSolverParameters solverParameters,
PmAllocator *allocatorPtr); typedef enum NeEquationDomainTag {
NE_EQUATION_DOMAIN_INVALID = -1, NE_EQUATION_DOMAIN_TIME,
NE_EQUATION_DOMAIN_FREQUENCY_REAL, NE_EQUATION_DOMAIN_FREQUENCY_IMAG,
NE_EQUATION_DOMAIN_COMPLEX, NE_EQUATION_DOMAIN_DELAY, NE_EQUATION_DOMAIN_NUM }
NeEquationDomain; typedef unsigned int NeDsEquationFlag; typedef unsigned int
NeDsVariableFlag; typedef struct NeDsEquationDataTag { const char * mFullPath;
size_t mIndex; NeDsEquationFlag mFlags; NeEquationDomain mDomain; const char *
mObject; size_t mNumRanges; size_t mStart; boolean_T mIsSwitchedLinear; real_T
mScale; const char * mUnit; } NeEquationData; typedef struct NeVariableDataTag {
const char * mFullPath; size_t mIndex; NeDsVariableFlag mFlags; const char *
mObject; real_T mScale; const char * mUnit; real_T mICValue; boolean_T
mIsDifferential; size_t mM; size_t mN; NeInitMode mInitMode; const char *
mDescription; } NeVariableData; typedef struct NeObservableDataTag { const char *
mFullPath; const char * mObject; size_t mM; size_t mN; const char * mUnit;
NeInitMode mInitMode; boolean_T mIsDetermined; boolean_T mIsDifferential; const
char * mDescription; } NeObservableData; typedef struct NeModeDataTag { const
char * mFullPath; size_t mIndex; const char * mObject; int32_T mICValue; }
NeModeData; typedef enum NeRangeTypeIdTag { NE_RANGE_TYPE_INVALID = -1,
NE_RANGE_TYPE_NORMAL, NE_RANGE_TYPE_PROTECTED, NE_RANGE_TYPE_NA,
NE_RANGE_TYPE_NUM } NeRangeTypeId; typedef struct NeRangeTag { const char *
mFileName; size_t mBeginLine; size_t mBeginColumn; size_t mEndLine; size_t
mEndColumn; NeRangeTypeId mType; } NeRange; typedef enum NeZcTypeTag {
NE_ZC_TYPE_INVALID = -1, NE_ZC_TYPE_TRUE, NE_ZC_TYPE_FALSE, NE_ZC_TYPE_EITHER,
NE_ZC_TYPE_NUM } NeZcType; typedef struct NeZCDataTag { const char * mObject;
size_t mNumRanges; size_t mStart; const char * mPath; const char * mDescriptor;
NeZcType mType; } NeZCData; typedef struct NeAssertDataTag { const char *
mObject; size_t mNumRanges; size_t mStart; const char * mPath; const char *
mDescriptor; boolean_T mIsWarn; const char * mMessage; const char * mMessageID; }
NeAssertData; typedef struct NeParameterDataTag { const char * mFullPath; const
char * mObject; const char * mDescription; size_t mIndex; size_t mM; size_t mN; }
NeParameterData; typedef struct NeConstraintStatTag NeConstraintStat; struct
NeConstraintStatTag { void (*mVariable) (const NeConstraintStat *, const
NeVariableData *); struct NeConstraintStatData *mData; }; typedef struct
NeCompStatsTag NeCompStats; struct NeCompStatsTag { const NeConstraintStat
*(*mConstraint) (const NeCompStats *); struct NeCompStatsData *mData; };
NeSolverSystem *nes_create_index_reduced_solver_system(NeSolverSystem *basePtr,
NeSolverParameters sp, const NeCompStats *compStats, PmAllocator *allocatorPtr);
NeSolverSystem *nes_create_optimized_solver_system(NeSolverSystem
*solverSystemPtr, PmAllocator *allocatorPtr); NeSolverSystem
*nes_create_regularized_solver_system(NeSolverSystem *ss, NeSolverParameters sp,
PmAllocator *allocator); NeSolverSystem
*nes_create_shrunk_solver_system(NeSolverSystem *solverSystemPtr, PmAllocator
*allocatorPtr); typedef struct NeProfilingServiceTag { NeDynamicSystem
*(*mProfileDs) (const NeProfiler *, NeDynamicSystem *); NeSolverSystem
*(*mProfileSs) (const NeProfiler *, NeSolverSystem *, const char *); NeDae
*(*mProfileDae) (const NeProfiler *, NeDae *); } NeProfilingService; boolean_T
nes_set_profiling_service(NeProfilingService *); NeDynamicSystem
*nes_profile_dynamic_system(const NeProfiler *, NeDynamicSystem *);
NeSolverSystem *nes_profile_solver_system(const NeProfiler *, NeSolverSystem *,
const char *); NeDae *nes_profile_dae(const NeProfiler *, NeDae *); typedef
int32_T (*DiagnosisSupportMethod)(const NeSolverSystem *baseSys, const
NeSystemInput *baseInput, const NeSolverSystem *topSys, const NeSystemInput
*topInput, real_T, PmCharVector, boolean_T); typedef PmfMessageId
(*LinearizationSupportMethod)(const NeSolverSystem *, const NeSystemInput *,
PmRealVector *); typedef PmfMessageId (*VslsSupportMethod)(const PmRealVector *);
typedef struct NeSolverSupportMethodsTag { DiagnosisSupportMethod
mDcDiagnosisSupportMethod; DiagnosisSupportMethod mTrDiagnosisSupportMethod;
DiagnosisSupportMethod mAdvSolDiagnosisSupportMethod; DiagnosisSupportMethod
mInconsistentIcMethod; LinearizationSupportMethod mLinearizationSupportMethod;
VslsSupportMethod mVslsSupportMethod; } NeSolverSupportMethods; void
nes_register_solver_support(const NeSolverSupportMethods *methods); const
NeSolverSupportMethods *nes_get_support_methods(void); typedef struct
NeslSimulationDataTag NeslSimulationData; typedef struct
NeslSimulationDataDataTag NeslSimulationDataData; struct NeslSimulationDataTag {
PmRealVector *(*mTime) (const NeslSimulationData *); PmRealVector *(*mContStates)
(const NeslSimulationData *); PmIntVector *(*mModeVector) (const
NeslSimulationData *); PmRealVector *(*mDiscStates) (const NeslSimulationData *);
PmIntVector *(*mSampleHits) (const NeslSimulationData *); PmRealVector
*(*mOutputs) (const NeslSimulationData *); PmRealVector *(*mDx) (const
NeslSimulationData *); PmRealVector *(*mNonSampledZCs) (const NeslSimulationData
*); PmRealVector *(*mResiduals) (const NeslSimulationData *); PmSparsityPattern
*(*mM_P) (const NeslSimulationData *); PmRealVector *(*mMassMatrixPr) (const
NeslSimulationData *); PmSparsityPattern *(*mLinJacobianPattern) (const
NeslSimulationData *); PmRealVector *(*mLinJacobian) (const NeslSimulationData
*); PmSparsityPattern *(*mSolJacobianPattern) (const NeslSimulationData *);
PmRealVector *(*mSolJacobianPr) (const NeslSimulationData *); PmRealVector
*(*mInputValues) (const NeslSimulationData *); PmIntVector *(*mInputOffsets)
(const NeslSimulationData *); boolean_T *(*mFoundZcEvents) (const
NeslSimulationData *); boolean_T *(*mIsMajorTimeStep) (const NeslSimulationData
*); boolean_T *(*mIsSolverAssertCheck) (const NeslSimulationData *); boolean_T
*(*mIsSolverCheckingCIC) (const NeslSimulationData *); boolean_T
*(*mIsComputingJacobian) (const NeslSimulationData *); boolean_T
*(*mIsSolverRequestingReset) (const NeslSimulationData *); boolean_T
*(*mIsFundamentalSampleHit) (const NeslSimulationData *); void (*mDestroy)
(NeslSimulationData *); NeslSimulationDataData *mData; }; PMF_DEPLOY_STATIC
PmRealVector nesl_get_time(const NeslSimulationData *sd) { return
*(sd->mTime(sd)); } PMF_DEPLOY_STATIC PmRealVector nesl_get_cont_states(const
NeslSimulationData *sd) { return *(sd->mContStates(sd)); } PMF_DEPLOY_STATIC
PmIntVector nesl_get_mode_vector(const NeslSimulationData *sd) { return
*(sd->mModeVector(sd)); } PMF_DEPLOY_STATIC PmRealVector
nesl_get_disc_states(const NeslSimulationData *sd) { return
*(sd->mDiscStates(sd)); } PMF_DEPLOY_STATIC PmIntVector
nesl_get_sample_hits(const NeslSimulationData *sd) { return
*(sd->mSampleHits(sd)); } PMF_DEPLOY_STATIC PmRealVector nesl_get_outputs(const
NeslSimulationData *sd) { return *(sd->mOutputs(sd)); } PMF_DEPLOY_STATIC
PmRealVector nesl_get_dx(const NeslSimulationData *sd) { return *(sd->mDx(sd)); }
PMF_DEPLOY_STATIC PmRealVector nesl_get_nonsampled_zcs(const NeslSimulationData
*sd) { return *(sd->mNonSampledZCs(sd)); } PMF_DEPLOY_STATIC PmRealVector
nesl_get_residuals(const NeslSimulationData *sd) { return *(sd->mResiduals(sd));
} PMF_DEPLOY_STATIC PmSparsityPattern nesl_get_mass_matrix_pattern(const
NeslSimulationData *sd) { return *(sd->mM_P(sd)); } PMF_DEPLOY_STATIC
PmRealVector nesl_get_mass_matrix_pr(const NeslSimulationData *sd) { return
*(sd->mMassMatrixPr(sd)); } PMF_DEPLOY_STATIC PmSparsityPattern
nesl_get_lin_jacobian_pattern(const NeslSimulationData *sd) { return
*(sd->mLinJacobianPattern(sd)); } PMF_DEPLOY_STATIC PmRealVector
nesl_get_lin_jacobian(const NeslSimulationData *sd) { return
*(sd->mLinJacobian(sd)); } PMF_DEPLOY_STATIC PmSparsityPattern
nesl_get_sol_jacobian_pattern(const NeslSimulationData *sd) { return
*(sd->mSolJacobianPattern(sd)); } PMF_DEPLOY_STATIC PmRealVector
nesl_get_sol_jacobian_pr(const NeslSimulationData *sd) { return
*(sd->mSolJacobianPr(sd)); } PMF_DEPLOY_STATIC PmRealVector
nesl_get_input_values(const NeslSimulationData *sd) { return
*(sd->mInputValues(sd)); } PMF_DEPLOY_STATIC PmIntVector
nesl_get_input_offsets(const NeslSimulationData *sd) { return
*(sd->mInputOffsets(sd)); } PMF_DEPLOY_STATIC boolean_T nesl_found_zcs(const
NeslSimulationData *sd) { return *(sd->mFoundZcEvents(sd)); } PMF_DEPLOY_STATIC
boolean_T nesl_is_major_time_step(const NeslSimulationData *sd) { return
*(sd->mIsMajorTimeStep(sd)); } PMF_DEPLOY_STATIC boolean_T
nesl_is_solver_assert_check(const NeslSimulationData *sd) { return
*(sd->mIsSolverAssertCheck(sd)); } PMF_DEPLOY_STATIC boolean_T
nesl_is_solver_checking_cic(const NeslSimulationData *sd) { return
*(sd->mIsSolverCheckingCIC(sd)); } PMF_DEPLOY_STATIC boolean_T
nesl_is_computing_jacobian(const NeslSimulationData *sd) { return
*(sd->mIsComputingJacobian(sd)); } PMF_DEPLOY_STATIC boolean_T
nesl_is_solver_requesting_reset(const NeslSimulationData *sd) { return
*(sd->mIsSolverRequestingReset(sd)); } PMF_DEPLOY_STATIC boolean_T
nesl_is_fundamental_sample_hit(const NeslSimulationData *sd) { return
*(sd->mIsFundamentalSampleHit(sd)); } PMF_DEPLOY_STATIC boolean_T
nesl_has_sample_hits(const NeslSimulationData *sd) { size_t i; PmIntVector
sample_hits = nesl_get_sample_hits(sd); for (i = 0; i < sample_hits.mN; i++) { if
(sample_hits.mX[i]) { return true; } } return false; } typedef struct
McSparseMatrixTag McSparseMatrix; struct McSparseMatrixTag { PmSparsityPattern
*mPattern; PmRealVector *mPr; }; McSparseMatrix *mc_assemble_sparse_matrix(const
PmSparsityPattern *patternPtr, const PmRealVector *prPtr, PmAllocator
*allocatorPtr); void mc_disassemble_sparse_matrix(McSparseMatrix *matrix,
PmAllocator *allocatorPtr); McSparseMatrix *mc_create_sparse_matrix(size_t
nNzMax, size_t nRow, size_t nCol, PmAllocator *allocatorPtr); McSparseMatrix
*mc_copy_sparse_matrix(const McSparseMatrix *matrixPtr, PmAllocator
*allocatorPtr); McSparseMatrix *mc_create_identity_sparse_matrix(size_t n,
PmAllocator *allocatorPtr); McSparseMatrix *mc_create_hcat_sparse_matrix(const
McSparseMatrix *a, const McSparseMatrix *b, PmAllocator *allocatorPtr);
McSparseMatrix *mc_create_vcat_sparse_matrix(const McSparseMatrix *a, const
McSparseMatrix *b, PmAllocator *allocatorPtr); McSparseMatrix
*mc_create_section_sparse_matrix(const McSparseMatrix *matrix, size_t rowStart,
size_t rowEndPlusOne, size_t colStart, size_t colEndPlusOne, PmAllocator
*allocatorPtr); McSparseMatrix *mc_create_transpose_sparse_matrix(const
McSparseMatrix *matrix, PmAllocator *allocatorPtr); McSparseMatrix
*mc_create_right_padded_sparse_matrix(const McSparseMatrix *matrix, size_t
padding, PmAllocator *allocatorPtr); McSparseMatrix
*mc_create_bottom_padded_sparse_matrix(const McSparseMatrix *matrix, size_t
padding, PmAllocator *allocatorPtr); McSparseMatrix
*mc_create_product_sparse_matrix(const McSparseMatrix *A, const McSparseMatrix
*B, PmAllocator *allocatorPtr); McSparseMatrix *mc_create_sum_sparse_matrix(const
McSparseMatrix *A, const McSparseMatrix *B, PmAllocator *allocatorPtr);
McSparseMatrix *mc_create_sparse_submatrix(const McSparseMatrix *matrix, const
PmBoolVector *selectedRows, const PmBoolVector *selectedCols, PmAllocator
*allocatorPtr); McSparseMatrix *mc_create_sparse_supermatrix(const McSparseMatrix
*matrix, const PmBoolVector *rows, const PmBoolVector *cols, PmAllocator *al);
McSparseMatrix *mc_create_sparse_restriction(const McSparseMatrix *matrix, const
PmBoolVector *selectedRows, const PmBoolVector *selectedCols, PmAllocator
*allocatorPtr); McSparseMatrix *mc_extract_col(const McSparseMatrix *matrix,
size_t col, PmAllocator *allocatorPtr); McSparseMatrix *mc_extract_row(const
McSparseMatrix *matrix, size_t row, PmAllocator *allocatorPtr); McSparseMatrix
*mc_remove_col(const McSparseMatrix *matrix, size_t col, PmAllocator
*allocatorPtr); McSparseMatrix *mc_remove_row(const McSparseMatrix *matrix,
size_t row, PmAllocator *allocatorPtr); void
mc_destroy_sparse_matrix(McSparseMatrix *matrixPtr, PmAllocator *allocatorPtr);
McSparseMatrix *mc_remove_element(const McSparseMatrix *matrix, size_t element,
PmAllocator *allocator); McSparseMatrix *mc_clean_sparse_matrix(const
McSparseMatrix *in, PmAllocator *allocator); typedef struct NeslContLtiDataTag
NeslContLtiData; struct NeslContLtiDataTag { PmRealVector *mLtiFlatU;
McSparseMatrix mDx; McSparseMatrix mDu; PmRealVector mC0; boolean_T mEmptyDx;
boolean_T mEmptyDu; }; typedef struct NeCustomDataSizeTag NeCustomDataSize;
typedef struct NeCustomDataTag NeCustomData; struct NeCustomDataSizeTag { size_t
mDoubleSize; size_t mIntegerSize; }; struct NeCustomDataTag { double * mDouble;
int32_T * mInteger; NeCustomDataSize mSizes; NeCustomData *mChildData; };
NeCustomDataSize ne_get_zero_custom_data_size(void); NeCustomData *
ne_allocate_custom_data(NeCustomDataSize sizes); NeCustomData *
ne_allocate_empty_custom_data(void); void ne_free_custom_data(NeCustomData *ncd);
typedef struct NeParameterBundleTag { PmIntVector mLogicalParameters; PmIntVector
mIntegerParameters; PmIntVector mIndexParameters; PmRealVector mRealParameters; }
NeParameterBundle; typedef struct NeParameterVectorTag { size_t mN;
NeParameterData *mX; } NeParameterVector; typedef struct NeParameterInfoTag {
NeParameterVector mLogicals; NeParameterVector mIntegers; NeParameterVector
mIndices; NeParameterVector mReals; } NeParameterInfo; typedef struct
SlSparseMatrixTag { PmSparsityPattern *mPattern; PmRealVector *mPr; }
SlSparseMatrix; typedef struct SLMatricesTag { boolean_T mIsYAffineTermUpdated;
boolean_T mIsXP0AffineTermUpdated; size_t mOffsetX0InD; size_t mOffsetU0InD;
size_t mSlDaeNumDiscreteMajor; size_t mSlDaeNumCache; PmRealVector mAffineY;
PmRealVector mAffineXP0; PmRealVector mYX0; PmRealVector mYU0; SlSparseMatrix
mDxddotDxd; SlSparseMatrix mDxddotDu; SlSparseMatrix mDyDxd; SlSparseMatrix
mDyDu; SlSparseMatrix mDxaDxd; SlSparseMatrix mDxaDu; PmIntVector mMode;
PmIntVector mMajor; PmIntVector mCache; } SLMatrices; typedef struct
NeslSimulationSizesTag { size_t mNumContStates; size_t mNumDiscStates; size_t
mNumModes; size_t mNumOutputs; size_t mNumZCs; size_t mNumRanges; size_t
mNumSamples; size_t mNumMassMatrixNzMax; size_t mNumLinJacobianNzMax; size_t
mNumSolJacobianNzMax; size_t mNumTrimResiduals; boolean_T mDisableProjection;
boolean_T mDefaultLinJacobian; boolean_T mDisableSolJacobian; boolean_T
mIsMConstant; boolean_T mUpdateJacobianAtReset; boolean_T mIsDae; boolean_T
mRegistersStateNames; boolean_T mHasUpdate; const PmIntVector *mNumInputs; const
PmBoolVector *mDirectFeedthrough; } NeslSimulationSizes; typedef struct
NeslStateNameDataTag { size_t mWidth; const char *mStateName; const char
*mBlockName; } NeslStateNameData; typedef struct NeslStateNameVectorTag {
NeslStateNameData* mStateNames; size_t mNumStates; } NeslStateNameVector; typedef
enum NeslSimulatorMethodIdTag { NESL_SIM_INVALID = -1, NESL_SIM_INITIALIZEONCE,
NESL_SIM_INITSYSTEMMATRICES, NESL_SIM_OUTPUTS, NESL_SIM_UPDATE,
NESL_SIM_PROJECTION, NESL_SIM_MASSMATRIX, NESL_SIM_DERIVATIVES,
NESL_SIM_FORCINGFUNCTION, NESL_SIM_ZEROCROSSINGS, NESL_SIM_LINJACOBIAN,
NESL_SIM_SOLJACOBIAN, NESL_SIM_LINJACOBIANIRJC, NESL_SIM_SOLJACOBIANIRJC,
NESL_SIM_RESIDUALS, NESL_NUM_SIMULATOR_METHODS } NeslSimulatorMethodId; typedef
struct NeslSimulatorTag NeslSimulator; typedef struct NeslSimulatorUserDataTag
NeslSimulatorUserData; typedef enum NeslSimulatorStatusTag { NESL_SIM_ERROR = -1,
NESL_SIM_OK }NeslSimulatorStatus; typedef NeslSimulatorStatus
(*NeslSimulatorMethod) (const NeslSimulator*, const NeslSimulationData*,
NeuDiagnosticManager *); struct NeslSimulatorTag { NeslSimulatorUserData
*mUserData; NeslSimulatorMethod mMethods[NESL_NUM_SIMULATOR_METHODS];
NeslSimulationSizes (*mSizes) (const NeslSimulator *s); void (*mStateNames)
(const NeslSimulator *s, const NeslStateNameVector *snv); void (*mSampleTimes)
(const NeslSimulator *s, PmRealVector *periods, PmRealVector *offsets);
NeslSimulatorStatus (*mInitialize) (const NeslSimulator *s, NeModelParameters mp,
NeuDiagnosticManager *mgr); void (*mSetupLogger) (const NeslSimulator *s,
NeLoggerBuilder *loggerBuilder); void (*mLog) (const NeslSimulator *s, const
NeslSimulationData *sd, PmRealVector *output); const NeslContLtiData *
(*mGetContLtiData) (const NeslSimulator *s); const SLMatrices **
(*mGetSLMatrices) (const NeslSimulator *s); void (*mDestroy) (NeslSimulator *);
NeCustomData* (*mGetCustomData)(const NeslSimulator *); NeslSimulatorStatus
(*mSetCustomData)( const NeCustomData *, const NeslSimulator *,
NeuDiagnosticManager *); const NeZCData *mZCData; const NeRange *mRanges;
NeParameterInfo mParameterInfo; void (*mSetParameters)(const NeslSimulator *,
const NeParameterBundle *); }; PMF_DEPLOY_STATIC NeslSimulatorStatus
ne_simulator_method(const NeslSimulator* simulator_ptr, NeslSimulatorMethodId
method_id, const NeslSimulationData* sim_data, NeuDiagnosticManager *mgr) {
return simulator_ptr->mMethods[method_id](simulator_ptr, sim_data, mgr); }
typedef struct NeOutputParametersTag { size_t mDaeIndex; size_t
mOutputFunctionIndex; const char *mDescriptor; } NeOutputParameters; typedef enum
NeslSimulatorCategoryTag { NESL_SIMULATOR_CATEGORY_INVALID = -1,
NESL_SIMULATOR_CATEGORY_STATE, NESL_SIMULATOR_CATEGORY_SINK,
NESL_SIMULATOR_CATEGORY_OUTPUT, NESL_SIMULATOR_CATEGORY_NUM }
NeslSimulatorCategory; typedef struct NeslSimulatorGroupTag NeslSimulatorGroup;
typedef struct NeslSimulatorGroupDataTag NeslSimulatorGroupData; struct
NeslSimulatorGroupTag { const NeslSimulator *(*mSimulator) (const
NeslSimulatorGroup *g, NeslSimulatorCategory c, size_t i); NeslSimulatorGroup
*(*mClone) (const NeslSimulatorGroup *g); void (*mGetReference)
(NeslSimulatorGroup *g); void (*mReleaseReference) (NeslSimulatorGroup *g); const
NeProfiler *mProfiler; NeslSimulatorGroupData *mData; size_t
mNumSimulators[NESL_SIMULATOR_CATEGORY_NUM]; }; PmfMessageId
nesl_register_simulator_group( const char *key, const size_t numDae, NeDae *
const *dae, const NeSolverParameters sp, const NeModelParameters mp, const size_t
numOutputs, const NeOutputParameters *op, const boolean_T sinksNeeded); typedef
struct NeslSimulatorGroupRegistryTag NeslSimulatorGroupRegistry; typedef struct
NeslSimulatorGroupRegistryDataTag NeslSimulatorGroupRegistryData; struct
NeslSimulatorGroupRegistryTag { void (*mInsert) (const NeslSimulatorGroupRegistry
*registry, const char *key, NeslSimulatorGroup *group); void (*mErase) (const
NeslSimulatorGroupRegistry *registry, const char *key); void (*mEraseModel)
(const NeslSimulatorGroupRegistry *registry, const char *model);
NeslSimulatorGroup * (*mLookup) (const NeslSimulatorGroupRegistry *registry,
const char *key); const NeslSimulator * (*mLeaseSimulator) ( const
NeslSimulatorGroupRegistry *registry, const char *key, NeslSimulatorCategory cat,
size_t idx); boolean_T (*mHasBeenCloned) ( const NeslSimulatorGroupRegistry
*registry, const char *key ); void (*mClear) (const NeslSimulatorGroupRegistry
*registry); void (*mDestroy) (NeslSimulatorGroupRegistry *registry);
NeslSimulatorGroupRegistryData *mData; }; const NeslSimulatorGroupRegistry
*nesl_get_registry(void);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* _nesl_rtw_h */
