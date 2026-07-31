#pragma once

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

    virtual bool HitTest(float mousePosX, float mousePosY, float distanceThreshold) = 0;

    InteractedState State() const noexcept { return m_state; }
    virtual void Select() noexcept { m_state = InteractedState::Selected; }
    virtual void Release() noexcept { m_state = InteractedState::Released; }
    virtual void Drag() noexcept { m_state = InteractedState::Dragged; }

    virtual void MoveTo(float mousePosX, float mousePosY) = 0;

private:
    InteractedState m_state = InteractedState::Released;
};