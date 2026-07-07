#include <gtest/gtest.h>

#include <robot_math/Transform3D.hpp>

namespace rm = robot_math;

TEST(Transform3DTest, IdentityDoesNotChangePoint)
{
    const rm::Transform3D T = rm::identity();
    const rm::Point3 p{1.0, 2.0, 3.0};

    const rm::Point3 result = rm::transformPoint(T, p);

    EXPECT_TRUE(result.isApprox(p));
}

TEST(Transform3DTest, InverseUndoTransform)
{
    rm::Transform3D T = rm::Transform3D::Identity();
    T.translation() = rm::Vec3{1.0, 2.0, 3.0};
    T.linear() = Eigen::AngleAxisd(0.5, rm::Vec3::UnitZ()).toRotationMatrix();

    const rm::Transform3D T_inv = rm::inverse(T);

    const rm::Point3 p{4.0, 5.0, 6.0};
    const rm::Point3 transformed = rm::transformPoint(T, p);
    const rm::Point3 recovered = rm::transformPoint(T_inv, transformed);

    EXPECT_TRUE(recovered.isApprox(p));
}

TEST(Transform3DTest, CompositionAppliesRightTransformFirst)
{
    rm::Transform3D world_from_robot = rm::Transform3D::Identity();
    world_from_robot.translation() = rm::Vec3{10.0, 0.0, 0.0};

    rm::Transform3D robot_from_camera = rm::Transform3D::Identity();
    robot_from_camera.translation() = rm::Vec3{0.0, 5.0, 0.0};

    const rm::Transform3D world_from_camera =
        rm::compose(world_from_robot, robot_from_camera);

    const rm::Point3 p_camera{1.0, 2.0, 3.0};
    const rm::Point3 p_world =
        rm::transformPoint(world_from_camera, p_camera);

    EXPECT_TRUE(p_world.isApprox(rm::Point3{11.0, 7.0, 3.0}));
}

TEST(Transform3DTest, PointTransformIncludesTranslation)
{
    rm::Transform3D T = rm::Transform3D::Identity();
    T.translation() = rm::Vec3{10.0, 20.0, 30.0};

    const rm::Point3 p{1.0, 2.0, 3.0};
    const rm::Point3 result = rm::transformPoint(T, p);

    EXPECT_TRUE(result.isApprox(rm::Point3{11.0, 22.0, 33.0}));
}

TEST(Transform3DTest, VectorTransformIgnoresTranslation)
{
    rm::Transform3D T = rm::Transform3D::Identity();
    T.translation() = rm::Vec3{10.0, 20.0, 30.0};

    const rm::Vec3 v{1.0, 2.0, 3.0};
    const rm::Vec3 result = rm::transformVector(T, v);

    EXPECT_TRUE(result.isApprox(v));
}