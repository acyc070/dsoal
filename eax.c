/* DirectSound EAX interface
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define CONST_VTABLE
#include <stdarg.h>
#include <string.h>

#include "windows.h"
#include "dsound.h"

#include "dsound_private.h"
#include "eax-presets.h"


/*******************
 * EAX 4 stuff
 ******************/

HRESULT EAX4Context_Query(DSPrimary *prim, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(prim->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~EAXCONTEXT_PARAMETER_DEFERRED))
    {
    case EAXCONTEXT_NONE:
    case EAXCONTEXT_ALLPARAMETERS:
    case EAXCONTEXT_PRIMARYFXSLOTID:
    case EAXCONTEXT_DISTANCEFACTOR:
    case EAXCONTEXT_AIRABSORPTIONHF:
    case EAXCONTEXT_HFREFERENCE:
    case EAXCONTEXT_LASTERROR:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}

HRESULT EAX4Slot_Query(DSPrimary *prim, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(prim->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~EAXFXSLOT_PARAMETER_DEFERRED))
    {
    case EAXFXSLOT_NONE:
    case EAXFXSLOT_ALLPARAMETERS:
    case EAXFXSLOT_LOADEFFECT:
    case EAXFXSLOT_VOLUME:
    case EAXFXSLOT_LOCK:
    case EAXFXSLOT_FLAGS:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    /* FIXME: This should probably only succeed for the available parameters of
     * the current effect type.
     */
    if((propid&~EAXFXSLOT_PARAMETER_DEFERRED) <= EAXREVERB_FLAGS)
    {
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}

HRESULT EAX4Source_Query(DSBuffer *buf, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(buf->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~EAXSOURCE_PARAMETER_DEFERRED))
    {
    case EAXSOURCE_NONE:
    case EAXSOURCE_ALLPARAMETERS:
    case EAXSOURCE_OBSTRUCTIONPARAMETERS:
    case EAXSOURCE_OCCLUSIONPARAMETERS:
    case EAXSOURCE_EXCLUSIONPARAMETERS:
    case EAXSOURCE_DIRECT:
    case EAXSOURCE_DIRECTHF:
    case EAXSOURCE_ROOM:
    case EAXSOURCE_ROOMHF:
    case EAXSOURCE_OBSTRUCTION:
    case EAXSOURCE_OBSTRUCTIONLFRATIO:
    case EAXSOURCE_OCCLUSION:
    case EAXSOURCE_OCCLUSIONLFRATIO:
    case EAXSOURCE_OCCLUSIONROOMRATIO:
    case EAXSOURCE_OCCLUSIONDIRECTRATIO:
    case EAXSOURCE_EXCLUSION:
    case EAXSOURCE_EXCLUSIONLFRATIO:
    case EAXSOURCE_OUTSIDEVOLUMEHF:
    case EAXSOURCE_DOPPLERFACTOR:
    case EAXSOURCE_ROLLOFFFACTOR:
    case EAXSOURCE_ROOMROLLOFFFACTOR:
    case EAXSOURCE_AIRABSORPTIONFACTOR:
    case EAXSOURCE_FLAGS:
    case EAXSOURCE_SENDPARAMETERS:
    case EAXSOURCE_ALLSENDPARAMETERS:
    case EAXSOURCE_OCCLUSIONSENDPARAMETERS:
    case EAXSOURCE_EXCLUSIONSENDPARAMETERS:
    case EAXSOURCE_ACTIVEFXSLOTID:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}


/*******************
 * EAX 3 stuff
 ******************/

HRESULT EAX3_Query(DSPrimary *prim, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(prim->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~DSPROPERTY_EAX30LISTENER_DEFERRED))
    {
    case DSPROPERTY_EAX30LISTENER_NONE:
    case DSPROPERTY_EAX30LISTENER_ALLPARAMETERS:
    case DSPROPERTY_EAX30LISTENER_ENVIRONMENT:
    case DSPROPERTY_EAX30LISTENER_ENVIRONMENTSIZE:
    case DSPROPERTY_EAX30LISTENER_ENVIRONMENTDIFFUSION:
    case DSPROPERTY_EAX30LISTENER_ROOM:
    case DSPROPERTY_EAX30LISTENER_ROOMHF:
    case DSPROPERTY_EAX30LISTENER_ROOMLF:
    case DSPROPERTY_EAX30LISTENER_DECAYTIME:
    case DSPROPERTY_EAX30LISTENER_DECAYHFRATIO:
    case DSPROPERTY_EAX30LISTENER_DECAYLFRATIO:
    case DSPROPERTY_EAX30LISTENER_REFLECTIONS:
    case DSPROPERTY_EAX30LISTENER_REFLECTIONSDELAY:
    case DSPROPERTY_EAX30LISTENER_REFLECTIONSPAN:
    case DSPROPERTY_EAX30LISTENER_REVERB:
    case DSPROPERTY_EAX30LISTENER_REVERBDELAY:
    case DSPROPERTY_EAX30LISTENER_REVERBPAN:
    case DSPROPERTY_EAX30LISTENER_ECHOTIME:
    case DSPROPERTY_EAX30LISTENER_ECHODEPTH:
    case DSPROPERTY_EAX30LISTENER_MODULATIONTIME:
    case DSPROPERTY_EAX30LISTENER_MODULATIONDEPTH:
    case DSPROPERTY_EAX30LISTENER_AIRABSORPTIONHF:
    case DSPROPERTY_EAX30LISTENER_HFREFERENCE:
    case DSPROPERTY_EAX30LISTENER_LFREFERENCE:
    case DSPROPERTY_EAX30LISTENER_ROOMROLLOFFFACTOR:
    case DSPROPERTY_EAX30LISTENER_FLAGS:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}

HRESULT EAX3Buffer_Query(DSBuffer *buf, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(buf->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~DSPROPERTY_EAX30BUFFER_DEFERRED))
    {
    case DSPROPERTY_EAX30BUFFER_NONE:
    case DSPROPERTY_EAX30BUFFER_ALLPARAMETERS:
    case DSPROPERTY_EAX30BUFFER_OBSTRUCTIONPARAMETERS:
    case DSPROPERTY_EAX30BUFFER_OCCLUSIONPARAMETERS:
    case DSPROPERTY_EAX30BUFFER_EXCLUSIONPARAMETERS:
    case DSPROPERTY_EAX30BUFFER_DIRECT:
    case DSPROPERTY_EAX30BUFFER_DIRECTHF:
    case DSPROPERTY_EAX30BUFFER_ROOM:
    case DSPROPERTY_EAX30BUFFER_ROOMHF:
    case DSPROPERTY_EAX30BUFFER_OBSTRUCTION:
    case DSPROPERTY_EAX30BUFFER_OBSTRUCTIONLFRATIO:
    case DSPROPERTY_EAX30BUFFER_OCCLUSION:
    case DSPROPERTY_EAX30BUFFER_OCCLUSIONLFRATIO:
    case DSPROPERTY_EAX30BUFFER_OCCLUSIONROOMRATIO:
    case DSPROPERTY_EAX30BUFFER_OCCLUSIONDIRECTRATIO:
    case DSPROPERTY_EAX30BUFFER_EXCLUSION:
    case DSPROPERTY_EAX30BUFFER_EXCLUSIONLFRATIO:
    case DSPROPERTY_EAX30BUFFER_OUTSIDEVOLUMEHF:
    case DSPROPERTY_EAX30BUFFER_DOPPLERFACTOR:
    case DSPROPERTY_EAX30BUFFER_ROLLOFFFACTOR:
    case DSPROPERTY_EAX30BUFFER_ROOMROLLOFFFACTOR:
    case DSPROPERTY_EAX30BUFFER_AIRABSORPTIONFACTOR:
    case DSPROPERTY_EAX30BUFFER_FLAGS:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}


/*******************
 * EAX 2 stuff
 ******************/

HRESULT EAX2_Query(DSPrimary *prim, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(prim->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~DSPROPERTY_EAX20LISTENER_DEFERRED))
    {
    case DSPROPERTY_EAX20LISTENER_NONE:
    case DSPROPERTY_EAX20LISTENER_ALLPARAMETERS:
    case DSPROPERTY_EAX20LISTENER_ROOM:
    case DSPROPERTY_EAX20LISTENER_ROOMHF:
    case DSPROPERTY_EAX20LISTENER_ROOMROLLOFFFACTOR:
    case DSPROPERTY_EAX20LISTENER_DECAYTIME:
    case DSPROPERTY_EAX20LISTENER_DECAYHFRATIO:
    case DSPROPERTY_EAX20LISTENER_REFLECTIONS:
    case DSPROPERTY_EAX20LISTENER_REFLECTIONSDELAY:
    case DSPROPERTY_EAX20LISTENER_REVERB:
    case DSPROPERTY_EAX20LISTENER_REVERBDELAY:
    case DSPROPERTY_EAX20LISTENER_ENVIRONMENT:
    case DSPROPERTY_EAX20LISTENER_ENVIRONMENTSIZE:
    case DSPROPERTY_EAX20LISTENER_ENVIRONMENTDIFFUSION:
    case DSPROPERTY_EAX20LISTENER_AIRABSORPTIONHF:
    case DSPROPERTY_EAX20LISTENER_FLAGS:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}

HRESULT EAX2Buffer_Query(DSBuffer *buf, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(buf->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch((propid&~DSPROPERTY_EAX20BUFFER_DEFERRED))
    {
    case DSPROPERTY_EAX20BUFFER_NONE:
    case DSPROPERTY_EAX20BUFFER_ALLPARAMETERS:
    case DSPROPERTY_EAX20BUFFER_DIRECT:
    case DSPROPERTY_EAX20BUFFER_DIRECTHF:
    case DSPROPERTY_EAX20BUFFER_ROOM:
    case DSPROPERTY_EAX20BUFFER_ROOMHF:
    case DSPROPERTY_EAX20BUFFER_ROOMROLLOFFFACTOR:
    case DSPROPERTY_EAX20BUFFER_OBSTRUCTION:
    case DSPROPERTY_EAX20BUFFER_OBSTRUCTIONLFRATIO:
    case DSPROPERTY_EAX20BUFFER_OCCLUSION:
    case DSPROPERTY_EAX20BUFFER_OCCLUSIONLFRATIO:
    case DSPROPERTY_EAX20BUFFER_OCCLUSIONROOMRATIO:
    case DSPROPERTY_EAX20BUFFER_OUTSIDEVOLUMEHF:
    case DSPROPERTY_EAX20BUFFER_AIRABSORPTIONFACTOR:
    case DSPROPERTY_EAX20BUFFER_FLAGS:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}


/*******************
 * EAX 1 stuff
 ******************/

HRESULT EAX1_Query(DSPrimary *prim, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(prim->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch(propid)
    {
    case DSPROPERTY_EAX10LISTENER_ALL:
    case DSPROPERTY_EAX10LISTENER_ENVIRONMENT:
    case DSPROPERTY_EAX10LISTENER_VOLUME:
    case DSPROPERTY_EAX10LISTENER_DECAYTIME:
    case DSPROPERTY_EAX10LISTENER_DAMPING:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}

HRESULT EAX1Buffer_Query(DSBuffer *buf, DWORD propid, ULONG *pTypeSupport)
{
    if(!HAS_EXTENSION(buf->share, EXT_EAX))
        return E_PROP_ID_UNSUPPORTED;

    switch(propid)
    {
    case DSPROPERTY_EAX10BUFFER_ALL:
    case DSPROPERTY_EAX10BUFFER_REVERBMIX:
        *pTypeSupport = KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET;
        return DS_OK;
    }
    FIXME("Unhandled propid: 0x%08lx\n", propid);
    return E_PROP_ID_UNSUPPORTED;
}
