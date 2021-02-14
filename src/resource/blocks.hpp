#pragma once

#include <random>
#include <map>

enum Blocks {
    AIR,
    GRASS_SEEDS,
    INVASIVE_GRASS_SEEDS,
    MAX
};

class World;
class BlockData;

class BaseBlock {
    private:
        void loadBlockData(std::string filename);

    protected:
        std::random_device rd;
        std::default_random_engine e;
        std::uniform_real_distribution<float> chance;

    public:
        int animationTime = 0;
        bool isAnimated = false;
        bool useBlockStage = false;
        uint maxStages = 0;
        float growthChance = 0;
        std::map<Blocks, float> blockDrops;
        bool isMutable;
        float mutationChance;
        Blocks mutatedBlock;

        BaseBlock(std::string filename);
        virtual void tick(World& world, BlockData& blockData, int x, int y);
        std::map<Blocks, int> getDrops(const BlockData& bd);
};

class GrowableBlock: public BaseBlock {
    public:
        GrowableBlock(std::string filename);
        virtual void tick(World& world, BlockData& blockData, int x, int y) override;
};

class CollectorBlock: public BaseBlock {
    public:
        CollectorBlock(std::string filename);
};