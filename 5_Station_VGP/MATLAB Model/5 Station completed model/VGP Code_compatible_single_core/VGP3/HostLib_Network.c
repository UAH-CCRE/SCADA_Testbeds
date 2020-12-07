/**
 * @file HostLib_Network.c
 * Copyright 2009 The MathWorks, Inc.
 */ 

#include "HostLib_Network.h"
#include <string.h>
#include <stdio.h>

#if defined(_WIN32)
const char *libName_Network = "networkdevice.dll";
#elif defined(__APPLE__)
const char *libName_Network = "libmwnetworkdevice.dylib";
#else
const char *libName_Network = "libmwnetworkdevice.so";
#endif

#ifdef _USE_TARGET_UDP_
void CreateTargetUDPInterface(void *hl);
void DestroyTargetUDPInterface(void *hl);
#endif

void CreateUDPInterface(void *hl) 
{
#ifndef _USE_TARGET_UDP_
    CreateHostLibrary(libName_Network, hl);
#else
    CreateTargetUDPInterface(hl);
#endif
}
void DestroyUDPInterface(void *hl) 
{
#ifndef _USE_TARGET_UDP_
    DestroyHostLibrary(hl);
#else
    DestroyTargetUDPInterface(hl);
#endif
}


void LibCreate_Network(void *hl, int inOut, const char *localURL, int localPort, 
                       const char *remoteURL, int remotePort, int bufferSize, int bytesPerSample, int blockingTime)
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    *hostLib->errorMessage  = '\0';
    (MAKE_FCN_PTR(pFnLibCreate_Network,hostLib->libCreate))(&hostLib->instance, hostLib->errorMessage, (NetworkInputOrOutput)inOut, 
                                                    localURL, localPort, remoteURL, remotePort, bufferSize, bytesPerSample, blockingTime);
}
void LibUpdate_Network(void *hl, const void *src, int nSamples)
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    if(hostLib->instance)
        (MAKE_FCN_PTR(pFnLibUpdate_Network,hostLib->libUpdate))(hostLib->instance, hostLib->errorMessage, src, nSamples);
}
void LibOutputs_Network(void *hl, void *src, int *nSamples)
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    if(hostLib->instance)
        (MAKE_FCN_PTR(pFnLibOutputs_Network,hostLib->libOutputs))(hostLib->instance, hostLib->errorMessage, src, nSamples);
}
