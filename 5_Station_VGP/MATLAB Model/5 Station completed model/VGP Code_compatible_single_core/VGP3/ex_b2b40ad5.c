#include "pm_std.h"
#include "external_std.h"
typedef struct ex_Qsk2XSyLTKr4dT3vMb4eN1 ex_tssZndnB40jO_RGxikopX1;struct
ex_Qsk2XSyLTKr4dT3vMb4eN1{int32_T *x;};typedef struct ex_iLlEpwr592OjwSFjo_OaK1
ex_i12E2uojT5T_SF9rcr8b82;struct ex_iLlEpwr592OjwSFjo_OaK1{uint32_T *x;};
extern int32_T ex_AYw_1C1hAo2dXKmju97mm0(const int32_T);extern int32_T
ex_jP6qyn5SvHsksFqu53Ywt1(uint32_T);typedef struct ex_PZjXC40cag2oJ88lkpwXz1
ex_N_v3us_A70Y5GPyTI8_N61;struct ex_PZjXC40cag2oJ88lkpwXz1{real_T *
ex_Oykw6K0HPhHwyTKBYVmkV_;real_T *ex_6PnIiNV6PoPlA1ihCbgyP_;int32_T *
ex_V1223Gsg2_1bKbHdwp5PT2;};static void ex_hLiDXH6wq_HKd46Bt1Dtp2(int32_T
ex_DTgb0ttXCPlPWcN7v_KZC_,int32_T *const out){int32_T ex_INuP1MbZ16qfYFyRD1reU0
;int32_T ex_PAFky__7iTOBA7aSwd4y51;real_T ex_xyKno9ueOIYaH8XrVw6tQ1;real_T
ex__C5ziQdaxfW5aFpxg2zZJ0;do{ex_DTgb0ttXCPlPWcN7v_KZC_=
ex_AYw_1C1hAo2dXKmju97mm0(ex_DTgb0ttXCPlPWcN7v_KZC_);ex_INuP1MbZ16qfYFyRD1reU0
= ex_DTgb0ttXCPlPWcN7v_KZC_;ex_xyKno9ueOIYaH8XrVw6tQ1= 2.0 *
4.6566128752457969e-10 *ex_INuP1MbZ16qfYFyRD1reU0 -1.0;
ex_DTgb0ttXCPlPWcN7v_KZC_= ex_AYw_1C1hAo2dXKmju97mm0(ex_DTgb0ttXCPlPWcN7v_KZC_
);ex_PAFky__7iTOBA7aSwd4y51= ex_DTgb0ttXCPlPWcN7v_KZC_;
ex__C5ziQdaxfW5aFpxg2zZJ0= 2.0 *4.6566128752457969e-10 *
ex_PAFky__7iTOBA7aSwd4y51 -1.0;}while(ex_xyKno9ueOIYaH8XrVw6tQ1 *
ex_xyKno9ueOIYaH8XrVw6tQ1 +ex__C5ziQdaxfW5aFpxg2zZJ0 *
ex__C5ziQdaxfW5aFpxg2zZJ0>1.0);out[0]= ex_INuP1MbZ16qfYFyRD1reU0;out[1]=
ex_PAFky__7iTOBA7aSwd4y51;}void compute_gaussian_value(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_N_v3us_A70Y5GPyTI8_N61 *in=(const ex_N_v3us_A70Y5GPyTI8_N61 *)
ex_8Knj_sbNPYaamO7zB0XjK0;real_T *out=(real_T *)ex_JC14Uma4n_uWFYyh6wmkX2;
real_T ex_xyKno9ueOIYaH8XrVw6tQ1= 2 *4.6566128752457969e-10 *in->
ex_V1223Gsg2_1bKbHdwp5PT2[0]-1.0;real_T ex__C5ziQdaxfW5aFpxg2zZJ0= 2 *
4.6566128752457969e-10 *in->ex_V1223Gsg2_1bKbHdwp5PT2[1]-1.0;
ex__C5ziQdaxfW5aFpxg2zZJ0= ex__C5ziQdaxfW5aFpxg2zZJ0 *
ex__C5ziQdaxfW5aFpxg2zZJ0 +ex_xyKno9ueOIYaH8XrVw6tQ1 *
ex_xyKno9ueOIYaH8XrVw6tQ1;out[0]=(sqrt(-2.0 *log(ex__C5ziQdaxfW5aFpxg2zZJ0)/
ex__C5ziQdaxfW5aFpxg2zZJ0)*ex_xyKno9ueOIYaH8XrVw6tQ1)*in->
ex_6PnIiNV6PoPlA1ihCbgyP_[0]+in->ex_Oykw6K0HPhHwyTKBYVmkV_[0];}void
update_gaussian_seed(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
ex_8Knj_sbNPYaamO7zB0XjK0){const ex_tssZndnB40jO_RGxikopX1 *in=(const
ex_tssZndnB40jO_RGxikopX1 *)ex_8Knj_sbNPYaamO7zB0XjK0;int32_T *out=(int32_T *)
ex_JC14Uma4n_uWFYyh6wmkX2;ex_hLiDXH6wq_HKd46Bt1Dtp2(in->x[1],out);}void
init_gaussian_seed(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
ex_8Knj_sbNPYaamO7zB0XjK0){const ex_i12E2uojT5T_SF9rcr8b82 *in=(const
ex_i12E2uojT5T_SF9rcr8b82 *)ex_8Knj_sbNPYaamO7zB0XjK0;int32_T *out=(int32_T *)
ex_JC14Uma4n_uWFYyh6wmkX2;int32_T ex_yHPrSIcEWDK9hl1llPimY0=
ex_jP6qyn5SvHsksFqu53Ywt1(in->x[0]);ex_hLiDXH6wq_HKd46Bt1Dtp2(
ex_yHPrSIcEWDK9hl1llPimY0,out);}
