/******************************************************************************
 *
 * Copyright (C) 2014 Microchip Technology Inc. and its
 *                    subsidiaries ("Microchip").
 *
 * All rights reserved.
 *
 * You are permitted to use the Aurea software, GestIC API, and other
 * accompanying software with Microchip products.  Refer to the license
 * agreement accompanying this software, if any, for additional info regarding
 * your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP, SMSC, OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH
 * OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY FOR ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR OTHER SIMILAR COSTS.
 *
 ******************************************************************************/
#include "console.h"

#include <stdlib.h>
#include <unistd.h>

void init_data(data_t *data)
{
    /* The demo should be running */
    data->running = 1;

    /* Render menu on startup. */
    data->menu_current = -1;

    /* Automatic calibration enabled by default */
    data->auto_calib = 1;

    /* No gestures so far */
    data->last_gesture = 0;

    /* No gestic_t instance allocated yet */
    data->gestic = NULL;
}

void quit()
{
    endwin();
}

int main()
{
    data_t data;

    /* Initialize curses */
    initscr();
    atexit(quit);
    clear();

    mvprintw(1, 8, "GestIC %s - Console Demo", gestic_version_str());

    /* Initialize data and the device */
    init_data(&data);
    init_device(&data);

    /* Change keyboard for menu-mode */
    noecho();
    cbreak();
    timeout(0);
    keypad(stdscr, 1);
    curs_set(0);

    /* Update device and menu until quit */
    while(data.running)
    {
        update_device(&data);
        update_menu(&data);
        refresh();
        usleep(10000);
    }

    /* Do the cleanup work */
    free_device(&data);

    return 0;
}
