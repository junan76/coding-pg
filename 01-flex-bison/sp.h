#ifndef _SP_H
#define _SP_H

struct chanel_list
{
    int chanel;
    struct chanel_list *next;
};

struct pindef_list
{
    int pin_no;
    char pin_name[32];
    struct chanel_list chanels_head;
    struct pindef_list *next;
};

struct socket_program
{
    char sp_bin_name[32];
    int sp_dut_max_pin;
    int sp_dut_measurement_count;
    int sp_iopinmode;
    struct pindef_list pindefs_head;
};

void init_socket_program();
void add_start_block(const char *bin_name, const int len, const int dut_max_pin);
void add_multiple_block(const int dut_measurement_count);
void add_iopinmode_block(const int iopinmode);
void add_pindef_block();
void insert_chanel_list(const int chanel);
void reset_chanels();
void insert_pindef_list(const int pin_no, const char *pin_name, const int len);
void print_socket_program();

#endif