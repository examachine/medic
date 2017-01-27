## INCLUDES = -I$(toplevel_src)/kernel/src

YACC := $(YACC) -d

bin_PROGRAMS = classgen

SUBDIRS = . autogen

classgen_SOURCES =  Application.cxx Parser.cxx Tag.cxx Attribute.cxx \
	DataSet.cxx Module.cxx IOD.cxx Message.cxx Pointer.cxx \
	dicom.lxx dicom-grammar.yxx

dicom.cxx: dicom-grammar.cxx

# Data files
DICTFILES = UIDDict.txt TAGDict.txt MODDict.txt CIODDict.txt \
            NIODDict.txt MESSAGEDict.txt TAGDict2.txt MODDict2.txt
DATAFILES = $(addprefix dictionaries/, $(DICTFILES))

DCGARGS = $(addprefix ../,$(DATAFILES))

.PHONY: autogen

autogen: classgen $(DATAFILES) # autogen-stamp
	@echo Generating adapter classes for dicom dictionaries
	cd autogen;\
	../classgen $(DCGARGS) gxx;\
	touch autogen-stamp

clean-local:
	rm autogen/autogen-stamp
	rm autogen/*.cxx autogen/*.hxx;
