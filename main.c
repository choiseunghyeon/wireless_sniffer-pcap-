#include <stdio.h>
#include <stdlib.h>
#include "pcap.h" /* if this gives you an error try pcap/pcap.h */
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include "packetinfo.h"
#include "wirelessframe.h"

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main()
{
pcap_if_t *alldevs;
pcap_if_t *d;
int inum;
int i=0;
pcap_t *adhandle;
char errbuf[PCAP_ERRBUF_SIZE];

    /* Retrieve the device list on the local machine */
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }

    /* Print the list */
    for(d=alldevs; d; d=d->next)
    {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
    }

    if(i==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -1;
    }

    printf("Enter the interface number (1-%d):",i);
    scanf("%d", &inum);

    if(inum < 1 || inum > i)
    {
        printf("\nInterface number out of range.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return -1;
    }

    /* Jump to the selected adapter */
    for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

    /* Open the device */
    if (!(adhandle=pcap_open_live(d->name,65536,1,1,errbuf)))
    {
        printf("pcap_open_live error %s \n",d->name);
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return -1;
    }


    printf("\nlistening on %s...\n", d->description);

    /* At this point, we don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);

    /* start the capture */
    pcap_loop(adhandle,0,packet_handler,NULL);

    return 0;
}


/* Callback function invoked by libpcap for every incoming packet */
 void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
     //struct ethernet *pethernet;
     //struct ip *pip;
     //struct tcphdr *ptcphdr;
     struct Radiotap *prp;
     struct probe_request *pprobe_r;
     struct Wlan_frame *pwframe;

     int k=0;
     k++;
      printf("%d  :  %02x", k,*pkt_data);


     /*prp=(struct prp *)pkt_data;
     pkt_data+=sizeof(struct Radiotap);
     pprobe_r=(struct probe_request *)pkt_data;
     pkt_data+=sizeof(struct probe_request);
     pwframe=(struct pwframe *)pkt_data;

     if(prp->Header_revision == 0x00 && prp->Header_pad == 0x00){
        for(int i=0;i<sizeof(struct Radiotap);i++){
            if(i%16 == 0)
                printf("\n");
            printf("%02x ",  prp[i]);
        }
    }*/

     /*if((ntohs(pethernet->ether_type)==ETHERTYPE_IP))
     {
     printf("ethernet : dst mac : %02x:%02x:%02x:%02x:%02x:%02x   src mac : %02x:%02x:%02x:%02x:%02x:%02x   ether_type : %04x\n",
            pethernet->ether_dhost[0],pethernet->ether_dhost[1],pethernet->ether_dhost[2],pethernet->ether_dhost[3],pethernet->ether_dhost[4],pethernet->ether_dhost[5],
            pethernet->ether_shost[0],pethernet->ether_shost[1],pethernet->ether_shost[2],pethernet->ether_shost[3],pethernet->ether_shost[4],pethernet->ether_shost[5],
             ntohs(pethernet->ether_type));
    printf("IP : ");
    printf("Src Address : %s\n", inet_ntoa(pip->ip_src));
    printf("Dst Address : %s\n", inet_ntoa(pip->ip_dst));
    printf("Header Len  : %d\n", (pip->ip_hl)*4);

         if(pip->ip_p==0x06)
        {
         printf(" TCP : src port : %d -> dst port : %d\n", ntohs(ptcphdr->th_sport),ntohs(ptcphdr->th_dport));
        }

    } */
}
