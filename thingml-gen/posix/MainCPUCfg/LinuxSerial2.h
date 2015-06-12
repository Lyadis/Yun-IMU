/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing LinuxSerial2
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef LinuxSerial2_H_
#define LinuxSerial2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : LinuxSerial2
 *****************************************************************************/


// BEGIN: Code from the c_header annotation LinuxSerial2

#include <string.h> // string function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <time.h> // time calls
#define TIMEOUT 10 // timeout waiting for messages from the serial device
#define INPUT_BUFFER_SIZE 128 // for possible future optimizations
// END: Code from the c_header annotation LinuxSerial2

// Definition of the instance stuct:
struct LinuxSerial2_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int LinuxSerial2_LinuxSerialImpl_State;
// Variables for the properties of the instance
int16_t LinuxSerial2_LinuxSerialImpl_serial_device__var;
int16_t LinuxSerial2_LinuxSerialImpl_success__var;
};

// Declaration of prototypes outgoing messages:
void LinuxSerial2_LinuxSerialImpl_OnEntry(int state, struct LinuxSerial2_Instance *_instance);
void LinuxSerial2_handle_serial_serial_tx(struct LinuxSerial2_Instance *_instance, uint8_t b);
void LinuxSerial2_handle_serial_serial_open(struct LinuxSerial2_Instance *_instance, char * device, uint32_t baudrate);
// Declaration of callbacks for incomming messages:
void register_LinuxSerial2_send_serial_serial_rx_listener(void (*_listener)(struct LinuxSerial2_Instance*, uint8_t));
void register_LinuxSerial2_send_serial_serial_closed_listener(void (*_listener)(struct LinuxSerial2_Instance*));
void register_LinuxSerial2_send_serial_serial_opened_listener(void (*_listener)(struct LinuxSerial2_Instance*));

// Definition of the states:
#define LINUXSERIAL2_LINUXSERIALIMPL_STATE 0
#define LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE 1



#ifdef __cplusplus
}
#endif

#endif //LinuxSerial2_H_