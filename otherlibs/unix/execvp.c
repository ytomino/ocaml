/**************************************************************************/
/*                                                                        */
/*                                 OCaml                                  */
/*                                                                        */
/*             Xavier Leroy, projet Cristal, INRIA Rocquencourt           */
/*                                                                        */
/*   Copyright 1996 Institut National de Recherche en Informatique et     */
/*     en Automatique.                                                    */
/*                                                                        */
/*   All rights reserved.  This file is distributed under the terms of    */
/*   the GNU Lesser General Public License version 2.1, with the          */
/*   special exception on linking described in the file LICENSE.          */
/*                                                                        */
/**************************************************************************/

#define _GNU_SOURCE  /* helps to find execvpe() */
#include <caml/mlvalues.h>
#include <caml/memory.h>
#define CAML_INTERNALS
#include <caml/osdeps.h>
#include "unixsupport.h"

CAMLprim value unix_execvp(value path, value args)
{
  char_os ** argv;
  char_os * wpath;
  caml_unix_check_path(path, "execvp");
  argv = cstringvect(args, "execvp");
  wpath = caml_stat_strdup_to_os(String_val(path));
  (void) execvp_os((const char_os *)wpath, EXECV_CAST argv);
  caml_stat_free(wpath);
  cstringvect_free(argv);
  uerror("execvp", path);
  return Val_unit;                  /* never reached, but suppress warnings */
                                    /* from smart compilers */
}

#ifndef HAS_EXECVPE
/* Use our implementation instead.  */
static int 
execvpe_local(const char *name, char *const *argv, char *const *envp);
#undef execvpe_os
#define execvpe_os execvpe_local
#endif


CAMLprim value unix_execvpe(value path, value args, value env)
{
  char_os ** argv;
  char_os ** envp;
  char_os * wpath;
  caml_unix_check_path(path, "execvpe");
  argv = cstringvect(args, "execvpe");
  envp = cstringvect(env, "execvpe");
  wpath = caml_stat_strdup_to_os(String_val(path));
  (void) execvpe_os((const char_os *)wpath, EXECV_CAST argv, EXECV_CAST envp);
  caml_stat_free(wpath);
  cstringvect_free(argv);
  cstringvect_free(envp);
  uerror("execvpe", path);
  return Val_unit;                  /* never reached, but suppress warnings */
                                    /* from smart compilers */
}

#ifndef HAS_EXECVPE

/* Reimplementation of execvpe() */

/* Since Windows provides execvpe(), our reimplementation can assume
   POSIX.1 system calls and needs not handle wide character strings. */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SHELL "/bin/sh"
#define DEFAULT_PATH  "/bin:/usr/bin"

static int
execvpe_aux(const char *file, char *const *argv, char *const *envp)
{
  mlsize_t argc;
  char ** new_argv;
  int err;

  /* Try to execute directly */
  execve(file, argv, envp);
  if (errno != ENOEXEC) return errno;
  /* If NOEXEC error, assume it is a script and try to execute through shell */
  for (argc = 0; argv[argc] != NULL; argc++) /*nothing*/;
  /* Skip old argv[0] if provided */
  if (argc > 0) { argv++; argc--; }
  /* argv[0] ... argv[argc-1] are the arguments to give to the shell script.
     argv[argc] is the terminating NULL. */
  /* Create new argv vector */
  new_argv = caml_stat_alloc((argc + 3) * sizeof(char *));
  new_argv[0] = DEFAULT_SHELL;
  new_argv[1] = (char *) file;
  /* Copy arguments, including final NULL */
  memcpy(new_argv + 2, argv, (argc + 1) * sizeof(char *));
  /* Try execution again */
  execve(new_argv[0], new_argv, envp);
  err = errno;
  caml_stat_free(new_argv);
  return err;
}

static int
execvpe_local(const char *name, char *const *argv, char *const *envp)
{
  char * path, * dir, * fullname, * tofree;
  struct ext_table paths;
  int i, err, eacces;

  /* Simple errors */
  if (name == NULL || name[0] == 0) { errno = ENOENT; return -1; }
  /* If it is an absolute or relative path, don't search */
  if (strchr(name, '/') != NULL) {
    execvpe_aux(name, argv, envp);
    return -1;
  }
  /* Decompose the file path as an array of directory names */
  path = getenv("PATH");
  if (path == NULL) path = DEFAULT_PATH;
  caml_ext_table_init(&paths, 8);
  tofree = caml_decompose_path(&paths, path);
  /* Try each directory in turn */
  eacces = 0;
  for (i = 0; i < paths.size; i++) {
    dir = paths.contents[i];
    if (dir[0] == 0) dir = ".";  /* empty path component = current dir */
    fullname = caml_stat_strconcat(3, dir, "/", name);
    err = execvpe_aux(fullname, argv, envp);
    caml_stat_free(fullname);
    switch (err) {
    case EACCES:
      /* Record that we found a file but were denied permission to run it.
         Then try the next directory in the path. */
      eacces = 1; break;
      /* The following errors are considered as nonfatal and worth
         trying the next directory in the path.  It is the union
         of the error codes considered  as nonfatal by the OpenBSD and Glibc 
         implementations of execvpe.  All the error codes are POSIX.1. */
    case EISDIR:
    case ELOOP:
    case ENAMETOOLONG:
    case ENODEV:      
    case ENOENT:
    case ENOTDIR:
    case ESTALE:
    case ETIMEDOUT:
      /* Try the next directory in the path. */
      break;
    default:
      /* Now we have a serious error, e.g. E2BIG for "too many arguments".
         Stop searching in the path and returns immediately with this error. */
      caml_stat_free(tofree);
      errno = err;
      return -1;
    }
  }
  caml_stat_free(tofree);
  /* If we found at least one file with the right name but were denied
     permission to run it, return EACCES.  Otherwise, return ENOENT to
     mean that no file with the right name was found. */
  errno = eacces ? EACCES : ENOENT;
  return -1;
}

#endif
