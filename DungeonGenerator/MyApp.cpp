#include "MyApp.h"

#include "CacheItem.h"
#include "CacheItemPolicy.h"
#include "MainWindowComponent.h"
#include "imgui.h"

#include <bitset>
#include <iostream>

void bitwise_demo()
{
    using std::bitset;
    using std::cout;

    constexpr unsigned int a = 0b10101010;  // 170 in decimal
    constexpr unsigned int b = 0b11001100;  // 204 in decimal
    constexpr unsigned int m = 0b00001111;  // Mask

    cout << "a = " << a << " (" << bitset<8>(a) << ")\n";
    cout << "b = " << b << " (" << bitset<8>(b) << ")\n";
    cout << "mask = " << m << " (" << bitset<8>(m) << ")\n";
    cout << "Bitwise Operations:\n";
    cout << "-------------------\n";

    // 1. Bitwise AND - Clears bits where either a or b is 0
    cout << "1. a & b \n"
        << bitset<8>(a) << "\n"
        << bitset<8>(b) << "\n"
        << "---------\n"
        << bitset<8>(a & b) << "\n"
        << "\n";

    // 2. Bitwise OR - Sets bits where either a or b is 1
    cout << "2. a | b = \n"
        << bitset<8>(a) << "\n"
        << bitset<8>(b) << "\n"
        << "---------\n"
        << bitset<8>(a | b) << "\n"
        << "\n";

    // 3. Bitwise XOR - Toggles bits
    cout << "3. a ^ b = \n"
        << bitset<8>(a) << "\n"
        << bitset<8>(b) << "\n"
        << "---------\n"
        << bitset<8>(a ^ b) << "\n"
        << "\n";

    // 4. Bitwise NOT - Inverts bits
    cout << "4. ~a = \n"
        << bitset<8>(a) << "\n"
        << "---------\n"
        << bitset<8>(~a) << "\n"
        << "\n";

    // 5. Left shift - Shift bits to the left, filling with 0s
    cout << "5. a << 1 = \n"
            << bitset<8>(a) << "\n"
            << "---------\n"
            << bitset<8>(a << 1) << "\n"
            << "\n";

    // 6. Right shift - Shift bits to the right, filling with 0s
    cout << "6. a >> 1 = \n"
            << bitset<8>(a) << "\n"
            << "---------\n"
            << bitset<8>(a >> 1) << "\n"
            << "\n";

    // 7. Clear specific bits - using AND with NOT mask
    // What is this technique?
    // This technique clears specific bits in a number to 0 using the AND (&) operator
    // combined with the NOT (~) operator applied to a bitmask.
    // The bitmask has 1s in the positions where we want to keep the bits
    // and 0s in the positions where we want to clear the bits.
    // When the AND operation is performed with the negated bitmask,
    // the bits in the original number that correspond to the 0s in the mask are cleared to 0,
    // while all other bits remain unchanged.
    // Example:
    // For a = 0b10101010 (170 in decimal) and mask = 0b00001111 (15 in decimal),
    // the result of (a & ~mask) is 0b10100000 (160 in decimal),
    // where the lower four bits have been cleared to 0.
    cout << "7. a & ~mask = " << " \n(" << bitset<8>(a & ~m) << ")\n";

    // 8. Set specific bits - using OR with mask
    // What is this technique?
    // This technique sets specific bits in a number to 1 using the OR (|) operator combined with a bitmask.
    // The bitmask has 1s in the positions where we want to set the bits and 0s elsewhere.
    // When the OR operation is performed with this bitmask,
    // the bits in the original number that correspond to the 1s in the mask are set to 1,
    // while all other bits remain unchanged.
    // Example:
    // For a = 0b10101010 (170 in decimal) and mask = 0b00001111 (15 in decimal),
    // the result of (a | mask) is 0b10101111 (175 in decimal),
    // where the lower four bits have been set to 1.
    cout << "8. a | mask = " << " \n(" << bitset<8>(a | m) << ")\n";

    // 9. Check if bit N is set - using AND and shift
    // What is this technique?
    // This technique checks if the N-th bit of a number is set (1) or not set (0)
    // by right-shifting the number N times and then performing a bitwise AND with 1.
    // If the result is 1, the N-th bit is set; otherwise, it is not set.
    // Example:
    // For a = 0b10101010 (170 in decimal) and N = 3,
    // right-shifting a by 3 gives 0b00010101 (21 in decimal).
    // Performing (21 & 1) results in 1, indicating that the 3rd bit of a is set.
    int N = 3;
    cout << "9. Bit " << N << " of a is " << (((a >> N) & 1) ? "set" : "not set") << "\n";

    // 10. Set bit N - using OR and shift
    // What is this technique?
    // This technique sets (turns to 1) the N-th bit of a number by using
    // the OR (|) operator combined with a bitmask created by shifting 1 to the left N times (1 << N).
    // The bitmask has a 1 at the N-th position and 0s elsewhere.
    // When the OR operation is performed with this bitmask,
    // the N-th bit of the original number is set to 1,
    // while all other bits remain unchanged.
    // Example:
    // For a = 0b10101010 (170 in decimal) and N = 3,
    // the bitmask (1 << 3) results in 0b00001000 (8 in decimal).
    // The result of (a | (1 << 3)) is 0b10101010 (170 in decimal),
    // where the 3rd bit has been set from 0 to 1.
    cout << "10. a with bit " << N << " set: " << (a | (1 << N)) << "\n";

    // 11. Clear bit N - using AND with NOT and shift
    // What is this technique?
    // This technique clears (sets to 0) the N-th bit of a number by using
    // the AND (&) operator combined with a bitmask created by shifting 1 to the left N times (1 << N)
    // and then negating it with the NOT (~) operator.
    // The negated bitmask has all bits set to 1 except for the N-th bit, which is 0.
    // When the AND operation is performed with this negated bitmask,
    // the N-th bit of the original number is cleared, while all other bits remain unchanged.
    // Example:
    // For a = 0b10101010 (170 in decimal) and N = 3,
    // the bitmask (1 << 3) results in 0b00001000 (8 in decimal).
    // The negated bitmask ~(1 << 3) is 0b11110111 (247 in decimal).
    // The result of (a & ~(1 << 3)) is 0b10100010 (162 in decimal),
    // where the 3rd bit has been cleared from 1 to 0.
    cout << "11. a with bit " << N << " cleared: " << (a & ~(1 << N)) << "\n";

    // 12. Toggle bit N - using XOR and shift
    // What is this technique?
    // This technique toggles (flips) the N-th bit of a number by using
    // the XOR (^) operator combined with a bitmask created by shifting 1 to the left N times (1 << N).
    // The XOR operation will change the bit at position N from 0 to 1 or from 1 to 0,
    // while leaving all other bits unchanged.
    // Example:
    // For a = 0b10101010 (170 in decimal) and N =
    // 3, the bitmask (1 << 3) results in 0b00001000 (8 in decimal).
    // The result of (a ^ (1 << 3)) is 0b10100010 (162 in decimal),
    // where the 3rd bit has been toggled from 1 to 0.
    cout << "12. a with bit " << N << " toggled: " << (a ^ (1 << N)) << "\n";

    // 13. Extract the lowest set bit - using AND with two's complement
    // What is this technique?
    // This technique extracts the lowest set bit from a number by performing a bitwise AND
    // between the number and its two's complement (which is equivalent to -a in signed integers).
    // The expression (a & -a) isolates the lowest set bit, effectively filtering out all other bits.
    // Example:
    // For
    //  a = 0b10101010 (170 in decimal),
    // -a = 0b01010110 (in two's complement representation).
    // The result of (a & -a) is 0b00000010 (2 in decimal), which is the lowest set bit of a.
    cout << "13. Lowest set bit of a: " << (a & -a) << " (" << bitset<8>(a & -a) << ")\n";

    // 14. Remove the lowest set bit - using AND with (a - 1)
    // What is this technique?
    // This technique removes the lowest set bit from a number by performing a bitwise AND
    // between the number and one less than the number (a - 1).
    // The expression (a & (a - 1)) effectively clears the lowest set bit
    // while leaving all other bits unchanged.
    cout << "14. a without lowest set bit: " << (a & (a - 1)) << " (" << bitset<8>(a & (a - 1)) << ")\n";

    // 15. Check if a is power of two - using AND with (a - 1)
    // What is this technique?
    // This technique checks if a number is a power of two by leveraging the property that
    // powers of two have exactly one bit set in their binary representation.
    // The expression (a & (a - 1)) clears the lowest set bit of a.
    // If a is a power of two, this operation will result in 0,
    // since there is only one bit set. Additionally, we check that a is not 0,
    // as 0 is not a power of two.
    cout << "15. a is " << ((a != 0 && (a & (a - 1)) == 0) ? "a power of two" : "not a power of two") << "\n";

    // 16. Count set bits (Brian Kernighan’s algorithm)
    // What is (Brian Kernighan’s algorithm)?
    // It is an efficient way to count the number of set bits (1s) in a binary representation of a number.
    // The algorithm works by repeatedly flipping the least significant set bit of the number to 0
    // and counting how many times this operation can be performed until the number becomes 0.
    // Example
    // For a = 0b10101010 (170 in decimal):
    // 1. Initial value: 0b10101010 (count = 0)
    // 2. After first iteration: 0b10101000 (count = 1)
    // 3. After second iteration: 0b10100000 (count = 2)
    // 4. After third iteration: 0b10000000 (count = 3)
    // 5. After fourth iteration: 0b00000000 (count = 4)
    // The loop runs 4 times, so there are 4 set bits in the original number.
    // This method is more efficient than checking each bit individually,
    // especially for numbers with a small number of set bits.
    unsigned int temp = a;
    int count = 0;
    while (temp)
    {
        temp &= (temp - 1);
        count++;
    }
    cout << "16. Number of set bits in a: " << count << "\n";

    // 17. Reverse bits (8-bit example) - using loop
    // What is this technique?
    // This technique reverses the order of bits in an 8-bit number by iteratively shifting and masking.
    // It initializes a result variable to 0, then for each bit position in the original number,
    // it shifts the result to the left and adds the least significant bit of the original number.
    // This process is repeated for all 8 bits, effectively reversing their order.
    // Example:
    // For a = 0b10101010 (170 in decimal):
    // 1. Start with rev = 0b00000000
    // 2. After processing each bit, rev becomes:
    //    - 1st bit: 0b00000001
    //    - 2nd bit: 0b00000010
    //    - 3rd bit: 0b00000101
    //    - 4th bit: 0b00001010
    //    - 5th bit: 0b00010101
    //    - 6th bit: 0b00101010
    //    - 7th bit: 0b01010101
    //    - 8th bit: 0b10101010
    // The final result is 0b01010101 (85 in decimal), which is the reverse of the original bit order.
    unsigned int rev = 0;
    for (int i = 0; i < 8; ++i)
    {
        rev <<= 1;
        rev |= (a >> i) & 1;
    }
    cout << "17. Reverse bits of a: " << rev << " (" << bitset<8>(rev) << ")\n";

    cout << std::endl;
}

MyApp::MyApp() : mCacheSystem(512), mGridSize(100), mTileSize(20.0f)
{
    mGenerator = std::make_unique<DungeonGenerator>(mGridSize, mGridSize);

    auto mainWindowComponent = std::make_unique<MainWindowComponent>();

    mainWindowComponent->mGridSize = mGridSize;
    mainWindowComponent->mTileSize = mTileSize;

    mainWindowComponent->onDungeonGenerationButtonClicked = [&]() { mDungeonGenerationRequested = true; };
    mainWindowComponent->onDungeonGenerationStarted = [&]() { mShowActivityIndicator = true; };
    mainWindowComponent->onDungeonGenerationCompleted = [&]() { mShowActivityIndicator = false; };

    AddComponent("Main", std::move(mainWindowComponent));

    mCacheSystem.AddItem(EvictionPolicy::AbsoluteExpiration, "ExampleItem",
                         std::make_unique<CacheItem>(std::chrono::seconds(60), std::string("This is a cached string")));
}

void MyApp::Update()
{
    mCacheSystem.Update();

    static bool firstRun = true;

    if (firstRun)
    {
        bitwise_demo();
        firstRun = false;
    }
}

void MyApp::Draw()
{
    App::Draw();

    auto mainWindowComponent = dynamic_cast<MainWindowComponent &>(GetComponent("Main"));

    if (mGridSize != mainWindowComponent.mGridSize)
    {
        mGridSize = mainWindowComponent.mGridSize;
        mGenerator = std::make_unique<DungeonGenerator>(mGridSize, mGridSize);
    }

    mTileSize = mainWindowComponent.mTileSize;

    if (mDungeonGenerationRequested)
    {
        mDungeonGenerationRequested = false;
        auto future = mTaskManager.submitTask([&]() {
            auto mainWindow = dynamic_cast<MainWindowComponent &>(GetComponent("Main"));

            mainWindow.onDungeonGenerationStarted();
            mGenerator->GenerateDungeon();
            mainWindow.onDungeonGenerationCompleted();
        });
    }

    DrawDungeonGrid();
}

void MyApp::DrawDungeonGrid() const
{
    const auto &grid = mGenerator->GetGrid();
    ImGui::Begin("Dungeon Grid");
    const ImVec2 spacing = {1, 1};
    ImVec2 cursor = ImGui::GetCursorScreenPos();

    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[y].size(); ++x)
        {
            ImColor tileColor;

            switch (grid[y][x].finalType)
            {
            case TileType::Wall:
                tileColor = ImColor(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray
                break;
            case TileType::Floor:
                tileColor = ImColor(0.8f, 0.8f, 0.8f, 1.0f); // Light gray
                break;
            case TileType::Corridor:
                tileColor = ImColor(0.6f, 0.6f, 0.6f, 1.0f); // Medium gray
                break;
            case TileType::Corner:
                tileColor = ImColor(0.4f, 0.4f, 0.4f, 1.0f); // Slightly darker gray
                break;
            default:
                tileColor = ImColor(0.0f, 0.0f, 0.0f, 1.0f); // Black for unknown
                break;
            }

            ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(cursor.x + x * (mTileSize + spacing.x), cursor.y + y * (mTileSize + spacing.y)),
                ImVec2(cursor.x + x * (mTileSize + spacing.x) + mTileSize,
                       cursor.y + y * (mTileSize + spacing.y) + mTileSize),
                tileColor);
        }
    }

    ImGui::End();
}

void MyApp::DrawMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                mExit = true;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                mShowAbout = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}