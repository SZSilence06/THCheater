#pragma once

#define THAPI _declspec(dllexport)

extern "C" {
	THAPI bool FindGameProcess();
	THAPI bool ReadValues();
	THAPI int GetLife();
	THAPI int GetBomb();
	THAPI int GetPower();
	THAPI long long GetScore();
	THAPI void SetLife(int life);
	THAPI void SetBomb(int bomb);
	THAPI void SetPower(int power);
	THAPI void SetScore(long long score);
	THAPI bool LockLife(bool lockLife);
	THAPI bool LockBomb(bool lockBomb);
	THAPI bool LockPower(bool lockPower);
	THAPI bool SetInvincible(bool invincible);
	THAPI bool WriteValues();
}
