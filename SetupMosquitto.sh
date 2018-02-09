sudo apt-get update
sudo apt-get install -y mosquitto
sudo apt-get install -y mosquitto-clients
sudo apt-get install -y libmosquitto
sudo apt-get install -y libmosquitto-dev
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/hieptd/SourceCode/SMB/Demo/lib:/home/hieptd/SourceCode/SMB/Demo/lib/cpp
