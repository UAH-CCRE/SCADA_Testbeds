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
ex_8B7ltUy9RiwsITRZEKL491;real_T *ex_gDBuMP55NisXTS_Or978e_;real_T *
ex_5AACdI3mRA9m_gLxP4W7n0;};typedef struct ex_En_LyKxEOtic0oQeOdulY1
ex_ktQGU_E4vPr78zuX7CJRB_;struct ex_En_LyKxEOtic0oQeOdulY1{real_T *
ex_kqTQ1epcuYM_DyDj2jQ1y1;real_T *ex_8B7ltUy9RiwsITRZEKL491;real_T *
ex_gDBuMP55NisXTS_Or978e_;real_T *x;boolean_T *pm_gN74BbsU5wqNjkJbC9b672;
size_t *n;};static void ex_EvnaHp_WiXimvjmXNkvEC2(const real_T *
ex_kqTQ1epcuYM_DyDj2jQ1y1,const real_T *ex_8B7ltUy9RiwsITRZEKL491,size_t
ex_OTMhYb6mZKAyJ0zoetNYt1,real_T *ex_gDBuMP55NisXTS_Or978e_){real_T *
ex_dHaXezXmjt7gKCLS0uxn2_= pmf_calloc(ex_OTMhYb6mZKAyJ0zoetNYt1 -1,sizeof(
real_T));real_T *ex_u4Ni9qCMdjAsZGbjYWBqS_= pmf_calloc(
ex_OTMhYb6mZKAyJ0zoetNYt1 -1,sizeof(real_T));real_T *ex_F0lEHZRLU_qljAkJXono51
= pmf_calloc(ex_OTMhYb6mZKAyJ0zoetNYt1,sizeof(real_T));real_T *
ex_pW5D8jbiMijyi7YBu7cxJ0= pmf_calloc(ex_OTMhYb6mZKAyJ0zoetNYt1,sizeof(real_T)
);real_T *ex_cUBIG1GUWIbyLeeHTCJAD2= pmf_calloc(ex_OTMhYb6mZKAyJ0zoetNYt1,
sizeof(real_T));size_t pm_SmSSPSQfR1qEYWsVj5ELF0;for(pm_SmSSPSQfR1qEYWsVj5ELF0
= 0;pm_SmSSPSQfR1qEYWsVj5ELF0<ex_OTMhYb6mZKAyJ0zoetNYt1 -1;++
pm_SmSSPSQfR1qEYWsVj5ELF0){ex_u4Ni9qCMdjAsZGbjYWBqS_[pm_SmSSPSQfR1qEYWsVj5ELF0
]= ex_kqTQ1epcuYM_DyDj2jQ1y1[pm_SmSSPSQfR1qEYWsVj5ELF0 +1]-
ex_kqTQ1epcuYM_DyDj2jQ1y1[pm_SmSSPSQfR1qEYWsVj5ELF0];ex_dHaXezXmjt7gKCLS0uxn2_
[pm_SmSSPSQfR1qEYWsVj5ELF0]=(ex_8B7ltUy9RiwsITRZEKL491[
pm_SmSSPSQfR1qEYWsVj5ELF0 +1]-ex_8B7ltUy9RiwsITRZEKL491[
pm_SmSSPSQfR1qEYWsVj5ELF0])/ ex_u4Ni9qCMdjAsZGbjYWBqS_[
pm_SmSSPSQfR1qEYWsVj5ELF0];}for(pm_SmSSPSQfR1qEYWsVj5ELF0= 0;
pm_SmSSPSQfR1qEYWsVj5ELF0<ex_OTMhYb6mZKAyJ0zoetNYt1 -2;++
pm_SmSSPSQfR1qEYWsVj5ELF0){if(ex_dHaXezXmjt7gKCLS0uxn2_[
pm_SmSSPSQfR1qEYWsVj5ELF0]*ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0
+1]>0){real_T ex_jnXLtX8zjAUv33luAJqeT_;real_T ex_pvM09KMYEmTze_Hk9_deT1;
real_T ex_k1ixHNiI7Bo5jjUtaTpzi0;real_T ex_SgBKSTiPUx00fTy4lySHK0;real_T
ex_cbFxWFzl7Q1fGOhbL75V41;ex_jnXLtX8zjAUv33luAJqeT_= ex_u4Ni9qCMdjAsZGbjYWBqS_
[pm_SmSSPSQfR1qEYWsVj5ELF0]+ex_u4Ni9qCMdjAsZGbjYWBqS_[
pm_SmSSPSQfR1qEYWsVj5ELF0 +1];ex_pvM09KMYEmTze_Hk9_deT1=(
ex_u4Ni9qCMdjAsZGbjYWBqS_[pm_SmSSPSQfR1qEYWsVj5ELF0]+ex_jnXLtX8zjAUv33luAJqeT_
)/ 3/ ex_jnXLtX8zjAUv33luAJqeT_;ex_k1ixHNiI7Bo5jjUtaTpzi0=(
ex_u4Ni9qCMdjAsZGbjYWBqS_[pm_SmSSPSQfR1qEYWsVj5ELF0 +1]+
ex_jnXLtX8zjAUv33luAJqeT_)/ 3/ ex_jnXLtX8zjAUv33luAJqeT_;if(fabs(
ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0])>fabs(
ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0 +1])){
ex_SgBKSTiPUx00fTy4lySHK0= fabs(ex_dHaXezXmjt7gKCLS0uxn2_[
pm_SmSSPSQfR1qEYWsVj5ELF0]);ex_cbFxWFzl7Q1fGOhbL75V41= fabs(
ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0 +1]);}else{
ex_SgBKSTiPUx00fTy4lySHK0= fabs(ex_dHaXezXmjt7gKCLS0uxn2_[
pm_SmSSPSQfR1qEYWsVj5ELF0 +1]);ex_cbFxWFzl7Q1fGOhbL75V41= fabs(
ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0]);}
ex_F0lEHZRLU_qljAkJXono51[pm_SmSSPSQfR1qEYWsVj5ELF0 +1]=
ex_cbFxWFzl7Q1fGOhbL75V41/(ex_pvM09KMYEmTze_Hk9_deT1 *(
ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0]/ ex_SgBKSTiPUx00fTy4lySHK0
)+ex_k1ixHNiI7Bo5jjUtaTpzi0 *(ex_dHaXezXmjt7gKCLS0uxn2_[
pm_SmSSPSQfR1qEYWsVj5ELF0 +1]/ ex_SgBKSTiPUx00fTy4lySHK0));}}
ex_F0lEHZRLU_qljAkJXono51[0]=((2 *ex_u4Ni9qCMdjAsZGbjYWBqS_[0]+
ex_u4Ni9qCMdjAsZGbjYWBqS_[1])*ex_dHaXezXmjt7gKCLS0uxn2_[0]-
ex_u4Ni9qCMdjAsZGbjYWBqS_[0]*ex_dHaXezXmjt7gKCLS0uxn2_[0])/(
ex_u4Ni9qCMdjAsZGbjYWBqS_[0]+ex_u4Ni9qCMdjAsZGbjYWBqS_[1]);if(
ex_F0lEHZRLU_qljAkJXono51[0]*ex_dHaXezXmjt7gKCLS0uxn2_[0]<0){
ex_F0lEHZRLU_qljAkJXono51[0]= 0;}else if(ex_dHaXezXmjt7gKCLS0uxn2_[0]*
ex_dHaXezXmjt7gKCLS0uxn2_[1]<0&&fabs(ex_F0lEHZRLU_qljAkJXono51[0])>fabs(3 *
ex_dHaXezXmjt7gKCLS0uxn2_[1])){ex_F0lEHZRLU_qljAkJXono51[0]= 3 *
ex_dHaXezXmjt7gKCLS0uxn2_[0];}ex_F0lEHZRLU_qljAkJXono51[
ex_OTMhYb6mZKAyJ0zoetNYt1 -1]=((2 *ex_u4Ni9qCMdjAsZGbjYWBqS_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2]+ex_u4Ni9qCMdjAsZGbjYWBqS_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -3])*ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2]-ex_u4Ni9qCMdjAsZGbjYWBqS_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2]*ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -3])/(ex_u4Ni9qCMdjAsZGbjYWBqS_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2]+ex_u4Ni9qCMdjAsZGbjYWBqS_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -3]);if(ex_F0lEHZRLU_qljAkJXono51[
ex_OTMhYb6mZKAyJ0zoetNYt1 -1]*ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2]<0){ex_F0lEHZRLU_qljAkJXono51[
ex_OTMhYb6mZKAyJ0zoetNYt1 -1]= 0;}else if(ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2]*ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -3]<0&&fabs(ex_F0lEHZRLU_qljAkJXono51[
ex_OTMhYb6mZKAyJ0zoetNYt1 -1])>fabs(3 *ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2])){ex_F0lEHZRLU_qljAkJXono51[
ex_OTMhYb6mZKAyJ0zoetNYt1 -1]= 3 *ex_dHaXezXmjt7gKCLS0uxn2_[
ex_OTMhYb6mZKAyJ0zoetNYt1 -2];}for(pm_SmSSPSQfR1qEYWsVj5ELF0= 0;
pm_SmSSPSQfR1qEYWsVj5ELF0<ex_OTMhYb6mZKAyJ0zoetNYt1 -1;++
pm_SmSSPSQfR1qEYWsVj5ELF0){ex_pW5D8jbiMijyi7YBu7cxJ0[pm_SmSSPSQfR1qEYWsVj5ELF0
]=(ex_dHaXezXmjt7gKCLS0uxn2_[pm_SmSSPSQfR1qEYWsVj5ELF0]-
ex_F0lEHZRLU_qljAkJXono51[pm_SmSSPSQfR1qEYWsVj5ELF0])/
ex_u4Ni9qCMdjAsZGbjYWBqS_[pm_SmSSPSQfR1qEYWsVj5ELF0];ex_cUBIG1GUWIbyLeeHTCJAD2
[pm_SmSSPSQfR1qEYWsVj5ELF0]=(ex_F0lEHZRLU_qljAkJXono51[
pm_SmSSPSQfR1qEYWsVj5ELF0 +1]-ex_dHaXezXmjt7gKCLS0uxn2_[
pm_SmSSPSQfR1qEYWsVj5ELF0])/ ex_u4Ni9qCMdjAsZGbjYWBqS_[
pm_SmSSPSQfR1qEYWsVj5ELF0];ex_gDBuMP55NisXTS_Or978e_[pm_SmSSPSQfR1qEYWsVj5ELF0
+0 *(ex_OTMhYb6mZKAyJ0zoetNYt1 -1)]=(ex_cUBIG1GUWIbyLeeHTCJAD2[
pm_SmSSPSQfR1qEYWsVj5ELF0]-ex_pW5D8jbiMijyi7YBu7cxJ0[pm_SmSSPSQfR1qEYWsVj5ELF0
])/ ex_u4Ni9qCMdjAsZGbjYWBqS_[pm_SmSSPSQfR1qEYWsVj5ELF0];
ex_gDBuMP55NisXTS_Or978e_[pm_SmSSPSQfR1qEYWsVj5ELF0 +1 *(
ex_OTMhYb6mZKAyJ0zoetNYt1 -1)]= 2 *ex_pW5D8jbiMijyi7YBu7cxJ0[
pm_SmSSPSQfR1qEYWsVj5ELF0]-ex_cUBIG1GUWIbyLeeHTCJAD2[pm_SmSSPSQfR1qEYWsVj5ELF0
];ex_gDBuMP55NisXTS_Or978e_[pm_SmSSPSQfR1qEYWsVj5ELF0 +2 *(
ex_OTMhYb6mZKAyJ0zoetNYt1 -1)]= ex_F0lEHZRLU_qljAkJXono51[
pm_SmSSPSQfR1qEYWsVj5ELF0];}pmf_free(ex_dHaXezXmjt7gKCLS0uxn2_);pmf_free(
ex_u4Ni9qCMdjAsZGbjYWBqS_);pmf_free(ex_F0lEHZRLU_qljAkJXono51);pmf_free(
ex_pW5D8jbiMijyi7YBu7cxJ0);pmf_free(ex_cUBIG1GUWIbyLeeHTCJAD2);}static real_T
ex_h9PBDMihcYS7CWc28W2Hk2(const ex_ktQGU_E4vPr78zuX7CJRB_ *
ex_6peHhhgu8wo0Kp3HDh_aI0,const size_t index,const real_T
ex_vKct5bj2VVv2h_QlqkYJ__,const boolean_T ex_xVJyoK3_zCEvg7tMJpsHl0){real_T
ex_JUjiqe0_pEuhg9gATVB_Z2= 0;const real_T *ex_kqTQ1epcuYM_DyDj2jQ1y1=
ex_6peHhhgu8wo0Kp3HDh_aI0->ex_kqTQ1epcuYM_DyDj2jQ1y1;const real_T *
ex_8B7ltUy9RiwsITRZEKL491= ex_6peHhhgu8wo0Kp3HDh_aI0->
ex_8B7ltUy9RiwsITRZEKL491;const real_T *ex_gDBuMP55NisXTS_Or978e_=
ex_6peHhhgu8wo0Kp3HDh_aI0->ex_gDBuMP55NisXTS_Or978e_;const size_t
ex_OTMhYb6mZKAyJ0zoetNYt1= *(ex_6peHhhgu8wo0Kp3HDh_aI0->n);real_T
ex_tTtxUlYB91DFoEeDuWMX42;size_t ex_Ik2rJhoYOSA9PDw7ZkfwK_;real_T
pm_9xuwQJgeHdekP5EKsGkzg0,ex_BqqeFz3N4AeaYfBJgZhXP1,ex_o4vEMLK0HyE2rpCeHx1ax2;
size_t pm_OUB2pptsvtdGL_LyqpgOa0;if(index>=ex_OTMhYb6mZKAyJ0zoetNYt1 +1){
ex_Ik2rJhoYOSA9PDw7ZkfwK_= ex_OTMhYb6mZKAyJ0zoetNYt1 -2;}else if(index<=1){
ex_Ik2rJhoYOSA9PDw7ZkfwK_= 0;}else{ex_Ik2rJhoYOSA9PDw7ZkfwK_= index -2;}
ex_tTtxUlYB91DFoEeDuWMX42= ex_kqTQ1epcuYM_DyDj2jQ1y1[ex_Ik2rJhoYOSA9PDw7ZkfwK_
];ex_o4vEMLK0HyE2rpCeHx1ax2= ex_vKct5bj2VVv2h_QlqkYJ__ -
ex_tTtxUlYB91DFoEeDuWMX42;pm_9xuwQJgeHdekP5EKsGkzg0= ex_gDBuMP55NisXTS_Or978e_
[ex_Ik2rJhoYOSA9PDw7ZkfwK_];ex_BqqeFz3N4AeaYfBJgZhXP1= 0.0;for(
pm_OUB2pptsvtdGL_LyqpgOa0= 1;pm_OUB2pptsvtdGL_LyqpgOa0<=2;++
pm_OUB2pptsvtdGL_LyqpgOa0){ex_BqqeFz3N4AeaYfBJgZhXP1= pm_9xuwQJgeHdekP5EKsGkzg0
+ex_o4vEMLK0HyE2rpCeHx1ax2 *ex_BqqeFz3N4AeaYfBJgZhXP1;
pm_9xuwQJgeHdekP5EKsGkzg0= ex_o4vEMLK0HyE2rpCeHx1ax2 *
pm_9xuwQJgeHdekP5EKsGkzg0 +ex_gDBuMP55NisXTS_Or978e_[ex_Ik2rJhoYOSA9PDw7ZkfwK_
+(ex_OTMhYb6mZKAyJ0zoetNYt1 -1)*pm_OUB2pptsvtdGL_LyqpgOa0];}
ex_BqqeFz3N4AeaYfBJgZhXP1= pm_9xuwQJgeHdekP5EKsGkzg0 +
ex_o4vEMLK0HyE2rpCeHx1ax2 *ex_BqqeFz3N4AeaYfBJgZhXP1;pm_9xuwQJgeHdekP5EKsGkzg0
= ex_o4vEMLK0HyE2rpCeHx1ax2 *pm_9xuwQJgeHdekP5EKsGkzg0 +
ex_8B7ltUy9RiwsITRZEKL491[ex_Ik2rJhoYOSA9PDw7ZkfwK_];if(
ex_xVJyoK3_zCEvg7tMJpsHl0){ex_JUjiqe0_pEuhg9gATVB_Z2= ex_BqqeFz3N4AeaYfBJgZhXP1
;}else{ex_JUjiqe0_pEuhg9gATVB_Z2= pm_9xuwQJgeHdekP5EKsGkzg0;}return
ex_JUjiqe0_pEuhg9gATVB_Z2;}void tlu_1d_cubic_nearest_process(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_YnqoD3vFb0iC7xd_KuIR32 *in=(const ex_YnqoD3vFb0iC7xd_KuIR32 *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_CDBtwDReIOd9fxEOHpM1k0 *out=(
ex_CDBtwDReIOd9fxEOHpM1k0 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;memcpy(out->ex_kqTQ1epcuYM_DyDj2jQ1y1,in->ex_o4vEMLK0HyE2rpCeHx1ax2,n *sizeof
(real_T));memcpy(out->ex_8B7ltUy9RiwsITRZEKL491,in->ex_qHGrqyLfXVeyuOsZ7rCPU0,
n *sizeof(real_T));if(!ex_0GHZIgf9eIkm4JLO26S3l_(n,out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)){ex_88fZfZQUB5GeldICfHd5W0(n,out->
ex_kqTQ1epcuYM_DyDj2jQ1y1);ex_88fZfZQUB5GeldICfHd5W0(n,out->
ex_8B7ltUy9RiwsITRZEKL491);}ex_EvnaHp_WiXimvjmXNkvEC2(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1,out->ex_8B7ltUy9RiwsITRZEKL491,n,out->
ex_gDBuMP55NisXTS_Or978e_);(out->ex_5AACdI3mRA9m_gLxP4W7n0)[0]=(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[0];(out->ex_5AACdI3mRA9m_gLxP4W7n0)[1]=(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -1];}void tlu_1d_cubic_linear_process(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_YnqoD3vFb0iC7xd_KuIR32 *in=(const ex_YnqoD3vFb0iC7xd_KuIR32 *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_CDBtwDReIOd9fxEOHpM1k0 *out=(
ex_CDBtwDReIOd9fxEOHpM1k0 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;memcpy(out->ex_kqTQ1epcuYM_DyDj2jQ1y1,in->ex_o4vEMLK0HyE2rpCeHx1ax2,n *sizeof
(real_T));memcpy(out->ex_8B7ltUy9RiwsITRZEKL491,in->ex_qHGrqyLfXVeyuOsZ7rCPU0,
n *sizeof(real_T));if(!ex_0GHZIgf9eIkm4JLO26S3l_(n,out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)){ex_88fZfZQUB5GeldICfHd5W0(n,out->
ex_kqTQ1epcuYM_DyDj2jQ1y1);ex_88fZfZQUB5GeldICfHd5W0(n,out->
ex_8B7ltUy9RiwsITRZEKL491);}ex_EvnaHp_WiXimvjmXNkvEC2(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1,out->ex_8B7ltUy9RiwsITRZEKL491,n,out->
ex_gDBuMP55NisXTS_Or978e_);(out->ex_5AACdI3mRA9m_gLxP4W7n0)[0]=(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[0];(out->ex_5AACdI3mRA9m_gLxP4W7n0)[1]=(out->
ex_kqTQ1epcuYM_DyDj2jQ1y1)[n -1];}void tlu_1d_cubic_nearest_F(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_ktQGU_E4vPr78zuX7CJRB_ *in=(const ex_ktQGU_E4vPr78zuX7CJRB_ *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_az29UWDxH5oFDrdpmo_Fj1 *out=(
ex_az29UWDxH5oFDrdpmo_Fj1 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;if((in->pm_gN74BbsU5wqNjkJbC9b672)[0]){out[0]=(in->ex_8B7ltUy9RiwsITRZEKL491)
[0];}else if(!(in->pm_gN74BbsU5wqNjkJbC9b672)[1]){out[0]=(in->
ex_8B7ltUy9RiwsITRZEKL491)[n -1];}else{const real_T x= *(in->x);const size_t
index= ex_L5fur6LFRji_Faer_7yzJ1(x,in->ex_kqTQ1epcuYM_DyDj2jQ1y1,n);out[0]=
ex_h9PBDMihcYS7CWc28W2Hk2(in,index,x,(0));}}void tlu_1d_cubic_nearest_DF(
PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){
const ex_ktQGU_E4vPr78zuX7CJRB_ *in=(const ex_ktQGU_E4vPr78zuX7CJRB_ *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_az29UWDxH5oFDrdpmo_Fj1 *out=(
ex_az29UWDxH5oFDrdpmo_Fj1 *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t n= *(in->n)
;if((in->pm_gN74BbsU5wqNjkJbC9b672)[0]){out[0]= 0.0;}else if(!(in->
pm_gN74BbsU5wqNjkJbC9b672)[1]){out[0]= 0.0;}else{const real_T x= *(in->x);
const size_t index= ex_L5fur6LFRji_Faer_7yzJ1(x,in->ex_kqTQ1epcuYM_DyDj2jQ1y1,
n);out[0]= ex_h9PBDMihcYS7CWc28W2Hk2(in,index,x,(1));}}void
tlu_1d_cubic_linear_F(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
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
;}}void tlu_1d_cubic_linear_DF(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
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
