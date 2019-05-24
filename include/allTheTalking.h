#ifndef allTheTalking_h
#define allTheTalking_h

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

int localPort = 8888;
char receiveBuffer[UDP_TX_PACKET_MAX_SIZE];
char replyBuffer[REPLY_BUFF_SIZE] = "RA_ready!!";

IPAddress myIP(192, 168, 0, 100);
byte myMAC[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02};
EthernetUDP Udp;

bool gotSomeData = false;
bool gotDriveData = false;

const char drive_pre = 'D', stop_pre = 'S', handshake_pre = 'H', telemetry_pre = 'T', reply_pre = 'R', available_pre = 'A', fill_suffix = '!';

String masterName;
String reply_msg;
String received_msg;
int r_msg_len;

int sensorFeedbackTimer = 0;
int sendSensorUpdateEvery = 50;

int battVal = 1024;

void initUDPServer()
{
    Ethernet.begin(myMAC, myIP);
    Udp.begin(localPort);
}

void manageCmdMessages()
{
    reply_msg.remove(1);
    switch (receiveBuffer[0])
    {
    case (handshake_pre):
        masterName = received_msg.substring(2, 9);

        if (!reply_msg.startsWith("R"))
        {
            reply_msg.concat(reply_pre);
        }
        reply_msg.concat(handshake_pre);
        reply_msg.concat(masterName);

        if (DEBUG_CMD_MSGS)
        {
            DEBUG("that is a handshake with: " + masterName);
        }

        break;
    case (drive_pre):
        if (sensorFeedbackTimer < sendSensorUpdateEvery)
        {
            if (!reply_msg.startsWith("R"))
            {
                reply_msg.concat(reply_pre);
            }
            reply_msg.concat(drive_pre);
            reply_msg.concat("easy");
            sensorFeedbackTimer++;
        }
        else if (sensorFeedbackTimer == sendSensorUpdateEvery)
        {

            if (!reply_msg.startsWith("R"))
            {
                reply_msg.concat(reply_pre);
            }
            reply_msg.concat(telemetry_pre);
            reply_msg.concat(battVal);
            sensorFeedbackTimer = 0;
        }

        if (DEBUG_CMD_MSGS)
        {
            //DEBUG("that is a drive cmd: " + driveFeedbackMsg);
        }
        gotDriveData = true;
        break;
    case (telemetry_pre):

        if (!reply_msg.startsWith("R"))
        {
            reply_msg.concat(reply_pre);
        }
        reply_msg.concat(telemetry_pre);
        reply_msg.concat(battVal);
        if (DEBUG_CMD_MSGS)
        {
            DEBUG("battery value: !" + battVal);
        }
        break;

    case (stop_pre):
        if (!reply_msg.startsWith("R"))
        {
            reply_msg.concat(reply_pre);
        }
        reply_msg.concat(available_pre);
        reply_msg.concat("stopped!");
        gotDriveData = false;
        masterName = NO_MASTER;
        if (DEBUG_CMD_MSGS)
        {
            DEBUG("stopping immediately!");
            DEBUG(masterName);
        }
        break;
    case (available_pre):
        if (masterName = NO_MASTER)
        {
            if (!reply_msg.startsWith("R"))
            {
                reply_msg.concat(reply_pre);
            }
            reply_msg.concat(available_pre);
            reply_msg.concat("available");
        }
        break;
    default:
        if (DEBUG_CMD_MSGS)
        {
            DEBUG("no idea what that is!");
        }
        gotDriveData = false;
        break;
    }
    if (r_msg_len < REPLY_BUFF_SIZE - 1)
    {
        for (int i = 0; i < REPLY_BUFF_SIZE - r_msg_len - 1; i++)
        {
            reply_msg.concat(fill_suffix);
        }
    }

    reply_msg.toCharArray(replyBuffer, REPLY_BUFF_SIZE);
    if (DEBUG_CMD_MSGS)
    {
        DEBUG("reply msg:" + reply_msg);
    }
}

void handleIncommmingPackets()
{
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        Udp.read(receiveBuffer, UDP_TX_PACKET_MAX_SIZE);
        received_msg = String(receiveBuffer);
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
        //gotDriveData = false;//stutters
    }
}

void handleReplies()
{

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyBuffer);
    Udp.endPacket();
    if (DEBUG_CMD_MSGS)
    {

        DEBUG(replyBuffer);
    }
}

int *decodeIncommingData(char input[])
{
    static int output[4];
    String s = String(input);

    int s_end = s.lastIndexOf(";");
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
    //driveFeedbackMsg = "data[0]:" + String(output[0]) + "_data[1]:" + String(output[1]) + "_data[2]:" + String(output[2]) + "_data[3]:" + String(output[3]);
    return output;
}

#endif