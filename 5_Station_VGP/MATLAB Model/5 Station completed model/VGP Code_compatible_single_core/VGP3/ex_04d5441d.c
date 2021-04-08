#include "pm_std.h"
typedef void *PMValue;typedef const void *ConstPMValue;
#include "external_std.h"
size_t ex_XgFqE_qWosDa601lsTn6b1(const real_T *x,const size_t n,const real_T
ex_aoel664zPcTjzpXADn7l40);void ex_58tHK_FJLrTVg5pTR2KLX0(real_T *
ex__lerGssn0Ru_r3kSOzEmI_,const size_t ex_MXQeXSu_MWFOwfbChjq0w_,const size_t
ex_pUjRTsp47EHBscIpj7Ulg0,const size_t ex_yCjoCtCCNaaT3TpkcO0PN_,const size_t
ex_G5C_Yq8nLf6PL2EMNiFAc1,const size_t ex_KTkrfjRMBsZjPvzwkIouc_,const size_t
ex_x_teXoaz0hlS1RzJxhHla0);void ex_kxquG9pkEjt4fXtMQOsqG2(real_T *x,real_T *
ex_VxxeDNxb3XYZvQXh_7Mga_,const size_t n);void ex_nC4jUddYFsKRLzFkVBm3G0(
real_T *ex_9_yWAFd98YjxIPCHmG5rr0,real_T *ex_Ds0gTsuf_v_EnBO9LqpvK_,real_T *
ex_VxxeDNxb3XYZvQXh_7Mga_,const size_t ex_MXQeXSu_MWFOwfbChjq0w_,const size_t
ex_pUjRTsp47EHBscIpj7Ulg0);void ex_p_64ouPbD9bddOkoAZOpZ1(real_T *
ex_9_yWAFd98YjxIPCHmG5rr0,real_T *ex_Ds0gTsuf_v_EnBO9LqpvK_,real_T *
ex_7brxsD4NMqseJwvqqCXpb_,real_T *ex_VxxeDNxb3XYZvQXh_7Mga_,const size_t
ex_MXQeXSu_MWFOwfbChjq0w_,const size_t ex_pUjRTsp47EHBscIpj7Ulg0,const size_t
ex_yCjoCtCCNaaT3TpkcO0PN_);size_t ex_ia6STLGqo9aFeiYN0gcmB_(real_T *
ex_tUzVGBAzf2uDE1xeON4Gc1,real_T *ex_5LnJCGYiDv_7y1GYvBMv60,size_t *
ex_yt2Bobcuk9gODDeT4FtSI0,const real_T *x,const size_t n,const real_T
ex_aoel664zPcTjzpXADn7l40,const boolean_T *ex__Fs1QSAh80AZdrHllXj3g_,const
boolean_T ex_1YXwEl8_6cUeYGB_i0l0p2);static void ex_rweYrcVwoyC1CNGIlXOiH_(
PMValue out,ConstPMValue in,const boolean_T ex_1YXwEl8_6cUeYGB_i0l0p2,const
boolean_T ex_Qmu676yE9oxL758xSv1lO1);static void ex_yHfj6furiKagbUS6IlLsO_(
PMValue out,ConstPMValue in);void tlu2_1d_linear_nearest_process(PMValue out,
ConstPMValue in){ex_yHfj6furiKagbUS6IlLsO_(out,in);}void
tlu2_1d_linear_linear_process(PMValue out,ConstPMValue in){
ex_yHfj6furiKagbUS6IlLsO_(out,in);}static void ex_yHfj6furiKagbUS6IlLsO_(
PMValue out,ConstPMValue in){const real_T *ex_o4vEMLK0HyE2rpCeHx1ax2=(const
real_T *)((const void *const *)in)[0];const real_T *ex_Uls_Qya8OT6MAYc5Y2sHL0=
(const real_T *)((const void *const *)in)[1];const size_t n= *((const size_t *
)((const void *const *)in)[2]);real_T *x=(real_T *)((void **)out)[0];real_T *
ex_VxxeDNxb3XYZvQXh_7Mga_=(real_T *)((void **)out)[1];real_T *
ex_nG9lEleqRQ___s_o0rpbM2=(real_T *)((void **)out)[2];memcpy(x,
ex_o4vEMLK0HyE2rpCeHx1ax2,n *sizeof(real_T));memcpy(ex_VxxeDNxb3XYZvQXh_7Mga_,
ex_Uls_Qya8OT6MAYc5Y2sHL0,n *sizeof(real_T));ex_kxquG9pkEjt4fXtMQOsqG2(x,
ex_VxxeDNxb3XYZvQXh_7Mga_,n);ex_nG9lEleqRQ___s_o0rpbM2[0]= x[0];
ex_nG9lEleqRQ___s_o0rpbM2[1]= x[n -1];}void tlu2_1d_linear_nearest_value(
PMValue out,ConstPMValue in){ex_rweYrcVwoyC1CNGIlXOiH_(out,in,(0),(0));}void
tlu2_1d_linear_linear_value(PMValue out,ConstPMValue in){
ex_rweYrcVwoyC1CNGIlXOiH_(out,in,(1),(0));}void
tlu2_1d_linear_nearest_derivatives(PMValue out,ConstPMValue in){
ex_rweYrcVwoyC1CNGIlXOiH_(out,in,(0),(1));}void
tlu2_1d_linear_linear_derivatives(PMValue out,ConstPMValue in){
ex_rweYrcVwoyC1CNGIlXOiH_(out,in,(1),(1));}static void
ex_rweYrcVwoyC1CNGIlXOiH_(PMValue out,ConstPMValue in,const boolean_T
ex_1YXwEl8_6cUeYGB_i0l0p2,const boolean_T ex_Qmu676yE9oxL758xSv1lO1){const
real_T *x=(const real_T *)((const void *const *)in)[0];const real_T *
ex_VxxeDNxb3XYZvQXh_7Mga_=(const real_T *)((const void *const *)in)[1];const
size_t n= *((const size_t *)((const void *const *)in)[4]);const real_T
ex_aoel664zPcTjzpXADn7l40= *(const real_T *)((const void *const *)in)[2];const
boolean_T *ex__Fs1QSAh80AZdrHllXj3g_=(const boolean_T *)((const void *const *)
in)[3];real_T *ex_Tm5e8nZqqU9KpHRYeiRYn2=(real_T *)out;real_T
ex_tUzVGBAzf2uDE1xeON4Gc1[2];real_T ex_5LnJCGYiDv_7y1GYvBMv60[2];size_t
ex_yt2Bobcuk9gODDeT4FtSI0= 2;size_t ex_zqRxlQY_R2aAe0l80GR7z1=
ex_ia6STLGqo9aFeiYN0gcmB_(ex_tUzVGBAzf2uDE1xeON4Gc1,ex_5LnJCGYiDv_7y1GYvBMv60,
&ex_yt2Bobcuk9gODDeT4FtSI0,x,n,ex_aoel664zPcTjzpXADn7l40,
ex__Fs1QSAh80AZdrHllXj3g_,ex_1YXwEl8_6cUeYGB_i0l0p2);if(
ex_Qmu676yE9oxL758xSv1lO1){if(ex_yt2Bobcuk9gODDeT4FtSI0<2){
ex_Tm5e8nZqqU9KpHRYeiRYn2[0]= 0.0;}else{ex_Tm5e8nZqqU9KpHRYeiRYn2[0]=
ex_VxxeDNxb3XYZvQXh_7Mga_[ex_zqRxlQY_R2aAe0l80GR7z1]*ex_5LnJCGYiDv_7y1GYvBMv60
[0]+ex_VxxeDNxb3XYZvQXh_7Mga_[ex_zqRxlQY_R2aAe0l80GR7z1 +1]*
ex_5LnJCGYiDv_7y1GYvBMv60[1];}}else{if(ex_yt2Bobcuk9gODDeT4FtSI0<2){
ex_Tm5e8nZqqU9KpHRYeiRYn2[0]= ex_VxxeDNxb3XYZvQXh_7Mga_[0];}else{
ex_Tm5e8nZqqU9KpHRYeiRYn2[0]= ex_VxxeDNxb3XYZvQXh_7Mga_[
ex_zqRxlQY_R2aAe0l80GR7z1]*ex_tUzVGBAzf2uDE1xeON4Gc1[0]+
ex_VxxeDNxb3XYZvQXh_7Mga_[ex_zqRxlQY_R2aAe0l80GR7z1 +1]*
ex_tUzVGBAzf2uDE1xeON4Gc1[1];}}}
