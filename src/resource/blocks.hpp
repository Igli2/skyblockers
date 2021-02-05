#pragma once

enum Blocks {
    AIR,
    DIRT,
    GABBRO,
    MONZONITE,
    PHYLLITE,
    FLINT,
    GRASS_SEEDS,
    BIOMASS,
    DAISY,
    COLLECTOR,
    MAX
};

class World;
class BlockData;

class BaseBlock {
    public:
        int animationTime;
        bool isAnimated;

        BaseBlock();
        virtual void tick(World& world, BlockData& blockData, int x, int y);
};

class FlowerBlock: public BaseBlock {
    public:
        virtual void tick(World& world, BlockData& blockData, int x, int y) override;
};

class CollectorBlock: public BaseBlock {};