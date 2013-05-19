#include <stdio.h>
#include <unistd.h>

/* Daemon which lols around in the background recording the telemetry values once per [update rate]
 * Currently updates: temperature
 */

#define UPDATE_RATE_SEC 1

const char temp_n1_log_path[] = "/var/www/logs/temp_n1.csv";
const char adc2_path[] = "/sys/devices/ocp.2/helper.15/AIN2";

int getTemp(float *temperature);

int main(int argc, char **argv)
{
	FILE *fp;
	float temp_n1;

	for(;;) {
		getTemp(&temp_n1);

		fp = fopen(temp_n1_log_path, "a");
		if(fp == NULL) {
			printf("Unable to open temp_n1 log file: %s for appending, exiting\n", temp_n1_log_path);
			return 1;
		}
		fprintf(fp, "%.2f,\n", temp_n1);
		fclose(fp);
		fp = NULL;

		sleep(1);
	}

	return 0;
}

int getTemp(float *temperature)
{
	FILE *fp;
	long adc2_v;
	float tmp;

	if (temperature == NULL) {
		printf("Passed NULL pointer to function 'getTemp', returning\n");
		return -1;
	}

	fp = fopen(adc2_path, "r");
	if(fp == NULL) {
		printf("Unable to open adc IO file: %s for reading, exiting\n", adc2_path);
		return -1;
	}

	fscanf(fp, "%ld", &adc2_v);
	fclose(fp);

	tmp = ((float)adc2_v * 2.7717); //account for voltage divider
	*temperature = (tmp/10.00) - 273.15; //10mv/K

	return 0;
}