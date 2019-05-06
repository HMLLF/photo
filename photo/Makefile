TARGET := main

CC := arm-linux-gcc

CARCS += $(wildcard *.c)
OBJS += $(patsubst  %.c,%.o,$(CARCS))

LIBS += -L/opt/arm_libs/lib -ljpeg
INCL += -I/home/gec/libjpeg/jpeg-8a
%.o:%.c
	$(CC) -c $^ -o $@ $(INCL)
	
$(TARGET):$(OBJS)
	$(CC) $^ -o $@  $(LIBS)
	cp $@ ~/tftp
	
clean:
	rm $(TARGET) $(OBJS)

