#pragma once

#include <GeometryCore/Primitives/Point2.h>

struct HitTestContext {
    Geometry::Point2<float> worldPoint2D; // Position of mouse click in world-space
    float distanceThreshold;
};

struct DragContext {
    Geometry::Vector2<float> worldDelta2D; // Offset of mouse position in world-space
};

enum class InteractedState
{
    Selected,
    Released,
    Dragged
};

class IInteractable
{
public:
    virtual ~IInteractable() = default;

    virtual bool HitTest(const HitTestContext& ctx) = 0;
    virtual void Move(const DragContext& ctx) = 0;

    InteractedState State() const noexcept { return m_state; }
    virtual void Select() noexcept { m_state = InteractedState::Selected; }
    virtual void Release() noexcept { m_state = InteractedState::Released; }
    virtual void Drag() noexcept { m_state = InteractedState::Dragged; }

private:
    InteractedState m_state = InteractedState::Released;
};