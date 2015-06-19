/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing LinuxSerial2
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "LinuxSerial2.h"

/*****************************************************************************
 * Implementation for type : LinuxSerial2
 *****************************************************************************/

// Declaration of prototypes:
#ifdef __cplusplus
extern "C" {
#endif
void LinuxSerial2_LinuxSerialImpl_OnExit(int state, struct LinuxSerial2_Instance *_instance);
void LinuxSerial2_send_serial_serial_rx(struct LinuxSerial2_Instance *_instance, uint8_t b);
void LinuxSerial2_send_serial_serial_closed(struct LinuxSerial2_Instance *_instance);
void LinuxSerial2_send_serial_serial_opened(struct LinuxSerial2_Instance *_instance);
int16_t f_LinuxSerial2_open_serial(struct LinuxSerial2_Instance *_instance, char * device, uint32_t baudrate);
int16_t f_LinuxSerial2_send_byte(struct LinuxSerial2_Instance *_instance, int16_t device, uint8_t byte);
void f_LinuxSerial2_start_receiver_process(struct LinuxSerial2_Instance *_instance, int16_t device);
#ifdef __cplusplus
}
#endif

// Declaration of functions:
// Definition of function open_serial
int16_t f_LinuxSerial2_open_serial(struct LinuxSerial2_Instance *_instance, char * device, uint32_t baudrate) {
{
int result;
		struct termios port_settings;
		printf("Opening Serial device at %s...\n", device);
		result = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
		if (result < 0) {
			perror("Error opening Serial port");
		}
		else if (tcgetattr(result, &port_settings) < 0) {// try to get current options
			perror("Error opening Serial port: could not get serial port attributes");
		}
		else {
			printf("Configuring port %s...\n", device);
			switch(baudrate) {
				case 115200:
					cfsetispeed(&port_settings, B115200);    // set baud rates to 115200 ---------- Test with 57600
					cfsetospeed(&port_settings, B115200);
				break;
				
				case 57600:
					cfsetispeed(&port_settings, B57600);    // set baud rates to 115200 ---------- Test with 57600
					cfsetospeed(&port_settings, B57600);
				break;
				
				case 38400:
					cfsetispeed(&port_settings, B38400);    // set baud rates to 38400 ---------- Test with 57600
					cfsetospeed(&port_settings, B38400);
				break;
				
				case 19200:
					cfsetispeed(&port_settings, B19200);    // set baud rates to 19200 ---------- Test with 57600
					cfsetospeed(&port_settings, B19200);
				break;
				
				case 9600:
					cfsetispeed(&port_settings, B9600);    // set baud rates to 115200 ---------- Test with 57600
					cfsetospeed(&port_settings, B9600);
				break;
				
				default:
					cfsetispeed(&port_settings, B115200);    // set baud rates to 115200 ---------- Test with 57600
					cfsetospeed(&port_settings, B115200);
				break;
			}
			// 8N1
			port_settings.c_cflag &= ~PARENB;
			port_settings.c_cflag &= ~CSTOPB;
			port_settings.c_cflag &= ~CSIZE;
			port_settings.c_cflag |= CS8;
			// no flow control
			port_settings.c_cflag &= ~CRTSCTS;
			port_settings.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
			port_settings.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
			port_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
			port_settings.c_oflag &= ~OPOST; // make raw
			// see: http://unixwiz.net/techtips/termios-vmin-vtime.html
			port_settings.c_cc[VMIN] = 0;
			port_settings.c_cc[VTIME] = 20;
			if (tcsetattr(result, TCSANOW, &port_settings) < 0 ) {
				perror("Error opening Serial port: could not set serial port attributes");
			}
			sleep(1); // wait a bit
		}
return result;
}
}

// Definition of function send_byte
int16_t f_LinuxSerial2_send_byte(struct LinuxSerial2_Instance *_instance, int16_t device, uint8_t byte) {
{
int n;
		unsigned char data[1];
		data[0] = byte;
		n = write(device, data, 1);
		if (n < 0) {
			perror("Error writing to Serial device");
			return -1;
		}
		return 0;
}
}

// Fork a thread to execute the function f_LinuxSerial2_start_receiver_process

// Struct for the parameters of the function  f_LinuxSerial2_start_receiver_process
struct f_LinuxSerial2_start_receiver_process_struct {
  struct LinuxSerial2_Instance *_instance;
   int16_t device;

  pthread_mutex_t *lock;
  pthread_cond_t *cv;
};

// Definition of function start_receiver_process (executed in a separate thread)
void f_LinuxSerial2_start_receiver_process_run(struct LinuxSerial2_Instance *_instance, int16_t device)
{
  {
char buffer[INPUT_BUFFER_SIZE]; // Data read from the ESUSMS device
		int n; // used to store the results of select and read
		int i; // loop index
		while (1) {
			fd_set rdfs; // The file descriptor to wait on
			FD_ZERO( &rdfs );
			FD_SET( device, &rdfs ); // set to the esusms fd
			n = select(device+1, &rdfs, NULL, NULL, NULL); // NO Timeout here (last parameter)
			if (n < 0) {
				perror("Error waiting for incoming data from Serial device");
				break;
			}
			else if (n == 0) { // timeout
				printf("Timeout waiting for incoming data from Serial device\n");
				break;
			}
			else { // there is something to read
				printf("[receiver] rx?");
				n = read(device, &buffer, INPUT_BUFFER_SIZE * sizeof(char));
				printf(" n=<%i>\n", n);
				if (n<0) {
					perror("Error reading from Serial device");
					break;
				}
				else if (n==0) {
					printf("Nothing to read from Serial device\n"); // Should never happen unless there are too many transmission errors with wrong CRCs
					break;
				}
				else { // There are n incoming bytes in buffer
					printf("[receiver] rx! <%i>\n", n);
					for (i = 0; i<n; i++) {
						
						printf("[receiver] rx:<%i>\n", buffer[i]);
						
LinuxSerial2_send_serial_serial_rx(_instance, buffer[i]);

					}
				}
			}
		}
LinuxSerial2_send_serial_serial_closed(_instance);
}

}


void f_LinuxSerial2_start_receiver_process_proc(void * p)
{
  // Get parameters from the main thread
  struct f_LinuxSerial2_start_receiver_process_struct params = *((struct f_LinuxSerial2_start_receiver_process_struct *) p);
  
  // Unblock the main thread
  pthread_mutex_lock(params.lock);
  pthread_cond_signal(params.cv);
  pthread_mutex_unlock(params.lock);
  
  // Run the function
  //f_LinuxSerial2_start_receiver_process_run(params._instance, params.esums_device);
  f_LinuxSerial2_start_receiver_process_run(params._instance, params.device);
}

// Operation called by the runtime and forking a new thread
void f_LinuxSerial2_start_receiver_process(struct LinuxSerial2_Instance *_instance, int16_t device)
{
  // Store parameters
  struct f_LinuxSerial2_start_receiver_process_struct params;
  pthread_mutex_t lock;
  pthread_cond_t cv;
  params.lock = &lock;
  params.cv = &cv;
  params._instance = _instance;
  params.device = device;

  pthread_mutex_init(params.lock, NULL);
  pthread_cond_init(params.cv, NULL);
  //Start the new thread
  pthread_mutex_lock(params.lock);
  pthread_t thread; 
  pthread_create( &thread, NULL, f_LinuxSerial2_start_receiver_process_proc, (void*) &params);
  // Wait until it has started and read its parameters
  pthread_cond_wait(params.cv, params.lock);
  // Realease mutex
  pthread_mutex_unlock(params.lock);
}

// On Entry Actions:
void LinuxSerial2_LinuxSerialImpl_OnEntry(int state, struct LinuxSerial2_Instance *_instance) {
switch(state) {
case LINUXSERIAL2_LINUXSERIALIMPL_STATE:
_instance->LinuxSerial2_LinuxSerialImpl_State = LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE;
LinuxSerial2_LinuxSerialImpl_OnEntry(_instance->LinuxSerial2_LinuxSerialImpl_State, _instance);
break;
case LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE:
break;
default: break;
}
}

// On Exit Actions:
void LinuxSerial2_LinuxSerialImpl_OnExit(int state, struct LinuxSerial2_Instance *_instance) {
switch(state) {
case LINUXSERIAL2_LINUXSERIALIMPL_STATE:
LinuxSerial2_LinuxSerialImpl_OnExit(_instance->LinuxSerial2_LinuxSerialImpl_State, _instance);
break;
case LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:
void LinuxSerial2_handle_serial_serial_open(struct LinuxSerial2_Instance *_instance, char * device, uint32_t baudrate) {
uint8_t LinuxSerial2_LinuxSerialImpl_State_event_consumed = 0;
if (_instance->LinuxSerial2_LinuxSerialImpl_State == LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE) {
if (LinuxSerial2_LinuxSerialImpl_State_event_consumed == 0 && 1) {
{
fprintf(stdout, "[LinuxSerial] received serial_open\n");

_instance->LinuxSerial2_LinuxSerialImpl_serial_device__var = f_LinuxSerial2_open_serial(_instance, device, baudrate);
if(_instance->LinuxSerial2_LinuxSerialImpl_serial_device__var >  -1) {
fprintf(stdout, "[LinuxSerial] suceed to open\n");

f_LinuxSerial2_start_receiver_process(_instance, _instance->LinuxSerial2_LinuxSerialImpl_serial_device__var);
fprintf(stdout, "[LinuxSerial] started receiver process\n");

LinuxSerial2_send_serial_serial_opened(_instance);
fprintf(stdout, "[LinuxSerial] opened\n");

}
}
LinuxSerial2_LinuxSerialImpl_State_event_consumed = 1;
}
}
}
void LinuxSerial2_handle_serial_serial_tx(struct LinuxSerial2_Instance *_instance, uint8_t b) {
uint8_t LinuxSerial2_LinuxSerialImpl_State_event_consumed = 0;
if (_instance->LinuxSerial2_LinuxSerialImpl_State == LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE) {
if (LinuxSerial2_LinuxSerialImpl_State_event_consumed == 0 && 1) {
{
_instance->LinuxSerial2_LinuxSerialImpl_success__var = f_LinuxSerial2_send_byte(_instance, _instance->LinuxSerial2_LinuxSerialImpl_serial_device__var, b);
printf( "[LinuxSerial] wrote<%i>", b);
printf( " returns %i \n", _instance->LinuxSerial2_LinuxSerialImpl_success__var);
}
LinuxSerial2_LinuxSerialImpl_State_event_consumed = 1;
}
}
}

// Observers for outgoing messages:
void (*LinuxSerial2_send_serial_serial_rx_listener)(struct LinuxSerial2_Instance*, uint8_t)= 0x0;
void register_LinuxSerial2_send_serial_serial_rx_listener(void (*_listener)(struct LinuxSerial2_Instance*, uint8_t)){
LinuxSerial2_send_serial_serial_rx_listener = _listener;
}
void LinuxSerial2_send_serial_serial_rx(struct LinuxSerial2_Instance *_instance, uint8_t b){
if (LinuxSerial2_send_serial_serial_rx_listener != 0x0) LinuxSerial2_send_serial_serial_rx_listener(_instance, b);
}
void (*LinuxSerial2_send_serial_serial_closed_listener)(struct LinuxSerial2_Instance*)= 0x0;
void register_LinuxSerial2_send_serial_serial_closed_listener(void (*_listener)(struct LinuxSerial2_Instance*)){
LinuxSerial2_send_serial_serial_closed_listener = _listener;
}
void LinuxSerial2_send_serial_serial_closed(struct LinuxSerial2_Instance *_instance){
if (LinuxSerial2_send_serial_serial_closed_listener != 0x0) LinuxSerial2_send_serial_serial_closed_listener(_instance);
}
void (*LinuxSerial2_send_serial_serial_opened_listener)(struct LinuxSerial2_Instance*)= 0x0;
void register_LinuxSerial2_send_serial_serial_opened_listener(void (*_listener)(struct LinuxSerial2_Instance*)){
LinuxSerial2_send_serial_serial_opened_listener = _listener;
}
void LinuxSerial2_send_serial_serial_opened(struct LinuxSerial2_Instance *_instance){
if (LinuxSerial2_send_serial_serial_opened_listener != 0x0) LinuxSerial2_send_serial_serial_opened_listener(_instance);
}

