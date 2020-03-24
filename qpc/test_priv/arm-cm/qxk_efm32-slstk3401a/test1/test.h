/*****************************************************************************
* Product: Test for EFM32-SLSTK3401A board, preemptive QXK kernel
* Last Updated for Version: 6.3.7
* Date of the Last Update:  2018-11-08
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
#ifndef test_h
#define test_h

enum TestSignals {
    TEST1_SIG = Q_USER_SIG,
    TEST2_SIG,
    MAX_PUB_SIG,    /* the last published signal */

    TEST3_SIG,
    TEST4_SIG,
    MAX_SIG         /* the last signal */
};

extern QActive * const the_Ticker0;
extern QXThread * const XT_Test1;
extern QXThread * const XT_Test2;
extern QXSemaphore * const the_Sema;


void Test1_ctor(void);
void Test2_ctor(void);

#endif /* test_h */
