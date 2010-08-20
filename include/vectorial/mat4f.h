#ifndef VECTORIAL_MAT4F_H
#define VECTORIAL_MAT4F_H

#ifndef VECTORIAL_SIMD4X4F_H
  #include "vectorial/simd4x4f.h"
#endif

#ifndef VECTORIAL_VEC4F_H
  #include "vectorial/vec4f.h"
#endif


namespace vectorial {
    

    class mat4f {
    public:

        simd4x4f value;
    
        inline mat4f() {}
        inline mat4f(const simd4x4f& v) : value(v) {}
        inline mat4f(vec4f v0, vec4f v1, vec4f v2, vec4f v3) : value(simd4x4f_create(v0.value, v1.value, v2.value, v3.value)) {}


        static mat4f identity() { mat4f m; simd4x4f_identity(&m.value); return m; }

        static mat4f perspective(float fovy, float aspect, float znear, float zfar) {
            simd4x4f m;
            simd4x4f_perspective(&m, fovy, aspect, znear, zfar);
            return m;
        }
        
        static mat4f ortho(float left, float right, float bottom, float top, float znear, float zfar) {
            simd4x4f m;
            simd4x4f_ortho(&m, left, right, bottom, top, znear, zfar);
            return m;
        }
        
        static mat4f lookAt(vec3f eye, vec3f center, vec3f up) {
            simd4x4f m;
            simd4x4f_lookat(&m, eye.value, center.value, up.value);
            return m;            
        }
    };
    
    
    vectorial_inline mat4f operator*(const mat4f& lhs, const mat4f& rhs) {
        mat4f ret;
        simd4x4f_matrix_mul(&lhs.value, &rhs.value, &ret.value);
        return ret;
    }

    vectorial_inline vec4f operator*(const mat4f& lhs, const vec4f& rhs) {
        vec4f ret;
        simd4x4f_matrix_vector_mul(&lhs.value, &rhs.value, &ret.value);
        return ret;
    }

    vectorial_inline vec3f transformVector(const mat4f& lhs, const vec3f& rhs) {
        vec3f ret;
        simd4x4f_matrix_vector3_mul(&lhs.value, &rhs.value, &ret.value);
        return ret;
    }

    vectorial_inline vec3f transformPoint(const mat4f& lhs, const vec3f& rhs) {
        vec3f ret;
        simd4x4f_matrix_point3_mul(&lhs.value, &rhs.value, &ret.value);
        return ret;
    }


}



#ifdef VECTORIAL_OSTREAM
//#include <ostream>

vectorial_inline std::ostream& operator<<(std::ostream& os, const vectorial::mat4f& v) {

    os << "[ ";
    os << simd4f_get_x(v.value.x) << ", ";
    os << simd4f_get_x(v.value.y) << ", ";
    os << simd4f_get_x(v.value.z) << ", ";
    os << simd4f_get_x(v.value.w) << " ; ";

    os << simd4f_get_y(v.value.x) << ", ";
    os << simd4f_get_y(v.value.y) << ", ";
    os << simd4f_get_y(v.value.z) << ", ";
    os << simd4f_get_y(v.value.w) << " ; ";

    os << simd4f_get_z(v.value.x) << ", ";
    os << simd4f_get_z(v.value.y) << ", ";
    os << simd4f_get_z(v.value.z) << ", ";
    os << simd4f_get_z(v.value.w) << " ; ";

    os << simd4f_get_w(v.value.x) << ", ";
    os << simd4f_get_w(v.value.y) << ", ";
    os << simd4f_get_w(v.value.z) << ", ";
    os << simd4f_get_w(v.value.w) << " ]";

    return os;
}
#endif




#endif
