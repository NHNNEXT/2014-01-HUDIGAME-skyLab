using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class GameTimer
    {
        // Timer
        System.Timers.Timer m_Timer = new System.Timers.Timer();

        int m_Second = 0;
        int m_Minute = 0;
        int m_Hour = 0;
        System.Windows.Forms.Label m_target = null;

        public GameTimer(ref System.Windows.Forms.Label target)
        {
            // 1초 주기로 전광판(?)을 갱신할 준비
            m_target = target;
            m_Timer.Interval = 1000;
            m_Timer.Elapsed += new System.Timers.ElapsedEventHandler(UpdateClock);
            m_Timer.Start();
        }

        private delegate void TimerEventFiredDelegate();

        private void UpdateClock(object sender, System.Timers.ElapsedEventArgs e)
        {
            ++m_Second;

            if (m_Second > 59)
            {
                ++m_Minute;
                m_Second = 0;
            }

            if (m_Minute > 59)
            {
                ++m_Hour;
                m_Minute = 0;
            }

            m_target.BeginInvoke(new TimerEventFiredDelegate(Work));
        }

        private void Work()
        {
            m_target.Text = m_Hour.ToString() + " 시  " + m_Minute.ToString() + " 분  " + m_Second.ToString() + " 초";
        }
    }


}
