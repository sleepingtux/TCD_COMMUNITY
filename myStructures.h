#ifndef MYSTRUCTURES_H
#define MYSTRUCTURES_H
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct FanSetting
{
    int m_FanSpeed;
    int m_FanDelay;
};

struct FanCurve
{
    int m_LowDelay;
    int m_LowTemp;
    int m_HighTemp;
    unsigned long m_Number_AverageTab;
    int m_Offset_TabCurve;
    vector <int> m_FanCurve;
    int m_SondeNumber;
    vector <int> m_TempTab;
    int m_tempTotal;
    int m_temp;
};

struct HardwareProfile
{
    string m_name;
    string m_Cmd1;
    string m_Cmd2;
    vector <FanCurve> m_ListCurve;
};



#endif // MYSTRUCTURES_H
