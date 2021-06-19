#include "hardwarecontrol.h"


HardwareControl::HardwareControl()
{

}


HardwareProfile HardwareControl::GenerateDefaultProfile(string p_name)
{
   HardwareProfile defaultProfile;
   FanCurve defaultFanCurve;
   defaultProfile.m_name=p_name;
   defaultFanCurve.m_offset_TabCurve=30;
   defaultFanCurve.m_highTemp=92;
   defaultFanCurve.m_lowDelay=2;
   defaultFanCurve.m_lowTemp=72;
   defaultFanCurve.m_number_AverageTab=7;

   #pragma region Curve {
     // Minimal temp = 30°
     //30°
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);

     //40°
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);

     //50°
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);
     defaultFanCurve.m_fanCurve.push_back(20);

     //60°
     defaultFanCurve.m_fanCurve.push_back(30);
     defaultFanCurve.m_fanCurve.push_back(30);
     defaultFanCurve.m_fanCurve.push_back(30);
     defaultFanCurve.m_fanCurve.push_back(30);
     defaultFanCurve.m_fanCurve.push_back(30);
     defaultFanCurve.m_fanCurve.push_back(40);
     defaultFanCurve.m_fanCurve.push_back(40);
     defaultFanCurve.m_fanCurve.push_back(40);
     defaultFanCurve.m_fanCurve.push_back(40);
     defaultFanCurve.m_fanCurve.push_back(40);

     //70°
     defaultFanCurve.m_fanCurve.push_back(50);
     defaultFanCurve.m_fanCurve.push_back(50);
     defaultFanCurve.m_fanCurve.push_back(50);
     defaultFanCurve.m_fanCurve.push_back(50);
     defaultFanCurve.m_fanCurve.push_back(50);
     defaultFanCurve.m_fanCurve.push_back(60);
     defaultFanCurve.m_fanCurve.push_back(60);
     defaultFanCurve.m_fanCurve.push_back(60);
     defaultFanCurve.m_fanCurve.push_back(60);
     defaultFanCurve.m_fanCurve.push_back(60);

     //80°
     defaultFanCurve.m_fanCurve.push_back(80);
     defaultFanCurve.m_fanCurve.push_back(80);
     defaultFanCurve.m_fanCurve.push_back(80);
     defaultFanCurve.m_fanCurve.push_back(80);
     defaultFanCurve.m_fanCurve.push_back(80);
     defaultFanCurve.m_fanCurve.push_back(100);
     defaultFanCurve.m_fanCurve.push_back(100);
     defaultFanCurve.m_fanCurve.push_back(100);
     defaultFanCurve.m_fanCurve.push_back(100);
     defaultFanCurve.m_fanCurve.push_back(100);
       #pragma endregion }

    defaultProfile.m_listCurve.push_back(defaultFanCurve);


    return defaultProfile;

}


HardwareProfile HardwareControl::LoadProfile(string p_profile)
{
    m_dedicatedGpu=false;
    string key;
    vector <string> target;

    YAML_CPP_API::YAML::Node m_config = YAML_CPP_API::YAML::LoadFile(p_profile);

    HardwareProfile r_profile;
    r_profile.m_name = m_config["ProfileName"].as<std::string>();
    r_profile.m_cmd1 = m_config["Cmd1"].as<std::string>();
    r_profile.m_cmd2 = m_config["Cmd2"].as<std::string>();
    m_dedicatedGpu = m_config["Dedicated_GPU"].as<bool>();

    target.push_back("CPU_");
    if(m_dedicatedGpu)
        target.push_back("GPU_");

    FanCurve Curve;
    for (std::size_t i=0; i<target.size(); i++)
    {
        key=target[i];
        key.append("Sonde");
        Curve.m_sondeNumber = m_config[key].as<std::int32_t>()-1;

        key=target[i];
        key.append("LowDelay");
        Curve.m_lowDelay=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("LowTemp");
        Curve.m_lowTemp=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("HighTemp");
        Curve.m_highTemp=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("Number_AverageTab");
        Curve.m_number_AverageTab=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("Offset_TabCurve");
        Curve.m_offset_TabCurve=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("FanCurve");
        int size= m_config[key].size();
        for (int k = 0;k < size;k++)
        {
            Curve.m_fanCurve.push_back(m_config[key][k].as<std::int32_t>());
            //cout<<Curve.m_FanCurve[k]<<endl;
        }
        //we add 100% at the end to be sure that it will be 100% on high temp;
        Curve.m_fanCurve.push_back(100);
        Curve.m_temp = 0;
        Curve.m_tempTotal = 0;
        r_profile.m_listCurve.push_back(Curve);
        if (CheckCurve(&Curve))
            m_profileList.push_back(r_profile);
    }
    //m_config=NULL;
    return r_profile;
}

bool HardwareControl::Initialize(string p_directory, string p_power, string p_battery)
{
    bool r_initialize_correct=true;
    //Get the number of the fan
    m_io.GetNumberFans(m_nbFan);
    cout<<"Number of Fan: "<<m_nbFan<<endl;

    //Yaml could only open a file that is in pwd dir, so change to the directory you want.
    char cwd[PATH_MAX];
    string previousWD;
    string newWD;
    previousWD=getcwd(cwd, sizeof (cwd));

    //if does not begin by / we start from the current pwd
    if (p_directory.at(1) != '/')
    {
        newWD=previousWD;
        //cout<<"PWD: "<<previousWD<<endl;
        newWD.append("/");
        newWD.append(p_directory);
        //cout<<"TMP: "<<newWD<<endl;
        chdir(newWD.c_str());
        //cout<<"PWD: "<<getcwd(cwd, sizeof (cwd))<<endl;
    }
    else
    {
        //cout<<"PWD: "<<previousWD<<endl;
        newWD=p_directory;
        //cout<<"TMP: "<<newWD<<endl;
        chdir(newWD.c_str());
        //cout<<"PWD: "<<getcwd(cwd, sizeof (cwd))<<endl;
    }


    //Power
    try
    {
        LoadProfile(p_power);

    }
    catch ( const YAML::Exception ex)
    {
        cout << "Error: "<< p_power<< " "<< ex.what()<<endl;
        r_initialize_correct = false;

    }

    //battery
    try
        {
            LoadProfile(p_battery);

        }
        catch ( const YAML::Exception ex)
        {
            cout << "Error: "<< p_battery<< " "<< ex.what()<<endl;
            r_initialize_correct=false;
        }

    if (r_initialize_correct)
    {
        cout<<"Profile: "<<m_profileList[0].m_name<<endl;
        cout<<"Profile: "<<m_profileList[1].m_name<<endl;
        if (m_dbusreader.Connect())
        {
            m_activeProfile=m_dbusreader.Is_OnBattery();
            m_targetProfile=m_activeProfile;
            ApplyProfile(m_activeProfile);
        }
        //dbus connnexion pb
        else
        {
                m_activeProfile=0;
                m_targetProfile=m_activeProfile;
                ApplyProfile(m_activeProfile);
        }

    }
    //error
    else
    {
        exit(99);
    }

    //return to default directory
    chdir(previousWD.c_str());
    //cout<<"PWD: "<<getcwd(cwd, sizeof (cwd))<<endl;
    return r_initialize_correct;
}

FanSetting HardwareControl::FoundTargetSpeed()
{
    FanSetting r_fanSetting;
    r_fanSetting.m_fanDelay=99;
    r_fanSetting.m_fanSpeed=0;
    int temp = 0;
    int tmpspeed = 0;
    int tmpdelay = 0;
    unsigned long access = 0;
    bool stop = false;
    int i = 0;
    int size = m_profileList[m_activeProfile].m_listCurve.size();
    FanCurve * currentFanCurve;
    while (i < size  and !stop)
    {
          //For easy access
          currentFanCurve = &m_profileList[m_activeProfile].m_listCurve[i];

          temp = 0;
          m_io.GetFanTemperature(currentFanCurve->m_sondeNumber, temp);
          currentFanCurve->m_temp=temp;

          //limit the number of element for the average calcul
          if (currentFanCurve->m_tempTab.size() > (currentFanCurve->m_number_AverageTab-1))
          {
              currentFanCurve->m_tempTotal-= currentFanCurve->m_tempTab.back();
              currentFanCurve->m_tempTab.pop_back();

          }
          currentFanCurve->m_tempTab.insert(currentFanCurve->m_tempTab.begin(),temp);
          currentFanCurve->m_tempTotal+=temp;
          access = (currentFanCurve->m_tempTotal/currentFanCurve->m_tempTab.size())-currentFanCurve->m_offset_TabCurve;
          //temp is to high so we stop immediatly to search over curve and set maximum speed
          if ((access > currentFanCurve->m_fanCurve.size()-1 and access >=0) or temp >= currentFanCurve->m_highTemp or temp==0)
          {
              access = currentFanCurve->m_fanCurve.size()-1;
              stop = true;
          }
          else
              if (access < 0)
                  access = 0;

          tmpspeed = currentFanCurve->m_fanCurve[access];
          if (tmpspeed > r_fanSetting.m_fanSpeed)
              r_fanSetting.m_fanSpeed = tmpspeed;

          tmpdelay = currentFanCurve->m_lowDelay;
          if (temp > currentFanCurve->m_lowTemp)
                        r_fanSetting.m_fanDelay = 1;
          else
              if (r_fanSetting.m_fanDelay > tmpdelay)
                        r_fanSetting.m_fanDelay = tmpdelay;


          //Debug stuff
          cout<<"Fan number: " << i <<endl;
          cout<<"Temp: "<<temp<<endl;
          cout<<"Temp Total: "<<currentFanCurve->m_tempTotal<<" | Number elements: "<<currentFanCurve->m_tempTab.size()<<endl;
          cout<<"Offset: "<<currentFanCurve->m_offset_TabCurve<<endl;
          cout<<"Average Temp: "<<(currentFanCurve->m_tempTotal/currentFanCurve->m_tempTab.size())<<endl;
          cout<<"Indice: "<<access<<endl;

          i++;
    }

    return r_fanSetting;
}

void HardwareControl::SetFanSpeed(int p_speed)
{
    for (int i =0; i<m_nbFan; i++)
        m_io.SetFanSpeedPercent(i, p_speed);
}


void HardwareControl::Run()
{
  m_run = true;
  m_io.SetEnableModeSet(1);

  m_speed= 0;
  //int previousSpeed=0;
  //int nbLoopSameSpeed=0;
  FanSetting workFanSetting;

  cout<< "HardwareControl::run()"<<endl;
  while (m_run)
  {
      //cout<< "Boucle HardwareControl::run()"<<endl;
      //detect that the profile change so reset the averageTemp
      if (m_targetProfile != m_activeProfile)
      {

          m_activeProfile = m_targetProfile;
          for (size_t i = 0; i < m_profileList[m_activeProfile].m_listCurve.size(); i++ )
          {
              m_profileList[m_activeProfile].m_listCurve[i].m_tempTab.clear();
              m_profileList[m_activeProfile].m_listCurve[i].m_tempTotal = 0;

          }
      }

      workFanSetting = FoundTargetSpeed();
      m_speed = workFanSetting.m_fanSpeed;

      // do not set speed if it was the same as previous
      // i add a set every 100 loop because sometimes fan control role back to automatic if no update...
      //cout<<"NBLoop: "<<nbLoopSameSpeed<<endl;
      //cout<<"Previous Speed: "<<previousSpeed<<endl;
      //cout<<"New speed: "<<m_speed<<endl;
      //if (m_speed != previousSpeed or nbLoopSameSpeed >p_optimizeLoop )
//      {
//        cout<<"====> Detect Speed change"<<endl;
        SetFanSpeed(m_speed);
        //previousSpeed=m_speed;
        //nbLoopSameSpeed=0;
//      }
      //nbLoopSameSpeed+=1;


      //Debug stuff
      cout << "Fan Speed: "<< m_speed<<endl;
      cout << "Wait time: "<< workFanSetting.m_fanDelay<<endl<<endl;;
      sleep(workFanSetting.m_fanDelay);

      //m_thread = boost::thread(RunThread,m_ProfileList[m_activeProfile]);
      //m_thread.join();
      //sleep(1);
   }

  //cout<<"Fan at 100% during 3s"<<endl;
  //SetFanSpeed(100);
  //io.SetFanSpeedPercent(nbFan,100);
  //sleep(3);
  m_io.SetFansAuto();

}

void HardwareControl::Stop()
{
  cout<< "HardwareControl::stop()"<<endl;
  m_run=false;
 // If we do that we are locked. Need to find a solution
 // m_dbusreader.Remove_signal();
 // Not really good to kill the thread. :/
  m_thread_Monitor_Power.~thread();
  cout<< "HardwareControl::stop() END"<<endl;

}


//check that settings are correct
bool HardwareControl::CheckCurve(FanCurve * p_fanCurve)
{
    bool r_answer = true;
    // We lock to 10 values because if there is too much value temp is false
    if ( p_fanCurve->m_number_AverageTab > 10)
        p_fanCurve->m_number_AverageTab = 7;
    //Maximum temp is 100° to protect the cpu
    if ( p_fanCurve->m_highTemp > 100)
        p_fanCurve->m_highTemp = 100;
    //LowDelay could only be 1 or 2
    if (p_fanCurve->m_lowDelay > 2 or p_fanCurve->m_lowDelay < 1 )
        p_fanCurve->m_lowDelay=2;
    //The begining of the curve could not be down to 80°
    if (p_fanCurve->m_offset_TabCurve > 80)
        r_answer = false;
    //If the curve is lower then 10 values the profile is not good  ==> error
    if (p_fanCurve->m_fanCurve.size() < 10)
        r_answer = false;

    return r_answer;
}

void HardwareControl::ApplyProfile(int p_numProfile)
{
    cout<<"Apply Profile: "<<m_profileList[p_numProfile].m_name <<endl;

    m_targetProfile = p_numProfile;
    // Wait until proilfe is active before apply the cmd;
    while (m_targetProfile != m_activeProfile)
        sleep(1);

    if ( m_profileList[p_numProfile].m_cmd1 != "" )
        system(m_profileList[p_numProfile].m_cmd1.data());
    if ( m_profileList[p_numProfile].m_cmd2 != "" )
        system(m_profileList[p_numProfile].m_cmd2.data());
}

void HardwareControl::MonitorPowerSource()
{
    m_dbusreader.Prepare_signal();
    while (m_run) {
        m_dbusreader.Wait_Event();
        ApplyProfile(m_dbusreader.Is_OnBattery());
        sleep(1);

    }
}

void HardwareControl::StartPowerMonitor()
{
    m_thread_Monitor_Power=std::thread (&HardwareControl::MonitorPowerSource, this);
    m_thread_Monitor_Power.detach();

}

