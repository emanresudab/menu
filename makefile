CC := cc
CCFLAGS := -lX11 -lXft -Os
LDFLAGS := `pkg-config --cflags freetype2`
DEBUGFLAGS := -fsanitize=undefined -fsanitize=address -fno-sanitize-recover -ggdb3
DEPS := cmenu.c cmenu.h config.h
TARGETS := cmenu

all: $(TARGETS)

debug: $(DEPS)
	@echo 'compiling with debug flags...'
	@$(CC) $< $(CCFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $(TARGETS)
	@echo 'done.'

clean:
	rm -f $(TARGETS)

$(TARGETS): $(DEPS)
	@echo 'compiling...'
	@$(CC) $< $(CCFLAGS) $(LDFLAGS) -o $@
	@echo 'done.'