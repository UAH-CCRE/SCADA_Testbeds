#include "pm_std.h"
#include "external_std.h"
#include "pm_std.h"
extern size_t ex_L5fur6LFRji_Faer_7yzJ1(const real_T x,const real_T *
ex_kqTQ1epcuYM_DyDj2jQ1y1,const size_t n);extern boolean_T
ex_0GHZIgf9eIkm4JLO26S3l_(const size_t n,const real_T *
ex_OI6G61_JNe4A2dfwPtv0e1);extern void ex_88fZfZQUB5GeldICfHd5W0(const size_t n
,real_T *ex_OI6G61_JNe4A2dfwPtv0e1);typedef struct ex_hcVEz6vngAa9af4AfCSgn0
ex_YnqoD3vFb0iC7xd_KuIR32;struct ex_hcVEz6vngAa9af4AfCSgn0{real_T *
ex_o4vEMLK0HyE2rpCeHx1ax2;real_T *ex_qHGrqyLfXVeyuOsZ7rCPU0;size_t *n;};
typedef real_T ex_az29UWDxH5oFDrdpmo_Fj1;static real_T
ex_TIwTX_Rq8_s1goUCfE5UK1(const real_T ex_9_yWAFd98YjxIPCHmG5rr0,const real_T
y1,const real_T ex_Ds0gTsuf_v_EnBO9LqpvK_,const real_T
ex_uua6zXwxgZCHpX13yyrt82,const real_T x){return(y1 +((x -
ex_9_yWAFd98YjxIPCHmG5rr0)/(ex_Ds0gTsuf_v_EnBO9LqpvK_ -
ex_9_yWAFd98YjxIPCHmG5rr0))*(ex_uua6zXwxgZCHpX13yyrt82 -y1));};static real_T
ex_WwJMpaE_pzo09LUWw9_Pw0(const real_T ex_9_yWAFd98YjxIPCHmG5rr0,const real_T
y1,const real_T ex_Ds0gTsuf_v_EnBO9LqpvK_,const real_T
ex_uua6zXwxgZCHpX13yyrt82,const real_T x){return((ex_uua6zXwxgZCHpX13yyrt82 -
y1)/(ex_Ds0gTsuf_v_EnBO9LqpvK_ -ex_9_yWAFd98YjxIPCHmG5rr0));};typedef struct
ex_3EStW2H50qnZ6beRs8FI1_ ex_CDBtwDReIOd9fxEOHpM1k0;struct
ex_3EStW2H50qnZ6beRs8FI1_{real_T *ex_kqTQ1epcuYM_DyDj2jQ1y1;real_T *
ex_8B7ltUy9RiwsITRZEKL491;real_T *ex_5AACdI3mRA9m_gLxP4W7n0;};typedef struct
ex_En_LyKxEOtic0oQeOdulY1 ex_ktQGU_E4vPr78zuX7CJRB_;struct
ex_En_LyKxEOtic0oQeOdulY1{real_T *ex_kqTQ1epcuYM_DyDj2jQ1y1;real_T *
ex_8B7ltUy9RiwsITRZEKL491;real_T *x;boolean_T *pm_gN74BbsU5wqNjkJbC9b672;
size_t *n;};static real_T ex_h9PBDMihcYS7CWc28W2Hk2(const
ex_ktQGU_E4vPr78zuX7CJRB_ *ex_6peHhhgu8wo0Kp3HDh_aI0,const size_t index,const
real_T ex_vKct5bj2VVv2h_QlqkYJ__,const boolean_T ex_xVJyoK3_zCEvg7tMJpsHl0){
const size_t ex_OTMhYb6mZKAyJ0zoetNYt1= *(ex_6peHhhgu8wo0Kp3HDh_aI0->n);const
real_T *ex_kqTQ1epcuYM_DyDj2jQ1y1= ex_6peHhhgu8wo0Kp3HDh_aI0->
ex_kqTQ1epcuYM_DyDj2jQ1y1;const real_T *ex_8B7ltUy9RiwsITRZEKL491=
ex_6peHhhgu8wo0Kp3HDh_aI0->ex_8B7ltUy9RiwsITRZEKL491;size_t
ex_Ik2rJhoYOSA9PDw7ZkfwK_,ex_lBGCoA3zXf1dB_tVpLKGL0;real_T
ex_tTtxUlYB91DFoEeDuWMX42,ex_INFh9oCMwF1cYY_NM_qI6_,ex_R7GeHlROOcMcs_D8xOULH_,
ex_2lOQ_J4Eg_4WEdK8QEWds2;real_T ex_2uBQKmJh8fN996cwNJ9xZ2;if(index>=
ex_OTMhYb6mZKAyJ0zoetNYt1 +1){ex_Ik2rJhoYOSA9PDw7ZkfwK_=
ex_OTMhYb6mZKAyJ0zoetNYt1 -2;ex_lBGCoA3zXf1dB_tVpLKGL0=
ex_OTMhYb6mZKAyJ0zoetNYt1 -1;}else if(index<=1){ex_Ik2rJhoYOSA9PDw7ZkfwK_= 0;
ex_lBGCoA3zXf1dB_tVpLKGL0= 1;}else{ex_Ik2rJhoYOSA9PDw7ZkfwK_= index -2;
ex_lBGCoA3zXf1dB_tVpLKGL0= index -1;}ex_tTtxUlYB91DFoEeDuWMX42=
ex_kqTQ1epcuYM_DyDj2jQ1y1[ex_Ik2rJhoYOSA9PDw7ZkfwK_];ex_INFh9oCMwF1cYY_NM_qI6_
= ex_kqTQ1epcuYM_DyDj2jQ1y1[ex_lBGCoA3zXf1dB_tVpLKGL0];
ex_R7GeHlROOcMcs_D8xOULH_= ex_8B7ltUy9RiwsITRZEKL491[ex_Ik2rJhoYOSA9PDw7ZkfwK_
];ex_2lOQ_J4Eg_4WEdK8QEWds2= ex_8B7ltUy9RiwsITRZEKL491[
ex_lBGCoA3zXf1dB_tVpLKGL0];if(ex_xVJyoK3_zCEvg7tMJpsHl0){return(
ex_2lOQ_J4Eg_4WEdK8QEWds2 -ex_R7GeHlROOcMcs_D8xOULH_)/(
ex_INFh9oCMwF1cYY_NM_qI6_ -ex_tTtxUlYB91DFoEeDuWMX42);}
ex_2uBQKmJh8fN996cwNJ9xZ2=(ex_vKct5bj2VVv2h_QlqkYJ__ -
ex_tTtxUlYB91DFoEeDuWMX42)/(ex_INFh9oCMwF1cYY_NM_qI6_ -
ex_tTtxUlYB91DFoEeDuWMX42);return(ex_R7GeHlROOcMcs_D8xOULH_ +
ex_2uBQKmJh8fN996cwNJ9xZ2 *(ex_2lOQ_J4Eg_4WEdK8QEWds2 -
ex_R7GeHlROOcMcs_D8xOULH_));}void tlu_1d_linear_nearest_process(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_YnqoD3vFb0iC7xd_KuIR32 *in=(const ex_YnqoD3vFb0iC7xd_KuIR32 *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_CDBtwDReIOd9fxEOHpM1k0 *out=(
ex_CDBtwDReIOd9fxEOHpM1k0 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;memcpy(out->ex_kqTQ1epcuYM_DyDj2jQ1y1,in->ex_o4vEMLK0HyE2rpCeHx1ax2,n *sizeof
(real_T));memcpy(out->ex_8B7ltUy9RiwsITRZEKL491,in->ex_qHGrqyLfXVeyuOsZ7rCPU0,
n *sizeof(real_T));if(!ex_0GHZIgf9eIkm4JLO26S3l_(n,out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)){ex_88fZfZQUB5GeldICfHd5W0(n,out->
ex_kqTQ1epcuYM_DyDj2jQ1y1);ex_88fZfZQUB5GeldICfHd5W0(n,out->
ex_8B7ltUy9RiwsITRZEKL491);}(out->ex_5AACdI3mRA9m_gLxP4W7n0)[0]=(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[0];(out->ex_5AACdI3mRA9m_gLxP4W7n0)[1]=(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -1];}void tlu_1d_linear_linear_process(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){
tlu_1d_linear_nearest_process(ex_JC14Uma4n_uWFYyh6wmkX2,
ex_8Knj_sbNPYaamO7zB0XjK0);}void tlu_1d_linear_nearest_F(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_ktQGU_E4vPr78zuX7CJRB_ *in=(const ex_ktQGU_E4vPr78zuX7CJRB_ *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_az29UWDxH5oFDrdpmo_Fj1 *out=(
ex_az29UWDxH5oFDrdpmo_Fj1 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;if((in->pm_gN74BbsU5wqNjkJbC9b672)[0]){out[0]=(in->ex_8B7ltUy9RiwsITRZEKL491)
[0];}else if(!(in->pm_gN74BbsU5wqNjkJbC9b672)[1]){out[0]=(in->
ex_8B7ltUy9RiwsITRZEKL491)[n -1];}else{const real_T x= *(in->x);const size_t
index= ex_L5fur6LFRji_Faer_7yzJ1(x,in->ex_kqTQ1epcuYM_DyDj2jQ1y1,n);out[0]=
ex_h9PBDMihcYS7CWc28W2Hk2(in,index,x,(0));}}void tlu_1d_linear_nearest_DF(
PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){
const ex_ktQGU_E4vPr78zuX7CJRB_ *in=(const ex_ktQGU_E4vPr78zuX7CJRB_ *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_az29UWDxH5oFDrdpmo_Fj1 *out=(
ex_az29UWDxH5oFDrdpmo_Fj1 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;if((in->pm_gN74BbsU5wqNjkJbC9b672)[0]){out[0]= 0.0;}else if(!(in->
pm_gN74BbsU5wqNjkJbC9b672)[1]){out[0]= 0.0;}else{const real_T x= *(in->x);
const size_t index= ex_L5fur6LFRji_Faer_7yzJ1(x,in->ex_kqTQ1epcuYM_DyDj2jQ1y1,
n);out[0]= ex_h9PBDMihcYS7CWc28W2Hk2(in,index,x,(1));}}void
tlu_1d_linear_linear_F(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
ex_8Knj_sbNPYaamO7zB0XjK0){const ex_ktQGU_E4vPr78zuX7CJRB_ *in=(const
ex_ktQGU_E4vPr78zuX7CJRB_ *)ex_8Knj_sbNPYaamO7zB0XjK0;
ex_az29UWDxH5oFDrdpmo_Fj1 *out=(ex_az29UWDxH5oFDrdpmo_Fj1 *)
ex_JC14Uma4n_uWFYyh6wmkX2;const real_T x= *(in->x);const size_t n= *(in->n);if
((in->pm_gN74BbsU5wqNjkJbC9b672)[0]){out[0]= ex_TIwTX_Rq8_s1goUCfE5UK1((in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[0],(in->ex_8B7ltUy9RiwsITRZEKL491)[0],(in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[1],(in->ex_8B7ltUy9RiwsITRZEKL491)[1],x);}else if(!
(in->pm_gN74BbsU5wqNjkJbC9b672)[1]){out[0]= ex_TIwTX_Rq8_s1goUCfE5UK1((in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -2],(in->ex_8B7ltUy9RiwsITRZEKL491)[n -2],(in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -1],(in->ex_8B7ltUy9RiwsITRZEKL491)[n -1],x);}
else{const size_t index= ex_L5fur6LFRji_Faer_7yzJ1(x,in->
ex_kqTQ1epcuYM_DyDj2jQ1y1,n);out[0]= ex_h9PBDMihcYS7CWc28W2Hk2(in,index,x,(0))
;}}void tlu_1d_linear_linear_DF(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
ex_8Knj_sbNPYaamO7zB0XjK0){const ex_ktQGU_E4vPr78zuX7CJRB_ *in=(const
ex_ktQGU_E4vPr78zuX7CJRB_ *)ex_8Knj_sbNPYaamO7zB0XjK0;
ex_az29UWDxH5oFDrdpmo_Fj1 *out=(ex_az29UWDxH5oFDrdpmo_Fj1 *)
ex_JC14Uma4n_uWFYyh6wmkX2;const real_T x= *(in->x);const size_t n= *(in->n);if
((in->pm_gN74BbsU5wqNjkJbC9b672)[0]){out[0]= ex_WwJMpaE_pzo09LUWw9_Pw0((in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[0],(in->ex_8B7ltUy9RiwsITRZEKL491)[0],(in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[1],(in->ex_8B7ltUy9RiwsITRZEKL491)[1],x);}else if(!
(in->pm_gN74BbsU5wqNjkJbC9b672)[1]){out[0]= ex_WwJMpaE_pzo09LUWw9_Pw0((in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -2],(in->ex_8B7ltUy9RiwsITRZEKL491)[n -2],(in->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -1],(in->ex_8B7ltUy9RiwsITRZEKL491)[n -1],x);}
else{const size_t index= ex_L5fur6LFRji_Faer_7yzJ1(x,in->
ex_kqTQ1epcuYM_DyDj2jQ1y1,n);out[0]= ex_h9PBDMihcYS7CWc28W2Hk2(in,index,x,(1))
;}}
