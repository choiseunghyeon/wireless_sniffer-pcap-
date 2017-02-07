#ifndef PACKETINFO_H
#define PACKETINFO_H


#include <stdint.h>
#include <netinet/in.h>

/* ethernet_header struct */
#define ETHERTYPE_IP 0x0800
#define ETHERTYPE_ARP 0x0806

struct ethernet
{
    uint8_t ether_dhost[6];
    uint8_t ether_shost[6];
    uint16_t ether_type;

}
__attribute__((__packed__));

/* ip header struct */

struct ip
{
    uint8_t ip_hl:4;
    uint8_t ip_v:4;
    uint8_t ip_tos;
    uint16_t ip_len;
     uint16_t ip_id;
     uint16_t ip_off;
#define IP_RF 0x8000
#define IP_DF 0x4000
#define IP_MF 0x2000
#define IP_OFFMASK 0x1fff
     uint8_t ip_ttl;
     uint8_t ip_p;
     uint16_t ip_sum;
     struct in_addr ip_src,ip_dst;

}
__attribute__((__packed__));

/* tcp header struct */
typedef uint32_t tcp_seq;

struct tcphdr
{
    uint16_t th_sport;
    uint16_t th_dport;
    tcp_seq th_seq;
    tcp_seq th_ack;
    uint8_t th_x2:4;
    uint8_t th_off:4;
    uint8_t th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
   #define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
    uint16_t th_win;
    uint16_t th_sum;
    uint16_t th_urp;
}
__attribute__((__packed__));

void dump_tcp_header(void *iphdr);

#endif // PACKETINFO_H
