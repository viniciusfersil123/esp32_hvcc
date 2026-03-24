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
#include "HvSignalLine.h"
#include "HvSignalVar.h"
#include "HvSignalTabread.h"
#include "HvControlSystem.h"
#include "HvControlBinop.h"
#include "HvControlDelay.h"
#include "HvControlTabhead.h"
#include "HvControlCast.h"
#include "HvTable.h"
#include "HvSignalPhasor.h"
#include "HvMath.h"
#include "HvControlVar.h"
#include "HvSignalTabwrite.h"

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
  static void cVar_SQgXk2Nv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ElS31LIb_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabhead_BAcw24z8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xcM50RPM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_vhiIiOuX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_UXzd7FfT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_D05qcQAm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_lgGBmVw6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sTabread_oc43q1AL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_MXr7zmC8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_s7yXd2mO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CreDAkWx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_bHWkb1g1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_X2N8EIPf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_eWe5iO3Z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_srkRLN2D_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_sG3cdpe0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_IFp8GGI1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_KImz8mcT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_bw8nqZ3c_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_veLbT91N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_haEoXoyB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_DRhvyGCh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_kwfw3HFh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_GsYwpKyZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_5ohcHI8i_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_lKAeCsaR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_SygP0i4H_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4xnZWl4j_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nLuYsXEO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_UjLeAh7v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ZEIcEiVz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_hLkOo9HV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vEUbTVeO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_W3rwfXOr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iER0mRab_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Idw40oZw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_tChyp7rd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_ZybrP9P1_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalTabread sTabread_oc43q1AL;
  SignalLine sLine_BmM94raF;
  SignalPhasor sPhasor_bmmCDF8J;
  SignalTabwrite sTabwrite_x8ny6Wv4;
  ControlVar cVar_SQgXk2Nv;
  ControlBinop cBinop_ElS31LIb;
  ControlTabhead cTabhead_BAcw24z8;
  ControlVar cVar_UXzd7FfT;
  ControlDelay cDelay_D05qcQAm;
  ControlDelay cDelay_lgGBmVw6;
  ControlBinop cBinop_MXr7zmC8;
  ControlBinop cBinop_s7yXd2mO;
  ControlBinop cBinop_CreDAkWx;
  ControlBinop cBinop_sG3cdpe0;
  ControlBinop cBinop_KImz8mcT;
  ControlBinop cBinop_bw8nqZ3c;
  ControlDelay cDelay_kwfw3HFh;
  ControlDelay cDelay_GsYwpKyZ;
  ControlBinop cBinop_lKAeCsaR;
  HvTable hTable_SygP0i4H;
  ControlBinop cBinop_nLuYsXEO;
  ControlBinop cBinop_W3rwfXOr;
  SignalVarf sVarf_4dwx8dkF;
};

#endif // _HEAVY_CONTEXT_HEAVY_HPP_
