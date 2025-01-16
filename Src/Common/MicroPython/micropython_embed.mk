# This file is part of the MicroPython project, http://micropython.org/
# The MIT License (MIT)
# Copyright (c) 2022-2023 Damien P. George

# Set the location of the top of the MicroPython repository.
MICROPYTHON_TOP = micropython

# Add C modules.
USER_C_MODULES = ORB/modules
CFLAGS += -IORB/modules
CFLAGS += -IORB/c_interface
CFLAGS += -IORB/python-vm


QSTR_DEFS += ORB/modules/qstr.h
# Include the main makefile fragment to build the MicroPython component.
include $(MICROPYTHON_TOP)/ports/embed/embed.mk
