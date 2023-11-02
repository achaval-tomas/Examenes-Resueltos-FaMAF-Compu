#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *front;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float priority = 0.5 * (average_grade/MAX_GRADE) 
                        + 0.5 * (approved_courses/TOTAL_COURSES);
    assert(priority >= 0 && priority<=1);
    return priority;
}

static struct s_node *create_node(pqueue_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{

    struct s_node *new_node = NULL;
    float priority = calculate_priority(average_grade, approved_courses);
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);

    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = priority;
    new_node->next = NULL;

    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    bool check = (q!=NULL);

    if (q->size > 1u){      // Si hay más de un elemento entonces debo asegurar que estén 
        struct s_node *iterator = q->front;          // correctamente ordenados por prioridades.
        while (iterator->next != NULL && check){
            check = iterator->priority >= iterator->next->priority;
            iterator = iterator->next;
        }
    }
    return check;
}

/* Creo una cola vacía con tamaño 0 y sin elementos */
pqueue pqueue_empty(void)
{
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    assert(q!=NULL);
    q->size = 0u;
    q->front = NULL;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q,
                      pqueue_elem e,
                      float average_grade,
                      unsigned int approved_courses)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    float priority = calculate_priority(average_grade, approved_courses);

    if (q->size == 0u){   // Si aún no hay elementos, el nuevo nodo será el primero de la cola.
        q->front = new_node;
    } else if (priority > pqueue_peek_priority(q)){
        new_node->next = q->front;   // Si la prioridad del nodo a agregar es mayor a cualquier otra de la cola, 
        q->front = new_node;        // entonces el nuevo nodo será agregado al inicio.
    } else {
        struct s_node *iterator = q->front;
        while(iterator->next != NULL && iterator->next->priority >= priority){
            iterator = iterator->next;
        }                                       // En otro caso, el nuevo nodo será agregado en frente del primer elemento
        new_node->next = iterator->next;       // de la cola que tenga una prioridad menor a la suya. Si dicho elemento 
        iterator->next = new_node;            // no existe, entonces el nuevo nodo se agrega al final del todo.
    }

    q->size += 1;  // Siempre que se utilice la funcion enqueue aumentará el tamaño de la queue por 1.
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return (q->size == 0u);
}


pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->approved_courses;
}

float pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    pqueue copied_queue = pqueue_empty();  // Inicializo una nueva cola vacía.

    struct s_node *adder = q->front;
    for (unsigned int iterator = 0u; iterator < q->size; ++iterator){
        assert(adder!=NULL);
        copied_queue = pqueue_enqueue(copied_queue, adder->elem, adder->average_grade,
                                        adder->approved_courses);
        adder = adder->next;
    }  // Todos los elementos de q están en copied_queue.

    assert(invrep(q) && invrep(copied_queue) 
           && pqueue_size(q) == pqueue_size(copied_queue));
    return copied_queue;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    
    struct s_node *dequeue_me = q->front;
    q->front = q->front->next;
    dequeue_me = destroy_node(dequeue_me);
    q->size -= 1;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    while (!pqueue_is_empty(q)){
        q = pqueue_dequeue(q);   // Destruyo todos los nodos de la cola hasta
    }                           // que la misma esté totalmente vacía.
    q->front = NULL;
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}