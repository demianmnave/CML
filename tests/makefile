CML_OPTS=-DCML_NO_DEFAULT_EXPR_TRAITS \
	 -DCML_VECTOR_UNROLL_LIMIT=25 \
	 -DCML_VECTOR_DOT_UNROLL_LIMIT=25 \
	 -DCML_DEFAULT_ARRAY_LAYOUT="cml::row_major" \
	 -DCML_DEFAULT_ARRAY_ALLOC="std::allocator<void>" \
	 -DCML_ALWAYS_PROMOTE_TO_DEFAULT_LAYOUT \
	 -DCML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT \
	 -UCML_CHECK_VECTOR_EXPR_SIZES \
	 -UCML_AUTOMATIC_MATRIX_RESIZE_ON_ASSIGNMENT \
	 -UCML_CHECK_MATRIX_EXPR_SIZES


#-- CXX=ppc64-redhat-linux-g++
#-- CPP=$(CXX) -MM
#-- ##:: SEEMS TO BE BEST FOR GCC 4.0 Linux/ppc64
#-- ##:: Note--GCC4 doesn't like hand-unrolled matrices of 4x4 and larger
#-- CXXFLAGS=-ftemplate-depth-50 -O3 -m64 -mcpu=G5 -mtune=G5 -mpowerpc64 \
#-- 	 -mpowerpc-gpopt -fomit-frame-pointer -funroll-loops \
#-- 	 -finline-functions -finline-limit=2000000000 \
#-- 	 -DCML_2D_UNROLLER -DCML_MATRIX_UNROLL_LIMIT=25
#-- CPPFLAGS=-I.. $(CML_OPTS)
#-- exe=
#-- obj=.o
#-- rm=rm -f
#-- LINK.o = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)


#-- CXX=powerpc-apple-darwin8-g++-4.0.0
#-- CPP=$(CXX) -MM
#-- CXXFLAGS=-ftemplate-depth-50 -O3 \
#-- 	 -mpowerpc-gpopt -fomit-frame-pointer -funroll-loops \
#-- 	 -finline-functions -finline-limit=2000000000 \
#-- 	 -DCML_2D_UNROLLER -DCML_MATRIX_UNROLL_LIMIT=25
#-- CPPFLAGS=-I.. $(CML_OPTS)
#-- exe=
#-- obj=.o
#-- rm=rm -f
#-- LINK.o = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)

#-- CXX=powerpc-apple-darwin8-g++-4.0.1
#-- CPP=$(CXX) -MM
#-- CXXFLAGS=-ftemplate-depth-50 -O3 -mcpu=G4 -mtune=G4 -mpowerpc \
#-- 	 -mpowerpc-gpopt -fomit-frame-pointer -funroll-loops \
#-- 	 -finline-functions -finline-limit=2000000000 \
#-- 	 -DCML_2D_UNROLLER -DCML_MATRIX_UNROLL_LIMIT=25
#-- CPPFLAGS=-I.. $(CML_OPTS)
#-- exe=
#-- obj=.o
#-- rm=rm -f
#-- LINK.o = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)


#-- CXX=i386-redhat-linux-g++ -Wall -W
#-- CPP=$(CXX) -M
#-- ##:: SEEMS TO BE BEST FOR GCC 4.0 Linux/x86
#-- CXXFLAGS=-ftemplate-depth-1000 -march=pentium4 -mtune=pentium4 -O3 \
#-- 	 -fomit-frame-pointer -funroll-loops -finline-functions \
#-- 	 -finline-limit=2000000000 \
#--  	 -DCML_2D_UNROLLER -DCML_MATRIX_UNROLL_LIMIT=25 #\
#-- 	 -DCML_NO_2D_UNROLLER #
#-- CPPFLAGS=-I.. $(CML_OPTS) \
#-- 	-I$(HOME)/projects/external/build/exmat/include \
#-- 	-I$(HOME)/projects/external/build/ltl-1.7.10
#-- 
#-- exe=
#-- obj=.o
#-- rm=rm -f
#-- LINK.o = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)


CXX=icpc -Wcheck -U__GXX_WEAK__
CPP=icpc -M
##:: SEEMS TO BE BEST FOR Intel C++ V9.0 Linux/x86
CXXFLAGS=-ftemplate-depth-100 -xN -O3 -no-prec-div -ip -ipo \
	 -finline-functions -fomit-frame-pointer -unroll \
	 -DCML_USE_MAT_BINOP_REF \
	 -DCML_NO_2D_UNROLLER #\
	 -DCML_2D_UNROLLER -DCML_MATRIX_UNROLL_LIMIT=25 #\

#CPPFLAGS=-I.. $(CML_OPTS)
CPPFLAGS=-I.. $(CML_OPTS) \
	-I$(HOME)/projects/external/build/exmat/include \
	-I$(HOME)/projects/external/build/ltl-1.7.10
exe=
obj=.o
rm=rm -f
LINK.o = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH) -lpthread


#-- CXX=cl
#-- ##:: SEEMS TO BE BEST FOR VC++ (from Visual Studio 2003)
#-- CXXFLAGS=/nologo /O2 /Ob2 /Og /Oi /Ot /Oy /G7 /EHsc /I.. $(CML_OPTS)
#-- #CXXFLAGS=/nologo /Ox /EHsc /I..
#-- exe=.exe
#-- obj=.obj
#-- rm=erase
#-- 
#-- .cpp.obj:
#-- 	$(CXX) $(CXXFLAGS) -c $**
#-- 
#-- .obj.exe:
#-- 	$(CXX) $(CXXFLAGS) -o $@ $**

#-- CXX=mingw32-g++
#-- CPP=$(CXX) -MM
#-- ##:: SEEMS TO BE BEST FOR GCC 3.4.2
#-- CXXFLAGS=-ftemplate-depth-50 -march=pentium4 -mtune=pentium4 -O3 \
#-- -funroll-loops -finline-functions -finline-limit=100000000
#-- CPPFLAGS=-I.. $(CML_OPTS)
#-- exe=.exe
#-- obj=.obj
#-- rm=erase
#-- 
#-- .SUFFIXES:.cpp .o .exe
#-- 
#-- .cpp.obj:
#-- 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $**
#-- 
#-- .obj.exe:
#-- 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $**

#-- CXX=icl
#-- ##:: SEEMS TO BE BEST FOR Intel C++ 9.0
#-- CXXFLAGS=/nologo /O3 /Ob2 /Og /Oi /Ot /Oy /Oa /QxN /EHsc /Qip /Qipo \
#-- /Qtemplate-depth50 /I.. $(CML_OPTS)
#-- exe=.exe
#-- obj=.obj
#-- rm=erase
#-- 
#-- .cpp.obj:
#-- 	$(CXX) $(CXXFLAGS) -c $**
#-- 
#-- .obj.exe:
#-- 	$(CXX) $(CXXFLAGS) -o $@ $**

VEC_TEST_SRC	= vector_et1.cpp
VEC_TESTS	= vector_et1$(exe)

ALL_SRC		= $(VEC_TEST_SRC)
ALL_TESTS	= $(VEC_TESTS)

all: $(ALL_TESTS)

clean:
	$(rm) $(ALL_TESTS) *$(obj) .depend

# This allows special processing for files in subdirectories that do not
# have their own build setup:
.depend: $(ALL_SRC)
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) $^ > .depend
#	$(CPP) $(CPPFLAGS) $(CXXFLAGS) $^ | sed -e 's@\(.*\)\.o[ :]*@$*.o : @g' -e 's@\($*\)\.o[ :]*@\1.o $@ : @g' > $@
#	$(CPP) $(CPPFLAGS) $(CXXFLAGS) $^

include .depend
