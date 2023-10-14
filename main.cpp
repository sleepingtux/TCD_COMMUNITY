#include <iostream>
#include <yaml-cpp/yaml.h>
#include <signal.h>
#include "hardwarecontrol.h"

using namespace std;

HardwareControl m_hardwareControl;

void signal_callback_handler(int signum) {
   cout << "Caught signal " << signum << endl;
   m_hardwareControl.Stop();
   // Terminate program
   //exit(signum);
}

int main()
{

    string directory,battery,power;
    bool initialize = false;
    //catch signal
    signal(SIGINT, signal_callback_handler);
    signal(SIGABRT, signal_callback_handler);
    signal(SIGTERM, signal_callback_handler);
    signal(SIGQUIT, signal_callback_handler);
    signal(SIGKILL, signal_callback_handler);

    vector <int> exclude;
    try
    {
        YAML::Node m_config = YAML::LoadFile("tcd_config.yaml");
        directory = m_config["Directory_Profile"].as<std::string>();
        battery = m_config["Profile_Battery"].as<std::string>();
        power = m_config["Profile_Power"].as<std::string>();

        m_config=NULL;
    }
    catch ( const YAML::Exception ex)
   {
       cout<<"Error: "<<ex.what()<<endl;
       cout<<"Check tcd_config.yaml File!!!!" <<endl;
       return 9;
   }

    initialize=m_hardwareControl.Initialize(directory,power,battery);
    if (initialize)
    {
        m_hardwareControl.StartPowerMonitor();
        m_hardwareControl.Run();
    }
    else
        cout<<"ERROR Service could not initialize, check settings files!!!"<<endl;
    return 0;
}
