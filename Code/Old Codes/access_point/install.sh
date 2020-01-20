#!/bin/bash
echo "Raspbeery Pi 3 Access Point Creation"
echo "====================================="
sudo apt-get update
echo "Network SSID:" 
read SSID                                          #SSID which needs to be created
echo "Paasword:"
read Pass                                          #Passphrase

#Installing required softwares
sudo apt install dnsmasq hostapd
sudo systemctl stop dnsmasq
sudo systemctl stop hostapd
x=/etc/dhcpcd.conf
sudo chmod -R 777 /etc/dhcpcd.conf
echo "interface wlan0" >> $x
echo  "static ip_address=192.168.4.1/24" >> $x
echo   "nohook wpa_supplicant" >> $x
sudo service dhcpcd restart
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
x=/etc/dnsmasq.conf
echo "interface=wlan0      # Use the require wireless interface - usually wlan0" >> $x
echo "dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h" >> $x
sudo systemctl reload dnsmasq
x=/etc/hostapd/hostapd.conf
sudo chmod -R 777 /etc/hostapd/hostapd.conf
echo "interface=wlan0" >> $x
echo "driver=nl80211" >> $x
echo "ssid=$SSID ">> $x
echo "hw_mode=g" >> $x
echo "channel=7" >> $x
echo "wmm_enabled=0" >> $x
echo "macaddr_acl=0" >> $x
echo "auth_algs=1" >> $x
echo "ignore_broadcast_ssid=0" >> $x
echo "wpa=2" >> $x
echo "wpa_passphrase=$Pass" >> $x
echo "wpa_key_mgmt=WPA-PSK" >> $x
echo "wpa_pairwise=TKIP" >> $x
echo "rsn_pairwise=CCMP" >> $x
x=/etc/default/hostapd
sudo chmod -R 777 /etc/default/hostapd
sed -i '10s/#DAEMON_CONF=""/DAEMON_CONF="/etc/hostapd/hostapd.conf"/' /etc/default/hostapd
sudo systemctl unmask hostapd
sudo systemctl enable hostapd
sudo systemctl start hostapd
sudo systemctl status hostapd
sudo systemctl status dnsmasq
sudo chmod -R 777 /etc/sysctl.conf
sed -i '28s/#net.ipv4.ip_forward=1/net.ipv4.ip_forward=1"/' /etc/sysctl.conf
sudo iptables -t nat -A  POSTROUTING -o eth0 -j MASQUERADE
sudo chmod -R 777 /etc/rc.local
sudo head -n -1 /etc/rc.local > /etc/temp.local ; mv /etc/temp.local /etc/rc.local
x=/etc/rc.local
echo "iptables-save > /etc/iptables.ipv4.nat" >> $x
echo "exit 0" >> $x
