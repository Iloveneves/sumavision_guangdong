
SUFFIX = arm-hisiv200-linux-

GCC     = $(SUFFIX)gcc
GPP     = $(SUFFIX)g++
CXX     = $(SUFFIX)gcc
LD      = $(SUFFIX)ld
AS      = $(SUFFIX)as
AR      = $(SUFFIX)ar
NM      = $(SUFFIX)nm
STRIP   = $(SUFFIX)strip
OBJCOPY = $(SUFFIX)objcopy
OBJDUMP = $(SUFFIX)objdump
RANLIB  = $(SUFFIX)ranlib

CP      = cp -f
RM      = rm -f
SORT    = sort
SED     = sed
TOUCH   = touch
MKDIR   = mkdir -p


SRC_DIR = ./src
PORTING_DIR = ./src/porting
DISK_DIR = ./src/disk_drv_adapt
FLASH_DIR = ./src/flash_drv_adapt
OS_DIR = ./src/os_drv_adapt
LIB_DIR = ./lib
BIN_DIR = ./bin
OBJ_DIR	= ./objs

STANDBY = $(BIN_DIR)/app/standby
EXE     = $(BIN_DIR)/app/tiartop

CFG_INC := -I./include
CFG_INC += -I./include/disk_drv_include
CFG_INC += -I./include/flash_drv_include
CFG_INC += -I./include/porting_include
CFG_INC += -I./include/os_drv_include
CFG_INC += -I./platform/include
CFG_INC += -I./platform/include/alsa
CFG_INC += -I./platform/include/ncurses
CFG_INC += -I./platform/include/sys


CFG_LIB := -L./lib
CFG_LIB += -L./platform/lib

CFLAGS := -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -DHAVE_INT64_SUPPORT -fPIC -DCHIP_TYPE_hi3716mv101 -DBOARD_TYPE_hi3716mstb
CFLAGS += -o2 -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
CFLAGS += $(CFG_INC)

HISILIB	:= \
	-lasound -leffect -lfreetype -lhi_common -lhi_ecs -lhi_mpi \
	-lhigo -lhigoadp -lhipng -ljpeg -ljpge \
	-lpetimer -lplayer -ltde -lz

MIDLIB := \
	-lrocme
	

LIB_SDK = -Wl,--start-group -lpthread -lrt -ldl -lm $(HISILIB) $(MIDLIB) -Wl,--end-group,--no-wchar-size-warning 


OBJS := $(OBJ_DIR)/Rocme_Porting_Base.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Cas.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Demux.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Eeprom.o
#OBJS += $(OBJ_DIR)/Rocme_Porting_Errno.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Event.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Av.o
OBJS += $(OBJ_DIR)/Rocme_Porting_File.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Flash.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Frontpanel.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Graphics.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Media.o
#OBJS += $(OBJ_DIR)/Rocme_Porting_Mediaplayer.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Network.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Osp.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Product.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Smartcard.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Socket.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Stbinfo.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Tuner.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Upgrade.o
OBJS += $(OBJ_DIR)/Rocme_Porting_Player.o
OBJS += $(OBJ_DIR)/Rocme_storage.o
OBJS += $(OBJ_DIR)/main.o
OBJS += $(OBJ_DIR)/hi_os.o
OBJS += $(OBJ_DIR)/flash_drv_hi.o
OBJS += $(OBJ_DIR)/hi_adp_flash.o
OBJS += $(OBJ_DIR)/nand_raw.o
OBJS += $(OBJ_DIR)/hi_udisk.o
OBJS += $(OBJ_DIR)/scsiexe.o

STDBY_OBJ := $(OBJ_DIR)/standby.o




.PHONY: all

all: prepare $(OBJS) $(STDBY_OBJ)
	$(GPP) -Wall -o $(EXE) $(OBJS) $(LIB_SDK) $(CFG_LIB)
#	$(STRIP) $(EXE)
	$(GPP) -Wall -o $(STANDBY) $(STDBY_OBJ) $(LIB_SDK) $(CFG_LIB)
#	$(STRIP) $(STANDBY)
	mkyaffs2image ./ui/ ./bin/res.yaffs 1 1 
	mkyaffs2image ./bin/app ./bin/app.yaffs 1 1
	cp bin/app/tiartop /home/hisi/xqb/tiartop_rocme
	chmod a+r ./bin/res.yaffs
	chmod a+r ./bin/app.yaffs

prepare:
	$(MKDIR) ./bin
	$(MKDIR) ./bin/app
	$(MKDIR) $(OBJ_DIR)

clean:
	$(RM) $(EXE)
	$(RM) $(STANDBY)
	$(RM) ./bin/res.yaffs
	$(RM) ./bin/app.yaffs
	$(RM) $(OBJS)
	$(RM) $(STANDBY)
$(OBJ_DIR)/hi_os.o:$(OS_DIR)/hi_os.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/flash_drv_hi.o:$(FLASH_DIR)/flash_drv_hi.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/hi_adp_flash.o:$(FLASH_DIR)/hi_adp_flash.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@	
$(OBJ_DIR)/nand_raw.o:$(FLASH_DIR)/nand_raw.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@	
$(OBJ_DIR)/hi_udisk.o:$(DISK_DIR)/hi_udisk.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@	
$(OBJ_DIR)/scsiexe.o:$(DISK_DIR)/scsiexe.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@		
$(OBJ_DIR)/Rocme_Porting_Base.o:$(PORTING_DIR)/Rocme_Porting_Base.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Cas.o:$(PORTING_DIR)/Rocme_Porting_Cas.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Demux.o:$(PORTING_DIR)/Rocme_Porting_Demux.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Eeprom.o:$(PORTING_DIR)/Rocme_Porting_Eeprom.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Errno.o:$(PORTING_DIR)/Rocme_Porting_Errno.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Event.o:$(PORTING_DIR)/Rocme_Porting_Event.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Av.o:$(PORTING_DIR)/Rocme_Porting_Av.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_File.o:$(PORTING_DIR)/Rocme_Porting_File.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Flash.o:$(PORTING_DIR)/Rocme_Porting_Flash.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Frontpanel.o:$(PORTING_DIR)/Rocme_Porting_Frontpanel.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Graphics.o:$(PORTING_DIR)/Rocme_Porting_Graphics.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Media.o:$(PORTING_DIR)/Rocme_Porting_Media.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Mediaplayer.o:$(PORTING_DIR)/Rocme_Porting_Mediaplayer.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Network.o:$(PORTING_DIR)/Rocme_Porting_Network.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Osp.o:$(PORTING_DIR)/Rocme_Porting_Osp.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Product.o:$(PORTING_DIR)/Rocme_Porting_Product.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Smartcard.o:$(PORTING_DIR)/Rocme_Porting_Smartcard.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Socket.o:$(PORTING_DIR)/Rocme_Porting_Socket.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Stbinfo.o:$(PORTING_DIR)/Rocme_Porting_Stbinfo.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Tuner.o:$(PORTING_DIR)/Rocme_Porting_Tuner.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Upgrade.o:$(PORTING_DIR)/Rocme_Porting_Upgrade.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_Porting_Player.o:$(PORTING_DIR)/Rocme_Porting_Player.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/Rocme_storage.o:$(PORTING_DIR)/Rocme_storage.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/main.o:$(SRC_DIR)/main.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
$(OBJ_DIR)/standby.o:$(SRC_DIR)/standby.c
	@$(GCC) $(CFLAGS) $(include_path) -c $^ -o $@
