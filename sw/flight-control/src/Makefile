PROJECT = flight-control
BUILD_DIR = bin

SHARED_DIR = ../inc ../messages
CPPFILES = main.cpp logger.cpp
CFILES = port.c queue.c tasks.c heap_1.c list.c stream_buffer.c
CFLAGS += -g3 -gdwarf-4
CXXFLAGS += -g3 -gdwarf-4

# TODO - you will need to edit these two lines!
DEVICE=stm32f103c8t6
OOCD_FILE = UNIMPLEMENTED.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
