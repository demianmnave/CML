# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

# Install all distributable headers:
FILE(GLOB_RECURSE FILELIST "*.h" "*.tpp")
INSTALL(FILES ${FILELIST} DESTINATION include/cml/mathlib)

# --------------------------------------------------------------------------
# vim:ft=cmake
