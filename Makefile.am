EXTRA_DIST = ptp-pack.c

lib_LTLIBRARIES = libptp2.la

libptp2_la_SOURCES = ptp.c ptp.h
libptp2_la_LDFLAGS = -module -avoid-version

noinst_PROGRAMS = ptpcam
ptpcam_SOURCES = ptpcam.c
ptpcam_LDADD = -lusb -lptp2
