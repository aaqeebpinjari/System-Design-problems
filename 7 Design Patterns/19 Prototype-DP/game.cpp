#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Prototype Interface
class GameObject {
public:
    virtual GameObject* clone() const = 0;
    virtual void render() const = 0;
    virtual ~GameObject() {}
};

// Concrete Prototype: Enemy
class Enemy : public GameObject {
private:
    string type;
    int health;
    int damage;
public:
    Enemy(string type, int health, int damage)
        : type(type), health(health), damage(damage) {}

    // Copy Constructor for cloning
    Enemy(const Enemy& other)
        : type(other.type), health(other.health), damage(other.damage) {}

    GameObject* clone() const override {
        return new Enemy(*this); // deep copy
    }

    void render() const override {
        cout << "Enemy Type: " << type << ", HP: " << health << ", Damage: " << damage << endl;
    }

    // Optional customization
    void setHealth(int hp) { health = hp; }
    void setDamage(int dmg) { damage = dmg; }
    void setType(string t) { type = t; }
};

// Prototype Factory / Registry
class GameObjectFactory {
private:
    unordered_map<string, GameObject*> prototypes;

public:
    void registerPrototype(string key, GameObject* prototype) {
        prototypes[key] = prototype;
    }

    GameObject* create(string key) {
        if (prototypes.count(key)) {
            return prototypes[key]->clone();
        }
        return nullptr;
    }

    ~GameObjectFactory() {
        for (auto& pair : prototypes) {
            delete pair.second;
        }
    }
};

// Main: Using Prototypes
int main() {
    GameObjectFactory factory;

    // Register prototypes
    factory.registerPrototype("goblin", new Enemy("Goblin", 100, 10));
    factory.registerPrototype("orc", new Enemy("Orc", 150, 20));

    // Clone objects
    GameObject* enemy1 = factory.create("goblin");
    GameObject* enemy2 = factory.create("orc");
    GameObject* enemy3 = factory.create("goblin");

    // Customize if needed
    dynamic_cast<Enemy*>(enemy3)->setHealth(80); // weaker goblin

    // Render
    enemy1->render();
    enemy2->render();
    enemy3->render();

    // Cleanup
    delete enemy1;
    delete enemy2;
    delete enemy3;

    return 0;
}
