
include ../build.mk

$(TARGET) : $(OBJS) ../libnginx.a
	gcc -o $@ $^ $(LDFLAGS) 


clean :
	rm -rf *.o $(TARGET)

