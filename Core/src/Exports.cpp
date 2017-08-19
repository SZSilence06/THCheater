#include "Exports.h"
#include "THCheater.h"

bool FindGameProcess()
{
	return THCheater::GetInstance().FindProcess();
}

bool ReadValues()
{
	return THCheater::GetInstance().ReadValues();
}

int GetLife()
{
	return THCheater::GetInstance().GetLife();
}

int GetBomb()
{
	return THCheater::GetInstance().GetBomb();
}

int GetPower()
{
	return THCheater::GetInstance().GetPower();
}

long long GetScore()
{
	return THCheater::GetInstance().GetScore();
}

bool LockLife(bool lockLife)
{
	return THCheater::GetInstance().LockLife(lockLife);
}

bool LockBomb(bool lockBomb)
{
	return THCheater::GetInstance().LockBomb(lockBomb);
}

bool LockPower(bool lockPower)
{
	return THCheater::GetInstance().LockPower(lockPower);
}

bool SetInvincible(bool invincible)
{
	return THCheater::GetInstance().SetInvincible(invincible);
}

void SetLife(int life)
{
	THCheater::GetInstance().SetLife(life);
}

void SetBomb(int bomb)
{
	THCheater::GetInstance().SetBomb(bomb);
}

void SetPower(int power)
{
	THCheater::GetInstance().SetPower(power);
}

void SetScore(long long score)
{
	THCheater::GetInstance().SetScore(score);
}

bool WriteValues()
{
	return THCheater::GetInstance().WriteValues();
}