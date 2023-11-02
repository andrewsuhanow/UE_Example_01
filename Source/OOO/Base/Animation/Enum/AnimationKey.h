
// ** #include "Base/Animation/Enum/AnimationKey.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EAnimationKey : uint8
{
	none,
	locomotion_equip,
	locomotion_unequip,
	locomotion_use,
	locomotion_attack1,
	locomotion_attack2,
	locomotion_attack3,
	locomotion_attack4,
	locomotion_attack5,
	locomotion_block,
	locomotion_parrir,
	locomotion_dodge_lft,
	locomotion_dodge_rt,
	locomotion_dodge_fwd,
	locomotion_dodge_bwd,
	locomotion_hit0_easy,
	locomotion_hit1_normal,
	locomotion_hit2_push,
	locomotion_hit3_fall,
	locomotion_dead,
	locomotion_up_barier03,
	locomotion_down_barier03,
	locomotion_up_barier06,
	locomotion_down_barier06,
	locomotion_up_barier1,
	locomotion_down_barier1,
	locomotion_up_barier15,
	locomotion_down_barier15, 
	locomotion_jump_forward, 
	locomotion_big_jump_forward, 
	locomotion_spell_Prepare_mid,
	locomotion_spell_cast_mid,
	locomotion_spell_Prepare_up,
	locomotion_spell_cast_up,
	locomotion_spell_Prepare_dwn,
	locomotion_spell_cast_dwn, 
	locomotion_throw_Prepare_mid,
	locomotion_throw_cast_mid,
	locomotion_throw_Prepare_up,
	locomotion_throw_cast_up,
	locomotion_throw_Prepare_dwn,
	locomotion_throw_cast_dwn,
	locomotion_stun,
	locomotion_indjure,				// ** hromanie
	locomotion_sleep1_prepare,
	locomotion_sleep1_idle,
	locomotion_sleep2_prepare,
	locomotion_sleep2_idle,
	locomotion_sleep3_prepare,
	locomotion_sleep3_idle,
	locomotion_cover_idle_stand,
	locomotion_cover_idle_sit,
	locomotion_cover_up,
	locomotion_cover_left,
	locomotion_cover_right,

	swordlong_equip,
	swordlong_unequip,
	swordlong_use,
	swordlong_attack1,
	swordlong_attack2,
	swordlong_attack3,
	swordlong_attack4,
	swordlong_attack5,
	swordlong_block,
	swordlong_parrir,
	swordlong_dodge_lft,
	swordlong_dodge_rt,
	swordlong_dodge_fwd,
	swordlong_dodge_bwd,
	swordlong_hit0_easy,
	swordlong_hit1_normal,
	swordlong_hit2_push,
	swordlong_hit3_fall,
	swordlong_dead,
	swordlong_up_barier03,
	swordlong_down_barier03,
	swordlong_up_barier06,
	swordlong_down_barier06,
	swordlong_up_barier1,
	swordlong_down_barier1,
	swordlong_up_barier15,
	swordlong_down_barier15,
	swordlong_jump_forward,
	swordlong_big_jump_forward,
	swordlong_spell_Prepare_mid,
	swordlong_spell_cast_mid,
	swordlong_spell_Prepare_up,
	swordlong_spell_cast_up,
	swordlong_spell_Prepare_dwn,
	swordlong_spell_cast_dwn,
	swordlong_throw_Prepare_mid,
	swordlong_throw_cast_mid,
	swordlong_throw_Prepare_up,
	swordlong_throw_cast_up,
	swordlong_throw_Prepare_dwn,
	swordlong_throw_cast_dwn,
	swordlong_stun,
	swordlong_indjure,				// ** hromanie
	swordlong_sleep1_prepare,
	swordlong_sleep1_idle,
	swordlong_sleep2_prepare,
	swordlong_sleep2_idle,
	swordlong_sleep3_prepare,
	swordlong_sleep3_idle,
	swordlong_cover_idle_stand,
	swordlong_cover_idle_sit,
	swordlong_cover_up,
	swordlong_cover_left,
	swordlong_cover_right,

	rifle_equip,
	rifle_unequip,
	rifle_use,
	rifle_attack1,
	rifle_attack2,
	rifle_attack3,
	rifle_attack4,
	rifle_attack5,
	rifle_block,
	rifle_parrir,
	rifle_dodge_lft,
	rifle_dodge_rt,
	rifle_dodge_fwd,
	rifle_dodge_bwd,
	rifle_hit0_easy,
	rifle_hit1_normal,
	rifle_hit2_push,
	rifle_hit3_fall,
	rifle_dead,
	rifle_up_barier03,
	rifle_down_barier03,
	rifle_up_barier06,
	rifle_down_barier06,
	rifle_up_barier1,
	rifle_down_barier1,
	rifle_up_barier15,
	rifle_down_barier15,
	rifle_jump_forward,
	rifle_big_jump_forward,
	rifle_spell_Prepare_mid,
	rifle_spell_cast_mid,
	rifle_spell_Prepare_up,
	rifle_spell_cast_up,
	rifle_spell_Prepare_dwn,
	rifle_spell_cast_dwn,
	rifle_throw_Prepare_mid,
	rifle_throw_cast_mid,
	rifle_throw_Prepare_up,
	rifle_throw_cast_up,
	rifle_throw_Prepare_dwn,
	rifle_throw_cast_dwn,
	rifle_stun,
	rifle_indjure,				// ** hromanie
	rifle_sleep1_prepare,
	rifle_sleep1_idle,
	rifle_sleep2_prepare,
	rifle_sleep2_idle,
	rifle_sleep3_prepare,
	rifle_sleep3_idle,
	rifle_cover_idle_stand,
	rifle_cover_idle_sit,
	rifle_cover_up,
	rifle_cover_left,
	rifle_cover_right,	MAX
};