dnl $Id$
dnl config.m4 for extension slim

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(slim, for slim support,
dnl Make sure that the comment is aligned:
dnl [  --with-slim             Include slim support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(slim, whether to enable slim support,
Make sure that the comment is aligned:
[  --enable-slim           Enable slim support])

if test "$PHP_SLIM" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-slim -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/slim.h"  # you most likely want to change this
  dnl if test -r $PHP_SLIM/$SEARCH_FOR; then # path given as parameter
  dnl   SLIM_DIR=$PHP_SLIM
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for slim files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SLIM_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SLIM_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the slim distribution])
  dnl fi

  dnl # --with-slim -> add include path
  dnl PHP_ADD_INCLUDE($SLIM_DIR/include)

  dnl # --with-slim -> check for lib and symbol presence
  dnl LIBNAME=slim # you may want to change this
  dnl LIBSYMBOL=slim # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SLIM_DIR/$PHP_LIBDIR, SLIM_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SLIMLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong slim lib version or lib not found])
  dnl ],[
  dnl   -L$SLIM_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SLIM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(slim,
      slim.c                          \
      slim_slim.c                     \
      slim_log.c                      \
      slim_environment.c              \
      slim_logwriter.c                \
      slim_middleware.c               \
      slim_route.c                    \
      slim_router.c                   \
      slim_view.c                     \
      exception/pass.c                \
      exception/stop.c                \
      helper/set.c                    \
      http/cookies.c                  \
      http/headers.c                  \
      http/requests.c                 \
      http/response.c                 \
      http/util.c                     \
      middleware/content_types.c      \
      middleware/flash.c              \
      middleware/method_override.c    \
      middleware/pretty_exceptions.c  \
      middleware/session_cookie.c, $ext_shared)
fi
