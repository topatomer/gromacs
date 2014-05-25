/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2004, The GROMACS development team.
 * Copyright (c) 2013,2014, by the GROMACS development team, led by
 * Mark Abraham, David van der Spoel, Berk Hess, and Erik Lindahl,
 * and including many others, as listed in the AUTHORS file in the
 * top-level source directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */

#ifndef _typedefs_h
#define _typedefs_h


/* DEPRECATED! value for signaling unitialized variables */
#define NOTSET -12345

#include <sys/types.h>

#include "types/simple.h"
#include "types/enums.h"
#include "../fileio/trx.h"
#include "../topology/topology.h"
#include "types/energy.h"
#include "types/inputrec.h"
#include "types/nrnb.h"
#include "types/nblist.h"
#include "types/nbnxn_pairlist.h"
#include "types/nsgrid.h"
#include "types/forcerec.h"
#include "types/fcdata.h"
#include "types/mdatom.h"
#include "types/ifunc.h"
#include "types/group.h"
#include "types/state.h"
#include "types/shellfc.h"
#include "types/constr.h"
#include "types/oenv.h"
#include "types/commrec_fwd.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Memory (re)allocation can be VERY slow, especially with some
 * MPI libraries that replace the standard malloc and realloc calls.
 * To avoid slow memory allocation we use over_alloc to set the memory
 * allocation size for large data blocks. Since this scales the size
 * with a factor, we use log(n) realloc calls instead of n.
 * This can reduce allocation times from minutes to seconds.
 */
/* This factor leads to 4 realloc calls to double the array size */
#define OVER_ALLOC_FAC 1.19

void set_over_alloc_dd(gmx_bool set);
/* Turns over allocation for variable size atoms/cg/top arrays on or off,
 * default is off.
 */

int over_alloc_dd(int n);
/* Returns n when domain decomposition over allocation is off.
 * Returns OVER_ALLOC_FAC*n + 100 when over allocation in on.
 * This is to avoid frequent reallocation
 * during domain decomposition in mdrun.
 */

/* Over allocation for small data types: int, real etc. */
#define over_alloc_small(n) (int)(OVER_ALLOC_FAC*(n) + 8000)

/* Over allocation for large data types: complex structs */
#define over_alloc_large(n) (int)(OVER_ALLOC_FAC*(n) + 1000)

int gmx_int64_to_int(gmx_int64_t step, const char *warn);
/* Convert a gmx_int64_t value to int.
 * If warn!=NULL a warning message will be written
 * to stderr when step does not fit in an int,
 * the first line is:
 * "WARNING during %s:", where warn is printed in %s.
 */

#define STEPSTRSIZE 22

char *gmx_step_str(gmx_int64_t i, char *buf);
/* Prints a gmx_int64_t value in buf and returns the pointer to buf.
 * buf should be large enough to contain i: STEPSTRSIZE (22) chars.
 * When multiple gmx_int64_t values are printed in the same printf call,
 * be sure to call gmx_step_str with different buffers.
 */

/* Functions to initiate and delete structures *
 * These functions are defined in gmxlib/typedefs.c
 */
void init_inputrec(t_inputrec *ir);
void init_energyhistory(energyhistory_t * enerhist);
void done_energyhistory(energyhistory_t * enerhist);
void init_gtc_state(t_state *state, int ngtc, int nnhpres, int nhchainlength);
void init_state(t_state *state, int natoms, int ngtc, int nnhpres, int nhchainlength, int nlambda);
t_state *serial_init_local_state(t_state *state_global);
void init_df_history(df_history_t *dfhist, int nlambda);
void done_df_history(df_history_t *dfhist);
void copy_df_history(df_history_t * df_dest, df_history_t *df_source);
void done_inputrec(t_inputrec *ir);
void done_state(t_state *state);

void set_box_rel(t_inputrec *ir, t_state *state);
/* Set state->box_rel used in mdrun to preserve the box shape */

void preserve_box_shape(t_inputrec *ir, matrix box_rel, matrix b);
/* Preserve the box shape, b can be box or boxv */

real max_cutoff(real cutoff1, real cutoff2);
/* Returns the maximum of the cut-off's, taking into account that 0=inf. */

#ifdef __cplusplus
}
#endif


#endif  /* _typedefs_h */
