
// Structure for RTL2832 parameters
typedef struct {
    int sampling_speed;
    int sernum1;
    int sernum2;
    int sernum3;
    int gain_mode;
    int freq_adjust;
    int direct_sampling;
    int bandwidth;
    int check;
} P_RTL2832;
#define MAX_RTL2832_PARM 9
extern P_RTL2832 rtl2832;

extern char *rtl2832_name_string;

char *pkgsize[2];
char *onoff[2];
char *adgains[2];
char *inp_connect[2];
char *rffil[2];



extern int *rtl2832_gains;
extern int no_of_rtl2832_gains;
extern int old_rtl2832_gain;

int display_rtl2832_parm_info(int *line);
void sdr_target_name(char *ss);
void sdr_target_serial_number(char *ss);
void init_rtl2832(void);
