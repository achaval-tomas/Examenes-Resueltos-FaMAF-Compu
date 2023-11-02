#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include <stdbool.h>

typedef struct s_pqueue *pqueue;

typedef unsigned int pqueue_elem;

#define MAX_GRADE 10.0
/*
 * DESC: Maximum possible grade.
 */

#define TOTAL_COURSES 30.0
/*
 * DESC: Total number of courses in the degree.
 */

pqueue pqueue_empty(void);
/*
 * DESC: Creates a new instance of pqueue
 *
 * PRE: {true}
 *  q = pqueue_empty();
 * POS: {q --> pqueue && pqueue_is_empty(q)}
 *
 */

pqueue pqueue_enqueue(pqueue q,
                      pqueue_elem e,
                      float average_grade,
                      unsigned int approved_courses);
/*
 * DESC: Adds element 'e' into the pqueue 'q' with the given 'priority'
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_enqueue(q, e, average_grade, approved_courses);
 * POS: {q --> pqueue && !pqueue_is_empty()}
 *
 */

bool pqueue_is_empty(pqueue q);
/*
 * DESC: Indicates whether the pqueue 'q' is empty or not
 *
 */

unsigned int pqueue_size(pqueue q);
/*
 * DESC: Return the number of elements inside the pqueue 'q'
 *
 */

pqueue_elem pqueue_peek(pqueue q);
/*
 * DESC: Return the element with the most urgent prioritiy of the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  e = pqueue_peek(q);
 * POS: {q --> pqueue}
 */

float pqueue_peek_average_grade(pqueue q);
/*
 * DESC: Return the average_grade that is most urgent from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  average_grade = pqueue_peek_average_grade(q);
 * POS: {q --> pqueue}
 */

unsigned int pqueue_peek_approved_courses(pqueue q);
/*
 * DESC: Return the approved_courses that is most urgent from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  approved_courses = pqueue_peek_approved_courses(q);
 * POS: {q --> pqueue}
 */

float pqueue_peek_priority(pqueue q);
/*
 * DESC: Return the priority that is most urgent from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  priority = pqueue_peek_priority(q);
 * POS: {q --> pqueue}
 */

pqueue pqueue_copy(pqueue q);
/*
 * DESC: Return a copy pqueue 'q'
 *
 * PRE: {q --> pqueue}
 *  copy = pqueue_copy(q);
 * POS: {q --> pqueue}
 */

pqueue pqueue_dequeue(pqueue q);
/*
 * DESC: Remove the element with the most urgent priority of the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  q = pqueue_dequeue(q);
 * POS: {q --> pqueue}
 *
 */

pqueue pqueue_destroy(pqueue q);
/*
 * DESC: Destroy instance of pqueue, freeing all memory used by 'q'.
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_destroy(q);
 * POS: {q == NULL}
 *
 */

#endif
