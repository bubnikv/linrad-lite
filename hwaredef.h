
void set_hardware_rx_gain(void);
void set_hardware_rx_frequency(void);
void set_hardware_tx_frequency(void);

extern int hware_flag;

// These parameters define the frequency control window.
#define FREQ_MHZ_DECIMALS 3
#define FREQ_MHZ_DIGITS 4
#define FREQ_MHZ_ROUNDCORR (0.5*pow(10,-FREQ_MHZ_DECIMALS))
#define FG_HSIZ ((FREQ_MHZ_DECIMALS+FREQ_MHZ_DIGITS+6)*text_width)
#define FG_VSIZ (3*text_height)
