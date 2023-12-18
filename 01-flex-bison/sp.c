#include "sp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct socket_program sp;

void init_socket_program()
{
    memset(&sp, 0, sizeof(sp));
}

void add_start_block(const char *bin_name, const int len, const int dut_max_pin)
{
    strncpy(sp.sp_bin_name, bin_name, len);
    sp.sp_dut_max_pin = dut_max_pin;
}

void add_multiple_block(const int dut_measurement_count)
{
    sp.sp_dut_measurement_count = dut_measurement_count;
}

void add_iopinmode_block(const int iopinmode)
{
    sp.sp_iopinmode = iopinmode;
}

static struct chanel_list *chanels = NULL;
void insert_chanel_list(const int chanel)
{
    struct chanel_list *cur = chanels;
    if (cur == NULL)
    {
        cur = malloc(sizeof(*chanels));
        chanels = cur;
    }
    else
    {
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(*cur));
        cur = cur->next;
    }
    cur->chanel = chanel;
    cur->next = NULL;
}

void reset_chanels()
{
    chanels = NULL;
}

struct pindef_list *pindefs = NULL;
void insert_pindef_list(const int pin_no, const char *pin_name, const int len)
{
    struct pindef_list *cur = pindefs;
    if (cur == NULL)
    {
        cur = malloc(sizeof(*pindefs));
        pindefs = cur;
    }
    else
    {

        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(*cur));
        cur = cur->next;
    }
    cur->pin_no = pin_no;
    strncpy(cur->pin_name, pin_name, len);
    cur->chanels_head.next = chanels;
    cur->next = NULL;
}

void add_pindef_block()
{
    sp.pindefs_head.next = pindefs;
    pindefs = NULL;
}

void print_socket_program()
{
    printf("\n\nSOCKET PROGRAM:\n"
           "\tBINARY NAME: %s\n"
           "\tMAX DUT PIN NUMBERS: %d\n"
           "\tMEASURED DUT COUNT: %d\n"
           "\tIOPINMODE: %d\n",
           sp.sp_bin_name, sp.sp_dut_max_pin, sp.sp_dut_measurement_count, sp.sp_iopinmode);

    struct pindef_list *pindef_list = sp.pindefs_head.next;
    struct chanel_list *chanel_list = NULL;
    printf("\tPINDEFS:\n");
    while (pindef_list != NULL)
    {
        printf("\t\t(pin_no: %d, pin_name: %s, chanels: ", pindef_list->pin_no, pindef_list->pin_name);
        chanel_list = pindef_list->chanels_head.next;
        while (chanel_list)
        {
            printf("%d%c", chanel_list->chanel, chanel_list->next != NULL ? ',' : '\0');
            chanel_list = chanel_list->next;
        }
        printf(")\n");
        pindef_list = pindef_list->next;
    }
}