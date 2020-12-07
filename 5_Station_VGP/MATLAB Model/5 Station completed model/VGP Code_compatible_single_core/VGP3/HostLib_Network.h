/**
 * @file HostLib_Network.h
 * @brief A UDP Netowrk interface
 * Copyright 2009 The MathWorks, Inc.
 */ 


/* Wrap everything in extern C */
#ifdef __cplusplus
extern "C" {
#endif 

extern const char *libName_Network;

typedef enum {
    NETWORK_INPUT  = 0,
    NETWORK_OUTPUT = 1
} NetworkInputOrOutput;

/*******************************
 * Routines which are defined in the library in question
 *******************************/
typedef void (*pFnLibCreate_Network)(void **device, char *err, NetworkInputOrOutput inOut, const char *localURL, int localPort, 
                             const char *remoteURL, int remotePort, int bufferSize, int bytesPerSample, int blockingTime);
typedef void (*pFnLibUpdate_Network)(void *device, char *err, const void *src, int nSamples);
typedef void (*pFnLibOutputs_Network)(void *device, char *err, void *src, int* nSamples);

/*******************************
 * Routines which we define to call the functions in the library 
 *******************************/

void CreateUDPInterface(void *hl);
void DestroyUDPInterface(void *hl);

void LibCreate_Network(void *hostLib, int inOut, const char *localURL, int localPort, 
                       const char *remoteURL, int remotePort, int bufferSize, int bytesPerSample, int blockingTime);
void LibUpdate_Network(void *hostLib, const void *src, int nSamples);
void LibOutputs_Network(void *hostLib, void *src, int *nSamples);

/* Include HostLib for declarations of LibStart, LibTerminate, CreateHostLibrary, and DestroyHostLibrary. */
#include "HostLib_rtw.h"

#ifdef __cplusplus
} // extern "C"
#endif 
