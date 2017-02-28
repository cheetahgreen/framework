#include "fw/numerical/GeometricIntersections.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "glm/glm.hpp"

TEST(intersectSegments, ShouldHandleCollinearCaseSameDirection)
{
    auto result = fw::intersectSegments<glm::dvec2, double>(
        {1.0, 1.0},
        {2.0, 2.0},
        {-1.0, -1.0},
        {10.0, 10.0}
    );

    EXPECT_EQ(fw::GeometricIntersectionKind::Infinite, result.kind);
}

TEST(intersectSegments, ShouldHandleCollinearNonColliding)
{
    auto result = fw::intersectSegments<glm::dvec2, double>(
        {1.0, 1.0},
        {2.0, 2.0},
        {5.0, 5.0},
        {10.0, 10.0}
    );

    EXPECT_EQ(fw::GeometricIntersectionKind::None, result.kind);
}

TEST(intersectSegments, ShouldHandleParallelCase)
{
    auto result = fw::intersectSegments<glm::dvec2, double>(
        {1.0, 1.0},
        {3.0, 3.0},
        {1.0, 4.0},
        {5.0, 8.0}
    );

    EXPECT_EQ(fw::GeometricIntersectionKind::None, result.kind);
}

TEST(intersectSegments, ShouldHandleSingleIntersection)
{
    auto result = fw::intersectSegments<glm::dvec2, double>(
        {1.0, 1.0},
        {2.0, 2.0},
        {1.0, 2.0},
        {2.0, 1.0}
    );

    EXPECT_EQ(fw::GeometricIntersectionKind::Single, result.kind);
    EXPECT_DOUBLE_EQ(0.5, result.t0);
}

TEST(intersectSegments, ShouldHandlePerpendicularNonColliding)
{
    auto result = fw::intersectSegments<glm::dvec2, double>(
        {1.0, 1.0},
        {3.0, 3.0},
        {3.0, 5.0},
        {5.0, 3.0}
    );

    EXPECT_EQ(fw::GeometricIntersectionKind::None, result.kind);
}

TEST(intersectSegments, ShouldHandleNonParallelCommonEnd)
{
    auto result = fw::intersectSegments<glm::dvec2, double>(
        {1.0, 1.0},
        {3.0, 3.0},
        {3.0, 3.0},
        {5.0, 1.0}
    );

    EXPECT_EQ(fw::GeometricIntersectionKind::Single, result.kind);
    EXPECT_DOUBLE_EQ(1.0, result.t0);
}

TEST(intersectCircles, ShouldReturnNoneIfTooFarAway)
{
    auto result = fw::intersectCircles<glm::dvec2, double>(
        {0.0, 0.0},
        1.0,
        {10.0, 10.0},
        1.0
    );

    EXPECT_EQ(0, result.size());
}

TEST(intersectCircles, ShouldReturnTwoIntersectionsWhenIntersectingDeeply)
{
    auto result = fw::intersectCircles<glm::dvec2, double>(
        {0.0, 0.0},
        4.0,
        {5.0, 0.0},
        4.0
    );

    EXPECT_EQ(2, result.size());

    if (result[0].y > result[1].y) { std::swap(result[0], result[1]); }

    EXPECT_DOUBLE_EQ(5.0/2, result[0].x);
    EXPECT_DOUBLE_EQ(-sqrt(39)/2, result[0].y);

    EXPECT_DOUBLE_EQ(5.0/2, result[1].x);
    EXPECT_DOUBLE_EQ(sqrt(39)/2, result[1].y);
}

TEST(
    intersectCircles,
    ShouldReturnOneIntersectionWhenIntersectingAlmostIdeally
)
{
    auto result = fw::intersectCircles<glm::dvec2, double>(
        {0.0, 0.0},
        0.5,
        {1.0, 0.0},
        0.5
    );

    EXPECT_EQ(1, result.size());

    EXPECT_DOUBLE_EQ(0.5, result[0].x);
    EXPECT_DOUBLE_EQ(0, result[0].y);
}

TEST(
    intersectCircles,
    ShouldReturnOneIntersectionWhenSmallerCircleInsideAndContacting
)
{
    auto result = fw::intersectCircles<glm::dvec2, double>(
        {0.0, 0.0},
        1.0,
        {0.5, 0.0},
        0.5
    );

    EXPECT_EQ(1, result.size());

    EXPECT_DOUBLE_EQ(1.0, result[0].x);
    EXPECT_DOUBLE_EQ(0, result[0].y);
}

TEST(
    intersectCircles,
    ShouldReturnNoneWhenSmallerCircleInsideAndNotContacting
)
{
    auto result = fw::intersectCircles<glm::dvec2, double>(
        {0.0, 0.0},
        1.0,
        {0.5, 0.0},
        0.25
    );

    EXPECT_EQ(0, result.size());
}
