
include ../build.mk

$(TARGET) : $(OBJS) ../libnginx.a
	gcc -o $@ $^ $(LDFLAGS) 

check : $(TARGET)		
	./$^

clean :
	rm -rf *.o $(TARGET)

