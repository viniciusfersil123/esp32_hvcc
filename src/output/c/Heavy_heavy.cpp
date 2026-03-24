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
  numBytes += sTabread_init(&sTabread_oc43q1AL, &hTable_SygP0i4H, true);
  numBytes += sLine_init(&sLine_BmM94raF);
  numBytes += sPhasor_init(&sPhasor_bmmCDF8J, sampleRate);
  numBytes += sTabwrite_init(&sTabwrite_x8ny6Wv4, &hTable_SygP0i4H);
  numBytes += cVar_init_f(&cVar_SQgXk2Nv, 1.0f);
  numBytes += cTabhead_init(&cTabhead_BAcw24z8, &hTable_SygP0i4H);
  numBytes += cVar_init_s(&cVar_UXzd7FfT, "del-teste");
  numBytes += cDelay_init(this, &cDelay_D05qcQAm, 500.0f);
  numBytes += cDelay_init(this, &cDelay_lgGBmVw6, 0.0f);
  numBytes += cBinop_init(&cBinop_MXr7zmC8, 500.0f); // __mul
  numBytes += cBinop_init(&cBinop_CreDAkWx, 0.0f); // __sub
  numBytes += cBinop_init(&cBinop_sG3cdpe0, 0.0f); // __max
  numBytes += cBinop_init(&cBinop_bw8nqZ3c, 0.0f); // __sub
  numBytes += cDelay_init(this, &cDelay_kwfw3HFh, 0.0f);
  numBytes += cDelay_init(this, &cDelay_GsYwpKyZ, 0.0f);
  numBytes += hTable_init(&hTable_SygP0i4H, 256);
  numBytes += sVarf_init(&sVarf_4dwx8dkF, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_heavy::~Heavy_heavy() {
  hTable_free(&hTable_SygP0i4H);
}

HvTable *Heavy_heavy::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0xB0952E2D: return &hTable_SygP0i4H; // del-teste
    default: return nullptr;
  }
}

void Heavy_heavy::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_ZybrP9P1_sendMessage);
      break;
    }
    case 0xFB2DC5B6: { // button1
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_tChyp7rd_sendMessage);
      break;
    }
    case 0x3A6EC41A: { // knob1
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_Idw40oZw_sendMessage);
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


void Heavy_heavy::cVar_SQgXk2Nv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_ElS31LIb_sendMessage);
  sVarf_onMessage(_c, &Context(_c)->sVarf_4dwx8dkF, m);
}

void Heavy_heavy::cBinop_ElS31LIb_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_SQgXk2Nv, 1, m, &cVar_SQgXk2Nv_sendMessage);
}

void Heavy_heavy::cTabhead_BAcw24z8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_CreDAkWx, HV_BINOP_SUBTRACT, 0, m, &cBinop_CreDAkWx_sendMessage);
}

void Heavy_heavy::cMsg_xcM50RPM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_vhiIiOuX_sendMessage);
}

void Heavy_heavy::cSystem_vhiIiOuX_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_s7yXd2mO_sendMessage);
}

void Heavy_heavy::cVar_UXzd7FfT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_X2N8EIPf_sendMessage(_c, 0, m);
}

void Heavy_heavy::cDelay_D05qcQAm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_D05qcQAm, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_lgGBmVw6, 0, m, &cDelay_lgGBmVw6_sendMessage);
  sTabread_onMessage(_c, &Context(_c)->sTabread_oc43q1AL, 0, m, &sTabread_oc43q1AL_sendMessage);
}

void Heavy_heavy::cDelay_lgGBmVw6_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_lgGBmVw6, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_oc43q1AL, 0, m, &sTabread_oc43q1AL_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_lgGBmVw6, 0, m, &cDelay_lgGBmVw6_sendMessage);
}

void Heavy_heavy::sTabread_oc43q1AL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_onMessage(_c, &Context(_c)->cBinop_bw8nqZ3c, HV_BINOP_SUBTRACT, 0, m, &cBinop_bw8nqZ3c_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cBinop_MXr7zmC8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_sG3cdpe0, HV_BINOP_MAX, 0, m, &cBinop_sG3cdpe0_sendMessage);
}

void Heavy_heavy::cBinop_s7yXd2mO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_MXr7zmC8, HV_BINOP_MULTIPLY, 0, m, &cBinop_MXr7zmC8_sendMessage);
}

void Heavy_heavy::cBinop_CreDAkWx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_eWe5iO3Z_sendMessage(_c, 0, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_oc43q1AL, 0, m, &sTabread_oc43q1AL_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_IFp8GGI1_sendMessage);
}

void Heavy_heavy::cSystem_bHWkb1g1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_bw8nqZ3c, HV_BINOP_SUBTRACT, 1, m, &cBinop_bw8nqZ3c_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_lgGBmVw6, 2, m, &cDelay_lgGBmVw6_sendMessage);
}

void Heavy_heavy::cMsg_X2N8EIPf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_bHWkb1g1_sendMessage);
}

void Heavy_heavy::cMsg_eWe5iO3Z_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_D05qcQAm, 0, m, &cDelay_D05qcQAm_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_lgGBmVw6, 0, m, &cDelay_lgGBmVw6_sendMessage);
}

void Heavy_heavy::cMsg_srkRLN2D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cBinop_onMessage(_c, &Context(_c)->cBinop_sG3cdpe0, HV_BINOP_MAX, 1, m, &cBinop_sG3cdpe0_sendMessage);
}

void Heavy_heavy::cBinop_sG3cdpe0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_CreDAkWx, HV_BINOP_SUBTRACT, 1, m, &cBinop_CreDAkWx_sendMessage);
}

void Heavy_heavy::cCast_IFp8GGI1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_D05qcQAm, 0, m, &cDelay_D05qcQAm_sendMessage);
}

void Heavy_heavy::cBinop_KImz8mcT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_D05qcQAm, 2, m, &cDelay_D05qcQAm_sendMessage);
}

void Heavy_heavy::cBinop_bw8nqZ3c_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_KImz8mcT_sendMessage);
}

void Heavy_heavy::cCast_veLbT91N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_UXzd7FfT, 0, m, &cVar_UXzd7FfT_sendMessage);
  cMsg_xcM50RPM_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_BAcw24z8, 0, m, &cTabhead_BAcw24z8_sendMessage);
}

void Heavy_heavy::cMsg_haEoXoyB_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_DRhvyGCh_sendMessage);
}

void Heavy_heavy::cSystem_DRhvyGCh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_nLuYsXEO_sendMessage);
}

void Heavy_heavy::cDelay_kwfw3HFh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_kwfw3HFh, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_GsYwpKyZ, 0, m, &cDelay_GsYwpKyZ_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kwfw3HFh, 0, m, &cDelay_kwfw3HFh_sendMessage);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_x8ny6Wv4, 1, m, NULL);
}

void Heavy_heavy::cDelay_GsYwpKyZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_GsYwpKyZ, m);
  cMsg_UjLeAh7v_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSwitchcase_5ohcHI8i_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x47BE8354: { // "clear"
      cMsg_vEUbTVeO_sendMessage(_c, 0, m);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cBinop_lKAeCsaR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_4xnZWl4j_sendMessage(_c, 0, m);
}

void Heavy_heavy::hTable_SygP0i4H_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_hLkOo9HV_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_kwfw3HFh, 2, m, &cDelay_kwfw3HFh_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ZEIcEiVz_sendMessage);
}

void Heavy_heavy::cMsg_4xnZWl4j_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "resize");
  msg_setElementToFrom(m, 1, n, 0);
  hTable_onMessage(_c, &Context(_c)->hTable_SygP0i4H, 0, m, &hTable_SygP0i4H_sendMessage);
}

void Heavy_heavy::cBinop_nLuYsXEO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 500.0f, 0, m, &cBinop_lKAeCsaR_sendMessage);
}

void Heavy_heavy::cMsg_UjLeAh7v_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "mirror");
  hTable_onMessage(_c, &Context(_c)->hTable_SygP0i4H, 0, m, &hTable_SygP0i4H_sendMessage);
}

void Heavy_heavy::cCast_ZEIcEiVz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_kwfw3HFh, 0, m, &cDelay_kwfw3HFh_sendMessage);
}

void Heavy_heavy::cMsg_hLkOo9HV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cDelay_onMessage(_c, &Context(_c)->cDelay_GsYwpKyZ, 2, m, &cDelay_GsYwpKyZ_sendMessage);
}

void Heavy_heavy::cMsg_vEUbTVeO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_x8ny6Wv4, 1, m, NULL);
}

void Heavy_heavy::cBinop_W3rwfXOr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_iER0mRab_sendMessage(_c, 0, m);
}

void Heavy_heavy::cMsg_iER0mRab_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 50.0f);
  sLine_onMessage(_c, &Context(_c)->sLine_BmM94raF, 0, m, NULL);
}

void Heavy_heavy::cReceive_Idw40oZw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 127.0f, 0, m, &cBinop_W3rwfXOr_sendMessage);
}

void Heavy_heavy::cReceive_tChyp7rd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_SQgXk2Nv, 0, m, &cVar_SQgXk2Nv_sendMessage);
}

void Heavy_heavy::cReceive_ZybrP9P1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_haEoXoyB_sendMessage(_c, 0, m);
  cMsg_srkRLN2D_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_UXzd7FfT, 0, m, &cVar_UXzd7FfT_sendMessage);
  cMsg_xcM50RPM_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_BAcw24z8, 0, m, &cTabhead_BAcw24z8_sendMessage);
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4, Bf5, Bf6;

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
    __hv_tabread_f(&sTabread_oc43q1AL, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f);
    __hv_line_f(&sLine_BmM94raF, VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f, 0.057762265046662f);
    __hv_mul_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_exp_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f, 8.175798915643707f);
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_phasor_f(&sPhasor_bmmCDF8J, VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_abs_f(VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf2), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf3), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf3), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf2), VIf(Bf3), VOf(Bf3));
    __hv_mul_f(VIf(Bf3), VIf(Bf3), VOf(Bf2));
    __hv_mul_f(VIf(Bf3), VIf(Bf2), VOf(Bf4));
    __hv_mul_f(VIf(Bf4), VIf(Bf2), VOf(Bf2));
    __hv_var_k_f(VOf(Bf5), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf6), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf4), VIf(Bf6), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf2), VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_var_k_f(VOf(Bf5), 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f);
    __hv_mul_f(VIf(Bf3), VIf(Bf5), VOf(Bf5));
    __hv_varread_f(&sVarf_4dwx8dkF, VOf(Bf3));
    __hv_mul_f(VIf(Bf5), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf0), VIf(Bf1), VIf(Bf3), VOf(Bf1));
    __hv_tabwrite_f(&sTabwrite_x8ny6Wv4, VIf(Bf1));
    __hv_add_f(VIf(Bf0), VIf(Bf3), VOf(Bf1));
    __hv_add_f(VIf(Bf1), VIf(O0), VOf(O0));
    __hv_add_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf3), VIf(O1), VOf(O1));

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
