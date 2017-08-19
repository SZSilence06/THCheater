#include "THCheater.h"
#include <TlHelp32.h>

const LPVOID addrLife = reinterpret_cast<LPVOID>(0x4a57f4);
const LPVOID addrBomb = reinterpret_cast<LPVOID>(0x4a5800);
const LPVOID addrPower = reinterpret_cast<LPVOID>(0x4a57e4);
const LPVOID addrScore = reinterpret_cast<LPVOID>(0x4a57b0);
const LPVOID addrContinueTimes = reinterpret_cast<LPVOID>(0x4a57b8);

THCheater& THCheater::GetInstance()
{
	static THCheater instance;
	return instance;
}

THCheater::~THCheater()
{
	if (_hProcess)
		CloseHandle(_hProcess);
}

bool THCheater::FindProcess()
{
	DWORD pid = _GetProcessIdByName(L"th16.exe");
	if (pid == 0)
		return false;

	if (_hProcess)
	{
		CloseHandle(_hProcess);
		_hProcess = NULL;
	}

	_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
	if (_hProcess == NULL)
		return false;

	return true;
}

bool THCheater::ReadValues()
{
	if (_ReadLife() == false)
		return false;

	if (_ReadBomb() == false)
		return false;

	if (_ReadPower() == false)
		return false;

	if (_ReadScore() == false)
		return false;

	return true;
}

bool THCheater::_ReadLife()
{
	if (!ReadProcessMemory(_hProcess, addrLife, &_life, sizeof(_life), NULL))
		return false;

	return true;
}

bool THCheater::_ReadBomb()
{
	if (!ReadProcessMemory(_hProcess, addrBomb, &_bomb, sizeof(_bomb), NULL))
		return false;

	return true;
}

bool THCheater::_ReadPower()
{
	if (!ReadProcessMemory(_hProcess, addrPower, &_power, sizeof(_power), NULL))
		return false;

	return true;
}

bool THCheater::_ReadScore()
{
	int score;
	if (!ReadProcessMemory(_hProcess, addrScore, &score, sizeof(score), NULL))
		return false;

	BYTE continueTimes;
	if (!ReadProcessMemory(_hProcess, addrContinueTimes, &continueTimes, sizeof(continueTimes), NULL))
		return false;

	_score = (long long)score * 10 + continueTimes;
	return true;
}

bool THCheater::SetInvincible(bool invincible)
{
	const LPVOID addrToHack = reinterpret_cast<LPVOID>(0x443fdb);
	BYTE newCode[10] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	BYTE originalCode[10] = { 0xc7, 0x87, 0xa8, 0x65, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00 };
	if (invincible)
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&newCode, sizeof(BYTE) * 10, NULL))
			return false;
	}
	else
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&originalCode, sizeof(BYTE) * 10, NULL))
			return false;
	}
	return true;
}

bool THCheater::LockLife(bool lockLife)
{
	const LPVOID addrToHack = reinterpret_cast<LPVOID>(0x443d39);
	BYTE newCode = 0x90;
	BYTE originalCode = 0x48;
	if (lockLife)
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&newCode, sizeof(BYTE), NULL))
			return false;
	}
	else
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&originalCode, sizeof(BYTE), NULL))
			return false;
	}
	return true;
}

bool THCheater::LockBomb(bool lockBomb)
{
	const LPVOID addrToHack = reinterpret_cast<LPVOID>(0x40db83);
	BYTE newCode[3] = { 0x90, 0x90, 0x90 };
	BYTE originalCode[3] = { 0x83, 0xe8, 0x01 };
	if (lockBomb)
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&newCode, sizeof(BYTE) * 3, NULL))
			return false;
	}
	else
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&originalCode, sizeof(BYTE) * 3, NULL))
			return false;
	}
	return true;
}

bool THCheater::LockPower(bool lockPower)
{
	const LPVOID addrToHack = reinterpret_cast<LPVOID>(0x442749);
	BYTE newCode[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	BYTE originalCode[6] = { 0x89, 0x0d, 0xe4, 0x57, 0x4a, 0x00 };
	if (lockPower)
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&newCode, sizeof(BYTE) * 6, NULL))
			return false;
	}
	else
	{
		if (!WriteProcessMemory(_hProcess, addrToHack, (LPVOID)&originalCode, sizeof(BYTE) * 6, NULL))
			return false;
	}
	return true;
}

bool THCheater::WriteValues()
{
	if (!WriteProcessMemory(_hProcess, addrLife, &_life, sizeof(_life), NULL))
		return false;

	if (!WriteProcessMemory(_hProcess, addrBomb, &_bomb, sizeof(_bomb), NULL))
		return false;

	if (!WriteProcessMemory(_hProcess, addrPower, &_power, sizeof(_power), NULL))
		return false;

	int score = _score / 10;
	BYTE continueTimes = _score % 10;
	if (!WriteProcessMemory(_hProcess, addrScore, &score, sizeof(score), NULL))
		return false;

	if (!WriteProcessMemory(_hProcess, addrContinueTimes, &continueTimes, sizeof(continueTimes), NULL))
		return false;

	return true;
}

DWORD THCheater::_GetProcessIdByName(const WCHAR* processName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (lstrcmp(entry.szExeFile, processName) == 0)
			{
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		}
	}
	CloseHandle(snapshot);
	return NULL;
}