#include "hardwarecontrol.h"


HardwareControl::HardwareControl()
{

}


HardwareProfile HardwareControl::GenerateDefaultProfile(string p_name)
{
   HardwareProfile defaultProfile;
   FanCurve defaultFanCurve;
   defaultProfile.m_name=p_name;
   defaultFanCurve.m_Offset_TabCurve=30;
   defaultFanCurve.m_HighTemp=92;
   defaultFanCurve.m_LowDelay=2;
   defaultFanCurve.m_LowTemp=72;
   defaultFanCurve.m_Number_AverageTab=7;

   #pragma region Curve {
     // Minimal temp = 30°
     //30°
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);

     //40°
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);

     //50°
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);
     defaultFanCurve.m_FanCurve.push_back(20);

     //60°
     defaultFanCurve.m_FanCurve.push_back(30);
     defaultFanCurve.m_FanCurve.push_back(30);
     defaultFanCurve.m_FanCurve.push_back(30);
     defaultFanCurve.m_FanCurve.push_back(30);
     defaultFanCurve.m_FanCurve.push_back(30);
     defaultFanCurve.m_FanCurve.push_back(40);
     defaultFanCurve.m_FanCurve.push_back(40);
     defaultFanCurve.m_FanCurve.push_back(40);
     defaultFanCurve.m_FanCurve.push_back(40);
     defaultFanCurve.m_FanCurve.push_back(40);

     //70°
     defaultFanCurve.m_FanCurve.push_back(50);
     defaultFanCurve.m_FanCurve.push_back(50);
     defaultFanCurve.m_FanCurve.push_back(50);
     defaultFanCurve.m_FanCurve.push_back(50);
     defaultFanCurve.m_FanCurve.push_back(50);
     defaultFanCurve.m_FanCurve.push_back(60);
     defaultFanCurve.m_FanCurve.push_back(60);
     defaultFanCurve.m_FanCurve.push_back(60);
     defaultFanCurve.m_FanCurve.push_back(60);
     defaultFanCurve.m_FanCurve.push_back(60);

     //80°
     defaultFanCurve.m_FanCurve.push_back(80);
     defaultFanCurve.m_FanCurve.push_back(80);
     defaultFanCurve.m_FanCurve.push_back(80);
     defaultFanCurve.m_FanCurve.push_back(80);
     defaultFanCurve.m_FanCurve.push_back(80);
     defaultFanCurve.m_FanCurve.push_back(100);
     defaultFanCurve.m_FanCurve.push_back(100);
     defaultFanCurve.m_FanCurve.push_back(100);
     defaultFanCurve.m_FanCurve.push_back(100);
     defaultFanCurve.m_FanCurve.push_back(100);
       #pragma endregion }

    defaultProfile.m_ListCurve.push_back(defaultFanCurve);


    return defaultProfile;

}


HardwareProfile HardwareControl::LoadProfile(string p_profile)
{
    m_dedicatedGpu=false;
    string key;
    vector <string> target;

    YAML_CPP_API::YAML::Node m_config = YAML_CPP_API::YAML::LoadFile(p_profile);

    HardwareProfile Profile;
    Profile.m_name = m_config["ProfileName"].as<std::string>();
    Profile.m_Cmd1 = m_config["Cmd1"].as<std::string>();
    Profile.m_Cmd2 = m_config["Cmd2"].as<std::string>();
    m_dedicatedGpu = m_config["Dedicated_GPU"].as<bool>();

    target.push_back("CPU_");
    if(m_dedicatedGpu)
        target.push_back("GPU_");

    FanCurve Curve;
    for (std::size_t i=0; i<target.size(); i++)
    {
        key=target[i];
        key.append("Sonde");
        Curve.m_SondeNumber = m_config[key].as<std::int32_t>()-1;

        key=target[i];
        key.append("LowDelay");
        Curve.m_LowDelay=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("LowTemp");
        Curve.m_LowTemp=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("HighTemp");
        Curve.m_HighTemp=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("Number_AverageTab");
        Curve.m_Number_AverageTab=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("Offset_TabCurve");
        Curve.m_Offset_TabCurve=m_config[key].as<std::int32_t>();

        key=target[i];
        key.append("FanCurve");
        int size= m_config[key].size();
        for (int k = 0;k < size;k++)
        {
            Curve.m_FanCurve.push_back(m_config[key][k].as<std::int32_t>());
            //cout<<Curve.m_FanCurve[k]<<endl;
        }
        //we add 100% at the end to be sure that it will be 100% on high temp;
        Curve.m_FanCurve.push_back(100);
        Curve.m_temp = 0;
        Curve.m_tempTotal = 0;
        Profile.m_ListCurve.push_back(Curve);
        if (checkCurve(&Curve))
            m_ProfileList.push_back(Profile);
    }
    //m_config=NULL;
    return Profile;
}

bool HardwareControl::initialize(string p_directory, string p_power, string p_battery)
{
    bool initialize_correct=true;
    //Get the number of the fan
    io.GetNumberFans(m_nbFan);
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
        initialize_correct = false;

    }

    //battery
    try
        {
            LoadProfile(p_battery);

        }
        catch ( const YAML::Exception ex)
        {
            cout << "Error: "<< p_battery<< " "<< ex.what()<<endl;
            initialize_correct=false;
        }

    if (initialize_correct)
    {
        cout<<"Profile: "<<m_ProfileList[0].m_name<<endl;
        cout<<"Profile: "<<m_ProfileList[1].m_name<<endl;
        if (m_dbusreader.connect())
        {
            m_activeProfile=m_dbusreader.is_OnBattery();
            m_targetProfile=m_activeProfile;
            applyProfile(m_activeProfile);
        }
        //dbus connnexion pb
        else
        {
                m_activeProfile=0;
                m_targetProfile=m_activeProfile;
                applyProfile(m_activeProfile);
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
    return initialize_correct;
}

FanSetting HardwareControl::FoundTargetSpeed()
{
    FanSetting returnFanSetting;
    returnFanSetting.m_FanDelay=99;
    returnFanSetting.m_FanSpeed=0;
    int temp = 0;
    int tmpspeed = 0;
    int tmpdelay = 0;
    unsigned long access = 0;
    bool stop = false;
    int i = 0;
    int size = m_ProfileList[m_activeProfile].m_ListCurve.size();
    FanCurve * currentFanCurve;
    while (i < size  and !stop)
    {
          //For easy access
          currentFanCurve = &m_ProfileList[m_activeProfile].m_ListCurve[i];

          temp = 0;
          io.GetFanTemperature(currentFanCurve->m_SondeNumber, temp);
          currentFanCurve->m_temp=temp;

          //limit the number of element for the average calcul
          if (currentFanCurve->m_TempTab.size() > (currentFanCurve->m_Number_AverageTab-1))
          {
              currentFanCurve->m_tempTotal-= currentFanCurve->m_TempTab.back();
              currentFanCurve->m_TempTab.pop_back();

          }
          currentFanCurve->m_TempTab.insert(currentFanCurve->m_TempTab.begin(),temp);
          currentFanCurve->m_tempTotal+=temp;
          access = (currentFanCurve->m_tempTotal/currentFanCurve->m_TempTab.size())-currentFanCurve->m_Offset_TabCurve;
          //temp is to high so we stop immediatly
          if ((access > currentFanCurve->m_FanCurve.size()-1 and access >=0) or temp >= currentFanCurve->m_HighTemp or temp==0)
          {
              access = currentFanCurve->m_FanCurve.size()-1;
              stop = true;
          }
          else
              if (access < 0)
                  access = 0;

          tmpspeed = currentFanCurve->m_FanCurve[access];
          if (tmpspeed > returnFanSetting.m_FanSpeed)
              returnFanSetting.m_FanSpeed = tmpspeed;

          tmpdelay = currentFanCurve->m_LowDelay;
          if (temp > currentFanCurve->m_LowTemp)
                        returnFanSetting.m_FanDelay = 1;
          else
              if (returnFanSetting.m_FanDelay > tmpdelay)
                        returnFanSetting.m_FanDelay = tmpdelay;


          //Debug stuff
          cout<<"Fan number: " << i <<endl;
          cout<<"Temp: "<<temp<<endl;
          cout<<"Temp Total: "<<currentFanCurve->m_tempTotal<<" | Number elements: "<<currentFanCurve->m_TempTab.size()<<endl;
          cout<<"Offset: "<<currentFanCurve->m_Offset_TabCurve<<endl;
          cout<<"Average Temp: "<<(currentFanCurve->m_tempTotal/currentFanCurve->m_TempTab.size())<<endl;
          cout<<"Indice: "<<access<<endl;

          i++;
    }

    return returnFanSetting;
}

void HardwareControl::SetFanSpeed(int p_speed)
{
    for (int i =0; i<m_nbFan; i++)
        io.SetFanSpeedPercent(i, p_speed);
}


void HardwareControl::run(int p_optimizeLoop)
{
  m_run = true;
  io.SetEnableModeSet(1);
  //int nbFan = 0;
  m_speed= 0;
  int previousSpeed=0;
  int nbLoopSameSpeed=0;
  FanSetting workFanSetting;

  cout<< "HardwareControl::run()"<<endl;
  while (m_run)
  {
      //cout<< "Boucle HardwareControl::run()"<<endl;
      //detect that the profile change so reset the averageTemp
      if (m_targetProfile != m_activeProfile)
      {
          cout<<"Detect Profile Change"<<endl;
          m_activeProfile = m_targetProfile;
          for (size_t i = 0; i < m_ProfileList[m_activeProfile].m_ListCurve.size(); i++ )
          {
              m_ProfileList[m_activeProfile].m_ListCurve[i].m_TempTab.clear();
              m_ProfileList[m_activeProfile].m_ListCurve[i].m_tempTotal = 0;

          }
      }

       /*
      io.GetFanTemperature(nbFan, m_temp);

      if (m_tempTab.size() > m_ProfileList[m_activeProfile].m_Number_AverageTab)
      {
          m_tempTotal-= m_tempTab.back();
          m_tempTab.pop_back();

      }
      m_tempTab.insert(m_tempTab.begin(),m_temp);
      m_tempTotal+=m_temp;
      access=(m_tempTotal/m_tempTab.size())-m_ProfileList[m_activeProfile].m_Offset_TabCurve;
      if ((access > m_ProfileList[m_activeProfile].m_FanCurve.size()-1 and access >=0) or m_temp >= m_ProfileList[m_activeProfile].m_HighTemp )
          access = m_ProfileList[m_activeProfile].m_FanCurve.size()-1;
      else
          if (access < 0)
              access = 0;

      m_speed=m_ProfileList[m_activeProfile].m_FanCurve[access];
      */
      workFanSetting = FoundTargetSpeed();
      m_speed = workFanSetting.m_FanSpeed;
      // do not set speed if it was the same as previous
      // i add a set every 100 loop because sometimes fan control role back to automatic if no update...
      //cout<<"NBLoop: "<<nbLoopSameSpeed<<endl;
      //cout<<"Previous Speed: "<<previousSpeed<<endl;
      //cout<<"New speed: "<<m_speed<<endl;
      if (m_speed != previousSpeed or nbLoopSameSpeed >p_optimizeLoop )
      {
        cout<<"====> Detect Speed change"<<endl;
        SetFanSpeed(m_speed);
        //io.SetFanSpeedPercent(nbFan, m_speed);
        //io.SetFanSpeedPercent(1, m_speed);
        previousSpeed=m_speed;
        nbLoopSameSpeed=0;
      }
      nbLoopSameSpeed+=1;

      /*
      if (m_temp > m_ProfileList[m_activeProfile].m_LowTemp )
          delay = 1;
      else
          delay = m_ProfileList[m_activeProfile].m_LowDelay;
       */

      //Debug stuff
 /*     cout << "Temp: "<< m_temp  <<endl;
      cout << "Temp Totale: "<< m_tempTotal<<endl;
      cout << "Temp Moyenne: "<< m_tempTotal/m_tempTab.size()<<endl;
      cout << "Temp Indice: " << access <<endl;
      cout << "Fan Speed: "<< m_speed<<endl;
      cout << "Wait time: "<< delay<<endl<<endl;; */
      cout << "Fan Speed: "<< m_speed<<endl;
      cout << "Wait time: "<< workFanSetting.m_FanDelay<<endl<<endl;;
      sleep(workFanSetting.m_FanDelay);

      //m_thread = boost::thread(RunThread,m_ProfileList[m_activeProfile]);
      //m_thread.join();
      //sleep(1);
   }

  cout<<"Fan at 100% during 3s"<<endl;
  SetFanSpeed(100);
  //io.SetFanSpeedPercent(nbFan,100);
  sleep(3);
  io.SetFansAuto();

}

void HardwareControl::stop()
{
  cout<< "HardwareControl::stop()"<<endl;
  m_run=false;
  m_thread_Monitor_Power.~thread();
  m_dbusreader.remove_signal();
}


//check that settings are correct
bool HardwareControl::checkCurve(FanCurve * p_fanCurve)
{
    bool answer = true;
    // We lock to 10 values because if there is too much value temp is false
    if ( p_fanCurve->m_Number_AverageTab > 10)
        p_fanCurve->m_Number_AverageTab = 7;
    //Maximum temp is 100° to protect the cpu
    if ( p_fanCurve->m_HighTemp > 100)
        p_fanCurve->m_HighTemp = 100;
    //LowDelay could only be 1 or 2
    if (p_fanCurve->m_LowDelay > 2 or p_fanCurve->m_LowDelay < 1 )
        p_fanCurve->m_LowDelay=2;
    //The begining of the curve could not be down to 80°
    if (p_fanCurve->m_Offset_TabCurve > 80)
        answer = false;
    //If the curve is lower then 10 values the profile is not good  ==> error
    if (p_fanCurve->m_FanCurve.size() < 10)
        answer = false;

    return answer;
}

void HardwareControl::applyProfile(int p_numProfile)
{
    m_targetProfile = p_numProfile;
    // Wait until proilfe is active before apply the cmd;
    while (m_targetProfile != m_activeProfile)
        sleep(1);

    if ( m_ProfileList[p_numProfile].m_Cmd1 != "" )
        system(m_ProfileList[p_numProfile].m_Cmd1.data());
    if ( m_ProfileList[p_numProfile].m_Cmd2 != "" )
        system(m_ProfileList[p_numProfile].m_Cmd2.data());
}

void HardwareControl::monitorPowerSource()
{
    m_dbusreader.prepare_signal();
    while (m_run) {
        m_dbusreader.wait_Event();
        applyProfile(m_dbusreader.is_OnBattery());
        sleep(1);

    }
}

void HardwareControl::startPowerMonitor()
{
    m_thread_Monitor_Power=std::thread (&HardwareControl::monitorPowerSource, this);
    m_thread_Monitor_Power.detach();

}

