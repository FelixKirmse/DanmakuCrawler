Spell
(
  "Attack",
  "Physical Attack dealing 100% A.AD - 100% D.DEF Damage",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    float damage = a.GetStats().GetTotalBaseStat(AD) - d.GetStats().GetTotalBaseStat(DEF);
    d.CurrentHP() -= (damage > 0.f) ? damage : 0.f;
  },
  0.f
),
Spell
(
  "Strong Punch",
  "A low-cost physical attack that is stronger than a normal attack.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    float damage = 2.f * a.GetStats().GetTotalBaseStat(AD) - d.GetStats().GetTotalBaseStat(DEF);
    d.CurrentHP() -= (damage > 0.f) ? damage : 0.f;
  },
  20.f
),
Spell
(
  "Roundhouse Kick",
  "You unleash a potent Roundhouse Kick that causes moderate physical damage to all enemies",
  TargetInfo::All,
  [] (Character& a, Character& d, int mod)
  {
    float damage = 3.f * a.GetStats().GetTotalBaseStat(AD) - 1.5f * d.GetStats().GetTotalBaseStat(DEF);
    d.CurrentHP() -= (damage > 0.f) ? damage : 0.f;
  },
  120.f
),
Spell
(
  "Devil's Nuke",
  "Deals extreme DRK damage to one target and causes all nearby targets to receive fallout damage depending on proximity",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    // Yes many braces are not needed, I included them to make the formula more clear
    float damage = ((6.66f * aMD * (aDRK/100.f) - 2.5f* dMR) * (100.f/dDRK)) / mod;
    d.CurrentHP() -= (damage > 0.f) ? damage : 0.f;
  },
  666.f
)
