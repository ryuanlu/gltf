include build.mk


TARGET:=gltf-read

PKG_CONFIG_PACKAGES:=json-c
$(TARGET)_src_files:=main.c gltf.c
$(TARGET)_cflags:=$(shell pkg-config --cflags $(PKG_CONFIG_PACKAGES)) -Wall -Og -g
$(TARGET)_ldflags:=$(shell pkg-config --libs $(PKG_CONFIG_PACKAGES)) -g

$(eval $(call define_c_targets,$(TARGET)))

all: $(TARGET)

clean: $(TARGET)_clean

