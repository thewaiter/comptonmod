dnl Process this file with autoconf to produce a configure script.

# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT([comptonmod],[0.0.1],[moksha@bodhilinux.com])
AC_PREREQ([2.71])
AC_CONFIG_SRCDIR(configure.ac)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_SEARCH_LIBS([strerror],[cposix])

AM_INIT_AUTOMAKE(1.6)
AC_CONFIG_HEADERS(config.h)

AC_PROG_CC

AC_CHECK_INCLUDES_DEFAULT
AC_PROG_EGREP

define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
LT_INIT

PKG_CHECK_MODULES(E, [enlightenment])
release=$(pkg-config --variable=release enlightenment)
MODULE_ARCH="$host_os-$host_cpu"
AC_SUBST(MODULE_ARCH)
AC_DEFINE_UNQUOTED(MODULE_ARCH, "$MODULE_ARCH", "Module architecture")


datadir=$(pkg-config --variable=modules enlightenment)/${PACKAGE}
AC_ARG_ENABLE(homedir-install,
  AS_HELP_STRING([--enable-homedir-install], [Install module in homedir]),
  [ datadir="${HOME}/.e/e/modules/${PACKAGE}" ]
)

AC_CONFIG_FILES([
Makefile
src/Makefile
data/Makefile
data/etc/Makefile
data/etc/compton.conf
e_modules-comptonmod.spec
module.desktop
])
AC_CONFIG_COMMANDS([default],[
],[])
AC_OUTPUT
