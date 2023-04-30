#define MSG_MAX_LEN 100


/*
the communiation protocol is as follows:


====================================
*from client to server only:

send: CONNECT
return: assigned ID
or -1(fail)

send: DISCONNECT
return: 0(success)
or -1(fail)

send: MAPGET
return: 0(success) (start sending map data)
or -1(fail)

send: MAPDATA argument
return: 0(success) (continue waiting for map data)
or -1(fail)

send: MAPEND
return: 0(success) (end waiting for map data)
or -1(fail)
====================================
*from both client and server:

send: MOVE argument
return: 0(success)
or -1(fail)

send: PAUSE
return: 0(success)
or -1(fail)

send: RESUME
return: 0(success)
or -1(fail)
====================================
*from server to client only:

send: START
return: 0(success)
or -1(fail)
====================================




*/