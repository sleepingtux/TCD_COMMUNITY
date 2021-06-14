#ifndef MYSTRUCTURES_H
#define MYSTRUCTURES_H
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct FanSetting
{
    int m_fanSpeed;
    int m_fanDelay;
};

struct FanCurve
{
    int m_lowDelay;
    int m_lowTemp;
    int m_highTemp;
    unsigned long m_number_AverageTab;
    int m_offset_TabCurve;
    vector <int> m_fanCurve;
    int m_sondeNumber;
    vector <int> m_tempTab;
    int m_tempTotal;
    int m_temp;
};

struct HardwareProfile
{
    string m_name;
    string m_cmd1;
    string m_cmd2;
    vector <FanCurve> m_listCurve;
};



#endif // MYSTRUCTURES_H
