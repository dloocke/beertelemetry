#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

/* Daemon which lols around in the background recording the telemetry values once per [update rate]
 * Currently updates: temperature
 */

#define UPDATE_RATE_SEC 1

const char temp_log_path[] = "/var/www/logs/temp_n1.csv";
const char adc2_path[] = "/sys/devices/ocp.2/helper.14/AIN2";
const char uart_port[] = "/dev/ttyO5";

int getTemp(float *temperature);
int logTempToFile(float temperature);
int initializeUART(int *fd);

int main(int argc, char **argv)
{
		int ret;
        float temp_n1;
        int fd;

        ret = initializeUART(&fd);
        if(ret < 0) {
        	fprintf(stdout, "Failed to initialize uart, exiting\n");
        	exit(1);
        }

        for(;;) {
            getTemp(&temp_n1);
            logTempToFile(temp_n1);

            char byte_out[4] = {0x30, 0x30, 0x30, 0x30};
            write(fd, byte_out, strlen(byte_out));

            sleep(UPDATE_RATE_SEC);
        }

        return 0;
}

int getTemp(float *temperature)
{
        FILE *fp;
        long adc2_v;
        float tmp;

        if (temperature == NULL) {
                fprintf(stdout, "Passed NULL pointer to function 'getTemp', returning\n");
                return -1;
        }

        fp = fopen(adc2_path, "r");
        if(fp == NULL) {
                fprintf(stdout, "Unable to open adc IO file: %s for reading, returning\n", adc2_path);
                return -1;
        }

        fscanf(fp, "%ld", &adc2_v);
        fclose(fp);

        tmp = ((float)adc2_v * 2.7717); //account for voltage divider
        *temperature = (tmp/10.00) - 273.15; //10mv/K

        return 0;
}

int logTempToFile(float temperature)
{
    FILE *fp;

    fp = fopen(temp_log_path, "a");
    if(fp == NULL) {
            printf("Unable to open temp log file: %s for appending, returning\n", temp_log_path);
            return -1;
    }
    fprintf(fp, "%.2f,\n", temperature);
    fclose(fp);
    fp = NULL;

    return 0;
}

int initializeUART(int *fd)
{
	int ret, fdtmp;
	struct termios uart6;

	fprintf(stdout, "Initializing uart\n");

    fdtmp = open(uart_port, O_WRONLY | O_NOCTTY | O_NDELAY);
    if(fdtmp < 0) {
    	fprintf(stdout, "Failed to open %s, returning\n", uart_port);
    	return -1;
    }

    ret = tcgetattr(fdtmp, &uart6);
    if(ret < 0) {
    	fprintf(stdout, "Could not get attributes of %s, returning\n", uart_port);
    	return -1;
    }

    ret = cfsetospeed(&uart6, B9600);
    if(ret < 0) {
		fprintf(stdout, "Could not set baud rate to 9600, returning\n");
		return -1;
    } else {
    	fprintf(stdout, "Baud rate set to 9600\n");
    }

    uart6.c_iflag = 0;
	uart6.c_oflag = 0;
	uart6.c_lflag = 0;
	tcsetattr(fdtmp, TCSANOW, &uart6);

    *fd = fdtmp;

	return 0;
}