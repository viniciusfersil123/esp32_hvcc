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
#include "HvControlBinop.h"
#include "HvControlSlice.h"
#include "HvControlUnop.h"
#include "HvControlCast.h"
#include "HvMath.h"
#include "HvControlVar.h"
#include "HvSignalPhasor.h"
#include "HvControlIf.h"
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
  static void cSlice_SOEVYC4J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_ePozDDku_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_JPNU99Ly_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_FZnG5ju3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_fWUaIJt4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_pMajSp6g_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_2w3Nr3nY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_p9oOb2kO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_vh6HxoeM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_fsFVS4Ij_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_KxbPSrq0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cIf_HM40D9jT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_jtApxtaq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_dDbf0YQc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_p5mkxnDj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_e4NneDhm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_tPnFFBwE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Z4ljKsrl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_C3R2K8Hu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_rnPdZoaP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_3fwUVF8m_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_rUiRlzsY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_yFKsNlKq_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_SXCeyomp;
  ControlSlice cSlice_SOEVYC4J;
  ControlSlice cSlice_ePozDDku;
  ControlSlice cSlice_JPNU99Ly;
  ControlVar cVar_FZnG5ju3;
  ControlIf cIf_2w3Nr3nY;
  ControlBinop cBinop_p9oOb2kO;
  ControlIf cIf_vh6HxoeM;
  ControlIf cIf_fsFVS4Ij;
  ControlIf cIf_KxbPSrq0;
  ControlIf cIf_HM40D9jT;
  ControlBinop cBinop_jtApxtaq;
  ControlBinop cBinop_dDbf0YQc;
  ControlBinop cBinop_p5mkxnDj;
  ControlBinop cBinop_rnPdZoaP;
  SignalVarf sVarf_DPBTP253;
};

#endif // _HEAVY_CONTEXT_HEAVY_HPP_
