#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H
#include <iostream>
#include <cmath>
#include <vector>
//#include <boost/thread.hpp>
//#include <boost/chrono.hpp>
#include "tuxedo_io_lib/tuxedo_io_api.hh"
#include <yaml-cpp/yaml.h>
#include <unistd.h>
#include <limits.h>
#include "myStructures.h"
#include <thread>
#include "dbus_reader.h"

using namespace std;


class HardwareControl
{
public:
    HardwareControl();
    bool Initialize(string p_directory, string p_power, string p_battery);

public:
    void StartPowerMonitor();
    void Run(int p_optimizeLoop);
    void Stop();



private:
    HardwareProfile m_hardwareprofile;
    //boost::thread m_thread;
    int m_activeProfile;
    int m_targetProfile;
    bool m_run;
    //vector <int> m_tempTab ;
    int m_speed;
    vector <HardwareProfile> m_profileList;
    TuxedoIOAPI m_io;
    int m_nbFan;
    int m_optimizeLoop;
    bool m_dedicatedGpu;
    //vector <int> m_ListSonde;
    dbus_reader m_dbusreader;
    std::thread m_thread_Monitor_Power;

private:
    bool CheckCurve(FanCurve * p_fanCurve);
    void ApplyProfile(int p_numProfile);
    HardwareProfile GenerateDefaultProfile(string p_name);
    HardwareProfile LoadProfile(string p_profile);
    void SetFanSpeed(int p_speed);
    FanSetting FoundTargetSpeed();
    void MonitorPowerSource();


};

#endif // HARDWARECONTROL_H
