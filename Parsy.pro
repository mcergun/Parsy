TEMPLATE = subdirs

SUBDIRS = \
          cli \
          parsy

cli.depends = parsy

DEFINES += \
           _CRT_SECURE_NO_WARNINGS
