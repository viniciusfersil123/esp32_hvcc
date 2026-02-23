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
#include "HvControlSystem.h"
#include "HvControlSlice.h"
#include "HvSignalVar.h"
#include "HvSignalPhasor.h"
#include "HvControlCast.h"
#include "HvControlDelay.h"
#include "HvControlVar.h"
#include "HvControlBinop.h"
#include "HvTable.h"
#include "HvControlTabwrite.h"
#include "HvMath.h"
#include "HvSignalSample.h"

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
  static void cVar_VSlGEZUU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_HEYzPohx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_gmdP2szr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_fxY4ZaBG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_WHyRZkU1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_oGHOHFig_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_5K2CY6rR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_OzmLSpW0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sSample_Ys4icdD9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_ZhftB8r5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_T6cg0gk9_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_c8ypzvMO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_VUXrqi2Y_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_CwHUgiTx_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_E1G0yZJh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_OSuYMI1T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9BvvrRxS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_gk8zFISF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_UCOypETd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_lXnRpSE0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_J2qH1o8J_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0D7xNxOO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_c3pWjUNB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CWQeoyYU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6tMMTB07_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4drAPfAy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_00DgCPGS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_EZLtIU3v_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_Hqt7CUzE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_wDl3ymhg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_brei7ivE_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_srbynuYf;
  SignalSample sSample_Ys4icdD9;
  SignalPhasor sPhasor_2KN7eC6M;
  SignalPhasor sPhasor_GBLvVaZy;
  ControlVar cVar_VSlGEZUU;
  ControlBinop cBinop_HEYzPohx;
  HvTable hTable_fxY4ZaBG;
  ControlVar cVar_oGHOHFig;
  ControlVar cVar_OzmLSpW0;
  ControlTabwrite cTabwrite_ZhftB8r5;
  ControlSlice cSlice_c8ypzvMO;
  ControlVar cVar_VUXrqi2Y;
  ControlDelay cDelay_E1G0yZJh;
  ControlVar cVar_UCOypETd;
  ControlBinop cBinop_J2qH1o8J;
  ControlBinop cBinop_0D7xNxOO;
  ControlBinop cBinop_c3pWjUNB;
  ControlBinop cBinop_CWQeoyYU;
  ControlBinop cBinop_6tMMTB07;
  ControlBinop cBinop_00DgCPGS;
  ControlBinop cBinop_EZLtIU3v;
  SignalVarf sVarf_G1ufSVb3;
};

#endif // _HEAVY_CONTEXT_HEAVY_HPP_
