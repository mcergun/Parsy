TEMPLATE = subdirs

SUBDIRS = \
          parsy \
          cli \
          ui

cli.depends = parsy
ui.depends = parsy

DEFINES += \
           _CRT_SECURE_NO_WARNINGS
