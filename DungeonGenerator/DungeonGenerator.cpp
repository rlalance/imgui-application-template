#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(int width, int height): width(width), height(height), grid(height, std::vector<Tile>(width, Tile({}))),
                                                           randomEngine(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
    InitializeGrid();
}

void DungeonGenerator::InitializeGrid()
{
    std::vector<TileType> allTileTypes = { TileType::Wall, TileType::Floor, TileType::Corridor, TileType::Corner };

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            grid[y][x] = Tile(allTileTypes);
        }
    }

    DefineRules();
}

void DungeonGenerator::DefineRules()
{
    // Wall rules: Walls can only be next to other Walls.
    rules[TileType::Wall][Direction::North] = { TileType::Wall };
    rules[TileType::Wall][Direction::South] = { TileType::Wall };
    rules[TileType::Wall][Direction::East] = { TileType::Wall };
    rules[TileType::Wall][Direction::West] = { TileType::Wall };

    // Floor rules: Floors can be next to Walls or Corridors.
    rules[TileType::Floor][Direction::North] = { TileType::Floor, TileType::Wall, TileType::Corridor };
    rules[TileType::Floor][Direction::South] = { TileType::Floor, TileType::Wall, TileType::Corridor };
    rules[TileType::Floor][Direction::East] = { TileType::Floor, TileType::Wall, TileType::Corridor };
    rules[TileType::Floor][Direction::West] = { TileType::Floor, TileType::Wall, TileType::Corridor };

    // Corridor rules: Corridors can be next to Floors, Walls, or other Corridors.
    rules[TileType::Corridor][Direction::North] = { TileType::Floor, TileType::Wall, TileType::Corridor };
    rules[TileType::Corridor][Direction::South] = { TileType::Floor, TileType::Wall, TileType::Corridor };
    rules[TileType::Corridor][Direction::East] = { TileType::Floor, TileType::Wall, TileType::Corridor };
    rules[TileType::Corridor][Direction::West] = { TileType::Floor, TileType::Wall, TileType::Corridor };

    // Corner rules: A simple rule for corners.
    rules[TileType::Corner][Direction::North] = { TileType::Wall };
    rules[TileType::Corner][Direction::South] = { TileType::Floor };
    rules[TileType::Corner][Direction::East] = { TileType::Wall };
    rules[TileType::Corner][Direction::West] = { TileType::Floor };
}

bool DungeonGenerator::GenerateDungeon()
{
    InitializeGrid();

    while (true)
    {
        // 1. Find the cell with the lowest entropy (fewest possible states).
        auto cellCoords = FindLowestEntropyCell();

        // If no un-collapsed cells are found, the generation is complete.
        if (cellCoords.first == -1)
        {
            return true; // Success!
        }

        // 2. Collapse the chosen cell.
        CollapseCell(cellCoords.first, cellCoords.second);

        // 3. Propagate the changes to its neighbors.
        Propagate(cellCoords.first, cellCoords.second);
    }
}

std::pair<int, int> DungeonGenerator::FindLowestEntropyCell()
{
    int minEntropy = std::numeric_limits<int>::max();
    std::vector<std::pair<int, int>> lowestEntropyCells;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Tile& tile = grid[y][x];
            if (!tile.IsCollapsed())
            {
                int entropy = tile.possibleTypes.size();
                if (entropy < minEntropy)
                {
                    minEntropy = entropy;
                    lowestEntropyCells.clear();
                    lowestEntropyCells.push_back({x, y});
                }
                else if (entropy == minEntropy)
                {
                    lowestEntropyCells.push_back({x, y});
                }
            }
        }
    }

    // If no un-collapsed cells, return -1.
    if (lowestEntropyCells.empty())
    {
        return {-1, -1};
    }

    // Randomly choose from the cells with the lowest entropy to avoid artifacts.
    std::uniform_int_distribution<int> dist(0, lowestEntropyCells.size() - 1);
    return lowestEntropyCells[dist(randomEngine)];
}

void DungeonGenerator::CollapseCell(int x, int y)
{
    Tile& tile = grid[y][x];
    std::uniform_int_distribution<int> dist(0, tile.possibleTypes.size() - 1);
    TileType chosenType = tile.possibleTypes[dist(randomEngine)];
    tile.possibleTypes.clear();
    tile.possibleTypes.push_back(chosenType);
    tile.finalType = chosenType;
    tile.isCollapsed = true;
}

bool DungeonGenerator::Propagate(int x, int y)
{
    std::stack<std::pair<int, int>> propagationStack;
    propagationStack.push({x, y});

    while (!propagationStack.empty())
    {
        auto currentCoords = propagationStack.top();
        propagationStack.pop();
        int currentX = currentCoords.first;
        int currentY = currentCoords.second;

        // Check all four neighbors.
        if (!CheckAndPropagateNeighbor(currentX, currentY, currentX, currentY - 1, Direction::North, Direction::South, propagationStack)) return false;
        if (!CheckAndPropagateNeighbor(currentX, currentY, currentX, currentY + 1, Direction::South, Direction::North, propagationStack)) return false;
        if (!CheckAndPropagateNeighbor(currentX, currentY, currentX - 1, currentY, Direction::West, Direction::East, propagationStack)) return false;
        if (!CheckAndPropagateNeighbor(currentX, currentY, currentX + 1, currentY, Direction::East, Direction::West, propagationStack)) return false;
    }
    return true;
}

bool DungeonGenerator::CheckAndPropagateNeighbor(int fromX, int fromY, int toX, int toY, Direction fromDir,
    Direction toDir, std::stack<std::pair<int, int>>& stack)
{
    // Boundary check.
    if (toX < 0 || toX >= width || toY < 0 || toY >= height)
    {
        return true;
    }

    const Tile& fromTile = grid[fromY][fromX];
    Tile& toTile = grid[toY][toX];

    // Only propagate if the neighbor is not yet collapsed.
    if (toTile.IsCollapsed())
    {
        return true;
    }

    // Determine the allowed types for the neighbor based on the current tile's final type.
    const auto& allowedTypes = rules[fromTile.finalType][fromDir];
    size_t initialCount = toTile.possibleTypes.size();

    // Remove any impossible types from the neighbor's list.
    auto it = toTile.possibleTypes.begin();
    while (it != toTile.possibleTypes.end())
    {
        if (std::find(allowedTypes.begin(), allowedTypes.end(), *it) == allowedTypes.end())
        {
            it = toTile.possibleTypes.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Check for contradiction
    if (toTile.possibleTypes.empty())
    {
        return false;
    }

    // If a change occurred, push the neighbor onto the stack to propagate further.
    if (toTile.possibleTypes.size() < initialCount)
    {
        stack.push({toX, toY});
    }
    return true;
}

const std::vector<std::vector<Tile>>& DungeonGenerator::GetGrid() const
{
    return grid;
}
