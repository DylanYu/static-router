#include "set_data.h"
#include "sr_protocol.h"
#include "sr_utils.h"

void set_ether_hdr(uint8_t* sp, uint8_t dhost[], uint8_t shost[], \
                    uint16_t type) {
    sr_ethernet_hdr_t* hdr = sp;
    int i;
    for (i = 0; i < ETHER_ADDR_LEN; i++) {
        hdr->ether_dhost[i] = dhost[i];
        hdr->ether_shost[i] = shost[i];
    }
    hdr->ether_type = type;
}

void set_ip_hdr(uint8_t* sp, uint8_t tos, uint16_t len, uint16_t id, \
                uint16_t off, uint8_t ttl, uint8_t pro, \
                uint32_t src, uint32_t dst) {
    sr_ip_hdr_t* hdr = sp;
    hdr->ip_v = 4;
    hdr->ip_hl = 4;
    hdr->ip_tos = tos;
    hdr->ip_len = len;
    hdr->ip_id = id;
    hdr->ip_off = off;
    hdr->ip_ttl = ttl; 
    hdr->ip_p = pro;
    hdr->ip_src = src;
    hdr->ip_dst = dst;
    hdr->ip_sum = cksum(hdr, IP_HDR_LEN);
}

void set_arp_hdr(uint8_t* sp, unsigned short hrd, unsigned short pro, \
                unsigned char hln, unsigned char pln, unsigned short op, \
                unsigned char sha[], uint32_t sip, \
                unsigned tha[], uint32_t tip) {
    sr_arp_hdr_t* hdr = sp;
    hdr->ar_hrd = hrd;
    hdr->ar_pro = pro;
    hdr->ar_hln = hln;
    hdr->ar_pln = pln;
    hdr->ar_op = op;
    int i;
    for (i = 0; i < ETHER_ADDR_LEN; i++) {
        hdr->ar_sha[i] = sha[i];
        hdr->ar_tha[i] = tha[i];
    }
    hdr->ar_sip = sip;
    hdr->ar_tip = tip;
}

void set_icmp_hdr(uint8_t* sp, uint8_t type, uint8_t code) {
    sr_icmp_hdr_t* hdr = sp;
    hdr->icmp_type = type;
    hdr->icmp_code = code;
    hdr->icmp_sum = cksum(hdr, ICMP_HDR_LEN);
}

