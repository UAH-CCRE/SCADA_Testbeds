#ifndef _ne_ds_h
#define _ne_ds_h
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef enum NeEquationDomainTag { NE_EQUATION_DOMAIN_INVALID = -1,
NE_EQUATION_DOMAIN_TIME, NE_EQUATION_DOMAIN_FREQUENCY_REAL,
NE_EQUATION_DOMAIN_FREQUENCY_IMAG, NE_EQUATION_DOMAIN_COMPLEX,
NE_EQUATION_DOMAIN_DELAY, NE_EQUATION_DOMAIN_NUM } NeEquationDomain; typedef
unsigned int NeDsEquationFlag; typedef unsigned int NeDsVariableFlag; typedef
struct NeDsEquationDataTag { const char * mFullPath; size_t mIndex;
NeDsEquationFlag mFlags; NeEquationDomain mDomain; const char * mObject; size_t
mNumRanges; size_t mStart; boolean_T mIsSwitchedLinear; real_T mScale; const char
* mUnit; } NeEquationData; typedef struct NeVariableDataTag { const char *
mFullPath; size_t mIndex; NeDsVariableFlag mFlags; const char * mObject; real_T
mScale; const char * mUnit; real_T mICValue; boolean_T mIsDifferential; size_t
mM; size_t mN; NeInitMode mInitMode; const char * mDescription; } NeVariableData;
typedef struct NeObservableDataTag { const char * mFullPath; const char *
mObject; size_t mM; size_t mN; const char * mUnit; NeInitMode mInitMode;
boolean_T mIsDetermined; boolean_T mIsDifferential; const char * mDescription; }
NeObservableData; typedef struct NeModeDataTag { const char * mFullPath; size_t
mIndex; const char * mObject; int32_T mICValue; } NeModeData; typedef enum
NeRangeTypeIdTag { NE_RANGE_TYPE_INVALID = -1, NE_RANGE_TYPE_NORMAL,
NE_RANGE_TYPE_PROTECTED, NE_RANGE_TYPE_NA, NE_RANGE_TYPE_NUM } NeRangeTypeId;
typedef struct NeRangeTag { const char * mFileName; size_t mBeginLine; size_t
mBeginColumn; size_t mEndLine; size_t mEndColumn; NeRangeTypeId mType; } NeRange;
typedef enum NeZcTypeTag { NE_ZC_TYPE_INVALID = -1, NE_ZC_TYPE_TRUE,
NE_ZC_TYPE_FALSE, NE_ZC_TYPE_EITHER, NE_ZC_TYPE_NUM } NeZcType; typedef struct
NeZCDataTag { const char * mObject; size_t mNumRanges; size_t mStart; const char
* mPath; const char * mDescriptor; NeZcType mType; } NeZCData; typedef struct
NeAssertDataTag { const char * mObject; size_t mNumRanges; size_t mStart; const
char * mPath; const char * mDescriptor; boolean_T mIsWarn; const char * mMessage;
const char * mMessageID; } NeAssertData; typedef struct NeParameterDataTag {
const char * mFullPath; const char * mObject; const char * mDescription; size_t
mIndex; size_t mM; size_t mN; } NeParameterData; typedef enum NeDsIoTypeTag {
UNKNOWN_IO_TYPE = -1, NE_INPUT_IO_TYPE, NE_OUTPUT_IO_TYPE, NUM_IO_TYPES }
NeDsIoType; typedef struct NeDsIoInfoTag { const char *mName; size_t mM; size_t
mN; const char *mUnit; const char *mIdentifier; } NeDsIoInfo; PMF_DEPLOY_STATIC
size_t ne_get_num_io_signals(const NeDsIoInfo * io_info_ptr, size_t io_info_size)
{ size_t i=0, num_signals=0; for (i = 0; i < io_info_size; i++) { num_signals +=
io_info_ptr[i].mM * io_info_ptr[i].mN; } return num_signals; } typedef struct
NeCgParamsTag NeCgParams; typedef struct NeCgResultsTag NeCgResults; enum {
NE_NODAL_EQ_FLAG = 1 << 0, NE_SIGNAL_EQ_FLAG = 1 << 1, NE_BRANCH_EQ_FLAG = 1 <<
2, NE_GENERAL_EQ_FLAG = 1 << 3, NE_ACROSS_EQ_FLAG = 1 << 4, NE_THROUGH_EQ_FLAG =
1 << 5, NE_NO_EQ_FLAGS = 0 }; enum { NE_NODAL_VAR_FLAG = 1 << 0,
NE_OUTPUT_VAR_FLAG = 1 << 1, NE_INPUT_VAR_FLAG = 1 << 2, NE_SIGNAL_VAR_FLAG = 1
<< 3, NE_NO_VAR_FLAGS = 0 }; typedef union NeDsMethodOutputTag {
PmSparsityPattern mM_P; PmRealVector mM; PmBoolVector mVMM; PmSparsityPattern
mDXM_P; PmRealVector mDXM; PmSparsityPattern mDUM_P; PmRealVector mDUM;
PmSparsityPattern mDTM_P; PmRealVector mDTM; PmSparsityPattern mA_P; PmRealVector
mA; PmSparsityPattern mB_P; PmRealVector mB; PmSparsityPattern mC_P; PmRealVector
mC; PmRealVector mF; PmBoolVector mVMF; PmBoolVector mSLF; PmSparsityPattern
mDXF_P; PmRealVector mDXF; PmSparsityPattern mDUF_P; PmRealVector mDUF;
PmSparsityPattern mDTF_P; PmRealVector mDTF; PmSparsityPattern mDDF_P;
PmRealVector mDDF; PmSparsityPattern mTDUF_P; PmSparsityPattern mTDXF_P;
PmRealVector mICR; PmIntVector mICR_IM; PmBoolVector mICR_ID; PmRealVector
mDXICR; PmSparsityPattern mDXICR_P; PmSparsityPattern mTDUICR_P;
PmSparsityPattern mMDUY_P; PmSparsityPattern mMDXY_P; PmSparsityPattern mTDUY_P;
PmSparsityPattern mTDXY_P; PmRealVector mY; PmSparsityPattern mDXY_P;
PmRealVector mDXY; PmSparsityPattern mDUY_P; PmRealVector mDUY; PmSparsityPattern
mDTY_P; PmRealVector mDTY; PmIntVector mMODE; PmRealVector mZC; PmIntVector
mCACHE; PmRealVector mUPDATE_R; PmIntVector mUPDATE_I; PmRealVector mSFO;
PmRealVector mSFP; PmRealVector mINIT_R; PmIntVector mINIT_I; PmRealVector mLOG;
PmIntVector mASSERT; PmRealVector mEXPAND; PmRealVector mDEL_T; PmRealVector
mDEL_V; PmRealVector mDEL_V0; PmRealVector mDEL_TMAX; PmSparsityPattern
mDXDELT_P; PmRealVector mDXDELT; PmSparsityPattern mDUDELT_P; PmRealVector
mDUDELT; PmSparsityPattern mDTDELT_P; PmRealVector mDTDELT; PmRealVector
mOBS_EXP; PmRealVector mOBS_ACT; PmIntVector mDP_L; PmIntVector mDP_I;
PmIntVector mDP_J; PmRealVector mDP_R; PmRealVector mQX; PmRealVector mQU;
PmRealVector mQT; PmRealVector mQ1; PmSparsityPattern mQX_P; PmSparsityPattern
mQU_P; PmSparsityPattern mQT_P; PmSparsityPattern mQ1_P; } NeDsMethodOutput;
typedef enum NeDsMethodIdTag { NE_INVALID_METHOD_ID = -1, NE_DS_METHOD_M_P,
NE_DS_METHOD_M, NE_DS_METHOD_VMM, NE_DS_METHOD_DXM_P, NE_DS_METHOD_DXM,
NE_DS_METHOD_DUM_P, NE_DS_METHOD_DUM, NE_DS_METHOD_DTM_P, NE_DS_METHOD_DTM,
NE_DS_METHOD_A_P, NE_DS_METHOD_A, NE_DS_METHOD_B_P, NE_DS_METHOD_B,
NE_DS_METHOD_C_P, NE_DS_METHOD_C, NE_DS_METHOD_F, NE_DS_METHOD_VMF,
NE_DS_METHOD_SLF, NE_DS_METHOD_DXF_P, NE_DS_METHOD_DXF, NE_DS_METHOD_DUF_P,
NE_DS_METHOD_DUF, NE_DS_METHOD_DTF_P, NE_DS_METHOD_DTF, NE_DS_METHOD_DDF_P,
NE_DS_METHOD_DDF, NE_DS_METHOD_TDUF_P, NE_DS_METHOD_TDXF_P, NE_DS_METHOD_ICR,
NE_DS_METHOD_ICR_IM, NE_DS_METHOD_ICR_ID, NE_DS_METHOD_DXICR,
NE_DS_METHOD_DXICR_P, NE_DS_METHOD_TDUICR_P, NE_DS_METHOD_MDUY_P,
NE_DS_METHOD_MDXY_P, NE_DS_METHOD_TDUY_P, NE_DS_METHOD_TDXY_P, NE_DS_METHOD_Y,
NE_DS_METHOD_DXY_P, NE_DS_METHOD_DXY, NE_DS_METHOD_DUY_P, NE_DS_METHOD_DUY,
NE_DS_METHOD_DTY_P, NE_DS_METHOD_DTY, NE_DS_METHOD_MODE, NE_DS_METHOD_ZC,
NE_DS_METHOD_CACHE, NE_DS_METHOD_UPDATE_R, NE_DS_METHOD_UPDATE_I,
NE_DS_METHOD_SFO, NE_DS_METHOD_SFP, NE_DS_METHOD_INIT_R, NE_DS_METHOD_INIT_I,
NE_DS_METHOD_LOG, NE_DS_METHOD_ASSERT, NE_DS_METHOD_EXPAND, NE_DS_METHOD_DEL_T,
NE_DS_METHOD_DEL_V, NE_DS_METHOD_DEL_V0, NE_DS_METHOD_DEL_TMAX,
NE_DS_METHOD_DXDELT_P, NE_DS_METHOD_DXDELT, NE_DS_METHOD_DUDELT_P,
NE_DS_METHOD_DUDELT, NE_DS_METHOD_DTDELT_P, NE_DS_METHOD_DTDELT,
NE_DS_METHOD_OBS_EXP, NE_DS_METHOD_OBS_ACT, NE_DS_METHOD_DP_L, NE_DS_METHOD_DP_I,
NE_DS_METHOD_DP_J, NE_DS_METHOD_DP_R, NE_DS_METHOD_QX, NE_DS_METHOD_QU,
NE_DS_METHOD_QT, NE_DS_METHOD_Q1, NE_DS_METHOD_QX_P, NE_DS_METHOD_QU_P,
NE_DS_METHOD_QT_P, NE_DS_METHOD_Q1_P, NE_NUM_METHODS } NeDsMethodId; typedef
int32_T (*NeDsMethod)(const NeDynamicSystem *, const NeDynamicSystemInput *,
NeDsMethodOutput *); typedef NeDsMethodOutput *(*NeDsMakeOutputFcn)(const
NeDynamicSystem *, PmAllocator *); typedef void
(*NeDsManagementFcn)(NeDynamicSystem *); typedef void (*NeDsGenerateFcn)(const
NeDynamicSystem *, const NeCgParams *, NeCgResults *); typedef void
(*NeDsSetupLoggerFcn) (const NeDynamicSystem *, NeLoggerBuilder *); typedef
NeDynamicSystem *(*NeDsCreateDsFcn) (const NeDynamicSystem *); struct
NeDynamicSystemTag { size_t mNumIo[NUM_IO_TYPES]; const NeDsIoInfo
*mIo[NUM_IO_TYPES]; size_t mNumVariables; size_t mNumDiscreteRealVariables;
size_t mNumDifferentialVariables; size_t mNumEquations; size_t mNumICResiduals;
size_t mNumModes; size_t mNumMajorModes; size_t mNumCache; size_t
mNumObservables; size_t mNumObservableElements; size_t mNumZcs; size_t
mNumAsserts; size_t mNumAssertRanges; size_t mNumRanges; size_t
mNumEquationRanges; size_t mNumFundamentalSamples; size_t mNumDelays; size_t
mNumLogicalParameters; size_t mNumIntegerParameters; size_t mNumIndexParameters;
size_t mNumRealParameters; size_t mNumLogicalDerivedParameters; size_t
mNumIntegerDerivedParameters; size_t mNumIndexDerivedParameters; size_t
mNumRealDerivedParameters; boolean_T mIsOutputLinear; boolean_T
mIsOutputSwitchedLinear; boolean_T mNewCompiler; NeDsManagementFcn
mReleaseReference; NeDsManagementFcn mGetReference; NeDsMethod
mMethods[NE_NUM_METHODS]; NeDsMakeOutputFcn mMakeOutput[NE_NUM_METHODS];
NeDsSetupLoggerFcn mSetupLogger; NeEquationData *mEquationData; NeVariableData
*mVariableData; NeVariableData *mDiscreteData; NeModeData *mMajorModeData;
NeObservableData *mObservableData; NeZCData *mZCData; NeAssertData *mAssertData;
NeRange *mAssertRanges; NeRange *mRanges; NeRange *mEquationRanges;
NeParameterData *mLogicalParameters; NeParameterData *mIntegerParameters;
NeParameterData *mIndexParameters; NeParameterData *mRealParameters; void
*mLargeArrayData; NeDsGenerateFcn mGenerateFcn; NeDsCreateDsFcn
mDiagnosticsDsFcn; NeChecksum mChecksum; }; PMF_DEPLOY_STATIC void
ne_ds_release_reference(NeDynamicSystem *dynSys) { if (dynSys) {
dynSys->mReleaseReference(dynSys); } } PMF_DEPLOY_STATIC void
ne_ds_get_reference(NeDynamicSystem *dynSys) { if (dynSys) {
dynSys->mGetReference(dynSys); } } PMF_DEPLOY_STATIC int32_T
ne_ds_call_method(const NeDynamicSystem *dynSys, NeDsMethodId id, const
NeDynamicSystemInput *input, NeDsMethodOutput *output) { return
dynSys->mMethods[id](dynSys, input, output); } PMF_DEPLOY_STATIC NeDsMethodOutput
*ne_ds_default_output(const NeDynamicSystem *dynSys, NeDsMethodId id, PmAllocator
*allocator) { return dynSys->mMakeOutput[id](dynSys, allocator); }
PMF_DEPLOY_STATIC NeDynamicSystemInputSizes ne_ds_get_system_input_sizes(const
NeDynamicSystem *ds) { NeDynamicSystemInputSizes sizes; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_Q ] = ds->mNumMajorModes; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_M ] = ds->mNumModes; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_T ] = 1; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_U ]
= ne_get_num_io_signals(ds->mIo[NE_INPUT_IO_TYPE] ,ds->mNumIo[NE_INPUT_IO_TYPE]);
sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_V ] =
ne_get_num_io_signals(ds->mIo[NE_INPUT_IO_TYPE], ds->mNumIo[NE_INPUT_IO_TYPE]);
sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_X ] = ds->mNumVariables; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_D ] = ds->mNumDiscreteRealVariables; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_E ] = ds->mNumFundamentalSamples; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_C ] = ds->mNumCache; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_W ] = ds->mNumDelays; sizes.mSizes[
NE_DYNAMIC_SYSTEM_INPUT_ID_S ] = 1; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_P_L
] = ds->mNumLogicalParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_P_I ] =
ds->mNumIntegerParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_P_J ] =
ds->mNumIndexParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_P_R ] =
ds->mNumRealParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_DP_L ] =
ds->mNumLogicalDerivedParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_DP_I ]
= ds->mNumIntegerDerivedParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_DP_J
] = ds->mNumIndexDerivedParameters; sizes.mSizes[ NE_DYNAMIC_SYSTEM_INPUT_ID_DP_R
] = ds->mNumRealDerivedParameters; return sizes; } PMF_DEPLOY_STATIC void
ne_ds_setup_logger(const NeDynamicSystem *dynSys, NeLoggerBuilder *builder) {
dynSys->mSetupLogger(dynSys, builder); } typedef enum NeEqGroupMethodIdTag {
NE_EQ_GROUP_INVALID = -1, NE_EQ_GROUP_ZC, NE_EQ_GROUP_MODE, NE_EQ_GROUP_CACHE,
NE_EQ_GROUP_UPDATE_R, NE_EQ_GROUP_UPDATE_I, NE_EQ_GROUP_SFO, NE_EQ_GROUP_SFP,
NE_EQ_GROUP_INIT_R, NE_EQ_GROUP_INIT_I, NE_EQ_GROUP_ASSERT, NE_EQ_GROUP_DEL_T,
NE_EQ_GROUP_DEL_V, NE_EQ_GROUP_DEL_V0, NE_EQ_GROUP_DEL_TMAX, NE_EQ_GROUP_DDELT,
NE_EQ_GROUP_DDELT_P, NE_EQ_GROUP_NUM } NeEqGroupMethodId; typedef enum
NeEqParamMethodIdTag { NE_EQ_PARAM_INVALID = -1, NE_EQ_PARAM_C1, NE_EQ_PARAM_NUM
} NeEqParamMethodId; typedef enum NeEqMethodIdTag { NE_EQ_INVALID = -1, NE_EQ_M,
NE_EQ_DM_P, NE_EQ_DM, NE_EQ_F, NE_EQ_VMF, NE_EQ_SLF, NE_EQ_VMM, NE_EQ_DF_P,
NE_EQ_DF, NE_EQ_DDF_P, NE_EQ_DDF, NE_EQ_TDF_P, NE_EQ_NUM } NeEqMethodId; typedef
union NeEqGroupMethodOutputTag { real_T * mZC; int32_T * mMODE; int32_T * mCACHE;
real_T * mUPDATE_R; int32_T * mUPDATE_I; real_T * mSFO; real_T * mSFP; real_T *
mINIT_R; int32_T * mINIT_I; int32_T * mASSERT; real_T * mDEL_T; real_T * mDEL_V;
real_T * mDEL_V0; real_T * mDEL_TMAX; real_T * mDDELT; int32_T * mDDELT_P; }
NeEqGroupMethodOutput; typedef union NeEqMethodParamOutputTag { real_T * mC1; }
NeEqParamMethodOutput; typedef union NeEqMethodOutputTag { real_T mM; int32_T *
mDM_P; real_T * mDM; real_T mF; boolean_T mVMF; boolean_T mSLF; boolean_T mVMM;
int32_T * mDF_P; real_T * mDF; int32_T * mDDF_P; real_T * mDDF; int32_T * mTDF_P;
} NeEqMethodOutput; typedef struct NeEqMethodInputTag NeEqMethodInput; typedef
struct NeElementEquationGroupInfoTag NeElementEquationGroupInfo; typedef void
*(*NeEqSetupFcn) (const NeElementEquationGroupInfo *); typedef void
(*NeEqCleanupFcn) (void *); typedef void (*NeEqParamMethod) (const void *,
NeEqParamMethodOutput *); typedef void (*NeEqMethod) (const NeEqMethodInput *,
NeEqMethodOutput *); struct NeEqMethodInputTag { real_T *mX; int32_T *mM; int32_T
*mQ; real_T *mW; void *mEqData; }; typedef struct EqDataTag EqData; enum
NeRtlPatternEnum { PATTERN_ENUM_INVALID = -1, NE_RTL_PATTERN_ID_DF_P,
PATTERN_ENUM_NUM }; typedef EqData *(*NeRtlEqSetupFcn)( size_t n, const void
**data, const size_t *sizes ); typedef void (*NeRtlEqCleanupFcn)( EqData * );
typedef void (*NeRtlEqMethod) ( const real_T * input, const int32_T * mode, const
int32_T * major, const EqData * data, NeEqMethodOutput * ); typedef void
(*NeRtlEqParamMethod)( const void *, NeEqParamMethodOutput * ); typedef void
(*NeRtlEqGroupMethod)( const real_T * input, const int32_T * mode, const int32_T
* major, const EqData * data, NeEqGroupMethodOutput * ); typedef struct
NeRtlEquationTag { NeRtlEqMethod mMethods [NE_EQ_NUM + 1]; NeRtlEqParamMethod
mParamMethods[NE_EQ_PARAM_NUM + 1]; size_t mNumMIdx; size_t *mMIdx;
NeEquationDomain mDomain; boolean_T mIsSwitchedLinear; size_t
mPatternSizes[PATTERN_ENUM_NUM]; } NeRtlEquation; typedef struct
NeRtlEqMethodsTag NeRtlEqMethods; struct NeRtlEqMethodsTag { NeRtlEqSetupFcn
mSetupFcn; NeRtlEqCleanupFcn mCleanupFcn; NeRtlEqGroupMethod
mGroupMethods[NE_EQ_GROUP_NUM + 1]; size_t mGroupSizes [NE_EQ_GROUP_NUM + 1];
size_t mNumEquations; const NeRtlEquation *mEquations; size_t
mNumReinitializableInputs; const size_t *mReinitializableInputs; }; typedef
struct NeRtlEqInfoTag NeRtlEqInfo; struct NeRtlEqInfoTag { const NeRtlEqMethods
*mMethods; EqData *mData; }; PMF_DEPLOY_STATIC EqData *ne_rtl_setup( const
NeRtlEqMethods *methods, size_t n, const void **data, const size_t *sizes ) {
EqData *dataOut = NULL; if ( methods->mSetupFcn != NULL ) { dataOut =
methods->mSetupFcn( n, data, sizes ); } return dataOut; } PMF_DEPLOY_STATIC void
ne_rtl_cleanup( const NeRtlEqMethods *methods, EqData *data ) { if (
methods->mCleanupFcn != NULL ) { methods->mCleanupFcn( data ); } }
PMF_DEPLOY_STATIC void ne_rtl_call_param_method( const NeRtlEqMethods *methods,
size_t eq, NeEqParamMethodId id, const void *eqData, NeEqParamMethodOutput
*output ) { if ( methods->mEquations[eq].mParamMethods[ id ] != NULL ) {
methods->mEquations[eq].mParamMethods[ id ]( eqData, output ); } } const
NeRtlEqMethods *nertl_counter(void); const NeRtlEqMethods *nertl_elm_2_pos(void);
const NeRtlEqMethods *nertl_fundamental_clutch(void); const NeRtlEqMethods
*nertl_hit_crossing(void); const NeRtlEqMethods *nertl_rand(void); const
NeRtlEqMethods *nertl_rand_uniform(void); const NeRtlEqMethods
*nertl_repeating_sequence(void); const NeRtlEqMethods
*nertl_simrf_ideal_delay(void); const NeRtlEqMethods *nertl_test_discrete(void);
const NeRtlEqMethods *nertl_test_switched_linear(void); const NeRtlEqMethods
*nertl_test_triggered_delay(void); const NeRtlEqMethods
*nertl_test_triggered_delay_init(void); const NeRtlEqMethods
*nertl_transfer_function1(void); void tlu1_eq_F_custom_function_(void *out, const
void* in ); void tlu1_eq_ZC_0_custom_function_(void *out, const void* in ); void
tlu1_eq_ZC_1_custom_function_(void *out, const void* in ); void
tlu1_eq_MODE_0_custom_function_(void *out, const void* in ); void
tlu1_eq_MODE_1_custom_function_(void *out, const void* in ); void
tlu1_eq_DF_0_1_custom_function_(void *out, const void* in ); void
tlu2_eq_F_custom_function_(void *out, const void* in ); void
tlu2_eq_ZC_0_custom_function_(void *out, const void* in ); void
tlu2_eq_ZC_1_custom_function_(void *out, const void* in ); void
tlu2_eq_ZC_2_custom_function_(void *out, const void* in ); void
tlu2_eq_ZC_3_custom_function_(void *out, const void* in ); void
tlu2_eq_MODE_0_custom_function_(void *out, const void* in ); void
tlu2_eq_MODE_1_custom_function_(void *out, const void* in ); void
tlu2_eq_MODE_2_custom_function_(void *out, const void* in ); void
tlu2_eq_MODE_3_custom_function_(void *out, const void* in ); void
tlu2_eq_DF_0_1_custom_function_(void *out, const void* in ); void
tlu2_eq_DF_1_1_custom_function_(void *out, const void* in ); void
floor_eq_F_custom_function_(void *out, const void* in ); void
floor_eq_ZC_0_custom_function_(void *out, const void* in ); void
floor_eq_ZC_1_custom_function_(void *out, const void* in ); void
floor_eq_MODE_0_custom_function_(void *out, const void* in ); void
floor_eq_MODE_1_custom_function_(void *out, const void* in ); void
floor_eq_DF_0_1_custom_function_(void *out, const void* in ); void
ceil_eq_F_custom_function_(void *out, const void* in ); void
ceil_eq_ZC_0_custom_function_(void *out, const void* in ); void
ceil_eq_ZC_1_custom_function_(void *out, const void* in ); void
ceil_eq_MODE_0_custom_function_(void *out, const void* in ); void
ceil_eq_MODE_1_custom_function_(void *out, const void* in ); void
ceil_eq_DF_0_1_custom_function_(void *out, const void* in ); void
fix_eq_F_custom_function_(void *out, const void* in ); void
fix_eq_ZC_0_custom_function_(void *out, const void* in ); void
fix_eq_ZC_1_custom_function_(void *out, const void* in ); void
fix_eq_MODE_0_custom_function_(void *out, const void* in ); void
fix_eq_MODE_1_custom_function_(void *out, const void* in ); void
fix_eq_DF_0_1_custom_function_(void *out, const void* in ); void
round_eq_F_custom_function_(void *out, const void* in ); void
round_eq_ZC_0_custom_function_(void *out, const void* in ); void
round_eq_ZC_1_custom_function_(void *out, const void* in ); void
round_eq_MODE_0_custom_function_(void *out, const void* in ); void
round_eq_MODE_1_custom_function_(void *out, const void* in ); void
round_eq_DF_0_1_custom_function_(void *out, const void* in ); void
ne_rtl_call_method_custom_function_(void *out, const void* in ); void
ne_rtl_call_group_method_custom_function_(void *out, const void* in ); typedef
struct FunDataTag FunData; void ne_rtl_call_method( const NeRtlEqMethods
*methods, size_t eq, NeEqMethodId id, const real_T * input, const int32_T * mode,
const int32_T * major, const EqData * data, NeEqMethodOutput *output ); void
ne_rtl_call_group_method( const NeRtlEqMethods *methods, NeEqGroupMethodId id,
const real_T * input, const int32_T * mode, const int32_T * major, const EqData *
data, NeEqGroupMethodOutput *output ); void tlu1_eq_setup(size_t n, const void
**data, const size_t *sizes, FunData ** dataOutp ); void tlu1_eq_cleanup( FunData
*data ); void tlu1_eq_F( const real_T * input, const int32_T * mode, const
int32_T * major, const FunData * data, real_T *f); void tlu1_eq_DF_0_1( const
real_T * input, const int32_T * mode, const int32_T * major, const FunData *
data, real_T *df); void tlu1_eq_MODE_0( const real_T * input, const int32_T *
mode, const int32_T * major, const FunData * data, int32_T *modeOut); void
tlu1_eq_MODE_1( const real_T * input, const int32_T * mode, const int32_T *
major, const FunData * data, int32_T *modeOut); void tlu1_eq_ZC_0( const real_T *
input, const int32_T * mode, const int32_T * major, const FunData * data, real_T
*out); void tlu1_eq_ZC_1( const real_T * input, const int32_T * mode, const
int32_T * major, const FunData * data, real_T *out); void tlu2_eq_setup(size_t n,
const void **data, const size_t *sizes, FunData ** dataOutp ); void
tlu2_eq_cleanup( FunData *data ); void tlu2_eq_F( const real_T * input, const
int32_T * mode, const int32_T * major, const FunData * data, real_T *f); void
tlu2_eq_DF_0_1( const real_T * input, const int32_T * mode, const int32_T *
major, const FunData * data, real_T *df); void tlu2_eq_DF_1_1( const real_T *
input, const int32_T * mode, const int32_T * major, const FunData * data, real_T
*df); void tlu2_eq_MODE_0( const real_T * input, const int32_T * mode, const
int32_T * major, const FunData * data, int32_T *modeOut); void tlu2_eq_MODE_1(
const real_T * input, const int32_T * mode, const int32_T * major, const FunData
* data, int32_T *modeOut); void tlu2_eq_MODE_2( const real_T * input, const
int32_T * mode, const int32_T * major, const FunData * data, int32_T *modeOut);
void tlu2_eq_MODE_3( const real_T * input, const int32_T * mode, const int32_T *
major, const FunData * data, int32_T *modeOut); void tlu2_eq_ZC_0( const real_T *
input, const int32_T * mode, const int32_T * major, const FunData * data, real_T
*out); void tlu2_eq_ZC_1( const real_T * input, const int32_T * mode, const
int32_T * major, const FunData * data, real_T *out); void tlu2_eq_ZC_2( const
real_T * input, const int32_T * mode, const int32_T * major, const FunData *
data, real_T *out); void tlu2_eq_ZC_3( const real_T * input, const int32_T *
mode, const int32_T * major, const FunData * data, real_T *out); void
floor_eq_setup(size_t n, const void **data, const size_t *sizes, FunData
**dataOutp); void floor_eq_cleanup(FunData *data); void floor_eq_F( const real_T
* input, const int32_T * mode, const int32_T * major, const FunData * data,
real_T *f); void floor_eq_DF_0_1( const real_T * input, const int32_T * mode,
const int32_T * major, const FunData * data, real_T * df); void floor_eq_MODE_0(
const real_T * input, const int32_T * mode, const int32_T * major, const FunData
* data, int32_T *modeOut ); void floor_eq_MODE_1( const real_T * input, const
int32_T * mode, const int32_T * major, const FunData * data, int32_T *modeOut );
void floor_eq_ZC_0(const real_T * input, const int32_T * mode, const int32_T *
major, const FunData * data, real_T *zc); void floor_eq_ZC_1(const real_T *
input, const int32_T * mode, const int32_T * major, const FunData * data, real_T
*zc); void ceil_eq_setup(size_t n, const void **data, const size_t *sizes,
FunData **dataOutp); void ceil_eq_cleanup(FunData *data); void ceil_eq_F( const
real_T * input, const int32_T * mode, const int32_T * major, const FunData *
data, real_T *f); void ceil_eq_DF_0_1( const real_T * input, const int32_T *
mode, const int32_T * major, const FunData * data, real_T * df); void
ceil_eq_MODE_0( const real_T * input, const int32_T * mode, const int32_T *
major, const FunData * data, int32_T *modeOut ); void ceil_eq_MODE_1( const
real_T * input, const int32_T * mode, const int32_T * major, const FunData *
data, int32_T *modeOut ); void ceil_eq_ZC_0(const real_T * input, const int32_T *
mode, const int32_T * major, const FunData * data, real_T *zc); void
ceil_eq_ZC_1(const real_T * input, const int32_T * mode, const int32_T * major,
const FunData * data, real_T *zc); void fix_eq_setup(size_t n, const void **data,
const size_t *sizes, FunData **dataOutp); void fix_eq_cleanup(FunData *data);
void fix_eq_F( const real_T * input, const int32_T * mode, const int32_T * major,
const FunData * data, real_T *f); void fix_eq_DF_0_1( const real_T * input, const
int32_T * mode, const int32_T * major, const FunData * data, real_T * df); void
fix_eq_MODE_0( const real_T * input, const int32_T * mode, const int32_T * major,
const FunData * data, int32_T *modeOut ); void fix_eq_MODE_1( const real_T *
input, const int32_T * mode, const int32_T * major, const FunData * data, int32_T
*modeOut ); void fix_eq_ZC_0(const real_T * input, const int32_T * mode, const
int32_T * major, const FunData * data, real_T *zc); void fix_eq_ZC_1(const real_T
* input, const int32_T * mode, const int32_T * major, const FunData * data,
real_T *zc); void round_eq_setup(size_t n, const void **data, const size_t
*sizes, FunData **dataOutp); void round_eq_cleanup(FunData *data); void
round_eq_F( const real_T * input, const int32_T * mode, const int32_T * major,
const FunData * data, real_T *f); void round_eq_DF_0_1( const real_T * input,
const int32_T * mode, const int32_T * major, const FunData * data, real_T * df);
void round_eq_MODE_0( const real_T * input, const int32_T * mode, const int32_T *
major, const FunData * data, int32_T *modeOut ); void round_eq_MODE_1( const
real_T * input, const int32_T * mode, const int32_T * major, const FunData *
data, int32_T *modeOut ); void round_eq_ZC_0(const real_T * input, const int32_T
* mode, const int32_T * major, const FunData * data, real_T *zc); void
round_eq_ZC_1(const real_T * input, const int32_T * mode, const int32_T * major,
const FunData * data, real_T *zc);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* _ne_ds_h */
