#include <stdlib.h>
#include "qpc.h"
#include "bsp.h"
#include "shape.h"
#include "rectangle.h"
#include "circle.h"


Q_DEFINE_THIS_FILE

QXSemaphore SW1_sema;

/*Shape instance*/
Shape s1(1,2); // static allocation

/*Rectangle instance*/
Rectangle r1(1, 2, 15, 10);

/*Circle instance*/
Circle c1(3, 4, 1);

/*Areas*/
uint32_t r1Arear1;
uint32_t a;

uint32_t stack_blinky1[40];
QXThread blinky1;
void main_blinky1(QXThread * const me) {
    while (1) {
        BSP_sendMorseCode(0xA8EEE2A0U); /* "SOS" */
        QXThread_delay(1U); /* block for 1 tick */
    }
}

uint32_t stack_blinky2[40];
QXThread blinky2;
void main_blinky2(QXThread * const me) {
    while (1) {
        uint32_t volatile i;

        QXSemaphore_wait(&SW1_sema,  /* pointer to semaphore to wait on */
                         QXTHREAD_NO_TIMEOUT); /* timeout for waiting */

        for (i = 3*1500U; i != 0U; --i) {
            //BSP_ledBlueOn();
            //BSP_ledBlueOff();
            BSP_ledBlueToggle();
        }
    }
}

uint32_t stack_blinky3[40];
QXThread blinky3;
void main_blinky3(QXThread * const me) {
    while (1) {
        BSP_sendMorseCode(0xE22A3800U); /* "TEST" */
        BSP_sendMorseCode(0xE22A3800U); /* "TEST" */
        QXThread_delay(5U);
    }
}



int main() {
    Shape s2(3,4); // dynamic allocation
    Shape *s3_p = new Shape(5, 6); // dynamic memory allocation
	
		/*Upcasting*/
		Shape *ps = &r1;
	
		/*Upcasted rectangle*/
		r1.draw();	// Early binding
		ps->draw();	// Late binding (or dynamic or RealTime)
		a = ps->area();
	
	
	
	
		/*Graph pointer array*/
		Shape const *graph[] = {
			&c1,
			&r1,
			s3_p,
			(Shape *)0
		};
		drawGraph(graph);
	
    /*Move the guys*/
    s1.moveBy(7, 8);
    s2.moveBy(9, 10);
    s3_p->moveBy(-1, -2);

    /*Assertions*/
    Q_ASSERT(s1.distanceFrom(&s1) == 0U);
    Q_ASSERT(s1.distanceFrom(&s2) == s2.distanceFrom(&s1));
    Q_ASSERT(s1.distanceFrom(&s1) <= 
            s1.distanceFrom(&s2) + s2.distanceFrom(s3_p));
	
		/*Rectangle draw*/
		r1.draw();	
		r1Arear1 = r1.area();
		/*Inheritance*/
		r1.moveBy(7, 8);
		Q_ASSERT(r1.distanceFrom(&r1) == 0U);
		
		
		
	
    /*Free s3_p heap memory*/
    delete s3_p;
    
    QF_init();
    BSP_init();

    /* initialize the SW1_sema semaphore as binary, signaling semaphore */
    QXSemaphore_init(&SW1_sema, /* pointer to semaphore to initialize */
                     0U,  /* initial semaphore count (singaling semaphore) */
                     1U); /* maximum semaphore count (binary semaphore) */

    /* initialize and start blinky1 thread */
    QXThread_ctor(&blinky1, &main_blinky1, 0);
    QXTHREAD_START(&blinky1,
                   5U, /* priority */
                   (void *)0, 0, /* message queue (not used) */
                   stack_blinky1, sizeof(stack_blinky1), /* stack */
                   (QEvt *)0); /* extra parameter (not used) */

    /* initialize and start blinky2 thread */
    QXThread_ctor(&blinky2, &main_blinky2, 0);
    QXTHREAD_START(&blinky2,
                   2U, /* priority */
                   (void *)0, 0, /* message queue (not used) */
                   stack_blinky2, sizeof(stack_blinky2), /* stack */
                   (QEvt *)0); /* extra parameter (not used) */

    /* initialize and start blinky3 thread */
    QXThread_ctor(&blinky3, &main_blinky3, 0);
    QXTHREAD_START(&blinky3,
                   1U, /* priority */
                   (void *)0, 0, /* message queue (not used) */
                   stack_blinky3, sizeof(stack_blinky3), /* stack */
                   (QEvt *)0); /* extra parameter (not used) */

    /* transfer control to the RTOS to run the threads */
    return QF_run();
}
