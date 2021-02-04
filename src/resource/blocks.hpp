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

class BaseBlock {
    public:
        const uint animationTime = 60;
};

class FlowerBlock: public BaseBlock {};