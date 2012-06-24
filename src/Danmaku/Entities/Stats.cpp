#include "Danmaku/Stats.h"

namespace Danmaku
{
// Base Stats
// General formula is (base + (base * items) + bonus) * buffs

float Stats::GetTotalHP() // not influenced by battle buffs
{
  return HP[0] + (HP[0] * (HP[1] + HP[2] + HP[3])) + (HP[6] * HP[5]);
}

float Stats::GetTotalMP() // not influenced by battle buffs
{
  return MP[0] + (MP[0] * (MP[1] + MP[2] + MP[3])) + (MP[6] * MP[5]);
}

float Stats::GetTotalAD()
{
  return (AD[0] + (AD[0] * (AD[1] + AD[2] + AD[3])) + (AD[6] * AD[5])) * AD[4];
}

float Stats::GetTotalMD()
{
  return (MD[0] + (MD[0] * (MD[1] + MD[2] + MD[3])) + (MD[6] * MD[5])) * MD[4];
}

float Stats::GetTotalDEF()
{
  return (DEF[0] + (DEF[0] * (DEF[1] + DEF[2] + DEF[3])) + (DEF[6] * DEF[5]))
      * DEF[4];
}

float Stats::GetTotalMR()
{
  return (MR[0] + (MR[0] * (MR[1] + MR[2] + MR[3])) + (MR[6] * MR[5])) * MR[4];
}

float Stats::GetTotalEVA()
{
  return (EVA[0] + (EVA[0] * (EVA[1] + EVA[2] + EVA[3])) + (EVA[6] * EVA[5]))
      * EVA[4];
}

float Stats::GetTotalSPD()
{
  return (SPD[0] + (SPD[0] * (SPD[1] + SPD[2] + SPD[3])) + (SPD[6] * SPD[5]))
      * SPD[4];
}

// Elemental Masteries
// General formular is base + items + bonus

float Stats::GetTotalFIR()
{
  return FIR[0] + FIR[1] + FIR[2] + FIR[3] + FIR[6];
}

float Stats::GetTotalWAT()
{
  return WAT[0] + WAT[1] + WAT[2] + WAT[3] + WAT[6];
}

float Stats::GetTotalICE()
{
  return ICE[0] + ICE[1] + ICE[2] + ICE[3] + ICE[6];
}

float Stats::GetTotalARC()
{
  return ARC[0] + ARC[1] + ARC[2] + ARC[3] + ARC[6];
}

float Stats::GetTotalWND()
{
  return WND[0] + WND[1] + WND[2] + WND[3] + WND[6];
}

float Stats::GetTotalHOL()
{
  return HOL[0] + HOL[1] + HOL[2] + HOL[3] + HOL[6];
}

float Stats::GetTotalDRK()
{
  return DRK[0] + DRK[1] + DRK[2] + DRK[3] + DRK[6];
}

float Stats::GetTotalGRN()
{
  return GRN[0] + GRN[1] + GRN[2] + GRN[3] + GRN[6];
}

float Stats::GetTotalLGT()
{
  return LGT[0] + LGT[1] + LGT[2] + LGT[3] + LGT[6];
}

// Debuff Resistances
// General formular is base + items

float Stats::GetTotalPSN()
{
  return PSN[0] + PSN[1] + PSN[2] + PSN[3];
}

float Stats::GetTotalPAR()
{
  return PAR[0] + PAR[1] + PAR[2] + PAR[3];
}

float Stats::GetTotalSLW()
{
  return SLW[0] + SLW[1] + SLW[2] + SLW[3];
}

float Stats::GetTotalSTD()
{
  return STD[0] + STD[1] + STD[2] + STD[3];
}

float Stats::GetTotalDTH()
{
  return DTH[0] + DTH[1] + DTH[2] + DTH[3];
}

float Stats::GetTotalSIL()
{
  return SIL[0] + SIL[1] + SIL[2] + SIL[3];
}

void Stats::LvlUp()
{
  HP[0] += HP[5];
  MP[0] += MP[5];
  AD[0] += AD[5];
  MD[0] += MD[5];
  DEF[0] += DEF[5];
  MR[0] += MR[5];
}
}
