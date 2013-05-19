#!/bin/sh
# 
# single-run script initializing beaglebone for beer telemetry program
#
# please run script once (as root)

mkdir /var/www/logs
chmod a+rw /var/www/logs

update-rc.d beertelemetry.sh defaults