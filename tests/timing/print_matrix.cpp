/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

/* Note: this has to have the same template params as cml::matrix<>: */
template<typename Element, class ArrayType> std::ostream&
operator<<(std::ostream& os, const cml::matrix<Element,ArrayType>& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < m.rows(); ++i) {
        os << "  [";
        for(size_t j = 0; j < m.cols(); ++j) {
            os << " " << m[i][j];
        }
        os << "]" << endl;
    }
    os << "]";
    return os;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
