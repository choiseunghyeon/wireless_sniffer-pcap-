#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcap.h" /* if this gives you an error try pcap/pcap.h */
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include "packetinfo.h"
#include "wirelessframe.h"
#include "function.h"
#include <stdint.h>



void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);



int main()
{
pcap_if_t *alldevs;
pcap_if_t *d;
int inum;
int i=0;
pcap_t *adhandle;
char errbuf[PCAP_ERRBUF_SIZE];

    reset_voice_flag();

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

    chkenv(d); //check monitor mode. I will add some function.

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

     struct Radiotap *prp;
     struct probe_request *pprobe_r;
     struct Wlan_frame *pwframe;

     prp=(struct prp *)pkt_data;
     pkt_data+=sizeof(struct Radiotap);
     pprobe_r=(struct probe_request *)pkt_data;
     pkt_data+=sizeof(struct probe_request);
     pwframe=(struct pwframe *)pkt_data;


     if(prp->Header_revision == 0x00 && prp->Header_pad == 0x00){
          if(pprobe_r->Subtype==0x40){
          printf("find probe\n");
          printf("length: %d",prp->Header_length);
          printf(" dst mac: %02x:%02x:%02x:%02x:%02x:%02x",
                 pprobe_r->Dest_addr[0], pprobe_r->Dest_addr[1],pprobe_r->Dest_addr[2],
                 pprobe_r->Dest_addr[3], pprobe_r->Dest_addr[4], pprobe_r->Dest_addr[5]);
          printf(" src mac : %02x:%02x:%02x:%02x:%02x:%02x\n",
                 pprobe_r->sour_addr[0], pprobe_r->sour_addr[1],pprobe_r->sour_addr[2],
                 pprobe_r->sour_addr[3], pprobe_r->sour_addr[4], pprobe_r->sour_addr[5]);

         printf("\n");
              for(int num=0;num<USER_NUMBER;num++){
                  if(chgstr(pprobe_r->sour_addr,&user_mac[num]))
                    voice(&user_voice_flag[num]);
              }
          }
     }
}

 /*
남은 기능
1. 사용자를 정확하게 판별하여 voice()실행시키게 하기 _ solve
2. voice()는 한번만 실행시키기_시간을 정해놓고 특정 시간마다 flag를 초기화_solve
3. sleep()을 이용하여 몇분씩 끊어서 패킷 받기
4. 데이터를 처리해줄 db 또는 하둡 쓰기
5. 처음에 monitor 모드 및 voice 파일 설정 및 확인해주는 기능 만들기 -> voice 설정 및 코드 재구성 하기
6. 처음에만 설정하는 것 만들기 ex) mac의 갯수


참고사항
1. 지정된 mac은 고정 되있다고 가정
2. 커널 프로그래밍을 통해서 하드웨어가 보내는 정보를 파싱해서 써보기(가능한지 알아보기)
3. iwconfig가 syscall을 이용해서 정보를 파싱해온다면 iwconfig를 통하지 않고 내 프로그램에서 직접  파싱해올 수도 있을 것.. 이러면 속도가 빨라지니까 한번 도전하자

문제점
1. 핸드폰의 화면을 켰을 때만 probe나 wireless 패킷을 보냄
즉 화면을 안키면 패킷의 흐름이 없어서 출결에 어려움이 존재함
2. QoS의 경우 키지  않아도 패킷을 보냄

*/
