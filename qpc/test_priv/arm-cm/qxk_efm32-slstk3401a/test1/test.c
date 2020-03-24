/*****************************************************************************
* Product: Test for EFM32-SLSTK3401A board, preemptive QXK kernel
* Last Updated for Version: 6.7.0
* Date of the Last Update:  2018-12-21
*
*                    Q u a n t u m  L e a P s
*                    ------------------------
*                    Modern Embedded Software
*
* Copyright (C) 2005-2018 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* https://www.state-machine.com
* mailto:info@state-machine.com
*****************************************************************************/
#include "qpc.h"
#include "test.h"
#include "bsp.h"

/* local objects ...........................................................*/
static QXThread l_test1;
static QXThread l_test2;
static QXSemaphore l_sema;

/* global pointers to the objects ..........................................*/
QXSemaphore * const the_Sema = &l_sema;
QXThread * const XT_Test1 = &l_test1;
QXThread * const XT_Test2 = &l_test2;

/*..........................................................................*/
static void Thread1_run(void * const e) {
    (void)e;
    for (;;) {
        QXThread_delay(BSP_TICKS_PER_SEC / 2U);
        QXTHREAD_POST_X(XT_Test2, Q_NEW(QEvt, TEST3_SIG), QF_NO_MARGIN, me);
    }
}

/*..........................................................................*/
void Test1_ctor(void) {
    QXThread_ctor(&l_test1, &Thread1_run, 0U);
}

/*..........................................................................*/
static void Thread2_run(void * const par) {
    /* subscribe to the test signal */
    QActive_subscribe((QActive *)par, TEST1_SIG);
    QActive_subscribe((QActive *)par, TEST2_SIG);

    for (;;) {
        QEvt const *e;

        BSP_ledOn();
        e = QXThread_queueGet(QXTHREAD_NO_TIMEOUT);
        BSP_ledOff();
        QF_gc(e); /* must explicitly recycle the event! */

        QXThread_delay(BSP_TICKS_PER_SEC / 4U);  /* wait more (BLOCK) */

        /* wait on a semaphore (BLOCK indefinitely) */
        //QXSemaphore_wait(the_Sema, QXTHREAD_NO_TIMEOUT);
        QXThread_delay(1U);  /* wait more (BLOCK) */
    }
}

/*..........................................................................*/
void Test2_ctor(void) {
    QXThread_ctor(&l_test2, &Thread2_run, 0U);
}
