#pragma once

namespace Danmaku
{
/*
 * Each stat in the struct has 7 fields.
 * Stat[0] contains the base value of a stat
 * Stat[1] - Stat[3] contain modifiers from items in the respective slot
 * Stat[4] contains temporary battle modifiers (buffs/debuffs)
 * Stat[5] contains the growth of a stat on levelup
 * Stat[6] contains the invested bonus points in a stat
 */

struct Stats
{
  // Base Stats
  float HP[7];    // Health Points
  float MP[7];    // Magic Points
  float AD[7];    // Attack Damage
  float MD[7];    // Magic Damage
  float DEF[7];   // Defense
  float MR[7];    // Magic Resist
  float EVA[7];   // Evasion Stat
  enum
  {
    Dodge,
    Block
  } EVAType;      // Type of Evasion Stat
  float SPD[7];   // Speed
  float CHA[7];   // Charisma

  //Elemental Masteries (increase damage done, decrease damage taken)
  float FIR[7];   // Fire
  float WAT[7];   // Water
  float ICE[7];   // Ice
  float ARC[7];   // Arcane
  float WND[7];   // Wind
  float HOL[7];   // Holy
  float DRK[7];   // Dark
  float GRN[7];   // Ground
  float LGT[7];   // Lightning

  //Debuff Resistances
  float PSN[7];   // Poison
  float PAR[7];   // Paralyze
  float SLW[7];   // Slow
  float STD[7];   // Statdrop
  float DTH[7];   // Instant-Death
  float SIL[7];   // Silence

  float GetTotalHP();
  float GetTotalMP();
  float GetTotalAD();
  float GetTotalMD();
  float GetTotalDEF();
  float GetTotalMR();
  float GetTotalEVA();
  float GetTotalSPD();
  float GetTotalCHA();

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
