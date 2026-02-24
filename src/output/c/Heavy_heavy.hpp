/**
 * Copyright (c) 2026 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_HEAVY_HPP_
#define _HEAVY_CONTEXT_HEAVY_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalPhasor.h"
#include "HvTable.h"
#include "HvControlSlice.h"
#include "HvControlCast.h"
#include "HvControlTabread.h"
#include "HvControlUnop.h"
#include "HvControlSystem.h"
#include "HvControlBinop.h"
#include "HvControlTabwrite.h"
#include "HvControlIf.h"
#include "HvControlPack.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvSignalVar.h"

class Heavy_heavy : public HeavyContext {

 public:
  Heavy_heavy(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_heavy();

  const char *getName() override { return "heavy"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 2; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;


  /*
  * Code for expr~ implementation
  * Write out the generic header code
  */

  // per class code

  // per object code


  // static sendMessage functions
  static void cSlice_Bx57uvw6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_VNlq9CXj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_E4CfZi5W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_DjySdKFe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_ypQiVV7R_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_MzsJVlIS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_Q5ZmhItY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ya1xh2rx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_59XfXVox_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_TFVimUlb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_Qpv2WxJi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_xUqbCYA4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ol6kjbg1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nv0mIrrW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_s93mPG1h_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_CPhe6Onh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_679f3hB8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_XuoxLZMe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_LDkrOUaU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_uTEZ9iOD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_GspTyaNS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_TJQX4orj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Z5BFzemh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_PRUerDkl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_jN3ZQFh8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_WAf4sr33_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Q0lqo1oK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_5aDEkdoO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_hNOcIZKj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_cqmKAcIF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_V0GJc7w4_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_2bmULu31_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_SZ1HL4HQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_f0vjuW4i_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_qOiy9TT7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_4J5beuic_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_ioPR2EMv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_WXZxIu86_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_PG6nLPPV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_eYmD2Kth_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_cfLLaseU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PsbQ3miE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Be54JnxX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_OYYkwwY2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_YCQhQybA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_Z9sgVR0U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Qihyf45a_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_jNaTds8O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_qhtvt80k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UWbvAujT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_05NRVOWb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_DGrhM4Yi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_eveIRZ3J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_YtY3AFqj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_q7yMyaMY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_a9xg1DcE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_KZZVx3Dg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_9LntvuXA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_krFQiPfL_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_FONOELcY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_2Viz8oX0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_2uailNU7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5iLDDroX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_M813dOR2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_sZu4GIrw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wF9qmSzg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JPzDCliw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_D6NAkc8x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_2MSZL0HZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_MJYNAwwS_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_Y46Bunad_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_wHLDiDaA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_LNtffcFT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LXJajNqY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_IgQZVift_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_DvQhoard_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HtVSTBHx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MiPX9f1F_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jkCzyGU4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_7AMA6gak_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_AOZNtsv7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_6o4NjOrh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_dITpopZp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_ubDolAOH_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_ZS2Wp7mR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_bZ9D3Z3X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ontsOYoB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vsxPvfAB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_T0oMfwFJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Gf9cpD0Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ITP2Pd96_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_1foFjkog_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_1kxzKvBb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_gVqrasLa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_jZsjpVl9_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cCast_ctByWSRo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_wTjCV9p3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_P9A0UmPo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_2j5aKC58_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_W1E8kixt_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_6DeTwsLi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_ZAJAjXY4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_QJWcZT9a_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_loVGtY1U_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_jenX1naE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ywydlWYX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_nDpgS3QA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_X1AYuCrm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_nG6BwIRa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_IQnvoR0B_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_GrDKzzsZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_4kHhiqKU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_8mVisc9l_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_460zhmCx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_LFd3aYFx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_nlLXsfGj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Jb8CVYPc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_OBR1xKWJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_uOx3wKoj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GgqtwLKs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jtoiKMWR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_lQOikhcI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5xtZtJXz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_BtNyjRsH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Ks00uYzH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_w9JlxX93_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_loF8rnxN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_XhyjvG2Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_aHrbeWKD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_jp295f0w_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_b36pr9vD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_yFuC7H4q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_mzbY3Ynu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_CayI6VF0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_wzEQogeR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_tfiUIupQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_J63CfCuR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_I2M4X9MK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_b915cH06_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_HntlOOUr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HXfxRhI0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Bn6Z2Dxf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_n3tDtKZj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_RGygtKvK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_Ldue13gv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ds55cEgy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_thbNXOYi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_pwBpjwzV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0vnXNECV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Kb6wxIen_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_eqhHCtUW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9C5Up5j4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jXO4Ipk7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ZD35gJek_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_23DqxJx6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_lfE1bXT0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_5ha4R9w3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_EOkuEltW_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_zdMrbjor_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_T3X4zQ3X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_QypSnFdx_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_vUUXN57g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_EakMs1N1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_mmHqQlXz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_uWTWsuiU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_3x7TcvvI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_xy1h15KW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sZ1Lqvp7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2qMLGloT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bTJl9Wns_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_zsUpxNqL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_toHySpS2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_sG1s3Dfu_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_3HEzm7DN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_6DMKHSTz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_ZRrE8zBr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FIJeBcMn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_iR18kBYE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_RSb5IPTc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_LbYsHzYe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vLqn2cFS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DH7yuFjw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_14m5Km29_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_2OoDdJID_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sqmje2li_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_JKUCnrkT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IotFHV6K_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_AgvuEZ8O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_o1Jg3S1A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_BL2gluGf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_psuKmuBJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_3xpObaMj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Q0J1CwxC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_KJWCYR4k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_NrmX0NBW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Cl2PAH7C_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_SUcFAxUI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_MmOcN1af_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_IyKk1bfw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_rofEINGS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_wsYnEWe2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_lsmXginu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_C9twer07_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_StbtoXCz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_nJ5D0PNf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_4K8jHrYA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_d8VBBWAJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Fy37uBYK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_tyMwY1Fg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_RMjtDx5c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MCvuEUe1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_U4gAlCC6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_vcS5wtB1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EpLQVEpP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VAuczMZK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_j4Nq9A2T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_F2bsGPHQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_ZTNXKqiz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_x80sCxdZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_DyDlU7h8_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_KYp2EHzg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_EWcFblCF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_nmiTedx1_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_QsRX1GMp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_ocmr8zkj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_UFXLhHX3_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_5LVocSCT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_QJ0urWO9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_QlIbBYU4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_QhUYEeci_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8HIfvM4J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_PUpPzIRn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_rRjWjGAU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_77tRegsX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_1Bhe3TOc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_mtlpoUrc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0XQN0rpy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_WImFdUkq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_BhiRwUcG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_pYNtFLWF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_Drzo6Nuu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_pGZrd8Zx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_G0WK6Jam_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_eup5P3K0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vYIZBe6r_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_a2XJPQhF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_VvEHBalu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_iR6jHDI0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_JiFdjP0F_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_enaD7IPW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_UqZn3pJd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_0WTwHPtk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_jKWYeDyQ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cCast_bxepMtAa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_55mXIbq2_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_3TOb1uKQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_OcPAbRWJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_3ukHbjFz_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cCast_irMuGnhF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_Q6aZh52O_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_P7yRE9X1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_JR5OZ7JN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_9LO5xinN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_ZzS8vxGU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_M9CxSETv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_Hz9hxnX4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_bksTHKY0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_7t3z8XEN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_bhW9LEcg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_AJPjnOqS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_dqSEucRu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_AGF4tH7k_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_aVTRqaHF_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_Hx86SU10_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_1frNzZny_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_0EKRJb4z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_9BACoTU9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_K4VaEWhB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Fp2SjUst_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Bp3clqRB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_B4ju3Wqi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_pCbzBmRb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_vfh9PzmI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_kkPfjJKV_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_xvlRoKZS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_fJIjyfcE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_KPe7d8yD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nuVxWOjd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_jZIISBD7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_hM05PVQw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IBygg9TF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2j8XDNSW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GfxEDflT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_7wijqASF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_MjHQ04Yz_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_1qZKA096_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabread_XGlI29Zh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_xIRsMaq7_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_gsisvPEA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_mX8MCOFF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_OppO3oKE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4QEsSBSh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_h6yAFDXJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_A3WqDw4J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_95vccudL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_V9JunGzq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_pxgIrUer_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_IhUIO3Ms_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_LbTR7F60_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_9rWN5kfy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_ZOR2AVCr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_wSvK99xn_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_8O1YfwGy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_hlKSVjT1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_XhmLtiQL_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_nqqO47cp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_Hk2yO5C5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_OsjcA99I_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_oktFgqji_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_JJw45i5G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_Q1KwYqUC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_aDyqVxh7_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_b4w7BMcB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_RgNBD1un_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_iWedTBib_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_I9kRTuu9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_BI3jXjVr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VNrHEqgQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6sdTfHI1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_X6QIrq3V_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_NuID23DF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_NbSRgNTr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_rSbx7RvU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_GkfEYHAN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Lcx4tE1G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_vT79ceRr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VNthAHsT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_PoLF2K2g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ySeqLZO3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_MOCvFihB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_C5lhKjtq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_cuXZWrVN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_fSSytMq1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_li812ZFH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ILfyj4pS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_y9a739pe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_4umJ7moQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_o0AcrWwr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_cS3POWyX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_vsH8LSMg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_TfQKHJU4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Vzv4wyvU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_PttSNo72_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_0EMKIjmx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_JCV0sq13_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_8ZHH97qW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Ktx1UwMY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VQA1iCj6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Q705rJHo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_9hBAeLMk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_SnRkkFne_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_wXZgdhOs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_m2zGmVL4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ePbURnpl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_WmdPX38J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_s6YJNn4x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_mXKCK2zA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_pc1hGxBr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_70yr1XcW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nyT7f947_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8nLkGwOV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_jpddYd33_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_nNI0tN1s_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_9P0ujLIT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_JWDHDoxL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fYe8PKYw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_1LZBK8IF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ZGcTLoAh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_RLNDlChm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ytZHE4HR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_gmEE7R1t_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_ivoZPpVn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_iEru2LnE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_hxmGE1uz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_i0rLgsMU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_uD8kqvkp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_AYDWTDb1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_uPIXesse_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_x019m1QZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_SRlei78Y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_YkBRJHu5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_OG4rWioP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vsxpeFpk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_nMKDwWtd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sHOuWDZ8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ZLbbcJCu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_Vgd4DT8h_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_KZiQJ78X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_rhgWA8bS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_qz9KcQJ7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_aBhYrhGU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSend_y7UDJ7gh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gppux2Ep_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FQflyFGn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nWwnYraO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sslm6Fbd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_jipvnWUb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_NlyLjmJo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_OWQISe4A_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_BVvicTf1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Rb4KjMCa_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_2iY6ySgH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_PSf9v7Tm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_v4kKkXLV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_EBYvF3am_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_8r0zT5qo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_tXLjaUyQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_hISwSgGW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_XiIqQ1qC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bByTEKFR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Zri0g7Cf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_xkNitfdh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_AJORIacz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Cw1MgNhW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_p2gpFqCb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_4aLil5CN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_twprzqWG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_zHAWhVTd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_HWuvdBrx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_EEiDDaMx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_MLgA66Lg_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_VjUFBnwQ;
  SignalPhasor sPhasor_iNWqynlv;
  SignalPhasor sPhasor_eaWKTY4m;
  SignalPhasor sPhasor_QslpjdQw;
  SignalPhasor sPhasor_31boaDNv;
  ControlSlice cSlice_Bx57uvw6;
  ControlSlice cSlice_VNlq9CXj;
  ControlSlice cSlice_E4CfZi5W;
  ControlVar cVar_DjySdKFe;
  ControlIf cIf_Q5ZmhItY;
  ControlBinop cBinop_ya1xh2rx;
  ControlIf cIf_59XfXVox;
  ControlIf cIf_TFVimUlb;
  ControlIf cIf_Qpv2WxJi;
  ControlIf cIf_xUqbCYA4;
  ControlBinop cBinop_Ol6kjbg1;
  ControlBinop cBinop_nv0mIrrW;
  ControlBinop cBinop_s93mPG1h;
  ControlBinop cBinop_uTEZ9iOD;
  ControlPack cPack_GspTyaNS;
  ControlPack cPack_TJQX4orj;
  ControlSlice cSlice_Z5BFzemh;
  ControlSlice cSlice_PRUerDkl;
  ControlSlice cSlice_jN3ZQFh8;
  ControlSlice cSlice_WAf4sr33;
  ControlSlice cSlice_Q0lqo1oK;
  ControlSlice cSlice_5aDEkdoO;
  ControlVar cVar_hNOcIZKj;
  ControlVar cVar_cqmKAcIF;
  ControlSlice cSlice_2bmULu31;
  ControlSlice cSlice_SZ1HL4HQ;
  ControlSlice cSlice_f0vjuW4i;
  ControlSlice cSlice_qOiy9TT7;
  ControlVar cVar_4J5beuic;
  ControlIf cIf_ioPR2EMv;
  ControlIf cIf_WXZxIu86;
  ControlIf cIf_PG6nLPPV;
  ControlVar cVar_eYmD2Kth;
  ControlIf cIf_cfLLaseU;
  ControlBinop cBinop_PsbQ3miE;
  ControlVar cVar_Be54JnxX;
  ControlIf cIf_Z9sgVR0U;
  ControlBinop cBinop_Qihyf45a;
  ControlBinop cBinop_UWbvAujT;
  ControlBinop cBinop_eveIRZ3J;
  ControlVar cVar_KZZVx3Dg;
  ControlTabread cTabread_9LntvuXA;
  ControlSlice cSlice_FONOELcY;
  ControlVar cVar_2Viz8oX0;
  ControlBinop cBinop_5iLDDroX;
  ControlBinop cBinop_wF9qmSzg;
  ControlBinop cBinop_D6NAkc8x;
  ControlTabread cTabread_2MSZL0HZ;
  ControlSlice cSlice_Y46Bunad;
  ControlVar cVar_wHLDiDaA;
  ControlBinop cBinop_LXJajNqY;
  ControlBinop cBinop_HtVSTBHx;
  ControlBinop cBinop_jkCzyGU4;
  ControlVar cVar_7AMA6gak;
  ControlSlice cSlice_AOZNtsv7;
  ControlSlice cSlice_6o4NjOrh;
  ControlTabread cTabread_dITpopZp;
  ControlSlice cSlice_ZS2Wp7mR;
  ControlVar cVar_bZ9D3Z3X;
  ControlBinop cBinop_vsxPvfAB;
  ControlBinop cBinop_ITP2Pd96;
  ControlBinop cBinop_1kxzKvBb;
  ControlVar cVar_gVqrasLa;
  ControlVar cVar_wTjCV9p3;
  ControlIf cIf_P9A0UmPo;
  ControlTabwrite cTabwrite_2j5aKC58;
  ControlSlice cSlice_6DeTwsLi;
  ControlTabwrite cTabwrite_ZAJAjXY4;
  ControlSlice cSlice_loVGtY1U;
  ControlVar cVar_jenX1naE;
  ControlVar cVar_ywydlWYX;
  ControlSlice cSlice_nDpgS3QA;
  ControlSlice cSlice_X1AYuCrm;
  ControlPack cPack_nG6BwIRa;
  ControlBinop cBinop_GgqtwLKs;
  ControlBinop cBinop_jtoiKMWR;
  ControlBinop cBinop_lQOikhcI;
  ControlBinop cBinop_5xtZtJXz;
  ControlIf cIf_I2M4X9MK;
  ControlVar cVar_b915cH06;
  ControlIf cIf_HntlOOUr;
  ControlBinop cBinop_HXfxRhI0;
  ControlVar cVar_Bn6Z2Dxf;
  ControlIf cIf_Ldue13gv;
  ControlBinop cBinop_ds55cEgy;
  ControlBinop cBinop_0vnXNECV;
  ControlBinop cBinop_9C5Up5j4;
  ControlVar cVar_lfE1bXT0;
  ControlTabwrite cTabwrite_5ha4R9w3;
  ControlSlice cSlice_zdMrbjor;
  ControlTabread cTabread_T3X4zQ3X;
  ControlSlice cSlice_vUUXN57g;
  ControlVar cVar_EakMs1N1;
  ControlBinop cBinop_uWTWsuiU;
  ControlBinop cBinop_sZ1Lqvp7;
  ControlBinop cBinop_bTJl9Wns;
  ControlIf cIf_zsUpxNqL;
  ControlTabread cTabread_toHySpS2;
  ControlSlice cSlice_3HEzm7DN;
  ControlVar cVar_6DMKHSTz;
  ControlBinop cBinop_FIJeBcMn;
  ControlBinop cBinop_LbYsHzYe;
  ControlBinop cBinop_DH7yuFjw;
  ControlIf cIf_rofEINGS;
  ControlVar cVar_wsYnEWe2;
  ControlIf cIf_lsmXginu;
  ControlBinop cBinop_C9twer07;
  ControlVar cVar_StbtoXCz;
  ControlIf cIf_d8VBBWAJ;
  ControlBinop cBinop_Fy37uBYK;
  ControlBinop cBinop_MCvuEUe1;
  ControlBinop cBinop_EpLQVEpP;
  ControlVar cVar_ZTNXKqiz;
  ControlTabwrite cTabwrite_x80sCxdZ;
  ControlSlice cSlice_KYp2EHzg;
  ControlTabwrite cTabwrite_EWcFblCF;
  ControlSlice cSlice_QsRX1GMp;
  ControlTabwrite cTabwrite_ocmr8zkj;
  ControlSlice cSlice_5LVocSCT;
  ControlIf cIf_77tRegsX;
  ControlVar cVar_1Bhe3TOc;
  ControlIf cIf_mtlpoUrc;
  ControlBinop cBinop_0XQN0rpy;
  ControlVar cVar_WImFdUkq;
  ControlIf cIf_Drzo6Nuu;
  ControlBinop cBinop_pGZrd8Zx;
  ControlBinop cBinop_vYIZBe6r;
  ControlBinop cBinop_iR6jHDI0;
  ControlVar cVar_0WTwHPtk;
  ControlVar cVar_55mXIbq2;
  ControlIf cIf_3TOb1uKQ;
  ControlVar cVar_OcPAbRWJ;
  ControlVar cVar_Q6aZh52O;
  ControlVar cVar_P7yRE9X1;
  ControlIf cIf_JR5OZ7JN;
  ControlIf cIf_9LO5xinN;
  ControlPack cPack_ZzS8vxGU;
  ControlVar cVar_M9CxSETv;
  ControlSlice cSlice_Hz9hxnX4;
  ControlSlice cSlice_bksTHKY0;
  ControlVar cVar_7t3z8XEN;
  ControlIf cIf_bhW9LEcg;
  ControlVar cVar_AJPjnOqS;
  ControlVar cVar_dqSEucRu;
  ControlTabread cTabread_AGF4tH7k;
  ControlSlice cSlice_Hx86SU10;
  ControlVar cVar_1frNzZny;
  ControlBinop cBinop_9BACoTU9;
  ControlBinop cBinop_Bp3clqRB;
  ControlBinop cBinop_pCbzBmRb;
  ControlTabread cTabread_vfh9PzmI;
  ControlSlice cSlice_xvlRoKZS;
  ControlVar cVar_fJIjyfcE;
  ControlBinop cBinop_nuVxWOjd;
  ControlBinop cBinop_IBygg9TF;
  ControlBinop cBinop_GfxEDflT;
  ControlTabwrite cTabwrite_7wijqASF;
  ControlSlice cSlice_1qZKA096;
  ControlTabread cTabread_XGlI29Zh;
  ControlSlice cSlice_gsisvPEA;
  ControlVar cVar_mX8MCOFF;
  ControlBinop cBinop_4QEsSBSh;
  ControlBinop cBinop_95vccudL;
  ControlBinop cBinop_pxgIrUer;
  ControlTabwrite cTabwrite_IhUIO3Ms;
  ControlSlice cSlice_9rWN5kfy;
  ControlTabwrite cTabwrite_ZOR2AVCr;
  ControlSlice cSlice_8O1YfwGy;
  ControlTabwrite cTabwrite_hlKSVjT1;
  ControlSlice cSlice_nqqO47cp;
  ControlTabwrite cTabwrite_Hk2yO5C5;
  ControlSlice cSlice_oktFgqji;
  ControlVar cVar_JJw45i5G;
  ControlTabwrite cTabwrite_Q1KwYqUC;
  ControlSlice cSlice_b4w7BMcB;
  ControlVar cVar_RgNBD1un;
  ControlSlice cSlice_iWedTBib;
  ControlSlice cSlice_I9kRTuu9;
  ControlVar cVar_BI3jXjVr;
  ControlBinop cBinop_VNrHEqgQ;
  ControlBinop cBinop_6sdTfHI1;
  ControlBinop cBinop_VNthAHsT;
  ControlBinop cBinop_PoLF2K2g;
  ControlBinop cBinop_C5lhKjtq;
  ControlBinop cBinop_o0AcrWwr;
  ControlBinop cBinop_70yr1XcW;
  ControlBinop cBinop_nyT7f947;
  ControlBinop cBinop_vsxpeFpk;
  ControlBinop cBinop_sHOuWDZ8;
  ControlBinop cBinop_ZLbbcJCu;
  HvTable hTable_Vgd4DT8h;
  HvTable hTable_KZiQJ78X;
  HvTable hTable_rhgWA8bS;
  ControlBinop cBinop_FQflyFGn;
  ControlBinop cBinop_nWwnYraO;
  ControlSlice cSlice_jipvnWUb;
  ControlSlice cSlice_NlyLjmJo;
  ControlSlice cSlice_OWQISe4A;
  ControlSlice cSlice_BVvicTf1;
  ControlSlice cSlice_2iY6ySgH;
  ControlSlice cSlice_PSf9v7Tm;
  ControlSlice cSlice_v4kKkXLV;
  ControlSlice cSlice_EBYvF3am;
  ControlSlice cSlice_8r0zT5qo;
  ControlBinop cBinop_tXLjaUyQ;
  ControlBinop cBinop_hISwSgGW;
  ControlBinop cBinop_XiIqQ1qC;
  ControlBinop cBinop_bByTEKFR;
  ControlBinop cBinop_Zri0g7Cf;
  SignalVarf sVarf_1yrQdxst;
  SignalVarf sVarf_CeHS8hbC;
  SignalVarf sVarf_p2wSbAQ0;
  SignalVarf sVarf_TamkdmTP;
  SignalVarf sVarf_MftE0OeT;
  SignalVarf sVarf_UfOqDW1W;
  SignalVarf sVarf_LCajUHmE;
  SignalVarf sVarf_D7dKXfBn;
  SignalVarf sVarf_wUeCy2mf;
  SignalVarf sVarf_acMHQEDX;
};

#endif // _HEAVY_CONTEXT_HEAVY_HPP_
