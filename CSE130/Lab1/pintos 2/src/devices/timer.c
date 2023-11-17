#include "devices/timer.h"
#include <debug.h>
#include <inttypes.h>
#include <round.h>
#include <stdio.h>
#include "devices/pit.h"
#include "threads/interrupt.h"
#include "threads/barrier.h"
#include "threads/thread.h"
  
/* See [8254] for hardware details of the 8254 timer chip. */

#if TIMER_FREQ < 19
#error 8254 timer requires TIMER_FREQ >= 19
#endif
#if TIMER_FREQ > 1000
#error TIMER_FREQ <= 1000 recommended
#endif

/* Number of timer ticks since OS booted. */
static int64_t ticks;

/* Number of loops per timer tick.
   Initialized by timer_calibrate(). */
static unsigned loops_per_tick;

static intr_handler_func timer_interrupt;
static bool too_many_loops (unsigned loops);
static void busy_wait (int64_t loops);
static void real_time_sleep (int64_t num, int32_t denom);
static void real_time_delay (int64_t num, int32_t denom);

/*************************/
static struct list sleeping_thread; //defining a list to keep track of sleeping thread
bool comparator(const struct list_elem *l1, const struct list_elem *l2, void *aux);//prototype of comparator
/*************************/
/* Sets up the timer to interrupt TIMER_FREQ times per second,
   and registers the corresponding interrupt. */
void
timer_init (void) 
{
  /*************************/
  list_init(&sleeping_thread);//Initialized from list.c kernel file
  /*************************/
  pit_configure_channel (0, 2, TIMER_FREQ);
  intr_register_ext (0x20, timer_interrupt, "8254 Timer");
}

/* Calibrates loops_per_tick, used to implement brief delays. */
void
timer_calibrate (void) 
{
  unsigned high_bit, test_bit;

  ASSERT (intr_get_level () == INTR_ON);
  printf ("Calibrating timer...  ");

  /* Approximate loops_per_tick as the largest power-of-two
     still less than one timer tick. */
  loops_per_tick = 1u << 10;
  while (!too_many_loops (loops_per_tick << 1)) 
    {
      loops_per_tick <<= 1;
      ASSERT (loops_per_tick != 0);
    }

  /* Refine the next 8 bits of loops_per_tick. */
  high_bit = loops_per_tick;
  for (test_bit = high_bit >> 1; test_bit != high_bit >> 10; test_bit >>= 1)
    if (!too_many_loops (loops_per_tick | test_bit))
      loops_per_tick |= test_bit;

  printf ("%'"PRIu64" loops/s.\n", (uint64_t) loops_per_tick * TIMER_FREQ);
}

/* Returns the number of timer ticks since the OS booted. */
int64_t
timer_ticks (void) 
{
  enum intr_level old_level = intr_disable ();
  int64_t t = ticks;
  intr_set_level (old_level);
  return t;
}

/* Returns the number of timer ticks elapsed since THEN, which
   should be a value once returned by timer_ticks(). */
int64_t
timer_elapsed (int64_t then) 
{
  return timer_ticks () - then;
}

/* Sleeps for approximately TICKS timer ticks.  Interrupts must
   be turned on. */
void
timer_sleep (int64_t ticks) 
{
  /*
  Refered the Pintos reference guide for list function: https://jeason.gitbooks.io/pintos-reference-guide-sysu/content/list.html

  1. According to the Saucer given by Prof. Harrison:
  2. Define a list for sleeping threads (sleeping_thread)
  3. initialize this somewhere approp. (sleeping_thread as a global variable)
  4. store wakeup time in current thread
  5. put the current thread into the list of sleeping thread
  6. put the current thread to sleep
  */

 //1. We make sure the thread is not idle
  if (ticks <= 0){
    return;
  }
  //2. Get the current thread from thead.h
  struct thread *current=thread_current();
  //3. Wake time is stored in current thread.
  current->wake=timer_ticks()+ticks;
  ASSERT (intr_get_level () == INTR_ON);
  //4. Disable interrupts to prevent timer interrupt from interferring. 
  intr_disable();
  //5. Insert element in the proper position in list which has to be sorted using the less_func
  //5. Sample: list_insert_ordered(struct list, struct list_elem, list_less_func, void aux)
  list_insert_ordered(&sleeping_thread, &current->sharedelem,comparator, NULL);
  //6. Put the current thread to sleep and we know block must be called when interrupts are off from thread.c
  thread_block();
  //7. Runs with interrupts off
  intr_enable();

  //while (timer_elapsed (start) < ticks) 
    //thread_yield ();
}

/*************************************/
/*
Implemented from list_less_func() in list.h. 
This function compares the value of two list (or threads in this case by their wakeup time) elements l1 and l2
And returns true if l1's wake time is less than l2's or false if l1 is greater than or equal to l2. 
*/
bool comparator(const struct list_elem *l1, const struct list_elem *l2, void *aux){
  const struct thread *thread_l1=list_entry(l1, struct thread, sharedelem);
  const struct thread *thread_l2=list_entry(l2, struct thread, sharedelem);
  if(thread_l1->wake < thread_l2->wake){
    return true;
  }
  else{
    return false;
  }
}
/*************************************/

/* Sleeps for approximately MS milliseconds.  Interrupts must be
   turned on. */
void
timer_msleep (int64_t ms) 
{
  real_time_sleep (ms, 1000);
}

/* Sleeps for approximately US microseconds.  Interrupts must be
   turned on. */
void
timer_usleep (int64_t us) 
{
  real_time_sleep (us, 1000 * 1000);
}

/* Sleeps for approximately NS nanoseconds.  Interrupts must be
   turned on. */
void
timer_nsleep (int64_t ns) 
{
  real_time_sleep (ns, 1000 * 1000 * 1000);
}

/* Busy-waits for approximately MS milliseconds.  Interrupts need
   not be turned on.

   Busy waiting wastes CPU cycles, and busy waiting with
   interrupts off for the interval between timer ticks or longer
   will cause timer ticks to be lost.  Thus, use timer_msleep()
   instead if interrupts are enabled. */
void
timer_mdelay (int64_t ms) 
{
  real_time_delay (ms, 1000);
}

/* Sleeps for approximately US microseconds.  Interrupts need not
   be turned on.

   Busy waiting wastes CPU cycles, and busy waiting with
   interrupts off for the interval between timer ticks or longer
   will cause timer ticks to be lost.  Thus, use timer_usleep()
   instead if interrupts are enabled. */
void
timer_udelay (int64_t us) 
{
  real_time_delay (us, 1000 * 1000);
}

/* Sleeps execution for approximately NS nanoseconds.  Interrupts
   need not be turned on.

   Busy waiting wastes CPU cycles, and busy waiting with
   interrupts off for the interval between timer ticks or longer
   will cause timer ticks to be lost.  Thus, use timer_nsleep()
   instead if interrupts are enabled.*/
void
timer_ndelay (int64_t ns) 
{
  real_time_delay (ns, 1000 * 1000 * 1000);
}

/* Prints timer statistics. */
void
timer_print_stats (void) 
{
  printf ("Timer: %"PRId64" ticks\n", timer_ticks ());
}

/* Timer interrupt handler. */
static void
timer_interrupt (struct intr_frame *args UNUSED)
{
  /*
  1. As per Prof. Harrison's secret sauce, we iterate over the list sleeping threads
  2. If any are at or past their wakeup time then
    1. Wake them up
    2. Remove them from the sleeping threads list.
  */
  ticks++;
  thread_tick ();
  
  // 1. Define the list_elem e to iterate over the sleeping threads list.
  struct list_elem *e=list_begin(&sleeping_thread);
  // 2. Loop through the end of sleeping threads list
  while(e != list_end(&sleeping_thread)){
    // 1. Converts from a struct list_elem back to structure object that contains it.
    struct thread *t=list_entry(e, struct thread, sharedelem);
    // 2. If any are past their wake time, remove the eleme from list and unblock them. 
    if(t->wake <= ticks){
      // 1. remove elem from list from list.c
      e=list_remove(e);
      // 2. unblocked the thread from list.c 
      thread_unblock(t);
    }
    //else continue until the next elem in list.
    else{
      // from list.c 
      e=list_next(e);
    }
  }
}

/* Returns true if LOOPS iterations waits for more than one timer
   tick, otherwise false. */
static bool
too_many_loops (unsigned loops) 
{
  /* Wait for a timer tick. */
  int64_t start = ticks;
  while (ticks == start)
    barrier ();

  /* Run LOOPS loops. */
  start = ticks;
  busy_wait (loops);

  /* If the tick count changed, we iterated too long. */
  barrier ();
  return start != ticks;
}

/* Iterates through a simple loop LOOPS times, for implementing
   brief delays.

   Marked NO_INLINE because code alignment can significantly
   affect timings, so that if this function was inlined
   differently in different places the results would be difficult
   to predict. */
static void NO_INLINE
busy_wait (int64_t loops) 
{
  while (loops-- > 0)
    barrier ();
}

/* Sleep for approximately NUM/DENOM seconds. */
static void
real_time_sleep (int64_t num, int32_t denom) 
{
  /* Convert NUM/DENOM seconds into timer ticks, rounding down.
          
        (NUM / DENOM) s          
     ---------------------- = NUM * TIMER_FREQ / DENOM ticks. 
     1 s / TIMER_FREQ ticks
  */
  int64_t ticks = num * TIMER_FREQ / denom;

  ASSERT (intr_get_level () == INTR_ON);
  if (ticks > 0)
    {
      /* We're waiting for at least one full timer tick.  Use
         timer_sleep() because it will yield the CPU to other
         processes. */                
      timer_sleep (ticks); 
    }
  else 
    {
      /* Otherwise, use a busy-wait loop for more accurate
         sub-tick timing. */
      real_time_delay (num, denom); 
    }
}

/* Busy-wait for approximately NUM/DENOM seconds. */
static void
real_time_delay (int64_t num, int32_t denom)
{
  /* Scale the numerator and denominator down by 1000 to avoid
     the possibility of overflow. */
  ASSERT (denom % 1000 == 0);
  busy_wait (loops_per_tick * num / 1000 * TIMER_FREQ / (denom / 1000)); 
}
