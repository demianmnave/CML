# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

# Install all distributable headers:
FILE(GLOB_RECURSE FILELIST "*.h" "*.tpp")
INSTALL(FILES ${FILELIST} DESTINATION include/cml/et)

# --------------------------------------------------------------------------
# vim:ft=cmake
