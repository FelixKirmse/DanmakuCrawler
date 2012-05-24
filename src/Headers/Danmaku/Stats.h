#pragma once

namespace Danmaku
{
/*
 * Each stat in the struct has 5 fields.
 * Stat[0] contains the base value of a stat
 * Stat[1] - Stat[3] contain modifiers from items in the respective slot
 * Stat[4] contains temporary battle modifiers (buffs/debuffs)
 * Stat[5] contains the growth of a stat on levelup
 * Stat[6] contains the invested bonus points in a stat
 */

struct Stats
{
  // Base Stats
  float HP[6];    // Health Points
  float MP[6];    // Magic Points
  float AD[6];    // Attack Damage
  float MD[6];    // Magic Damage
  float DEF[6];   // Defense
  float MR[6];    // Magic Resist
  float EVA[6];   // Evasion Stat
  enum
  {
    Dodge,
    Block
  } EVAType;      // Type of Evasion Stat
  float SPD[6];   // Speed

  //Elemental Masteries (increase damage done, decrease damage taken)
  float FIR[6];   // Fire
  float WAT[6];   // Water
  float ICE[6];   // Ice
  float ARC[6];   // Arcane
  float WND[6];   // Wind
  float HOL[6];   // Holy
  float DRK[6];   // Dark
  float GRN[6];   // Ground
  float LGT[6];

  //Debuff Resistances
  float PSN[6];   // Poison
  float PAR[6];   // Paralyze
  float SLW[6];   // Slow
  float STD[6];   // Statdrop
  float DTH[6];   // Instant-Death
  float SIL[6];   // Silence

  float GetTotalHP();
  float GetTotalMP();
  float GetTotalAD();
  float GetTotalMD();
  float GetTotalDEF();
  float GetTotalMR();
  float GetTotalEVA();
  float GetTotalSPD();

  float GetTotalFIR();
  float GetTotalWAT();
  float GetTotalICE();
  float GetTotalARC();
  float GetTotalWND();
  float GetTotalHOL();
  float GetTotalDRK();
  float GetTotalGRN();
  float GetTotalLGT();

  float GetTotalPSN();
  float GetTotalPAR();
  float GetTotalSLW();
  float GetTotalSTD();
  float GetTotalDTH();
  float GetTotalSIL();

  void LvlUp();
};
}
