#!/bin/bash
#
# Make sure we have all our pre-requisites for a new SD-Card install.
# If you are cutting your own SD card, you don't need this process
#
sudo apt-get update
sudo apt-get upgrade -y
sudo rpi-update
sleep 30
sudo reboot
