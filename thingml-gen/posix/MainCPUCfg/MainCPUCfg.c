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
#include "Bridge.h"
#include "LinuxSerial2.h"
#include "HTTPServer.h"
#include "WSServer.h"


// NO C_HEADERS Annotation


/*****************************************************************************
 * Definitions for configuration : MainCPUCfg
 *****************************************************************************/

//Declaration of instance variables
struct LinuxSerial2_Instance MainCPUCfg_serial1_var;
struct WSServer_Instance MainCPUCfg_WS_var;
struct Bridge_Instance MainCPUCfg_B_var;
struct HTTPServer_Instance MainCPUCfg_H_var;

// Enqueue of messages WSServer::WSService::CMDStart
void enqueue_WSServer_send_WSService_CMDStart(struct WSServer_Instance *_instance){
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
// Enqueue of messages WSServer::WSService::CMDStop
void enqueue_WSServer_send_WSService_CMDStop(struct WSServer_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (2 >> 8) & 0xFF );
_fifo_enqueue( 2 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
fifo_unlock_and_notify();
}
// Enqueue of messages WSServer::WSService::WSStarted
void enqueue_WSServer_send_WSService_WSStarted(struct WSServer_Instance *_instance){
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
// Enqueue of messages Bridge::Serial1::CPUBridgeReady
void enqueue_Bridge_send_Serial1_CPUBridgeReady(struct Bridge_Instance *_instance){
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
// Enqueue of messages Bridge::Serial1::Measure
void enqueue_Bridge_send_Serial1_Measure(struct Bridge_Instance *_instance, long m){
fifo_lock();
if ( fifo_byte_available() > 8 ) {

_fifo_enqueue( (5 >> 8) & 0xFF );
_fifo_enqueue( 5 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter m
_fifo_enqueue((m>>24) & 0xFF);
_fifo_enqueue((m>>16) & 0xFF);
_fifo_enqueue((m>>8) & 0xFF);
_fifo_enqueue(m & 0xFF);
}
fifo_unlock_and_notify();
}
// Enqueue of messages Bridge::WSService::WSStart
void enqueue_Bridge_send_WSService_WSStart(struct Bridge_Instance *_instance, uint16_t Port){
fifo_lock();
if ( fifo_byte_available() > 6 ) {

_fifo_enqueue( (6 >> 8) & 0xFF );
_fifo_enqueue( 6 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter Port
_fifo_enqueue((Port>>8) & 0xFF);
_fifo_enqueue(Port & 0xFF);
}
fifo_unlock_and_notify();
}
// Enqueue of messages Bridge::WSService::WSStop
void enqueue_Bridge_send_WSService_WSStop(struct Bridge_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (7 >> 8) & 0xFF );
_fifo_enqueue( 7 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
fifo_unlock_and_notify();
}
// Enqueue of messages Bridge::WSService::sendM
void enqueue_Bridge_send_WSService_sendM(struct Bridge_Instance *_instance, long m){
fifo_lock();
if ( fifo_byte_available() > 8 ) {

_fifo_enqueue( (8 >> 8) & 0xFF );
_fifo_enqueue( 8 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter m
_fifo_enqueue((m>>24) & 0xFF);
_fifo_enqueue((m>>16) & 0xFF);
_fifo_enqueue((m>>8) & 0xFF);
_fifo_enqueue(m & 0xFF);
}
fifo_unlock_and_notify();
}
// Enqueue of messages HTTPServer::bridge::CommandStart
void enqueue_HTTPServer_send_bridge_CommandStart(struct HTTPServer_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (9 >> 8) & 0xFF );
_fifo_enqueue( 9 & 0xFF );

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

_fifo_enqueue( (10 >> 8) & 0xFF );
_fifo_enqueue( 10 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
fifo_unlock_and_notify();
}

// Dispatch for messages LinuxSerial2::serial::serial_rx
void dispatch_LinuxSerial2_send_serial_serial_rx(struct LinuxSerial2_Instance *_instance, uint8_t b){
if (_instance == &MainCPUCfg_serial1_var) {
Bridge_handle_serial_serial_rx(&MainCPUCfg_B_var, b);
}
}
// Dispatch for messages LinuxSerial2::serial::serial_opened
void dispatch_LinuxSerial2_send_serial_serial_opened(struct LinuxSerial2_Instance *_instance){
if (_instance == &MainCPUCfg_serial1_var) {
Bridge_handle_serial_serial_opened(&MainCPUCfg_B_var);
}
}
// Dispatch for messages LinuxSerial2::serial::serial_closed
void dispatch_LinuxSerial2_send_serial_serial_closed(struct LinuxSerial2_Instance *_instance){
if (_instance == &MainCPUCfg_serial1_var) {
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
// Dispatch for messages WSServer::WSService::CMDStart
void dispatch_WSServer_send_WSService_CMDStart(struct WSServer_Instance *_instance){
if (_instance == &MainCPUCfg_WS_var) {
Bridge_handle_WSService_CMDStart(&MainCPUCfg_B_var);
}
}
// Dispatch for messages WSServer::WSService::CMDStop
void dispatch_WSServer_send_WSService_CMDStop(struct WSServer_Instance *_instance){
if (_instance == &MainCPUCfg_WS_var) {
Bridge_handle_WSService_CMDStop(&MainCPUCfg_B_var);
}
}
// Dispatch for messages WSServer::WSService::WSStarted
void dispatch_WSServer_send_WSService_WSStarted(struct WSServer_Instance *_instance){
if (_instance == &MainCPUCfg_WS_var) {
}
}
// Dispatch for messages Bridge::Serial1::CPUBridgeReady
void dispatch_Bridge_send_Serial1_CPUBridgeReady(struct Bridge_Instance *_instance){
if (_instance == &MainCPUCfg_B_var) {
}
}
// Dispatch for messages Bridge::Serial1::Measure
void dispatch_Bridge_send_Serial1_Measure(struct Bridge_Instance *_instance, long m){
if (_instance == &MainCPUCfg_B_var) {
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
// Dispatch for messages Bridge::serial::serial_tx
void dispatch_Bridge_send_serial_serial_tx(struct Bridge_Instance *_instance, uint8_t b){
if (_instance == &MainCPUCfg_B_var) {
LinuxSerial2_handle_serial_serial_tx(&MainCPUCfg_serial1_var, b);
}
}
// Dispatch for messages Bridge::WSService::WSStart
void dispatch_Bridge_send_WSService_WSStart(struct Bridge_Instance *_instance, uint16_t Port){
if (_instance == &MainCPUCfg_B_var) {
WSServer_handle_WSService_WSStart(&MainCPUCfg_WS_var, Port);
}
}
// Dispatch for messages Bridge::WSService::WSStop
void dispatch_Bridge_send_WSService_WSStop(struct Bridge_Instance *_instance){
if (_instance == &MainCPUCfg_B_var) {
WSServer_handle_WSService_WSStop(&MainCPUCfg_WS_var);
}
}
// Dispatch for messages Bridge::WSService::sendM
void dispatch_Bridge_send_WSService_sendM(struct Bridge_Instance *_instance, long m){
if (_instance == &MainCPUCfg_B_var) {
WSServer_handle_WSService_sendM(&MainCPUCfg_WS_var, m);
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
dispatch_WSServer_send_WSService_CMDStart((struct WSServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 2:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_WSServer_send_WSService_CMDStop((struct WSServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 3:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_WSServer_send_WSService_WSStarted((struct WSServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 4:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_Serial1_CPUBridgeReady((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 5:
while (mbufi < 6) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_Serial1_Measure((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<24) + (mbuf[3]<<16) + (mbuf[4]<<8) + mbuf[5] /* m */ );
break;
case 6:
while (mbufi < 4) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_WSService_WSStart((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<8) + mbuf[3] /* Port */ );
break;
case 7:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_WSService_WSStop((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 8:
while (mbufi < 6) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_Bridge_send_WSService_sendM((struct Bridge_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<24) + (mbuf[3]<<16) + (mbuf[4]<<8) + mbuf[5] /* m */ );
break;
case 9:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_HTTPServer_send_bridge_CommandStart((struct HTTPServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 10:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_HTTPServer_send_bridge_CommandStop((struct HTTPServer_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
}
}

void initialize_configuration_MainCPUCfg() {
// Initialize connectors
register_Bridge_send_Serial1_Measure_listener(enqueue_Bridge_send_Serial1_Measure);
register_Bridge_send_Serial1_CPUBridgeReady_listener(enqueue_Bridge_send_Serial1_CPUBridgeReady);
register_Bridge_send_serial_serial_open_listener(dispatch_Bridge_send_serial_serial_open);
register_Bridge_send_serial_serial_close_listener(dispatch_Bridge_send_serial_serial_close);
register_Bridge_send_serial_serial_tx_listener(dispatch_Bridge_send_serial_serial_tx);
register_Bridge_send_WSService_WSStart_listener(enqueue_Bridge_send_WSService_WSStart);
register_Bridge_send_WSService_WSStop_listener(enqueue_Bridge_send_WSService_WSStop);
register_Bridge_send_WSService_sendM_listener(enqueue_Bridge_send_WSService_sendM);
register_LinuxSerial2_send_serial_serial_rx_listener(dispatch_LinuxSerial2_send_serial_serial_rx);
register_LinuxSerial2_send_serial_serial_closed_listener(dispatch_LinuxSerial2_send_serial_serial_closed);
register_LinuxSerial2_send_serial_serial_opened_listener(dispatch_LinuxSerial2_send_serial_serial_opened);
register_HTTPServer_send_bridge_CommandStop_listener(enqueue_HTTPServer_send_bridge_CommandStop);
register_HTTPServer_send_bridge_CommandStart_listener(enqueue_HTTPServer_send_bridge_CommandStart);
register_WSServer_send_WSService_WSStarted_listener(enqueue_WSServer_send_WSService_WSStarted);
register_WSServer_send_WSService_CMDStop_listener(enqueue_WSServer_send_WSService_CMDStop);
register_WSServer_send_WSService_CMDStart_listener(enqueue_WSServer_send_WSService_CMDStart);

// Init the ID, state variables and properties for instance MainCPUCfg_WS
MainCPUCfg_WS_var.id = add_instance( (void*) &MainCPUCfg_WS_var);
MainCPUCfg_WS_var.WSServer_ServerChart_State = WSSERVER_SERVERCHART_IDLE_STATE;
MainCPUCfg_WS_var.WSServer_M__var = 0;
MainCPUCfg_WS_var.WSServer_serverPort__var = 9000;
MainCPUCfg_WS_var.WSServer_Running__var = 0;

// Init the ID, state variables and properties for instance MainCPUCfg_H
MainCPUCfg_H_var.id = add_instance( (void*) &MainCPUCfg_H_var);
MainCPUCfg_H_var.HTTPServer_ServerChart_State = HTTPSERVER_SERVERCHART_INIT_STATE;
MainCPUCfg_H_var.HTTPServer_serverPort__var = 50999;

// Init the ID, state variables and properties for instance MainCPUCfg_B
MainCPUCfg_B_var.id = add_instance( (void*) &MainCPUCfg_B_var);
MainCPUCfg_B_var.Bridge_BridgeChart_State = BRIDGE_BRIDGECHART_INIT_STATE;
MainCPUCfg_B_var.Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE;
MainCPUCfg_B_var.Bridge_START_BYTE__var = 18;
MainCPUCfg_B_var.Bridge_STOP_BYTE__var = 19;
MainCPUCfg_B_var.Bridge_ESCAPE_BYTE__var = 125;
MainCPUCfg_B_var.Bridge_MsgSize__var = 0;
MainCPUCfg_B_var.Bridge_bps__var = 115200;

// Init the ID, state variables and properties for instance MainCPUCfg_serial1
MainCPUCfg_serial1_var.id = add_instance( (void*) &MainCPUCfg_serial1_var);
MainCPUCfg_serial1_var.LinuxSerial2_LinuxSerialImpl_State = LINUXSERIAL2_LINUXSERIALIMPL_RUNNING_STATE;

Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_STATE, &MainCPUCfg_B_var);
HTTPServer_ServerChart_OnEntry(HTTPSERVER_SERVERCHART_STATE, &MainCPUCfg_H_var);
WSServer_ServerChart_OnEntry(WSSERVER_SERVERCHART_STATE, &MainCPUCfg_WS_var);
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