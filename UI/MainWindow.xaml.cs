using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Text.RegularExpressions;

namespace THCheater
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private Cheater _cheater = null;

        public MainWindow()
        {
            InitializeComponent();

            _cheater = new Cheater();
            Load();
        }

        private bool FindGameProcess()
        {
            return false;
        }

        private void Update()
        {
            _cheater.ReadValues();
            this.textLife.Text = _cheater.life.ToString();
            this.textPower.Text = _cheater.power.ToString();
            this.textBomb.Text = _cheater.bomb.ToString();
            this.textScore.Text = _cheater.score.ToString();
        }

        private void OnHack(object sender, RoutedEventArgs e)
        {
            _cheater.invincible = this.checkBoxInvincible.IsChecked.Value;
            _cheater.lockLife = this.checkBoxLockLife.IsChecked.Value;
            _cheater.lockBomb = this.checkBoxLockBomb.IsChecked.Value;
            _cheater.lockPower = this.checkBoxLockPower.IsChecked.Value;
            _cheater.life = Convert.ToInt32(this.textLife.Text);
            _cheater.bomb = Convert.ToInt32(this.textBomb.Text);
            _cheater.score = Convert.ToInt64(this.textScore.Text);
            _cheater.power = Convert.ToInt32(this.textPower.Text);

            if (_cheater.Hack())
                MessageBox.Show("修改成功！");
            else
                MessageBox.Show("修改失败！");
        }

        private void OnLoad(object sender, RoutedEventArgs e)
        {
            Load();
        }

        private void Load()
        {
            if (_cheater.Init())
            {
                this.upText.Content = "已找到游戏进程";
                Update();
            }
            else
            {
                MessageBox.Show("未找到游戏进程");
                this.upText.Content = "未找到游戏进程";
            }
        }

        private void OnHelp(object sender, RoutedEventArgs e)
        {
            HelpWindow helpWindow = new HelpWindow();
            helpWindow.Show();
        }
    }

    public class NumericTextBox : TextBox
    {
        public static readonly DependencyProperty MinProperty;
        public static readonly DependencyProperty MaxProperty;

        private long min;
        private long max;

        public long Min
        {
            get
            {
                return (long)GetValue(MinProperty);
            }
            set
            {
                SetValue(MinProperty, value);
            }
        }

        public long Max
        {
            get
            {
                return (long)GetValue(MaxProperty);
            }
            set
            {
                SetValue(MaxProperty, value);
            }
        }

        static NumericTextBox()
        {
            FrameworkPropertyMetadata metaData_Min = new FrameworkPropertyMetadata(Int64.MinValue);
            FrameworkPropertyMetadata metaData_Max = new FrameworkPropertyMetadata(Int64.MaxValue);

            MinProperty = DependencyProperty.Register("Min", typeof(long), typeof(NumericTextBox), metaData_Min);
            MaxProperty = DependencyProperty.Register("Max", typeof(long), typeof(NumericTextBox), metaData_Max);
        }

        private bool IsTextAllowed(string text)
        {
            long result;
            if (Int64.TryParse(text, out result) == false)
                return false;

            return true;
        }

        protected override void OnPreviewTextInput(TextCompositionEventArgs e)
        {
            long result;
            if (Int64.TryParse(e.Text, out result) == false)
                e.Handled = true;

            base.OnPreviewTextInput(e);
        }

        protected override void OnLostFocus(RoutedEventArgs e)
        {
            base.OnLostFocus(e);
            long result;
            if (Int64.TryParse(this.Text, out result) == false)
                this.Text = Min.ToString();
            else
            {
                if (result < Min)
                    this.Text = Min.ToString();
                if (result > Max)
                    this.Text = Max.ToString();
            }
        }
    }
}