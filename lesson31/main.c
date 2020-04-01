#include <stdlib.h>
#include "qpc.h"
#include "bsp.h"
#include "shape.h"
#include "rectangle.h"

Q_DEFINE_THIS_FILE

QXSemaphore SW1_sema;

/*Shape instance*/
Shape s1; // static allocation
/*Rectangle instance*/
Rectangle_t r1;

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
    Shape s2; // dynamic allocation
    Shape *s3_p = malloc(sizeof(Shape)); // dynamic memory allocation
		//Shape const *s1_p = &s1;
    uint32_t r1Area;
	
    /*Constructors*/
    shape_constructor(&s1, 1, 2);
    shape_constructor(&s2, 3, 4);
    shape_constructor(s3_p, 5, 6);
		//shape_constructor(s1_p, 5, 6);
    Rectangle_ctor(&r1, 1, 2, 15, 10);

    /*Move the guys*/
    shape_moveBy(&s1, 7, 8);
    shape_moveBy(&s2, 9, 10);
    shape_moveBy(s3_p, -1, -2);
	
	    /*Draw Rectangle*/
    Rectangle_draw(&r1);

    /*Rectangle Area*/
    r1Area = Rectangle_area(&r1);
		

    /*Assertions*/
    Q_ASSERT(shape_distanceFrom(&s1, &s1) == 0U);
    Q_ASSERT(shape_distanceFrom(&s1, &s2) == shape_distanceFrom(&s2, &s1));
    Q_ASSERT(shape_distanceFrom(&s1, &s1) <= 
            shape_distanceFrom(&s1, &s2) + shape_distanceFrom(&s2, s3_p));
   		
		/*Rectangle inheritance*/
		shape_moveBy((Shape *)&r1, 7, 8);
		Q_ASSERT(shape_distanceFrom((Shape *)&r1, (Shape *)&r1) == 0U);
	

    /*Free s3_p heap memory*/
    free(s3_p);
    
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
                   (void *)0); /* extra parameter (not used) */

    /* initialize and start blinky2 thread */
    QXThread_ctor(&blinky2, &main_blinky2, 0);
    QXTHREAD_START(&blinky2,
                   2U, /* priority */
                   (void *)0, 0, /* message queue (not used) */
                   stack_blinky2, sizeof(stack_blinky2), /* stack */
                   (void *)0); /* extra parameter (not used) */

    /* initialize and start blinky3 thread */
    QXThread_ctor(&blinky3, &main_blinky3, 0);
    QXTHREAD_START(&blinky3,
                   1U, /* priority */
                   (void *)0, 0, /* message queue (not used) */
                   stack_blinky3, sizeof(stack_blinky3), /* stack */
                   (void *)0); /* extra parameter (not used) */

    /* transfer control to the RTOS to run the threads */
    return QF_run();
}
