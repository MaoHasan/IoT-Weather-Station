# IoT-Weather-Station
Data logging with google spread sheets, implementing a weather station concept using Temboo platform.

## Remember to change the followings:
- AccountName: TembooAccount.h
- AppKeyName: TembooAccount.h
- AppKey: TembooAccount.h
- City: main .ino file
- RefreshTocken: main .ino file
- ClientSecret: main .ino file
- ClientID: main .ino file
- SpreadsheetID: main .ino file

Note that you can get all these keys from google api credentials and Temboo google's initial, final and sheets settings.

## Set the time zone of Linux OpenWRT Yun OS:
- Login to your Arduino using SSH
- Type the following in your terminal
```
uci set system.@system[0].zonename='Asia/Muscat'
uci set system.@system[0].timezone='GST-4'
uci commit system
```
- Reboot your arduino
```
> reboot

```

__NOTE:__ To get your city's time zone [CLICK HERE](http://famschmid.net/timezones.html) 

__MORE INFO SOON__
