#cp build/monitor.uf2 /media/$USER/RPI-RP2
sudo picotool load -f build/monitor.uf2
sudo picotool reboot -f