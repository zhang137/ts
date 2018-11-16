#ifndef PROTOCAL_H
#define PROTOCAL_H

void use_rawip_socket();

void use_normal_socket();

void send_packet();

int parcel_proto_packet(const char *, int *);

void send_packet_flood();

void wait_client_connect();

void scan_host();

void wait_packet();

#endif //PROTOCAL_H

