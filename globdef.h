// Always include stdio.h, math.h stdlib.h stdint.h and errno.h
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define STDERR stderr

#define INITIAL_SKIP_FLAG_MAX 25

#define CALLBACK_CMD_START 3
#define CALLBACK_ANSWER_AWAKE 2
#define CALLBACK_CMD_ACTIVE 1
#define CALLBACK_CMD_CLOSE 0
#define CALLBACK_ANSWER_CLOSED -1
#define CALLBACK_ERROR -2

#define TX_DA_MARGIN 0.97

// MAX_MOUSE_CURSIZE is used by svgalib and fbdev
#define MAX_MOUSE_CURSIZE 50

// Structure for soundcard info.
typedef struct {
    int no_of_blocks;
    int valid_frames;
    int min_valid_frames;
    int valid_bytes;
    int empty_frames;
    int empty_bytes;
    int tot_frames;
    int tot_bytes;
    int framesize;
    int block_bytes;
    int block_frames;
    float interrupt_rate;
    int open_flag;
} SOUNDCARD_PARM;

#define CONVERTER_USE 1
#define CONVERTER_UP 2
#define CONVERTER_LO_BELOW 4

// Pointers into the SOUNDCARD_PARM snd[4] structures.
enum SoundcardParmPointerType {
    RXAD            = 0,
    RXDA            = 1,
    TXDA            = 2,
    TXAD            = 3,
    MAX_IOTEST      = TXAD,
};

#define RX_SOUNDCARD_RADIO_UNDEFINED 0
#define RX_SOUNDCARD_RADIO_UNDEFINED_REVERSED 1
#define RX_SOUNDCARD_RADIO_SI570 2
#define MAX_RX_SOUNDCARD_RADIO 3

#define TX_SOUNDCARD_RADIO_UNDEFINED 0
#define TX_SOUNDCARD_RADIO_UNDEFINED_REVERSED 1
#define TX_SOUNDCARD_RADIO_SI570 2
#define MAX_TX_SOUNDCARD_RADIO 3

#define TRUE 1
#define FALSE 0
#define YELLOW 14
#define LIGHT_GREEN 10
#define LIGHT_RED 12

#define MAX_FFT1_AVG1 9

#define NO_REDRAW_BLOCKS 16

// *******************************************
// Global numerical values
#define PI_L 3.1415926535897932
#define BIGFLOAT 300000000000000000000000000000000000000.F
#define BIGDOUBLE 300000000000000000000000000000000000000.

// Signal power to the power of four may become a very large number.
// Define something small to multiply by to prevent overflows.
#define P4SCALE 0.000000000000000000001
#define P2SCALE 0.00000000001

// values for lir_status
// Memory errors are larger than LIR_OK.
// Other abnormal conditions smaller than LIR_OK.
#define LIR_OK 0
#define LIR_TUNEERR 1
#define LIR_FFT1ERR 2
#define LIR_SAVE_UIPARM 4
#define LIR_NEW_SETTINGS -1
#define LIR_SPURERR -2
#define LIR_PARERR -3
#define LIR_NEW_POL -4
#define LIR_TUNEERR2 -5
#define LIR_POWTIM -6
#define LIR_PA_FLAG_ERROR -7
#define LIR_PA_NO_SUCH_DEVICE -8
#define LIR_PA_FORMAT_NOT_SUPPORTED -9
#define LIR_PA_OPENSTREAM_FAILED -10
#define LIR_PA_START_STREAM_FAILED -11
#define LIR_DLL_FAILED -12
#define LIR_TXPAR_FAILED -13

// *******************************************
// Fixed array dimensions depend on these defines:
enum ProcessingMode {
    // Wideband CW
    MODE_WCW        = 0,
    // Narrowband CW
    MODE_NCW        = 1,
    MODE_HSMS       = 2,
    MODE_SSB        = 3,
    MODE_FM         = 4,
    MODE_AM         = 5,
    MODE_QRSS       = 6,
    // Note that modes below MODE_TXTEST are allowed to call
    // users tx routines, but that MODE_TXTEST and higher may
    // call users_init_mode, but users_hwaredriver is responsible
    // for checking rx_mode < MODE_TXTEST and not do any tx
    // activities or screen writes.
    MODE_TXTEST     = 7,
    MODE_RX_ADTEST  = 8,
    // Note that MAX_RX_MODES can be up to 12. 'L' is reserved
    // for an new mode that might be desireable to add.
    MAX_RX_MODE     = 11,
};

//******************************************************************
// Information about what device drivers to use for soundcards
// is stored in ui.use_alsa. The name has became misleading,
// but a change would make par_userint incompatible once again...
// Use the following masks for testing on ui.use_alsa
enum SoundSystemType {
    // Linux specific: Directly accessing an ALSA driver.
    NATIVE_ALSA_USED        = 1 << 0,
    // PortAudio library is supported on all systems.
    PORTAUDIO_RX_IN         = 1 << 1,
    PORTAUDIO_RX_OUT        = 1 << 2,
    PORTAUDIO_TX_IN         = 1 << 3,
    PORTAUDIO_TX_OUT        = 1 << 4,
    PORTAUDIO_DLL_VERSION   = (1<<5)|(1<<6)|(1<<7),
    // Win32 specific: Use the WAVE_FORMAT_EXTENSIBLE for MME audio API.
    RXAD_USE_EXTENSIBLE     = 1 << 8,
    RXDA_USE_EXTENSIBLE     = 1 << 9,
    TXAD_USE_EXTENSIBLE     = 1 << 10,
    TXDA_USE_EXTENSIBLE     = 1 << 11,
    // Sound system defined mask on Linux.
    SOUND_SYSTEM_DEFINED    = 2096
};

#define TXMODE_OFF 0
#define TXMODE_CW 1
#define TXMODE_SSB 2

#define MAX_COLOR_SCALE 23
#define MAX_SCRO 50
#define LLSQ_MAXPAR 25
#define MAX_ADCHAN 4
#define MAX_MIX1 8           // No of different signals to process simultaneously
#define MAX_AD_CHANNELS 4
#define MAX_RX_CHANNELS 2
#define DAOUT_MAXTIME 1.
#define SPUR_N 3
#define SPUR_SIZE (1<<SPUR_N)
#define NO_OF_SPUR_SPECTRA 256
#define MAX_FFT1_ARRAYS 85
#define MAX_FFT3_ARRAYS 30
#define MAX_BASEB_ARRAYS 40
#define CG_MAXTRACE 24
#define MAX_HIRES_ARRAYS  8
#define MAX_AFC_ARRAYS 20
#define MAX_VOICELAB_ARRAYS 16
#define MAX_VOICELAB_ARRAYS 16
#define MAX_TXMEM_ARRAYS 40
#define MAX_BLANKER_ARRAYS 15

#define USR_NORMAL_RX 0
#define USR_TXTEST 1
#define USR_POWTIM 2
#define USR_ADTEST 3
#define USR_IQ_BALANCE 4
#define USR_CAL_INTERVAL 5
#define USR_CAL_FILTERCORR 6
#define USR_TUNE 7

#define UNDEFINED_DEVICE_CODE -1
#define DISABLED_DEVICE_CODE -2
#define SPECIFIC_DEVICE_CODES 9999
#define RTL2832_DEVICE_CODE (SPECIFIC_DEVICE_CODES+6)

// Positions for runtime error messages in the main spectrum.
#define WGERR_DASYNC 0
#define WGERR_ADSPEED 1
#define WGERR_HWARE 2
#define WGERR_MEMORY 2
#define WGERR_SCREEN 2
#define WGERR_RXIN 3
#define WGERR_TIMF1_OVERLOAD 3
#define WGERR_TIMF2_OVERLOAD 4
#define WGERR_FFT3_OVERLOAD 0
#define WGERR_BASEB_OVERLOAD 2
#define WGERR_RXOUT 4
#define WGERR_TXIN 5
#define WGERR_TXOUT 6
#define WGERR_NETWR 7
#define WGERR_SOUNDCARD 0

typedef void (*ROUTINE) (void);
#define PERMDEB fprintf(dmp,
#define DEB if(dmp != NULL)PERMDEB
#define XZ xz
// *******************************************
// Audio board and disk file parameter definitions
#define DWORD_INPUT 1
#define TWO_CHANNELS 2
#define IQ_DATA 4
#define BYTE_INPUT 8
#define NO_DUPLEX 16
#define DIGITAL_IQ 32
#define FLOAT_INPUT 64
#define QWORD_INPUT 128
#define MODEPARM_MAX 256

// *******************************************
// Processing parameter definitions
enum GenParmType {
    FIRST_FFT_BANDWIDTH         = 0,
    FIRST_FFT_SINPOW            = 1,
    FIRST_FFT_VERNR             = 2,
    FIRST_FFT_NO_OF_THREADS     = 3,
    FFT1_STORAGE_TIME           = 4,
    FIRST_FFT_GAIN              = 5,
    WG_WATERF_BLANKED_PERCENT   = 6,
    FFT1_CORRELATION_SPECTRUM   = 7,
    SECOND_FFT_ENABLE           = 8,

    FIRST_BCKFFT_VERNR          = 9,
    SELLIM_MAXLEVEL             = 10,
    FIRST_BCKFFT_ATT_N          = 11,
    SECOND_FFT_NINC             = 12,
    SECOND_FFT_SINPOW           = 13,
    SECOND_FFT_VERNR            = 14,
    SECOND_FFT_ATT_N            = 15,
    FFT2_STORAGE_TIME           = 16,

    AFC_ENABLE                  = 17,
    AFC_LOCK_RANGE              = 18,
    AFC_MAX_DRIFT               = 19,
    CW_DECODE_ENABLE            = 20,
    MAX_NO_OF_SPURS             = 21,
    SPUR_TIMECONSTANT           = 22,

    MIX1_BANDWIDTH_REDUCTION_N  = 23,
    MIX1_NO_OF_CHANNELS         = 24,
    THIRD_FFT_SINPOW            = 25,
    BASEBAND_STORAGE_TIME       = 26,
    OUTPUT_DELAY_MARGIN         = 27,
    DA_OUTPUT_SPEED             = 28,

    OUTPUT_MODE                 = 29,

    AMPLITUDE_EXPAND_EXPONENT   = 30,
    BG_WATERF_BLANKED_PERCENT   = 31,

// Parameters of a receiver, mode specific.
// Length of the genparm, genparm_min, genparm_max, genparm_default, genparm_text, newco_genparm tables.
    MAX_GENPARM                 = 32,
};

// *******************************************************
// Defines for state machine in fft2.c
#define FFT2_NOT_ACTIVE 0
#define FFT2_B 10
#define FFT2_C 11
#define FFT2_MMXB 20
#define FFT2_MMXC 21
#define FFT2_ELIMINATE_SPURS 104
#define FFT2_WATERFALL_LINE 1001
#define FFT2_TEST_FINISH 9999
#define FFT2_COMPLETE -1
// **********************************************
#define CALIQ 2
#define CALAMP 1

// **********************************************
#define SCREEN_TYPE_X11 1
#define SCREEN_TYPE_X11_SHM 2
#define SCREEN_TYPE_SVGALIB 4
#define SCREEN_TYPE_FBDEV 8
#define SCREEN_TYPE_WINDOWS 16

#define OSNUM_LINUX 1
#define OSNUM_WINDOWS 2
#define OSNUM_BSD 3
#define OSNUM_DARWIN 4
// *******************************************

#if(OSNUM == OSNUM_WINDOWS)
#define FD uint64_t
#else
#define FD int
#endif


// Structure for Si570
typedef struct {
    int libusb_version;
    int rx_firmware_type;  // 1=DG8SAQ/PE0FKO 2=FiFi SDR 3=SDR-Widget
    int rx_usb_index;
    int min_rx_freq;
    int max_rx_freq;
    int rx_lo_multiplier;
    int rx_lo_freq_offset;
    int rx_passband_direction;
    int rx_freq_adjust;
    int rx_serial1;
    int rx_serial2;
    int rx_serial3;
    int rx_serial4;
    int tx_firmware_type;
    int tx_usb_index;
    int min_tx_freq;
    int max_tx_freq;
    int tx_lo_multiplier;
    int tx_lo_freq_offset;
    int tx_passband_direction;
    int tx_freq_adjust;
    int tx_serial1;
    int tx_serial2;
    int tx_serial3;
    int tx_serial4;
} P_SI570;
P_SI570 si570;
#define MAX_SI570_PARM            25
extern char *si570_parm_text[MAX_SI570_PARM];

// Structure for transmitter parameters in ssb mode
typedef struct {
    int minfreq;
    int maxfreq;
    int slope;
    int bass;
    int treble;
    int mic_gain;
    int mic_agc_time;
    int mic_f_threshold;
    int mic_t_threshold;
    int rf1_gain;
    int alc_time;
    int micblock_time;
    int delay_margin;
    int frequency_shift;
    int check;
} SSBPROC_PARM;
#define MAX_SSBPROC_PARM 15
extern char *ssbprocparm_text[MAX_SSBPROC_PARM];

// Structure for transmitter parameters in CW modes
typedef struct {
    int rise_time;
    int enable_hand_key;
    int enable_tone_key;
    int enable_ascii;
    int delay_margin;
    int carrier_freq;
    int sidetone_ampl;
    int sidetone_freq;
    int wcw_mute_on;
    int wcw_mute_off;
    int ncw_mute_on;
    int ncw_mute_off;
    int hsms_mute_on;
    int hsms_mute_off;
    int qrss_mute_on;
    int qrss_mute_off;
    int check;
} CWPROC_PARM;
#define MAX_CWPROC_PARM 21
extern char *cwprocparm_text[MAX_CWPROC_PARM];

// *******************************************
// Structure for printing time stamps on waterfall graphs
typedef struct {
    int line;
    char text[10];
} WATERF_TIMES;

// *******************************************
// Structure for 5th order Butterworth low pass filter
typedef struct {
    float gain;
    float c0;
    float c1;
    float c2;
    float c3;
    float c4;
} IIR5_PARMS;

// *******************************************
// Structure for user interface parameters selected by operator
typedef struct {
    int vga_mode;
    int screen_width_factor;
    int screen_height_factor;
    int font_scale;
    int mouse_speed;
    int max_dma_rate;
    int process_priority;
    int use_alsa;
    int rx_input_mode;
    int rx_rf_channels;
    int rx_ad_channels;
    int rx_ad_speed;
    int rx_addev_no;
    int rx_admode;
    int rx_damode;
    int rx_dadev_no;
    int rx_min_da_speed;
    int rx_max_da_speed;
    int rx_max_da_channels;
    int rx_max_da_bytes;
    int rx_min_da_channels;
    int rx_min_da_bytes;
    int rx_soundcard_radio;
    unsigned int converter_hz;
    unsigned int converter_mhz;
    int converter_mode;
    // The network flag is not used in this Linrad fork, but it is kept to maintain
    // compatibility of the config files.
    unsigned int network_flag;
    int tx_ad_speed;
    int tx_da_speed;
    int tx_addev_no;
    int tx_dadev_no;
    int tx_da_channels;
    int tx_ad_channels;
    int tx_da_bytes;
    int tx_ad_bytes;
    int tx_enable;
    int tx_pilot_tone_db;
    int tx_pilot_tone_prestart;
    int tx_soundcard_radio;
    int operator_skil;
    int max_blocked_cpus;
    unsigned int timer_resolution;
    int autostart;
    int rx_ad_latency;
    int rx_da_latency;
    int tx_ad_latency;
    int tx_da_latency;
    int sample_shift;
    int min_dma_rate;
    int use_extio;
    int extio_type;
    int transceiver_mode;
    int ptt_control;
    int check;
} USERINT_PARM;
#define MAX_UIPARM 54
extern char *uiparm_text[MAX_UIPARM];

#define DEFAULT_MIN_DMA_RATE 30
#define DEFAULT_MAX_DMA_RATE 300
#define MIN_DMA_RATE 10
#define MAX_DMA_RATE 5000
#define DMA_MIN_DIGITS 2
#define DMA_MAX_DIGITS 4
#define MIN_DMA_RATE_EXP 1
#define MAX_DMA_RATE_EXP 100000
#define DMA_MIN_DIGITS_EXP 1
#define DMA_MAX_DIGITS_EXP 6


#define OPERATOR_SKIL_NEWCOMER 1
#define OPERATOR_SKIL_NORMAL 2
#define OPERATOR_SKIL_EXPERT 3


// *******************************************
// Screen object parameters for mouse and screen drawing.
// Each screen object is defined by it's number, scro[].no
// For each type scro[].type the number scro[].no is unique and
// defines what to do in the event of a mouse click.

// Definitions for type = GRAPH
#define WIDE_GRAPH 1
#define HIRES_GRAPH 2
#define TRANSMIT_GRAPH 3
#define FREQ_GRAPH 4
#define MAX_WIDEBAND_GRAPHS 10
#define AFC_GRAPH 11
#define BASEBAND_GRAPH 12
#define POL_GRAPH 13
#define COH_GRAPH 14
#define EME_GRAPH 15
#define METER_GRAPH 16
#define PHASING_GRAPH 19
#define GRAPH_RIGHTPRESSED 128
#define GRAPH_MASK 0x8000007f

// Definitions for parameter input routines under mouse control
#define FIXED_INT_PARM 3
#define TEXT_PARM 4
#define FIXED_FLOAT_PARM 5
#define FIXED_DOUBLE_PARM 6
#define DATA_READY_PARM 128
#define MAX_TEXTPAR_CHARS 32
#define EG_DX_CHARS 12
#define EG_LOC_CHARS 6

// Definitions for type WIDE_GRAPH
enum WideGraphParameters {
    WG_TOP              = 0,
    WG_BOTTOM           = 1,
    WG_LEFT             = 2,
    WG_RIGHT            = 3,
    WG_BORDER           = 4,
    WG_YSCALE_EXPAND    = 5,
    WG_YSCALE_CONTRACT  = 6,
    WG_YZERO_DECREASE   = 7,
    WG_YZERO_INCREASE   = 8,
    WG_FQMIN_DECREASE   = 9,
    WG_FQMIN_INCREASE   = 10,
    WG_FQMAX_DECREASE   = 11,
    WG_FQMAX_INCREASE   = 12,
    WG_AVG1NUM          = 13,
    WG_FFT1_AVGNUM      = 14,
    WG_WATERF_AVGNUM    = 15,
    WG_WATERF_ZERO      = 16,
    WG_WATERF_GAIN      = 17,
    WG_SPUR_TOGGLE      = 18,
    WG_FREQ_ADJUSTMENT_MODE = 19,
    WG_LOWEST_FREQ      = 20,
    WG_HIGHEST_FREQ     = 21,
    MAX_WGBUTT          = 22,
};

// Definitions for type HIRES_GRAPH
enum HiresGraphParameters {
    HG_TOP              = 0,
    HG_BOTTOM           = 1,
    HG_LEFT             = 2,
    HG_RIGHT            = 3,
    HG_BLN_STUPID       = 4,
    HG_BLN_CLEVER       = 5,
    HG_TIMF2_STATUS     = 6,
    HG_TIMF2_WK_INC     = 7,
    HG_TIMF2_WK_DEC     = 8,
    HG_TIMF2_ST_INC     = 9,
    HG_TIMF2_ST_DEC     = 10,
    HG_TIMF2_LINES      = 11,
    HG_TIMF2_HOLD       = 12,
    HG_FFT2_AVGNUM      = 13,
    HG_SPECTRUM_ZERO    = 14,
    HG_SPECTRUM_GAIN    = 15,
    HG_SELLIM_PAR1      = 18,
    HG_SELLIM_PAR2      = 19,
    HG_SELLIM_PAR3      = 20,
    HG_SELLIM_PAR4      = 21,
    HG_SELLIM_PAR5      = 22,
    HG_SELLIM_PAR6      = 23,
    HG_SELLIM_PAR7      = 24,
    HG_SELLIM_PAR8      = 25,
    MAX_HGBUTT          = 26,
};

// Definitions for type BASEBAND_GRAPH
enum BasebandGraphParameters {
    BG_TOP                  = 0,
    BG_BOTTOM               = 1,
    BG_LEFT                 = 2,
    BG_RIGHT                = 3,
    BG_YSCALE_EXPAND        = 4,
    BG_YSCALE_CONTRACT      = 5,
    BG_YZERO_DECREASE       = 6,
    BG_YZERO_INCREASE       = 7,
    BG_RESOLUTION_DECREASE  = 8,
    BG_RESOLUTION_INCREASE  = 9,
    BG_OSCILLOSCOPE         = 10,
    BG_OSC_INCREASE         = 11,
    BG_OSC_DECREASE         = 12,
    BG_PIX_PER_PNT_INC      = 13,
    BG_PIX_PER_PNT_DEC      = 14,
    BG_TOGGLE_EXPANDER      = 15,
    BG_TOGGLE_COHERENT      = 16,
    BG_TOGGLE_PHASING       = 17,
    BG_TOGGLE_CHANNELS      = 18,
    BG_TOGGLE_BYTES         = 19,
    BG_TOGGLE_TWOPOL        = 20,
    BG_SEL_COHFAC           = 21,
    BG_SEL_DELPNTS          = 22,
    BG_SEL_FFT3AVGNUM       = 23,
    BG_TOGGLE_AGC           = 24,
    BG_SEL_AGC_ATTACK       = 25,
    BG_SEL_AGC_RELEASE      = 26,
    BG_SEL_AGC_HANG         = 27,
    BG_YBORDER              = 28,
    BG_WATERF_ZERO          = 29,
    BG_WATERF_GAIN          = 30,
    BG_WATERF_AVGNUM        = 31,
    BG_HORIZ_ARROW_MODE     = 32,
    BG_MIXER_MODE           = 33,
    BG_FILTER_SHIFT         = 34,
    BG_NOTCH_NO             = 35,
    BG_NOTCH_POS            = 36,
    BG_NOTCH_WIDTH          = 37,
    BG_TOGGLE_FM_MODE       = 38,
    BG_TOGGLE_FM_SUBTRACT   = 39,
    BG_SEL_FM_AUDIO_BW      = 40,
    BG_TOGGLE_CH2_PHASE     = 41,
    BG_SQUELCH_TIME         = 42,
    BG_SQUELCH_POINT        = 43,
    BG_SQUELCH_LEVEL        = 44,
    MAX_BGBUTT              = 45,
};

#define MAX_BG_NOTCHES 9

// Definitions for type AFC_GRAPH
enum AFCGraphParameters {
    AG_TOP                  = 0,
    AG_BOTTOM               = 1,
    AG_LEFT                 = 2,
    AG_RIGHT                = 3,
    AG_FQSCALE_EXPAND       = 4,
    AG_FQSCALE_CONTRACT     = 5,
    AG_MANAUTO              = 6,
    AG_WINTOGGLE            = 7,
    AG_SEL_AVGNUM           = 8,
    AG_SEL_FIT              = 9,
    AG_SEL_DELAY            = 10,
    MAX_AGBUTT              = 11,
};

// Definitions for type POL_GRAPH
enum PolGraphParameters {
    PG_TOP                  = 0,
    PG_BOTTOM               = 1,
    PG_LEFT                 = 2,
    PG_RIGHT                = 3,
    PG_ANGLE                = 4,
    PG_CIRC                 = 5,
    PG_AUTO                 = 6,
    PG_AVGNUM               = 7,
    MAX_PGBUTT              = 8,
};

// Definitions for type PHASING_GRAPH
enum PhasingGraphParameters {
    XG_TOP                  = 0,
    XG_BOTTOM               = 1,
    XG_LEFT                 = 2,
    XG_RIGHT                = 3,
    XG_INCREASE_PAR1        = 4,
    XG_DECREASE_PAR1        = 5,
    XG_INCREASE_PAR2        = 6,
    XG_DECREASE_PAR2        = 7,
    XG_INCREASE_PAR1_F      = 8,
    XG_DECREASE_PAR1_F      = 9,
    XG_INCREASE_PAR2_F      = 10,
    XG_DECREASE_PAR2_F      = 11,
    XG_DO_A                 = 12,
    XG_DO_B                 = 13,
    XG_DO_C                 = 14,
    XG_DO_D                 = 15,
    XG_DO_1                 = 16,
    XG_DO_2                 = 17,
    XG_DO_3                 = 18,
    XG_COPY                 = 19,
    XG_MEM_1                = 20,
    XG_MEM_2                = 21,
    XG_MEM_3                = 22,
    MAX_XGBUTT              = 23,
};

// Definitions for type COH_GRAPH
enum CoherentGraphParameters {
    CG_TOP                  = 0,
    CG_BOTTOM               = 1,
    CG_LEFT                 = 2,
    CG_RIGHT                = 3,
    CG_OSCILLOSCOPE         = 4,
    CG_METER_GRAPH          = 5,
    MAX_CGBUTT              = 6,
};

// Definitions for type AEME_GRAPH
enum AEMEGraphParameters {
    EG_TOP                  = 0,
    EG_BOTTOM               = 1,
    EG_LEFT                 = 2,
    EG_RIGHT                = 3,
    EG_MINIMISE             = 4,
    EG_LOC                  = 5,
    EG_DX                   = 6,
    MAX_EGBUTT              = 7,
};

// Definitions for type FREQ_GRAPH
enum FreqGraphParameters {
    FG_TOP                  = 0,
    FG_BOTTOM               = 1,
    FG_LEFT                 = 2,
    FG_RIGHT                = 3,
    FG_INCREASE_FQ          = 4,
    FG_DECREASE_FQ          = 5,
    FG_INCREASE_GAIN        = 6,
    FG_DECREASE_GAIN        = 7,
    MAX_FGBUTT              = 8,
};

// Definitions for type (S)METER_GRAPH
enum SMeterGraphParameters {
    MG_TOP                  = 0,
    MG_BOTTOM               = 1,
    MG_LEFT                 = 2,
    MG_RIGHT                = 3,
    MG_INCREASE_AVGN        = 4,
    MG_DECREASE_AVGN        = 5,
    MG_INCREASE_GAIN        = 6,
    MG_DECREASE_GAIN        = 7,
    MG_INCREASE_YREF        = 8,
    MG_DECREASE_YREF        = 9,
    MG_CHANGE_CAL           = 10,
    MG_CHANGE_TYPE          = 11,
    MG_CHANGE_TRACKS        = 12,
    MG_SCALE_STON_SIGSHIFT  = 13,
    MAX_MGBUTT              = 14,
};

// Definitions for type TRANSMIT_GRAPH
enum TransmitGraphParameters {
    TG_TOP                  = 0,
    TG_BOTTOM               = 1,
    TG_LEFT                 = 2,
    TG_RIGHT                = 3,
    TG_INCREASE_FQ          = 4,
    TG_DECREASE_FQ          = 5,
    TG_CHANGE_TXPAR_FILE_NO = 6,
    TG_NEW_TX_FREQUENCY     = 7,
    TG_SET_SIGNAL_LEVEL     = 8,
    TG_ONOFF                = 9,
    TG_MUTE_ON              = 11,
    TG_MUTE_OFF             = 12,
    MAX_TGBUTT              = 13,
};

// Structure for the eme database.
#define CALLSIGN_CHARS 12
typedef struct {
    char call[CALLSIGN_CHARS];
    float lon;
    float lat;
} DXDATA;

// Structure for mouse buttons
typedef struct {
    int x1;
    int x2;
    int y1;
    int y2;
} BUTTONS;

// Structure to remember screen positions
// for processing parameter change boxes
typedef struct {
    int no;
    int type;
    int x;
    int y;
} SAVPARM;

// Structure for a screen object on which the mouse can operate.
typedef struct {
    int no;
    int x1;
    int x2;
    int y1;
    int y2;
} SCREEN_OBJECT;

// Structure for the AFC graph
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int mode_control;
    int avgnum;
    int window;
    int fit_points;
    int delay;
    int check;
    float minston;
    float search_range;
    float lock_range;
    float frange;
} AG_PARMS;
#define MAX_AG_INTPAR 10
extern char *ag_intpar_text[MAX_AG_INTPAR];
#define MAX_AG_FLOATPAR 4
extern char *ag_floatpar_text[MAX_AG_FLOATPAR];

// Structure for the wide graph.
// Waterfall and full dynamic range spectrum
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int yborder;
    int xpoints_per_pixel;
    int pixels_per_xpoint;
    int first_xpoint;
    int xpoints;
    int fft_avg1num;
    int spek_avgnum;
    int waterfall_avgnum;
    int spur_inhibit;
    int check;
    float yzero;
    float yrange;
    float waterfall_db_zero;
    float waterfall_db_gain;
} WG_PARMS;
#define MAX_WG_INTPAR 14
extern char *wg_intpar_text[MAX_WG_INTPAR];
#define MAX_WG_FLOATPAR 4
extern char *wg_floatpar_text[MAX_WG_FLOATPAR];

// Structure for the high resolution and blanker control graph.
// Waterfall and full dynamic range spectrum
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int stupid_bln_mode;
    int clever_bln_mode;
    int timf2_oscilloscope;
    int timf2_oscilloscope_lines;
    int timf2_oscilloscope_hold;
    int spek_avgnum;
    unsigned int stupid_bln_limit;
    unsigned int clever_bln_limit;
    int spek_zero;
    int spek_gain;
    int sellim_par1;  //0,1,2
    int sellim_par2;  //0,1
    int sellim_par3;  //0,1
    int sellim_par4;  //0,1
    int sellim_par5;  //0,1,2
    int sellim_par6;  // 0,1
    int sellim_par7;  // 0,1
    int sellim_par8;  // 0,1
    int check;
    float stupid_bln_factor;
    float clever_bln_factor;
    float blanker_ston_fft1;
    float blanker_ston_fft2;
    float timf2_oscilloscope_wk_gain;
    float timf2_oscilloscope_st_gain;
} HG_PARMS;
#define MAX_HG_INTPAR 25
extern char *hg_intpar_text[MAX_HG_INTPAR];
#define MAX_HG_FLOATPAR 6
extern char *hg_floatpar_text[MAX_HG_FLOATPAR];


// Structure for the baseband graph
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int yborder;
    int fft_avgnum;
    int pixels_per_point;
    int coh_factor;
    int delay_points;
    int agc_flag;
    int agc_attack;
    int agc_release;
    int agc_hang;
    int waterfall_avgnum;
    int wheel_stepn;
    int oscill_on;
    int horiz_arrow_mode;
    int mixer_mode;
    int filter_shift;
    int fm_mode;
    int fm_subtract;
    int fm_audio_bw;
    int ch2_phase;
    int squelch_level;
    int squelch_time;
    int squelch_point;
    int check;
    float filter_flat;
    float filter_curv;
    float yzero;
    float yrange;
    float db_per_pixel;
    float yfac_power;
    float yfac_log;
    float bandwidth;
    float first_frequency;
    float bfo_freq;
    float output_gain;
    float waterfall_gain;
    float waterfall_zero;
    float oscill_gain;
} BG_PARMS;
#define MAX_BG_INTPAR 27
extern char *bg_intpar_text[MAX_BG_INTPAR];
#define MAX_BG_FLOATPAR 14
extern char *bg_floatpar_text[MAX_BG_FLOATPAR];

// Structure for the polarization graph
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int adapt;
    int avg;
    int startpol;
    int enable_phasing;
    int check;
    float angle;
    float c1;
    float c2;
    float c3;
    float ch2_amp;
    float ch2_phase;
} PG_PARMS;
#define MAX_PG_INTPAR 9
extern char *pg_intpar_text[MAX_PG_INTPAR];
#define MAX_PG_FLOATPAR 6
extern char *pg_floatpar_text[MAX_PG_FLOATPAR];

typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    float ampl_bal;
    float phase_shift;
    float m1ampl;
    float m1phase;
    float m2ampl;
    float m2phase;
    float m3ampl;
    float m3phase;
} XG_PARMS;
#define MAX_XG_INTPAR 4
extern char *xg_intpar_text[MAX_XG_INTPAR];
#define MAX_XG_FLOATPAR 8
extern char *xg_floatpar_text[MAX_XG_FLOATPAR];


// Structure for the coherent processing graph
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int meter_graph_on;
    int oscill_on;
} CG_PARMS;
#define MAX_CG_INTPAR 6
extern char *cg_intpar_text[MAX_CG_INTPAR];
#define MAX_CG_FLOATPAR 0
extern char *cg_floatpar_text[MAX_CG_FLOATPAR+1];


// Structure for the S-meter graph
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int scale_type;
    int avgnum;
    int tracks;
    int check;
    float ygain;
    float yzero;
    float cal_dbm;
    float cal_ston;
    float cal_ston_sigshift;
    float cal_s_units;
} MG_PARMS;
#define MAX_MG_INTPAR 8
extern char *mg_intpar_text[MAX_MG_INTPAR];
#define MAX_MG_FLOATPAR 6
extern char *mg_floatpar_text[MAX_MG_FLOATPAR];


// Structure for the EME graph.
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int minimise;
} EG_PARMS;
#define MAX_EG_INTPAR 5
extern char *eg_intpar_text[MAX_EG_INTPAR];
#define MAX_EG_FLOATPAR 0
extern char *eg_floatpar_text[MAX_EG_FLOATPAR+1];

// Structure for the frequency control box.
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int yborder;
    int passband_direction;
    int gain;
    int gain_increment;
    double passband_increment;
    double passband_center;
    double tune_frequency;
} FG_PARMS;
#define MAX_FG_INTPAR 8
extern char *fg_intpar_text[MAX_FG_INTPAR];
#define MAX_FG_FLOATPAR 3
extern char *fg_floatpar_text[MAX_FG_FLOATPAR];

// Structure for the Tx control box.
typedef struct {
    int ytop;
    int ybottom;
    int xleft;
    int xright;
    int spproc_no;
    int passband_direction;
    double level_db;
    double freq;
    double band_increment;
    double band_center;
} TG_PARMS;
#define MAX_TG_INTPAR 6
extern char *tg_intpar_text[MAX_TG_INTPAR];
#define MAX_TG_FLOATPAR 4
extern char *tg_floatpar_text[MAX_TG_FLOATPAR];

// ***********************************************
// Structure used by float fft routines
typedef struct {
    float sin;
    float cos;
} COSIN_TABLE;

// ***********************************************
// Structure used by d_float fft routines (double)
typedef struct {
    double sin;
    double cos;
} D_COSIN_TABLE;

// Structure used by MMX fft routines
typedef struct {
    short int c1p;
    short int s2p;
    short int c3p;
    short int s4m;
} MMX_COSIN_TABLE;

// Structure for mixer/decimater using backwards FFTs
typedef struct {
    float *window;
    float *cos2win;
    float *sin2win;
    unsigned short int *permute;
    COSIN_TABLE *table;
    unsigned int interleave_points;
    unsigned int new_points;
    unsigned int crossover_points;
    unsigned int size;
    unsigned int n;
} MIXER_VARIABLES;

// Define setup info for each fft version.
typedef struct {
    unsigned char window;
    unsigned char permute;
    unsigned char max_n;
    unsigned char real2complex;
    unsigned char parall_fft;
    char *text;
} FFT_SETUP_INFO;

typedef struct {
    void *pointer;
    int size;
    int scratch_size;
    int num;
} MEM_INF;

typedef struct {
    float x2;
    float y2;
    float im_xy;
    float re_xy;
} TWOCHAN_POWER;

// Number of FFT implementations, see the fft_cntrl table.
#define MAX_FFT_VERSIONS 18
// Length of the fft1_version table, listing the FFT implementations allowed for FFT1.
#define MAX_FFT1_VERNR 4
// Length of the fft1_back_version table, listing the FFT implementations allowed for the reverse FFT1.
#define MAX_FFT1_BCKVERNR 2
// Length of the fft2_version table, listing the FFT implementations allowed for the FFT2.
#define MAX_FFT2_VERNR 3

#ifdef _MSC_VER
#ifndef ssize_t
#ifdef _WIN64
typedef  __int64 ssize_t;
#else
typedef  __int32 ssize_t;
#endif
#endif
#endif

#define TIMF1_UNMUTED 0
#define TIMF1_MUTED 1
