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
  TargetInfo::Enemies,
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
  "The ground below you becomes filled with holy energy.\nThe healing is not much, but the thought counts.\nYou are pretty tired after this spell.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float dHOL = ds.GetTotalMastery(HOL);

    float amount =  0.88 * aMD * (aHOL/dHOL);
    d.Heal(amount);
  },
  .72f,
  0.f
),
Spell
(
  "Barrier of Faith",
  "Holy power flows through everyone in your party.\nIncreases DEF and MR.",
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

    float damage = ((4.f * aMD * (aARC/100) - dMR) * (100.f/dARC)) * mod;
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

    float damage = ((7.f + currentMP/100.f) * aMD * (aARC/100.f) - 0.5f * dMR) * (100.f/dARC);
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
  TargetInfo::Self,
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
  "A medium strong physical attack. It's cheap, but also the only\noffense you have. Get used to it!",
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
  "Curse of the Han'yo",
  "Unleash your full demonic potential.\nIncreases AD, MD, DEF & MR.\nInflicts PSN & PAR.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(AD, .7f);
    as.BuffBaseStat(MD, .7f);
    as.BuffBaseStat(DEF, .7f);
    as.BuffBaseStat(MR, .7f);

    if(as.TryToApplyDebuff(PSN, 2000))
    {
      a.ApplyPoison(200);
    }
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
    (d.CurrentHP() / ds.GetTotalBaseStat(HP) < .25f ? 3.f : 1.f);
    if(ds.TryToApplyDebuff(DTH, 50))
      d.CurrentHP() = 0.f;

    d.TakeDamage(damage);

  },
  1.5f,
  0.f
),
Spell
(
  "Tickling Needles",
  "Throw magic infused needles at your enemies.\nWeak but cheap.",
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
    ds.BuffBaseStat(SPD, 1.f);
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

    float damage = 5.f * aMD - .5f * dMR;
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

    d.RemoveDebuffs();

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
                    - (.8f * dDEF + .8f * dMR)) * (100/dICE);
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

    float damage = (3.3f * aAD * (aICE/100.f) - .825f * dDEF) * (100.f/dICE);
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
                    - (.675f * dDEF + .675f * dMR)) * (100/dICE);
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
  "Strike faster than sound, hits all enemies with immense force.\nDeals physical WND damage.",
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

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float damage = 2.f * aMD * (aDRK/100);
    d.TakeDamage(damage);
  },
  .40f,
  .38f
),
Spell
(
  "Dark Fog (Ally)",
  "Summon a fog that removes all debuffs and heals a little.\nHealing increased by DRK mastery.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float healing = .25f * aMD * (aDRK/100);
    d.Heal(healing);

    d.RemoveDebuffs();
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

    if(!ds.TryToApplyDebuff(PSN, 120))
      return;

    d.ApplyPoison(120);
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

    if(!ds.TryToApplyDebuff(PSN, 90))
      return;

    d.ApplyPoison(90);
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

    if(ds.TryToApplyDebuff(PSN, 60))
    {
      d.ApplyPoison(60);
    }
    if(ds.TryToApplyDebuff(PAR, 30))
    {
      d.ApplyPAR(30);
    }
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
Spell
(
  "Melting Thunder",
  "Lightning strikes your target.\nThe heat melts most of their armor.\nDeals WND damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (4.f * aMD * (aWND/100.f) - 1.f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .25f,
  .45f
),
Spell
(
  "Violent Thunderstorm",
  "Summon a violent thunderstorm to annihilate your foes.\nMelts the armor of each target hit.\nDeals WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.8f * aMD * (aWND/100.f) - .95f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .48f,
  .38f
),
Spell
(
  "Surge of Lightning",
  "Infuse your target with the power of lightning.\nIncreases AD & MD greatly.\nInflicts PAR.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(AD, .72f);
    ds.BuffBaseStat(MD, .72f);

    if(ds.TryToApplyDebuff(PAR, 300))
    {
      d.ApplyPAR(300);
    }
  },
  .4f,
  .6f
),
Spell
(
  "Hurricane",
  "Summon a hurricane to blast away your enemies.\nDeals WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (4.375f * aMD * (aWND/100.f) - .875f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .6f,
  .28f
),
Spell
(
  "Scythe of the Doomed",
  "Slash at the life source of your target.\nChance to instantly kill target.\nDeals physical damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 2.7225f * aAD - .825f * dDEF;
    if(ds.TryToApplyDebuff(DTH, 40))
      d.CurrentHP() = 0.f;
    d.TakeDamage(damage);
  },
  .32f,
  .45f
),
Spell
(
  "Freeze Them To Death!",
  "Absorb all heat from your enemies bodies.\nChance to instantly kill targets.\nDeals physical ICE damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aICE = as.GetTotalMastery(ICE);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dICE = ds.GetTotalMastery(ICE);

    float damage = (4.375f * aAD * (aICE/100.f) - .875f * dDEF) * (100.f/dICE);
    if(ds.TryToApplyDebuff(DTH, 40))
      d.CurrentHP() = 0.f;
    d.TakeDamage(damage);
  },
  .48f,
  .4f
),
Spell
(
  "Fuck Them Up!",
  "Spread a deadly disease to your enemies.\nReduces EVA, DEF, MR & SPD.\nCan also inflict PAR, PSN and DTH.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (1.25f * aAD * (aDRK/100.f) - 1.25f * dDEF) * (100.f/dDRK);
    if(ds.TryToApplyDebuff(DTH, 30))
      d.CurrentHP() = 0.f;
    d.TakeDamage(damage);

    if(ds.TryToApplyDebuff(PSN, 45))
    {
      d.ApplyPoison(45);
    }
    if(ds.TryToApplyDebuff(PAR, 30))
    {
      d.ApplyPAR(30);
    }

    ds.BuffBaseStat(EVA, -1.5f);
    ds.BuffBaseStat(DEF, -.25f);
    ds.BuffBaseStat(MR, -.25f);
    ds.BuffBaseStat(SPD, -.25f);
  },
  .6f,
  .5f
),
Spell
(
  "Omae Wa Mo Shindeiru",
  "You are already dead.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (5.f * aAD * (aDRK/100.f) - 1.f * dDEF) * (100.f/dDRK)
                    * (d.CurrentHP() / ds.GetTotalBaseStat(HP) < .5f ? 3.f : 1.f);
    if(ds.TryToApplyDebuff(DTH, 75))
      d.CurrentHP() = 0.f;
    d.TakeDamage(damage);
  },
  1.f,
  0.f
),
Spell
(
  "Glimmering Trap",
  "Trap your target with arcane energy.\nChance to inflict PAR.\nDeals physical ARC damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aARC = as.GetTotalMastery(ARC);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (5.f * aAD * (aARC/100.f) - 1.25f * dDEF) * (100.f/dARC);
    d.TakeDamage(damage);

    if(ds.TryToApplyDebuff(PAR, 80))
    {
      d.ApplyPAR(80);
    }
  },
  .3f,
  .45f
),
Spell
(
  "Tsunami",
  "Summon a powerful Tsunami.\nReduces enemies MR.\nDeals WAT damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWAT = as.GetTotalMastery(WAT);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWAT = ds.GetTotalMastery(WAT);

    float damage = (4.5f * aMD * (aWAT/100.f) - 1.125f * dMR) * (100.f/dWAT);
    d.TakeDamage(damage);

    ds.BuffBaseStat(MR, -.25f);
  },
  .65f,
  .28f
),
Spell
(
  "Jumping Jacks",
  "Throw jumping jacks at an enemy.\nDeals high physical DRK damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (7.95f * aAD * (aDRK/100.f) - 1.325f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .5f,
  .2f
),
Spell
(
  "Wave of Darkness",
  "Similar to Tsunami, but with a different element.\nReduces enemies DEF.\nDeals DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (4.5f * aMD * (aDRK/100.f) - 1.125f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);

    ds.BuffBaseStat(DEF, -.15f);
  },
  .55f,
  .28f
),
Spell
(
  "Holy Entanglement",
  "Prevent your enemies from evading.\nReduces enemies EVA.\nDeals HOL damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (3.24f * aMD * (aHOL/100.f) - .9f * dMR) * (100.f/dHOL);
    d.TakeDamage(damage);
    ds.BuffBaseStat(EVA, -.5f);
  },
  .46f,
  .35f
),
Spell
(
  "Hidden Seal #37",
  "Something unknown surges through your enemies.\nDeals damage based on proximity to target.\nUnaffected by Mastery.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dMR = ds.GetTotalBaseStat(MR);

    float damage = (4.f * aMD - dMR) / mod;
    d.TakeDamage(damage);
  },
  .66f,
  .45f
),
Spell
(
  "Divine Restoration",
  "Heal and cleanse your target of all debuffs.\nHeal affected by HOL of both caster and target.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dHOL = ds.GetTotalMastery(HOL);

    float healing = aMD * (aHOL/dHOL);
    d.Heal(healing);
    d.RemoveDebuffs();
  },
  .48f,
  .25f
),
Spell
(
  "Miracle Poke",
  "Poke an ally, increasing all their stats.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    for(int i = 0; i < 9; ++i)
      ds.BuffBaseStat((BaseStat)i, .35f);
  },
  .48f,
  .25f
),
Spell
(
  "Waterfall X84",
  "Out of nowhere, a fucking waterfall.\nDeals physical WAT damage, wait what?.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWAT = as.GetTotalMastery(WAT);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWAT = ds.GetTotalMastery(WAT);

    float damage = (5.5f * aAD * (aWAT/100.f) - 2.75f * dDEF) * (100.f/dWAT);
    d.TakeDamage(damage);
  },
  .48f,
  .4f
),
Spell
(
  "Amazing Bitchslap X11",
  "Extend your arm to bitchslap all enemies.\nDeals physical DRK damage, WTF?!",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (5.f * aAD * (aDRK/100.f) - 1.25f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .5f,
  .36f
),
Spell
(
  "Optical Camouflage X69",
  "Vanish before your foes.\nIncreases defensive stats, lolumad?",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    as.BuffBaseStat(EVA, .66f);
    as.BuffBaseStat(DEF, .5f);
    as.BuffBaseStat(MR, .5f);
    as.BuffBaseStat(SPD, .5f);
  },
  .64f,
  .36f
),
Spell
(
  "5 ExaWatts Extermination Laser X1337",
  "Oh god, what the shit is that thing?\nDon't point it in my direction, FUCK!",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 10.f * aAD - .75f * dDEF;
    d.TakeDamage(damage);
  },
  .88f,
  .0f
),
Spell
(
  "8 Headed Radiant Hydra",
  "Summon a hydra to cause chaos among your enemies.\nUseful against high MR enemies.\nDeals HOL damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (3.75f * aMD * (aHOL/100.f) - .75f * dMR) * (100.f/dHOL);
    d.TakeDamage(damage);
  },
  .6f,
  .4f
),
Spell
(
  "Mystical Dragonfly",
  "Summon a Dragonfly to attack your enemies.\nUseful against low MR enemies.\nDeals ARC damage, but doesn't use caster Mastery.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (5.25f * aMD - 1.75f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
  },
  .6f,
  .4f
),
Spell
(
  "Balance Is Key",
  "A composite attack using both AD & MD.\nLow recovery.\nDamage depends on proximity to target.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aAD = as.GetTotalBaseStat(AD);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = (3.5f * aAD + 3.5f * aMD) - (dDEF + dMR);
    d.TakeDamage(damage);
  },
  .48f,
  .7f
),
Spell
(
  "Defense of the Ancients",
  "An old and long forgotten spell.\nBuffs the defense of everyone in your Party,\nincluding characters on reserve.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();

    ds.BuffBaseStat(DEF, .2f);
    ds.BuffBaseStat(MR, .2f);

    int aliveCount = 0;
    for(auto& chara : Party::GetFrontRow())
      if(!chara.IsDead())
        ++aliveCount;

    float amount = .2f / aliveCount;
    for(auto& chara : Party::GetBackSeat())
    {
      chara.GetStats().BuffBaseStat(DEF, amount);
      chara.GetStats().BuffBaseStat(MR, amount);
    }
  },
  1.12f,
  .35f
),
Spell
(
  "Offense of the Ancients",
  "An old and long forgotten spell.\nBuffs the offense of everyone in your Party,\nincluding characters on reserve.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();

    ds.BuffBaseStat(AD, .2f);
    ds.BuffBaseStat(MD, .2f);

    int aliveCount = 0;
    for(auto& chara : Party::GetFrontRow())
      if(!chara.IsDead())
        ++aliveCount;

    float amount = .2f / aliveCount;
    for(auto& chara : Party::GetBackSeat())
    {
      chara.GetStats().BuffBaseStat(AD, amount);
      chara.GetStats().BuffBaseStat(MD, amount);
    }
  },
  1.12f,
  .35f
),
Spell
(
  "Fractured Laser Barrage",
  "Bombard your foes with sharp arcane lasers.\nLowers enemies MR.\nDeals ARC damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (3.875f * aMD * (aARC/100.f) - 1.25f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
    ds.BuffBaseStat(MR, -.35f);
  },
  .56f,
  .35f
),
Spell
(
  "Mind Storm",
  "An arcane storm spreads chaos among your enemies.\nUseful against low MR enemies.\nDeals ARC damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (4.725f * aMD * (aARC/100.f) - 1.75f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
  },
  .56f,
  .35f
),
Spell
(
  "Weakening Fire Beam",
  "Focus a fire beam on your target.\nSlightly lowers all stats of target.\nDeals FIR damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = (4.f * aMD * (aFIR/100.f) - dMR) * (100.f/dFIR);
    d.TakeDamage(damage);

    for(int i = 0; i < 8; ++i)
      ds.BuffBaseStat((BaseStat)i, -.15f);
  },
  .48f,
  .3f
),
Spell
(
  "Orb of Filth",
  "Summon an orb of filth among the enemy ranks that explodes.\nChance to inflict poison.\nDeals DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (2.f * aMD * (aDRK/100.f) - dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
    if(ds.TryToApplyDebuff(PSN, 60))
    {
      d.ApplyPoison(60);
    }
  },
  .48f,
  .3f
),
Spell
(
  "The Alchemists Secret Elixir",
  "Chug down an elixir of great power.\nIncreases all your stats.\nLow delay.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    for(int i = 0; i < 8; ++i)
      as.BuffBaseStat((BaseStat)i, .4f);
  },
  .72f,
  .84f
),
Spell
(
  "Forbidden Spell #42",
  "Noone knows why it is forbidden.\nIt doesn't seem particularly strong.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dMR = ds.GetTotalBaseStat(MR);

    float damage = 3.75f * aMD - .75f * dMR;
    d.TakeDamage(damage);
  },
  .4f,
  .4f
),
Spell
(
  "Acidic Sea",
  "A sea of acid surrounds the enemy.\nLowers enemies AD.\nDeals WAT damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWAT = as.GetTotalMastery(WAT);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWAT = ds.GetTotalMastery(WAT);

    float damage = (3.0625f * aMD * (aWAT/100.f) - .875f * dMR) * (100.f/dWAT);
    d.TakeDamage(damage);
    ds.BuffBaseStat(AD, -.18f);
  },
  .6f,
  .3f
),
Spell
(
  "Magic-Dampening Zone",
  "Summon a magic-dampening zone.\nReduces enemies MD.\nDeals ARC damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (3.0625f * aMD * (aARC/100.f) - .875f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
    ds.BuffBaseStat(MD, -.18);
  },
  .6f,
  .3f
),
Spell
(
  "Grand Healing Potion",
  "Heals target for 50% of their max. HP.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();

    d.Heal(ds.GetTotalBaseStat(HP) / 2.f);
  },
  .88f,
  .25f
),
Spell
(
  "Twisting Nether",
  "Twist space around your enemies, dealing high damage.\nLong delay.\nDeals HOL damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (6.f * aMD * (aHOL/100.f) - 1.5f * dMR) * (100.f/dHOL);
    d.TakeDamage(damage);
  },
  1.38f,
  0.f
),
Spell
(
  "Secret Technique #48",
  "An attacked that is enhanced by darkness.\nDeals physical DRK damage.",
  TargetInfo::Single,
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
  .48f,
  .3f
),
Spell
(
  "Secret Technique #64",
  "Strike out at all enemies using shadow energy.\nUseful against low DEF enemies.\nDeals physical DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (5.25f * aAD * (aDRK/100.f) - 1.75f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .64f,
  .1f
),
Spell
(
  "Secret Technique #76",
  "A vicious strike that attempts to weaken the enemy.\nChance to steal stat buffs from target.\nDeals physical ARC damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aARC = as.GetTotalMastery(ARC);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = (3.75f * aAD * (aARC/100.f) - 1.25f * dDEF) * (100.f/dARC);
    d.TakeDamage(damage);

    IntGenerator stealRoll(0, 100);
    for(int i = 0; i < 8; ++i)
    {
      float& stat = ds.BaseStats[(BaseStat)i][4];
      if(stat > 1.f && stealRoll(_rng) < 40)
      {
        as.BuffBaseStat((BaseStat)i, stat - 1.f);
        stat = 1.f;
      }
    }
  },
  .76f,
  .3f
),
Spell
(
  "Secret Technique: Stoneform",
  "Turn to stone. Increases DEF, MR & EVA.\nReduces SPD.\nInflicts PAR & SIL.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    as.BuffBaseStat(DEF, 1.f);
    as.BuffBaseStat(MR, 1.f);
    as.BuffBaseStat(EVA, 1.f);
    as.BuffBaseStat(SPD, -1.f);

    if(as.TryToApplyDebuff(PAR, 200))
    {
      a.ApplyPAR(200);
    }

    if(as.TryToApplyDebuff(SIL, 200))
    {
      a.ApplySIL(200);
    }
  },
  1.28f,
  0.f
),
Spell
(
  "Flying Phoenix",
  "Become a phoenix to strike the enemy.\nDeals FIR damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = (4.f * aMD * (aFIR/100.f) - 1.f * dMR) * (100.f/dFIR);
    d.TakeDamage(damage);
  },
  .6f,
  .4f
),
Spell
(
  "Raging Firestorm",
  "Summon a raging firestorm that engulfs all enemies.\nReduces enemies AD & MD.\nDeals both FIR & WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.375f * aMD * (aFIR + aWND/200.f) - 1.25f * dMR) * (200.f/dFIR + dWND);
    d.TakeDamage(damage);
    ds.BuffBaseStat(AD, -.12f);
    ds.BuffBaseStat(MD, -.12f);
  },
  .6f,
  .3f
),
Spell
(
  "Forbidden Spell #64",
  "Summons an explosion of unfathomable energy at target's location.\nEnemies in proximity of target also take reduced damage.\nDamage greatly increased by FIR,WND & DRK but unresistable.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);
    float aWND = as.GetTotalMastery(WND);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);

    float damage = 4.375f * aMD * ((aFIR + aWND + aDRK)/100.f) - 1.75f * dMR;
    d.TakeDamage(damage);
  },
  1.6f,
  0.f
),
Spell
(
  "Rise of the Phoenix",
  "Rise up from the ashes, healing you to full.\nVastly increases all stats.\nEffect only works if current HP < 10%, else has no effect.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    if(a.CurrentHP() / as.GetTotalBaseStat(HP) > .1f)
      return;
    a.Heal(as.GetTotalBaseStat(HP));
    for(int i = 0; i < 9; ++i)
      as.BuffBaseStat((BaseStat)i, 2.f);
  },
  0.f,
  99.f
),
Spell
(
  "Reckless Swing",
  "Strike recklessly at your foe.\nAlso damages self slightly.\nDeals phisical damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDEF = as.GetTotalBaseStat(DEF);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 4.5f * aAD - 1.125f * dDEF;
    d.TakeDamage(damage);

    float selfDamage = .16f * aAD - .2f * aDEF;
    a.TakeDamage(selfDamage);
  },
  .66f,
  .5f
),
Spell
(
  "Forbidden Technique: Rage",
  "Infuse your weapon with arcane and strike all enemies.\nDrops the wait gauge of allies by 15% for each enemy hit.\nDeals composite ARC damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = ((3.f * aAD + 3.f * aMD) * (aARC/100.f) - (.75f * dDEF + .75f * dMR))
                    * (100.f/dARC);
    d.TakeDamage(damage);

    if(Battle::AttackerIsEnemy())
      for(auto& chara : Battle::GetInstance()->GetEnemies())
        chara.TurnCounter() *= .85f;
    else
      for(auto& chara : Party::GetFrontRow())
        chara.TurnCounter() *= .85f;
  },
  1.f,
  .5f
),
Spell
(
  "Ultimate Taboo",
  "Drain energy from your allies to empower your strike.\nUses 10% of max HP per target hit from each ally.\nDeals composite FIR damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);

    float extraDamage(0.f);
    if(Battle::AttackerIsEnemy())
    {
      for(auto& chara : Battle::GetInstance()->GetEnemies())
      {
        chara.TurnCounter() = 0.f;
        float extraValue = chara.GetStats().GetTotalBaseStat(HP) * .1f;
        extraDamage += extraValue;
        chara.TakeTrueDamage(extraValue);
      }
    }
    else
    {
      for(auto& chara : Party::GetFrontRow())
      {
        chara.TurnCounter() = 0.f;
        float totalHP = chara.GetStats().GetTotalBaseStat(HP);
        float extraValue = totalHP * .1f;
        extraDamage += extraValue;
        chara.TakeTrueDamage(extraValue);
      }
    }

    float damage = ((4.5f * aAD + 4.5f * aMD) * (aFIR/100.f) - (.75f * dDEF + .75f * dMR))
                    * (100.f/dFIR) + extraDamage;
    d.TakeDamage(damage);
  },
  2.66f,
  0.f
),
Spell
(
  "Catwalk",
  "Swiftly attack your target.\nVery low delay.\nIgnores a bunch of DEF.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 1.25f * aAD - .625f * dDEF;
    d.TakeDamage(damage);
  },
  .1f,
  .9f
),
Spell
(
  "Vengeful Spirit",
  "Send out a spirit to attack your target.\nLowers DEF and can inflict PNS.\nDeals composite HOL damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = ((2.625f * aAD + 2.625f * aMD) * (aHOL/100.f) - (.875f * dDEF + .875f * dMR))
                    * (100.f/dHOL);
    d.TakeDamage(damage);
    ds.BuffBaseStat(DEF, -.5f);
    // TODO Inflict PSN
  },
  .6f,
  .32f
),
Spell
(
  "Needle Rain",
  "Needles rain down from the sky upon your enemies.\nIgnores most DEF.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 3.2f * aAD - .5f * dDEF;
    d.TakeDamage(damage);
  },
  .72f,
  .3f
),
Spell
(
  "Fire Wheel",
  "Spin around shrouded in fire and attack your enemies.\nDeals composite FIR damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = ((4.f * aAD + 4.f * aMD) * (aFIR/100.f) - (dDEF + dMR))
                    * (100.f/dFIR);
    d.TakeDamage(damage);
  },
  .84f,
  .35f
),
Spell
(
  "Penetrating Horn",
  "Ram your horn into your target.\nUseful against high DEF enemies.\nDeals physical DRK damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (2.25f * aAD * (aDRK/100.f) - .5f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .36f,
  .45f
),
Spell
(
  "Mini Black Hole",
  "Summon a mini black hole behind your enemies.\nReduces SPD.\nDeals composite WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = ((2.25f * aAD + 2.25f * aMD) * (aWND/100.f) - (.75f * dDEF + .75f * dMR))
                    * (100.f/dWND);
    d.TakeDamage(damage);
    ds.BuffBaseStat(SPD, -.4f);
  },
  .6f,
  .25f
),
Spell
(
  "Fuzzy Overhaul",
  "Cleanse target from all buffs and debuffs.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    d.RemoveDebuffs();
    ds.RemoveBuffs();
  },
  .48f,
  .5f
),
Spell
(
  "Hidden Power",
  "Heighten your combat ability for speed.\nIncreases AD & DEF, decreases SPD.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(AD, .75f);
    ds.BuffBaseStat(DEF, .75f);
    ds.BuffBaseStat(SPD, -.75f);
  },
  .8f,
  .8f
),
Spell
(
  "One At A Time",
  "Focus your attacks on one enemy.\nHigh Delay.\nDeals physical WND damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (5.f * aAD * (aWND/100.f) - .8f * dDEF) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .8f,
  .0f
),
Spell
(
  "Haunt",
  "Haunt the enemy, dealing damage and healing you.\nChance to instantly kill target.\nDeals DRK damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    if(ds.TryToApplyDebuff(DTH, 75))
      d.CurrentHP() = 0.f;

    float damage = (3.0625f * aMD * (aDRK/100.f) - .875f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
    a.Heal(damage);
  },
  .64f,
  .38f
),
Spell
(
  "Seed of Corruption",
  "Plant a seed of corruption in the target.\nThe seed explodes and damages nearby enemies.\nDeals DRK damage.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = ((3.75f * aMD * (aDRK/100.f) - .625f * dMR) * (100.f/dDRK)) / mod;
    d.TakeDamage(damage);
  },
  .64f,
  .3f
),
Spell
(
  "Ghost Nova",
  "Unleash several ghosts to haunt your enemies.\nChance to instantly kill targets.\nDeals DRK damage and heals you for 1/4th the damage done.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    if(ds.TryToApplyDebuff(DTH, 66))
      d.CurrentHP() = 0.f;

    float damage = (4.f * aMD * (aDRK/100.f) - 1.f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
    a.Heal(damage / 4.f);
  },
  .96f,
  .1f
),
Spell
(
  "Hand of Death",
  "Attempt to kill all enemies.\nHigh damage modifier.\nDeals DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    if(ds.TryToApplyDebuff(DTH, 100))
      d.CurrentHP() = 0.f;

    float damage = (9.f * aMD * (aDRK/100.f) - 1.5f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  1.88f,
  .4f
),
Spell
(
  "Anomaly",
  "Deals magic damage to all enemies.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dMR = ds.GetTotalBaseStat(MR);

    float damage = 3.0625f * aMD - .875f * dMR;
    d.TakeDamage(damage);
  },
  .64f,
  .3f
),
Spell
(
  "Blessing of the Gods",
  "Bless the target, increasing all their stats.\nAlso sets their speed bar to 100%.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();

    if(&a != &d)
      d.TurnCounter() = d.TimeToAction * 1.1f;

    for(int i = 0; i < 9; ++i)
      ds.BuffBaseStat((BaseStat)i, .25f);
  },
  1.32f,
  .5f
),
Spell
(
  "Piercing Flames",
  "Piercing hot flames attack all enemies.\nDeals unresistable FIR damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float damage = 2.5f * aMD * (aFIR/100.f);
    d.TakeDamage(damage);
  },
  .64f,
  .4f
),
Spell
(
  "Darkness Comes From Within",
  "Unleash your inner darkness onto your enemies.\nRemoves caster's debuffs.\nDeals unresistable DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    a.RemoveDebuffs();

    float damage = 3.125f * aMD * (aDRK/100.f);
    d.TakeDamage(damage);
  },
  .64f,
  .4f
),
Spell
(
  "Divine Light of the Goddess",
  "Smite your enemies with this divine attack.\nVery high delay.\nDeals unresistable HOL damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    a.RemoveDebuffs();

    float damage = 6.25f * aMD * (aHOL/100.f);
    d.TakeDamage(damage);
  },
  1.58f,
  0.f
),
Spell
(
  "Light and Shadow Intertwined",
  "Twilight surrounds your enemies.\nReduces SPD and can inflict PAR.\nDeals HOL and DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (3.75f * aMD * (aHOL + aDRK / 200.f) - 1.5f * dMR) * (200.f / dHOL + dDRK);
    d.TakeDamage(damage);

    ds.BuffBaseStat(SPD, -.15);

    if(ds.TryToApplyDebuff(PAR, 35))
    {
      d.ApplyPAR(35);
    }
  },
  .64f,
  .4f
),
Spell
(
  "Miniature Tornado",
  "Summon a mini tornado among the enemy ranks.\nEnemies near the target also take damage.\nDeals WND damage, but targets enemy DEF.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (3.75f * aMD * (aWND/100.f) - .75f * dDEF) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  .64f,
  .4f
),
Spell
(
  "Last Man Standing",
  "Unleash a spell that deals more damage if you are the last active Character.\nDeals magic damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dMR = ds.GetTotalBaseStat(MR);

    float deadCount(0.f);
    if(Battle::AttackerIsEnemy())
      for(auto& chara : Battle::GetInstance()->GetEnemies())
        if(chara.IsDead())
          ++deadCount;
    else
      for(auto& chara : Party::GetFrontRow())
        if(chara.IsDead())
          ++deadCount;


    float damage = ((6.f + deadCount) * aMD - 1.5f * dMR) * deadCount;
    d.TakeDamage(damage);
  },
  1.f,
  .5f
),
Spell
(
  "Let's speed this up",
  "Instantly fill the speed bar of your allies to 100%.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    if(&a != &d)
      a.TurnCounter() = a.TimeToAction;
  },
  2.44f,
  0.f
),
Spell
(
  "Twilight Barrier",
  "Summon a twilight barrier to aid your allies.\nIncreases DEF & MR.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(DEF, .5f);
    ds.BuffBaseStat(MR, .5f);
  },
  .88f,
  .3f
),
Spell
(
  "Scarlet Sword Slash",
  "Slash your scarlet sword at the enemy.\nUseful on high DEF enemies.\nDeals physical damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 3.5f * aAD - .4375f * dDEF;
    d.TakeDamage(damage);
  },
  .52f,
  .4f
),
Spell
(
  "Inspiring Speech",
  "Hold an incredibly inspiring speech.\nIncreases AD, MD, DEF & MR significantly.\nUses up all your MP.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    a.CurrentMP() = 0.f;
    Stats& ds = d.GetStats();
    ds.BuffBaseStat(AD, 1.f);
    ds.BuffBaseStat(MD, 1.f);
    ds.BuffBaseStat(DEF, 1.f);
    ds.BuffBaseStat(MR, 1.f);
  },
  1.88f,
  0.f
),
Spell
(
  "Night Stalker",
  "Attack all enemies with shadowy power.\nDeals physical DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (4.f * aAD * (aDRK/100.f) - 1.f * dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .88f,
  .3f
),
Spell
(
  "Explosive Fist",
  "Attack your target with an arcane-enchanted punch.\nEnemies in proximity also take damage.\nDeals composite ARC damage.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aAD = as.GetTotalBaseStat(AD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dARC = ds.GetTotalMastery(ARC);

    float damage = ((3.75f * aAD + 3.75f * aMD) * (aARC/100.f) - (1.25f * dDEF + 1.25f * dMR))
                    * (100.f/dARC);
    d.TakeDamage(damage);
  },
  .88f,
  .3f
),
Spell
(
  "Technique #10",
  "Attack all enemies with magic-enchanted attacks.\nDeals composite damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aAD = as.GetTotalBaseStat(AD);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = (3.f * aAD + 3.f * aMD)  - (1.f * dDEF + 1.f * dMR);
    d.TakeDamage(damage);
  },
  1.32f,
  .2f
),
Spell
(
  "Timestop",
  "Stop the time for your enemies.\nReduces SPD and is nearly guaranteed to inflict PAR.\nDeals minor unresistable magic damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float damage = .5f * aMD;
    d.TakeDamage(damage);

    ds.BuffBaseStat(SPD, -1.f);

    if(ds.TryToApplyDebuff(PAR, 120))
    {
      d.ApplyPAR(120);
    }
  },
  .6f,
  0.f
),
Spell
(
  "Blood for Power",
  "Hit your allies with empowering magic.\nIncreases AD, MD, MR & DEF, but halves speed bar.\nDeals minor unresistable magic damage.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float damage = .5f * aMD;
    d.TakeDamage(damage);

    ds.BuffBaseStat(AD, .75f);
    ds.BuffBaseStat(MD, .75f);
    ds.BuffBaseStat(DEF, .75f);
    ds.BuffBaseStat(MR, .75f);
    d.TurnCounter() /= 2;
  },
  1.24f,
  0.f
),
Spell
(
  "Crippling Aura",
  "Focus your aura to cripple your enemies.\nReduces AD, MD, DEF & MR of enemies.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();

    ds.BuffBaseStat(AD, -1.f);
    ds.BuffBaseStat(MD, -1.f);
    ds.BuffBaseStat(DEF, -1.f);
    ds.BuffBaseStat(MR, -1.f);
  },
  .88f,
  0.f
),
Spell
(
  "Chaos Barrier",
  "Summon a small barrier that decreases damage done\nand increases damage taken.\nReduces AD, MD, DEF & MR.\nDeals HOL damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (3.75f * aMD * (aHOL/100.f) - 1.25f * dMR) * (100.f/dHOL);
    d.TakeDamage(damage);

    ds.BuffBaseStat(AD, -.15f);
    ds.BuffBaseStat(MD, -.15f);
    ds.BuffBaseStat(DEF, -.15f);
    ds.BuffBaseStat(MR, -.15f);
  },
  .48f,
  .5f
),
Spell
(
  "Cataclysmic Barrier",
  "Summon a huge barrier that decreases damage done\nand increases damage taken.\nReduces AD, MD, DEF & MR.\nDeals HOL damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);

    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = (5.25f * aMD * (aHOL/100.f) - 1.75f * dMR) * (100.f/dHOL);
    d.TakeDamage(damage);

    ds.BuffBaseStat(AD, -.25f);
    ds.BuffBaseStat(MD, -.25f);
    ds.BuffBaseStat(DEF, -.25f);
    ds.BuffBaseStat(MR, -.25f);
  },
  1.44f,
  .15f
),
Spell
(
  "Balance Strike",
  "A strike that combines HOL and DRK, magic and physical,\nin order to achieve true balance.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aAD = as.GetTotalBaseStat(AD);
    float aMD = as.GetTotalBaseStat(MD);
    float aHOL = as.GetTotalMastery(HOL);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dMR = ds.GetTotalBaseStat(MR);
    float dHOL = ds.GetTotalMastery(HOL);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = ((3.f * aAD + 3.f * aMD) * (aDRK + aHOL/200.f) - (.75f * dDEF + .75f * dMR))
                     * (200.f/dDRK + dHOL);
    d.TakeDamage(damage);
  },
  .92f,
  .4f
),
Spell
(
  "Wind Slash",
  "Disturb the wind around your target.\nEnemies in proximity take reduced damage.\nDeals WND damage.",
  TargetInfo::Decaying,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (4.5f * aMD * (aWND/100.f) - .75f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  1.44f,
  .3f
),
Spell
(
  "True Potential",
  "Unlocks your full potential and increase all your stats.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    for(int i = 0; i < 9; ++i)
      as.BuffBaseStat((BaseStat)i, .75f);
  },
  .88f,
  0.f
),
Spell
(
  "Hellfire Flare",
  "Shoot a massive ball of hellfire at your enemies.\nHuge delay.\nDeals unresistable FIR damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float damage = 3.5f * aMD * (aFIR/100);
    d.TakeDamage(damage);
  },
  1.68f,
  0.f
),
Spell
(
  "Nuclear Meltdown",
  "Overheat yourself, sacrificing DEF & MR for MD.\nAlso deals FIR damage to all enemies.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();

    as.BuffBaseStat(MD, .35f);
    as.BuffBaseStat(MR, -.2f);
    as.BuffBaseStat(DEF, -.2f);

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    if(!Battle::AttackerIsEnemy())
    {
      for(auto& chara : Battle::GetInstance()->GetEnemies())
      {
        Stats& ds = chara.GetStats();
        float dMR = ds.GetTotalBaseStat(MR);
        float dFIR = ds.GetTotalMastery(FIR);

        float damage = (2.25f * aMD * (aFIR/100.f) - .75f * dMR) * (100.f/dFIR);
        chara.TakeDamage(damage);
      }
    }
    else
    {
      for(auto& chara : Party::GetFrontRow())
      {
        Stats& ds = chara.GetStats();
        float dMR = ds.GetTotalBaseStat(MR);
        float dFIR = ds.GetTotalMastery(FIR);

        float damage = (2.25f * aMD * (aFIR/100.f) - .75f * dMR) * (100.f/dFIR);
        chara.TakeDamage(damage);
      }
    }
  },
  .8f,
  .5f
),
Spell
(
  "Hell's Inferno",
  "An inferno from hell appears below the enemies.\nDecreases MR.\nDeals FIR damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aFIR = as.GetTotalMastery(FIR);

    float dMR = ds.GetTotalBaseStat(MR);
    float dFIR = ds.GetTotalMastery(FIR);

    float damage = (4.5f * aMD * (aFIR/100.f) - 1.5f * dMR) * (100.f/dFIR);
    d.TakeDamage(damage);
    ds.BuffBaseStat(MR, -.25f);
  },
  1.12f,
  .3f
),
Spell
(
  "Demonic Seal 61: Maru",
  "A technique that uses HOL energy to focus down a target.\nIgnores most DEF.\nDeals composite HOL damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aAD = as.GetTotalBaseStat(AD);
    float aHOL = as.GetTotalMastery(HOL);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDEF = ds.GetTotalBaseStat(DEF);
    float dHOL = ds.GetTotalMastery(HOL);

    float damage = ((1.5f * aAD + 2.25f * aMD) * (aHOL/100.f) - (.15f * dDEF + .75f * dMR))
                    * (100.f/dHOL);
    d.TakeDamage(damage);
  },
  .48f,
  .66f
),
Spell
(
  "Forbidden Spell #74",
  "Through some foul magic this spell's damage is reduced by DEF.\nTargets all enemies.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 3.5f * aMD - .875f * dDEF;
    d.TakeDamage(damage);
  },
  .96f,
  .35f
),
Spell
(
  "Frost Blast",
  "A chilling blast of frost.\nDeals ICE damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aICE = as.GetTotalMastery(ICE);

    float dMR = ds.GetTotalBaseStat(MR);
    float dICE = ds.GetTotalMastery(ICE);

    float damage = (6.25f * aMD * (aICE/100.f) - 1.25f * dMR) * (100.f/dICE);
    d.TakeDamage(damage);
  },
  .88f,
  .25f
),
Spell
(
  "Wind God Tornado",
  "Summon a powerful tornado to wreak havoc among your enemies.\nDeals WND damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aWND = as.GetTotalMastery(WND);

    float dMR = ds.GetTotalBaseStat(MR);
    float dWND = ds.GetTotalMastery(WND);

    float damage = (6.f * aMD * (aWND/100.f) - 1.5f * dMR) * (100.f/dWND);
    d.TakeDamage(damage);
  },
  1.48f,
  .2f
),
Spell
(
  "Shadow Shot",
  "Focus your energy into a shadowball.\nDeals DRK damage.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();

    float aMD = as.GetTotalBaseStat(MD);
    float aDRK = as.GetTotalMastery(DRK);

    float dMR = ds.GetTotalBaseStat(MR);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (3.0625f * aMD * (aDRK/100.f) - .875f * dMR) * (100.f/dDRK);
    d.TakeDamage(damage);
  },
  .32f,
  .66f
),
Spell
(
  "Dark Mend",
  "Dark energy fills the air.\nDeals DRK damage to enemies.\nHeals allies by 10% of their max HP.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    auto damageFunc = [] (Character& a, Character& d)
                      {
                        Stats& as = a.GetStats();
                        Stats& ds = d.GetStats();

                        float aMD = as.GetTotalBaseStat(MD);
                        float aDRK = as.GetTotalMastery(DRK);

                        float dMR = ds.GetTotalBaseStat(MR);
                        float dDRK = ds.GetTotalMastery(DRK);

                        float damage = (4.5f * aMD * (aDRK/100.f) - 1.5f * dMR) * (100.f/dDRK);
                        d.TakeDamage(damage);
                      };

    auto healFunc = [] (Character& a)
                    {
                      a.Heal(a.GetStats().GetTotalBaseStat(HP) * .1f);
                    };

    if(Battle::AttackerIsEnemy())
    {
      for(auto& chara : Battle::GetInstance()->GetEnemies())
        healFunc(chara);
      for(auto& chara : Party::GetFrontRow())
        damageFunc(a, chara);
    }
    else
    {
      for(auto& chara : Party::GetFrontRow())
        healFunc(chara);
      for(auto& chara : Battle::GetInstance()->GetEnemies())
        damageFunc(a, chara);
    }
  },
  1.44f,
  .1f
),
Spell
(
  "Chaos Cleanse",
  "Summon a chaotic storm on the battlefield.\nDeals DRK damage to enemies.\nCleanses stat debuffs of allies.",
  TargetInfo::Self,
  [] (Character& a, Character& d, int mod)
  {
    auto damageFunc = [] (Character& a, Character& d)
                      {
                        Stats& as = a.GetStats();
                        Stats& ds = d.GetStats();

                        float aMD = as.GetTotalBaseStat(MD);
                        float aDRK = as.GetTotalMastery(DRK);

                        float dMR = ds.GetTotalBaseStat(MR);
                        float dDRK = ds.GetTotalMastery(DRK);

                        float damage = (3.75f * aMD * (aDRK/100.f) - .625f * dMR) * (100.f/dDRK);
                        d.TakeDamage(damage);
                      };

    auto healFunc = [] (Character& a)
                    {
                      a.GetStats().RemoveStatDebuffs();
                    };

    if(Battle::AttackerIsEnemy())
    {
      for(auto& chara : Battle::GetInstance()->GetEnemies())
        healFunc(chara);
      for(auto& chara : Party::GetFrontRow())
        damageFunc(a, chara);
    }
    else
    {
      for(auto& chara : Party::GetFrontRow())
        healFunc(chara);
      for(auto& chara : Battle::GetInstance()->GetEnemies())
        damageFunc(a, chara);
    }
  },
  .96f,
  .24f
),
Spell
(
  "Ragnarǫk",
  "Fires a concentrated laser of pure arcane energy at your enemies.\nUses up all of your MP, making the spell stronger.\nYou are completely exhausted after using this.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aMD = as.GetTotalBaseStat(MD);
    float aARC = as.GetTotalMastery(ARC);

    float dMR = ds.GetTotalBaseStat(MR);
    float dARC = ds.GetTotalMastery(ARC);
    float& currentMP = a.CurrentMP();

    float damage = ((10.f + currentMP/100.f) * aMD * (aARC/100.f) - .5f * dMR) * (100.f/dARC);
    d.TakeDamage(damage);
    currentMP = 0.f;
  },
  1.6f,
  0.f
),
Spell
(
  "Quick Dive",
  "Quickly dive at the target.\nLow delay.\nDeals physical damage.",
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
  .24f,
  .68f
),
Spell
(
  "Poison Flight",
  "Fly among the enemy ranks leaving a poison trail behind you.\nChance to inflict PAR and PSN.\nDeals physical DRK damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);
    float aDRK = as.GetTotalMastery(DRK);

    float dDEF = ds.GetTotalBaseStat(DEF);
    float dDRK = ds.GetTotalMastery(DRK);

    float damage = (4.f * aAD * (aDRK/100.f) - dDEF) * (100.f/dDRK);
    d.TakeDamage(damage);
    // TODO inflict PAR(70), PSN(70)
    if(ds.TryToApplyDebuff(PAR, 70))
    {
      d.ApplyPAR(70);
    }
    if(ds.TryToApplyDebuff(PSN, 70))
    {
      d.ApplyPoison(70);
    }
  },
  .8f,
  .25f
),
Spell
(
  "Offense Is The Best Defense",
  "Fast as the wind you attack all enemies and try to PAR them.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 6.f * aAD - 1.5f * dDEF;
    d.TakeDamage(damage);

    if(ds.TryToApplyDebuff(PAR, 20))
    {
      d.ApplyPAR(20);
    }
  },
  .8f,
  .35f
),
Spell
(
  "Cleansing Song",
  "Sing a nice melody that removes all status debuffs of the target\nand converts stat debuffs into buffs.",
  TargetInfo::Single,
  [] (Character& a, Character& d, int mod)
  {
    Stats& ds = d.GetStats();
    d.RemoveDebuffs();
    for(int i = 0; i < 9; ++i)
    {
      float stat = ds.BaseStats[(BaseStat)i][4];
      if(stat < 1.f)
        ds.BuffBaseStat((BaseStat)i, 1.f - stat);
    }
  },
  .4f,
  .65f
),
Spell
(
  "The Old Ways",
  "A physical attack dealing physical damage to all enemies.\nGood old times.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);

    float dDEF = ds.GetTotalBaseStat(DEF);

    float damage = 3.4225f * aAD - .925f * dDEF;
    d.TakeDamage(damage);
  },
  .52f,
  .4f
),
Spell
(
  "The New Ways",
  "A physical attack dealing magical damage to all enemies.\nWhat a twist!",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    Stats& ds = d.GetStats();
    float aAD = as.GetTotalBaseStat(AD);

    float dMR = ds.GetTotalBaseStat(MR);

    float damage = 3.4225f * aAD - .925f * dMR;
    d.TakeDamage(damage);
  },
  .52f,
  .4f
),
Spell
(
  "Support Technique: Sword",
  "Increases AD of all allies.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    d.GetStats().BuffBaseStat(AD, .48f);
  },
  .8f,
  .3f
),
Spell
(
  "Support Technique: Wand",
  "Increases MD of all allies.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    d.GetStats().BuffBaseStat(MD, .48f);
  },
  .8f,
  .3f
),
Spell
(
  "Support Technique: Shield",
  "Increases DEF of all allies.",
  TargetInfo::Allies,
  [] (Character& a, Character& d, int mod)
  {
    d.GetStats().BuffBaseStat(DEF, .48f);
  },
  .8f,
  .3f
),
Spell
(
  "Number of the Beast",
  "A strong attack dealing high unresistable physical damage.",
  TargetInfo::Enemies,
  [] (Character& a, Character& d, int mod)
  {
    Stats& as = a.GetStats();
    float aAD = as.GetTotalBaseStat(AD);

    float damage = 6.66f * aAD;
    d.TakeDamage(damage);
  },
  1.2f,
  .15f
),
