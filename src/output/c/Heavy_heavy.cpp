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
 * Table Data
 */

float hTable_Sr5mZKpr_data[259] = {-0.0896033f, 0.0f, 0.0896033f, 0.178356f, 0.265425f, 0.350007f, 0.431348f, 0.508756f, 0.58161f, 0.649372f, 0.711597f, 0.767935f, 0.818137f, 0.862053f, 0.89963f, 0.930912f, 0.956028f, 0.975187f, 0.988669f, 0.996811f, 1.0f, 0.998655f, 0.993223f, 0.984158f, 0.971919f, 0.956953f, 0.939691f, 0.920538f, 0.899867f, 0.878018f, 0.85529f, 0.831945f, 0.808204f, 0.784252f, 0.760239f, 0.736284f, 0.712477f, 0.688888f, 0.665568f, 0.642553f, 0.619872f, 0.59755f, 0.575607f, 0.554066f, 0.532953f, 0.512296f, 0.49213f, 0.472491f, 0.453419f, 0.434957f, 0.417147f, 0.400027f, 0.383632f, 0.367992f, 0.353126f, 0.339046f, 0.32575f, 0.313227f, 0.301453f, 0.290394f, 0.280002f, 0.270224f, 0.260995f, 0.252248f, 0.24391f, 0.235908f, 0.22817f, 0.220628f, 0.213219f, 0.205888f, 0.198586f, 0.191278f, 0.183936f, 0.176545f, 0.169098f, 0.1616f, 0.154063f, 0.146505f, 0.138954f, 0.131437f, 0.123987f, 0.116636f, 0.109415f, 0.102354f, 0.0954784f, 0.0888083f, 0.08236f, 0.0761442f, 0.0701659f, 0.0644253f, 0.0589178f, 0.0536354f, 0.0485669f, 0.0436994f, 0.0390194f, 0.0345135f, 0.0301695f, 0.0259776f, 0.0219306f, 0.0180245f, 0.0142591f, 0.0106377f, 0.00716724f, 0.00385775f, 0.000722025f, -0.00222511f, -0.0049675f, -0.00748845f, -0.00977153f, -0.0118014f, -0.0135644f, -0.0150493f, -0.0162479f, -0.0171551f, -0.0177693f, -0.0180928f, -0.0181312f, -0.0178936f, -0.017392f, -0.0166417f, -0.0156601f, -0.0144666f, -0.0130822f, -0.0115294f, -0.00983114f, -0.0080113f, -0.00609396f, -0.0041034f, -0.00206402f, -2.23572e-07f, 0.00206358f, 0.00410297f, 0.00609353f, 0.00801089f, 0.00983075f, 0.011529f, 0.0130819f, 0.0144663f, 0.0156599f, 0.0166416f, 0.0173919f, 0.0178935f, 0.0181312f, 0.0180929f, 0.0177695f, 0.0171552f, 0.0162481f, 0.0150496f, 0.0135647f, 0.0118018f, 0.009772f, 0.00748897f, 0.00496807f, 0.00222573f, -0.000721367f, -0.00385706f, -0.00716651f, -0.010637f, -0.0142583f, -0.0180237f, -0.0219297f, -0.0259767f, -0.0301686f, -0.0345125f, -0.0390184f, -0.0436984f, -0.0485658f, -0.0536343f, -0.0589167f, -0.0644241f, -0.0701647f, -0.0761429f, -0.0823587f, -0.0888069f, -0.0954769f, -0.102353f, -0.109414f, -0.116634f, -0.123985f, -0.131435f, -0.138952f, -0.146504f, -0.154061f, -0.161598f, -0.169097f, -0.176543f, -0.183935f, -0.191276f, -0.198584f, -0.205886f, -0.213218f, -0.220627f, -0.228169f, -0.235906f, -0.243908f, -0.252246f, -0.260993f, -0.270222f, -0.28f, -0.290392f, -0.301451f, -0.313224f, -0.325747f, -0.339043f, -0.353123f, -0.367989f, -0.383629f, -0.400023f, -0.417143f, -0.434954f, -0.453415f, -0.472486f, -0.492125f, -0.512292f, -0.532948f, -0.554062f, -0.575602f, -0.597545f, -0.619868f, -0.642548f, -0.665563f, -0.688883f, -0.712472f, -0.736279f, -0.760234f, -0.784247f, -0.808199f, -0.83194f, -0.855285f, -0.878013f, -0.899863f, -0.920533f, -0.939687f, -0.956949f, -0.971916f, -0.984156f, -0.993221f, -0.998655f, -1.0f, -0.996813f, -0.988671f, -0.975191f, -0.956033f, -0.930918f, -0.899638f, -0.862061f, -0.818147f, -0.767947f, -0.71161f, -0.649386f, -0.581625f, -0.508772f, -0.431366f, -0.350025f, -0.265443f, -0.178375f, -0.0896226f, -1.94061e-05f, 0.089584f};
float hTable_MhogIGuU_data[259] = {757.143f, 757.143f, 735.714f, 700.0f, 671.429f, 650.0f, 621.429f, 600.0f, 571.429f, 550.0f, 521.429f, 507.143f, 485.714f, 464.286f, 442.857f, 428.571f, 414.286f, 400.0f, 378.571f, 364.286f, 342.857f, 328.571f, 928.571f, 921.429f, 921.429f, 914.286f, 907.143f, 892.857f, 885.714f, 878.571f, 864.286f, 850.0f, 828.571f, 807.143f, 792.857f, 785.714f, 775.0f, 764.286f, 753.571f, 742.857f, 735.714f, 728.571f, 721.429f, 714.286f, 703.571f, 692.857f, 682.143f, 671.429f, 650.0f, 628.571f, 617.857f, 607.143f, 596.429f, 585.714f, 575.0f, 564.286f, 553.571f, 542.857f, 532.143f, 521.429f, 510.714f, 500.0f, 485.714f, 478.571f, 464.286f, 450.0f, 435.714f, 428.571f, 400.0f, 392.857f, 385.714f, 378.571f, 357.143f, 350.0f, 342.857f, 335.714f, 328.571f, 314.286f, 292.857f, 285.714f, 271.429f, 264.286f, 571.429f, 571.429f, 571.429f, 571.429f, 571.429f, 564.286f, 564.286f, 278.571f, 271.429f, 271.429f, 278.571f, 278.571f, 278.571f, 278.571f, 571.429f, 571.429f, 571.429f, 575.0f, 578.571f, 578.571f, 278.571f, 278.571f, 285.714f, 285.714f, 278.571f, 278.571f, 278.571f, 878.571f, 878.571f, 878.571f, 878.571f, 878.571f, 321.429f, 325.0f, 328.571f, 328.571f, 328.571f, 328.571f, 885.714f, 885.714f, 885.714f, 885.714f, 207.143f, 207.143f, 207.143f, 200.0f, 207.143f, 207.143f, 207.143f, 214.286f, 214.286f, 221.429f, 228.571f, 228.571f, 242.857f, 250.0f, 257.143f, 264.286f, 278.571f, 292.857f, 307.143f, 321.429f, 335.714f, 350.0f, 371.429f, 392.857f, 421.429f, 435.714f, 471.429f, 500.0f, 542.857f, 571.429f, 628.571f, 664.286f, 700.0f, 728.571f, 757.143f, 792.857f, 828.571f, 885.714f, 928.571f, 978.571f, 1000.0f, 1007.14f, 1007.14f, 1000.0f, 1000.0f, 992.857f, 985.714f, 885.714f, 914.286f, 671.429f, 671.429f, 671.429f, 671.429f, 671.429f, 671.429f, 671.429f, 671.429f, 671.429f, 671.429f, 678.571f, 635.714f, 635.714f, 678.571f, 714.286f, 714.286f, 678.571f, 635.714f, 635.714f, 635.714f, 742.857f, 742.857f, 685.714f, 685.714f, 635.714f, 621.429f, 685.714f, 792.857f, 792.857f, 678.571f, 521.429f, 521.429f, 521.429f, 864.286f, 857.143f, 857.143f, 471.429f, 471.429f, 471.429f, 471.429f, 921.429f, 921.429f, 385.714f, 385.714f, 385.714f, 964.286f, 964.286f, 964.286f, 328.571f, 328.571f, 328.571f, 328.571f, 885.714f, 885.714f, 885.714f, 685.714f, 214.286f, 214.286f, 207.143f, 207.143f, 921.429f, 921.429f, 921.429f, 921.429f, 207.143f, 207.143f, 200.0f, 200.0f, 957.143f, 957.143f, 950.0f, 214.286f, 214.286f, 207.143f, 207.143f, 957.143f, 957.143f, 950.0f, 200.0f, 207.143f, 207.143f, 942.857f, 942.857f, 942.857f, 950.0f, 950.0f};



/*
 * Class Functions
 */

Heavy_heavy::Heavy_heavy(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_init(&sPhasor_dQPxSk9v, sampleRate);
  numBytes += sTabread_init(&sTabread_mVPQUbZD, &hTable_MhogIGuU, false);
  numBytes += sTabread_init(&sTabread_9B2ohzOQ, &hTable_MhogIGuU, false);
  numBytes += sPhasor_init(&sPhasor_puJ8dGFD, sampleRate);
  numBytes += sTabread_init(&sTabread_zLaTY53o, &hTable_Sr5mZKpr, false);
  numBytes += sTabread_init(&sTabread_NBN9x3pC, &hTable_Sr5mZKpr, false);
  numBytes += hTable_initWithData(&hTable_Sr5mZKpr, 259, hTable_Sr5mZKpr_data);
  numBytes += hTable_initWithData(&hTable_MhogIGuU, 259, hTable_MhogIGuU_data);
  numBytes += cVar_init_s(&cVar_bPiWlViL, "pitch11");
  numBytes += cSlice_init(&cSlice_92JQVrhc, 1, 1);
  numBytes += sVarf_init(&sVarf_XDWuQe2A, 0.0f, 0.0f, false);
  numBytes += cVar_init_s(&cVar_BROX6Zuj, "waveform11");
  numBytes += cSlice_init(&cSlice_bc1U9sAd, 1, 1);
  numBytes += sVarf_init(&sVarf_Nsw3BAyy, 0.0f, 0.0f, false);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_heavy::~Heavy_heavy() {
  hTable_free(&hTable_Sr5mZKpr);
  hTable_free(&hTable_MhogIGuU);
}

HvTable *Heavy_heavy::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0xC3B514F8: return &hTable_Sr5mZKpr; // waveform11
    case 0xF30CEF72: return &hTable_MhogIGuU; // pitch11
    default: return nullptr;
  }
}

void Heavy_heavy::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_lJSu2RXq_sendMessage);
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


void Heavy_heavy::hTable_Sr5mZKpr_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::hTable_MhogIGuU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
}

void Heavy_heavy::cVar_bPiWlViL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ZRNRiEzh_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSwitchcase_60QRhYOa_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_92JQVrhc, 0, m, &cSlice_92JQVrhc_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cSystem_Pt4VZsZm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 2.0f, 0, m, &cBinop_fyLCPy3p_sendMessage);
}

void Heavy_heavy::cMsg_ZRNRiEzh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_Pt4VZsZm_sendMessage);
}

void Heavy_heavy::cBinop_fyLCPy3p_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_XDWuQe2A, m);
}

void Heavy_heavy::cSlice_92JQVrhc_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cVar_onMessage(_c, &Context(_c)->cVar_bPiWlViL, 0, m, &cVar_bPiWlViL_sendMessage);
      sTabread_onMessage(_c, &Context(_c)->sTabread_9B2ohzOQ, 1, m, NULL);
      sTabread_onMessage(_c, &Context(_c)->sTabread_mVPQUbZD, 1, m, NULL);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cVar_BROX6Zuj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_y8mopBp7_sendMessage(_c, 0, m);
}

void Heavy_heavy::cSwitchcase_qX1CA3oX_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x3E004DAB: { // "set"
      cSlice_onMessage(_c, &Context(_c)->cSlice_bc1U9sAd, 0, m, &cSlice_bc1U9sAd_sendMessage);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_heavy::cSystem_LoGbONQT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 2.0f, 0, m, &cBinop_FOuikEjZ_sendMessage);
}

void Heavy_heavy::cMsg_y8mopBp7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_LoGbONQT_sendMessage);
}

void Heavy_heavy::cBinop_FOuikEjZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_Nsw3BAyy, m);
}

void Heavy_heavy::cSlice_bc1U9sAd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cVar_onMessage(_c, &Context(_c)->cVar_BROX6Zuj, 0, m, &cVar_BROX6Zuj_sendMessage);
      sTabread_onMessage(_c, &Context(_c)->sTabread_NBN9x3pC, 1, m, NULL);
      sTabread_onMessage(_c, &Context(_c)->sTabread_zLaTY53o, 1, m, NULL);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_heavy::cReceive_lJSu2RXq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_bPiWlViL, 0, m, &cVar_bPiWlViL_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_BROX6Zuj, 0, m, &cVar_BROX6Zuj_sendMessage);
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
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3;
  hv_bufferi_t Bi0, Bi1;

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
    __hv_var_k_f(VOf(Bf0), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_phasor_f(&sPhasor_dQPxSk9v, VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_XDWuQe2A, VOf(Bf1));
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_floor_f(VIf(Bf1), VOf(Bf0));
    __hv_cast_fi(VIf(Bf0), VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 1, 1, 1, 1, 1, 1, 1, 1);
    __hv_add_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_tabread_if(&sTabread_mVPQUbZD, VIi(Bi1), VOf(Bf2));
    __hv_tabread_if(&sTabread_9B2ohzOQ, VIi(Bi0), VOf(Bf3));
    __hv_sub_f(VIf(Bf2), VIf(Bf3), VOf(Bf2));
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_fma_f(VIf(Bf2), VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_phasor_f(&sPhasor_puJ8dGFD, VIf(Bf3), VOf(Bf3));
    __hv_varread_f(&sVarf_Nsw3BAyy, VOf(Bf0));
    __hv_mul_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_floor_f(VIf(Bf0), VOf(Bf3));
    __hv_cast_fi(VIf(Bf3), VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 1, 1, 1, 1, 1, 1, 1, 1);
    __hv_add_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_tabread_if(&sTabread_zLaTY53o, VIi(Bi1), VOf(Bf2));
    __hv_tabread_if(&sTabread_NBN9x3pC, VIi(Bi0), VOf(Bf1));
    __hv_sub_f(VIf(Bf2), VIf(Bf1), VOf(Bf2));
    __hv_sub_f(VIf(Bf0), VIf(Bf3), VOf(Bf3));
    __hv_fma_f(VIf(Bf2), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf3), 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f);
    __hv_mul_f(VIf(Bf1), VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf3), VIf(O0), VOf(O0));
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
