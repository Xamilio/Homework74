#include <iostream>
#include <memory>
using namespace std;

class Herbivore {
public:
    virtual ~Herbivore() = default;
    virtual void EatGrass() = 0;
    int GetWeight() const 
    { 
        return weight; 
    }

protected:
    int weight;
};

class Carnivore {
public:
    virtual ~Carnivore() = default;
    virtual void Eat(shared_ptr<Herbivore> herbivore) = 0;
    int GetPower() const
    { 
        return power; 
    }

protected:
    int power;
};

class Wildebeest : public Herbivore {
public:
    Wildebeest()
    {
        weight = 150;
    }

    void EatGrass() override 
    {
        weight += 10;
        cout << "Wildebeest ate grass and now weighs " << weight << " kg.\n";
    }
};

class Bison : public Herbivore 
{
public:
    Bison()
    {
        weight = 300;
    }

    void EatGrass() override 
    {
        weight += 10;
        cout << "Bison ate grass and now weighs " << weight << " kg.\n";
    }
};

class Lion : public Carnivore {
public:
    Lion() 
    {
        power = 200;
    }

    void Eat(shared_ptr<Herbivore> herbivore) override
    {
        if (power > herbivore->GetWeight()) 
        {
            power += 10;
            cout << "Lion ate a herbivore and now has power " << power << ".\n";
        }
        else
        {
            power -= 10;
            cout << "Lion failed to eat the herbivore and now has power " << power << ".\n";
        }
    }
};

class Wolf : public Carnivore {
public:
    Wolf() {
        power = 80;
    }

    void Eat(shared_ptr<Herbivore> herbivore) override
    {
        if (power > herbivore->GetWeight()) 
        {
            power += 10;
            cout << "Wolf ate a herbivore and now has power " << power << ".\n";
        }
        else
        {
            power -= 10;
            cout << "Wolf failed to eat the herbivore and now has power " << power << ".\n";
        }
    }
};

class Continent {
public:
    virtual ~Continent() = default;
    virtual shared_ptr<Herbivore> CreateHerbivore() = 0;
    virtual shared_ptr<Carnivore> CreateCarnivore() = 0;
};

class Africa : public Continent {
public:
    shared_ptr<Herbivore> CreateHerbivore() override 
    {
        return make_shared<Wildebeest>();
    }

    shared_ptr<Carnivore> CreateCarnivore() override
    {
        return make_shared<Lion>();
    }
};

class NorthAmerica : public Continent {
public:
    shared_ptr<Herbivore> CreateHerbivore() override
    {
        return make_shared<Bison>();
    }

    shared_ptr<Carnivore> CreateCarnivore() override
    {
        return make_shared<Wolf>();
    }
};

class AnimalWorld {
public:
    AnimalWorld(shared_ptr<Continent> continent)
    {
        herbivore = continent->CreateHerbivore();
        carnivore = continent->CreateCarnivore();
    }

    void MealsHerbivores()
    {
        herbivore->EatGrass();
    }

    void NutritionCarnivores()
    {
        carnivore->Eat(herbivore);
    }

private:
    shared_ptr<Herbivore> herbivore;
    shared_ptr<Carnivore> carnivore;
};

int main() {
    shared_ptr<Continent> africa = make_shared<Africa>();
    AnimalWorld world1(africa);
    world1.MealsHerbivores();
    world1.NutritionCarnivores();

    shared_ptr<Continent> northAmerica = make_shared<NorthAmerica>();
    AnimalWorld world2(northAmerica);
    world2.MealsHerbivores();
    world2.NutritionCarnivores();
}
