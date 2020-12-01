TEMPLATE = subdirs

SUBDIRS = \
          parsy \
          cli \
          ui

cli.depends = parsy
ui.depends = parsy
