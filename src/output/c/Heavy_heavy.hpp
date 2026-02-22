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
#include "HvControlDelay.h"
#include "HvMath.h"
#include "HvControlBinop.h"
#include "HvControlCast.h"
#include "HvControlSlice.h"
#include "HvControlTabwrite.h"
#include "HvTable.h"
#include "HvSignalPhasor.h"
#include "HvSignalVar.h"
#include "HvControlSystem.h"
#include "HvSignalSample.h"
#include "HvControlVar.h"

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
  static void cVar_S5S1tZGJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_5WoFX23z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_u33Z1Viq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_zDoxXJsu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_gcZsvpN7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_s9RAl9e6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Tvh9gWsy_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_JCMr8AuZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sSample_dMs1hNug_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabwrite_TXQ7ineB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_zSN7OMLW_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_f7fAx007_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_H9nQ3fS5_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_2J5ktIEl_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_uMwDgk0p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ErwcuVT0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_HYrUcIaA_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_pIfyY9Ka_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_GbqoxVf6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_knfhm5I1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_DBd3IXVH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_IcNiDIQe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_a6Ud00PO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_VjZbORB6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_UccC6UWn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_wDO32NqB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_GXv9srWh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_qU86e1EQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_beDIXDGD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_8vfQIR7s_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_9Kc9UyHP_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_OGdYFvqJ;
  SignalSample sSample_dMs1hNug;
  SignalPhasor sPhasor_ob6jEBAG;
  SignalPhasor sPhasor_vNhCrcaA;
  ControlVar cVar_S5S1tZGJ;
  ControlBinop cBinop_5WoFX23z;
  HvTable hTable_zDoxXJsu;
  ControlVar cVar_s9RAl9e6;
  ControlVar cVar_JCMr8AuZ;
  ControlTabwrite cTabwrite_TXQ7ineB;
  ControlSlice cSlice_f7fAx007;
  ControlVar cVar_H9nQ3fS5;
  ControlDelay cDelay_uMwDgk0p;
  ControlVar cVar_GbqoxVf6;
  ControlBinop cBinop_DBd3IXVH;
  ControlBinop cBinop_IcNiDIQe;
  ControlBinop cBinop_a6Ud00PO;
  ControlBinop cBinop_VjZbORB6;
  ControlBinop cBinop_UccC6UWn;
  ControlBinop cBinop_GXv9srWh;
  ControlBinop cBinop_qU86e1EQ;
  SignalVarf sVarf_zpIoJGAq;
};

#endif // _HEAVY_CONTEXT_HEAVY_HPP_
