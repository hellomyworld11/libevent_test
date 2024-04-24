#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

struct timeval tv;

event* timerev;

void timer_cb(evutil_socket_t sig, short events, void* user_data)
{
	printf("≤‚ ‘ libevent timer\n");
	event_add(timerev, &tv);
}


int main(int argc, char *argv[])
{
#ifdef _WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	event_base* base = event_base_new();
	
	timerev = evtimer_new(base, timer_cb, NULL);

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	event_add(timerev, &tv);

	event_base_dispatch(base);
	return 0;
}