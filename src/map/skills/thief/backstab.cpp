// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "backstab.hpp"

#include <config/core.hpp>

#include "map/pc.hpp"
#include "map/status.hpp"

SkillBackStab::SkillBackStab() : SkillImpl(RG_BACKSTAP) {
}

void SkillBackStab::calculateSkillRatio(const Damage *wd, const block_list *src, const block_list *target, uint16 skill_lv, int32 &base_skillratio, int32 mflag) const {
	const map_session_data* sd = BL_CAST( BL_PC, src );

	if(sd && sd->status.weapon == W_BOW && battle_config.backstab_bow_penalty)
		base_skillratio += (200 + 40 * skill_lv) / 2;
	else
		base_skillratio += 200 + 40 * skill_lv;
}

void SkillBackStab::castendDamageId(block_list *src, block_list *target, uint16 skill_lv, t_tick tick, int32& flag) const {
	map_session_data* sd = BL_CAST(BL_PC, src);

	// Apenas verifica se é inimigo válido
	if (battle_check_target(src, target, BCT_ENEMY) <= 0) {
		if (sd)
			clif_skill_fail(*sd, getSkillId());
		return;
	}

	// Remove hiding normalmente
	status_change_end(src, SC_HIDING);

	// Aplica dano independentemente da direção
	skill_attack(BF_WEAPON, src, src, target, getSkillId(), skill_lv, tick, flag);
}

void SkillBackStab::applyAdditionalEffects(block_list *src, block_list *target, uint16 skill_lv, t_tick tick, int32 attack_type, enum damage_lv dmg_lv) const {
#ifdef RENEWAL
	sc_start(src,target,SC_STUN,(5+2*skill_lv),skill_lv,skill_get_time(getSkillId(),skill_lv));
#endif
}

void SkillBackStab::modifyHitRate(int16& hit_rate, const block_list* src, const block_list* target, uint16 skill_lv) const {
#ifdef RENEWAL
	hit_rate += skill_lv; // !TODO: What's the rate increase?
#endif
}
