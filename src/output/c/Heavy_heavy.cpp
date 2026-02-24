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

#include "Heavy_heavy.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_heavy *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_heavy_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_heavy));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_heavy(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_heavy_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_heavy));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_heavy(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_heavy_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_heavy();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_heavy::Heavy_heavy(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_init(&sPhasor_VjUFBnwQ, sampleRate);
  numBytes += sPhasor_init(&sPhasor_iNWqynlv, sampleRate);
  numBytes += sPhasor_init(&sPhasor_eaWKTY4m, sampleRate);
  numBytes += sPhasor_init(&sPhasor_QslpjdQw, sampleRate);
  numBytes += sPhasor_init(&sPhasor_31boaDNv, sampleRate);
  numBytes += cSlice_init(&cSlice_Bx57uvw6, 2, 1);
  numBytes += cSlice_init(&cSlice_VNlq9CXj, 1, 1);
  numBytes += cSlice_init(&cSlice_E4CfZi5W, 0, 1);
  numBytes += cVar_init_f(&cVar_DjySdKFe, 0.0f);
  numBytes += cIf_init(&cIf_Q5ZmhItY, false);
  numBytes += cIf_init(&cIf_59XfXVox, false);
  numBytes += cIf_init(&cIf_TFVimUlb, false);
  numBytes += cIf_init(&cIf_Qpv2WxJi, false);
  numBytes += cIf_init(&cIf_xUqbCYA4, false);
  numBytes += cBinop_init(&cBinop_s93mPG1h, 0.0f); // __eq
  numBytes += cPack_init(&cPack_GspTyaNS, 2, 0.0f, 0.0f);
  numBytes += cPack_init(&cPack_TJQX4orj, 3, 0.0f, 0.0f, 0.0f);
  numBytes += cSlice_init(&cSlice_Z5BFzemh, 1, 1);
  numBytes += cSlice_init(&cSlice_PRUerDkl, 0, 1);
  numBytes += cSlice_init(&cSlice_jN3ZQFh8, 1, 1);
  numBytes += cSlice_init(&cSlice_WAf4sr33, 0, 1);
  numBytes += cSlice_init(&cSlice_Q0lqo1oK, 1, 1);
  numBytes += cSlice_init(&cSlice_5aDEkdoO, 0, 1);
  numBytes += cVar_init_f(&cVar_hNOcIZKj, 0.0f);
  numBytes += cVar_init_f(&cVar_cqmKAcIF, 0.0f);
  numBytes += cSlice_init(&cSlice_2bmULu31, 1, -1);
  numBytes += cSlice_init(&cSlice_SZ1HL4HQ, 1, -1);
  numBytes += cSlice_init(&cSlice_f0vjuW4i, 1, 1);
  numBytes += cSlice_init(&cSlice_qOiy9TT7, 0, 1);
  numBytes += cVar_init_f(&cVar_4J5beuic, 0.0f);
  numBytes += cIf_init(&cIf_ioPR2EMv, false);
  numBytes += cIf_init(&cIf_WXZxIu86, false);
  numBytes += cIf_init(&cIf_PG6nLPPV, false);
  numBytes += cVar_init_f(&cVar_eYmD2Kth, 0.0f);
  numBytes += cIf_init(&cIf_cfLLaseU, false);
  numBytes += cVar_init_f(&cVar_Be54JnxX, 0.0f);
  numBytes += cIf_init(&cIf_Z9sgVR0U, false);
  numBytes += cBinop_init(&cBinop_UWbvAujT, 0.0f); // __lt
  numBytes += cVar_init_f(&cVar_KZZVx3Dg, 3.0f);
  numBytes += cTabread_init(&cTabread_9LntvuXA, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_FONOELcY, 1, -1);
  numBytes += cVar_init_s(&cVar_2Viz8oX0, "1023-used");
  numBytes += cBinop_init(&cBinop_wF9qmSzg, 0.0f); // __min
  numBytes += cTabread_init(&cTabread_2MSZL0HZ, &hTable_rhgWA8bS); // 1023-ids
  numBytes += cSlice_init(&cSlice_Y46Bunad, 1, -1);
  numBytes += cVar_init_s(&cVar_wHLDiDaA, "1023-ids");
  numBytes += cBinop_init(&cBinop_HtVSTBHx, 0.0f); // __min
  numBytes += cVar_init_f(&cVar_7AMA6gak, 0.0f);
  numBytes += cSlice_init(&cSlice_AOZNtsv7, 1, 1);
  numBytes += cSlice_init(&cSlice_6o4NjOrh, 0, 1);
  numBytes += cTabread_init(&cTabread_dITpopZp, &hTable_Vgd4DT8h); // 1023-pitches
  numBytes += cSlice_init(&cSlice_ZS2Wp7mR, 1, -1);
  numBytes += cVar_init_s(&cVar_bZ9D3Z3X, "1023-pitches");
  numBytes += cBinop_init(&cBinop_ITP2Pd96, 0.0f); // __min
  numBytes += cVar_init_f(&cVar_gVqrasLa, 0.0f);
  numBytes += cVar_init_f(&cVar_wTjCV9p3, 0.0f);
  numBytes += cIf_init(&cIf_P9A0UmPo, false);
  numBytes += cTabwrite_init(&cTabwrite_2j5aKC58, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_6DeTwsLi, 1, -1);
  numBytes += cTabwrite_init(&cTabwrite_ZAJAjXY4, &hTable_rhgWA8bS); // 1023-ids
  numBytes += cSlice_init(&cSlice_loVGtY1U, 1, -1);
  numBytes += cVar_init_f(&cVar_jenX1naE, 0.0f);
  numBytes += cVar_init_f(&cVar_ywydlWYX, 0.0f);
  numBytes += cSlice_init(&cSlice_nDpgS3QA, 1, 1);
  numBytes += cSlice_init(&cSlice_X1AYuCrm, 0, 1);
  numBytes += cPack_init(&cPack_nG6BwIRa, 2, 0.0f, 0.0f);
  numBytes += cBinop_init(&cBinop_GgqtwLKs, 0.0f); // __eq
  numBytes += cBinop_init(&cBinop_jtoiKMWR, 0.0f); // __logand
  numBytes += cBinop_init(&cBinop_lQOikhcI, 0.0f); // __logand
  numBytes += cBinop_init(&cBinop_5xtZtJXz, 0.0f); // __lt
  numBytes += cIf_init(&cIf_I2M4X9MK, false);
  numBytes += cVar_init_f(&cVar_b915cH06, 0.0f);
  numBytes += cIf_init(&cIf_HntlOOUr, false);
  numBytes += cVar_init_f(&cVar_Bn6Z2Dxf, 0.0f);
  numBytes += cIf_init(&cIf_Ldue13gv, false);
  numBytes += cBinop_init(&cBinop_0vnXNECV, 0.0f); // __lt
  numBytes += cVar_init_f(&cVar_lfE1bXT0, 3.0f);
  numBytes += cTabwrite_init(&cTabwrite_5ha4R9w3, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_zdMrbjor, 1, -1);
  numBytes += cTabread_init(&cTabread_T3X4zQ3X, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_vUUXN57g, 1, -1);
  numBytes += cVar_init_s(&cVar_EakMs1N1, "1023-used");
  numBytes += cBinop_init(&cBinop_sZ1Lqvp7, 0.0f); // __min
  numBytes += cIf_init(&cIf_zsUpxNqL, false);
  numBytes += cTabread_init(&cTabread_toHySpS2, &hTable_Vgd4DT8h); // 1023-pitches
  numBytes += cSlice_init(&cSlice_3HEzm7DN, 1, -1);
  numBytes += cVar_init_s(&cVar_6DMKHSTz, "1023-pitches");
  numBytes += cBinop_init(&cBinop_LbYsHzYe, 0.0f); // __min
  numBytes += cIf_init(&cIf_rofEINGS, false);
  numBytes += cVar_init_f(&cVar_wsYnEWe2, 0.0f);
  numBytes += cIf_init(&cIf_lsmXginu, false);
  numBytes += cVar_init_f(&cVar_StbtoXCz, 0.0f);
  numBytes += cIf_init(&cIf_d8VBBWAJ, false);
  numBytes += cBinop_init(&cBinop_MCvuEUe1, 0.0f); // __lt
  numBytes += cVar_init_f(&cVar_ZTNXKqiz, 3.0f);
  numBytes += cTabwrite_init(&cTabwrite_x80sCxdZ, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_KYp2EHzg, 1, -1);
  numBytes += cTabwrite_init(&cTabwrite_EWcFblCF, &hTable_rhgWA8bS); // 1023-ids
  numBytes += cSlice_init(&cSlice_QsRX1GMp, 1, -1);
  numBytes += cTabwrite_init(&cTabwrite_ocmr8zkj, &hTable_Vgd4DT8h); // 1023-pitches
  numBytes += cSlice_init(&cSlice_5LVocSCT, 1, -1);
  numBytes += cIf_init(&cIf_77tRegsX, false);
  numBytes += cVar_init_f(&cVar_1Bhe3TOc, 0.0f);
  numBytes += cIf_init(&cIf_mtlpoUrc, false);
  numBytes += cVar_init_f(&cVar_WImFdUkq, 0.0f);
  numBytes += cIf_init(&cIf_Drzo6Nuu, false);
  numBytes += cBinop_init(&cBinop_vYIZBe6r, 0.0f); // __lt
  numBytes += cVar_init_f(&cVar_0WTwHPtk, 3.0f);
  numBytes += cVar_init_f(&cVar_55mXIbq2, 0.0f);
  numBytes += cIf_init(&cIf_3TOb1uKQ, false);
  numBytes += cVar_init_f(&cVar_OcPAbRWJ, 0.0f);
  numBytes += cVar_init_f(&cVar_Q6aZh52O, 0.0f);
  numBytes += cVar_init_f(&cVar_P7yRE9X1, 0.0f);
  numBytes += cIf_init(&cIf_JR5OZ7JN, false);
  numBytes += cIf_init(&cIf_9LO5xinN, false);
  numBytes += cPack_init(&cPack_ZzS8vxGU, 2, 0.0f, 0.0f);
  numBytes += cVar_init_f(&cVar_M9CxSETv, 0.0f);
  numBytes += cSlice_init(&cSlice_Hz9hxnX4, 1, 1);
  numBytes += cSlice_init(&cSlice_bksTHKY0, 0, 1);
  numBytes += cVar_init_f(&cVar_7t3z8XEN, 0.0f);
  numBytes += cIf_init(&cIf_bhW9LEcg, false);
  numBytes += cVar_init_f(&cVar_AJPjnOqS, 0.0f);
  numBytes += cVar_init_f(&cVar_dqSEucRu, 0.0f);
  numBytes += cTabread_init(&cTabread_AGF4tH7k, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_Hx86SU10, 1, -1);
  numBytes += cVar_init_s(&cVar_1frNzZny, "1023-used");
  numBytes += cBinop_init(&cBinop_Bp3clqRB, 0.0f); // __min
  numBytes += cTabread_init(&cTabread_vfh9PzmI, &hTable_rhgWA8bS); // 1023-ids
  numBytes += cSlice_init(&cSlice_xvlRoKZS, 1, -1);
  numBytes += cVar_init_s(&cVar_fJIjyfcE, "1023-ids");
  numBytes += cBinop_init(&cBinop_IBygg9TF, 0.0f); // __min
  numBytes += cTabwrite_init(&cTabwrite_7wijqASF, &hTable_Vgd4DT8h); // 1023-pitches
  numBytes += cSlice_init(&cSlice_1qZKA096, 1, -1);
  numBytes += cTabread_init(&cTabread_XGlI29Zh, &hTable_Vgd4DT8h); // 1023-pitches
  numBytes += cSlice_init(&cSlice_gsisvPEA, 1, -1);
  numBytes += cVar_init_s(&cVar_mX8MCOFF, "1023-pitches");
  numBytes += cBinop_init(&cBinop_95vccudL, 0.0f); // __min
  numBytes += cTabwrite_init(&cTabwrite_IhUIO3Ms, &hTable_Vgd4DT8h); // 1023-pitches
  numBytes += cSlice_init(&cSlice_9rWN5kfy, 1, -1);
  numBytes += cTabwrite_init(&cTabwrite_ZOR2AVCr, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_8O1YfwGy, 1, -1);
  numBytes += cTabwrite_init(&cTabwrite_hlKSVjT1, &hTable_rhgWA8bS); // 1023-ids
  numBytes += cSlice_init(&cSlice_nqqO47cp, 1, -1);
  numBytes += cTabwrite_init(&cTabwrite_Hk2yO5C5, &hTable_rhgWA8bS); // 1023-ids
  numBytes += cSlice_init(&cSlice_oktFgqji, 1, -1);
  numBytes += cVar_init_f(&cVar_JJw45i5G, 0.0f);
  numBytes += cTabwrite_init(&cTabwrite_Q1KwYqUC, &hTable_KZiQJ78X); // 1023-used
  numBytes += cSlice_init(&cSlice_b4w7BMcB, 1, -1);
  numBytes += cVar_init_f(&cVar_RgNBD1un, 0.0f);
  numBytes += cSlice_init(&cSlice_iWedTBib, 1, 1);
  numBytes += cSlice_init(&cSlice_I9kRTuu9, 0, 1);
  numBytes += cVar_init_f(&cVar_BI3jXjVr, 0.0f);
  numBytes += cBinop_init(&cBinop_VNrHEqgQ, 0.0f); // __logand
  numBytes += cBinop_init(&cBinop_6sdTfHI1, 0.0f); // __lt
  numBytes += cBinop_init(&cBinop_VNthAHsT, 0.0f); // __logand
  numBytes += cBinop_init(&cBinop_o0AcrWwr, 0.0f); // __lt
  numBytes += cBinop_init(&cBinop_70yr1XcW, 0.0f); // __logand
  numBytes += cBinop_init(&cBinop_ZLbbcJCu, 65535.0f); // __unimod
  numBytes += hTable_init(&hTable_Vgd4DT8h, 3);
  numBytes += hTable_init(&hTable_KZiQJ78X, 3);
  numBytes += hTable_init(&hTable_rhgWA8bS, 3);
  numBytes += cSlice_init(&cSlice_jipvnWUb, 1, 1);
  numBytes += cSlice_init(&cSlice_NlyLjmJo, 0, 1);
  numBytes += cSlice_init(&cSlice_OWQISe4A, 1, 1);
  numBytes += cSlice_init(&cSlice_BVvicTf1, 0, 1);
  numBytes += cSlice_init(&cSlice_2iY6ySgH, 1, -1);
  numBytes += cSlice_init(&cSlice_PSf9v7Tm, 1, -1);
  numBytes += cSlice_init(&cSlice_v4kKkXLV, 1, -1);
  numBytes += cSlice_init(&cSlice_EBYvF3am, 1, -1);
  numBytes += cSlice_init(&cSlice_8r0zT5qo, 1, -1);
  numBytes += sVarf_init(&sVarf_1yrQdxst, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_CeHS8hbC, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_p2wSbAQ0, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_TamkdmTP, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_MftE0OeT, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_UfOqDW1W, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_LCajUHmE, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_D7dKXfBn, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_wUeCy2mf, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_acMHQEDX, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_heavy::~Heavy_heavy() {
  cPack_free(&cPack_GspTyaNS);
  cPack_free(&cPack_TJQX4orj);
  cPack_free(&cPack_nG6BwIRa);
  cPack_free(&cPack_ZzS8vxGU);
  hTable_free(&hTable_Vgd4DT8h);
  hTable_free(&hTable_KZiQJ78X);
  hTable_free(&hTable_rhgWA8bS);
}

HvTable *Heavy_heavy::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0x62D84860: return &hTable_Vgd4DT8h; // 1023-pitches
    case 0x352F3ABD: return &hTable_KZiQJ78X; // 1023-used
    case 0x8E3D88CB: return &hTable_rhgWA8bS; // 1023-ids
    default: return nullptr;
  }
}

void Heavy_heavy::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCDF32FF6: { // 1023-currentVoiceId
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_p2gpFqCb_sendMessage);
      break;
    }
    case 0x3C8AE98D: { // 1023-indexOff
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_HWuvdBrx_sendMessage);
      break;
    }
    case 0x4FAD54EC: { // 1023-indexOn
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_zHAWhVTd_sendMessage);
      break;
    }
    case 0xD06AA72: { // 1023-isFirstOff
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_EEiDDaMx_sendMessage);
      break;
    }
    case 0xC2D593E2: { // 1023-isFirstOn
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_MLgA66Lg_sendMessage);
      break;
    }
    case 0x7598FECD: { // 1023-maxVoiceId
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_twprzqWG_sendMessage);
      break;
    }
    case 0x9A66BF9F: { // 1023-shouldSteal
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_Cw1MgNhW_sendMessage);
      break;
    }
    case 0x846C1935: { // 1023-voiceId++
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_4aLil5CN_sendMessage);
      break;
    }
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_xkNitfdh_sendMessage);
      break;
    }
    case 0x67E37CA3: { // __hv_notein
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_AJORIacz_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_heavy::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 0;
}



/*
 * Send Function Implementations
 */


void Heavy_heavy::cSlice_Bx57uvw6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_Ol6kjbg1_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_VNlq9CXj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cIf_onMessage(_c, &Context(_c)->cIf_Qpv2WxJi, 0, m, &cIf_Qpv2WxJi_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_59XfXVox, 0, m, &cIf_59XfXVox_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_E4CfZi5W_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cIf_onMessage(_c, &Context(_c)->cIf_xUqbCYA4, 0, m, &cIf_xUqbCYA4_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_TFVimUlb, 0, m, &cIf_TFVimUlb_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_DjySdKFe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_ya1xh2rx_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_Q5ZmhItY, 0, m, &cIf_Q5ZmhItY_sendMessage);
}

void Heavy_heavy::cUnop_ypQiVV7R_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_nv0mIrrW_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_s93mPG1h, HV_BINOP_EQ, 1, m, &cBinop_s93mPG1h_sendMessage);
}

void Heavy_heavy::cUnop_MzsJVlIS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_nv0mIrrW_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_s93mPG1h, HV_BINOP_EQ, 1, m, &cBinop_s93mPG1h_sendMessage);
}

void Heavy_heavy::cIf_Q5ZmhItY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cUnop_onMessage(_c, HV_UNOP_CEIL, m, &cUnop_MzsJVlIS_sendMessage);
      break;
    }
    case 1: {
      cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_ypQiVV7R_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_ya1xh2rx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_Q5ZmhItY, 1, m, &cIf_Q5ZmhItY_sendMessage);
}

void Heavy_heavy::cIf_59XfXVox_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cPack_onMessage(_c, &Context(_c)->cPack_GspTyaNS, 1, m, &cPack_GspTyaNS_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cIf_TFVimUlb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cPack_onMessage(_c, &Context(_c)->cPack_GspTyaNS, 0, m, &cPack_GspTyaNS_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cIf_Qpv2WxJi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cPack_onMessage(_c, &Context(_c)->cPack_GspTyaNS, 1, m, &cPack_GspTyaNS_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cIf_xUqbCYA4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cPack_onMessage(_c, &Context(_c)->cPack_GspTyaNS, 0, m, &cPack_GspTyaNS_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_Ol6kjbg1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_s93mPG1h, HV_BINOP_EQ, 0, m, &cBinop_s93mPG1h_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_uTEZ9iOD_sendMessage);
}

void Heavy_heavy::cBinop_nv0mIrrW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_LDkrOUaU_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_XuoxLZMe_sendMessage);
}

void Heavy_heavy::cBinop_s93mPG1h_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_679f3hB8_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_CPhe6Onh_sendMessage);
}

void Heavy_heavy::cCast_CPhe6Onh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_xUqbCYA4, 1, m, &cIf_xUqbCYA4_sendMessage);
}

void Heavy_heavy::cCast_679f3hB8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_59XfXVox, 1, m, &cIf_59XfXVox_sendMessage);
}

void Heavy_heavy::cCast_XuoxLZMe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_TFVimUlb, 1, m, &cIf_TFVimUlb_sendMessage);
}

void Heavy_heavy::cCast_LDkrOUaU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_Qpv2WxJi, 1, m, &cIf_Qpv2WxJi_sendMessage);
}

void Heavy_heavy::cBinop_uTEZ9iOD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cPack_GspTyaNS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_V0GJc7w4_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cPack_TJQX4orj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_Rb4KjMCa_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cSlice_Z5BFzemh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 127.0f, 0, m, &cBinop_tXLjaUyQ_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_PRUerDkl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sVarf_onMessage(_c, &Context(_c)->sVarf_1yrQdxst, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_jN3ZQFh8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 127.0f, 0, m, &cBinop_hISwSgGW_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_WAf4sr33_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sVarf_onMessage(_c, &Context(_c)->sVarf_p2wSbAQ0, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_Q0lqo1oK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 127.0f, 0, m, &cBinop_XiIqQ1qC_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_5aDEkdoO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sVarf_onMessage(_c, &Context(_c)->sVarf_MftE0OeT, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_hNOcIZKj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_NEQ, 0.0f, 0, m, &cBinop_sslm6Fbd_sendMessage);
}

void Heavy_heavy::cVar_cqmKAcIF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZLbbcJCu, HV_BINOP_MOD_UNIPOLAR, 0, m, &cBinop_ZLbbcJCu_sendMessage);
}

void Heavy_heavy::cSwitchcase_V0GJc7w4_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x7A5B032D: { // "stop"
      cSlice_onMessage(_c, &Context(_c)->cSlice_2bmULu31, 0, m, &cSlice_2bmULu31_sendMessage);
      break;
    }
    case 0x47BE8354: { // "clear"
      cSlice_onMessage(_c, &Context(_c)->cSlice_SZ1HL4HQ, 0, m, &cSlice_SZ1HL4HQ_sendMessage);
      break;
    }
    default: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_f0vjuW4i, 0, m, &cSlice_f0vjuW4i_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_qOiy9TT7, 0, m, &cSlice_qOiy9TT7_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_2bmULu31_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_2OoDdJID_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_14m5Km29_sendMessage);
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_2OoDdJID_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_14m5Km29_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_SZ1HL4HQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_QlIbBYU4_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_QhUYEeci_sendMessage);
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_QlIbBYU4_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_QhUYEeci_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_f0vjuW4i_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cVar_onMessage(_c, &Context(_c)->cVar_4J5beuic, 0, m, &cVar_4J5beuic_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_qOiy9TT7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cIf_onMessage(_c, &Context(_c)->cIf_ioPR2EMv, 0, m, &cIf_ioPR2EMv_sendMessage);
      cIf_onMessage(_c, &Context(_c)->cIf_WXZxIu86, 0, m, &cIf_WXZxIu86_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_4J5beuic_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_ZzS8vxGU, 1, m, &cPack_ZzS8vxGU_sendMessage);
  cPack_onMessage(_c, &Context(_c)->cPack_nG6BwIRa, 1, m, &cPack_nG6BwIRa_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_FQflyFGn_sendMessage);
}

void Heavy_heavy::cIf_ioPR2EMv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_4umJ7moQ_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ILfyj4pS_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_y9a739pe_sendMessage);
      cPack_onMessage(_c, &Context(_c)->cPack_ZzS8vxGU, 0, m, &cPack_ZzS8vxGU_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cIf_WXZxIu86_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cPack_onMessage(_c, &Context(_c)->cPack_nG6BwIRa, 0, m, &cPack_nG6BwIRa_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cIf_PG6nLPPV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_a9xg1DcE_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_q7yMyaMY_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_eYmD2Kth_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_jNaTds8O_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_qhtvt80k_sendMessage);
}

void Heavy_heavy::cIf_cfLLaseU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_05NRVOWb_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_DGrhM4Yi_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_PsbQ3miE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_cfLLaseU, 1, m, &cIf_cfLLaseU_sendMessage);
}

void Heavy_heavy::cVar_Be54JnxX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_Qihyf45a_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_Z9sgVR0U, 0, m, &cIf_Z9sgVR0U_sendMessage);
}

void Heavy_heavy::cUnop_OYYkwwY2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_PsbQ3miE_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_cfLLaseU, 0, m, &cIf_cfLLaseU_sendMessage);
}

void Heavy_heavy::cUnop_YCQhQybA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_PsbQ3miE_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_cfLLaseU, 0, m, &cIf_cfLLaseU_sendMessage);
}

void Heavy_heavy::cIf_Z9sgVR0U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cUnop_onMessage(_c, HV_UNOP_CEIL, m, &cUnop_YCQhQybA_sendMessage);
      break;
    }
    case 1: {
      cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_OYYkwwY2_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_Qihyf45a_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_Z9sgVR0U, 1, m, &cIf_Z9sgVR0U_sendMessage);
}

void Heavy_heavy::cCast_jNaTds8O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_UWbvAujT, HV_BINOP_LESS_THAN, 0, m, &cBinop_UWbvAujT_sendMessage);
}

void Heavy_heavy::cCast_qhtvt80k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_PG6nLPPV, 0, m, &cIf_PG6nLPPV_sendMessage);
}

void Heavy_heavy::cBinop_UWbvAujT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_PG6nLPPV, 1, m, &cIf_PG6nLPPV_sendMessage);
}

void Heavy_heavy::cCast_05NRVOWb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_UWbvAujT, HV_BINOP_LESS_THAN, 1, m, &cBinop_UWbvAujT_sendMessage);
}

void Heavy_heavy::cCast_DGrhM4Yi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_YtY3AFqj_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_eveIRZ3J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_eYmD2Kth, 0, m, &cVar_eYmD2Kth_sendMessage);
}

void Heavy_heavy::cMsg_YtY3AFqj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cVar_onMessage(_c, &Context(_c)->cVar_eYmD2Kth, 0, m, &cVar_eYmD2Kth_sendMessage);
}

void Heavy_heavy::cCast_q7yMyaMY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_eveIRZ3J_sendMessage);
}

void Heavy_heavy::cCast_a9xg1DcE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_4kHhiqKU_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_IQnvoR0B_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_GrDKzzsZ_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_8mVisc9l_sendMessage);
}

void Heavy_heavy::cVar_KZZVx3Dg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Be54JnxX, 0, m, &cVar_Be54JnxX_sendMessage);
}

void Heavy_heavy::cTabread_9LntvuXA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lQOikhcI, HV_BINOP_LOGICAL_AND, 0, m, &cBinop_lQOikhcI_sendMessage);
}

void Heavy_heavy::cSwitchcase_krFQiPfL_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_FONOELcY, 0, m, &cSlice_FONOELcY_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_M813dOR2_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_sZu4GIrw_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_FONOELcY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_9LntvuXA, 1, m, &cTabread_9LntvuXA_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_9LntvuXA, 1, m, &cTabread_9LntvuXA_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_2Viz8oX0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_JPzDCliw_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_2uailNU7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_D6NAkc8x_sendMessage);
}

void Heavy_heavy::cBinop_5iLDDroX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wF9qmSzg, HV_BINOP_MIN, 0, m, &cBinop_wF9qmSzg_sendMessage);
}

void Heavy_heavy::cCast_M813dOR2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_2Viz8oX0, 0, m, &cVar_2Viz8oX0_sendMessage);
}

void Heavy_heavy::cCast_sZu4GIrw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_5iLDDroX_sendMessage);
}

void Heavy_heavy::cBinop_wF9qmSzg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_9LntvuXA, 0, m, &cTabread_9LntvuXA_sendMessage);
}

void Heavy_heavy::cMsg_JPzDCliw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_2uailNU7_sendMessage);
}

void Heavy_heavy::cBinop_D6NAkc8x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_wF9qmSzg, HV_BINOP_MIN, 1, m, &cBinop_wF9qmSzg_sendMessage);
}

void Heavy_heavy::cTabread_2MSZL0HZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_loF8rnxN_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_XhyjvG2Q_sendMessage);
}

void Heavy_heavy::cSwitchcase_MJYNAwwS_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Y46Bunad, 0, m, &cSlice_Y46Bunad_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_DvQhoard_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_IgQZVift_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_Y46Bunad_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_2MSZL0HZ, 1, m, &cTabread_2MSZL0HZ_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_2MSZL0HZ, 1, m, &cTabread_2MSZL0HZ_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_wHLDiDaA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_MiPX9f1F_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_LNtffcFT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_jkCzyGU4_sendMessage);
}

void Heavy_heavy::cBinop_LXJajNqY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_HtVSTBHx, HV_BINOP_MIN, 0, m, &cBinop_HtVSTBHx_sendMessage);
}

void Heavy_heavy::cCast_IgQZVift_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_LXJajNqY_sendMessage);
}

void Heavy_heavy::cCast_DvQhoard_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_wHLDiDaA, 0, m, &cVar_wHLDiDaA_sendMessage);
}

void Heavy_heavy::cBinop_HtVSTBHx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_2MSZL0HZ, 0, m, &cTabread_2MSZL0HZ_sendMessage);
}

void Heavy_heavy::cMsg_MiPX9f1F_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_LNtffcFT_sendMessage);
}

void Heavy_heavy::cBinop_jkCzyGU4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_HtVSTBHx, HV_BINOP_MIN, 1, m, &cBinop_HtVSTBHx_sendMessage);
}

void Heavy_heavy::cVar_7AMA6gak_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_2j5aKC58, 1, m, &cTabwrite_2j5aKC58_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZAJAjXY4, 1, m, &cTabwrite_ZAJAjXY4_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_ywydlWYX, 1, m, &cVar_ywydlWYX_sendMessage);
}

void Heavy_heavy::cSlice_AOZNtsv7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_6o4NjOrh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_OBR1xKWJ_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_uOx3wKoj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabread_dITpopZp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GgqtwLKs, HV_BINOP_EQ, 0, m, &cBinop_GgqtwLKs_sendMessage);
}

void Heavy_heavy::cSwitchcase_ubDolAOH_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_ZS2Wp7mR, 0, m, &cSlice_ZS2Wp7mR_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_T0oMfwFJ_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Gf9cpD0Q_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_ZS2Wp7mR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_dITpopZp, 1, m, &cTabread_dITpopZp_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_dITpopZp, 1, m, &cTabread_dITpopZp_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_bZ9D3Z3X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_1foFjkog_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_ontsOYoB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_1kxzKvBb_sendMessage);
}

void Heavy_heavy::cBinop_vsxPvfAB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ITP2Pd96, HV_BINOP_MIN, 0, m, &cBinop_ITP2Pd96_sendMessage);
}

void Heavy_heavy::cCast_T0oMfwFJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_bZ9D3Z3X, 0, m, &cVar_bZ9D3Z3X_sendMessage);
}

void Heavy_heavy::cCast_Gf9cpD0Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_vsxPvfAB_sendMessage);
}

void Heavy_heavy::cBinop_ITP2Pd96_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_dITpopZp, 0, m, &cTabread_dITpopZp_sendMessage);
}

void Heavy_heavy::cMsg_1foFjkog_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ontsOYoB_sendMessage);
}

void Heavy_heavy::cBinop_1kxzKvBb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ITP2Pd96, HV_BINOP_MIN, 1, m, &cBinop_ITP2Pd96_sendMessage);
}

void Heavy_heavy::cVar_gVqrasLa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_5xtZtJXz, HV_BINOP_LESS_THAN, 1, m, &cBinop_5xtZtJXz_sendMessage);
}

void Heavy_heavy::cSwitchcase_jZsjpVl9_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3F800000: { // "1.0"
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ctByWSRo_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cCast_ctByWSRo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_w9JlxX93_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_Ks00uYzH_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_BtNyjRsH_sendMessage);
}

void Heavy_heavy::cVar_wTjCV9p3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_5xtZtJXz, HV_BINOP_LESS_THAN, 1, m, &cBinop_5xtZtJXz_sendMessage);
}

void Heavy_heavy::cIf_P9A0UmPo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_yFuC7H4q_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_mzbY3Ynu_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_wzEQogeR_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_nDpgS3QA, 0, m, &cSlice_nDpgS3QA_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_X1AYuCrm, 0, m, &cSlice_X1AYuCrm_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_tfiUIupQ_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_2j5aKC58_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_W1E8kixt_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_6DeTwsLi, 0, m, &cSlice_6DeTwsLi_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_2j5aKC58, 0, m, &cTabwrite_2j5aKC58_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_6DeTwsLi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_2j5aKC58, 2, m, &cTabwrite_2j5aKC58_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_2j5aKC58, 2, m, &cTabwrite_2j5aKC58_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_ZAJAjXY4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_QJWcZT9a_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_loVGtY1U, 0, m, &cSlice_loVGtY1U_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZAJAjXY4, 0, m, &cTabwrite_ZAJAjXY4_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_loVGtY1U_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZAJAjXY4, 2, m, &cTabwrite_ZAJAjXY4_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZAJAjXY4, 2, m, &cTabwrite_ZAJAjXY4_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_jenX1naE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_QJWcZT9a_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cVar_ywydlWYX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_sHOuWDZ8_sendMessage);
}

void Heavy_heavy::cSlice_nDpgS3QA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_X1AYuCrm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 1, m, &cPack_TJQX4orj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cPack_nG6BwIRa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_nlLXsfGj_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_Jb8CVYPc_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_AOZNtsv7, 0, m, &cSlice_AOZNtsv7_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_6o4NjOrh, 0, m, &cSlice_6o4NjOrh_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_P9A0UmPo, 0, m, &cIf_P9A0UmPo_sendMessage);
}

void Heavy_heavy::cCast_IQnvoR0B_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_MJYNAwwS_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_GrDKzzsZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_krFQiPfL_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_4kHhiqKU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_7AMA6gak, 1, m, &cVar_7AMA6gak_sendMessage);
}

void Heavy_heavy::cCast_8mVisc9l_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_ubDolAOH_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cMsg_460zhmCx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cIf_onMessage(_c, &Context(_c)->cIf_P9A0UmPo, 1, m, &cIf_P9A0UmPo_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_7AMA6gak, 0, m, &cVar_7AMA6gak_sendMessage);
}

void Heavy_heavy::cMsg_LFd3aYFx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cIf_onMessage(_c, &Context(_c)->cIf_P9A0UmPo, 1, m, &cIf_P9A0UmPo_sendMessage);
}

void Heavy_heavy::cCast_nlLXsfGj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_gVqrasLa, 0, m, &cVar_gVqrasLa_sendMessage);
}

void Heavy_heavy::cCast_Jb8CVYPc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_460zhmCx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_OBR1xKWJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_GgqtwLKs, HV_BINOP_EQ, 1, m, &cBinop_GgqtwLKs_sendMessage);
}

void Heavy_heavy::cCast_uOx3wKoj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_KZZVx3Dg, 0, m, &cVar_KZZVx3Dg_sendMessage);
}

void Heavy_heavy::cBinop_GgqtwLKs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jtoiKMWR, HV_BINOP_LOGICAL_AND, 0, m, &cBinop_jtoiKMWR_sendMessage);
}

void Heavy_heavy::cBinop_jtoiKMWR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_jZsjpVl9_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cBinop_lQOikhcI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_jtoiKMWR, HV_BINOP_LOGICAL_AND, 1, m, &cBinop_jtoiKMWR_sendMessage);
}

void Heavy_heavy::cBinop_5xtZtJXz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_lQOikhcI, HV_BINOP_LOGICAL_AND, 1, m, &cBinop_lQOikhcI_sendMessage);
}

void Heavy_heavy::cCast_BtNyjRsH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_7AMA6gak, 0, m, &cVar_7AMA6gak_sendMessage);
}

void Heavy_heavy::cCast_Ks00uYzH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_LFd3aYFx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_w9JlxX93_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_wTjCV9p3, 0, m, &cVar_wTjCV9p3_sendMessage);
}

void Heavy_heavy::cCast_loF8rnxN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_wTjCV9p3, 1, m, &cVar_wTjCV9p3_sendMessage);
}

void Heavy_heavy::cCast_XhyjvG2Q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_5xtZtJXz, HV_BINOP_LESS_THAN, 0, m, &cBinop_5xtZtJXz_sendMessage);
}

void Heavy_heavy::cCast_aHrbeWKD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_jenX1naE, 0, m, &cVar_jenX1naE_sendMessage);
}

void Heavy_heavy::cCast_jp295f0w_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_b36pr9vD_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_b36pr9vD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_4aLil5CN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_yFuC7H4q_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_CayI6VF0_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_mzbY3Ynu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_jp295f0w_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_aHrbeWKD_sendMessage);
}

void Heavy_heavy::cMsg_CayI6VF0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cSwitchcase_W1E8kixt_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_wzEQogeR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_J63CfCuR_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_tfiUIupQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_ywydlWYX, 0, m, &cVar_ywydlWYX_sendMessage);
}

void Heavy_heavy::cMsg_J63CfCuR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 2, m, &cPack_TJQX4orj_sendMessage);
}

void Heavy_heavy::cIf_I2M4X9MK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_23DqxJx6_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_ZD35gJek_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_b915cH06_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_thbNXOYi_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_pwBpjwzV_sendMessage);
}

void Heavy_heavy::cIf_HntlOOUr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Kb6wxIen_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_eqhHCtUW_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_HXfxRhI0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_HntlOOUr, 1, m, &cIf_HntlOOUr_sendMessage);
}

void Heavy_heavy::cVar_Bn6Z2Dxf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_ds55cEgy_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_Ldue13gv, 0, m, &cIf_Ldue13gv_sendMessage);
}

void Heavy_heavy::cUnop_n3tDtKZj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_HXfxRhI0_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_HntlOOUr, 0, m, &cIf_HntlOOUr_sendMessage);
}

void Heavy_heavy::cUnop_RGygtKvK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_HXfxRhI0_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_HntlOOUr, 0, m, &cIf_HntlOOUr_sendMessage);
}

void Heavy_heavy::cIf_Ldue13gv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cUnop_onMessage(_c, HV_UNOP_CEIL, m, &cUnop_RGygtKvK_sendMessage);
      break;
    }
    case 1: {
      cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_n3tDtKZj_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_ds55cEgy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_Ldue13gv, 1, m, &cIf_Ldue13gv_sendMessage);
}

void Heavy_heavy::cCast_thbNXOYi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0vnXNECV, HV_BINOP_LESS_THAN, 0, m, &cBinop_0vnXNECV_sendMessage);
}

void Heavy_heavy::cCast_pwBpjwzV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_I2M4X9MK, 0, m, &cIf_I2M4X9MK_sendMessage);
}

void Heavy_heavy::cBinop_0vnXNECV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_I2M4X9MK, 1, m, &cIf_I2M4X9MK_sendMessage);
}

void Heavy_heavy::cCast_Kb6wxIen_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0vnXNECV, HV_BINOP_LESS_THAN, 1, m, &cBinop_0vnXNECV_sendMessage);
}

void Heavy_heavy::cCast_eqhHCtUW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jXO4Ipk7_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_9C5Up5j4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_b915cH06, 0, m, &cVar_b915cH06_sendMessage);
}

void Heavy_heavy::cMsg_jXO4Ipk7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cVar_onMessage(_c, &Context(_c)->cVar_b915cH06, 0, m, &cVar_b915cH06_sendMessage);
}

void Heavy_heavy::cCast_ZD35gJek_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_9C5Up5j4_sendMessage);
}

void Heavy_heavy::cCast_23DqxJx6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_o1Jg3S1A_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_AgvuEZ8O_sendMessage);
}

void Heavy_heavy::cVar_lfE1bXT0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Bn6Z2Dxf, 0, m, &cVar_Bn6Z2Dxf_sendMessage);
}

void Heavy_heavy::cTabwrite_5ha4R9w3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_EOkuEltW_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_zdMrbjor, 0, m, &cSlice_zdMrbjor_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_5ha4R9w3, 0, m, &cTabwrite_5ha4R9w3_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_zdMrbjor_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_5ha4R9w3, 2, m, &cTabwrite_5ha4R9w3_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_5ha4R9w3, 2, m, &cTabwrite_5ha4R9w3_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabread_T3X4zQ3X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_NEQ, 0.0f, 0, m, &cBinop_IotFHV6K_sendMessage);
}

void Heavy_heavy::cSwitchcase_QypSnFdx_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_vUUXN57g, 0, m, &cSlice_vUUXN57g_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_xy1h15KW_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_3x7TcvvI_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_vUUXN57g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_T3X4zQ3X, 1, m, &cTabread_T3X4zQ3X_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_T3X4zQ3X, 1, m, &cTabread_T3X4zQ3X_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_EakMs1N1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_2qMLGloT_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_mmHqQlXz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_bTJl9Wns_sendMessage);
}

void Heavy_heavy::cBinop_uWTWsuiU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sZ1Lqvp7, HV_BINOP_MIN, 0, m, &cBinop_sZ1Lqvp7_sendMessage);
}

void Heavy_heavy::cCast_3x7TcvvI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_uWTWsuiU_sendMessage);
}

void Heavy_heavy::cCast_xy1h15KW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_EakMs1N1, 0, m, &cVar_EakMs1N1_sendMessage);
}

void Heavy_heavy::cBinop_sZ1Lqvp7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_T3X4zQ3X, 0, m, &cTabread_T3X4zQ3X_sendMessage);
}

void Heavy_heavy::cMsg_2qMLGloT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_mmHqQlXz_sendMessage);
}

void Heavy_heavy::cBinop_bTJl9Wns_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sZ1Lqvp7, HV_BINOP_MIN, 1, m, &cBinop_sZ1Lqvp7_sendMessage);
}

void Heavy_heavy::cIf_zsUpxNqL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_psuKmuBJ_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_KJWCYR4k_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_3xpObaMj_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Q0J1CwxC_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_NrmX0NBW_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabread_toHySpS2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 1, m, &cPack_TJQX4orj_sendMessage);
}

void Heavy_heavy::cSwitchcase_sG1s3Dfu_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_3HEzm7DN, 0, m, &cSlice_3HEzm7DN_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_RSb5IPTc_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_iR18kBYE_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_3HEzm7DN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_toHySpS2, 1, m, &cTabread_toHySpS2_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_toHySpS2, 1, m, &cTabread_toHySpS2_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_6DMKHSTz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_vLqn2cFS_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_ZRrE8zBr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_DH7yuFjw_sendMessage);
}

void Heavy_heavy::cBinop_FIJeBcMn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LbYsHzYe, HV_BINOP_MIN, 0, m, &cBinop_LbYsHzYe_sendMessage);
}

void Heavy_heavy::cCast_iR18kBYE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_FIJeBcMn_sendMessage);
}

void Heavy_heavy::cCast_RSb5IPTc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_6DMKHSTz, 0, m, &cVar_6DMKHSTz_sendMessage);
}

void Heavy_heavy::cBinop_LbYsHzYe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_toHySpS2, 0, m, &cTabread_toHySpS2_sendMessage);
}

void Heavy_heavy::cMsg_vLqn2cFS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_ZRrE8zBr_sendMessage);
}

void Heavy_heavy::cBinop_DH7yuFjw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_LbYsHzYe, HV_BINOP_MIN, 1, m, &cBinop_LbYsHzYe_sendMessage);
}

void Heavy_heavy::cCast_14m5Km29_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_lfE1bXT0, 0, m, &cVar_lfE1bXT0_sendMessage);
}

void Heavy_heavy::cCast_2OoDdJID_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_sqmje2li_sendMessage(_c, 0, m);
}

void Heavy_heavy::cMsg_sqmje2li_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cSend_JKUCnrkT_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_JKUCnrkT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_4aLil5CN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_IotFHV6K_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_zsUpxNqL, 1, m, &cIf_zsUpxNqL_sendMessage);
}

void Heavy_heavy::cCast_AgvuEZ8O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_zsUpxNqL, 0, m, &cIf_zsUpxNqL_sendMessage);
}

void Heavy_heavy::cCast_o1Jg3S1A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_QypSnFdx_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cMsg_BL2gluGf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 2, m, &cPack_TJQX4orj_sendMessage);
}

void Heavy_heavy::cCast_psuKmuBJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_BL2gluGf_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_3xpObaMj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_sHOuWDZ8_sendMessage);
}

void Heavy_heavy::cCast_Q0J1CwxC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Cl2PAH7C_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_SUcFAxUI_sendMessage);
}

void Heavy_heavy::cCast_KJWCYR4k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_sG1s3Dfu_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_NrmX0NBW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_IyKk1bfw_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_Cl2PAH7C_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_5ha4R9w3, 1, m, &cTabwrite_5ha4R9w3_sendMessage);
}

void Heavy_heavy::cCast_SUcFAxUI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_MmOcN1af_sendMessage(_c, 0, m);
}

void Heavy_heavy::cMsg_MmOcN1af_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cSwitchcase_EOkuEltW_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cSend_IyKk1bfw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_4aLil5CN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cIf_rofEINGS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_F2bsGPHQ_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_j4Nq9A2T_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_wsYnEWe2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_RMjtDx5c_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_tyMwY1Fg_sendMessage);
}

void Heavy_heavy::cIf_lsmXginu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_vcS5wtB1_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_U4gAlCC6_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_C9twer07_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_lsmXginu, 1, m, &cIf_lsmXginu_sendMessage);
}

void Heavy_heavy::cVar_StbtoXCz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_Fy37uBYK_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_d8VBBWAJ, 0, m, &cIf_d8VBBWAJ_sendMessage);
}

void Heavy_heavy::cUnop_nJ5D0PNf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_C9twer07_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_lsmXginu, 0, m, &cIf_lsmXginu_sendMessage);
}

void Heavy_heavy::cUnop_4K8jHrYA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_C9twer07_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_lsmXginu, 0, m, &cIf_lsmXginu_sendMessage);
}

void Heavy_heavy::cIf_d8VBBWAJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cUnop_onMessage(_c, HV_UNOP_CEIL, m, &cUnop_4K8jHrYA_sendMessage);
      break;
    }
    case 1: {
      cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_nJ5D0PNf_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_Fy37uBYK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_d8VBBWAJ, 1, m, &cIf_d8VBBWAJ_sendMessage);
}

void Heavy_heavy::cCast_tyMwY1Fg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_rofEINGS, 0, m, &cIf_rofEINGS_sendMessage);
}

void Heavy_heavy::cCast_RMjtDx5c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MCvuEUe1, HV_BINOP_LESS_THAN, 0, m, &cBinop_MCvuEUe1_sendMessage);
}

void Heavy_heavy::cBinop_MCvuEUe1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_rofEINGS, 1, m, &cIf_rofEINGS_sendMessage);
}

void Heavy_heavy::cCast_U4gAlCC6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_VAuczMZK_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_vcS5wtB1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MCvuEUe1, HV_BINOP_LESS_THAN, 1, m, &cBinop_MCvuEUe1_sendMessage);
}

void Heavy_heavy::cBinop_EpLQVEpP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_wsYnEWe2, 0, m, &cVar_wsYnEWe2_sendMessage);
}

void Heavy_heavy::cMsg_VAuczMZK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cVar_onMessage(_c, &Context(_c)->cVar_wsYnEWe2, 0, m, &cVar_wsYnEWe2_sendMessage);
}

void Heavy_heavy::cCast_j4Nq9A2T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_EpLQVEpP_sendMessage);
}

void Heavy_heavy::cCast_F2bsGPHQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ocmr8zkj, 1, m, &cTabwrite_ocmr8zkj_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_EWcFblCF, 1, m, &cTabwrite_EWcFblCF_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_x80sCxdZ, 1, m, &cTabwrite_x80sCxdZ_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_rRjWjGAU_sendMessage);
}

void Heavy_heavy::cVar_ZTNXKqiz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_StbtoXCz, 0, m, &cVar_StbtoXCz_sendMessage);
}

void Heavy_heavy::cTabwrite_x80sCxdZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_DyDlU7h8_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_KYp2EHzg, 0, m, &cSlice_KYp2EHzg_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_x80sCxdZ, 0, m, &cTabwrite_x80sCxdZ_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_KYp2EHzg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_x80sCxdZ, 2, m, &cTabwrite_x80sCxdZ_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_x80sCxdZ, 2, m, &cTabwrite_x80sCxdZ_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_EWcFblCF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_nmiTedx1_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_QsRX1GMp, 0, m, &cSlice_QsRX1GMp_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_EWcFblCF, 0, m, &cTabwrite_EWcFblCF_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_QsRX1GMp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_EWcFblCF, 2, m, &cTabwrite_EWcFblCF_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_EWcFblCF, 2, m, &cTabwrite_EWcFblCF_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_ocmr8zkj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_UFXLhHX3_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_5LVocSCT, 0, m, &cSlice_5LVocSCT_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ocmr8zkj, 0, m, &cTabwrite_ocmr8zkj_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_5LVocSCT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ocmr8zkj, 2, m, &cTabwrite_ocmr8zkj_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ocmr8zkj, 2, m, &cTabwrite_ocmr8zkj_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cMsg_QJ0urWO9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cSwitchcase_UFXLhHX3_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_nmiTedx1_onMessage(_c, NULL, 0, m, NULL);
  cSwitchcase_DyDlU7h8_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_QlIbBYU4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8HIfvM4J_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_QhUYEeci_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_ZTNXKqiz, 0, m, &cVar_ZTNXKqiz_sendMessage);
}

void Heavy_heavy::cMsg_8HIfvM4J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cSend_PUpPzIRn_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_PUpPzIRn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_4aLil5CN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_rRjWjGAU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_QJ0urWO9_sendMessage(_c, 0, m);
}

void Heavy_heavy::cIf_77tRegsX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_enaD7IPW_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_UqZn3pJd_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_1Bhe3TOc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_eup5P3K0_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_G0WK6Jam_sendMessage);
}

void Heavy_heavy::cIf_mtlpoUrc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_a2XJPQhF_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_VvEHBalu_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_0XQN0rpy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_mtlpoUrc, 1, m, &cIf_mtlpoUrc_sendMessage);
}

void Heavy_heavy::cVar_WImFdUkq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN, 0.0f, 0, m, &cBinop_pGZrd8Zx_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_Drzo6Nuu, 0, m, &cIf_Drzo6Nuu_sendMessage);
}

void Heavy_heavy::cUnop_BhiRwUcG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_0XQN0rpy_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_mtlpoUrc, 0, m, &cIf_mtlpoUrc_sendMessage);
}

void Heavy_heavy::cUnop_pYNtFLWF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_GREATER_THAN_EQL, 1.0f, 0, m, &cBinop_0XQN0rpy_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_mtlpoUrc, 0, m, &cIf_mtlpoUrc_sendMessage);
}

void Heavy_heavy::cIf_Drzo6Nuu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cUnop_onMessage(_c, HV_UNOP_CEIL, m, &cUnop_pYNtFLWF_sendMessage);
      break;
    }
    case 1: {
      cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_BhiRwUcG_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_pGZrd8Zx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_Drzo6Nuu, 1, m, &cIf_Drzo6Nuu_sendMessage);
}

void Heavy_heavy::cCast_G0WK6Jam_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_77tRegsX, 0, m, &cIf_77tRegsX_sendMessage);
}

void Heavy_heavy::cCast_eup5P3K0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vYIZBe6r, HV_BINOP_LESS_THAN, 0, m, &cBinop_vYIZBe6r_sendMessage);
}

void Heavy_heavy::cBinop_vYIZBe6r_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_77tRegsX, 1, m, &cIf_77tRegsX_sendMessage);
}

void Heavy_heavy::cCast_a2XJPQhF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vYIZBe6r, HV_BINOP_LESS_THAN, 1, m, &cBinop_vYIZBe6r_sendMessage);
}

void Heavy_heavy::cCast_VvEHBalu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_JiFdjP0F_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_iR6jHDI0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_1Bhe3TOc, 0, m, &cVar_1Bhe3TOc_sendMessage);
}

void Heavy_heavy::cMsg_JiFdjP0F_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cVar_onMessage(_c, &Context(_c)->cVar_1Bhe3TOc, 0, m, &cVar_1Bhe3TOc_sendMessage);
}

void Heavy_heavy::cCast_enaD7IPW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_X6QIrq3V_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_NuID23DF_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_rSbx7RvU_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_NbSRgNTr_sendMessage);
}

void Heavy_heavy::cCast_UqZn3pJd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_iR6jHDI0_sendMessage);
}

void Heavy_heavy::cVar_0WTwHPtk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_WImFdUkq, 0, m, &cVar_WImFdUkq_sendMessage);
}

void Heavy_heavy::cSwitchcase_jKWYeDyQ_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3F800000: { // "1.0"
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_bxepMtAa_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cCast_bxepMtAa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_wXZgdhOs_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_SnRkkFne_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_m2zGmVL4_sendMessage);
}

void Heavy_heavy::cVar_55mXIbq2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_GkfEYHAN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cIf_3TOb1uKQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cSwitchcase_3ukHbjFz_onMessage(_c, NULL, 0, m, NULL);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_OcPAbRWJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_cuXZWrVN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSwitchcase_3ukHbjFz_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3F800000: { // "1.0"
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_irMuGnhF_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cCast_irMuGnhF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_Ktx1UwMY_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_JCV0sq13_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_8ZHH97qW_sendMessage);
}

void Heavy_heavy::cVar_Q6aZh52O_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6sdTfHI1, HV_BINOP_LESS_THAN, 1, m, &cBinop_6sdTfHI1_sendMessage);
}

void Heavy_heavy::cVar_P7yRE9X1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_o0AcrWwr, HV_BINOP_LESS_THAN, 1, m, &cBinop_o0AcrWwr_sendMessage);
}

void Heavy_heavy::cIf_JR5OZ7JN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_Hz9hxnX4, 0, m, &cSlice_Hz9hxnX4_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_bksTHKY0, 0, m, &cSlice_bksTHKY0_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ZGcTLoAh_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_RLNDlChm_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_1LZBK8IF_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cIf_9LO5xinN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_x019m1QZ_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_iWedTBib, 0, m, &cSlice_iWedTBib_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_I9kRTuu9, 0, m, &cSlice_I9kRTuu9_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_uD8kqvkp_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_uPIXesse_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_AYDWTDb1_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cPack_ZzS8vxGU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_9LO5xinN, 0, m, &cIf_9LO5xinN_sendMessage);
  cIf_onMessage(_c, &Context(_c)->cIf_JR5OZ7JN, 0, m, &cIf_JR5OZ7JN_sendMessage);
}

void Heavy_heavy::cVar_M9CxSETv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_sHOuWDZ8_sendMessage);
}

void Heavy_heavy::cSlice_Hz9hxnX4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 2, m, &cPack_TJQX4orj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_bksTHKY0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSwitchcase_LbTR7F60_onMessage(_c, NULL, 0, m, NULL);
      cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 1, m, &cPack_TJQX4orj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_7t3z8XEN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_sHOuWDZ8_sendMessage);
}

void Heavy_heavy::cIf_bhW9LEcg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cIf_onMessage(_c, &Context(_c)->cIf_9LO5xinN, 1, m, &cIf_9LO5xinN_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_AJPjnOqS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_xIRsMaq7_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cVar_dqSEucRu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_XhmLtiQL_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cTabread_AGF4tH7k_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Lcx4tE1G_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_vT79ceRr_sendMessage);
}

void Heavy_heavy::cSwitchcase_aVTRqaHF_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_Hx86SU10, 0, m, &cSlice_Hx86SU10_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_K4VaEWhB_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Fp2SjUst_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_Hx86SU10_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_AGF4tH7k, 1, m, &cTabread_AGF4tH7k_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_AGF4tH7k, 1, m, &cTabread_AGF4tH7k_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_1frNzZny_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_B4ju3Wqi_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_0EKRJb4z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_pCbzBmRb_sendMessage);
}

void Heavy_heavy::cBinop_9BACoTU9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Bp3clqRB, HV_BINOP_MIN, 0, m, &cBinop_Bp3clqRB_sendMessage);
}

void Heavy_heavy::cCast_K4VaEWhB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_1frNzZny, 0, m, &cVar_1frNzZny_sendMessage);
}

void Heavy_heavy::cCast_Fp2SjUst_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_9BACoTU9_sendMessage);
}

void Heavy_heavy::cBinop_Bp3clqRB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_AGF4tH7k, 0, m, &cTabread_AGF4tH7k_sendMessage);
}

void Heavy_heavy::cMsg_B4ju3Wqi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_0EKRJb4z_sendMessage);
}

void Heavy_heavy::cBinop_pCbzBmRb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Bp3clqRB, HV_BINOP_MIN, 1, m, &cBinop_Bp3clqRB_sendMessage);
}

void Heavy_heavy::cTabread_vfh9PzmI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_cS3POWyX_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_TfQKHJU4_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_vsH8LSMg_sendMessage);
}

void Heavy_heavy::cSwitchcase_kkPfjJKV_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_xvlRoKZS, 0, m, &cSlice_xvlRoKZS_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_hM05PVQw_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_jZIISBD7_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_xvlRoKZS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_vfh9PzmI, 1, m, &cTabread_vfh9PzmI_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_vfh9PzmI, 1, m, &cTabread_vfh9PzmI_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_fJIjyfcE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_2j8XDNSW_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_KPe7d8yD_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_GfxEDflT_sendMessage);
}

void Heavy_heavy::cBinop_nuVxWOjd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_IBygg9TF, HV_BINOP_MIN, 0, m, &cBinop_IBygg9TF_sendMessage);
}

void Heavy_heavy::cCast_jZIISBD7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_nuVxWOjd_sendMessage);
}

void Heavy_heavy::cCast_hM05PVQw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_fJIjyfcE, 0, m, &cVar_fJIjyfcE_sendMessage);
}

void Heavy_heavy::cBinop_IBygg9TF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_vfh9PzmI, 0, m, &cTabread_vfh9PzmI_sendMessage);
}

void Heavy_heavy::cMsg_2j8XDNSW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_KPe7d8yD_sendMessage);
}

void Heavy_heavy::cBinop_GfxEDflT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_IBygg9TF, HV_BINOP_MIN, 1, m, &cBinop_IBygg9TF_sendMessage);
}

void Heavy_heavy::cTabwrite_7wijqASF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_MjHQ04Yz_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_1qZKA096, 0, m, &cSlice_1qZKA096_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_7wijqASF, 0, m, &cTabwrite_7wijqASF_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_1qZKA096_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_7wijqASF, 2, m, &cTabwrite_7wijqASF_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_7wijqASF, 2, m, &cTabwrite_7wijqASF_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabread_XGlI29Zh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 1, m, &cPack_TJQX4orj_sendMessage);
}

void Heavy_heavy::cSwitchcase_xIRsMaq7_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_gsisvPEA, 0, m, &cSlice_gsisvPEA_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_A3WqDw4J_sendMessage);
      cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_h6yAFDXJ_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_gsisvPEA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_XGlI29Zh, 1, m, &cTabread_XGlI29Zh_sendMessage);
      break;
    }
    case 1: {
      cTabread_onMessage(_c, &Context(_c)->cTabread_XGlI29Zh, 1, m, &cTabread_XGlI29Zh_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_mX8MCOFF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_V9JunGzq_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSystem_OppO3oKE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 1.0f, 0, m, &cBinop_pxgIrUer_sendMessage);
}

void Heavy_heavy::cBinop_4QEsSBSh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_95vccudL, HV_BINOP_MIN, 0, m, &cBinop_95vccudL_sendMessage);
}

void Heavy_heavy::cCast_h6yAFDXJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.0f, 0, m, &cBinop_4QEsSBSh_sendMessage);
}

void Heavy_heavy::cCast_A3WqDw4J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_mX8MCOFF, 0, m, &cVar_mX8MCOFF_sendMessage);
}

void Heavy_heavy::cBinop_95vccudL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabread_onMessage(_c, &Context(_c)->cTabread_XGlI29Zh, 0, m, &cTabread_XGlI29Zh_sendMessage);
}

void Heavy_heavy::cMsg_V9JunGzq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "length");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_OppO3oKE_sendMessage);
}

void Heavy_heavy::cBinop_pxgIrUer_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_95vccudL, HV_BINOP_MIN, 1, m, &cBinop_95vccudL_sendMessage);
}

void Heavy_heavy::cTabwrite_IhUIO3Ms_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_LbTR7F60_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9rWN5kfy, 0, m, &cSlice_9rWN5kfy_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_IhUIO3Ms, 0, m, &cTabwrite_IhUIO3Ms_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_9rWN5kfy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_IhUIO3Ms, 2, m, &cTabwrite_IhUIO3Ms_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_IhUIO3Ms, 2, m, &cTabwrite_IhUIO3Ms_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_ZOR2AVCr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_wSvK99xn_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_8O1YfwGy, 0, m, &cSlice_8O1YfwGy_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZOR2AVCr, 0, m, &cTabwrite_ZOR2AVCr_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_8O1YfwGy_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZOR2AVCr, 2, m, &cTabwrite_ZOR2AVCr_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZOR2AVCr, 2, m, &cTabwrite_ZOR2AVCr_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_hlKSVjT1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_XhmLtiQL_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_nqqO47cp, 0, m, &cSlice_nqqO47cp_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_hlKSVjT1, 0, m, &cTabwrite_hlKSVjT1_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_nqqO47cp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_hlKSVjT1, 2, m, &cTabwrite_hlKSVjT1_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_hlKSVjT1, 2, m, &cTabwrite_hlKSVjT1_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cTabwrite_Hk2yO5C5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_OsjcA99I_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_oktFgqji, 0, m, &cSlice_oktFgqji_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Hk2yO5C5, 0, m, &cTabwrite_Hk2yO5C5_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_oktFgqji_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Hk2yO5C5, 2, m, &cTabwrite_Hk2yO5C5_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Hk2yO5C5, 2, m, &cTabwrite_Hk2yO5C5_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_JJw45i5G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_OsjcA99I_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cTabwrite_Q1KwYqUC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cSwitchcase_aDyqVxh7_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_b4w7BMcB, 0, m, &cSlice_b4w7BMcB_sendMessage);
      break;
    }
    default: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Q1KwYqUC, 0, m, &cTabwrite_Q1KwYqUC_sendMessage);
      break;
    }
  }
}

void Heavy_heavy::cSlice_b4w7BMcB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Q1KwYqUC, 2, m, &cTabwrite_Q1KwYqUC_sendMessage);
      break;
    }
    case 1: {
      cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Q1KwYqUC, 2, m, &cTabwrite_Q1KwYqUC_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_RgNBD1un_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_PttSNo72_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_Vzv4wyvU_sendMessage);
}

void Heavy_heavy::cSlice_iWedTBib_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 2, m, &cPack_TJQX4orj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_I9kRTuu9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSwitchcase_MjHQ04Yz_onMessage(_c, NULL, 0, m, NULL);
      cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 1, m, &cPack_TJQX4orj_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_BI3jXjVr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_70yr1XcW, HV_BINOP_LOGICAL_AND, 0, m, &cBinop_70yr1XcW_sendMessage);
}

void Heavy_heavy::cBinop_VNrHEqgQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_ySeqLZO3_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_MOCvFihB_sendMessage);
}

void Heavy_heavy::cBinop_6sdTfHI1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_VNthAHsT, HV_BINOP_LOGICAL_AND, 1, m, &cBinop_VNthAHsT_sendMessage);
}

void Heavy_heavy::cCast_X6QIrq3V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_55mXIbq2, 1, m, &cVar_55mXIbq2_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_OcPAbRWJ, 1, m, &cVar_OcPAbRWJ_sendMessage);
}

void Heavy_heavy::cCast_NuID23DF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_kkPfjJKV_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_NbSRgNTr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cCast_rSbx7RvU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_aVTRqaHF_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cSend_GkfEYHAN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_zHAWhVTd_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_Lcx4tE1G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_VNrHEqgQ, HV_BINOP_LOGICAL_AND, 0, m, &cBinop_VNrHEqgQ_sendMessage);
}

void Heavy_heavy::cCast_vT79ceRr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_PoLF2K2g_sendMessage);
}

void Heavy_heavy::cBinop_VNthAHsT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_3TOb1uKQ, 0, m, &cIf_3TOb1uKQ_sendMessage);
}

void Heavy_heavy::cBinop_PoLF2K2g_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_VNthAHsT, HV_BINOP_LOGICAL_AND, 0, m, &cBinop_VNthAHsT_sendMessage);
}

void Heavy_heavy::cCast_ySeqLZO3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_jKWYeDyQ_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_MOCvFihB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_C5lhKjtq_sendMessage);
}

void Heavy_heavy::cBinop_C5lhKjtq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_3TOb1uKQ, 1, m, &cIf_3TOb1uKQ_sendMessage);
}

void Heavy_heavy::cSend_cuXZWrVN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_HWuvdBrx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_fSSytMq1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_zHAWhVTd_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_li812ZFH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_HWuvdBrx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_ILfyj4pS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_RgNBD1un, 0, m, &cVar_RgNBD1un_sendMessage);
}

void Heavy_heavy::cCast_y9a739pe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_0WTwHPtk, 0, m, &cVar_0WTwHPtk_sendMessage);
}

void Heavy_heavy::cCast_4umJ7moQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ePbURnpl_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_o0AcrWwr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_VNrHEqgQ, HV_BINOP_LOGICAL_AND, 1, m, &cBinop_VNrHEqgQ_sendMessage);
}

void Heavy_heavy::cCast_cS3POWyX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Q6aZh52O, 1, m, &cVar_Q6aZh52O_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_P7yRE9X1, 1, m, &cVar_P7yRE9X1_sendMessage);
}

void Heavy_heavy::cCast_vsH8LSMg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_6sdTfHI1, HV_BINOP_LESS_THAN, 0, m, &cBinop_6sdTfHI1_sendMessage);
}

void Heavy_heavy::cCast_TfQKHJU4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_o0AcrWwr, HV_BINOP_LESS_THAN, 0, m, &cBinop_o0AcrWwr_sendMessage);
}

void Heavy_heavy::cCast_Vzv4wyvU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Q6aZh52O, 0, m, &cVar_Q6aZh52O_sendMessage);
}

void Heavy_heavy::cCast_PttSNo72_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_P7yRE9X1, 0, m, &cVar_P7yRE9X1_sendMessage);
}

void Heavy_heavy::cSend_0EMKIjmx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_EEiDDaMx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_JCV0sq13_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_VQA1iCj6_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_8ZHH97qW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_OcPAbRWJ, 0, m, &cVar_OcPAbRWJ_sendMessage);
}

void Heavy_heavy::cCast_Ktx1UwMY_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_Q6aZh52O, 0, m, &cVar_Q6aZh52O_sendMessage);
}

void Heavy_heavy::cMsg_VQA1iCj6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cSend_0EMKIjmx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cMsg_Q705rJHo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cSend_9hBAeLMk_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_9hBAeLMk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_MLgA66Lg_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_SnRkkFne_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Q705rJHo_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_wXZgdhOs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_P7yRE9X1, 0, m, &cVar_P7yRE9X1_sendMessage);
}

void Heavy_heavy::cCast_m2zGmVL4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_55mXIbq2, 0, m, &cVar_55mXIbq2_sendMessage);
}

void Heavy_heavy::cMsg_ePbURnpl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cSend_li812ZFH_sendMessage(_c, 0, m);
  cSend_fSSytMq1_sendMessage(_c, 0, m);
  cSend_WmdPX38J_sendMessage(_c, 0, m);
  cSend_s6YJNn4x_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_WmdPX38J_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_MLgA66Lg_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_s6YJNn4x_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_EEiDDaMx_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_mXKCK2zA_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_JR5OZ7JN, 1, m, &cIf_JR5OZ7JN_sendMessage);
}

void Heavy_heavy::cCast_pc1hGxBr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_nyT7f947_sendMessage);
}

void Heavy_heavy::cBinop_70yr1XcW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_bhW9LEcg, 0, m, &cIf_bhW9LEcg_sendMessage);
}

void Heavy_heavy::cBinop_nyT7f947_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_BI3jXjVr, 0, m, &cVar_BI3jXjVr_sendMessage);
}

void Heavy_heavy::cMsg_8nLkGwOV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cSwitchcase_wSvK99xn_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cMsg_jpddYd33_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  cSwitchcase_aDyqVxh7_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_heavy::cCast_nNI0tN1s_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_AJPjnOqS, 0, m, &cVar_AJPjnOqS_sendMessage);
}

void Heavy_heavy::cCast_9P0ujLIT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_7t3z8XEN, 0, m, &cVar_7t3z8XEN_sendMessage);
}

void Heavy_heavy::cCast_JWDHDoxL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_fYe8PKYw_sendMessage(_c, 0, m);
}

void Heavy_heavy::cMsg_fYe8PKYw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 2, m, &cPack_TJQX4orj_sendMessage);
}

void Heavy_heavy::cCast_1LZBK8IF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_gmEE7R1t_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ytZHE4HR_sendMessage);
}

void Heavy_heavy::cCast_ZGcTLoAh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_M9CxSETv, 0, m, &cVar_M9CxSETv_sendMessage);
}

void Heavy_heavy::cCast_RLNDlChm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_8nLkGwOV_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_ytZHE4HR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_dqSEucRu, 0, m, &cVar_dqSEucRu_sendMessage);
}

void Heavy_heavy::cCast_gmEE7R1t_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_ivoZPpVn_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSend_ivoZPpVn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_4aLil5CN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_iEru2LnE_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_i0rLgsMU_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_hxmGE1uz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_JJw45i5G, 0, m, &cVar_JJw45i5G_sendMessage);
}

void Heavy_heavy::cSend_i0rLgsMU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_4aLil5CN_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_uD8kqvkp_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_7t3z8XEN, 0, m, &cVar_7t3z8XEN_sendMessage);
}

void Heavy_heavy::cCast_AYDWTDb1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_iEru2LnE_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_hxmGE1uz_sendMessage);
}

void Heavy_heavy::cCast_uPIXesse_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_jpddYd33_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_x019m1QZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_JWDHDoxL_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_nNI0tN1s_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_9P0ujLIT_sendMessage);
}

void Heavy_heavy::cCast_SRlei78Y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_70yr1XcW, HV_BINOP_LOGICAL_AND, 1, m, &cBinop_70yr1XcW_sendMessage);
}

void Heavy_heavy::cCast_YkBRJHu5_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_BI3jXjVr, 0, m, &cVar_BI3jXjVr_sendMessage);
}

void Heavy_heavy::cSend_OG4rWioP_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_Cw1MgNhW_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_vsxpeFpk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_cqmKAcIF, 1, m, &cVar_cqmKAcIF_sendMessage);
}

void Heavy_heavy::cSend_nMKDwWtd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_p2gpFqCb_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_sHOuWDZ8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cPack_onMessage(_c, &Context(_c)->cPack_TJQX4orj, 0, m, &cPack_TJQX4orj_sendMessage);
}

void Heavy_heavy::cBinop_ZLbbcJCu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_vsxpeFpk_sendMessage);
  cSend_nMKDwWtd_sendMessage(_c, 0, m);
}

void Heavy_heavy::hTable_Vgd4DT8h_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::hTable_KZiQJ78X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::hTable_rhgWA8bS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cCast_qz9KcQJ7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_gppux2Ep_sendMessage(_c, 0, m);
}

void Heavy_heavy::cCast_aBhYrhGU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_hNOcIZKj, 0, m, &cVar_hNOcIZKj_sendMessage);
}

void Heavy_heavy::cSend_y7UDJ7gh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cReceive_twprzqWG_sendMessage(_c, 0, m);
}

void Heavy_heavy::cMsg_gppux2Ep_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 65535.0f);
  cSend_y7UDJ7gh_sendMessage(_c, 0, m);
}

void Heavy_heavy::cBinop_FQflyFGn_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_ioPR2EMv, 1, m, &cIf_ioPR2EMv_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_nWwnYraO_sendMessage);
}

void Heavy_heavy::cBinop_nWwnYraO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_WXZxIu86, 1, m, &cIf_WXZxIu86_sendMessage);
}

void Heavy_heavy::cBinop_sslm6Fbd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSend_OG4rWioP_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSlice_jipvnWUb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 127.0f, 0, m, &cBinop_bByTEKFR_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_NlyLjmJo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sVarf_onMessage(_c, &Context(_c)->sVarf_LCajUHmE, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_OWQISe4A_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 127.0f, 0, m, &cBinop_Zri0g7Cf_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_BVvicTf1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      sVarf_onMessage(_c, &Context(_c)->sVarf_wUeCy2mf, m);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSwitchcase_Rb4KjMCa_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3F800000: { // "1.0"
      cSlice_onMessage(_c, &Context(_c)->cSlice_2iY6ySgH, 0, m, &cSlice_2iY6ySgH_sendMessage);
      break;
    }
    case 0x40000000: { // "2.0"
      cSlice_onMessage(_c, &Context(_c)->cSlice_PSf9v7Tm, 0, m, &cSlice_PSf9v7Tm_sendMessage);
      break;
    }
    case 0x40400000: { // "3.0"
      cSlice_onMessage(_c, &Context(_c)->cSlice_v4kKkXLV, 0, m, &cSlice_v4kKkXLV_sendMessage);
      break;
    }
    case 0x40800000: { // "4.0"
      cSlice_onMessage(_c, &Context(_c)->cSlice_EBYvF3am, 0, m, &cSlice_EBYvF3am_sendMessage);
      break;
    }
    case 0x40A00000: { // "5.0"
      cSlice_onMessage(_c, &Context(_c)->cSlice_8r0zT5qo, 0, m, &cSlice_8r0zT5qo_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cSlice_2iY6ySgH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_Z5BFzemh, 0, m, &cSlice_Z5BFzemh_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_PRUerDkl, 0, m, &cSlice_PRUerDkl_sendMessage);
      break;
    }
    case 1: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_Z5BFzemh, 0, m, &cSlice_Z5BFzemh_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_PRUerDkl, 0, m, &cSlice_PRUerDkl_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_PSf9v7Tm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_jN3ZQFh8, 0, m, &cSlice_jN3ZQFh8_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_WAf4sr33, 0, m, &cSlice_WAf4sr33_sendMessage);
      break;
    }
    case 1: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_jN3ZQFh8, 0, m, &cSlice_jN3ZQFh8_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_WAf4sr33, 0, m, &cSlice_WAf4sr33_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_v4kKkXLV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_Q0lqo1oK, 0, m, &cSlice_Q0lqo1oK_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_5aDEkdoO, 0, m, &cSlice_5aDEkdoO_sendMessage);
      break;
    }
    case 1: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_Q0lqo1oK, 0, m, &cSlice_Q0lqo1oK_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_5aDEkdoO, 0, m, &cSlice_5aDEkdoO_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_EBYvF3am_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_jipvnWUb, 0, m, &cSlice_jipvnWUb_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_NlyLjmJo, 0, m, &cSlice_NlyLjmJo_sendMessage);
      break;
    }
    case 1: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_jipvnWUb, 0, m, &cSlice_jipvnWUb_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_NlyLjmJo, 0, m, &cSlice_NlyLjmJo_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cSlice_8r0zT5qo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_OWQISe4A, 0, m, &cSlice_OWQISe4A_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_BVvicTf1, 0, m, &cSlice_BVvicTf1_sendMessage);
      break;
    }
    case 1: {
      cSlice_onMessage(_c, &Context(_c)->cSlice_OWQISe4A, 0, m, &cSlice_OWQISe4A_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_BVvicTf1, 0, m, &cSlice_BVvicTf1_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_tXLjaUyQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_CeHS8hbC, m);
}

void Heavy_heavy::cBinop_hISwSgGW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_TamkdmTP, m);
}

void Heavy_heavy::cBinop_XiIqQ1qC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_UfOqDW1W, m);
}

void Heavy_heavy::cBinop_bByTEKFR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_D7dKXfBn, m);
}

void Heavy_heavy::cBinop_Zri0g7Cf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_acMHQEDX, m);
}

void Heavy_heavy::cReceive_xkNitfdh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_DjySdKFe, 0, m, &cVar_DjySdKFe_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_qz9KcQJ7_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_aBhYrhGU_sendMessage);
}

void Heavy_heavy::cReceive_AJORIacz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSlice_onMessage(_c, &Context(_c)->cSlice_Bx57uvw6, 0, m, &cSlice_Bx57uvw6_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_VNlq9CXj, 0, m, &cSlice_VNlq9CXj_sendMessage);
  cSlice_onMessage(_c, &Context(_c)->cSlice_E4CfZi5W, 0, m, &cSlice_E4CfZi5W_sendMessage);
}

void Heavy_heavy::cReceive_Cw1MgNhW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cIf_onMessage(_c, &Context(_c)->cIf_bhW9LEcg, 1, m, &cIf_bhW9LEcg_sendMessage);
}

void Heavy_heavy::cReceive_p2gpFqCb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_jenX1naE, 1, m, &cVar_jenX1naE_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_dqSEucRu, 1, m, &cVar_dqSEucRu_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_JJw45i5G, 1, m, &cVar_JJw45i5G_sendMessage);
}

void Heavy_heavy::cReceive_4aLil5CN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_cqmKAcIF, 0, m, &cVar_cqmKAcIF_sendMessage);
}

void Heavy_heavy::cReceive_twprzqWG_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_gVqrasLa, 1, m, &cVar_gVqrasLa_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_RgNBD1un, 1, m, &cVar_RgNBD1un_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_ZLbbcJCu, HV_BINOP_MOD_UNIPOLAR, 1, m, &cBinop_ZLbbcJCu_sendMessage);
}

void Heavy_heavy::cReceive_zHAWhVTd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_7wijqASF, 1, m, &cTabwrite_7wijqASF_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Q1KwYqUC, 1, m, &cTabwrite_Q1KwYqUC_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_Hk2yO5C5, 1, m, &cTabwrite_Hk2yO5C5_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_7t3z8XEN, 1, m, &cVar_7t3z8XEN_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_AJPjnOqS, 1, m, &cVar_AJPjnOqS_sendMessage);
}

void Heavy_heavy::cReceive_HWuvdBrx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_M9CxSETv, 1, m, &cVar_M9CxSETv_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_hlKSVjT1, 1, m, &cTabwrite_hlKSVjT1_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_IhUIO3Ms, 1, m, &cTabwrite_IhUIO3Ms_sendMessage);
  cTabwrite_onMessage(_c, &Context(_c)->cTabwrite_ZOR2AVCr, 1, m, &cTabwrite_ZOR2AVCr_sendMessage);
}

void Heavy_heavy::cReceive_EEiDDaMx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_pc1hGxBr_sendMessage);
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_mXKCK2zA_sendMessage);
}

void Heavy_heavy::cReceive_MLgA66Lg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_FLOAT, 0, m, &cCast_SRlei78Y_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_YkBRJHu5_sendMessage);
}



/*
 * Code for expr~ implementation
 * Write out the generic implementation code
 */

 // per class code

 // per object code


/*
 * Context Process Implementation
 */

int Heavy_heavy::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }

  sendBangToReceiver(0xDD21C0EB); // send to __hv_bang~ on next cycle
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6, Bf7, Bf8, Bf9, Bf10, Bf11, Bf12;

  // input and output vars
  hv_bufferf_t O0, O1;

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    

    // zero output buffers
    __hv_zero_f(VOf(O0));
    __hv_zero_f(VOf(O1));

    // process all signal functions
    __hv_varread_f(&sVarf_wUeCy2mf, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_exp_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_phasor_f(&sPhasor_VjUFBnwQ, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf4), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf0), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_acMHQEDX, VOf(Bf3));
    __hv_varread_f(&sVarf_LCajUHmE, VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_exp_f(VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf0), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_phasor_f(&sPhasor_iNWqynlv, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_abs_f(VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf4), VOf(Bf0));
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf5), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf6), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf6), VIf(Bf4), VOf(Bf4));
    __hv_fma_f(VIf(Bf0), VIf(Bf5), VIf(Bf4), VOf(Bf4));
    __hv_varread_f(&sVarf_D7dKXfBn, VOf(Bf5));
    __hv_varread_f(&sVarf_MftE0OeT, VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_exp_f(VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_phasor_f(&sPhasor_eaWKTY4m, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_abs_f(VIf(Bf6), VOf(Bf6));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf6), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf6), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf6), VOf(Bf6));
    __hv_mul_f(VIf(Bf6), VIf(Bf6), VOf(Bf0));
    __hv_mul_f(VIf(Bf6), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf7), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf8), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf8), VIf(Bf6), VOf(Bf6));
    __hv_fma_f(VIf(Bf0), VIf(Bf7), VIf(Bf6), VOf(Bf6));
    __hv_varread_f(&sVarf_UfOqDW1W, VOf(Bf7));
    __hv_varread_f(&sVarf_1yrQdxst, VOf(Bf0));
    __hv_var_k_f(VOf(Bf8), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf0), VIf(Bf8), VOf(Bf8));
    __hv_exp_f(VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf0), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf8), VIf(Bf0), VOf(Bf0));
    __hv_phasor_f(&sPhasor_QslpjdQw, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf8), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf8), VOf(Bf8));
    __hv_abs_f(VIf(Bf8), VOf(Bf8));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf8), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf8), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf8), VOf(Bf8));
    __hv_mul_f(VIf(Bf8), VIf(Bf8), VOf(Bf0));
    __hv_mul_f(VIf(Bf8), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf9), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf10), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf10), VIf(Bf8), VOf(Bf8));
    __hv_fma_f(VIf(Bf0), VIf(Bf9), VIf(Bf8), VOf(Bf8));
    __hv_varread_f(&sVarf_CeHS8hbC, VOf(Bf9));
    __hv_varread_f(&sVarf_p2wSbAQ0, VOf(Bf0));
    __hv_var_k_f(VOf(Bf10), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_exp_f(VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf0), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf10), VIf(Bf0), VOf(Bf0));
    __hv_phasor_f(&sPhasor_31boaDNv, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf10), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_abs_f(VIf(Bf10), VOf(Bf10));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf10), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf10), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf10), VOf(Bf10));
    __hv_mul_f(VIf(Bf10), VIf(Bf10), VOf(Bf0));
    __hv_mul_f(VIf(Bf10), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf11), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf12), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf12), VIf(Bf10), VOf(Bf10));
    __hv_fma_f(VIf(Bf0), VIf(Bf11), VIf(Bf10), VOf(Bf10));
    __hv_varread_f(&sVarf_TamkdmTP, VOf(Bf11));
    __hv_mul_f(VIf(Bf10), VIf(Bf11), VOf(Bf11));
    __hv_fma_f(VIf(Bf8), VIf(Bf9), VIf(Bf11), VOf(Bf11));
    __hv_fma_f(VIf(Bf6), VIf(Bf7), VIf(Bf11), VOf(Bf11));
    __hv_fma_f(VIf(Bf4), VIf(Bf5), VIf(Bf11), VOf(Bf11));
    __hv_fma_f(VIf(Bf1), VIf(Bf3), VIf(Bf11), VOf(Bf11));
    __hv_var_k_f(VOf(Bf3), 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f);
    __hv_mul_f(VIf(Bf11), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf11), 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f);
    __hv_div_f(VIf(Bf3), VIf(Bf11), VOf(Bf11));
    __hv_add_f(VIf(Bf11), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf11), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_heavy::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float **const bOut = reinterpret_cast<float **>(hv_alloca(2*sizeof(float *)));
  bOut[0] = outputBuffers+(0*n4);
  bOut[1] = outputBuffers+(1*n4);

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_heavy::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float *const bOut = reinterpret_cast<float *>(hv_alloca(2*n4*sizeof(float)));

  int n = processInline(bIn, bOut, n4);

  // interleave the heavy output into the output buffer
  #if HV_SIMD_AVX
  for (int i = 0, j = 0; j < n4; j += 8, i += 16) {
    __m256 x = _mm256_load_ps(bOut+j);    // LLLLLLLL
    __m256 y = _mm256_load_ps(bOut+n4+j); // RRRRRRRR
    __m256 a = _mm256_unpacklo_ps(x, y);  // LRLRLRLR
    __m256 b = _mm256_unpackhi_ps(x, y);  // LRLRLRLR
    _mm256_store_ps(outputBuffers+i, a);
    _mm256_store_ps(outputBuffers+8+i, b);
  }
  #elif HV_SIMD_SSE
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    __m128 x = _mm_load_ps(bOut+j);    // LLLL
    __m128 y = _mm_load_ps(bOut+n4+j); // RRRR
    __m128 a = _mm_unpacklo_ps(x, y);  // LRLR
    __m128 b = _mm_unpackhi_ps(x, y);  // LRLR
    _mm_store_ps(outputBuffers+i, a);
    _mm_store_ps(outputBuffers+4+i, b);
  }
  #elif HV_SIMD_NEON
  // https://community.arm.com/groups/processors/blog/2012/03/13/coding-for-neon--part-5-rearranging-vectors
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    float32x4_t x = vld1q_f32(bOut+j);
    float32x4_t y = vld1q_f32(bOut+n4+j);
    float32x4x2_t z = {x, y};
    vst2q_f32(outputBuffers+i, z); // interleave and store
  }
  #else // HV_SIMD_NONE
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n4; ++j) {
      outputBuffers[i+2*j] = bOut[i*n4+j];
    }
  }
  #endif

  return n;
}
