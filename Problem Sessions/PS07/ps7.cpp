#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

const int WORLD_SIZE = 20;
const int INIT_ANTS = 100;
const int INIT_BUGS = 5;
const int DOODLE_BUG = 1;
const int ANT = 2;
const int ANT_BREED = 3;
const int DOODLE_BREED = 8;
const int DOODLE_SATARVE = 3;

// Forward declare classes so we can reference them in World class
class Organism;
class Doodlebug;
class Ant;

class World
{
    friend class Organism;
    friend class Doodlebug;
    friend class Ant;

public:
    World();
    ~World();
    Organism *getAt(int x, int y);
    void setAt(int x, int y, Organism *org);
    void Display();
    void SimulateOneStep();

private:
    Organism *grid[WORLD_SIZE][WORLD_SIZE];
};

class Organism
{
    friend class World;

public:
    Organism();
    Organism(World *world, int x, int y);
    ~Organism();

    virtual void breed() = 0;  // Whether or not to breed
    virtual void move() = 0;   // Rules to move the critter
    virtual int getType() = 0; // return if ant or doodlebug
    virtual bool starve() = 0; // determine if organism starves

protected:
    int x, y;        // position in world
    bool moved;      // indicate if critter has moved in this turn
    int breeedTicks; // number of ticks since breeding
    World *world;
};

World::World()
{
    // Initialize world to have empty spaces
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
            grid[i][j] = NULL;
    }
}

World::~World()
{ // Free any non-null elements
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
        {
            if (grid[i][j] != NULL)
                delete (grid[i][j]);
        }
    }
}

Organism *World::getAt(int x, int y)
{ // Returns the entry stored in the grid array in the indeces given in the parameter
    if ((x >= 0) && (x < WORLD_SIZE) && (y >= 0) && (y < WORLD_SIZE))
        return grid[x][y];
    return NULL;
}

void World::setAt(int x, int y, Organism *org)
{ // Sets an organism to the indeces given in the parameter
    if ((x >= 0) && (x < WORLD_SIZE) && (y >= 0) && (y < WORLD_SIZE))
        grid[x][y] = org;
}

void World::Display()
{ // Function to display the world in ASCII
    cout << endl
         << endl;

    for (int j = 0; j < WORLD_SIZE; j++)
    {
        for (int i = 0; i < WORLD_SIZE; i++)
        {
            if (grid[i][j] == NULL)
                cout << ".";

            else if (grid[i][j]->getType() == ANT)
                cout << "o";

            else
                cout << "X";
        }
        cout << endl;
    }
}

void World::SimulateOneStep()
{
    // Function to simulate one turn in the world.
    // First, a flag for each organism is used to indicate if it have moved or not.
    // This is because we iterate through the grid starting from the top looking
    // for an organism to move. If one moves down, we don't want it to move again when we reach it.
    // First move doodlebugs, then ants, and if they are still alive, we breed them.

    int i, j;

    // Reset all organisms to not moved
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            if (grid[i][j] != NULL)
                grid[i][j]->moved = false;
        }
    }

    // Loop through cells and move if its a doodlebug
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            if ((grid[i][j] != NULL) && (grid[i][j]->getType() == DOODLE_BUG))
            {
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true; // MArk as moved
                    grid[i][j]->move();
                }
            }
        }
    }

    // Loop through cells and move if its an ant
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            if ((grid[i][j] != NULL) && (grid[i][j]->getType() == ANT))
            {
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }

    // Loop thorugh cells and check if we should starve
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            // Kill any bugs that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->getType() == DOODLE_BUG)
            {
                if (grid[i][j]->starve())
                {
                    delete (grid[i][j]);
                    grid[i][j] = NULL;
                }
            }
        }
    }

    // Loop through cells to check if we should breed
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            // Only breed organisms that have moved to avoid breeding any new organisms
            if ((grid[i][j] != NULL) && (grid[i][j]->moved == true))
                grid[i][j]->breed();
        }
    }
}

Organism::Organism()
    : world(NULL), moved(false), breeedTicks(0), x(0), y(0)
{
    // Intentionally left blank
}

Organism::Organism(World *wrld, int x, int y)
    : moved(false), breeedTicks(0)
{
    this->world = wrld;
    this->x = x;
    this->y = y;

    wrld->setAt(x, y, this);
}

Organism::~Organism()
{
    // Intentionally left empty
}

class Ant : public Organism
{
    friend class World;

public:
    Ant();
    Ant(World *world, int x, int y);

    // Must define virtual functions
    void breed();
    void move();
    int getType();

    // Ant does not starve
    bool starve() { return false; }
};

class Doodlebug : public Organism
{
    friend class World;

public:
    Doodlebug();
    Doodlebug(World *world, int x, int y);

    // Must define virtual functions
    void breed();
    void move();
    int getType();

    bool starve(); // Check if doodlebug is starving

private:
    int starveTicks; // Number of moves before starving
};

// ANT CONSTRUCTORS
Ant::Ant() : Organism()
{
    // Intentionally left blank
}
Ant::Ant(World *world, int x, int y) : Organism(world, x, y)
{
    // Intentionally left blank
}

void Ant::move()
{
    // pick a random direction to mnove
    int dir = rand() % 4;

    // try to move up if current position is not at na egde and is an empty spot
    if (dir == 0)
    {
        if ((y > 0) && (world->getAt(x, y - 1)) == NULL)
        {
            world->setAt(x, y - 1, world->getAt(x, y));
            // TODO world->setAt(x, y - 1, this);
            world->setAt(x, y, NULL);
            y--;
        }
    }

    // Try to move down
    else if (dir == 1)
    {
        if ((y < WORLD_SIZE - 1) && (world->getAt(x, y + 1) == NULL))
        {
            world->setAt(x, y + 1, world->getAt(x, y));
            world->setAt(x, y, NULL);
            y++;
        }
    }

    // try to move left
    else if (dir == 2)
    {
        if ((x > 0) && (world->getAt(x - 1, y) == NULL))
        {
            world->setAt(x - 1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x--;
        }
    }

    // try to move right
    else
    {
        if ((x < WORLD_SIZE - 1) && (world->getAt(x + 1, y) == NULL))
        {
            world->setAt(x + 1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x++;
        }
    }
}

int Ant::getType()
{
    // Get the type of an organism (ant)
    return ANT;
}

void Ant::breed()
{
    // increment the tick count for breeding
    // if it equals to the threshold of breeding, then create (breed)
    // a new ant in any available direction (u,d,l,r)
    // do not breed if there is no available space in any adjacent cell
    breeedTicks++;
    if (breeedTicks == ANT_BREED)
    {
        breeedTicks = 0;

        if ((y > 0) && (world->getAt(x, y - 1) == NULL))
            Ant *newANt = new Ant(world, x, y - 1);

        else if ((y < WORLD_SIZE - 1) && (world->getAt(x, y + 1) == NULL))
            Ant *newANt = new Ant(world, x, y + 1);

        else if (((x > 0) && (world->getAt(x - 1, y) == NULL)))
            Ant *newANt = new Ant(world, x - 1, y);

        else if (((x < WORLD_SIZE - 1) && (world->getAt(x + 1, y) == NULL)))
            Ant *newANt = new Ant(world, x + 1, y);
    }
}

// DOODLEBUG CONSTRUCTORS
Doodlebug::Doodlebug() : Organism()
{
    starveTicks = 0;
}
Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world, x, y)
{
    starveTicks = 0;
}

void Doodlebug::move()
{
    // Look in each direction and if a bug is found. move there and eat it
    if ((y > 0) && (world->getAt(x, y - 1) != NULL) && (world->getAt(x, y - 1)->getType() == ANT))
    {
        delete (world->grid[x][y - 1]); // kill ant
        world->grid[x][y - 1] = this;   // move to spot
        world->setAt(x, y, NULL);
        starveTicks = 0; // reset hunger
        y--;
        return;
    }

    else if ((y < WORLD_SIZE - 1) && (world->getAt(x, y + 1) != NULL) && (world->getAt(x, y + 1)->getType() == ANT))
    {
        delete (world->grid[x][y + 1]);
        world->grid[x][y + 1] = this; // move to spot
        world->setAt(x, y, NULL);
        starveTicks = 0; // reset hunger
        y++;
        return;
    }

    else if ((x > 0) && (world->getAt(x - 1, y) != NULL) && (world->getAt(x - 1, y)->getType() == ANT))
    {
        delete (world->grid[x - 1][y]);
        world->grid[x - 1][y] = this; // move to spot
        world->setAt(x, y, NULL);
        starveTicks = 0; // reset hunger
        x--;
        return;
    }

    else if ((x < WORLD_SIZE - 1) && (world->getAt(x + 1, y) != NULL) && (world->getAt(x + 1, y)->getType() == ANT))
    {
        delete (world->grid[x + 1][y]);
        world->grid[x + 1][y] = this; // move to spot
        world->setAt(x, y, NULL);
        starveTicks = 0; // reset hunger
        x++;
        return;
    }
}

void Doodlebug::breed()
{
    breeedTicks++;
    if (breeedTicks == DOODLE_BREED)
    {
        breeedTicks = 0;

        if ((y > 0) && (world->getAt(x, y - 1) == NULL))
            Doodlebug *newDoodle = new Doodlebug(world, x, y - 1);

        else if ((y < WORLD_SIZE - 1) && (world->getAt(x, y + 1)) == NULL)
            Doodlebug *newDoodle = new Doodlebug(world, x, y + 1);

        else if (((x > 0) && (world->getAt(x - 1, y) == NULL)))
            Doodlebug *newDoodle = new Doodlebug(world, x - 1, y);

        else if (((x < WORLD_SIZE - 1) && (world->getAt(x + 1, y) == NULL)))
            Doodlebug *newDoodle = new Doodlebug(world, x + 1, y);
    }
}

int Doodlebug::getType()
{
    // Virtual function to return the type of an Organism (Doodlebug)
    return DOODLE_BUG;
}

bool Doodlebug::starve()
{
    // Returns true if the doodlebug should die, false if it should not
    if (starveTicks > DOODLE_SATARVE)
        return true;

    else
        return false;
}

// ############### MAIN FUNCTION ############### //

int main()
{
    string s;

    srand(time(NULL));
    World w;

    // Randomly create 100 ants;
    int antCount = 0;
    while (antCount < INIT_ANTS)
    {
        int x = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if (w.getAt(x, y) == NULL) // make sure ant is in an empty spot
        {
            antCount++;
            Ant *a1 = new Ant(&w, x, y);
        }
    }

    // Randomly create 5 doodlebugs
    int doodleCount = 0;
    while (doodleCount < INIT_BUGS)
    {
        int x = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if (w.getAt(x, y) == NULL) // make sure ant is in an empty spot
        {
            doodleCount++;
            Doodlebug *d1 = new Doodlebug(&w, x, y);
        }
    }

    // Run simulation until user cancels
    while (true)
    {
        w.Display();
        w.SimulateOneStep();
        cout << endl
             << "Press enter for the next step" << endl;
        getline(cin, s);
    }

    return 0;
}