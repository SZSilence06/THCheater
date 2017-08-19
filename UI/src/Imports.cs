using System.Runtime.InteropServices;

namespace THCheater
{
    internal class Imports
    {
        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool FindGameProcess();

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool ReadValues();

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetLife();

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetBomb();

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetPower();

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern long GetScore();

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool LockLife(bool lockLife);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool LockBomb(bool lockBomb);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool LockPower(bool lockPower);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetInvincible(bool invincible);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLife(int life);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetBomb(int bomb);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPower(int power);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetScore(long score);

        [DllImport("THCheaterCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool WriteValues();
    }
}