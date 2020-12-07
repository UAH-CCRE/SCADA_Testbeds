#ifndef ne_dae_construct_h
#define ne_dae_construct_h
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
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
mAutomaticFiltering; real_T mFilteringTimeConstant; }; typedef struct
NeModelParametersTag NeModelParameters; typedef enum SscDiagnosticSettingTag {
SSC_DIAGNOSTIC_INVALID = -1, SSC_DIAGNOSTIC_ERROR, SSC_DIAGNOSTIC_WARNING,
SSC_DIAGNOSTIC_NONE, SSC_DIAGNOSTIC_NUM } SscDiagnosticSetting; typedef enum
SscLoggingSettingTag { SSC_LOGGING_INVALID = -1, SSC_LOGGING_NONE,
SSC_LOGGING_ALL, SSC_LOGGING_LOCAL, SSC_LOGGING_NUM } SscLoggingSetting; typedef
enum NeSolverTypeTag { NE_SOLVER_TYPE_INVALID = -1, NE_SOLVER_TYPE_DAE,
NE_SOLVER_TYPE_ODE, NE_SOLVER_TYPE_DISCRETE, NE_SOLVER_TYPE_NUM } NeSolverType;
struct NeModelParametersTag { NeSolverType mSolverType; real_T mSolverTolerance;
boolean_T mVariableStepSolver; real_T mFixedStepSize; real_T mStartTime;
boolean_T mLoadInitialState; boolean_T mUseSimState; boolean_T mLinTrimCompile;
SscLoggingSetting mLoggingMode; }; typedef enum NeEquationDomainTag {
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
*(*mConstraint) (const NeCompStats *); struct NeCompStatsData *mData; }; typedef
enum StateModelModeTag { STATE_MODEL_MODE_UNSET = -1, STATE_MODEL_MODE_NORMAL,
STATE_MODEL_MODE_IMPORTED, STATE_MODEL_MODE_NUM } StateModelMode; const char*
state_model_mode_to_string(StateModelMode); typedef enum StateModelInputsModeTag
{ STATE_MODEL_INPUTS_UNSET = -1, STATE_MODEL_INPUTS_NOINPUTS,
STATE_MODEL_INPUTS_INPUTS, STATE_MODEL_INPUTS_NUM } StateModelInputsMode; const
char* state_model_inputs_mode_to_string(StateModelInputsMode); typedef struct
CStateManagerTag CStateManager; typedef struct CStateManagerDataTag
CStateManagerData; struct CStateManagerTag { const char* (*mModel) (const
CStateManager*); size_t (*mSize) (const CStateManager*, int); void (*mAllocate)
(const CStateManager*); int32_T* (*mInteger) (const CStateManager*); size_t *
(*mIndex) (const CStateManager*); double* (*mReal) (const CStateManager*); void
(*mEliminated) (const CStateManager*, const char*); boolean_T
(*mIsEliminated)(const CStateManager*, const char*); void (*mUnsatisfied) (const
CStateManager*, const char*); boolean_T (*mIsSatisfied) (const CStateManager*,
const char*); void (*mInputDependent) (const CStateManager*, const char*);
boolean_T (*mIsInputDependent) (const CStateManager*, const char*); void
(*mAlgebraic) (const CStateManager*, const char*); boolean_T (*mIsAlgebraic)
(const CStateManager*, const char*); void (*mErrorAll) (const CStateManager*,
boolean_T); void (*mError) (const CStateManager*, const char*, boolean_T);
boolean_T (*mHasError) (const CStateManager*, const char*); boolean_T
(*mIsHideValue) (const CStateManager*, const char*); void (*mSteadyStateAll)
(const CStateManager*); void (*mSteadyState) (const CStateManager*, const char*);
boolean_T (*mIsSteadyState) (const CStateManager*, const char*); StateModelMode
(*mGetModelMode)(const CStateManager*); void (*mSetModelMode)(const
CStateManager*, StateModelMode); StateModelInputsMode
(*mGetModelInputsMode)(const CStateManager*); void (*mSetModelInputsMode)(const
CStateManager*, StateModelInputsMode); void (*mUpdate) (const CStateManager*);
void (*mUpdateMode) (const CStateManager*); CStateManager* (*mClone) (const
CStateManager*); void (*mDestroy) (CStateManager*); CStateManagerData* mData; };
typedef struct NeVectorStateManagerTag NeVectorStateManager; struct
NeVectorStateManagerTag { CStateManager *mMgr; boolean_T mNeedPairs; PmIntVector
*mPairs1; PmIntVector *mPairs2; void (*mDestroy) (NeVectorStateManager *vsm); };
NeVectorStateManager *neu_create_vector_state_manager(CStateManager *mgr, size_t
nScalarVars, boolean_T needPairs); PmfMessageId ne_dae_create( NeDae **dae,
NeDynamicSystem *dynamicsystemPtr, NeSolverParameters solverParameters,
NeModelParameters modelParameters, const McLinearAlgebra *linearAlgebraPtr,
NeProfiler *profiler, const NeCompStats *compStats, NeVectorStateManager *vsm,
PmAllocator *allocatorPtr);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* ne_dae_construct_h */
