#include "pm_std.h"
#include "external_std.h"
#include "pm_std.h"
typedef struct ex_IuYX6mMtzQRrlAKu3ip_E_ ex_cbyrbWqSk4amuoUetStLK0;struct
ex_IuYX6mMtzQRrlAKu3ip_E_{real_T *ex_A_srSgeyQdgCUkWuwyHbd1;real_T *
ex_qHGrqyLfXVeyuOsZ7rCPU0;real_T *ex_aGys3dHsbUjKIaWLKSbh_1;size_t *
ex_ciE8LKs8_EBMIcmRNjm312;};typedef real_T ex_esEokFlOVmuwrxG4VY0Kx_;static
size_t ex_L5fur6LFRji_Faer_7yzJ1(const real_T x,const real_T *
ex_kqTQ1epcuYM_DyDj2jQ1y1,const size_t n){size_t pm_SmSSPSQfR1qEYWsVj5ELF0;if(
x<ex_kqTQ1epcuYM_DyDj2jQ1y1[0]){pm_SmSSPSQfR1qEYWsVj5ELF0= 0;}else if(x>
ex_kqTQ1epcuYM_DyDj2jQ1y1[n -1]){pm_SmSSPSQfR1qEYWsVj5ELF0= n +1;}else{for(
pm_SmSSPSQfR1qEYWsVj5ELF0= 1;((pm_SmSSPSQfR1qEYWsVj5ELF0<=n)&&(
ex_kqTQ1epcuYM_DyDj2jQ1y1[pm_SmSSPSQfR1qEYWsVj5ELF0 -1]<x));++
pm_SmSSPSQfR1qEYWsVj5ELF0);}return pm_SmSSPSQfR1qEYWsVj5ELF0;}static void
ex_h9PBDMihcYS7CWc28W2Hk2(const ex_cbyrbWqSk4amuoUetStLK0 *
ex_6peHhhgu8wo0Kp3HDh_aI0,const size_t index,const real_T
ex_vKct5bj2VVv2h_QlqkYJ__,const boolean_T ex_xVJyoK3_zCEvg7tMJpsHl0,real_T *
out){const size_t ex_MXQeXSu_MWFOwfbChjq0w_= ex_6peHhhgu8wo0Kp3HDh_aI0->
ex_ciE8LKs8_EBMIcmRNjm312[0];const size_t ex_pUjRTsp47EHBscIpj7Ulg0=
ex_6peHhhgu8wo0Kp3HDh_aI0->ex_ciE8LKs8_EBMIcmRNjm312[1];const real_T *
ex_kqTQ1epcuYM_DyDj2jQ1y1= ex_6peHhhgu8wo0Kp3HDh_aI0->
ex_A_srSgeyQdgCUkWuwyHbd1;const real_T *ex_8B7ltUy9RiwsITRZEKL491=
ex_6peHhhgu8wo0Kp3HDh_aI0->ex_qHGrqyLfXVeyuOsZ7rCPU0;const real_T
ex_tTtxUlYB91DFoEeDuWMX42= ex_kqTQ1epcuYM_DyDj2jQ1y1[index -2];const real_T
ex_INFh9oCMwF1cYY_NM_qI6_= ex_kqTQ1epcuYM_DyDj2jQ1y1[index -1];size_t
pm_SmSSPSQfR1qEYWsVj5ELF0;for(pm_SmSSPSQfR1qEYWsVj5ELF0= 0;
pm_SmSSPSQfR1qEYWsVj5ELF0<ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0
;++pm_SmSSPSQfR1qEYWsVj5ELF0){const real_T ex_R7GeHlROOcMcs_D8xOULH_=
ex_8B7ltUy9RiwsITRZEKL491[ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0
*(index -2)+pm_SmSSPSQfR1qEYWsVj5ELF0];const real_T ex_2lOQ_J4Eg_4WEdK8QEWds2=
ex_8B7ltUy9RiwsITRZEKL491[ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0
*(index -1)+pm_SmSSPSQfR1qEYWsVj5ELF0];if(ex_xVJyoK3_zCEvg7tMJpsHl0){out[
pm_SmSSPSQfR1qEYWsVj5ELF0]=(ex_2lOQ_J4Eg_4WEdK8QEWds2 -
ex_R7GeHlROOcMcs_D8xOULH_)/(ex_INFh9oCMwF1cYY_NM_qI6_ -
ex_tTtxUlYB91DFoEeDuWMX42);}else{const real_T ex_2uBQKmJh8fN996cwNJ9xZ2=(
ex_vKct5bj2VVv2h_QlqkYJ__ -ex_tTtxUlYB91DFoEeDuWMX42)/(
ex_INFh9oCMwF1cYY_NM_qI6_ -ex_tTtxUlYB91DFoEeDuWMX42);out[
pm_SmSSPSQfR1qEYWsVj5ELF0]=(ex_R7GeHlROOcMcs_D8xOULH_ +
ex_2uBQKmJh8fN996cwNJ9xZ2 *(ex_2lOQ_J4Eg_4WEdK8QEWds2 -
ex_R7GeHlROOcMcs_D8xOULH_));}}}void tlu_simrf_F(PMValue
ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue ex_8Knj_sbNPYaamO7zB0XjK0){const
ex_cbyrbWqSk4amuoUetStLK0 *in=(const ex_cbyrbWqSk4amuoUetStLK0 *)
ex_8Knj_sbNPYaamO7zB0XjK0;ex_esEokFlOVmuwrxG4VY0Kx_ *out=(
ex_esEokFlOVmuwrxG4VY0Kx_ *)ex_JC14Uma4n_uWFYyh6wmkX2;const size_t
ex_MXQeXSu_MWFOwfbChjq0w_= in->ex_ciE8LKs8_EBMIcmRNjm312[0];const size_t
ex_pUjRTsp47EHBscIpj7Ulg0= in->ex_ciE8LKs8_EBMIcmRNjm312[1];const size_t
ex_aaoxK9WbdAx5eZJ1nk8lT_= in->ex_ciE8LKs8_EBMIcmRNjm312[2];const real_T
ex_aGys3dHsbUjKIaWLKSbh_1= *(in->ex_aGys3dHsbUjKIaWLKSbh_1);const size_t index
= ex_L5fur6LFRji_Faer_7yzJ1(ex_aGys3dHsbUjKIaWLKSbh_1,in->
ex_A_srSgeyQdgCUkWuwyHbd1,ex_aaoxK9WbdAx5eZJ1nk8lT_);if(index>=
ex_aaoxK9WbdAx5eZJ1nk8lT_ +1){size_t pm_SmSSPSQfR1qEYWsVj5ELF0;for(
pm_SmSSPSQfR1qEYWsVj5ELF0= 0;pm_SmSSPSQfR1qEYWsVj5ELF0<
ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0;++
pm_SmSSPSQfR1qEYWsVj5ELF0){out[pm_SmSSPSQfR1qEYWsVj5ELF0]= in->
ex_qHGrqyLfXVeyuOsZ7rCPU0[ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0
*(ex_aaoxK9WbdAx5eZJ1nk8lT_ -1)+pm_SmSSPSQfR1qEYWsVj5ELF0];}}else if(index<=1)
{size_t pm_SmSSPSQfR1qEYWsVj5ELF0;for(pm_SmSSPSQfR1qEYWsVj5ELF0= 0;
pm_SmSSPSQfR1qEYWsVj5ELF0<ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0
;++pm_SmSSPSQfR1qEYWsVj5ELF0){out[pm_SmSSPSQfR1qEYWsVj5ELF0]= in->
ex_qHGrqyLfXVeyuOsZ7rCPU0[pm_SmSSPSQfR1qEYWsVj5ELF0];}}else{
ex_h9PBDMihcYS7CWc28W2Hk2(in,index,ex_aGys3dHsbUjKIaWLKSbh_1,(0),out);}}void
tlu_simrf_DF(PMValue ex_JC14Uma4n_uWFYyh6wmkX2,ConstPMValue
ex_8Knj_sbNPYaamO7zB0XjK0){const ex_cbyrbWqSk4amuoUetStLK0 *in=(const
ex_cbyrbWqSk4amuoUetStLK0 *)ex_8Knj_sbNPYaamO7zB0XjK0;
ex_esEokFlOVmuwrxG4VY0Kx_ *out=(ex_esEokFlOVmuwrxG4VY0Kx_ *)
ex_JC14Uma4n_uWFYyh6wmkX2;const size_t ex_MXQeXSu_MWFOwfbChjq0w_= in->
ex_ciE8LKs8_EBMIcmRNjm312[0];const size_t ex_pUjRTsp47EHBscIpj7Ulg0= in->
ex_ciE8LKs8_EBMIcmRNjm312[1];const size_t ex_aaoxK9WbdAx5eZJ1nk8lT_= in->
ex_ciE8LKs8_EBMIcmRNjm312[2];const real_T ex_aGys3dHsbUjKIaWLKSbh_1= *(in->
ex_aGys3dHsbUjKIaWLKSbh_1);const size_t index= ex_L5fur6LFRji_Faer_7yzJ1(
ex_aGys3dHsbUjKIaWLKSbh_1,in->ex_A_srSgeyQdgCUkWuwyHbd1,
ex_aaoxK9WbdAx5eZJ1nk8lT_);if((index>=ex_aaoxK9WbdAx5eZJ1nk8lT_ +1)||(index<=1
)){size_t pm_SmSSPSQfR1qEYWsVj5ELF0;for(pm_SmSSPSQfR1qEYWsVj5ELF0= 0;
pm_SmSSPSQfR1qEYWsVj5ELF0<ex_MXQeXSu_MWFOwfbChjq0w_ *ex_pUjRTsp47EHBscIpj7Ulg0
;++pm_SmSSPSQfR1qEYWsVj5ELF0){out[pm_SmSSPSQfR1qEYWsVj5ELF0]= 0.0;}}else{
ex_h9PBDMihcYS7CWc28W2Hk2(in,index,ex_aGys3dHsbUjKIaWLKSbh_1,(1),out);}}
