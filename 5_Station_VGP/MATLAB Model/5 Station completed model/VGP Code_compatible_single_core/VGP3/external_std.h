#ifndef external_std_h
#define external_std_h
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef void* PMValue; typedef const void* ConstPMValue; void
tlu_1d_cubic_nearest_process(PMValue y, ConstPMValue u); void
tlu_1d_cubic_nearest_F(PMValue y, ConstPMValue u); void
tlu_1d_cubic_nearest_DF(PMValue y, ConstPMValue u); void
tlu_1d_cubic_linear_process(PMValue y, ConstPMValue u); void
tlu_1d_cubic_linear_F(PMValue y, ConstPMValue u); void
tlu_1d_cubic_linear_DF(PMValue y, ConstPMValue u); void
tlu_1d_linear_nearest_process(PMValue y, ConstPMValue u); void
tlu_1d_linear_nearest_F(PMValue y, ConstPMValue u); void
tlu_1d_linear_nearest_DF(PMValue y, ConstPMValue u); void
tlu_1d_linear_linear_process(PMValue y, ConstPMValue u); void
tlu_1d_linear_linear_F(PMValue y, ConstPMValue u); void
tlu_1d_linear_linear_DF(PMValue y, ConstPMValue u); void
tlu_1d_spline_nearest_process(PMValue y, ConstPMValue u); void
tlu_1d_spline_nearest_F(PMValue y, ConstPMValue u); void
tlu_1d_spline_nearest_DF(PMValue y, ConstPMValue u); void
tlu_1d_spline_linear_process(PMValue y, ConstPMValue u); void
tlu_1d_spline_linear_F(PMValue y, ConstPMValue u); void
tlu_1d_spline_linear_DF(PMValue y, ConstPMValue u); void
tlu_2d_cubic_nearest_process(PMValue y, ConstPMValue u); void
tlu_2d_cubic_nearest_F(PMValue y, ConstPMValue u); void
tlu_2d_cubic_nearest_DF1(PMValue y, ConstPMValue u); void
tlu_2d_cubic_nearest_DF2(PMValue y, ConstPMValue u); void
tlu_2d_cubic_linear_process(PMValue y, ConstPMValue u); void
tlu_2d_cubic_linear_F(PMValue y, ConstPMValue u); void
tlu_2d_cubic_linear_DF1(PMValue y, ConstPMValue u); void
tlu_2d_cubic_linear_DF2(PMValue y, ConstPMValue u); void
tlu_2d_linear_nearest_process(PMValue y, ConstPMValue u); void
tlu_2d_linear_nearest_F(PMValue y, ConstPMValue u); void
tlu_2d_linear_nearest_DF1(PMValue y, ConstPMValue u); void
tlu_2d_linear_nearest_DF2(PMValue y, ConstPMValue u); void
tlu_2d_linear_linear_process(PMValue y, ConstPMValue u); void
tlu_2d_linear_linear_F(PMValue y, ConstPMValue u); void
tlu_2d_linear_linear_DF1(PMValue y, ConstPMValue u); void
tlu_2d_linear_linear_DF2(PMValue y, ConstPMValue u); void
tlu_2d_spline_nearest_process(PMValue y, ConstPMValue u); void
tlu_2d_spline_nearest_F(PMValue y, ConstPMValue u); void
tlu_2d_spline_nearest_DF1(PMValue y, ConstPMValue u); void
tlu_2d_spline_nearest_DF2(PMValue y, ConstPMValue u); void
tlu_2d_spline_linear_process(PMValue y, ConstPMValue u); void
tlu_2d_spline_linear_F(PMValue y, ConstPMValue u); void
tlu_2d_spline_linear_DF1(PMValue y, ConstPMValue u); void
tlu_2d_spline_linear_DF2(PMValue y, ConstPMValue u); void
tlu2_1d_akima_nearest_process(PMValue out, ConstPMValue in); void
tlu2_1d_akima_linear_process(PMValue out, ConstPMValue in); void
tlu2_1d_akima_nearest_value(PMValue out, ConstPMValue in); void
tlu2_1d_akima_linear_value(PMValue out, ConstPMValue in); void
tlu2_1d_akima_nearest_derivatives(PMValue out, ConstPMValue in); void
tlu2_1d_akima_linear_derivatives(PMValue out, ConstPMValue in); void
tlu2_1d_linear_nearest_process(PMValue out, ConstPMValue in); void
tlu2_1d_linear_linear_process(PMValue out, ConstPMValue in); void
tlu2_1d_linear_nearest_value(PMValue out, ConstPMValue in); void
tlu2_1d_linear_linear_value(PMValue out, ConstPMValue in); void
tlu2_1d_linear_nearest_derivatives(PMValue out, ConstPMValue in); void
tlu2_1d_linear_linear_derivatives(PMValue out, ConstPMValue in); void
tlu2_2d_akima_nearest_process(PMValue out, ConstPMValue in); void
tlu2_2d_akima_linear_process(PMValue out, ConstPMValue in); void
tlu2_2d_akima_nearest_value(PMValue out, ConstPMValue in); void
tlu2_2d_akima_linear_value(PMValue out, ConstPMValue in); void
tlu2_2d_akima_nearest_derivatives(PMValue out, ConstPMValue in); void
tlu2_2d_akima_linear_derivatives(PMValue out, ConstPMValue in); void
tlu2_2d_linear_nearest_process(PMValue out, ConstPMValue in); void
tlu2_2d_linear_linear_process(PMValue out, ConstPMValue in); void
tlu2_2d_linear_nearest_value(PMValue out, ConstPMValue in); void
tlu2_2d_linear_linear_value(PMValue out, ConstPMValue in); void
tlu2_2d_linear_nearest_derivatives(PMValue out, ConstPMValue in); void
tlu2_2d_linear_linear_derivatives(PMValue out, ConstPMValue in); void
tlu2_3d_akima_nearest_process(PMValue out, ConstPMValue in); void
tlu2_3d_akima_linear_process(PMValue out, ConstPMValue in); void
tlu2_3d_akima_nearest_value(PMValue out, ConstPMValue in); void
tlu2_3d_akima_linear_value(PMValue out, ConstPMValue in); void
tlu2_3d_akima_nearest_derivatives(PMValue out, ConstPMValue in); void
tlu2_3d_akima_linear_derivatives(PMValue out, ConstPMValue in); void
tlu2_3d_linear_nearest_process(PMValue out, ConstPMValue in); void
tlu2_3d_linear_linear_process(PMValue out, ConstPMValue in); void
tlu2_3d_linear_nearest_value(PMValue out, ConstPMValue in); void
tlu2_3d_linear_linear_value(PMValue out, ConstPMValue in); void
tlu2_3d_linear_nearest_derivatives(PMValue out, ConstPMValue in); void
tlu2_3d_linear_linear_derivatives(PMValue out, ConstPMValue in); void
compute_gaussian_value(PMValue y, ConstPMValue u); void
update_gaussian_seed(PMValue y, ConstPMValue u); void init_gaussian_seed(PMValue
y, ConstPMValue u); void compute_uniform_value(PMValue y, ConstPMValue u); void
update_uniform_seed(PMValue y, ConstPMValue u); void init_uniform_seed(PMValue y,
ConstPMValue u); void tlu_simrf_F(PMValue y, ConstPMValue u); void
tlu_simrf_DF(PMValue y, ConstPMValue u);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* external_std_h */
