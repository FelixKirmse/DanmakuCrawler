Spell
(
  "Attack",
  "Physical Attack dealing 100% A.AD - 100% D.DEF Damage",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    float damage = a.GetStats().GetTotalBaseStat(AD) - d.GetStats().GetTotalBaseStat(DEF);
    d.TakeDamage(damage);
  },
  0.f,
  .5f
),
Spell
(
  "Defend",
  "Aquire a defensive stance, increasing DEF & MR by 20% and recovering 20% of MP",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(DEF, 0.2f);
    as.BuffBaseStat(MR, 0.2f);
    a.UseMP(-(a.GetStats().GetTotalBaseStat(MP) * 0.2f));
  },
  0.f,
  .5f
),
Spell
(
  "Holy Orb",
  "An orb of pure holy power encased in a physical shell.\nCheap, but not very powerful.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float aAD = as.GetTotalBaseStat(AD);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (2.625f * aAD + 2.625 * aMD * (aHOL/100.f) -
                   (0.875f * dDEF + 0.875f * dMR)) * (100.f/dHOL);
    d.TakeDamage(damage);    
  },
  .20f,
  .45f
),
Spell
(
  "Radiant Light",
  "A beam of holy engery radiates from the sky onto the target.\nDeals damage depending on proximity to target.\nHas a chance to paralize.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float aAD = as.GetTotalBaseStat(AD);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = ((3.f * aAD + 3.f * aMD * (aHOL/100.f) -
                   (dDEF + dMR)) * (100.f/dHOL)) / mod;
    d.TakeDamage(damage);

    // TODO Make it apply PAR
  },
  .40f,
  .38f
),
Spell
(
  "Seal of God",
  "Tries to seal away all enemies with holy energy.",
  TargetInfo::All,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float aAD = as.GetTotalBaseStat(AD);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (4.f * aAD + 4.f * aMD * (aHOL/100.f) -
                   (dDEF + dMR)) * (100.f/dHOL);
    d.TakeDamage(damage);
  },
  .60f,
  .30f
),
Spell
(
  "Blessed Ground",
  "The ground below you becomes filled with holy energy.\nThe healing is not much, but it's the thought counts.\nYou are pretty tired after this spell.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float dHOL = ds.GetTotalMastery(HOL);

    float amount =  0.88 * aMD * (aHOL/dHOL));
    d.Heal(amount);
  },
  .72f,
  0.f
),
Spell
(
  "Barrier of Faith",
  "Holy power flows through everyone in your party, increasing DEF and MR.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(DEF, .5f);
    ds.BuffBaseStat(MR, .5f);
  },
  .88f,
  .30f
),
Spell
(
  "Magic Missile",
  "An arcane missile. Not really good for much, but cheap.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (3.6f * aMD * (aARC/100) - dMR) * (100.f/dARC);
    d.TakeDamage(damage);
  },
  .16f,
  .50f
),
Spell
(
  "Blind Knowledge",
  "Blindly shoots a thousand arcane projectiles in targets direction.\nDeals more damage to enemies further away.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = ((4f * aMD * (aARC/100) - dMR) * (100.f/dARC)) * mod;
    d.TakeDamage(damage);
  },
  .32f,
  .50f
),
Spell
(
  "Distortion Field",
  "Creates a field of arcane energy, damaging all enemies.\nSlightly ignores enemies MR.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (3.75f * aMD * (aARC/100) - 0.75f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
  },
  .56f,
  .25f
),
Spell
(
  "Ravaging Flow",
  "Fires a concentrated laser of pure arcane engery at the target.\nUses up all of your MP, making the spell stronger.\nYou are completely exhausted after using this.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);
    float& currentMP = a.CurrentMP();
    currentMP -= as.BaseStats[MP][0] * 1.5f;

    float damage = ((7.f + currentMP/1000.f) * aMD * (aARC/100.f) - 0.5f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
    currentMP = 0.f;
  },
  1.6f,
  0.f
),
Spell
(
  "Mastery of Mind",
  "You gain complete mastery over your mind, doubling your MD.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(MD, 1.f);
  },
  .72f,
  .7f
),
Spell
(
  "Demonic Strike",
  "A medium strong physical attack. It's pretty cheap, but also the only\noffense you have. Get used to it!",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);
    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 3.2 * aAD - .8f * dDEF;
    d.TakeDamage(damage);
  },
  .24f,
  .5f
),
Spell
(
  "Curse of the Han'yō",
  "Unleash your full demonic potential, vastly increasing your offensive and\ndefensive capabilities. This power comes with a price.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(AD, .7f);
    as.BuffBaseStat(MD, .7f);
    as.BuffBaseStat(DEF, .7f);
    as.BuffBaseStat(MR, .7f);

    // TODO Inflict PSN and PAR Debuff
  },
  .66f,
  .5f
),
Spell
(
  "Embrace of the Demon",
  "The targets heart is embraced by demonic energy. Deals unresistable DRK damage\nand has a chance to instantly kill the target.\nTargets under 25% health receive triple damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float damage = 5.f * aMD * (aDRK/100) *
    (d.CurrentHP / ds.GetTotalBaseStat(HP) < .25f ? 3.f : 1.f);
    if(ds.TryToApplyDebuff(DTH, 50))
      d.CurrentHP = 0.f;

    d.TakeDamage(damage);

  },
  1.5f,
  0.f
),
Spell
(
  "Tickling Needles",
  "Throw magic infused needles at your enemies. Weak but cheap.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);

    float damage = (1.875f * aAD + .625f * aMD) - (.625f * dDEF + .3125f * dMR);
    d.TakeDamage(damage);
  },
  .24f,
  .4f
),
Spell
(
  "Stabby Stab!",
  "Stab the target with a knife.\nVery ineffective against targets with high DEF.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 5.5f * aAD - 2.75f * dDEF;
    d.TakeDamage(damage);
  },
  .48f,
  .48f
),
Spell
(
  "Sharp Assault",
  "Throw magic infused knives that seek out the enemy.\nIgnores MR.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = (3.3f * aAD + .825f * aMD) - .825f * dDEF;
    d.TakeDamage(damage);
  },
  .68f,
  .25f
),
Spell
(
  "Blitzkrieg",
  "Use the moment of surprise and increase SPD of all allies by 40%.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(SPD, .4f);
  },
  1.22f,
  .0f
),
Spell
(
  "Time Bubble",
  "Create a time bubble around you that allows you to act faster.\nDoubles your SPD.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(SPD, 1f);
  },
  1.f,
  .8f
),
Spell
(
  "Extinction",
  "Meteors rain down upon your enemies.\nDeals FIR damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = (5.0625f * aMD * (aFIR/100.f) - 1.125f * dMR) * (100.f/dFIR);
    d.TakeDamage(damage);
  },
  .52f,
  .15f
),
Spell
(
  "Icicle Barrage",
  "Summon icicles to impale your enemies.\nPierces MR and deals ICE damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aICE = as.GetTotalMastery(ICE);

    float dMR = ds.GetTotalBaseStat(MR);
    float dICE = ds.GetTotalMastery(ICE);

    float damage = (2.5f * aMD * (aICE/100.f) - .5f * dMR) * (100.f/dICE);
    d.TakeDamage(damage);
  },
  .3f,
  .25f
),
Spell
(
  "Tornado",
  "Summon a tornado to blow your enemies away.\nIneffective against targets with high MR.\nDeals WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (4.5f * aMD * (aWND/100.f) - 2.25f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .3f,
  .25f
),
Spell
(
  "Fear of the Dark",
  "Darkness surrounds your enemies, driving them insane.\nDeals DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (3.24f * aMD * (aDRK/100.f) - .9f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .3f,
  .25f
),
Spell
(
  "Forbidden Spell #19",
  "Cast a spell of unknown element that pierces target's MR.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float dMR = ds.GetTotalBaseStat(MR);

    float damage = (3.24f * aMD * (aDRK/100.f) - .9f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .52f,
  .40f
),
Spell
(
  "Quick Surprise",
  "A quick strike with low recovery.\nThe enemy is unable to prepare fully for the attack.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);
    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 2.5f * aAD - .625f * dDEF;
    d.TakeDamage(damage);
  },
  .18f,
  .85f
),
Spell
(
  "Expect the Unexpected",
  "Unleash a flurry of attacks on one target.\nTargets in proximity take collateral damage.\nLargely ignores DEF.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);
    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = (3.3f * aAD - .25f * dDEF) / mod;
    d.TakeDamage(damage);
  },
  .24f,
  .65f
),
Spell
(
  "Untouchable",
  "Your concentration allows you to better react to incoming attacks.\nDoubles EVA.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(EVA, 1.f);
  },
  .24f,
  .66f
),
Spell
(
  "True Form",
  "Reveal your true form, sacrificing defense for pure offense.\nThis spell has no delay.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(SPD, 1.f);
    as.BuffBaseStat(AD, 1.f);
    as.BuffBaseStat(DEF, -.5f);
    as.BuffBaseStat(MR, -.5f);
  },
  .75f,
  .99f
),
Spell
(
  "Holy Punch",
  "Punch the enemy with a holy-infused fist. Deals physical damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aHOL = as.GetTotalMastery(HOL);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 4.5f * aAD * (aHOL/100.f) - 1.5f * dDEF;
    d.TakeDamage(damage);
  },
  .20f,
  .5f
),
Spell
(
  "Stonebreaker",
  "A harsh kick that ignores a bunch of DEF.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 4.5f * aAD - .5f * dDEF;
    d.TakeDamage(damage);
  },
  .20f,
  .5f
),
Spell
(
  "Healing Rain",
  "Summon a healing rain that provides slight healing to your party.\nHealing not affected by HOL.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);

    float healing = 1.5f * aAD + 1.5f * aMD;
    d.Heal(healing);
  },
  .44f,
  .5f
),
Spell
(
  "Cleanse",
  "Cleanses target of all status effects. Also provides slight healing.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);

    // TODO Cleanse status effects

    float healing = 1.5f * aAD + 1.5f * aMD;
    d.Heal(healing);
  },
  .10f,
  .5f
),
Spell
(
  "Breath of the Baby Ice Dragon",
  "A breath attack using both your AD & MD to slow your target.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aICE = as.GetTotalMastery(ICE);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dICE = ds.GetTotalMastery(ICE);

    float damage = (((2.53f * aAD + 2.53f * aMD) * (aICE/100.f))
                    - (.8f * dDEF + .8f * dMD)) * (100/dICE);
    d.TakeDamage(damage);
    ds.BuffBaseStat(SPD, -.5f);
  },
  .2f,
  .5f
),
Spell
(
  "Ice Prison",
  "Imprison every enemy within ice.\nCan inflict PAR.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aICE = as.GetTotalMastery(ICE);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dICE = ds.GetTotalMastery(ICE);

    float damage = 3.3f * aAD * (aICE/100) - .825f * dDEF;
    d.TakeDamage(damage);

    if(ds.TryToApplyDebuff(PAR, 35))
      ;//TODO PAR logic here
  },
  .4f,
  .4f
),
Spell
(
  "Blizzard of the Tundra Wasteland",
  "Summon a powerful blizzard which slows every enemy.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aICE = as.GetTotalMastery(ICE);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dICE = ds.GetTotalMastery(ICE);

    float damage = (((2.7f * aAD + 2.7f * aMD) * (aICE/100.f))
                    - (.675f * dDEF + .675f * dMD)) * (100/dICE);
    d.TakeDamage(damage);
    ds.BuffBaseStat(SPD, -.3f);
  },
  .52f,
  .25f
),
Spell
(
  "Frozen Blood",
  "Freeze your blood to enhance your defesive capabilities.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(DEF, .5f);
    as.BuffBaseStat(MR, .5f);
  },
  .36f,
  .5f
),
Spell
(
  "Leavecutter",
  "Send sharp leaves flying at the enemy.\nVery large MR piercing.\nDeals WND damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.375f * aMD * (aWND/100) - .15f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .2f,
  .5f
),
Spell
(
  "Raging Storm",
  "Summon a storm to harm your foes.\nIgnores a good chunk of MR.\nDeals WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.f * aMD * (aWND/100) - .45f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .38f,
  .5f
),
Spell
(
  "Blessing of the Wind God",
  "Bless the target, enhancing defensive capabilities.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(DEF, .5f);
    ds.BuffBaseStat(MR, .5f);
  },
  .12f,
  .65f
),
Spell
(
  "Second Wind",
  "Heal target with the power of the wind.\nHeal increased by your WND mastery.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float healing = 1.8f * aMD * (aWND/100);

    d.Heal(healing);
  },
  .18f,
  .50f
),
Spell
(
  "Alpha Slash",
  "A strong physical sword slash.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 4.f * aAD - dDEF;
    d.TakeDamage(damage);
  },
  .40f,
  .4f
),
Spell
(
  "Omega Slash",
  "Attempts to execute the target.\nLess effective against enemies with high DEF.\nDeals triple damage to targets below 25% HP.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = (7.5f * aAD - 1.5f * dDEF)
                    * (d.CurrentHP() / ds.GetTotalBaseStat(HP) < .25f ? 3.f : 1.f);
    d.TakeDamage(damage);
  },
  .88f,
  .1f
),
Spell
(
  "Supersonic Slash",
  "Strike faster than sound, striking all enemies with immense force.\nDeals physical WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (6.25f * aAD * (aWND/100.f) - 1.25f * dDEF) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  1.1f,
  0.f
),
Spell
(
  "Omni Slash",
  "Using dark engery, strike out at all enemies.\nIgnores a good chunk of DEF\nDeals physical DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (4.f * aAD * (aDRK/100.f) - .5f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .88f,
  .5f
),
Spell
(
  "Stun Bomb",
  "Throw a bomb at the target.\nSlightly reduces target's AD.\nDeals physical FIR damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = (5.f * aMD * (aFIR/100.f) - dDEF) * (100.f/dFIR);
    d.TakeDamage(damage);

    ds.BuffBaseStat(AD, -.18f);
  },
  .36f,
  .4f
),
Spell
(
  "Magic Sap",
  "Sap the magic energy of your enemies.\nSlighty reduces enemies MD.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dMR = ds.GetTotalBaseStat(MR);

    float damage = 4.125f * aMD - 1.375f * dMR;
    d.TakeDamage(damage);

    ds.BuffBaseStat(MD, -.18f);
  },
  .48f,
  .4f
),
Spell
(
  "Thousand Needles",
  "Wears down the enemies defense.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 4.f * aMD - 1.f * dDEF;
    d.TakeDamage(damage);

    ds.BuffBaseStat(DEF, -.25f);
  },
  .6f,
  .3f
),
Spell
(
  "Empowering Laser",
  "Cast a massive arcane laser.\nOnly effective against low-MR enemies.\nDeals ARC damage and increases your MR.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (5.f * aMD * (aARC/100.f) - 2.5f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);

    as.BuffBaseStat(MR, .25f);
  },
  .48f,
  .3f
),
Spell
(
  "Shadow Ray",
  "Focus a ray of shadow energy onto target.\nDeals DRK damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (6.625f * aMD * (aDRK/100.f) - 1.325f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .32f,
  .4f
),
Spell
(
  "Dark Fog (Enemy)",
  "Summon a fog that deals unresistable DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float damage = 2.f * aMD * (aDRK/100);
    d.TakeDamage(damage);
  },
  .40f,
  .38f
),
,
Spell
(
  "Dark Fog (Ally)",
  "Summon a fog that removes all debuffs and heals a little.\nHealing increased by DRK mastery.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float healing = .25f * aMD * (aDRK/100);
    d.Heal(healing);

    // TODO Remove all Debuffs
  },
  .36f,
  .3f
),
Spell
(
  "Deadly Venom",
  "Inject the target with a deadly venom.\nAlmost guaranteed to apply PSN.\nDeals physical DRK damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (3.f * aAD * (aDRK/100.f) - dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);

    // TODO Apply Poison(120)
  },
  .28f,
  .45f
),
Spell
(
  "Deadly Swarm",
  "A swarm of poisonous insects attacks all enemies.\nHigh chance to apply PSN.\nDeals physical DRK damage",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (2.5f * aAD * (aDRK/100.f) - dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);

    // TODO Apply Poison(90)
  },
  .5f,
  .35f
),
Spell
(
  "Bug Storm",
  "Millions of bugs storm the enemy.\nDeals physical DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (4.5f * aAD * (aDRK/100.f) - 1.125f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .66f,
  .30f
),
Spell
(
  "Beastly Smash",
  "Smash your target. Simple and easy. Relatively strong.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);


    float damage = 3.5f * aAD - dDEF;
    d.TakeDamage(damage);
  },
  .30f,
  .18f
),
Spell
(
  "Shadow Trap",
  "Entrap your target and try to inject a deadly poison into it.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 1.5f * aAD - .5f * dDEF;
    d.TakeDamage(damage);

    // TODO Apply debuffs PSN(60), PAR(30)
  },
  .32f,
  .65f
),
Spell
(
  "Summon Storm",
  "Summons a relatively weak storm to attack the enemies.\nDeals physical WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (2.5f * aAD * (aWND/100.f) - 1.25f * dDEF) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .48f,
  .40f
),
Spell
(
  "Fiery Fury Fist",
  "Strike with your flame-imbued fist.\nThe heat causes you to ignore some of the enemies DEF.\nDeals physical FIR damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aFIR = as.GetTotalMastery(FIR);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = (5.f * aAD * (aFIR/100.f) - .8f * dDEF) * (100.f/dFIR);
    d.TakeDamage(damage);
  },
  .58f,
  0.f
),
Spell
(
  "Wind Strike",
  "Strike with the power of the wind.\nDeals physical WND damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.3f * aAD * (aWND/100.f) - dDEF) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .32f,
  .65f
),
Spell
(
  "Storm Dash",
  "Quickly strike all enemies.\nDeals physical WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (2.875f * aAD * (aWND/100.f) - 1.25f * dDEF) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .50f,
  .60f
),
Spell
(
  "Sharing is caring",
  "Imbue your target with the power of the wind.\nLow delay.\nIncreases SPD.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(SPD, .5f);
  },
  .28f,
  .75f
),
Spell
(
  "Embrace of the Wind God",
  "Strike your target with an empowered Wind Strike.\nIncreases your SPD.\nDeals physical WND damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.75f * aAD * (aWND/100.f) - 1.25f * dDEF) * (100.f/dWND);
    d.TakeDamage(damage);

    as.BuffBaseStat(SPD, .3f);
  },
  .7f,
  .7f
),
