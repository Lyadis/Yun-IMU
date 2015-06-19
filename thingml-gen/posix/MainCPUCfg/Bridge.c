/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing Bridge
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "Bridge.h"

/*****************************************************************************
 * Implementation for type : Bridge
 *****************************************************************************/

// Declaration of prototypes:
#ifdef __cplusplus
extern "C" {
#endif
void Bridge_BridgeChart_OnExit(int state, struct Bridge_Instance *_instance);
void Bridge_send_Serial1_Measure(struct Bridge_Instance *_instance, float m);
void Bridge_send_Serial1_CPUBridgeReady(struct Bridge_Instance *_instance);
void Bridge_send_serial_serial_open(struct Bridge_Instance *_instance, char * device, uint32_t baudrate);
void Bridge_send_serial_serial_close(struct Bridge_Instance *_instance);
void Bridge_send_serial_serial_tx(struct Bridge_Instance *_instance, uint8_t b);
void Bridge_send_WSService_WSStart(struct Bridge_Instance *_instance, uint16_t Port);
void Bridge_send_WSService_WSStop(struct Bridge_Instance *_instance);
void Bridge_send_WSService_sendM(struct Bridge_Instance *_instance, long m);
void f_Bridge_SerialSend(struct Bridge_Instance *_instance, uint8_t b);
void f_Bridge_SerialStart(struct Bridge_Instance *_instance);
void f_Bridge_SerialStop(struct Bridge_Instance *_instance);
void f_Bridge_parse(struct Bridge_Instance *_instance);
#ifdef __cplusplus
}
#endif

// Declaration of functions:
// Definition of function SerialSend
void f_Bridge_SerialSend(struct Bridge_Instance *_instance, uint8_t b) {
{
if((b == _instance->Bridge_START_BYTE__var) || (b == _instance->Bridge_STOP_BYTE__var) || (b == _instance->Bridge_ESCAPE_BYTE__var)) {
Bridge_send_serial_serial_tx(_instance, _instance->Bridge_ESCAPE_BYTE__var);
}
Bridge_send_serial_serial_tx(_instance, b);
}
}

// Definition of function SerialStart
void f_Bridge_SerialStart(struct Bridge_Instance *_instance) {
{
Bridge_send_serial_serial_tx(_instance, _instance->Bridge_START_BYTE__var);
}
}

// Definition of function SerialStop
void f_Bridge_SerialStop(struct Bridge_Instance *_instance) {
{
Bridge_send_serial_serial_tx(_instance, _instance->Bridge_STOP_BYTE__var);
}
}

// Definition of function parse
void f_Bridge_parse(struct Bridge_Instance *_instance) {
{
printf("parse\n");
long l;
		uint16_t msgID = 256 * _instance->Bridge_Buffer__var[0] + _instance->Bridge_Buffer__var[1];
		switch(msgID){
			case 1://Measure
				l = (_instance->Bridge_Buffer__var[4] >> 24);
				l += (_instance->Bridge_Buffer__var[5] >> 16);
				l += (_instance->Bridge_Buffer__var[6] >> 8);
				l += _instance->Bridge_Buffer__var[7];
				
				float * f = (float *) &l;
				
Bridge_send_Serial1_Measure(_instance, *f);

				
Bridge_send_WSService_sendM(_instance, l);

			break;
		}
}
}


// On Entry Actions:
void Bridge_BridgeChart_OnEntry(int state, struct Bridge_Instance *_instance) {
switch(state) {
case BRIDGE_BRIDGECHART_STATE:
_instance->Bridge_BridgeChart_State = BRIDGE_BRIDGECHART_INIT_STATE;
Bridge_BridgeChart_OnEntry(_instance->Bridge_BridgeChart_State, _instance);
break;
case BRIDGE_BRIDGECHART_INIT_STATE:
{
Bridge_send_serial_serial_open(_instance, "/dev/ttyATH0", _instance->Bridge_bps__var);
Bridge_send_WSService_WSStart(_instance, 9000);
}
break;
case BRIDGE_BRIDGECHART_ACTIVE_STATE:
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE;
Bridge_BridgeChart_OnEntry(_instance->Bridge_BridgeChart_Active_State, _instance);
break;
case BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_READING_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE:
break;
default: break;
}
}

// On Exit Actions:
void Bridge_BridgeChart_OnExit(int state, struct Bridge_Instance *_instance) {
switch(state) {
case BRIDGE_BRIDGECHART_STATE:
Bridge_BridgeChart_OnExit(_instance->Bridge_BridgeChart_State, _instance);
break;
case BRIDGE_BRIDGECHART_INIT_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_STATE:
Bridge_BridgeChart_OnExit(_instance->Bridge_BridgeChart_Active_State, _instance);
break;
case BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_READING_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE:
break;
case BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:
void Bridge_handle_Serial1_CommandStop(struct Bridge_Instance *_instance) {
uint8_t Bridge_BridgeChart_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_ACTIVE_STATE) {
uint8_t Bridge_BridgeChart_Active_State_event_consumed = 0;
Bridge_BridgeChart_State_event_consumed = 0 | Bridge_BridgeChart_Active_State_event_consumed ;
if (Bridge_BridgeChart_State_event_consumed == 0 && 1) {
{
f_Bridge_SerialStart(_instance);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 12);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 1);
f_Bridge_SerialStop(_instance);
}
Bridge_BridgeChart_State_event_consumed = 1;
}
}
}
void Bridge_handle_Serial1_CommandStart(struct Bridge_Instance *_instance) {
uint8_t Bridge_BridgeChart_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_ACTIVE_STATE) {
uint8_t Bridge_BridgeChart_Active_State_event_consumed = 0;
Bridge_BridgeChart_State_event_consumed = 0 | Bridge_BridgeChart_Active_State_event_consumed ;
if (Bridge_BridgeChart_State_event_consumed == 0 && 1) {
{
f_Bridge_SerialStart(_instance);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 11);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 1);
f_Bridge_SerialStop(_instance);
}
Bridge_BridgeChart_State_event_consumed = 1;
}
}
}
void Bridge_handle_serial_serial_opened(struct Bridge_Instance *_instance) {
uint8_t Bridge_BridgeChart_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_INIT_STATE) {
if (Bridge_BridgeChart_State_event_consumed == 0 && 1) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_INIT_STATE, _instance);
_instance->Bridge_BridgeChart_State = BRIDGE_BRIDGECHART_ACTIVE_STATE;
{
Bridge_send_Serial1_CPUBridgeReady(_instance);
}
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_STATE, _instance);
Bridge_BridgeChart_State_event_consumed = 1;
}
}
}
void Bridge_handle_serial_serial_rx(struct Bridge_Instance *_instance, uint8_t b) {
uint8_t Bridge_BridgeChart_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_ACTIVE_STATE) {
uint8_t Bridge_BridgeChart_Active_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_Active_State == BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE) {
if (Bridge_BridgeChart_Active_State_event_consumed == 0 && b == _instance->Bridge_START_BYTE__var) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_READING_STATE;
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
}
else if (_instance->Bridge_BridgeChart_Active_State == BRIDGE_BRIDGECHART_ACTIVE_READING_STATE) {
if (Bridge_BridgeChart_Active_State_event_consumed == 0 && _instance->Bridge_MsgSize__var > 31) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE;
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
else if (Bridge_BridgeChart_Active_State_event_consumed == 0 && b == _instance->Bridge_ESCAPE_BYTE__var) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE;
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
else if (Bridge_BridgeChart_Active_State_event_consumed == 0 && b == _instance->Bridge_STOP_BYTE__var) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE;
{
f_Bridge_parse(_instance);
_instance->Bridge_MsgSize__var = 0;
}
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
else if (Bridge_BridgeChart_Active_State_event_consumed == 0 && 1) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_READING_STATE;
{
_instance->Bridge_Buffer__var[_instance->Bridge_MsgSize__var] = b;
_instance->Bridge_MsgSize__var = _instance->Bridge_MsgSize__var + 1;
}
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
}
else if (_instance->Bridge_BridgeChart_Active_State == BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE) {
if (Bridge_BridgeChart_Active_State_event_consumed == 0 && _instance->Bridge_MsgSize__var > 31) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE;
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
else if (Bridge_BridgeChart_Active_State_event_consumed == 0 && 1) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_ESCAPING_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_READING_STATE;
{
_instance->Bridge_Buffer__var[_instance->Bridge_MsgSize__var] = b;
_instance->Bridge_MsgSize__var = _instance->Bridge_MsgSize__var + 1;
}
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_READING_STATE, _instance);
Bridge_BridgeChart_Active_State_event_consumed = 1;
}
}
Bridge_BridgeChart_State_event_consumed = 0 | Bridge_BridgeChart_Active_State_event_consumed ;
}
}
void Bridge_handle_WSService_CMDStop(struct Bridge_Instance *_instance) {
uint8_t Bridge_BridgeChart_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_ACTIVE_STATE) {
uint8_t Bridge_BridgeChart_Active_State_event_consumed = 0;
Bridge_BridgeChart_State_event_consumed = 0 | Bridge_BridgeChart_Active_State_event_consumed ;
if (Bridge_BridgeChart_State_event_consumed == 0 && 1) {
{
f_Bridge_SerialStart(_instance);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 12);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 1);
f_Bridge_SerialStop(_instance);
}
Bridge_BridgeChart_State_event_consumed = 1;
}
}
}
void Bridge_handle_WSService_CMDStart(struct Bridge_Instance *_instance) {
uint8_t Bridge_BridgeChart_State_event_consumed = 0;
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_ACTIVE_STATE) {
uint8_t Bridge_BridgeChart_Active_State_event_consumed = 0;
Bridge_BridgeChart_State_event_consumed = 0 | Bridge_BridgeChart_Active_State_event_consumed ;
if (Bridge_BridgeChart_State_event_consumed == 0 && 1) {
{
f_Bridge_SerialStart(_instance);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 11);
f_Bridge_SerialSend(_instance, 0);
f_Bridge_SerialSend(_instance, 1);
f_Bridge_SerialStop(_instance);
}
Bridge_BridgeChart_State_event_consumed = 1;
}
}
}
void Bridge_handle_empty_event(struct Bridge_Instance *_instance) {
if (_instance->Bridge_BridgeChart_State == BRIDGE_BRIDGECHART_ACTIVE_STATE) {
if (_instance->Bridge_BridgeChart_Active_State == BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE) {
if (1) {
Bridge_BridgeChart_OnExit(BRIDGE_BRIDGECHART_ACTIVE_ERROR_STATE, _instance);
_instance->Bridge_BridgeChart_Active_State = BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE;
{
_instance->Bridge_MsgSize__var = 0;
}
Bridge_BridgeChart_OnEntry(BRIDGE_BRIDGECHART_ACTIVE_IDLE_STATE, _instance);
}
}
}
}

// Observers for outgoing messages:
void (*Bridge_send_Serial1_Measure_listener)(struct Bridge_Instance*, float)= 0x0;
void register_Bridge_send_Serial1_Measure_listener(void (*_listener)(struct Bridge_Instance*, float)){
Bridge_send_Serial1_Measure_listener = _listener;
}
void Bridge_send_Serial1_Measure(struct Bridge_Instance *_instance, float m){
if (Bridge_send_Serial1_Measure_listener != 0x0) Bridge_send_Serial1_Measure_listener(_instance, m);
}
void (*Bridge_send_Serial1_CPUBridgeReady_listener)(struct Bridge_Instance*)= 0x0;
void register_Bridge_send_Serial1_CPUBridgeReady_listener(void (*_listener)(struct Bridge_Instance*)){
Bridge_send_Serial1_CPUBridgeReady_listener = _listener;
}
void Bridge_send_Serial1_CPUBridgeReady(struct Bridge_Instance *_instance){
if (Bridge_send_Serial1_CPUBridgeReady_listener != 0x0) Bridge_send_Serial1_CPUBridgeReady_listener(_instance);
}
void (*Bridge_send_serial_serial_open_listener)(struct Bridge_Instance*, char *, uint32_t)= 0x0;
void register_Bridge_send_serial_serial_open_listener(void (*_listener)(struct Bridge_Instance*, char *, uint32_t)){
Bridge_send_serial_serial_open_listener = _listener;
}
void Bridge_send_serial_serial_open(struct Bridge_Instance *_instance, char * device, uint32_t baudrate){
if (Bridge_send_serial_serial_open_listener != 0x0) Bridge_send_serial_serial_open_listener(_instance, device, baudrate);
}
void (*Bridge_send_serial_serial_close_listener)(struct Bridge_Instance*)= 0x0;
void register_Bridge_send_serial_serial_close_listener(void (*_listener)(struct Bridge_Instance*)){
Bridge_send_serial_serial_close_listener = _listener;
}
void Bridge_send_serial_serial_close(struct Bridge_Instance *_instance){
if (Bridge_send_serial_serial_close_listener != 0x0) Bridge_send_serial_serial_close_listener(_instance);
}
void (*Bridge_send_serial_serial_tx_listener)(struct Bridge_Instance*, uint8_t)= 0x0;
void register_Bridge_send_serial_serial_tx_listener(void (*_listener)(struct Bridge_Instance*, uint8_t)){
Bridge_send_serial_serial_tx_listener = _listener;
}
void Bridge_send_serial_serial_tx(struct Bridge_Instance *_instance, uint8_t b){
if (Bridge_send_serial_serial_tx_listener != 0x0) Bridge_send_serial_serial_tx_listener(_instance, b);
}
void (*Bridge_send_WSService_WSStart_listener)(struct Bridge_Instance*, uint16_t)= 0x0;
void register_Bridge_send_WSService_WSStart_listener(void (*_listener)(struct Bridge_Instance*, uint16_t)){
Bridge_send_WSService_WSStart_listener = _listener;
}
void Bridge_send_WSService_WSStart(struct Bridge_Instance *_instance, uint16_t Port){
if (Bridge_send_WSService_WSStart_listener != 0x0) Bridge_send_WSService_WSStart_listener(_instance, Port);
}
void (*Bridge_send_WSService_WSStop_listener)(struct Bridge_Instance*)= 0x0;
void register_Bridge_send_WSService_WSStop_listener(void (*_listener)(struct Bridge_Instance*)){
Bridge_send_WSService_WSStop_listener = _listener;
}
void Bridge_send_WSService_WSStop(struct Bridge_Instance *_instance){
if (Bridge_send_WSService_WSStop_listener != 0x0) Bridge_send_WSService_WSStop_listener(_instance);
}
void (*Bridge_send_WSService_sendM_listener)(struct Bridge_Instance*, long)= 0x0;
void register_Bridge_send_WSService_sendM_listener(void (*_listener)(struct Bridge_Instance*, long)){
Bridge_send_WSService_sendM_listener = _listener;
}
void Bridge_send_WSService_sendM(struct Bridge_Instance *_instance, long m){
if (Bridge_send_WSService_sendM_listener != 0x0) Bridge_send_WSService_sendM_listener(_instance, m);
}

