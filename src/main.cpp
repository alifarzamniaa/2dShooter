#include "ECS/factory.h"
#include "ECS/world.h"

int main()
{
    World world(100);
    Factory factory(world, nullptr);
    return 0;
}
