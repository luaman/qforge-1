/*
	#FILENAME#

	#DESCRIPTION#

	Copyright (C) 2002 #AUTHOR#

	Author: #AUTHOR#
	Date: #DATE#

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

static __attribute__ ((unused))
const char  rcsid[] = "$Id$";

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "QF/sys.h"
#include "QF/cbuf.h"
#include "QF/gib_parse.h"
#include "QF/gib_thread.h"
#include "QF/gib_function.h"
#include "QF/gib_buffer.h"
#include "QF/dstring.h"
#include "QF/hash.h"

gib_thread_t *gib_threads = 0;
gib_thread_t **gib_thread_p = &gib_threads;

hashtab_t  *gib_events;

static unsigned long int nextid = 0;

void
GIB_Thread_Add (gib_thread_t * thread)
{
	thread->prev = *gib_thread_p;
	*gib_thread_p = thread;
	gib_thread_p = &thread->next;
}

void
GIB_Thread_Remove (gib_thread_t * thread)
{
	if (thread->prev)
		thread->prev->next = thread->next;
	else
		gib_threads = thread->next;
	if (thread->next)
		thread->next->prev = thread->prev;
	else if (thread->prev)
		gib_thread_p = &thread->prev->next;
	else
		gib_thread_p = &gib_threads;
}

gib_thread_t *
GIB_Thread_Find (unsigned long int id)
{
	gib_thread_t *cur;

	for (cur = gib_threads; cur; cur = cur->next)
		if (cur->id == id)
			return cur;
	return 0;
}

gib_thread_t *
GIB_Thread_New (void)
{
	gib_thread_t *new = calloc (1, sizeof (gib_thread_t));

	new->cbuf = Cbuf_New (&gib_interp);
	new->id = nextid;
	nextid++;
	return new;
}

static void
GIB_Thread_Delete (gib_thread_t * thread)
{
	Cbuf_DeleteStack (thread->cbuf);
	free (thread);
}

void
GIB_Thread_Execute (void)
{
	gib_thread_t *cur, *tmp;

	if (!gib_threads)
		return;

	for (cur = gib_threads; cur; cur = tmp) {
		tmp = cur->next;
		if (cur->trash) {
			GIB_Thread_Remove (cur);
			GIB_Thread_Delete (cur);
		} else
			Cbuf_Execute_Stack (cur->cbuf);
	}
}

static const char *
GIB_Event_Get_Key (void *ele, void *ptr)
{
	return ((gib_event_t *) ele)->name;
}

static void
GIB_Event_Free (void *ele, void *ptr)
{
	gib_event_t *ev = (gib_event_t *) ele;

	free ((void *) ev->name);
	free (ev);
}

gib_event_t *
GIB_Event_New (const char *name)
{
	gib_event_t *new;

	new = calloc (1, sizeof (gib_event_t));
	new->name = strdup (name);
	Hash_Add (gib_events, new);
	return new;
}

int
GIB_Event_Register (const char *name, gib_function_t * func)
{
	gib_event_t *ev;

	if (!(ev = Hash_Find (gib_events, name)))
		return -1;
	ev->func = func;
	return 0;
}

void
GIB_Event_Callback (gib_event_t * event, unsigned int argc, ...)
{
	gib_function_t *f = event->func;
	gib_thread_t *thread;
	cbuf_args_t *args;
	va_list     ap;
	unsigned int i;

	if (!f)
		return;

	thread = GIB_Thread_New ();
	args = Cbuf_ArgsNew ();

	va_start (ap, argc);

	Cbuf_ArgsAdd (args, f->name);
	for (i = 0; i < argc; i++)
		Cbuf_ArgsAdd (args, va_arg (ap, const char *));

	va_end (ap);

	GIB_Function_Execute (thread->cbuf, f, args->argv, args->argc);
	GIB_Thread_Add (thread);
	Cbuf_ArgsDelete (args);
}

void
GIB_Event_Init (void)
{
	gib_events = Hash_NewTable (1024, GIB_Event_Get_Key, GIB_Event_Free, 0);
}
