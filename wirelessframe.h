#ifndef WIRELESSFRAME_H
#define WIRELESSFRAME_H


#include <stdint.h>
#include <netinet/in.h>

struct Radiotap{
    uint8_t Header_revision;
    uint8_t Header_pad;
    uint8_t Header_length[2];
    uint8_t Present_flags[8];
    uint8_t flags;
    uint8_t Data_Rate;
    uint8_t Channel_frequency[2];
    uint8_t Channel_flags[2];
    uint8_t SSI_Signal;
    uint8_t dummy;
    uint8_t RX_flags[2];
    uint8_t SSI2_Siganl;
    uint8_t Antenna;
}
__attribute__((__packed__));

struct probe_request{
    uint8_t Subtype;
    uint8_t Control_Field[2];
    uint16_t dummy;
    uint8_t Dest_addr[6]; // Receiver == Dest
    uint8_t sour_addr[6]; // Transmitter == source
    uint8_t bssid[6];
    uint8_t num[2]; // Fragment, Sequence
}
__attribute__((__packed__));

struct Wlan_frame{
    uint8_t dont_care[90];
};

#endif // WIRELESSFRAME_H

