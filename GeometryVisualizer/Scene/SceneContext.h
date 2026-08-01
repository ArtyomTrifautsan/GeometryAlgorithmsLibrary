#pragma once

#include <vector>
#include <memory>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObject.h>
#include <GeometryVisualizer/Scene/Interfaces/IInteractable.h>


class SceneContext {
private:
    std::vector<std::unique_ptr<ISceneObject>> m_objects;
    ISceneObject* m_selectedObject = nullptr;

public:
    void AddObject(std::unique_ptr<ISceneObject> obj)
    {
        m_objects.push_back(std::move(obj));
    }

    const std::vector<std::unique_ptr<ISceneObject>>& GetObjects() const
    {
        return m_objects;
    }

    void Update()
    {
        for (auto& obj : m_objects) {
            if (obj) {
                obj->Update();
            }
        }
    }

    //void Draw(sf::RenderTarget& target) const
    //{
    //    for (const auto& obj : m_objects) {
    //        if (obj) {
    //            obj->Draw(target); // или target.draw(*obj), если ISceneObject наследует sf::Drawable
    //        }
    //    }
    //}

    void SelectObject(ISceneObject* obj)
    {
        if (m_selectedObject == obj) return;

        if (m_selectedObject) {
            if (auto interactable = dynamic_cast<IInteractable*>(m_selectedObject)) {
                interactable->Release();
            }
        }

        m_selectedObject = obj;

        if (m_selectedObject) {
            if (auto interactable = dynamic_cast<IInteractable*>(m_selectedObject)) {
                interactable->Select();
            }
        }
    }

    ISceneObject* FindObjectAt(const HitTestContext& ctx) const
    {
        for (auto it = m_objects.rbegin(); it != m_objects.rend(); ++it) {
            if (auto interactable = dynamic_cast<IInteractable*>(it->get())) {
                if (interactable->HitTest(ctx)) {
                    return it->get();
                }
            }
        }
        return nullptr;
    }

    void SelectObjectAt(const HitTestContext& ctx)
    {
        SelectObject(FindObjectAt(ctx));
    }

    void ClearSelection()
    {
        SelectObject(nullptr);
    }

    ISceneObject* GetSelectedObject() const
    {
        return m_selectedObject;
    }
};