/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity.hpp
*/

#pragma once

#include "Component.hpp"

/**
 * @brief The IEntity class represents an entity in the game engine.
 *
 * This class defines the interface for all entities in the game engine.
 * An entity is an object that can be updated and rendered in the game.
 * It can have multiple components attached to it.
 */
class IEntity {
    public:
        virtual ~IEntity() = default;

        /**
         * @brief Updates the entity.
         *
         * This method is called every frame to update the state of the entity.
         */
        virtual void update() = 0;

        /**
         * @brief Renders the entity.
         *
         * This method is called every frame to render the entity on the screen.
         */
        virtual void render() = 0;

        virtual void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) = 0;

        /**
         * @brief Adds a component to the entity.
         *
         * @param component The component to add.
         */
        virtual void addComponent(std::unique_ptr<Component> component) = 0;

        /**
         * @brief Removes a component from the entity.
         *
         * @param component The component to remove.
         */
        virtual void removeComponent(Component* component) = 0;

        /**
         * @brief Gets the list of components attached to the entity.
         *
         * @return A reference to the vector of components.
         */
        virtual std::vector<std::unique_ptr<Component>>& getComponents() = 0;

        /**
         * @brief Gets a component of a specific type attached to the entity.
         *
         * @param ti The type information of the component.
         * @return A pointer to the component if found, nullptr otherwise.
         */
        virtual Component* getComponentOfType(const std::type_info& ti) = 0;
};

class AbstractEntity : public IEntity {
    public:
        void update() override = 0;
        void render() override = 0;
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override = 0;

        void addComponent(std::unique_ptr<Component> component) override {
            components.push_back(std::move(component));
        }
        void removeComponent(Component* component) override {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (it->get() == component) {
                    components.erase(it);
                    return;
                }
            }
        }
        std::vector<std::unique_ptr<Component>>& getComponents() override {
            return components;
        }
        Component* getComponentOfType(const std::type_info& ti) override {
            for (auto& component : components) {
                if (typeid(*component) == ti) {
                    return component.get();
                }
            }
            return nullptr;
        }
    private:
        std::vector<std::unique_ptr<Component>> components;
};

class E_Bullet : public AbstractEntity {
    public:
        E_Bullet(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) {
            addComponent(std::make_unique<C_Transform>(position_x, position_y, size_x, size_y, velocity_x, velocity_y));
            addComponent(std::make_unique<C_Sprite>(path));
            addComponent(std::make_unique<C_Damage>(name, damage));
        }
        void update() override {}
        void render() override {
            auto* transform = dynamic_cast<C_Transform*>(getComponents()[0].get());
            auto* spriteComponent = dynamic_cast<C_Sprite*>(getComponents()[1].get());
            if (transform && spriteComponent) {
                transform->_position.x += transform->_velocity.x;
                transform->_position.y += transform->_velocity.y;
                Texture2D sprite = spriteComponent->_texture;
                Rectangle sourceRec = { 0.0f, 0.0f, (float)transform->_size.x, (float)transform->_size.y };
                Rectangle destRec = { (float)transform->_position.x, (float)transform->_position.y, (float)transform->_size.x * 2, (float)transform->_size.y * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
            }
        }
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override {}
};

class E_Player : public AbstractEntity {
    public:
        E_Player(std::string path, int position_x, int position_y, float size_x, float size_y) {
            addComponent(std::make_unique<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
            addComponent(std::make_unique<C_Health>(100));
            addComponent(std::make_unique<C_Sprite>(path));
            addComponent(std::make_unique<C_Hitbox>(33, 17));
            addComponent(std::make_unique<C_Score>());
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
        }
        void render() override {
            C_Score *score = dynamic_cast<C_Score*>(getComponents()[4].get());
            std::string scoreText = "Score: " + std::to_string(score->_score);
            DrawText(scoreText.c_str(), 250, 250, 30, WHITE);
            C_Hitbox *hitbox = dynamic_cast<C_Hitbox*>(getComponents()[3].get());
            if (hitbox->_status == 1) {
                if ((hitbox->_time % 2) != 0) {
                    int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
                    int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
                    int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
                    int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
                    int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
                    Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                    Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
                    Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                    Vector2 origin = { 0.0f, 0.0f };
                    DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                    for (auto& bullet : _bullets) {
                        bullet->render();
                    }
                    hitbox->_time -= 1;
                } else {
                    hitbox->_time -= 1;
                }
                if (hitbox->_time <= 0) {
                    hitbox->_time = 10;
                    hitbox->_status = 0;
                }
            } else if (hitbox->_status == 2) {
                int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
                int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
                int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
                int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
                Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                C_Transform *transform = dynamic_cast<C_Transform*>(getComponents()[0].get());
                if (transform->_animation <= 7) {
                    Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                    Rectangle sourceRec = { (float)(xSize * transform->_animation), 0, (float)xSize, (float)ySize };
                    Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                    Vector2 origin = { 0.0f, 0.0f };
                    DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                    transform->_animation += 1;
                }
                for (auto& bullet : _bullets) {
                    bullet->render();
                }
            } else {
                int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
                int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
                int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
                int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
                int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
                Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
                Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                for (auto& bullet : _bullets) {
                    bullet->render();
                } 
            }
        }
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override {
            auto newBullet = std::make_unique<E_Bullet>(path, name, damage, position_x, position_y, size_x, size_y, velocity_x, velocity_y);
            _bullets.push_back(std::move(newBullet));
        }
    private:
        std::vector<std::unique_ptr<E_Bullet>> _bullets;
};

class E_Enemy : public AbstractEntity {
    public:
        E_Enemy(std::string path, int position_x, int position_y, float size_x, float size_y) {
            addComponent(std::make_unique<C_Transform>(position_x, position_y, size_x, size_y, 0, 0));
            addComponent(std::make_unique<C_Health>(20));
            addComponent(std::make_unique<C_Sprite>(path));
            addComponent(std::make_unique<C_Hitbox>(65, 66));
        }
        void update() override {
            auto& transform = getComponents()[0];
            auto& health = getComponents()[1];
        }
        void render() override {
            C_Hitbox *hitbox = dynamic_cast<C_Hitbox*>(getComponents()[3].get());
            if (hitbox->_status == 1) {
                if ((hitbox->_time % 2) != 0) {
                    int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
                    int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
                    int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
                    int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
                    int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
                    Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                    Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
                    Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                    Vector2 origin = { 0.0f, 0.0f };
                    DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                    for (auto& bullet : _bullets) {
                        bullet->render();
                    }
                    hitbox->_time -= 1;
                } else {
                    hitbox->_time -= 1;
                }
                if (hitbox->_time <= 0) {
                    hitbox->_time = 10;
                    hitbox->_status = 0;
                }
            } else if (hitbox->_status == 2) {
                int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
                int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
                int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
                int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
                Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                C_Transform *transform = dynamic_cast<C_Transform*>(getComponents()[0].get());
                if (transform->_animation <= 7) {
                    Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                    Rectangle sourceRec = { (float)(xSize * transform->_animation), 0, (float)xSize, (float)ySize };
                    Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                    Vector2 origin = { 0.0f, 0.0f };
                    DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                    transform->_animation += 1;
                }
                for (auto& bullet : _bullets) {
                    bullet->render();
                }
            } else {
                int xPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.x;
                int yPos = dynamic_cast<C_Transform*>(getComponents()[0].get())->_position.y;
                int xSize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.x;
                int ySize = dynamic_cast<C_Transform*>(getComponents()[0].get())->_size.y;
                int animation = dynamic_cast<C_Transform*>(getComponents()[0].get())->_animation;
                Texture2D sprite = dynamic_cast<C_Sprite*>(getComponents()[2].get())->_texture;
                Rectangle sourceRec = { (float)(xSize * animation), 0, (float)xSize, (float)ySize };
                Rectangle destRec = { (float)xPos, (float)yPos, (float)xSize * 2, (float)ySize * 2 };
                Vector2 origin = { 0.0f, 0.0f };
                DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
                for (auto& bullet : _bullets) {
                    bullet->render();
                } 
            }
        }
        void newShoot(std::string path, std::string name, int damage, int position_x, int position_y, float size_x, float size_y, float velocity_x, float velocity_y) override {
            auto newBullet = std::make_unique<E_Bullet>(path, name, damage, position_x, position_y, size_x, size_y, velocity_x, velocity_y);
            _bullets.push_back(std::move(newBullet));
        }
    private:
        std::vector<std::unique_ptr<E_Bullet>> _bullets;
};

namespace Engine {
    C_Transform* getTransform(std::unique_ptr<IEntity> entity);
    C_Damage* getDamage(std::unique_ptr<IEntity> entity);
    C_Health* getHealth(std::unique_ptr<IEntity> entity);
    C_Sprite* getSprite(std::unique_ptr<IEntity> entity);
    C_Hitbox* getHitbox(std::unique_ptr<IEntity> entity);
    C_Score* getScore(std::unique_ptr<IEntity> entity);
    void setTransformPos(IEntity& entity, Vec2 newPos);
    void setTransformSize(IEntity& entity, Vec2 newSize);
    void setTransformVel(IEntity& entity, Vec2 newVel);
    void setTransformAni(IEntity& entity, int newAni);
    void setDamageName(IEntity& entity, std::string newName);
    void setDamageDamage(IEntity& entity, int newDamage);
    void setHealth(IEntity& entity, int newHealth);
    void setSpriteName(IEntity& entity, std::string newSpriteName);
    void setSpriteImage(IEntity& entity, Image newImage);
    void setSpriteTexture(IEntity& entity, Texture2D newTexture);
    void setHitboxSize(IEntity& entity, Vec2 newHitbox);
    void setHitboxTime(IEntity& entity, int newTime);
    void setHitboxStatus(IEntity& entity, int newStatus);
    void setScore(IEntity& entity, int newScore);

    template<typename T>
    T* getComponentRef(IEntity& entity)
    {
        T* component = dynamic_cast<T*>(entity.getComponentOfType(typeid(T)));
        if (component) {
            return (component);
        }
        return (nullptr);
    }
}