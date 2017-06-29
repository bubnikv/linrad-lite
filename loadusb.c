
#include <string.h>
#include "loadusb.h"
#include "uidef.h"
#include "options.h"

p_libusb_control_transfer libusb_control_transfer;
p_libusb_get_string_descriptor_ascii libusb_get_string_descriptor_ascii;
p_libusb_close libusb_close;
p_libusb_open libusb_open;
p_libusb_init libusb_init;
p_libusb_get_device_list libusb_get_device_list;
p_libusb_get_device_descriptor libusb_get_device_descriptor;
p_libusb_free_device_list libusb_free_device_list;
/* not used (yet?)
p_libusb_reset_device libusb_reset_device;
p_libusb_exit libusb_exit;
p_libusb_bulk_transfer libusb_bulk_transfer;
p_libusb_release_interface libusb_release_interface;
p_libusb_claim_interface libusb_claim_interface;
p_libusb_set_interface_alt_setting libusb_set_interface_alt_setting;
*/

p_libusb_alloc_transfer libusb_alloc_transfer;
p_libusb_submit_transfer libusb_submit_transfer;
p_libusb_handle_events_timeout libusb_handle_events_timeout;
p_libusb_free_transfer libusb_free_transfer;
p_libusb_cancel_transfer libusb_cancel_transfer;

int libusb1_library_flag;

#if OSNUM == OSNUM_WINDOWS
#include "wscreen.h"
#endif
#if OSNUM == OSNUM_LINUX
#include <dlfcn.h>
#include "lscreen.h"
#endif

void library_error_screen(char* libname, int info)
{
    char s[200];
    int i, line;
#if(OSNUM == OSNUM_LINUX)
    char* pkg;
    char *ss;
#endif
#if(OSNUM == OSNUM_WINDOWS)
    DWORD winerr;
#endif
    settextcolor(7);
    line=5;
    lir_status=LIR_DLL_FAILED;
    lir_sched_yield();
    clear_screen();
    sprintf(s,"Could not load library %s",libname);
    lir_text(5,line,s);
    line+=2;
    if(info == 0) {
#if(OSNUM == OSNUM_LINUX)
        ss=dlerror();
        if(ss)lir_text(5,line,ss);
        line+=2;
        lir_text(5,line,"Did you run ./configure after installing this library?");
        line+=2;
#endif
#if(OSNUM == OSNUM_WINDOWS)
        winerr=GetLastError();
        switch (winerr) {
        case 0x7e:
            sprintf(s,"Module not found.");
            break;

        case 0xc1:
            sprintf(s,"Not a valid Win32 application or the module tries to");
            lir_text(5,line,s);
            line++;
            sprintf(s,"load another module which is not a Win32 application.");
            break;

        default:
            sprintf(s,"Call to LoadLibrary returned error code 0x%lx",winerr);
        }
        lir_text(5,line,s);
#endif
    } else {
#if(OSNUM == OSNUM_LINUX)
        ss=dlerror();
        if(ss)lir_text(5,line,ss);
        line+=2;
#endif
        lir_text(5,line,"Library not compatible with Linrad. Maybe too old?");
    }
    line+=2;
#if(OSNUM == OSNUM_LINUX)
#if IA64 == 0
    i=32;
#else
    i=64;
#endif
    pkg=libname;
//                                               help        //1
//                                               x11         //2
//                                               xext        //3
//                                               svgalib     //4
    if(strcmp(libname,"libasound.so")==0)pkg="ALSA";             //5
    if(strcmp(libname,"libusb-1.0.so")==0)pkg="libusb1";         //6
    if(strcmp(libname,"librtlsdr.so")==0)pkg="rtlsdr";           //8
    if(strcmp(libname,"libudev.so")==0)pkg="udev";               //15
    if(strcmp(libname,"libportaudio.so")==0)pkg="portaudio";     //16

#if BUILD == 0
    lir_text(5,line,"Run ");
    settextcolor(12);
    sprintf(s,"./configure --with-%s-%d ", pkg, i);
    lir_text(9,line,s);
    fprintf(stderr,"\n%s\n",s);
    settextcolor(7);
    lir_text(9+strlen(s),line,"to get install instructions for");
    line++;
    lir_text(5,line,"this particular library or run ");
    settextcolor(12);
    lir_text(37,line,"./configure --with-help ");
    settextcolor(7);
    lir_text(61,line,"to get");
    line++;
    lir_text(5,line,"install instructions for all currently un-installed packages");
    line+=2;
    sprintf(s,"Repeat the configure command until %s (%dbit) is no longer 'Not present'",
            libname,i);
    lir_text(5,line,s);
    line+=2;
#if IA64 == 0
    lir_text(5,line,"Finally run make xlinrad");
#else
    lir_text(5,line,"Finally run make xlinrad64.");
#endif
#else
    lir_text(5,line,"Run ");
    settextcolor(12);
    sprintf(s,"../configure --with-%s-%d ", pkg, i);
    lir_text(9,line,s);
    fprintf(stderr,"\n%s\n",s);
    settextcolor(7);
    lir_text(9+strlen(s),line,"to get install instructions for");
    line++
    lir_text(5,line,"this particular library or run ../configure --with-help to get")
    line++;
    lir_text(5,line,"install instructions for all currently un-installed packages");
    line+=2;
    sprintf(s,"Repeat the configure command until %s (%dbit) is no longer 'Not present'",
            libname,i
            lir_text(5,line,s);
            line+=2;
            line+=2;
            lir_text(5,line,"After the installation, run cmake .. ");
            lir_text(5,line,"Finally run make");
#endif
    line+=3;
#endif
    lir_text(9,line,press_any_key);
    i=lir_inkey;
    await_processed_keyboard();
    lir_inkey=i;
    clear_screen();
}

#if(OSNUM == OSNUM_WINDOWS)
HANDLE libusb1_libhandle;

int load_usb1_library(int msg_flag)
{
    char libusb1_dllname[80];
    int info;
    if(libusb1_library_flag)return TRUE;
    info=0;
    sprintf(libusb1_dllname,"%slibusb-1.0.dll",DLLDIR);
    libusb1_libhandle=LoadLibraryEx(libusb1_dllname, NULL,
                                    LOAD_WITH_ALTERED_SEARCH_PATH);
    if(!libusb1_libhandle)goto libusb1_load_error;
    info=1;
    libusb_init=(p_libusb_init)GetProcAddress(libusb1_libhandle, "libusb_init");
    if(!libusb_init)goto libusb1_sym_error;
    libusb_control_transfer=(p_libusb_control_transfer)GetProcAddress(libusb1_libhandle, "libusb_control_transfer");
    if(!libusb_control_transfer)goto libusb1_sym_error;
    libusb_get_string_descriptor_ascii=(p_libusb_get_string_descriptor_ascii)GetProcAddress(libusb1_libhandle, "libusb_get_string_descriptor_ascii");
    if(!libusb_get_string_descriptor_ascii)goto libusb1_sym_error;
    libusb_close=(p_libusb_close)GetProcAddress(libusb1_libhandle, "libusb_close");
    if(!libusb_close)goto libusb1_sym_error;
    libusb_open=(p_libusb_open)GetProcAddress(libusb1_libhandle, "libusb_open");
    if(!libusb_open)goto libusb1_sym_error;
    libusb_get_device_list=(p_libusb_get_device_list)GetProcAddress(libusb1_libhandle, "libusb_get_device_list");
    if(!libusb_get_device_list)goto libusb1_sym_error;
    libusb_get_device_descriptor=(p_libusb_get_device_descriptor)GetProcAddress(libusb1_libhandle, "libusb_get_device_descriptor");
    if(!libusb_get_device_descriptor)goto libusb1_sym_error;
    libusb_free_device_list=(p_libusb_free_device_list)GetProcAddress(libusb1_libhandle, "libusb_free_device_list");
    if(!libusb_free_device_list)goto libusb1_sym_error;
    libusb_alloc_transfer=(p_libusb_alloc_transfer)GetProcAddress(libusb1_libhandle, "libusb_alloc_transfer");
    if(!libusb_alloc_transfer)goto libusb1_sym_error;
    libusb_submit_transfer=(p_libusb_submit_transfer)GetProcAddress(libusb1_libhandle, "libusb_submit_transfer");
    if(!libusb_submit_transfer)goto libusb1_sym_error;
    libusb_handle_events_timeout=(p_libusb_handle_events_timeout)GetProcAddress(libusb1_libhandle, "libusb_handle_events_timeout");
    if(!libusb_handle_events_timeout)goto libusb1_sym_error;
    libusb_free_transfer=(p_libusb_free_transfer)GetProcAddress(libusb1_libhandle, "libusb_free_transfer");
    if(!libusb_free_transfer)goto libusb1_sym_error;
    libusb_cancel_transfer=(p_libusb_cancel_transfer)GetProcAddress(libusb1_libhandle, "libusb_cancel_transfer");
    if(!libusb_cancel_transfer)goto libusb1_sym_error;
    libusb1_library_flag=TRUE;
    return TRUE;
libusb1_sym_error:
    FreeLibrary(libusb1_libhandle);
libusb1_load_error:
    libusb1_library_flag=FALSE;
    if(msg_flag)library_error_screen(libusb1_dllname,info);
    return FALSE;
}

void unload_usb1_library(void)
{
    if(!libusb1_library_flag)return;
    FreeLibrary(libusb1_libhandle);
    libusb1_library_flag=FALSE;
}
#endif



#if(OSNUM == OSNUM_LINUX)
#include <dlfcn.h>
void *libusb1_libhandle;

int load_usb1_library(int msg_flag)
{
    int info;
    info=0;
    if(libusb1_library_flag)return TRUE;
    libusb1_libhandle=dlopen(LIBUSB1_LIBNAME, RTLD_NOW|RTLD_GLOBAL);
    if(!libusb1_libhandle)goto libusb1_load_error;
    info=1;
    libusb_init=(p_libusb_init)dlsym(libusb1_libhandle, "libusb_init");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_control_transfer=(p_libusb_control_transfer)dlsym(libusb1_libhandle, "libusb_control_transfer");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_get_string_descriptor_ascii=(p_libusb_get_string_descriptor_ascii)dlsym(libusb1_libhandle, "libusb_get_string_descriptor_ascii");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_close=(p_libusb_close)dlsym(libusb1_libhandle, "libusb_close");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_open=(p_libusb_open)dlsym(libusb1_libhandle, "libusb_open");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_get_device_list=(p_libusb_get_device_list)dlsym(libusb1_libhandle, "libusb_get_device_list");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_get_device_descriptor=(p_libusb_get_device_descriptor)dlsym(libusb1_libhandle, "libusb_get_device_descriptor");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_free_device_list=(p_libusb_free_device_list)dlsym(libusb1_libhandle, "libusb_free_device_list");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_alloc_transfer=(p_libusb_alloc_transfer)dlsym(libusb1_libhandle, "libusb_alloc_transfer");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_submit_transfer=(p_libusb_submit_transfer)dlsym(libusb1_libhandle, "libusb_submit_transfer");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_handle_events_timeout=(p_libusb_handle_events_timeout)dlsym(libusb1_libhandle, "libusb_handle_events_timeout");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_free_transfer=(p_libusb_free_transfer)dlsym(libusb1_libhandle, "libusb_free_transfer");
    if(dlerror() != 0)goto libusb1_sym_error;
    libusb_cancel_transfer=(p_libusb_cancel_transfer)dlsym(libusb1_libhandle, "libusb_cancel_transfer");
    if(dlerror() != 0)goto libusb1_sym_error;

    libusb1_library_flag=TRUE;
    return TRUE;
libusb1_sym_error:
    dlclose(libusb1_libhandle);
libusb1_load_error:
    libusb1_library_flag=FALSE;
    if(msg_flag)library_error_screen(LIBUSB1_LIBNAME,info);
    return FALSE;
}

void unload_usb1_library(void)
{
    if(!libusb1_library_flag)return;
    dlclose(libusb1_libhandle);
    libusb1_library_flag=FALSE;
}

#endif

int select_libusb_version(char* name, char* lib0, char* lib1)
{
    int i;
    char s[80];
    int vernr;
    clear_screen();
    load_usb1_library(FALSE);
    settextcolor(14);
    sprintf(s,"Library selection for %s",name);
    lir_text(10,1,s);
#if OSNUM == OSNUM_WINDOWS
    sprintf(s,"Use zadig.exe or zadig_xp.exe to install USB drivers.");
    lir_text(10,2,s);
#endif
    settextcolor(7);
    if(libusb1_library_flag == FALSE) {
        lir_text(5,5,"Can not load any of libusb or libusb-1.0");
        lir_text(9,10,press_any_key);
        i=lir_inkey;
        await_processed_keyboard();
        lir_inkey=i;
        clear_screen();
        return -1;
    }
    if(libusb1_library_flag == TRUE) {
        lir_text(5,5,"Both libusb and libusb-1.0 are available on this system.");
        lir_text(5,6,"Select which one to use:");
#if OSNUM == OSNUM_WINDOWS
        sprintf(s,"0 = %s for libusb-win32 driver.",lib0);
        lir_text(5,8,s);
        sprintf(s,"1 = %s for for WinUSB (libusbx) driver.",lib1);
        lir_text(5,9,s);
#endif
#if OSNUM == OSNUM_LINUX
        sprintf(s,"0 = %s",lib0);
        lir_text(5,8,s);
        sprintf(s,"1 = %s",lib1);
        lir_text(5,9,s);
#endif
        lir_text(5,11,"=>");
        vernr=lir_get_integer(8,11,1,0,1);
    } else {
        if(libusb1_library_flag == TRUE) {
            lir_text(5,5,"Only libusb-1.0 is available on this system.");
#if OSNUM == OSNUM_WINDOWS
            sprintf(s,"Will use %s for for WinUSB (libusbx) driver.",lib1);
#endif
#if OSNUM == OSNUM_LINUX
            sprintf(s,"Will use %s",lib1);
#endif
            vernr=1;
        } else {
            lir_text(5,5,"Only libusb is available on this system.");
#if OSNUM == OSNUM_WINDOWS
            sprintf(s,"Will use %s for for libusb-win32 driver.",lib0);
#endif
#if OSNUM == OSNUM_LINUX
            sprintf(s,"Will use %s",lib1);
#endif
            vernr=0;
        }
        lir_text(5,7,s);
        lir_text(10,10,press_any_key);
        i=lir_inkey;
        await_processed_keyboard();
        lir_inkey=i;
    }
    unload_usb1_library();
    clear_screen();
    return vernr;
}
