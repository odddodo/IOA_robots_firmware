#ifndef allTheTalking_h
#define allTheTalking_h

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

int localPort = 8888;
char receiveBuffer[UDP_TX_PACKET_MAX_SIZE];
char replyBuffer[REPLY_BUFF_SIZE] = "blankReply";
IPAddress myIP(192, 168, 0, 100);
byte myMAC[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02};
EthernetUDP Udp;

bool gotSomeData = false;
bool gotDriveData = false;

const char drive_pre = 'D', stop_pre = 'S', handshake_pre = 'H', reply_pre = 'R', fill_post = '!';
String masterName;

void initUDPServer()
{
    Ethernet.begin(myMAC, myIP);
    Udp.begin(localPort);
}

void manageCmdMessages()
{
    String repl_msg;
    int r_msg_len;
    switch (receiveBuffer[0])
    {
    case (handshake_pre):

        masterName = String(receiveBuffer).substring(2);
        repl_msg.concat(reply_pre);
        repl_msg.concat(handshake_pre);
        repl_msg.concat(masterName);
        r_msg_len = repl_msg.length();
        if (DEBUG_CMD_MSGS)
        {
            DEBUG("that is a handshake! with: " + masterName);
        }

        break;
    case (drive_pre):
        if (DEBUG_CMD_MSGS)
        {
            DEBUG("that is a drive cmd!");
        }
        gotDriveData = true;
        break;
    case (stop_pre):

        break;
    default:
        if (DEBUG_CMD_MSGS)
        {
            DEBUG("no idea what that is!");
        }
        gotDriveData = false;
        break;
    }
    if (r_msg_len < REPLY_BUFF_SIZE)
    {
        for (int i = 0; i < REPLY_BUFF_SIZE - r_msg_len; i++)
        {
            repl_msg.concat(fill_post);
        }
    }
    repl_msg.toCharArray(replyBuffer, REPLY_BUFF_SIZE);
}

void handleIncommmingPackets()
{
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        Udp.read(receiveBuffer, UDP_TX_PACKET_MAX_SIZE);
        gotSomeData = true;
        manageCmdMessages();
        if (DEBUG_UDP)
        {
            DEBUG(receiveBuffer);
        }
    }
    else
    {
        gotSomeData = false;
    }
}

void handleReplies()
{
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyBuffer);
    Udp.endPacket();
}

int *decodeIncommingData(char input[])
{
    static int output[4];
    String s = String(input);

    int s_end = s.lastIndexOf("_");
    int s_I = s.lastIndexOf("I") + 1;
    int I_val = s.substring(s_I, s_end).toInt();
    int s_R = s.lastIndexOf("R") + 1;
    int R_val = s.substring(s_R, s_I - 2).toInt();
    int s_D = s.lastIndexOf("D") + 1;
    int D_val = s.substring(s_D, s_R - 2).toInt();
    int s_F = s.lastIndexOf("F") + 1;
    int F_val = s.substring(s_F, s_D - 2).toInt();
    output[0] = F_val;
    output[1] = D_val;
    output[2] = R_val;
    output[3] = I_val;
    if (DEBUG_UDP)
    {
        DEBUG("data[0]:" + String(output[0]) + "_data[1]:" + String(output[1]) + "_data[2]:" + String(output[2]) + "_data[3]:" + String(output[3]));
    }
    return output;
}

#endif