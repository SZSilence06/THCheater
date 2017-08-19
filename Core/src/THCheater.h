#pragma once

#include "stdafx.h"
#include <vector>

class THCheater
{
public:
	static THCheater& GetInstance();

	~THCheater();

	bool FindProcess();
	bool ReadValues();
	bool WriteValues();

	int GetLife() const { return _life; }
	int GetBomb() const { return _bomb; }
	int GetPower() const { return _power; }
	long long GetScore() const { return _score; }

	void SetLife(int life) { _life = life; }
	void SetBomb(int bomb) { _bomb = bomb; }
	void SetScore(long long score) { _score = score; }
	void SetPower(int power) { _power = power; }

	bool SetInvincible(bool invincible);
	bool LockLife(bool lockLife);
	bool LockBomb(bool lockBomb);
	bool LockPower(bool lockPower);

private:
	THCheater() = default;

	DWORD _GetProcessIdByName(const WCHAR* processName);
	bool _ReadLife();
	bool _ReadBomb();
	bool _ReadPower();
	bool _ReadScore();

private:
	HANDLE _hProcess = NULL;

	BYTE _life;
	BYTE _bomb;
	WORD _power;
	long long _score;
};
