# TCD_COMMUNITY
Daemon for controling Fan on Tuxedo notebook (replace TCD nodejs from tuxedo)

How to use it?

I) Compile or download compiled package from https://github.com/sleepingtux/TCD_COMMUNITY_PACKAGE

II) make a profile for your computer. Take a look of some exemple in https://github.com/sleepingtux/TCD_COMMUNITY_PACKAGE \
  You should have a config file tcd_config.yaml near the binary. \
  In this file, you should configure: \
  Directory_Profile: "profile" ==> if the directory "profile" is near the binary or "/home/user/profile" if you put it on a directory "profile" in your home for exemple \
  Profile_Battery: "pulse_battery.yaml" ==> name of the file that contain the profile for battery \
  Profile_Power: "pulse_power.yaml" ==> name of the file that contain the profile for ac \
  IF you got a dedicated gpu, dont forger to add a GPU Curve!!! 
  
III) Install tuxedo-keyboard (it's needed to use it)  

IV) you could test the settings with launching in root ./TCD_COMMUNITY \
TAKE A LOOKS OF THE TEMPERATURE!!!! Before forget it in background.

V) If all is ok, make a service to launch it on start. \
For exemple here is my systemd service: \
[unit] \
Description=TCD Community \
[Service] \
Type=simple \
WorkingDirectory=/opt/TCD_Community \
ExecStart=/opt/TCD_Community/TCD_COMMUNITY \
StandardOutput=syslog \
StandardError=syslog \
SyslogIdentifier=TCD_Community \
User=root \
Group=root \
[Install] \
WantedBy=multi-user.target
