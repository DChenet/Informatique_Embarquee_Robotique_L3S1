typedef struct {
	char const *name;
	int desc;
}serial_com;

serial_com newSerial_Com();
int msleep(long msec);
serial_com * serial_open(serial_com * sc);
serial_com * serial_close(serial_com * sc);
void serial_read(serial_com sc, char* buf);
void serial_write(serial_com sc, const char *message);