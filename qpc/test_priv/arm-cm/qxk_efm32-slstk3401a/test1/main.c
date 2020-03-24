/*****************************************************************************
* Product: Test for EFM32-SLSTK3401A board, preemptive QXK kernel
* Last updated for version 6.4.0
* Last updated on  2019-02-08
*
*                    Q u a n t u m  L e a P s
*                    ------------------------
*                    Modern Embedded Software
*
* Copyright (C) 2005-2019 Quantum Leaps, LLC. All rights reserved.
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

Q_DEFINE_THIS_FILE

static QTicker l_ticker0;
QActive * const the_Ticker0 = &l_ticker0;

/*..........................................................................*/
int main() {
    static QSubscrList subscrSto[MAX_PUB_SIG];
    static QF_MPOOL_EL(QEvt) smlPoolSto[20]; /* small pool */

    /* stacks and queues for the extended test threads */
    static void const *test1QueueSto[5];
    static uint64_t test1StackSto[64];
    static void const *test2QueueSto[5];
    static uint64_t test2StackSto[64];

    QF_init();    /* initialize the framework and the underlying RT kernel */
    BSP_init();   /* initialize the Board Support Package */

    /* object dictionaries... */
    QS_OBJ_DICTIONARY(the_Ticker0);
    QS_OBJ_DICTIONARY(the_Sema);
    QS_OBJ_DICTIONARY(XT_Test1);
    QS_OBJ_DICTIONARY(XT_Test2);

    /* initialize publish-subscribe... */
    QF_psInit(subscrSto, Q_DIM(subscrSto));

    /* initialize event pools... */
    QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    /* initialize the semaphore used in the Tests */
    QXSemaphore_init(the_Sema,
                     0U,  /* count==0 (signaling semaphore) */
                     1U); /* max_count==1 (binary semaphore) */

    /* start the extended thread */
    Test1_ctor(); /* instantiate the Test1 extended thread */
    QXTHREAD_START(XT_Test1,              /* Thread to start */
                  (uint_fast8_t)1,        /* QP priority of the thread */
                  test1QueueSto,          /* message queue storage */
                  Q_DIM(test1QueueSto),   /* message length [events] */
                  test1StackSto,          /* stack storage */
                  sizeof(test1StackSto),  /* stack size [bytes] */
                  (QEvt *)0);             /* initialization event */

    /* NOTE: leave priority 2 free for a mutex */

    /* example of prioritizing the Ticker0 active object */
    QTicker_ctor(the_Ticker0, 0U); /* ticker AO for tick rate 0 */
    QACTIVE_START(the_Ticker0, (uint_fast8_t)3, 0, 0, 0, 0, 0);

    /* NOTE: leave priority 4 free for mutex */

    Test2_ctor(); /* instantiate the Test2 extended thread */
    QXTHREAD_START(XT_Test2,              /* Thread to start */
                  (uint_fast8_t)5,        /* QP priority of the thread */
                  test2QueueSto,          /* message queue storage */
                  Q_DIM(test2QueueSto),   /* message length [events] */
                  test2StackSto,          /* stack storage */
                  sizeof(test2StackSto),  /* stack size [bytes] */
                  (QEvt *)0);             /* initialization event */

    return QF_run(); /* run the QF application */
}

