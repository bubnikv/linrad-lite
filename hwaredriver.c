// Copyright (c) <2012> <Leif Asbrink>
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.


#include <ctype.h>
#include "globdef.h"
#include "uidef.h"
#include "hwaredef.h"
#include "fft1def.h"
#include "screendef.h"
#include "seldef.h"
#include "sdrdef.h"
#include "thrdef.h"
#include "txdef.h"

int hware_flag;
int fg_new_band;

void set_hardware_tx_frequency(void)
{
    if(ui.tx_dadev_no < SPECIFIC_DEVICE_CODES) {
        switch (ui.tx_soundcard_radio) {
        case TX_SOUNDCARD_RADIO_SI570:
// Set the transmitter carrier frequency to tg.freq.
            tg.passband_direction=si570.tx_passband_direction;
            tg.band_increment = 0.00001;
            switch (ui.transceiver_mode ) {
            case 0:
// The transmitter has its own Si570
                break;

            case 1:
// The Si570 is common to Rx and Tx. Keep the Si570 frequency constant
// and change tg_basebfreq_hz as needed.
                tg_basebfreq_hz=1000000*(fg.passband_center-tg.freq);
                if(tg_basebfreq_hz > (float)ui.tx_da_speed*0.4F) {
                    tg_basebfreq_hz=(float)ui.tx_da_speed*0.35F;
                    tg.freq=fg.passband_center-tg_basebfreq_hz/1000000.F;
                }
                if(tg_basebfreq_hz < -(float)ui.tx_da_speed*0.4F) {
                    tg_basebfreq_hz=-(float)ui.tx_da_speed*0.35F;
                    tg.freq=fg.passband_center-tg_basebfreq_hz/1000000.F;
                }
                break;

            case 2:
// The Si570 is common to Rx and Tx. Keep the audio tone, tg_basebfreq_hz
// constant and change the Si570 between Rx and tx.
                tx_passband_center=tg.freq+tg_basebfreq_hz/1000000.F;
                break;
            }
            make_tx_phstep();
            break;
        }
    }
}

void hware_hand_key(void)
{
// This routine is called from the rx_input_thread.
// It is responsible for reading the hardware and setting
// hand_key to TRUE or FALSE depending on whether the hand key
// is depressed or not.
    if(ui.tx_dadev_no < SPECIFIC_DEVICE_CODES) {
        switch (ui.tx_soundcard_radio) {
        case TX_SOUNDCARD_RADIO_SI570:
            if(ui.ptt_control == 1) {
// We use the pilot tone to control PTT.
                si570_ptt=0;
            }
            si570_get_ptt();
            break;
        }
    }
}

void hware_set_ptt(int state)
{
    if(ui.tx_dadev_no < SPECIFIC_DEVICE_CODES) {
        switch (ui.tx_soundcard_radio) {
        case TX_SOUNDCARD_RADIO_SI570:
            if(ui.ptt_control == 1) {
// We use the pilot tone to control PTT.
                si570_ptt=0;
            } else {
                if(si570_ptt != state) {
                    si570_ptt=state;
                    si570_set_ptt();
                }
            }
            break;
        }
    }
}

void set_hardware_rx_gain(void)
{
    int i, j, k, m;
    float t1;
    if(diskread_flag >= 2)return;
    if(ui.rx_addev_no == RTL2832_DEVICE_CODE) {
        if(rtl2832.gain_mode == 0) {
            fg.gain=0;
            return;
        }
        fg.gain_increment=1;
        t1=(float)rint(0.1F*(float)old_rtl2832_gain);
        k=fg.gain-(int)t1;
        if(k == 0)return;
        if(abs(k) == fg.gain_increment) {
            j=0;
            m=10000;
            for(i=0; i<no_of_rtl2832_gains; i++) {
                if(abs(old_rtl2832_gain-rtl2832_gains[i]) < m) {
                    m=abs(old_rtl2832_gain-rtl2832_gains[i]);
                    j=i;
                }
            }
            if(k > 0) {
                j++;
            } else {
                j--;
            }
            if(j < 0)j=0;
            if(j >= no_of_rtl2832_gains)j=no_of_rtl2832_gains-1;
        } else {
            j=0;
            m=10000;
            for(i=0; i<no_of_rtl2832_gains; i++) {
                t1=(float)rint(0.1F*(float)rtl2832_gains[i]);
                if(abs(fg.gain-(int)t1) < m) {
                    m=abs(fg.gain-(int)t1);
                    j=i;
                }
            }
        }
        t1=(float)rint(0.1F*(float)rtl2832_gains[j]);
        fg.gain=(int)t1;
        old_rtl2832_gain=rtl2832_gains[j];
        sdr_att_counter++;
        return;
    }
    switch (ui.rx_soundcard_radio) {
    case RX_SOUNDCARD_RADIO_SI570:
        fg.gain=0;
        break;
    }
}

void set_hardware_rx_frequency(void)
{
    if(diskread_flag >= 2) {
        sc[SC_WG_FQ_SCALE]++;
        return;
    }
    if(ui.rx_addev_no == RTL2832_DEVICE_CODE) {
        fg.passband_direction=1;
        sdr_nco_counter++;
        goto setfq_x;
    }

    fg.passband_direction=1;
    switch (ui.rx_soundcard_radio) {
    case RX_SOUNDCARD_RADIO_UNDEFINED:
        break;

    case RX_SOUNDCARD_RADIO_UNDEFINED_REVERSED:
        fg.passband_direction=-1;
        break;

    case RX_SOUNDCARD_RADIO_SI570:
        fg.passband_direction=si570.rx_passband_direction;
        si570_rx_freq_control();
        break;
    }
setfq_x:
    ;
    if( (ui.converter_mode & CONVERTER_USE) != 0) {
        fg.passband_direction*=ui_converter_direction;
    }
    fft1_direction=fg.passband_direction;
    check_filtercorr_direction();
}
