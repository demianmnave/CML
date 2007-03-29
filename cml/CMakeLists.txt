# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

# Install all distributable headers:
# XXX This won't be necessary after the header directory is cleaned up.
FILE(GLOB_RECURSE DISTRIBUTABLE_HEADERS "*.h" "*.tpp")
LIST(REMOVE_ITEM
  DISTRIBUTABLE_HEADERS
  code_052306_1.h
  code_061106_1.h
  )

INSTALL(FILES ${DISTRIBUTABLE_HEADERS} DESTINATION include/cml)

# --------------------------------------------------------------------------
# vim:ft=cmake
