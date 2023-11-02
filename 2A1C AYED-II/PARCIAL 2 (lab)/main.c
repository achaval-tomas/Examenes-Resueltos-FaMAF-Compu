/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "pqueue.h"

/* The constants*/
static const int RIGHT_NUMBER_OF_ARGUMENTS = 2;

static const char *STUDENTS_FILE_FORMAT = " %u %f %u ";
static const int STUDENTS_FILE_FIELDS_FOR_RECORD = 3;
static const char *STUDENTS_DUMP_FORMAT = "%u: %f, %u -- %f";

static const char *ERR_FILE_NOT_EXIST = "File does not exist.\n";
static const char *ERR_INVALID_STUDENTS_LIST = "Invalid list of students.\n";

void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Read students arrivals with an associated data and return the"
           "order in which the students are seen.\n"
           "\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < RIGHT_NUMBER_OF_ARGUMENTS)
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

pqueue pqueue_from_file(const char *filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "%s", ERR_FILE_NOT_EXIST);
        exit(EXIT_FAILURE);
    }
    int res = 0;
    pqueue q = pqueue_empty();
    while (!feof(file))
    {
        pqueue_elem student_id = 0u;
        float average_grade = 0.f;
        unsigned int approved_courses = 0u;
        res = fscanf(file, STUDENTS_FILE_FORMAT,
                     &student_id, &average_grade, &approved_courses);
        if (res != STUDENTS_FILE_FIELDS_FOR_RECORD)
        {
            fprintf(stderr, "%s", ERR_INVALID_STUDENTS_LIST);
            pqueue_destroy(q);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        q = pqueue_enqueue(q, student_id, average_grade, approved_courses);
    }
    fclose(file);
    return q;
}

void pqueue_dump(pqueue q)
{
    pqueue copy_q = NULL;
    copy_q = pqueue_copy(q);

    unsigned int length = pqueue_size(copy_q);
    fprintf(stdout, "length: %u\n", length);

    while (!pqueue_is_empty(copy_q))
    {
        pqueue_elem elem = pqueue_peek(copy_q);
        float average_grade = pqueue_peek_average_grade(copy_q);
        unsigned int approved_courses = pqueue_peek_approved_courses(copy_q);
        float priority = pqueue_peek_priority(copy_q);

        fprintf(stdout, STUDENTS_DUMP_FORMAT,
                elem, average_grade, approved_courses, priority);

        copy_q = pqueue_dequeue(copy_q);
        if (!pqueue_is_empty(copy_q))
        {
            fprintf(stdout, "\n");
        }
    }
    fprintf(stdout, "\n");
    pqueue_destroy(copy_q);
}

int main(int argc, char *argv[])
{
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* get the dequeue from the file */
    pqueue q = pqueue_from_file(filepath);

    /* call the function for show the priority queue of patients */
    pqueue_dump(q);

    /* destroy instance of dequeue */
    q = pqueue_destroy(q);

    return (EXIT_SUCCESS);
}
