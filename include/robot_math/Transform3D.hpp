#pragma once

#include <Eigen/Geometry>

namespace robot_math
{

using Vec3 = Eigen::Vector3d;
using Point3 = Eigen::Vector3d;
using Transform3D = Eigen::Isometry3d;

inline Transform3D identity()
{
    return Transform3D::Identity();
}

inline Transform3D inverse(const Transform3D& transform)
{
    return transform.inverse();
}

inline Transform3D compose(const Transform3D& a_from_b,
                           const Transform3D& b_from_c)
{
    return a_from_b * b_from_c;
}

inline Point3 transformPoint(const Transform3D& a_from_b,
                             const Point3& point_b)
{
    return a_from_b * point_b;
}

inline Vec3 transformVector(const Transform3D& a_from_b,
                            const Vec3& vector_b)
{
    return a_from_b.linear() * vector_b;
}

} // namespace robot_math