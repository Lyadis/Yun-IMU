/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *      Implementation for Application MainCPUCfg
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <pthread.h>
#include "thingml_typedefs.h"
#include "runtime.h"
#include "HTTPServer.h"
#include "Bridge.h"
#include "LinuxSerial2.h"


// NO C_HEADERS Annotation


/*****************************************************************************
 * Definitions for configuration : MainCPUCfg
 *****************************************************************************/

//Declaration of instance variables
struct HTTPServer_Instance MainCPUCfg_H_var;
struct LinuxSerial2_Instance MainCPUCfg_serial1_var;
struct Bridge_Instance MainCPUCfg_B_var;

// Enqueue of messages Bridge::Serial1::CPUBridgeReady
void enqueue_Bridge_send_Serial1_CPUBridgeReady(struct Bridge_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (1 >> 8) & 0xFF );
_fifo_enqueue( 1 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
fifo_unlock_and_notify();
}
// Enqueue of messages Bridge::Serial1::Measure
void enqueue_Bridge_send_Serial1_Measure(struct Bridge_Instance *_instance, float m){
fifo_lock();
if ( fifo_byte_available() > 8 ) {

_fifo_enqueue( (2 >> 8) & 0xFF );
_fifo_enqueue( 2 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter m
long * l = (long *) &m;
_fifo_enqueue((*l>>24) & 0xFF);
_fifo_enqueue((*l>>16) & 0xFF);
_fifo_enqueue((*l>>8) & 0xFF);
_fifo_enqueue(*l & 0xFF);
}
fifo_unlock_and_notify();
}
// Enqueue of messages HTTPServer::bridge::CommandStart
void enqueue_HTTPServer_send_bridge_CommandStart(struct HTTPServer_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (3 >> 8) & 0xFF );
_fifo_enqueue( 3 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
fifo_unlock_and_notify();
}
// Enqueue of messages HTTPServer::bridge::CommandStop
void enqueue_HTTPServer_send_bridge_CommandStop(struct HTTPServer_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (4 >> 8) & 0xFF );
_fifo_enqueue( 4 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
fifo_unlock_and_notify();
}

// Dispatch for messages LinuxSerial2::serial::serial_closed
void dispatch_LinuxSerial2_send_serial_serial_closed(struct LinuxSerial2_Instance *_instance){
if (_instance == &MainCPUCfg_serial1_var) {
}
}
// Dispatch for messages LinuxSerial2::serial::serial_opened
void dispatch_LinuxSerial2_send_serial_serial_opened(struct LinuxSerial2_Instance *_instance){
if (_instance == &MainCPUCfg_serial1_var) {
Bridge_handle_serial_serial_opened(&MainCPUCfg_B_var);
}
}
// Dispatch for messages LinuxSerial2::serial::serial_rx
void dispatch_LinuxSerial2_send_serial_serial_rx(struct LinuxSerial2_Instance *_instance, uint8_t b){
if (_instance == &MainCPUCfg_serial1_var) {
Bridge_handle_serial_serial_rx(&MainCPUCfg_B_var, b);
}
}
// Dispatch for messages HTTPServer::bridge::CommandStart
void dispatch_HTTPServer_send_bridge_CommandStart(struct HTTPServer_Instance *_instance){
if (_instance == &MainCPUCfg_H_var) {
Bridge_handle_Serial1_CommandStart(&MainCPUCfg_B_var);
}
}
// Dispatch for messages HTTPServer::bridge::CommandStop
void dispatch_HTTPServer_send_bridge_CommandStop(struct HTTPServer_Instance *_instance){
if (_instance == &MainCPUCfg_H_var) {
Bridge_handle_Serial1_CommandStop(&MainCPUCfg_B_var);
}
}
// Dispatch for messages Bridge::Serial1::CPUBridgeReady
void dispatch_Bridge_send_Serial1_CPUBridgeReady(struct Bridge_Instance *_instance){
if (_instance == &MainCPUCfg_B_var) {
}
}
// Dispatch for messages Bridge::Serial1::Measure
void dispatch_Bridge_send_Serial1_Measure(struct Bridge_Instance *_instance, float m){
if (_instance == &MainCPUCfg_B_var) {
}
}
// Dispatch for messages Bridge::serial::serial_tx
void dispatch_Bridge_send_serial_serial_tx(struct Bridge_Instance *_instance, uint8_t b){
if (_instance == &MainCPUCfg_B_var) {
LinuxSerial2_handle_serial_serial_tx(&MainCPUCfg_serial1_var, b);
}
}
// Dispatch for messages Bridge::serial::serial_close
void dispatch_Bridge_send_serial_serial_close(struct Bridge_Instance *_instance){
if (_instance == &MainCPUCfg_B_var) {
}
}
// Dispatch for messages Bridge::serial::serial_open
void dispatch_Bridge_send_serial_serial_open(struct Bridge_Instance *_instance, char * device, uint32_t baudrate){
if (_instance == &MainCPUCfg_B_var) {
LinuxSerial2_handle_serial_serial_open(&MainCPUCfg_serial1_var, device, baudrate);
}
}

void processMessageQueue() {
fifo_lock();
while (fifo_empty()) fifo_wait();
byte mbuf[6];
uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 1:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_Serial1_CPUBridgeReady((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 2:
while (mbufi < 6) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_Serial1_Measure((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<24) + (mbuf[3]<<16) + (mbuf[4]<<8) + mbuf[5] /* m */ );
break;
case 3:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_HTTPServer_send_bridge_CommandStart((struct HTTPServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 4:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_HTTPServer_send_bridge_CommandStop((struct HTTPServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
}
}

void initialize_configuration_MainCPUCfg() {
// Initialize connectors
register_LinuxSerial2_send_serial_serial_rx_listener(dispatch_LinuxSerial2_send_serial_serial_rx);
register_LinuxSerial2_send_serial_serial_closed_listener(dispatch_LinuxSerial2_send_serial_serial_closed);
register_LinuxSerial2_send_serial_serial_opened_listener(dispatch_LinuxSerial2_send_serial_serial_opened);
register_HTTPServer_send_bridge_CommandStop_listener(enqueue_HTTPServer_send_bridge_CommandStop);
register_HTTPServer_send_bridge_CommandStart_listener(enqueue_HTTPServer_send_bridge_CommandStart);
register_Bridge_send_Serial1_Measure_listener(enqueue_Bridge_send_Serial1_Measure);
register_Bridge_send_Serial1_CPUBridgeReady_listener(enqueue_Bridge_send_Serial1_CPUBridgeReady);
register_Bridge_send_serial_serial_open_listener(dispatch_Bridge_send_serial_serial_open);
register_Bridge_send_serial_serial_close_listener(dispatch_Bridge_send_serial_serial_close);
register_Bridge_send_serial_serial_tx_listener(dispatch_Bridge_send_serial_serial_tx);

// Init the ID, state variables and properties for instance MainCPUCfg_serial1
MainCPUCfg_serial1_var.id = add_instance( (void*) &MainCPUCfg_serial1_var);
MainCPUCfg_serial1_var.LinuxSerial2_LinuxSerialImpl_State = LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE;

// Init the ID, state variables and properties for instance MainCPUCfg_B
MainCPUCfg_B_var.id = add_instance( (void*) &MainCPUCfg_B_var);
MainCPUCfg_B_var.Bridge_BridgeChart_State = BRIDGE_BRIDGECHART_INIT_STATE;
MainCPUCfg_B_var.Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE;
MainCPUCfg_B_var.Bridge_START_BYTE__var = 18;
MainCPUCfg_B_var.Bridge_STOP_BYTE__var = 19;
MainCPUCfg_B_var.Bridge_ESCAPE_BYTE__var = 125;
MainCPUCfg_B_var.Bridge_MsgSize__var = 0;
MainCPUCfg_B_var.Bridge_bps__var = 115200;

// Init the ID, state variables and properties for instance MainCPUCfg_H
MainCPUCfg_H_var.id = add_instance( (void*) &MainCPUCfg_H_var);
MainCPUCfg_H_var.HTTPServer_ServerChart_State = HTTPSERVER_SERVERCHART_INIT_STATE;
MainCPUCfg_H_var.HTTPServer_serverPort__var = 50999;

HTTPServer_ServerChart_OnEntry(HTTPSERVER_SERVERCHART_STATE, &MainCPUCfg_H_var);
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_STATE, &MainCPUCfg_B_var);
LinuxSerial2_LinuxSerialImpl_OnEntry(LINUXSERIAL2_LINUXSERIALIMPL_STATE, &MainCPUCfg_serial1_var);
}


// NO C_GLOBALS Annotation

int main(int argc, char *argv[]) {
  init_runtime();
  // NO C_MAIN Annotation
  initialize_configuration_MainCPUCfg();

  while (1) {
    Bridge_handle_empty_event(&MainCPUCfg_B_var);

    processMessageQueue();
  }
}
