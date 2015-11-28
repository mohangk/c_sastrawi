CFLAGS=-Wall -g -O2 -Wextra -Isrc -I/usr/local/include -DNDEBUG $(OPTFLAGS)
LDFLAGS=-lpcre2-8  -L/usr/local/lib $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libsastrawi.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET)  tests

dev: CFLAGS=-Wall -g -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# $(SO_TARGET): $(TARGET) $(OBJECTS)
# 	$(CC) -shared -o $@ $(OBJECTS)
#
build:
	@mkdir -p build
	@mkdir -p bin

.PHONY: tests
tests: LDLIBS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind: all
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log"

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|prrk|tok|_)stpm?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

list:
	sh -c "$(MAKE) -p no_targets__ | awk -F':' '/^[a-zA-Z0-9][^\$$#\/\\t=]*:([^=]|$$)/ {split(\$$1,A,/ /);for(i in A)print A[i]}' | grep -v '__\$$' | sort"
