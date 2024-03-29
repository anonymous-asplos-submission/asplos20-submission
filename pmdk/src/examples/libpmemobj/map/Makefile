#
# Copyright 2015-2018, Intel Corporation
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in
#       the documentation and/or other materials provided with the
#       distribution.
#
#     * Neither the name of the copyright holder nor the names of its
#       contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
# examples/libpmemobj/map/Makefile -- build the map example
#
TOP := $(dir $(lastword $(MAKEFILE_LIST)))../../../../
include $(TOP)/src/common.inc

PROGS = mapcli data_store
LIBRARIES = map_ctree map_btree map_rbtree map_skiplist\
		map_hashmap_atomic map_hashmap_tx map_hashmap_rp\
		map_rtree map

LIBUV := $(call check_package, libuv --atleast-version 1.0)
ifeq ($(LIBUV),y)
PROGS += kv_server
else
$(info NOTE: Skipping kv_server because libuv is missing \
-- see src/examples/libpmemobj/map/README for details.)
endif

LIBS = -lpmemobj -pthread

ifeq ($(LIBUV),y)
LIBS += $(shell $(PKG_CONFIG) --libs libuv)
endif

include ../../Makefile.inc

CFLAGS += -I../
CFLAGS += -I../hashmap
CFLAGS += -I../tree_map
CFLAGS += -I../list_map
CFLAGS += -g -static

mapcli: mapcli.o libmap.a
data_store: data_store.o libmap.a
kv_server: kv_server.o libmap.a

libmap_ctree.o: map_ctree.o map.o ../tree_map/libctree_map.a
libmap_btree.o: map_btree.o map.o ../tree_map/libbtree_map.a
libmap_rtree.o: map_rtree.o map.o ../tree_map/librtree_map.a
libmap_rbtree.o: map_rbtree.o map.o ../tree_map/librbtree_map.a
libmap_hashmap_atomic.o: map_hashmap_atomic.o map.o ../hashmap/libhashmap_atomic.a
libmap_hashmap_tx.o: map_hashmap_tx.o map.o ../hashmap/libhashmap_tx.a
libmap_hashmap_rp.o: map_hashmap_rp.o map.o ../hashmap/libhashmap_rp.a
libmap_skiplist.o: map_skiplist.o map.o ../list_map/libskiplist_map.a

libmap.o: map.o map_ctree.o map_btree.o map_rtree.o map_rbtree.o map_skiplist.o\
	map_hashmap_atomic.o map_hashmap_tx.o map_hashmap_rp.o\
	../tree_map/libctree_map.a\
	../tree_map/libbtree_map.a\
	../tree_map/librtree_map.a\
	../tree_map/librbtree_map.a\
	../list_map/libskiplist_map.a\
	../hashmap/libhashmap_atomic.a\
	../hashmap/libhashmap_tx.a\
	../hashmap/libhashmap_rp.a

../tree_map/libctree_map.a:
	$(MAKE) -C ../tree_map ctree_map

../tree_map/libbtree_map.a:
	$(MAKE) -C ../tree_map btree_map

../tree_map/librtree_map.a:
	$(MAKE) -C ../tree_map rtree_map

../tree_map/librbtree_map.a:
	$(MAKE) -C ../tree_map rbtree_map

../list_map/libskiplist_map.a:
	$(MAKE) -C ../list_map skiplist_map

../hashmap/libhashmap_atomic.a:
	$(MAKE) -C ../hashmap hashmap_atomic

../hashmap/libhashmap_tx.a:
	$(MAKE) -C ../hashmap hashmap_tx

../hashmap/libhashmap_rp.a:
	$(MAKE) -C ../hashmap hashmap_rp
