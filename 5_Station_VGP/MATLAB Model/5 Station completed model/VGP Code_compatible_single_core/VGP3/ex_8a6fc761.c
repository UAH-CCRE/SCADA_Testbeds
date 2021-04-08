#include "pm_std.h"
size_t ex_ia6STLGqo9aFeiYN0gcmB_(real_T *ex_tUzVGBAzf2uDE1xeON4Gc1,real_T *
ex_5LnJCGYiDv_7y1GYvBMv60,size_t *ex_yt2Bobcuk9gODDeT4FtSI0,const real_T *x,
const size_t n,const real_T ex_aoel664zPcTjzpXADn7l40,const boolean_T *
ex__Fs1QSAh80AZdrHllXj3g_,const boolean_T ex_1YXwEl8_6cUeYGB_i0l0p2);size_t
ex_XgFqE_qWosDa601lsTn6b1(const real_T *x,const size_t n,const real_T
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
boolean_T ex_1YXwEl8_6cUeYGB_i0l0p2){size_t ex_zqRxlQY_R2aAe0l80GR7z1;real_T
ex_w_oCkEWPNmlVJvldp25MJ1;real_T ex_3EwSP2D8RHe6dG6BQOgNv1,
ex_BWzU1iqUNGj0f00v_MJWy0;if(n<2){ex_tUzVGBAzf2uDE1xeON4Gc1[0]= 1.0;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]= 0.0;ex_5LnJCGYiDv_7y1GYvBMv60[0]= 0.0;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 0.0;*ex_yt2Bobcuk9gODDeT4FtSI0= 1;return 0;}else
{*ex_yt2Bobcuk9gODDeT4FtSI0= 2;}if(ex__Fs1QSAh80AZdrHllXj3g_[0]){
ex_zqRxlQY_R2aAe0l80GR7z1= 0;ex_3EwSP2D8RHe6dG6BQOgNv1= x[0];
ex_BWzU1iqUNGj0f00v_MJWy0= x[1];ex_w_oCkEWPNmlVJvldp25MJ1=
ex_BWzU1iqUNGj0f00v_MJWy0 -ex_3EwSP2D8RHe6dG6BQOgNv1;if(
ex_w_oCkEWPNmlVJvldp25MJ1==0.0){ex_tUzVGBAzf2uDE1xeON4Gc1[0]= 0.5;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]= 0.5;ex_5LnJCGYiDv_7y1GYvBMv60[0]= 0.0;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 0.0;return ex_zqRxlQY_R2aAe0l80GR7z1;}if(
ex_1YXwEl8_6cUeYGB_i0l0p2){ex_tUzVGBAzf2uDE1xeON4Gc1[0]=(
ex_BWzU1iqUNGj0f00v_MJWy0 -ex_aoel664zPcTjzpXADn7l40)/
ex_w_oCkEWPNmlVJvldp25MJ1;ex_tUzVGBAzf2uDE1xeON4Gc1[1]=(
ex_aoel664zPcTjzpXADn7l40 -ex_3EwSP2D8RHe6dG6BQOgNv1)/
ex_w_oCkEWPNmlVJvldp25MJ1;ex_5LnJCGYiDv_7y1GYvBMv60[0]= -1.0/
ex_w_oCkEWPNmlVJvldp25MJ1;ex_5LnJCGYiDv_7y1GYvBMv60[1]= 1.0/
ex_w_oCkEWPNmlVJvldp25MJ1;}else{ex_tUzVGBAzf2uDE1xeON4Gc1[0]= 1.0;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]= 0.0;ex_5LnJCGYiDv_7y1GYvBMv60[0]= 0.0;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 0.0;}}else if(!ex__Fs1QSAh80AZdrHllXj3g_[1]){
ex_zqRxlQY_R2aAe0l80GR7z1= n -2;ex_3EwSP2D8RHe6dG6BQOgNv1= x[n -2];
ex_BWzU1iqUNGj0f00v_MJWy0= x[n -1];ex_w_oCkEWPNmlVJvldp25MJ1=
ex_BWzU1iqUNGj0f00v_MJWy0 -ex_3EwSP2D8RHe6dG6BQOgNv1;if(
ex_w_oCkEWPNmlVJvldp25MJ1==0.0){ex_tUzVGBAzf2uDE1xeON4Gc1[0]= 0.5;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]= 0.5;ex_5LnJCGYiDv_7y1GYvBMv60[0]= 0.0;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 0.0;return ex_zqRxlQY_R2aAe0l80GR7z1;}if(
ex_1YXwEl8_6cUeYGB_i0l0p2){ex_tUzVGBAzf2uDE1xeON4Gc1[0]=(
ex_BWzU1iqUNGj0f00v_MJWy0 -ex_aoel664zPcTjzpXADn7l40)/
ex_w_oCkEWPNmlVJvldp25MJ1;ex_tUzVGBAzf2uDE1xeON4Gc1[1]=(
ex_aoel664zPcTjzpXADn7l40 -ex_3EwSP2D8RHe6dG6BQOgNv1)/
ex_w_oCkEWPNmlVJvldp25MJ1;ex_5LnJCGYiDv_7y1GYvBMv60[0]= -1.0/
ex_w_oCkEWPNmlVJvldp25MJ1;ex_5LnJCGYiDv_7y1GYvBMv60[1]= 1.0/
ex_w_oCkEWPNmlVJvldp25MJ1;}else{ex_tUzVGBAzf2uDE1xeON4Gc1[0]= 0.0;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]= 1.0;ex_5LnJCGYiDv_7y1GYvBMv60[0]= 0.0;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 0.0;}}else{ex_zqRxlQY_R2aAe0l80GR7z1=
ex_XgFqE_qWosDa601lsTn6b1(x,n,ex_aoel664zPcTjzpXADn7l40);if(
ex_zqRxlQY_R2aAe0l80GR7z1<=0){ex_zqRxlQY_R2aAe0l80GR7z1= 0;}else if(
ex_zqRxlQY_R2aAe0l80GR7z1>=n){ex_zqRxlQY_R2aAe0l80GR7z1= n -2;}else{--
ex_zqRxlQY_R2aAe0l80GR7z1;}ex_3EwSP2D8RHe6dG6BQOgNv1= x[
ex_zqRxlQY_R2aAe0l80GR7z1];ex_BWzU1iqUNGj0f00v_MJWy0= x[
ex_zqRxlQY_R2aAe0l80GR7z1 +1];ex_w_oCkEWPNmlVJvldp25MJ1=
ex_BWzU1iqUNGj0f00v_MJWy0 -ex_3EwSP2D8RHe6dG6BQOgNv1;if(
ex_w_oCkEWPNmlVJvldp25MJ1==0.0){ex_tUzVGBAzf2uDE1xeON4Gc1[0]= 0.5;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]= 0.5;ex_5LnJCGYiDv_7y1GYvBMv60[0]= 0.0;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 0.0;return ex_zqRxlQY_R2aAe0l80GR7z1;}
ex_tUzVGBAzf2uDE1xeON4Gc1[0]=(ex_BWzU1iqUNGj0f00v_MJWy0 -
ex_aoel664zPcTjzpXADn7l40)/ ex_w_oCkEWPNmlVJvldp25MJ1;
ex_tUzVGBAzf2uDE1xeON4Gc1[1]=(ex_aoel664zPcTjzpXADn7l40 -
ex_3EwSP2D8RHe6dG6BQOgNv1)/ ex_w_oCkEWPNmlVJvldp25MJ1;
ex_5LnJCGYiDv_7y1GYvBMv60[0]= -1.0/ ex_w_oCkEWPNmlVJvldp25MJ1;
ex_5LnJCGYiDv_7y1GYvBMv60[1]= 1.0/ ex_w_oCkEWPNmlVJvldp25MJ1;}return
ex_zqRxlQY_R2aAe0l80GR7z1;}
