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
#include "HvControlVar.h"
#include "HvControlSlice.h"
#include "HvSignalTabread.h"
#include "HvTable.h"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlSystem.h"
#include "HvMath.h"

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
  static void hTable_Sr5mZKpr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_MhogIGuU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_bPiWlViL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_60QRhYOa_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSystem_Pt4VZsZm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZRNRiEzh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fyLCPy3p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_92JQVrhc_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_BROX6Zuj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_qX1CA3oX_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSystem_LoGbONQT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_y8mopBp7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FOuikEjZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_bc1U9sAd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_lJSu2RXq_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_dQPxSk9v;
  SignalTabread sTabread_mVPQUbZD;
  SignalTabread sTabread_9B2ohzOQ;
  SignalPhasor sPhasor_puJ8dGFD;
  SignalTabread sTabread_zLaTY53o;
  SignalTabread sTabread_NBN9x3pC;
  HvTable hTable_Sr5mZKpr;
  HvTable hTable_MhogIGuU;
  ControlVar cVar_bPiWlViL;
  ControlBinop cBinop_fyLCPy3p;
  ControlSlice cSlice_92JQVrhc;
  SignalVarf sVarf_XDWuQe2A;
  ControlVar cVar_BROX6Zuj;
  ControlBinop cBinop_FOuikEjZ;
  ControlSlice cSlice_bc1U9sAd;
  SignalVarf sVarf_Nsw3BAyy;
};

#endif // _HEAVY_CONTEXT_HEAVY_HPP_
