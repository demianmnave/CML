# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

include(target-functions)

# Settings to auto-create Vesion.h:
set(VERSION_FILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in")
set(VERSION_FILE_OUT "${CMAKE_BINARY_DIR}/cml/version.h")

macro(pad_string string_in pad_in space var_out)
  string(LENGTH ${string_in} len)
  math(EXPR count "${space} - ${len}" OUTPUT_FORMAT DECIMAL)
  string(REPEAT ${pad_in} ${count} padding)
  set(${var_out} "${padding}${string_in}")
endmacro()

set(VERSION_MAJOR ${CML_VERSION_MAJOR})
set(VERSION_MINOR ${CML_VERSION_MINOR})
set(VERSION_PATCH ${CML_VERSION_PATCH})

# Make a version number as <M><mmm><pp>, with minor and patch padded with
# 0s up to length 3 and 2, respectively:
pad_string(${VERSION_MINOR} "0" 3 _padded_minor)
pad_string(${VERSION_PATCH} "0" 2 _padded_patch)
# TODO These could be configurable.

# The version number and string:
set(VERSION_NUMBER "${VERSION_MAJOR}${_padded_minor}${_padded_patch}")
set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Complete the version update:
configure_file("${VERSION_FILE_IN}" "${VERSION_FILE_OUT}" @ONLY)
set_source_files_properties(${VERSION_FILE_OUT} PROPERTIES GENERATED TRUE)

set(GENERATED_HEADERS
  ${VERSION_FILE_OUT}
)

set(main_HEADERS
  cml.h
  matrix.h
  quaternion.h
  types.h
  util.h
  vector.h
)

set(common_HEADERS
  common/array_size_of.h
  common/basis_tags.h
  common/exception.h
  common/hash.h
  common/layout_tags.h
  common/memory_tags.h
  common/promotion.h
  common/size_tags.h
  common/storage_tags.h
  common/temporary.h
  common/traits.h
  common/type_util.h
)

set(common_mpl_HEADERS
  common/mpl/are_convertible.h
  common/mpl/are_same.h
  common/mpl/enable_if_arithmetic.h
  common/mpl/enable_if_array.h
  common/mpl/enable_if_convertible.h
  common/mpl/enable_if_pointer.h
  common/mpl/enable_if_reshapeable.h
  common/mpl/enable_if_same.h
  common/mpl/enable_if_t.h
  common/mpl/if_t.h
  common/mpl/int_c.h
  common/mpl/is_reshapeable.h
  common/mpl/is_same_pair.h
  common/mpl/is_statically_polymorphic.h
  common/mpl/item_at.h
  common/mpl/plus_c.h
  common/mpl/rebind.h
  common/mpl/type_map.h
  common/mpl/type_table.h
)

set(scalar_HEADERS
  scalar/binary_ops.h
  scalar/constants.h
  scalar/functions.h
  scalar/promotion.h
  scalar/traits.h
  scalar/unary_ops.h
)

set(storage_HEADERS
  storage/allocated_selector.h
  storage/any_selector.h
  storage/compiled_selector.h
  storage/external_selector.h
  storage/promotion.h
  storage/resize.h
  storage/selectors.h
  storage/type_util.h
)

set(vector_HEADERS
  vector/binary_node.h
  vector/binary_node.tpp
  vector/binary_ops.h
  vector/comparison.h
  vector/comparison.tpp
  vector/cross.h
  vector/cross_node.h
  vector/cross_node.tpp
  vector/cross_ops.h
  vector/dot.h
  vector/dot.tpp
  vector/dynamic.h
  vector/dynamic_allocated.h
  vector/dynamic_allocated.tpp
  vector/dynamic_const_external.h
  vector/dynamic_const_external.tpp
  vector/dynamic_external.h
  vector/dynamic_external.tpp
  vector/external.h
  vector/fixed.h
  vector/fixed_compiled.h
  vector/fixed_compiled.tpp
  vector/fixed_const_external.h
  vector/fixed_const_external.tpp
  vector/fixed_external.h
  vector/fixed_external.tpp
  vector/functions.h
  vector/functions.tpp
  vector/fwd.h
  vector/hadamard_product.h
  vector/ops.h
  vector/outer_product.h
  vector/outer_product_node.h
  vector/outer_product_node.tpp
  vector/outer_product_ops.h
  vector/perp_dot.h
  vector/perp_dot.tpp
  vector/products.h
  vector/promotion.h
  vector/readable_vector.h
  vector/readable_vector.tpp
  vector/scalar_node.h
  vector/scalar_node.tpp
  vector/scalar_ops.h
  vector/size_checking.h
  vector/size_checking.tpp
  vector/subvector.h
  vector/subvector_node.h
  vector/subvector_node.tpp
  vector/subvector_ops.h
  vector/subvector_ops.tpp
  vector/temporary.h
  vector/traits.h
  vector/triple_product.h
  vector/triple_product.tpp
  vector/types.h
  vector/type_util.h
  vector/unary_node.h
  vector/unary_node.tpp
  vector/unary_ops.h
  vector/vector.h
  vector/writable_vector.h
  vector/writable_vector.tpp
)

set(vector_detail_HEADERS
  vector/detail/check_or_resize.h
  vector/detail/combined_size_of.h
  vector/detail/resize.h
)

set(matrix_HEADERS
  matrix/array_size_of.h
  matrix/basis.h
  matrix/basis_node.h
  matrix/basis_node.tpp
  matrix/basis_ops.h
  matrix/binary_node.h
  matrix/binary_node.tpp
  matrix/binary_ops.h
  matrix/col_node.h
  matrix/col_node.tpp
  matrix/col_ops.h
  matrix/comparison.h
  matrix/comparison.tpp
  matrix/determinant.h
  matrix/determinant.tpp
  matrix/dynamic.h
  matrix/dynamic_allocated.h
  matrix/dynamic_allocated.tpp
  matrix/dynamic_external.h
  matrix/dynamic_external.tpp
  matrix/external.h
  matrix/fixed.h
  matrix/fixed_compiled.h
  matrix/fixed_compiled.tpp
  matrix/fixed_external.h
  matrix/fixed_external.tpp
  matrix/functions.h
  matrix/fwd.h
  matrix/hadamard_product.h
  matrix/inverse.h
  matrix/lu.h
  matrix/lu.tpp
  matrix/matrix.h
  matrix/matrix_product.h
  matrix/matrix_product.tpp
  matrix/ops.h
  matrix/promotion.h
  matrix/readable_matrix.h
  matrix/readable_matrix.tpp
  matrix/row_col.h
  matrix/row_node.h
  matrix/row_node.tpp
  matrix/row_ops.h
  matrix/scalar_node.h
  matrix/scalar_node.tpp
  matrix/scalar_ops.h
  matrix/size_checking.h
  matrix/size_checking.tpp
  matrix/temporary.h
  matrix/trace.h
  matrix/trace.tpp
  matrix/traits.h
  matrix/transpose.h
  matrix/transpose_node.h
  matrix/transpose_node.tpp
  matrix/transpose_ops.h
  matrix/types.h
  matrix/type_util.h
  matrix/unary_node.h
  matrix/unary_node.tpp
  matrix/unary_ops.h
  matrix/vector_product.h
  matrix/vector_product.tpp
  matrix/writable_matrix.h
  matrix/writable_matrix.tpp
)

set(matrix_detail_HEADERS
  matrix/detail/apply.h
  matrix/detail/check_or_resize.h
  matrix/detail/copy.h
  matrix/detail/determinant.h
  matrix/detail/determinant.tpp
  matrix/detail/generate.h
  matrix/detail/get.h
  matrix/detail/inverse.h
  matrix/detail/lu.h
  matrix/detail/lu.tpp
  matrix/detail/resize.h
  matrix/detail/transpose.h
)

set(quaternion_HEADERS
  quaternion/binary_node.h
  quaternion/binary_node.tpp
  quaternion/binary_ops.h
  quaternion/comparison.h
  quaternion/comparison.tpp
  quaternion/conjugate.h
  quaternion/conjugate_node.h
  quaternion/conjugate_node.tpp
  quaternion/conjugate_ops.h
  quaternion/conjugate_ops.tpp
  quaternion/cross_tags.h
  quaternion/dot.h
  quaternion/dot.tpp
  quaternion/fixed.h
  quaternion/fixed_compiled.h
  quaternion/fixed_compiled.tpp
  quaternion/functions.h
  quaternion/functions.tpp
  quaternion/fwd.h
  quaternion/imaginary.h
  quaternion/imaginary_node.h
  quaternion/imaginary_node.tpp
  quaternion/imaginary_ops.h
  quaternion/imaginary_ops.tpp
  quaternion/inverse.h
  quaternion/inverse_node.h
  quaternion/inverse_node.tpp
  quaternion/inverse_ops.h
  quaternion/inverse_ops.tpp
  quaternion/ops.h
  quaternion/order_tags.h
  quaternion/product.h
  quaternion/product.tpp
  quaternion/promotion.h
  quaternion/quaternion.h
  quaternion/readable_quaternion.h
  quaternion/readable_quaternion.tpp
  quaternion/scalar_node.h
  quaternion/scalar_node.tpp
  quaternion/scalar_ops.h
  quaternion/size_checking.h
  quaternion/temporary.h
  quaternion/traits.h
  quaternion/types.h
  quaternion/type_util.h
  quaternion/unary_node.h
  quaternion/unary_node.tpp
  quaternion/unary_ops.h
  quaternion/writable_quaternion.h
  quaternion/writable_quaternion.tpp
)

set(mathlib_HEADERS
  mathlib/axis_order.h
  mathlib/constants.h
  mathlib/coordinate_conversion.h
  mathlib/coordinate_conversion.tpp
  mathlib/euler_order.h
  mathlib/frustum.h
  mathlib/frustum.tpp
  mathlib/mathlib.h
  mathlib/random_unit.h
  mathlib/random_unit.tpp
)

set(mathlib_vector_HEADERS
  mathlib/vector/angle.h
  mathlib/vector/angle.tpp
  mathlib/vector/generators.h
  mathlib/vector/misc.h
  mathlib/vector/misc.tpp
  mathlib/vector/orthonormal.h
  mathlib/vector/orthonormal.tpp
  mathlib/vector/products.h
  mathlib/vector/rotation.h
  mathlib/vector/rotation.tpp
  mathlib/vector/transform.h
  mathlib/vector/transform.tpp
)

set(mathlib_matrix_HEADERS
  mathlib/matrix/basis.h
  mathlib/matrix/basis.tpp
  mathlib/matrix/concat.h
  mathlib/matrix/concat.tpp
  mathlib/matrix/generators.h
  mathlib/matrix/invert.h
  mathlib/matrix/invert.tpp
  mathlib/matrix/misc.h
  mathlib/matrix/misc.tpp
  mathlib/matrix/projection.h
  mathlib/matrix/projection.tpp
  mathlib/matrix/rotation.h
  mathlib/matrix/rotation.tpp
  mathlib/matrix/scale.h
  mathlib/matrix/scale.tpp
  mathlib/matrix/size_checking.h
  mathlib/matrix/size_checking.tpp
  mathlib/matrix/temporary.h
  mathlib/matrix/transform.h
  mathlib/matrix/transform.tpp
  mathlib/matrix/translation.h
  mathlib/matrix/translation.tpp
)

set(mathlib_quaternion_HEADERS
  mathlib/quaternion/basis.h
  mathlib/quaternion/basis.tpp
  mathlib/quaternion/rotation.h
  mathlib/quaternion/rotation.tpp
)

set(util_HEADERS
  util/matrix_print.h
  util/matrix_print.tpp
  util/quaternion_print.h
  util/quaternion_print.tpp
  util/vector_hash.h
  util/vector_print.h
  util/vector_print.tpp
)

set(all_headers
  version.h.in
  ${main_HEADERS}
  ${common_HEADERS}
  ${common_mpl_HEADERS}
  ${scalar_HEADERS}
  ${storage_HEADERS}
  ${matrix_HEADERS}
  ${matrix_detail_HEADERS}
  ${quaternion_HEADERS}
  ${util_HEADERS}
  ${vector_HEADERS}
  ${vector_detail_HEADERS}
  ${mathlib_HEADERS}
  ${mathlib_vector_HEADERS}
  ${mathlib_matrix_HEADERS}
  ${mathlib_quaternion_HEADERS}
)

cml_add_library(cml INTERFACE
 SOURCES ${all_headers}
  PUBLIC FILE_SET headers TYPE HEADERS
  FILES ${all_headers} BASE_DIRS ${PROJECT_SOURCE_DIR}
  PUBLIC FILE_SET generated TYPE HEADERS
  FILES ${GENERATED_HEADERS} BASE_DIRS ${CMAKE_BINARY_DIR}
 FOLDER "/"
)
target_include_directories(cml INTERFACE
 $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
 $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
 $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

# Needs to be separate:
target_sources(cml PRIVATE ${GENERATED_HEADERS})
source_group("/" FILES ${GENERATED_HEADERS})