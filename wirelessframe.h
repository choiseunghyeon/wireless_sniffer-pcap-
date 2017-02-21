#ifndef WIRELESSFRAME_H
#define WIRELESSFRAME_H


#include <stdint.h>
#define MAC_LEN 6

struct Radiotap{ //18byte or 24byte 무선랜카드 또는 wifi에 따라 raditap의 크기가 달라짐
    uint8_t Header_revision;
    uint8_t Header_pad;
    uint16_t Header_length;
    uint64_t Present_flags;
    uint8_t flags;
    uint8_t Data_Rate;
    uint16_t Channel_frequency;
    uint16_t Channel_flags;
    uint8_t SSI_Signal;
    uint8_t dummy;
    uint8_t RX_flags[2];
    uint8_t SSI_Signal2;
    uint8_t Antenna;

}
__attribute__((__packed__));

struct QoS_Radiotap{ //27byte
    uint8_t Header_revision;
    uint8_t Header_pad;
    uint16_t Header_length;
    uint64_t Present_flags;
    uint8_t flags;
    uint8_t dummy;
    uint16_t Channel_frequency;
    uint16_t Channel_flags;
    uint8_t SSI_Signal;
    uint8_t dummy2;
    uint8_t RX_flags[2];
    uint8_t MCS_info[3];
    uint8_t SSI_Signal2;
    uint8_t Antenna;
}
__attribute__((__packed__));

struct probe_request{ // 24byte
    uint8_t Subtype;
    uint8_t Control_Field;
    uint16_t dummy;
    uint8_t Dest_addr[6]; // Receiver == Dest
    uint8_t sour_addr[6]; // Transmitter == source
    uint8_t bssid[6];
    uint8_t num[2]; // Fragment, Sequence
}
__attribute__((__packed__));


struct QoS{
    uint8_t Subtype;
    uint8_t flags;
    uint16_t dummy;
    uint8_t Dest_addr[6];
    uint8_t bssid[6];
    uint8_t sour_addr[6];
    uint16_t dummy2;
    uint16_t control;
    uint64_t CCMP_param;

}
__attribute__((__packed__));

struct Wlan_frame{
    uint8_t dont_care[90];
};


/*      if(1){
         for(int i=0;i<sizeof(struct probe_request);i++){
             printf("%02x %02x %04x dst: %02x %02x %02x %02x %02x %02x src: %02x %02x %02x %02x %02x %02x\n"
                    ,pprobe_r->Subtype,pprobe_r->Control_Field,pprobe_r->dummy,
                    pprobe_r->Dest_addr[0],pprobe_r->Dest_addr[1],pprobe_r->Dest_addr[2],
                    pprobe_r->Dest_addr[3],pprobe_r->Dest_addr[4],pprobe_r->Dest_addr[5],
                    pprobe_r->sour_addr[0],pprobe_r->sour_addr[1],pprobe_r->sour_addr[2],
                    pprobe_r->sour_addr[3],pprobe_r->sour_addr[4],pprobe_r->sour_addr[5]);
         }
     }*/
#endif // WIRELESSFRAME_H

