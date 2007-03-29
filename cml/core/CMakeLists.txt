# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

# Install all distributable headers:
FILE(GLOB FILELIST "*.h" "*.tpp")
INSTALL(FILES ${FILELIST} DESTINATION include/cml/core)
ADD_SUBDIRECTORY(meta)

# --------------------------------------------------------------------------
# vim:ft=cmake
