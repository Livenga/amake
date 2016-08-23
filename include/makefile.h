#ifndef _MAKEFILE_H
#define _MAKEFILE_H

const char *c_make =
"CC     = gcc\n"
"FLAGS  = -g -Wall\n\n"
"TARGET = %s\n"
"OBJDIR = objs\n\n"
"SOURCE = $(shell find src/ -name \\*.c)\n"
"OBJS   = $(addprefix $(OBJDIR)/, $(patsubst %%.c, %%.o, $(SOURCE)))\n"
"BINDIR = $(dir $(OBJS))\n\n"
"default:\n"
"\t[ -d  $(OBJDIR)  ] || mkdir -pv $(OBJDIR)\n"
"\t[ -d \"$(BINDIR)\" ] || mkdir -pv $(BINDIR)\n"
"\tmake $(TARGET)\n\n"
"$(TARGET):$(OBJS)\n"
"\t$(CC) -o $@ $^ $(FLAGS)\n\n"
"$(OBJDIR)/%%.o:%%.c\n"
"\t$(CC) -o $@ -c $<\n\n"
"clear:\n"
"\t[ ! -d $(OBJDIR) ] || rm -rv $(OBJDIR)\n"
"\t[ ! -f $(TARGET) ] || rm -v $(TARGET)\n\n"
"all:\n"
"\tmake clear default\n"
;

const char *tex_make =
"TEX    = platext\n"
"DIV    = divpdfmx\n"
"TARGET = %s\n"
"SOURCE = $(TARGET).tex\n"
"OBJC   = $(TARGET).dvi\n"
"PDF    = $(TARGET).pdf\n\n"
"$(PDF):$(OBJC)\n"
"\t$(DIV) $^\n"
"$(OBJC):$(SOURCE)\n"
"\t$(TEX) $^"
;
#endif
