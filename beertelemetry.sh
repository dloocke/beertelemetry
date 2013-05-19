#!/bin/sh
### BEGIN INIT INFO
# Provides:          skeleton
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: init script for functionality required by beertelemetry prgm
# Description:    
# includes:
#	initialization of ADC2 I/O
# please copy to /etc/init.d/ directory
# must be run as root user
### END INIT INFO

# Carry out specific functions when asked to by the system
case "$1" in
  start)
    echo cape-bone-iio > /sys/devices/bone_capemgr.9/slots
    ;;
  stop)
    # no-op (maybe remove ADC enable?)
    ;;
  *)
    echo "Usage: /etc/init.d/beertelemetry {start|stop}"
    exit 1
    ;;
esac

exit 0
