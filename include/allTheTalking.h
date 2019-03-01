#ifndef allTheTalking_h
#define allTheTalking_h

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

int localPort = 8888;
char replyBuffer[] = "got it!";
char receiveBuffer[UDP_TX_PACKET_MAX_SIZE];
IPAddress myIP(192, 168, 0, 100);
byte myMAC[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02};
EthernetUDP Udp;

void initUDPServer()
{
    Ethernet.begin(myMAC, myIP);
    Udp.begin(localPort);
}

void handleIncommmingPackets()
{
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        Udp.read(receiveBuffer, UDP_TX_PACKET_MAX_SIZE);
        DEBUG(receiveBuffer);
    }
}

#endif