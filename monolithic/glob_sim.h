#ifndef GLOB_H
#define GLOB_H

#include <stdlib.h>

typedef struct {
	int gl_pathc; /* Count of paths matched by the pattern.  */
	char ** gl_pathv; /* List of matched pathnames.  */
} glob_t;

#define	GLOB_ERR	(1 << 0)/* Return on read errors.  */
#define	GLOB_NOSORT	(1 << 2)/* Don't sort the names.  */
#define	GLOB_PERIOD	(1 << 7)/* Leading `.' can be matched by metachars.  */

int glob(char * pattern, int flags,  int *(errfunc) (char*, int),glob_t * id );

void globfree (glob_t * id);

#endif
