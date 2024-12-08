Sockets are endpoint, where computer sends/receives connections. With protocols we say this is the way we will communicate.

UDP - Connectionless 
    Packets sends without order, non numeric, doesn't receive info about packet is received, packed may arrive twice.
    Used mainly in live oriented scenarios, IoTs and DNS services. Supports multicast and broadcast.

TCP - Connection oriented
    Packets sends with order numerically, receive info about packet is received. If not resends. May send twice but server pass it.
    Used mainly in web pages, mail services, file transfer, ssh. Doesn't support multicast or broadcast as it is bidirectional connection.

tcp server/client
udp server/client



Functions:
Socket()  https://man7.org/linux/man-pages/man2/socket.2.html
Bind()  https://man7.org/linux/man-pages/man2/bind.2.html
Listen()    https://man7.org/linux/man-pages/man2/listen.2.html
Connect()   https://man7.org/linux/man-pages/man2/connect.2.html
Send()  https://man7.org/linux/man-pages/man2/send.2.html
Recv() https://man7.org/linux/man-pages/man2/recv.2.html
Close() https://man7.org/linux/man-pages/man2/close.2.html
Shutdown()  https://man7.org/linux/man-pages/man2/shutdown.2.html
Select() https://man7.org/linux/man-pages/man2/select.2.html (non modern)
getnameinfo()   https://man7.org/linux/man-pages/man3/getnameinfo.3p.html
setsockopt() https://man7.org/linux/man-pages/man3/setsockopt.3p.html
fcntl() https://man7.org/linux/man-pages/man2/fcntl.2.html
