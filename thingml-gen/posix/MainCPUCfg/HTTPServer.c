/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing HTTPServer
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "HTTPServer.h"

/*****************************************************************************
 * Implementation for type : HTTPServer
 *****************************************************************************/


// BEGIN: Code from the c_global annotation HTTPServer

struct HTTPServer_Instance *_HTTPServer_Instance;

// END: Code from the c_global annotation HTTPServer

// Declaration of prototypes:
#ifdef __cplusplus
extern "C" {
#endif
void HTTPServer_ServerChart_OnExit(int state, struct HTTPServer_Instance *_instance);
void HTTPServer_send_bridge_CommandStop(struct HTTPServer_Instance *_instance);
void HTTPServer_send_bridge_CommandStart(struct HTTPServer_Instance *_instance);
static int ahc_echo (void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **ptr);
void f_HTTPServer_start_httpd(struct HTTPServer_Instance *_instance, uint16_t Port);
#ifdef __cplusplus
}
#endif

// Declaration of functions:
// Definition of function ahc_echo
static int ahc_echo (void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **ptr) {
{

          
		  static int aptr;
		  const char *fmt = cls;
		  const char *val;
		  char *me;
		  struct MHD_Response *response;
		  int ret;
		
		  if (0 != strcmp (method, "GET"))
		    return MHD_NO;              /* unexpected method */
		  if (&aptr != *ptr)
		    {
		      /* do never respond on first call */
		      *ptr = &aptr;
		      return MHD_YES;
		    }
		  *ptr = NULL;                  /* reset when done */
		  val = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, "q");
		
		  if(strcmp(val, "START") == 0) {
		    printf("START\n");
		    
HTTPServer_send_bridge_CommandStart(_HTTPServer_Instance);

		  } else if (strcmp(val, "STOP") == 0) {
		    printf("STOP\n");
		    
HTTPServer_send_bridge_CommandStop(_HTTPServer_Instance);

		  }
		
		  me = malloc (snprintf (NULL, 0, fmt, "q", val) + 1);
		  if (me == NULL)
		    return MHD_NO;
		  sprintf (me, fmt, "q", val);
		  response = MHD_create_response_from_buffer (strlen (me), me,
							      MHD_RESPMEM_MUST_FREE);
		  if (response == NULL)
		    {
		      free (me);
		      return MHD_NO;
		    }
		  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
		  MHD_destroy_response (response);
		  
return ret;
}
}

// Fork a thread to execute the function f_HTTPServer_start_httpd

// Struct for the parameters of the function  f_HTTPServer_start_httpd
struct f_HTTPServer_start_httpd_struct {
  struct HTTPServer_Instance *_instance;
   uint16_t Port;

  pthread_mutex_t *lock;
  pthread_cond_t *cv;
};

// Definition of function start_receiver_process (executed in a separate thread)
void f_HTTPServer_start_httpd_run(struct HTTPServer_Instance *_instance, uint16_t Port)
{
  {
struct MHD_Daemon *d;
				_HTTPServer_Instance = _instance;

				  
				  d = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
				                        Port,
				                        NULL, NULL, &ahc_echo, PAGE, MHD_OPTION_END);
				  if (d == NULL)
				    return 1;
				  (void) getc (stdin);
				  MHD_stop_daemon (d);
}

}


void f_HTTPServer_start_httpd_proc(void * p)
{
  // Get parameters from the main thread
  struct f_HTTPServer_start_httpd_struct params = *((struct f_HTTPServer_start_httpd_struct *) p);
  
  // Unblock the main thread
  pthread_mutex_lock(params.lock);
  pthread_cond_signal(params.cv);
  pthread_mutex_unlock(params.lock);
  
  // Run the function
  //f_HTTPServer_start_httpd_run(params._instance, params.esums_device);
  f_HTTPServer_start_httpd_run(params._instance, params.Port);
}

// Operation called by the runtime and forking a new thread
void f_HTTPServer_start_httpd(struct HTTPServer_Instance *_instance, uint16_t Port)
{
  // Store parameters
  struct f_HTTPServer_start_httpd_struct params;
  pthread_mutex_t lock;
  pthread_cond_t cv;
  params.lock = &lock;
  params.cv = &cv;
  params._instance = _instance;
  params.Port = Port;

  pthread_mutex_init(params.lock, NULL);
  pthread_cond_init(params.cv, NULL);
  //Start the new thread
  pthread_mutex_lock(params.lock);
  pthread_t thread; 
  pthread_create( &thread, NULL, f_HTTPServer_start_httpd_proc, (void*) &params);
  // Wait until it has started and read its parameters
  pthread_cond_wait(params.cv, params.lock);
  // Realease mutex
  pthread_mutex_unlock(params.lock);
}

// On Entry Actions:
void HTTPServer_ServerChart_OnEntry(int state, struct HTTPServer_Instance *_instance) {
switch(state) {
case HTTPSERVER_SERVERCHART_STATE:
_instance->HTTPServer_ServerChart_State = HTTPSERVER_SERVERCHART_INIT_STATE;
HTTPServer_ServerChart_OnEntry(_instance->HTTPServer_ServerChart_State, _instance);
break;
case HTTPSERVER_SERVERCHART_INIT_STATE:
{
fprintf(stdout, "[HTTPServer] Starting\n");

f_HTTPServer_start_httpd(_instance, _instance->HTTPServer_serverPort__var);
fprintf(stdout, "[HTTPServer] Started\n");

}
break;
default: break;
}
}

// On Exit Actions:
void HTTPServer_ServerChart_OnExit(int state, struct HTTPServer_Instance *_instance) {
switch(state) {
case HTTPSERVER_SERVERCHART_STATE:
HTTPServer_ServerChart_OnExit(_instance->HTTPServer_ServerChart_State, _instance);
break;
case HTTPSERVER_SERVERCHART_INIT_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:

// Observers for outgoing messages:
void (*HTTPServer_send_bridge_CommandStop_listener)(struct HTTPServer_Instance*)= 0x0;
void register_HTTPServer_send_bridge_CommandStop_listener(void (*_listener)(struct HTTPServer_Instance*)){
HTTPServer_send_bridge_CommandStop_listener = _listener;
}
void HTTPServer_send_bridge_CommandStop(struct HTTPServer_Instance *_instance){
if (HTTPServer_send_bridge_CommandStop_listener != 0x0) HTTPServer_send_bridge_CommandStop_listener(_instance);
}
void (*HTTPServer_send_bridge_CommandStart_listener)(struct HTTPServer_Instance*)= 0x0;
void register_HTTPServer_send_bridge_CommandStart_listener(void (*_listener)(struct HTTPServer_Instance*)){
HTTPServer_send_bridge_CommandStart_listener = _listener;
}
void HTTPServer_send_bridge_CommandStart(struct HTTPServer_Instance *_instance){
if (HTTPServer_send_bridge_CommandStart_listener != 0x0) HTTPServer_send_bridge_CommandStart_listener(_instance);
}

