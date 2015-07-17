/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing HTTPServer
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef HTTPServer_H_
#define HTTPServer_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : HTTPServer
 *****************************************************************************/


// BEGIN: Code from the c_header annotation HTTPServer

//#include <platform.h>
#include <microhttpd.h>

#define PAGE "<html><head><title>libmicrohttpd demo</title></head><body>Query string for &quot;%s&quot; was &quot;%s&quot;</body></html>"


// END: Code from the c_header annotation HTTPServer

// Definition of the instance stuct:
struct HTTPServer_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int HTTPServer_ServerChart_State;
// Variables for the properties of the instance
uint16_t HTTPServer_serverPort__var;
};

// Declaration of prototypes outgoing messages:
void HTTPServer_ServerChart_OnEntry(int state, struct HTTPServer_Instance *_instance);
// Declaration of callbacks for incomming messages:
void register_HTTPServer_send_bridge_CommandStop_listener(void (*_listener)(struct HTTPServer_Instance*));
void register_HTTPServer_send_bridge_CommandStart_listener(void (*_listener)(struct HTTPServer_Instance*));

// Definition of the states:
#define HTTPSERVER_SERVERCHART_STATE 0
#define HTTPSERVER_SERVERCHART_INIT_STATE 1



#ifdef __cplusplus
}
#endif

#endif //HTTPServer_H_