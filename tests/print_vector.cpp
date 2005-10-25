/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */


/* Note: this has to have the same template params as cml::vector<>: */
template<typename Element, class ArrayType> std::ostream&
operator<<(std::ostream& os, const cml::vector<Element,ArrayType>& v)
{
    os << "[";
    for(size_t i = 0; i < v.size(); ++ i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
