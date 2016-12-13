#pragma once
#include "glm/glm.hpp"
#include <algorithm>
#include <vector>

namespace fw
{

enum class GeometricIntersectionKind
{
    Unknown,
    None,
    Single,
    Multiple,
    Infinite
};

template <typename TPrecision>
struct GeometricIntersectionResult
{
    GeometricIntersectionResult():
        kind{GeometricIntersectionKind::Unknown},
        t0{},
        t1{}
    {
    }

    GeometricIntersectionResult(const GeometricIntersectionKind &kind):
        kind{kind},
        t0{},
        t1{}
    {
    }

    GeometricIntersectionKind kind;
    TPrecision t0;
    TPrecision t1;
};

template <typename TVector2D, typename TPrecision>
GeometricIntersectionResult<TPrecision> intersectSegments(
    const TVector2D& aStart,
    const TVector2D& aEnd,
    const TVector2D& bStart,
    const TVector2D& bEnd
)
{
    GeometricIntersectionResult<TPrecision> result;
    // stackoverflow: how-do-you-detect-where-two-line-segments-intersect
    // http://stackoverflow.com/a/565282

    auto r = aEnd - aStart;
    auto s = bEnd - bStart;
    auto qp = bStart - aStart;

    // cross products
    auto rxs = r.x * s.y - r.y * s.x;
    auto qpxr = qp.x * r.y - qp.y * r.x;
    auto qpxs = qp.x * s.y - qp.y * s.x;

    const TPrecision eps = static_cast<TPrecision>(10e-6);
    if (std::abs(rxs) <= eps && std::abs(qpxr) <= eps)
    {
        auto t0 = glm::dot(bStart - aStart, r) / glm::dot(r, r);
        auto t1 = t0 + glm::dot(s, r) / glm::dot(r, r);
        if (t0 > t1) { std::swap(t0, t1); }
        t0 = std::max(static_cast<TPrecision>(0), t0);
        t1 = std::min(static_cast<TPrecision>(1), t1);
        if (0 <= t0 && t0 <= 1 && 0 <= t1 && t1 <= 1)
        {
            result.t0 = t0;
            result.t1 = t1;
            result.kind = GeometricIntersectionKind::Infinite;
        }
        else
        {
            result.kind = GeometricIntersectionKind::None;
        }

        return result;
    }

    if (std::abs(rxs) <= eps && std::abs(qpxr) > eps)
    {
        result.kind = GeometricIntersectionKind::None;
        return result;
    }

    if (std::abs(rxs) > eps)
    {
        auto t = qpxs / rxs;
        auto u = qpxr / rxs;
        if (0 <= t && t <= 1 && 0 <= u && u <= 1)
        {
            result.t0 = result.t1 = t;
            result.kind = GeometricIntersectionKind::Single;
            return result;
        }
    }

    result.kind = GeometricIntersectionKind::None;
    return result;
}

template <typename TVector2D, typename TPrecision>
std::vector<TVector2D> intersectCircles(
    TVector2D lhsOrigin,
    TPrecision lhsRadius,
    TVector2D rhsOrigin,
    TPrecision rhsRadius,
    TPrecision epsilon = 10e-6
)
{
    if (lhsRadius < rhsRadius)
    {
        std::swap(lhsOrigin, rhsOrigin);
        std::swap(lhsRadius, rhsRadius);
    }

    auto originVector = rhsOrigin - lhsOrigin;
    auto originsDistance = glm::length(originVector);

    if (originsDistance > lhsRadius + rhsRadius)
    {
        return {};
    }

    // rhs circle inside and is not contacting
    if (originsDistance < lhsRadius - rhsRadius)
    {
        return {};
    }

    if (originsDistance < epsilon)
    {
        // todo: this is actually not true
        return {};
    }

    auto originVectorPerpendicular = glm::normalize(TVector2D{
        -originVector.y,
        originVector.x
    });

    auto lhsRadiusSq = lhsRadius * lhsRadius;
    auto rhsRadiusSq = rhsRadius * rhsRadius;
    auto originsDistanceSq = originsDistance * originsDistance;

    auto a = (lhsRadiusSq - rhsRadiusSq + originsDistanceSq)
        / (2*originsDistance);

    auto h = static_cast<TPrecision>(sqrt(lhsRadiusSq - a*a));
    auto midpoint = glm::mix(lhsOrigin, rhsOrigin, a/originsDistance);

    if (h < epsilon)
    {
        return {midpoint};
    }

    return
    {
        midpoint + h * originVectorPerpendicular,
        midpoint - h * originVectorPerpendicular
    };
}

}
