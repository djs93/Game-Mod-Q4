#include "../../idlib/precompiled.h"
#pragma hdrstop

#include "../Game_local.h"
#include "../Weapon.h"
#include "../Projectile.h"

class rvWeaponDarkMatterGun : public rvWeapon {
public:

	CLASS_PROTOTYPE(rvWeaponDarkMatterGun);

	rvWeaponDarkMatterGun(void);

	virtual void			Spawn(void);
	void					PreSave(void);
	void					PostSave(void);

#ifdef _XENON
	virtual bool		AllowAutoAim(void) const { return false; }
#endif

private:

	stateResult_t		State_Idle(const stateParms_t& parms);
	stateResult_t		State_Fire(const stateParms_t& parms);
	stateResult_t		State_Reload(const stateParms_t& parms);

	const char*			GetFireAnim() const { return (!AmmoInClip()) ? "fire_empty" : "fire"; }
	const char*			GetIdleAnim() const { return (!AmmoInClip()) ? "idle_empty" : "idle"; }

	CLASS_STATES_PROTOTYPE(rvWeaponDarkMatterGun);
};

CLASS_DECLARATION(rvWeapon, rvWeaponDarkMatterGun)
END_CLASS

/*
================
rvWeaponDarkMatterGun::rvWeaponDarkMatterGun
================
*/
rvWeaponDarkMatterGun::rvWeaponDarkMatterGun(void) {
}

/*
================
rvWeaponDarkMatterGun::Spawn
================
*/
void rvWeaponDarkMatterGun::Spawn(void) {
	SetState("Raise", 0);
}

/*
================
rvWeaponDarkMatterGun::PreSave
================
*/
void rvWeaponDarkMatterGun::PreSave(void) {
}

/*
================
rvWeaponDarkMatterGun::PostSave
================
*/
void rvWeaponDarkMatterGun::PostSave(void) {
}

/*
===============================================================================

States

===============================================================================
*/

CLASS_STATES_DECLARATION(rvWeaponDarkMatterGun)
STATE("Idle", rvWeaponDarkMatterGun::State_Idle)
STATE("Fire", rvWeaponDarkMatterGun::State_Fire)
STATE("Reload", rvWeaponDarkMatterGun::State_Reload)
END_CLASS_STATES

/*
================
rvWeaponDarkMatterGun::State_Idle
================
*/
stateResult_t rvWeaponDarkMatterGun::State_Idle(const stateParms_t& parms) {
	enum {
		STAGE_INIT,
		STAGE_WAIT,
	};
	switch (parms.stage) {
	case STAGE_INIT:
		if (!AmmoAvailable()) {
			SetStatus(WP_OUTOFAMMO);
		}
		else {
			SetStatus(WP_READY);
		}

		PlayCycle(ANIMCHANNEL_ALL, GetIdleAnim(), parms.blendFrames);
		return SRESULT_STAGE(STAGE_WAIT);

	case STAGE_WAIT:
		if (wsfl.lowerWeapon) {
			SetState("Lower", 4);
			return SRESULT_DONE;
		}
		if (!clipSize) {
			if (wsfl.attack && AmmoAvailable()) {
				SetState("Fire", 0);
				return SRESULT_DONE;
			}
		}
		else {
			if (gameLocal.time > nextAttackTime && wsfl.attack && AmmoInClip()) {
				SetState("Fire", 0);
				return SRESULT_DONE;
			}

			if (wsfl.attack && AutoReload() && !AmmoInClip() && AmmoAvailable()) {
				SetState("Reload", 4);
				return SRESULT_DONE;
			}
			if (wsfl.netReload || (wsfl.reload && AmmoInClip() < ClipSize() && AmmoAvailable()>AmmoInClip())) {
				SetState("Reload", 4);
				return SRESULT_DONE;
			}
		}
		return SRESULT_WAIT;
	}
	return SRESULT_ERROR;
}

/*
================
rvWeaponDarkMatterGun::State_Fire
================
*/
stateResult_t rvWeaponDarkMatterGun::State_Fire(const stateParms_t& parms) {
	enum {
		STAGE_INIT,
		STAGE_WAIT,
	};
	switch (parms.stage) {
	case STAGE_INIT:
		nextAttackTime = gameLocal.time + (fireRate * owner->PowerUpModifier(PMOD_FIRERATE));
		Attack(false, 1, spread, 0, 1.0f);
		PlayAnim(ANIMCHANNEL_ALL, GetFireAnim(), 0);
		return SRESULT_STAGE(STAGE_WAIT);

	case STAGE_WAIT:
		if (wsfl.attack && gameLocal.time >= nextAttackTime && AmmoInClip() && !wsfl.lowerWeapon) {
			SetState("Fire", 0);
			return SRESULT_DONE;
		}
		if (AnimDone(ANIMCHANNEL_ALL, 0)) {
			SetState("Idle", 0);
			return SRESULT_DONE;
		}
		return SRESULT_WAIT;
	}
	return SRESULT_ERROR;
}

/*
================
rvWeaponDarkMatterGun::State_Reload
================
*/
stateResult_t rvWeaponDarkMatterGun::State_Reload(const stateParms_t& parms) {
	enum {
		STAGE_INIT,
		STAGE_WAIT,
	};
	switch (parms.stage) {
	case STAGE_INIT:
		if (wsfl.netReload) {
			wsfl.netReload = false;
		}
		else {
			NetReload();
		}

		SetStatus(WP_RELOAD);
		PlayAnim(ANIMCHANNEL_ALL, "reload", parms.blendFrames);
		return SRESULT_STAGE(STAGE_WAIT);

	case STAGE_WAIT:
		if (AnimDone(ANIMCHANNEL_ALL, 4)) {
			AddToClip(ClipSize());
			SetState("Idle", 4);
			return SRESULT_DONE;
		}
		if (wsfl.lowerWeapon) {
			SetState("Lower", 4);
			return SRESULT_DONE;
		}
		return SRESULT_WAIT;
	}
	return SRESULT_ERROR;
}

/*
===============================================================================
rvDarkMatterProjectile
===============================================================================
*/

class rvDarkMatterProjectile : public idProjectile {
public:
	CLASS_PROTOTYPE(rvDarkMatterProjectile);

	rvDarkMatterProjectile(void);
	~rvDarkMatterProjectile(void);

	void					Spawn(void);

	void					Save(idSaveGame *savefile) const;
	void					Restore(idRestoreGame *savefile);

	virtual void			Think(void);

protected:

	int					nextDamageTime;
	const idDict*		radiusDamageDef;
};

CLASS_DECLARATION(idProjectile, rvDarkMatterProjectile)
END_CLASS

/*
================
rvDarkMatterProjectile::rvDarkMatterProjectile
================
*/
rvDarkMatterProjectile::rvDarkMatterProjectile(void) {
	radiusDamageDef = NULL;
}

/*
================
rvDarkMatterProjectile::~rvDarkMatterProjectile
================
*/
rvDarkMatterProjectile::~rvDarkMatterProjectile(void) {
}

/*
================
rvDarkMatterProjectile::Spawn
================
*/
void rvDarkMatterProjectile::Spawn(void) {
	nextDamageTime = 0;
	radiusDamageDef = gameLocal.FindEntityDefDict(spawnArgs.GetString("def_radius_damage"));
}

/*
================
rvDarkMatterProjectile::Save
================
*/
void rvDarkMatterProjectile::Save(idSaveGame *savefile) const {
	savefile->WriteInt(nextDamageTime);
}

/*
================
rvDarkMatterProjectile::Restore
================
*/
void rvDarkMatterProjectile::Restore(idRestoreGame *savefile) {
	savefile->ReadInt(nextDamageTime);

	radiusDamageDef = gameLocal.FindEntityDefDict(spawnArgs.GetString("def_radius_damage"));
}

/*
================
rvDarkMatterProjectile::Think
================
*/
void rvDarkMatterProjectile::Think(void) {
	physicsObj.SetClipMask(MASK_DMGSOLID);
	idProjectile::Think();

	if (gameLocal.time > nextDamageTime) {
		gameLocal.RadiusDamage(GetPhysics()->GetOrigin(), this, owner, owner, NULL, spawnArgs.GetString("def_radius_damage"), 1.0f, &hitCount);
		nextDamageTime = gameLocal.time + SEC2MS(spawnArgs.GetFloat("damageRate", ".05"));
	}
}


