#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <stack>
#include <map>
#include <future>
#include <utility>
#include <limits>
#include <algorithm>

// A simple enum to represent the different types of tiles.
// You would expand this with more complex tiles for a full dungeon.
enum class TileType
{
    Wall,
    Floor,
    Corner,
    Corridor,
    Empty
};

// Represents a single cell on our grid. It holds a list of all possible
// tile types it could be, until it is "collapsed" to a single type.
class Tile
{
public:
    std::vector<TileType> possibleTypes;
    TileType finalType;
    bool isCollapsed;

    Tile(const std::vector<TileType>& allPossibleTypes)
        : possibleTypes(allPossibleTypes), finalType(TileType::Empty), isCollapsed(false)
    {
    }

    // A check to see if the tile has been "collapsed" to a single type.
    bool IsCollapsed() const { return possibleTypes.size() <= 1; }
};

// An enum to represent cardinal directions for propagation.

enum class Direction { North, South, East, West };

// The main class that performs the Wave Function Collapse algorithm.
class DungeonGenerator
{
public:
    DungeonGenerator(int width, int height);

    // Initializes the grid with all tiles in a state of "superposition."
    void InitializeGrid();

    // Defines the adjacency rules for each tile type. This is the crucial part.
    void DefineRules();

    // The main generation loop. This function is designed to be run asynchronously.
    bool GenerateDungeon();

    // Finds the cell with the lowest number of possible states. This is the "observation" step.
    std::pair<int, int> FindLowestEntropyCell();

    // Collapses a cell by randomly selecting one of its possible tile types.
    void CollapseCell(int x, int y);

    // Propagates the constraints from a collapsed cell to its un-collapsed neighbors.
    bool Propagate(int x, int y);

    // Helper method to check and update a single neighbor's possible states.
    bool CheckAndPropagateNeighbor(
        int fromX, int fromY, int toX, int toY,
        Direction fromDir, Direction toDir,
        std::stack<std::pair<int, int>>& stack);

    // Returns the generated grid. This is what you would pass to your ImGui renderer.
    const std::vector<std::vector<Tile>>& GetGrid() const;

private:
    const int width;
    const int height;
    std::vector<std::vector<Tile>> grid;
    std::map<TileType, std::map<Direction, std::vector<TileType>>> rules;
    std::mt19937 randomEngine;
};
