#************************************************************************
#*   $Version:$
#*   Package	: xmt_build
#*   Synopsis	: included by $(XMTBUILD)/proto/lang/<language>/generic.inc
#*   Purpose	: 
#*              This Makefile segment adds architecture support to
#*              $(XMTBUILD)/proto/lang/<language>/generic.inc
#*              It is intended to be included by that file only.
#*
#*   To add support for a new target architecture,  clone any existing
#*   <architecture>.inc file & alter program paths & flags appropriately.
#*   Remember to also update $(XMTBUILD)/proto/cshrc  to add the new
#*   architecture to XMTBUILD_SUPP_ARCHS.
#*
#*  Copyright (c) 1998	Neumann & Associates Information Systems Inc.
#*  			legal.info@neumann-associates.com
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
COMPILE.java.SunOS-sparc := javac
LD.java.SunOS-sparc	:= /bin/true
AR.java.SunOS-sparc	:= jar
LINT.java.SunOS-sparc	:= echo no lint installed for Java
DOC.java.SunOS-sparc	:= javadoc

#**********************************************************************
# This is the place to define flags that are specific to THIS language
# when compiled for THIS architecture.
#**********************************************************************
CFLAGS.java.SunOS-sparc	= 
LDFLAGS.java.SunOS-sparc	= 
ARFLAGS.java.SunOS-sparc	=
LINTFLAGS.java.SunOS-sparc	= 
DOCFLAGS.java.SunOS-sparc	=
LIB_PFX.java.SunOS-sparc	:= 
LIB_SFX.java.SunOS-sparc	:= .jar
EXE_PFX.java.SunOS-sparc	:= 
EXE_SFX.java.SunOS-sparc	:= 

#**********************************************************************
# rule for java files without namespace heirarchy
#**********************************************************************
$(OBJDIR)/%.class: $(SRCDIR)/%.java
	@mkdir -p $(OBJDIR)/$(JAVA_PKGROOT);
	@echo	$(CFLAGS) $(CFLAGS.java) $(CFLAGS.java.$(ARCH)) > $(OBJDIR)/$@.cflags ;
	$(COMPILE.java.$(ARCH))	@$(OBJDIR)/$@.cflags $< 

#**********************************************************************
# rule for java files with namespace heirarchy of arbitrary depth
#**********************************************************************
$(JAVA_PKGROOT)/%.class: subdirs=$(patsubst $(JAVA_PKGROOT)/%,%,$(dir $@))
$(JAVA_PKGROOT)/%.class: $(SRCDIR)/$(JAVA_PKGROOT)/%.java
	( mkdir -p $(OBJDIR)/$(JAVA_PKGROOT)/$(subdirs);\
	echo  $(CFLAGS) $(CFLAGS.java) $(CFLAGS.java.$(ARCH)) > \
	$(OBJDIR)/$(JAVA_PKGROOT)/$(subdirs)/$(notdir $@).cflags ;\
	$(COMPILE.java.$(ARCH)) @$(OBJDIR)/$(JAVA_PKGROOT)/$(subdirs)/$(notdir $@).cflags $<;\
	)

$(DOCDIR)/%.html: $(SRCDIR)/$(JAVA_PKGROOT)/%.java
	cd $(DOCDIR); $(DOC.java.$(ARCH)) $(DOCFLAGS) $(DOCFLAGS.java) $(DOCFLAGS.java.$(ARCH)) $<

.lib.$(LANGUAGE):	$(TGTDIR)/$(LIB_NM)
.lib.$(LANGUAGE):	$(TGTDIR)/$(LIB_NM)
$(TGTDIR)/$(LIB_NM): $(objs.$(LANGUAGE)) 
	(cd $(OBJDIR);  \
	echo $(ARFLAGS) $(ARFLAGS.$(LANGUAGE)) $(ARFLAGS.$(LANGUAGE).$(ARCH)) > $(LIB_NM).arflags;\
	$(AR.$(LANGUAGE).$(ARCH)) @$(LIB_NM).arflags $(LIB_NM) $(objs.$(LANGUAGE)) $(EXTRA_OBJS);)
	-/bin/mv $(OBJDIR)/$(LIB_NM) $(TGTDIR)/$(LIB_NM)


