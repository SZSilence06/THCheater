namespace THCheater
{
    internal class Cheater
    {
        public Cheater()
        {
        }

        public int life;
        public int bomb;
        public int power;
        public long score;

        public bool invincible;
        public bool lockLife;
        public bool lockBomb;
        public bool lockPower;

        public bool Init()
        {
            return Imports.FindGameProcess();
        }

        public bool ReadValues()
        {
            if (Imports.ReadValues() == false)
                return false;

            this.life = Imports.GetLife();
            this.bomb = Imports.GetBomb();
            this.power = Imports.GetPower();
            this.score = Imports.GetScore();

            return true;
        }

        public bool Hack()
        {
            if (Imports.LockLife(lockLife) == false)
                return false;

            if (Imports.LockBomb(lockBomb) == false)
                return false;

            if (Imports.LockPower(lockPower) == false)
                return false;

            if (Imports.SetInvincible(invincible) == false)
                return false;

            Imports.SetLife(life);
            Imports.SetBomb(bomb);
            Imports.SetPower(power);
            Imports.SetScore(score);

            if (Imports.WriteValues() == false)
                return false;

            return true;
        }
    }
}