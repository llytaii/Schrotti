#include <Arduino.h>
#include <Servo.h>

class SchrottiLeg : public Servo
{
public:
    void set_inversed(bool val)
    {
        m_inversed_front = val;
    }

    bool move_to(int target_deg, int speed_deg = 1)
    {
        target_deg = m_inversed_front ? 180 - target_deg : target_deg;

        if (m_cur_pos == target_deg)
            return true;

        m_cur_pos = m_cur_pos > target_deg ? m_cur_pos - speed_deg : m_cur_pos + speed_deg;
        m_cur_pos = abs(m_cur_pos - target_deg) <= speed_deg ? target_deg : m_cur_pos;
        this->write(m_cur_pos);
        return m_cur_pos == target_deg;
    }

private:
    bool m_inversed_front = false;
    int m_cur_pos = 0;
};

class Schrotti
{
public:
    Schrotti(int fl, int fr, int bl, int br)
    {
        // m_legs[FL].attach(3);
        // m_legs[FR].attach(5);
        // m_legs[BL].attach(6);
        // m_legs[BR].attach(9);
        
        m_legs[FL].attach(2);
        m_legs[FR].attach(3);
        m_legs[BL].attach(4);
        m_legs[BR].attach(5);

        m_legs[FR].set_inversed(true);
        m_legs[BR].set_inversed(true);

        this->walk_blocking(fl, fr, bl, br);
    }

private:
    enum WalkState
    {
        WALK_ONE,
        RESET_ONE,
        WALK_TWO,
        RESET_TWO,
    };
    enum LegPos
    {
        FL,
        FR,
        BL,
        BR
    };

public:
    void walk_blocking(int fl, int fr, int bl, int br, int dly = 5)
    {
        while(true)
        {
            bool done = true;
            done &= m_legs[FL].move_to(fl);
            done &= m_legs[FR].move_to(fr);
            done &= m_legs[BL].move_to(bl);
            done &= m_legs[BR].move_to(br);
            delay(dly);
            if(done) break;
        }
    };

private:
    SchrottiLeg m_legs[4];
};