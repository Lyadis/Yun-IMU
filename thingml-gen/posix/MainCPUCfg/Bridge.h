/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing Bridge
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef Bridge_H_
#define Bridge_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : Bridge
 *****************************************************************************/

// Definition of the instance stuct:
struct Bridge_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int Bridge_BridgeChart_State;
int Bridge_BridgeChart_Active_State;
// Variables for the properties of the instance
uint8_t Bridge_START_BYTE__var;
uint8_t Bridge_STOP_BYTE__var;
uint8_t Bridge_ESCAPE_BYTE__var;
uint8_t Bridge_Buffer__var[64];
uint8_t Bridge_MsgSize__var;
int Bridge_bps__var;
};

// Declaration of prototypes outgoing messages:
void Bridge_BridgeChart_OnEntry(int state, struct Bridge_Instance *_instance);
void Bridge_handle_Serial1_CommandStop(struct Bridge_Instance *_instance);
void Bridge_handle_Serial1_CommandStart(struct Bridge_Instance *_instance);
void Bridge_handle_serial_serial_opened(struct Bridge_Instance *_instance);
void Bridge_handle_serial_serial_rx(struct Bridge_Instance *_instance, uint8_t b);
void Bridge_handle_WSService_CMDStop(struct Bridge_Instance *_instance);
void Bridge_handle_WSService_CMDStart(struct Bridge_Instance *_instance);
// Declaration of callbacks for incomming messages:
void register_Bridge_send_Serial1_Measure_listener(void (*_listener)(struct Bridge_Instance*, float));
void register_Bridge_send_Serial1_CPUBridgeReady_listener(void (*_listener)(struct Bridge_Instance*));
void register_Bridge_send_serial_serial_open_listener(void (*_listener)(struct Bridge_Instance*, char *, uint32_t));
void register_Bridge_send_serial_serial_close_listener(void (*_listener)(struct Bridge_Instance*));
void register_Bridge_send_serial_serial_tx_listener(void (*_listener)(struct Bridge_Instance*, uint8_t));
void register_Bridge_send_WSService_WSStart_listener(void (*_listener)(struct Bridge_Instance*, uint16_t));
void register_Bridge_send_WSService_WSStop_listener(void (*_listener)(struct Bridge_Instance*));
void register_Bridge_send_WSService_sendM_listener(void (*_listener)(struct Bridge_Instance*, long));

// Definition of the states:
#define BRIDGE_BRIDGECHART_STATE 0
#define BRIDGE_BRIDGECHART_INIT_STATE 1
#define BRIDGE_BRIDGECHART_ACTIVE_STATE 2
#define BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE 3
#define BRIDGE_BRIDGECHART_ACTIVE_READING_STATE 4
#define BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE 5
#define BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE 6



#ifdef __cplusplus
}
#endif

#endif //Bridge_H_