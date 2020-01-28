#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([stdplus], [v0.0.1], [hi@std.plus])
AC_CONFIG_SRCDIR([inc/stdplus.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE(subdir-objects foreign)

ROOT_DIR=`pwd`
AC_SUBST(ROOT_DIR)
: ${CFLAGS=""}
AM_SILENT_RULES(no)

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES(Makefile
                src/Makefile
                unit_test/Makefile)

AC_OUTPUT
