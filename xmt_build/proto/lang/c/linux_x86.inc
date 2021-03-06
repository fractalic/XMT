#************************************************************************
#*   $Version:$
#*   Package	: xmt_build
#*   Synopsis	: included by $(XMTBUILD)/proto/lang/<language>/generic.inc
#*   Purpose	: 
#*              This Makefile segment adds architecture support to
#*              $(XMTBUILD)/proto/lang/<language>/generic.inc
#*
#*   To add support for a new target architecture,  clone any existing
#*   <architecture>.inc file & alter program paths & flags appropriately.
#*   Remember to also update $(XMTBUILD)/proto/cshrc  to add the new
#*   architecture to XMTBUILD_SUPP_ARCHS.
#*
#*  Copyright (c) 2017	Visionary Research Inc.
#*  			info@visionary-research.com
#*  Licensed under the Apache License, Version 2.0 (the "License");
#*  you may not use this file except in compliance with the License.
#*  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#*  
#*  Unless required by applicable law or agreed to in writing, software
#*  distributed under the License is distributed on an "AS IS" BASIS,
#*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#*  See the License for the specific language governing permissions and
#*  limitations under the License. 
#************************************************************************


#**********************************************************************
# define program paths...
#**********************************************************************
COMPILE.c.linux_x86	:= gcc
LD.c.linux_x86		:= gcc
AR.c.linux_x86		:= ar
DOC.c.linux_x86		:= $(XMTBUILD)/bin/srcdoc 
LINT.c.linux_x86	:= echo lint not installed
LIB_PFX.c.linux_x86	:= lib
LIB_SFX.c.linux_x86	:= .a
EXE_PFX.c.linux_x86	:= 
EXE_SFX.c.linux_x86	:= 

#**********************************************************************
# This is the place to define default flags that are specific to THIS 
# platform and THIS language.
#**********************************************************************
CFLAGS.c.linux_x86 += -Wall -Wno-unused-const-variable -m32 
LDFLAGS.c.linux_x86	+= $(CFLAGS.c.linux_x86) 
ARFLAGS.c.linux_x86	+= -r
LINTFLAGS.c.linux_x86	+= $(CFLAGS.c.linux_x86)
DOCFLAGS.c.linux_x86	+= 



$(OBJDIR)/%.o	: %.S
	@echo $(CFLAGS) $(CFLAGS.c) $(CFLAGS.c.$(ARCH)) > $@.cflags ; 
	$(COMPILE.c.$(ARCH)) @$@.cflags $< 

$(OBJDIR)/%.o	: %.s
	@echo $(CFLAGS) $(CFLAGS.c) $(CFLAGS.c.$(ARCH)) > $@.cflags ; 
	$(COMPILE.c.$(ARCH)) @$@.cflags $< 

$(OBJDIR)/%.o	: %.c
	@echo $(CFLAGS) $(CFLAGS.c) $(CFLAGS.c.$(ARCH)) > $@.cflags ; 
	$(COMPILE.c.$(ARCH)) @$@.cflags $< 

$(OBJDIR)/%.i	: /%.c
	@echo -E $(CFLAGS) $(CFLAGS.c) $(CFLAGS.c.$(ARCH)) > $@.cflags ; 
	$(COMPILE.c.$(ARCH)) @$@.cflags $< 

$(OBJDIR)/%.ln	: %.c
	@echo $(LINTFLAGS) $(LINTFLAGS.c) $(LINTFLAGS.c.$(ARCH)) > $@.lintflags ; 
	$(LINT.c.$(ARCH)) @$@.lintflags $< 

$(DOCDIR)/%.html: $(SRCDIR)/%.c
	@echo $(DOCFLAGS) $(DOCFLAGS.c) $(DOCFLAGS.c.$(ARCH)) > $@.docflags ; 
	$(DOC.c.$(ARCH)) @$@.docflags $< 

.lib.$(LANGUAGE):	$(TGTDIR)/$(LIB_NM)
$(LIB_NM): $(TGTDIR)/$(LIB_NM)
$(TGTDIR)/$(LIB_NM): $(objs.$(LANGUAGE)) $(EXTRA_OBJS)
	@echo 	$(ARFLAGS) $(ARFLAGS.$(LANGUAGE)) $(ARFLAGS.$(LANGUAGE).$(ARCH)) > $@.arflags;
	$(AR.$(LANGUAGE).$(ARCH)) @$@.arflags $@ $^ 	

.exe.$(LANGUAGE):	$(TGTDIR)/$(EXE_NM)
$(EXE_NM): $(TGTDIR)/$(EXE_NM)
$(TGTDIR)/$(EXE_NM): $(objs.$(LANGUAGE)) $(EXTRA_OBJS) 
	@echo $(LDFLAGS) $(LDFLAGS.$(LANGUAGE)) $(LDFLAGS.$(LANGUAGE).$(ARCH)) > $@.ldflags;
	$(LD.$(LANGUAGE).$(ARCH)) @$@.ldflags $^ \
	    $(LIBS) $(LIBS.$(LANGUAGE)) $(LIBS.$(LANGUAGE).$(ARCH)) 



