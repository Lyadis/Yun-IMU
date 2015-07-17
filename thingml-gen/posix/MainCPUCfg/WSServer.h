/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing WSServer
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef WSServer_H_
#define WSServer_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : WSServer
 *****************************************************************************/


// BEGIN: Code from the c_header annotation WSServer

#include <lws_config.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>


#include <syslog.h>
#include <sys/time.h>
#include <unistd.h>

#include <libwebsockets.h>




// END: Code from the c_header annotation WSServer

// Definition of the instance stuct:
struct WSServer_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int WSServer_ServerChart_State;
// Variables for the properties of the instance
long WSServer_M__var;
uint16_t WSServer_serverPort__var;
uint8_t WSServer_Running__var;
};

// Declaration of prototypes outgoing messages:
void WSServer_ServerChart_OnEntry(int state, struct WSServer_Instance *_instance);
void WSServer_handle_WSService_WSStart(struct WSServer_Instance *_instance, uint16_t Port);
void WSServer_handle_WSService_WSStop(struct WSServer_Instance *_instance);
void WSServer_handle_WSService_sendM(struct WSServer_Instance *_instance, long m);
// Declaration of callbacks for incomming messages:
void register_WSServer_send_WSService_WSStarted_listener(void (*_listener)(struct WSServer_Instance*));
void register_WSServer_send_WSService_CMDStop_listener(void (*_listener)(struct WSServer_Instance*));
void register_WSServer_send_WSService_CMDStart_listener(void (*_listener)(struct WSServer_Instance*));

// Definition of the states:
#define WSSERVER_SERVERCHART_STATE 0
#define WSSERVER_SERVERCHART_IDLE_STATE 1
#define WSSERVER_SERVERCHART_RUNNING_STATE 2



#ifdef __cplusplus
}
#endif

#endif //WSServer_H_