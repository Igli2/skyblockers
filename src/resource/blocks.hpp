#pragma once

#include <random>

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
    private:
        void loadBlockData(std::string filename);

    public:
        int animationTime = 0;
        bool isAnimated = false;
        bool useBlockStage = false;
        uint maxStages = 0;
        float growthChance = 0;

        BaseBlock(std::string filename);
        virtual void tick(World& world, BlockData& blockData, int x, int y);
};

class GrowableBlock: public BaseBlock {
    private:
        std::random_device rd;
        std::default_random_engine e;
        std::uniform_real_distribution<float> chance;

    public:
        GrowableBlock(std::string filename);
        virtual void tick(World& world, BlockData& blockData, int x, int y) override;
};

class CollectorBlock: public BaseBlock {
    public:
        CollectorBlock(std::string filename);
};