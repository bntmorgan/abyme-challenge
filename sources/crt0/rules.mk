sp              := $(sp).x
dirstack_$(sp)  := $(d)
d               := $(dir)

OBJS_$(d)				:= $(call SRC_2_OBJ, \
	$(patsubst %.c, %.o, $(wildcard $(d)/*.c)))

OBJECTS 				+= $(OBJS_$(d))

d               := $(dirstack_$(sp))
sp              := $(basename $(sp))
