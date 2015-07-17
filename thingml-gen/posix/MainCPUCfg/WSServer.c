/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing WSServer
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "WSServer.h"

/*****************************************************************************
 * Implementation for type : WSServer
 *****************************************************************************/


// BEGIN: Code from the c_global annotation WSServer

struct WSServer_Instance *_WSServer_Instance;

static int close_testing;
int max_poll_elements;

#ifdef EXTERNAL_POLL
struct pollfd *pollfds;
int *fd_lookup;
int count_pollfds;
#endif
static volatile int force_exit = 0;
static struct libwebsocket_context *context;


enum demo_protocols {
	/* always first */
	PROTOCOL_HTTP = 0,

	PROTOCOL_IMU,

	DEMO_PROTOCOL_COUNT
};


#define LOCAL_RESOURCE_PATH "./libwebsockets-test-server"
char *resource_path = LOCAL_RESOURCE_PATH;

/*
 * We take a strict whitelist approach to stop ../ attacks
 */

struct serveable {
	const char *urlpath;
	const char *mimetype;
}; 

struct per_session_data__http {
	int fd;
};

/*
 * this is just an example of parsing handshake headers, you don't need this
 * in your code unless you will filter allowing connections by the header
 * content
 */

static void dump_handshake_info(struct libwebsocket *wsi)
{
	int n = 0;
	char buf[256];
	const unsigned char *c;

	do {
		c = lws_token_to_string(n);
		if (!c) {
			n++;
			continue;
		}

		if (!lws_hdr_total_length(wsi, n)) {
			n++;
			continue;
		}

		lws_hdr_copy(wsi, buf, sizeof buf, n);

		fprintf(stderr, " %s = %s ", (char *)c, buf);
		n++;
	} while (c);
}

const char * get_mimetype(const char *file)
{
	int n = strlen(file);

	if (n < 5)
		return NULL;

	if (!strcmp(&file[n - 4], ".ico"))
		return "image/x-icon";

	if (!strcmp(&file[n - 4], ".png"))
		return "image/png";

	if (!strcmp(&file[n - 5], ".html"))
		return "text/html";

	return NULL;
}


struct per_session_data__IMU {
	int number;
};

/* list of supported protocols and callbacks */

static struct libwebsocket_protocols * protocols;



// END: Code from the c_global annotation WSServer

// Declaration of prototypes:
#ifdef __cplusplus
extern "C" {
#endif
void WSServer_ServerChart_OnExit(int state, struct WSServer_Instance *_instance);
void WSServer_send_WSService_WSStarted(struct WSServer_Instance *_instance);
void WSServer_send_WSService_CMDStop(struct WSServer_Instance *_instance);
void WSServer_send_WSService_CMDStart(struct WSServer_Instance *_instance);
static int callback_http(struct libwebsocket_context *context,
					struct libwebsocket *wsi,
					enum libwebsocket_callback_reasons reason, void *user,
					void *in, size_t len);
static int
			callback_IMU(struct libwebsocket_context *context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason,
			void *user, void *in, size_t len);
void f_WSServer_start_wsServer(struct WSServer_Instance *_instance, uint16_t Port);
#ifdef __cplusplus
}
#endif

// Declaration of functions:
// Definition of function http_callback
static int callback_http(struct libwebsocket_context *context,
					struct libwebsocket *wsi,
					enum libwebsocket_callback_reasons reason, void *user,
					void *in, size_t len) {
{
	
			char buf[256];
			char leaf_path[1024];
			char b64[64];
			struct timeval tv;
			int n, m;
			unsigned char *p;
			char *other_headers;
			static unsigned char buffer[4096];
			struct stat stat_buf;
			struct per_session_data__http *pss =
					(struct per_session_data__http *)user;
			const char *mimetype;
		#ifdef EXTERNAL_POLL
			struct libwebsocket_pollargs *pa = (struct libwebsocket_pollargs *)in;
		#endif
			unsigned char *end;
			switch (reason) {
			case LWS_CALLBACK_HTTP:
		
				dump_handshake_info(wsi);
		
				if (len < 1) {
					libwebsockets_return_http_status(context, wsi,
								HTTP_STATUS_BAD_REQUEST, NULL);
					goto try_to_reuse;
				}
		
				/* this example server has no concept of directories */
				if (strchr((const char *)in + 1, '/')) {
					libwebsockets_return_http_status(context, wsi,
								HTTP_STATUS_FORBIDDEN, NULL);
					goto try_to_reuse;
				}
		
				/* if a legal POST URL, let it continue and accept data */
				if (lws_hdr_total_length(wsi, WSI_TOKEN_POST_URI))
					return 0;
		
				/* check for the "send a big file by hand" example case */
		
				if (!strcmp((const char *)in, "/leaf.jpg")) {
					if (strlen(resource_path) > sizeof(leaf_path) - 10)
						return -1;
					sprintf(leaf_path, "%s/leaf.jpg", resource_path);
		
					/* well, let's demonstrate how to send the hard way */
		
					p = buffer + LWS_SEND_BUFFER_PRE_PADDING;
					end = p + sizeof(buffer) - LWS_SEND_BUFFER_PRE_PADDING;
		
					pss->fd = open(leaf_path, O_RDONLY);
		
					if (pss->fd < 0)
						return -1;
		
					if (fstat(pss->fd, &stat_buf) < 0)
						return -1;
		
					/*
					 * we will send a big jpeg file, but it could be
					 * anything.  Set the Content-Type: appropriately
					 * so the browser knows what to do with it.
					 * 
					 * Notice we use the APIs to build the header, which
					 * will do the right thing for HTTP 1/1.1 and HTTP2
					 * depending on what connection it happens to be working
					 * on
					 */
					if (lws_add_http_header_status(context, wsi, 200, &p, end))
						return 1;
					if (lws_add_http_header_by_token(context, wsi,
							WSI_TOKEN_HTTP_SERVER,
						    	(unsigned char *)"libwebsockets",
							13, &p, end))
						return 1;
					if (lws_add_http_header_by_token(context, wsi,
							WSI_TOKEN_HTTP_CONTENT_TYPE,
						    	(unsigned char *)"image/jpeg",
							10, &p, end))
						return 1;
					if (lws_add_http_header_content_length(context, wsi,
								stat_buf.st_size, &p, end))
						return 1;
					if (lws_finalize_http_header(context, wsi, &p, end))
						return 1;
		
					/*
					 * send the http headers...
					 * this won't block since it's the first payload sent
					 * on the connection since it was established
					 * (too small for partial)
					 * 
					 * Notice they are sent using LWS_WRITE_HTTP_HEADERS
					 * which also means you can't send body too in one step,
					 * this is mandated by changes in HTTP2
					 */
		
					n = libwebsocket_write(wsi,
							buffer + LWS_SEND_BUFFER_PRE_PADDING,
							p - (buffer + LWS_SEND_BUFFER_PRE_PADDING),
							LWS_WRITE_HTTP_HEADERS);
		
					if (n < 0) {
						close(pss->fd);
						return -1;
					}
					/*
					 * book us a LWS_CALLBACK_HTTP_WRITEABLE callback
					 */
					libwebsocket_callback_on_writable(context, wsi);
					break;
				}
		
				/* if not, send a file the easy way */
				strcpy(buf, resource_path);
				if (strcmp(in, "/")) {
					if (*((const char *)in) != '/')
						strcat(buf, "/");
					strncat(buf, in, sizeof(buf) - strlen(resource_path));
				} else /* default file to serve */
					strcat(buf, "/IMU.html");
				buf[sizeof(buf) - 1] = '\0';
		
				/* refuse to serve files we don't understand */
				mimetype = get_mimetype(buf);
				if (!mimetype) {
					lwsl_err("Unknown mimetype for %s\n", buf);
					libwebsockets_return_http_status(context, wsi,
						      HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE, NULL);
					return -1;
				}
		
				/* demostrates how to set a cookie on / */
		
				other_headers = NULL;
				n = 0;
				if (!strcmp((const char *)in, "/") &&
					   !lws_hdr_total_length(wsi, WSI_TOKEN_HTTP_COOKIE)) {
					/* this isn't very unguessable but it'll do for us */
					gettimeofday(&tv, NULL);
					n = sprintf(b64, "test=LWS_%u_%u_COOKIE;Max-Age=360000",
						(unsigned int)tv.tv_sec,
						(unsigned int)tv.tv_usec);
		
					p = (unsigned char *)leaf_path;
		
					if (lws_add_http_header_by_name(context, wsi, 
						(unsigned char *)"set-cookie:", 
						(unsigned char *)b64, n, &p,
						(unsigned char *)leaf_path + sizeof(leaf_path)))
						return 1;
					n = (char *)p - leaf_path;
					other_headers = leaf_path;
				}
		
				n = libwebsockets_serve_http_file(context, wsi, buf,
								mimetype, other_headers, n);
				if (n < 0 || ((n > 0) && lws_http_transaction_completed(wsi)))
					return -1; /* error or can't reuse connection: close the socket */
		
				/*
				 * notice that the sending of the file completes asynchronously,
				 * we'll get a LWS_CALLBACK_HTTP_FILE_COMPLETION callback when
				 * it's done
				 */
		
				break;
		
			case LWS_CALLBACK_HTTP_BODY:
				strncpy(buf, in, 20);
				buf[20] = '\0';
				if (len < 20)
					buf[len] = '\0';
		
				lwsl_notice("LWS_CALLBACK_HTTP_BODY: %s... len %d\n",
						(const char *)buf, (int)len);
		
				break;
		
			case LWS_CALLBACK_HTTP_BODY_COMPLETION:
				lwsl_notice("LWS_CALLBACK_HTTP_BODY_COMPLETION\n");
				/* the whole of the sent body arrived, close or reuse the connection */
				libwebsockets_return_http_status(context, wsi,
								HTTP_STATUS_OK, NULL);
				goto try_to_reuse;
		
			case LWS_CALLBACK_HTTP_FILE_COMPLETION:
		//		lwsl_info("LWS_CALLBACK_HTTP_FILE_COMPLETION seen\n");
				/* kill the connection after we sent one file */
				goto try_to_reuse;
		
			case LWS_CALLBACK_HTTP_WRITEABLE:
				/*
				 * we can send more of whatever it is we were sending
				 */
				do {
					/* we'd like the send this much */
					n = sizeof(buffer) - LWS_SEND_BUFFER_PRE_PADDING;
					
					/* but if the peer told us he wants less, we can adapt */
					m = lws_get_peer_write_allowance(wsi);
		
					/* -1 means not using a protocol that has this info */
					if (m == 0)
						/* right now, peer can't handle anything */
						goto later;
		
					if (m != -1 && m < n)
						/* he couldn't handle that much */
						n = m;
					
					n = read(pss->fd, buffer + LWS_SEND_BUFFER_PRE_PADDING,
											n);
					/* problem reading, close conn */
					if (n < 0)
						goto bail;
					/* sent it all, close conn */
					if (n == 0)
						goto flush_bail;
					/*
					 * To support HTTP2, must take care about preamble space
					 * 
					 * identification of when we send the last payload frame
					 * is handled by the library itself if you sent a
					 * content-length header
					 */
					m = libwebsocket_write(wsi,
							       buffer + LWS_SEND_BUFFER_PRE_PADDING,
							       n, LWS_WRITE_HTTP);
					if (m < 0)
						/* write failed, close conn */
						goto bail;
		
					/*
					 * http2 won't do this
					 */
					if (m != n)
						/* partial write, adjust */
						if (lseek(pss->fd, m - n, SEEK_CUR) < 0)
							goto bail;
		
					if (m) /* while still active, extend timeout */
						libwebsocket_set_timeout(wsi,
							PENDING_TIMEOUT_HTTP_CONTENT, 5);
					
					/* if we have indigestion, let him clear it before eating more */
					if (lws_partial_buffered(wsi))
						break;
		
				} while (!lws_send_pipe_choked(wsi));
		
		later:
				libwebsocket_callback_on_writable(context, wsi);
				break;
		flush_bail:
				/* true if still partial pending */
				if (lws_partial_buffered(wsi)) {
					libwebsocket_callback_on_writable(context, wsi);
					break;
				}
				close(pss->fd);
				goto try_to_reuse;
		
		bail:
				close(pss->fd);
				return -1;
		
			/*
			 * callback for confirming to continue with client IP appear in
			 * protocol 0 callback since no websocket protocol has been agreed
			 * yet.  You can just ignore this if you won't filter on client IP
			 * since the default uhandled callback return is 0 meaning let the
			 * connection continue.
			 */
		
			case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:
		
				/* if we returned non-zero from here, we kill the connection */
				break;
		
		#ifdef EXTERNAL_POLL
			/*
			 * callbacks for managing the external poll() array appear in
			 * protocol 0 callback
			 */
		
			case LWS_CALLBACK_LOCK_POLL:
				/*
				 * lock mutex to protect pollfd state
				 * called before any other POLL related callback
				 */
				break;
		
			case LWS_CALLBACK_UNLOCK_POLL:
				/*
				 * unlock mutex to protect pollfd state when
				 * called after any other POLL related callback
				 */
				break;
		
			case LWS_CALLBACK_ADD_POLL_FD:
		
				if (count_pollfds >= max_poll_elements) {
					lwsl_err("LWS_CALLBACK_ADD_POLL_FD: too many sockets to track\n");
					return 1;
				}
		
				fd_lookup[pa->fd] = count_pollfds;
				pollfds[count_pollfds].fd = pa->fd;
				pollfds[count_pollfds].events = pa->events;
				pollfds[count_pollfds++].revents = 0;
				break;
		
			case LWS_CALLBACK_DEL_POLL_FD:
				if (!--count_pollfds)
					break;
				m = fd_lookup[pa->fd];
				/* have the last guy take up the vacant slot */
				pollfds[m] = pollfds[count_pollfds];
				fd_lookup[pollfds[count_pollfds].fd] = m;
				break;
		
			case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
			        pollfds[fd_lookup[pa->fd]].events = pa->events;
				break;
		
		#endif
		
			case LWS_CALLBACK_GET_THREAD_ID:
				/*
				 * if you will call "libwebsocket_callback_on_writable"
				 * from a different thread, return the caller thread ID
				 * here so lws can use this information to work out if it
				 * should signal the poll() loop to exit and restart early
				 */
		
				/* return pthread_getthreadid_np(); */
		
				break;
		
			default:
				break;
			}
		
			return 0;
			
		try_to_reuse:
			if (lws_http_transaction_completed(wsi))
				return -1;
		
			return 0;
		
}
}

// Definition of function IMU_callback
static int
			callback_IMU(struct libwebsocket_context *context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason,
			void *user, void *in, size_t len) {
{
	
		
			int n, m;
			unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 512 +
								  LWS_SEND_BUFFER_POST_PADDING];
			unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
			struct per_session_data__IMU *pss = (struct per_session_data__IMU *)user;
		
			switch (reason) {
		
			case LWS_CALLBACK_ESTABLISHED:
				lwsl_info("callback_IMU: "
								 "LWS_CALLBACK_ESTABLISHED\n");
				pss->number = 0;
				break;
		
			case LWS_CALLBACK_SERVER_WRITEABLE:
				n = sprintf((char *)p, "%d", _instance->WSServer_M__var);
				m = libwebsocket_write(wsi, p, n, LWS_WRITE_TEXT);
				if (m < n) {
					lwsl_err("ERROR %d writing to di socket\n", n);
					return -1;
				}
				if (close_testing && pss->number == 50) {
					lwsl_info("close tesing limit, closing\n");
					return -1;
				}
				break;
		
			case LWS_CALLBACK_RECEIVE:
		//		fprintf(stderr, "rx %d\n", (int)len);
				if (len < 6)
					break;
				if (strcmp((const char *)in, "cmd_stop\n") == 0)
					
WSServer_send_WSService_CMDStop(_WSServer_Instance);

				if (strcmp((const char *)in, "cmd_start\n") == 0)
					
WSServer_send_WSService_CMDStart(_WSServer_Instance);

				break;
			/*
			 * this just demonstrates how to use the protocol filter. If you won't
			 * study and reject connections based on header content, you don't need
			 * to handle this callback
			 */
		
			case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
				dump_handshake_info(wsi);
				/* you could return non-zero here and kill the connection */
				break;
		
			default:
				break;
			}
		
			return 0;
		
}
}

// Fork a thread to execute the function f_WSServer_start_wsServer

// Struct for the parameters of the function  f_WSServer_start_wsServer
struct f_WSServer_start_wsServer_struct {
  struct WSServer_Instance *_instance;
   uint16_t Port;

  pthread_mutex_t *lock;
  pthread_cond_t *cv;
};

// Definition of function start_receiver_process (executed in a separate thread)
void f_WSServer_start_wsServer_run(struct WSServer_Instance *_instance, uint16_t Port)
{
  {
_WSServer_Instance = _instance;
		struct libwebsocket_protocols protocols_tmp[] = {
			/* first protocol must always be HTTP handler */
		
			{
				"http-only",		/* name */
				callback_http,		/* callback */
				sizeof (struct per_session_data__http),	/* per_session_data_size */
				0,			/* max frame size / rx buffer */
			},
			{
				"IMU-protocol",
				callback_IMU,
				sizeof(struct per_session_data__IMU),
				10,
			},
			{ NULL, NULL, 0, 0 } /* terminator */
		};
		protocols = &protocols_tmp;
		
		int port = Port;
		int n = 0;
		int use_ssl = 0;
		int opts = 0;
		char interface_name[128] = "";
		const char *iface = NULL;
		int syslog_options = LOG_PID | LOG_PERROR;
		unsigned int ms, oldms = 0;
		struct lws_context_creation_info info;
	
		int debug_level = 7;
	#ifndef LWS_NO_DAEMONIZE
		int daemonize = 0;
	#endif
	
		memset(&info, 0, sizeof info);
		info.port = port;
	
		
	#if !defined(LWS_NO_DAEMONIZE) && !defined(WIN32)
		/* 
		 * normally lock path would be /var/lock/lwsts or similar, to
		 * simplify getting started without having to take care about
		 * permissions or running as root, set to /tmp/.lwsts-lock
		 */
		if (daemonize && lws_daemonize("/tmp/.lwsts-lock")) {
			fprintf(stderr, "Failed to daemonize\n");
			return 1;
		}
	#endif
	
		
	
		/* we will only try to log things according to our debug_level */
		setlogmask(LOG_UPTO (LOG_DEBUG));
		openlog("lwsts", syslog_options, LOG_DAEMON);
	
		/* tell the library what debug level to emit and to send it to syslog */
		lws_set_log_level(debug_level, lwsl_emit_syslog);
	
		lwsl_notice("libwebsockets test server - "
				"(C) Copyright 2010-2015 Andy Green <andy@warmcat.com> - "
							    "licensed under LGPL2.1\n");
	
		printf("Using resource path \"%s\"\n", resource_path);
	#ifdef EXTERNAL_POLL
		max_poll_elements = getdtablesize();
		pollfds = malloc(max_poll_elements * sizeof (struct pollfd));
		fd_lookup = malloc(max_poll_elements * sizeof (int));
		if (pollfds == NULL || fd_lookup == NULL) {
			lwsl_err("Out of memory pollfds=%d\n", max_poll_elements);
			return -1;
		}
	#endif
	
		info.iface = iface;
		info.protocols = protocols;
	#ifndef LWS_NO_EXTENSIONS
		info.extensions = libwebsocket_get_internal_extensions();
	#endif
		info.ssl_cert_filepath = NULL;
		info.ssl_private_key_filepath = NULL;
		
		info.gid = -1;
		info.uid = -1;
		info.options = opts;
	
		context = libwebsocket_create_context(&info);
		if (context == NULL) {
			lwsl_err("libwebsocket init failed\n");
			return -1;
		}
	
		n = 0;
		while (n >= 0 && _instance->WSServer_Running__var) {
			struct timeval tv;
	
			gettimeofday(&tv, NULL);
	
			/*
			 * This provokes the LWS_CALLBACK_SERVER_WRITEABLE for every
			 * live websocket connection using the IMU protocol,
			 * as soon as it can take more packets (usually immediately)
			 */
	
			ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
			if ((ms - oldms) > 50) {
				libwebsocket_callback_on_writable_all_protocol(&protocols[PROTOCOL_IMU]);
				oldms = ms;
			}
	
	#ifdef EXTERNAL_POLL
	
			/*
			 * this represents an existing server's single poll action
			 * which also includes libwebsocket sockets
			 */
	
			n = poll(pollfds, count_pollfds, 50);
			if (n < 0)
				continue;
	
	
			if (n)
				for (n = 0; n < count_pollfds; n++)
					if (pollfds[n].revents)
						/*
						* returns immediately if the fd does not
						* match anything under libwebsockets
						* control
						*/
						if (libwebsocket_service_fd(context,
									  &pollfds[n]) < 0)
							goto done;
	#else
			/*
			 * If libwebsockets sockets are all we care about,
			 * you can use this api which takes care of the poll()
			 * and looping through finding who needed service.
			 *
			 * If no socket needs service, it'll return anyway after
			 * the number of ms in the second argument.
			 */
	
			n = libwebsocket_service(context, 50);
	#endif
		}
	
	#ifdef EXTERNAL_POLL
	done:
	#endif
	
		libwebsocket_context_destroy(context);
	
		lwsl_notice("libwebsockets-test-server exited cleanly\n");
	
		return 0;
	    
}

}


void f_WSServer_start_wsServer_proc(void * p)
{
  // Get parameters from the main thread
  struct f_WSServer_start_wsServer_struct params = *((struct f_WSServer_start_wsServer_struct *) p);
  
  // Unblock the main thread
  pthread_mutex_lock(params.lock);
  pthread_cond_signal(params.cv);
  pthread_mutex_unlock(params.lock);
  
  // Run the function
  //f_WSServer_start_wsServer_run(params._instance, params.esums_device);
  f_WSServer_start_wsServer_run(params._instance, params.Port);
}

// Operation called by the runtime and forking a new thread
void f_WSServer_start_wsServer(struct WSServer_Instance *_instance, uint16_t Port)
{
  // Store parameters
  struct f_WSServer_start_wsServer_struct params;
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
  pthread_create( &thread, NULL, f_WSServer_start_wsServer_proc, (void*) &params);
  // Wait until it has started and read its parameters
  pthread_cond_wait(params.cv, params.lock);
  // Realease mutex
  pthread_mutex_unlock(params.lock);
}

// On Entry Actions:
void WSServer_ServerChart_OnEntry(int state, struct WSServer_Instance *_instance) {
switch(state) {
case WSSERVER_SERVERCHART_STATE:
_instance->WSServer_ServerChart_State = WSSERVER_SERVERCHART_IDLE_STATE;
WSServer_ServerChart_OnEntry(_instance->WSServer_ServerChart_State, _instance);
break;
case WSSERVER_SERVERCHART_IDLE_STATE:
break;
case WSSERVER_SERVERCHART_RUNNING_STATE:
break;
default: break;
}
}

// On Exit Actions:
void WSServer_ServerChart_OnExit(int state, struct WSServer_Instance *_instance) {
switch(state) {
case WSSERVER_SERVERCHART_STATE:
WSServer_ServerChart_OnExit(_instance->WSServer_ServerChart_State, _instance);
break;
case WSSERVER_SERVERCHART_IDLE_STATE:
break;
case WSSERVER_SERVERCHART_RUNNING_STATE:
break;
default: break;
}
}

// Event Handlers for incoming messages:
void WSServer_handle_WSService_WSStart(struct WSServer_Instance *_instance, uint16_t Port) {
uint8_t WSServer_ServerChart_State_event_consumed = 0;
if (_instance->WSServer_ServerChart_State == WSSERVER_SERVERCHART_IDLE_STATE) {
if (WSServer_ServerChart_State_event_consumed == 0 && 1) {
WSServer_ServerChart_OnExit(WSSERVER_SERVERCHART_IDLE_STATE, _instance);
_instance->WSServer_ServerChart_State = WSSERVER_SERVERCHART_RUNNING_STATE;
{
_instance->WSServer_Running__var = 1;
_instance->WSServer_serverPort__var = Port;
fprintf(stdout, "[WSServer] Starting\n");

f_WSServer_start_wsServer(_instance, _instance->WSServer_serverPort__var);
fprintf(stdout, "[WSServer] Started\n");

WSServer_send_WSService_WSStarted(_instance);
}
WSServer_ServerChart_OnEntry(WSSERVER_SERVERCHART_RUNNING_STATE, _instance);
WSServer_ServerChart_State_event_consumed = 1;
}
}
}
void WSServer_handle_WSService_WSStop(struct WSServer_Instance *_instance) {
uint8_t WSServer_ServerChart_State_event_consumed = 0;
if (_instance->WSServer_ServerChart_State == WSSERVER_SERVERCHART_RUNNING_STATE) {
if (WSServer_ServerChart_State_event_consumed == 0 && 1) {
WSServer_ServerChart_OnExit(WSSERVER_SERVERCHART_RUNNING_STATE, _instance);
_instance->WSServer_ServerChart_State = WSSERVER_SERVERCHART_IDLE_STATE;
{
_instance->WSServer_Running__var = 0;
fprintf(stdout, "[WSServer] Stop\n");

}
WSServer_ServerChart_OnEntry(WSSERVER_SERVERCHART_IDLE_STATE, _instance);
WSServer_ServerChart_State_event_consumed = 1;
}
}
}
void WSServer_handle_WSService_sendM(struct WSServer_Instance *_instance, long m) {
uint8_t WSServer_ServerChart_State_event_consumed = 0;
if (_instance->WSServer_ServerChart_State == WSSERVER_SERVERCHART_RUNNING_STATE) {
if (WSServer_ServerChart_State_event_consumed == 0 && 1) {
{
_instance->WSServer_M__var = m;
}
WSServer_ServerChart_State_event_consumed = 1;
}
}
}

// Observers for outgoing messages:
void (*WSServer_send_WSService_WSStarted_listener)(struct WSServer_Instance*)= 0x0;
void register_WSServer_send_WSService_WSStarted_listener(void (*_listener)(struct WSServer_Instance*)){
WSServer_send_WSService_WSStarted_listener = _listener;
}
void WSServer_send_WSService_WSStarted(struct WSServer_Instance *_instance){
if (WSServer_send_WSService_WSStarted_listener != 0x0) WSServer_send_WSService_WSStarted_listener(_instance);
}
void (*WSServer_send_WSService_CMDStop_listener)(struct WSServer_Instance*)= 0x0;
void register_WSServer_send_WSService_CMDStop_listener(void (*_listener)(struct WSServer_Instance*)){
WSServer_send_WSService_CMDStop_listener = _listener;
}
void WSServer_send_WSService_CMDStop(struct WSServer_Instance *_instance){
if (WSServer_send_WSService_CMDStop_listener != 0x0) WSServer_send_WSService_CMDStop_listener(_instance);
}
void (*WSServer_send_WSService_CMDStart_listener)(struct WSServer_Instance*)= 0x0;
void register_WSServer_send_WSService_CMDStart_listener(void (*_listener)(struct WSServer_Instance*)){
WSServer_send_WSService_CMDStart_listener = _listener;
}
void WSServer_send_WSService_CMDStart(struct WSServer_Instance *_instance){
if (WSServer_send_WSService_CMDStart_listener != 0x0) WSServer_send_WSService_CMDStart_listener(_instance);
}

