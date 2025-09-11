if(PORT STREQUAL "tbb")
    set(VCPKG_C_FLAGS "-mrtm")
    set(VCPKG_CXX_FLAGS "-mrtm")
endif()
if(PORT MATCHES "^(re2)$")
    set(VCPKG_LIBRARY_LINKAGE static)
endif()

# Note: All gn ports still use cl unless we figure out to pass it a toolchain somehow. 
if(PORT MATCHES "^(arrow|akali|arb|cello|chakracore|flint|folly|glog|zydis|graphicsmagick|freerdp|gtk|irrlicht|libde265|llfio|mongo-c-driver|tcl|nvtt)$")
    # akali -> typedef private void (T::*POnTimer)(void); -> error
    # arb -> probably related to flint!
    # cello -> redefines throw();
    # cgicc -> error: explicit instantiation of 'vector' not in a namespace enclosing 'std'
    # chakracore
    # mongo-c-driver -> strange redefinition error. Couldn't find why it claims that the defs are different. 
    # llfio -> code has correctness issues which cl accepts. (wrong thread_local and friend declaration)
    # gtk -> .res files in archives via /WHOLEARCHIVE not correctly handled by lld-link yet
    # libde265 -> probably some macro collision
    # arrow implicit deleted default constructor
    # libirecovery missing getopt linkage -> linkage general problem in msbuild ports since autolinkage is deactivated`?
    # graphicsmagick -> requires wrapping the allocators in namespace std
    # glog hardcodes builtin expected if build with clang-cl (#if 1 otehrwise #if 0) -> folly sees that. 
    # zydis,freerdp,irrlicht UTF-16 encoding in rc file
    # tcl -> requires nmake compiler setup
    # nvtt: too complicated compiler dependent behavior to fix quickly. 
    # TODO: Recheck flint
    message(STATUS "Falling back to cl!")
    unset(VCPKG_CHAINLOAD_TOOLCHAIN_FILE)
    unset(VCPKG_PLATFORM_TOOLSET)
    unset(VCPKG_VS_CMAKE_GENERATOR)
    set(ENV{PATH} "${LLVM_PATH_BACKUP}")
endif()

if(PORT MATCHES "^gettext$" AND "tools" IN_LIST FEATURES
   OR PORT MATCHES "^gettext-libintl$") # uses /EXTRACT unsupported by llvm-lib
    list(APPEND VCPKG_CMAKE_CONFIGURE_OPTIONS "-DCMAKE_AR=llvm-ar.exe")
    set(ENV{AR} "llvm-ar.exe")
endif()

if(CMAKE_PARENT_LIST_FILE MATCHES "-lto(\\\.|-)" AND NOT PORT MATCHES "(benchmark|gtest|pkgconf|^qt[a-z]+)")
    list(APPEND VCPKG_CMAKE_CONFIGURE_OPTIONS "-DVCPKG_USE_LTO:BOOL=TRUE")
endif()
if(PORT MATCHES "(qtconnectivity|qtsensors|qtspeech)")
  list(APPEND VCPKG_CMAKE_CONFIGURE_OPTIONS "-DQT_FEATURE_cxx20=ON")
  # cppwinrt uses Coroutines which is only supported with c++20 using clang
endif()
