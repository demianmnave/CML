# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

# Install all distributable headers:
# XXX This won't be necessary after the header directory is cleaned up.
FILE(GLOB FILELIST "*.h" "*.tpp")
LIST(REMOVE_ITEM FILELIST
  code_052306_1.h
  code_061106_1.h
  )

INSTALL(FILES ${FILELIST} DESTINATION include/cml)

SET(HEADER_SUBDIRS
  core
  et
  mathlib
  matrix
  matvec
  quaternion
  vector
  )
FOREACH(Dir ${HEADER_SUBDIRS})
  ADD_SUBDIRECTORY(${Dir})
ENDFOREACH(Dir)



# --------------------------------------------------------------------------
# vim:ft=cmake
